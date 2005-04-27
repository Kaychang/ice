// **********************************************************************
//
// Copyright (c) 2003-2005 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <ReapThread.h>

using namespace std;
using namespace Demo;

ReapThread::ReapThread() :
    _timeout(IceUtil::Time::seconds(10)),
    _terminated(false)
{
}

void
ReapThread::run()
{
    Lock sync(*this);

    while(!_terminated)
    {
	timedWait(_timeout);

	if(!_terminated)
	{
	    list<SessionProxyPair>::iterator p = _sessions.begin();
	    while(p != _sessions.end())
	    {
		try
		{
		    //
		    // Session destruction may take time in a
		    // real-world example. Therefore the current time
		    // is computed for each iteration.
		    //
		    if((IceUtil::Time::now() - p->session->timestamp()) > _timeout)
		    {
			p->proxy->destroy();
			cout << "The session " << p->proxy->getName() << " has timed out." << endl;
    	    	    	p = _sessions.erase(p);
		    }
		    else
		    {
			++p;
		    }
    	    	}
		catch(const Ice::ObjectNotExistException&)
		{
		    p = _sessions.erase(p);
		}
	    }
	}
    }
}

void
ReapThread::terminate()
{
    Lock sync(*this);

    _terminated = true;
    notify();

    for(list<SessionProxyPair>::const_iterator p = _sessions.begin(); p != _sessions.end(); ++p)
    {
	try
	{
	    p->proxy->destroy();
	}
	catch(const Ice::Exception&)
	{
	    // Ignore.
	}
    }

    _sessions.clear();
}

void
ReapThread::add(const SessionPrx& proxy, const SessionIPtr& session)
{
    Lock sync(*this);
    _sessions.push_back(SessionProxyPair(proxy, session));
}
