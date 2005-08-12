// **********************************************************************
//
// Copyright (c) 2003-2005 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_INITIALIZE_H
#define ICEE_INITIALIZE_H

#include <IceE/CommunicatorF.h>
#include <IceE/PropertiesF.h>
#include <IceE/InstanceF.h>
#include <IceE/BuiltinSequences.h>

namespace Ice
{

ICE_API StringSeq argsToStringSeq(int, char*[]);
//
// This function assumes that the string sequence only contains
// elements of the argument vector. The function shifts the
// the argument vector elements so that the vector matches the
// contents of the sequence.
//
ICE_API void stringSeqToArgs(const StringSeq&, int&, char*[]);

ICE_API PropertiesPtr createProperties();
ICE_API PropertiesPtr createProperties(StringSeq&);
ICE_API PropertiesPtr createProperties(int&, char*[]);

ICE_API CommunicatorPtr initialize(int&, char*[], Int = ICEE_INT_VERSION);
ICE_API CommunicatorPtr initializeWithProperties(int&, char*[], const PropertiesPtr&, Int = ICEE_INT_VERSION);

ICE_API PropertiesPtr getDefaultProperties();
ICE_API PropertiesPtr getDefaultProperties(StringSeq&);
ICE_API PropertiesPtr getDefaultProperties(int&, char*[]);

}

namespace IceInternal
{

//
// Some Ice extensions need access to the Ice internal instance. Do
// not use this operation for regular application code! It is intended
// to be used by modules such as Freeze.
//
ICE_API InstancePtr getInstance(const ::Ice::CommunicatorPtr&);

}

#endif
