// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

namespace IceSSL
{
    using System;
    using System.Collections;
    using System.IO;
    using System.Net.Security;
    using System.Net.Sockets;
    using System.Security.Authentication;
    using System.Security.Cryptography;
    using System.Security.Cryptography.X509Certificates;
    using System.Threading;

    internal sealed class ServerContext : Context
    {
	internal SslStream authenticate(Socket fd, int timeout)
	{
	    NetworkStream ns = new NetworkStream(fd, true);
	    SslStream stream = new SslStream(ns, false, new RemoteCertificateValidationCallback(validationCallback),
					     null); // TODO: Need callbacks?

	    try
	    {
		AuthInfo info = new AuthInfo();
		info.stream = stream;
		info.done = false;
		IAsyncResult ar = stream.BeginAuthenticateAsServer(cert_, requireClientCert_, protocols_,
								   checkCRL_, new AsyncCallback(authCallback), info);
		lock(info)
		{
		    if(!info.done)
		    {
			if(!Monitor.Wait(info, timeout == -1 ? Timeout.Infinite : timeout))
			{
			    throw new Ice.TimeoutException("SSL authentication timed out after " + timeout + " msec");
			}
		    }
		    if(info.ex != null)
		    {
			throw info.ex;
		    }
		}
	    }
	    catch(Ice.LocalException ex)
	    {
		stream.Close();
		throw ex;
	    }
	    catch(IOException ex)
	    {
		stream.Close();

		if(IceInternal.Network.connectionLost(ex))
		{
		    throw new Ice.ConnectionLostException(ex);
		}
		throw new Ice.SocketException(ex);
	    }
	    catch(AuthenticationException ex)
	    {
		stream.Close();

		SslException e = new SslException(ex);
		e.ice_message_ = ex.Message;
		throw e;
	    }
	    catch(Exception ex)
	    {
		stream.Close();
		throw new Ice.SyscallException(ex);
	    }

	    return stream;
	}

	internal bool initialized()
	{
	    return cert_ != null;
	}

	internal ServerContext(Instance instance, X509Certificate2 cert) : base(instance)
	{
	    const string prefix = "IceSSL.Server.";
	    Ice.Properties properties = instance.communicator().getProperties();

	    if(cert != null)
	    {
		cert_ = cert;
	    }
	    else
	    {
		//
		// Load the certificate from a file if IceSSL.Server.CertFile is defined.
		//
		string certFile = properties.getProperty(prefix + "CertFile");
		string certPassword = properties.getProperty(prefix + "CertPassword");
		if(certFile.Length > 0)
		{
		    if(!File.Exists(certFile))
		    {
			logger_.error("IceSSL: server certificate file not found: " + certFile);
			Ice.FileException ex = new Ice.FileException();
			ex.path = certFile;
			throw ex;
		    }
		    try
		    {
			if(certPassword.Length == 0)
			{
			    cert_ = new X509Certificate2(certFile);
			}
			else
			{
			    cert_ = new X509Certificate2(certFile, certPassword);
			}
		    }
		    catch(CryptographicException ex)
		    {
			SslException e = new SslException(ex);
			e.ice_message_ = "attempting to load certificate from " + certFile;
			throw e;
		    }
		}
		else
		{
		    //
		    // Select the certificate from a store.
		    //
		    const string findPrefix = "IceSSL.Server.FindCert.";
		    Ice.PropertyDict certProps = properties.getPropertiesForPrefix(findPrefix);
		    if(certProps.Count > 0)
		    {
			X509Certificate2Collection certs = new X509Certificate2Collection();
			foreach(DictionaryEntry entry in certProps)
			{
			    string name = (string)entry.Key;
			    string val = (string)entry.Value;
			    if(val.Length > 0)
			    {
				string storeSpec = name.Substring(findPrefix.Length);
				X509Certificate2Collection coll = findCertificates(name, storeSpec, val);
				certs.AddRange(coll);
			    }
			}
			if(certs.Count == 0)
			{
			    const string msg = "no server certificates found";
			    logger_.error("IceSSL: " + msg);
			    SslException e = new SslException();
			    e.ice_message_ = msg;
			    throw e;
			}
			else if(certs.Count > 1)
			{
			    logger_.warning("IceSSL: multiple server certificates found");
			}
			cert_ = certs[0];
		    }
		}
	    }

	    // TODO: Review default value
	    requireClientCert_ = properties.getPropertyAsIntWithDefault(prefix + "RequireClientCert", 1) > 0;

	    protocols_ = parseProtocols(prefix + "Protocols");

	    // TODO: Review default value
	    checkCRL_ = properties.getPropertyAsIntWithDefault(prefix + "CheckCRL", 0) > 0;

	    // TODO: Review default value
	    checkCertName_ = properties.getPropertyAsIntWithDefault(prefix + "CheckCertName", 0) > 0;
	}

	private class AuthInfo
	{
	    internal SslStream stream;
	    volatile internal Exception ex;
	    volatile internal bool done;
	}

	private static void authCallback(IAsyncResult ar)
	{
	    AuthInfo info = (AuthInfo)ar.AsyncState;
	    lock(info)
	    {
		try
		{
		    info.stream.EndAuthenticateAsServer(ar);
		}
		catch(Exception ex)
		{
		    info.ex = ex;
		}
		finally
		{
		    info.done = true;
		    Monitor.Pulse(info);
		}
	    }
	}

	private bool validationCallback(object sender, X509Certificate certificate, X509Chain chain,
					SslPolicyErrors sslPolicyErrors)
	{
	    if(sslPolicyErrors == SslPolicyErrors.None)
	    {
		if(instance_.securityTraceLevel() >= 1)
		{
		    logger_.trace(instance_.securityTraceCategory(), "SSL certificate validation succeeded");
		}
		return true;
	    }

	    string message = "";
	    int errors = (int)sslPolicyErrors;
	    if((errors & (int)SslPolicyErrors.RemoteCertificateNotAvailable) > 0)
	    {
		if(requireClientCert_)
		{
		    if(instance_.securityTraceLevel() >= 1)
		    {
			logger_.trace(instance_.securityTraceCategory(),
				      "SSL certificate validation failed - client certificate not provided");
		    }
		    return false;
		}
		errors ^= (int)SslPolicyErrors.RemoteCertificateNotAvailable;
		message = message + "\nremote certificate not provided (ignored)";
	    }

	    if((errors & (int)SslPolicyErrors.RemoteCertificateNameMismatch) > 0)
	    {
		if(!checkCertName_)
		{
		    errors ^= (int)SslPolicyErrors.RemoteCertificateNameMismatch;
		    message = message + "\nremote certificate name mismatch (ignored)";
		}
		else
		{
		    if(instance_.securityTraceLevel() >= 1)
		    {
			logger_.trace(instance_.securityTraceCategory(),
				      "SSL certificate validation failed - remote certificate name mismatch");
		    }
		    return false;
		}
	    }

	    if(errors > 0)
	    {
		if(instance_.securityTraceLevel() >= 1)
		{
		    logger_.trace(instance_.securityTraceCategory(), "SSL certificate validation failed");
		}
		return false;
	    }

	    if(instance_.securityTraceLevel() >= 1)
	    {
		logger_.trace(instance_.securityTraceCategory(), "SSL certificate validation succeeded" + message);
	    }
	    return true;
	}

	private X509Certificate2 cert_;
	private bool requireClientCert_;
	private SslProtocols protocols_;
	private bool checkCRL_;
	private bool checkCertName_;
    }
}
