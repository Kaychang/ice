// **********************************************************************
//
// Copyright (c) 2003-2005 ZeroC, Inc. All rights reserved.
//
// This copy of Ice-E is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEE_ENDPOINT_FACTORY_F_H
#define ICEE_ENDPOINT_FACTORY_F_H

#include <IceE/Handle.h>

namespace IceInternal
{

class EndpointFactory;
ICE_API void incRef(EndpointFactory*);
ICE_API void decRef(EndpointFactory*);
typedef Handle<EndpointFactory> EndpointFactoryPtr;

}

#endif
