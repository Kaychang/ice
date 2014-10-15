// **********************************************************************
//
// Copyright (c) 2003-2014 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <TestAMDI.h>

using namespace Test;
using namespace IceUtil;
using namespace Ice;
using namespace std;

InitialI::InitialI()
{
}

void
InitialI::shutdown_async(const ::Test::AMD_Initial_shutdownPtr& cb,
                         const Ice::Current& current)
{
    current.adapter->getCommunicator()->shutdown();
    cb->ice_response();
}

void
InitialI::pingPong_async(const ::Test::AMD_Initial_pingPongPtr& cb,
                         const Ice::ObjectPtr& obj,
                         const Ice::Current&)
{
    cb->ice_response(obj);
}

void
InitialI::opOptionalException_async(const ::Test::AMD_Initial_opOptionalExceptionPtr& cb,
                                    const IceUtil::Optional< ::Ice::Int>& a,
                                    const IceUtil::Optional< ::std::string>& b,
                                    const IceUtil::Optional<Test::OneOptionalPtr>& o,
                                    const Ice::Current&)
{
    OptionalException ex;
    ex.a = a;
    ex.b = b;
    ex.o = o;
    cb->ice_exception(ex);
}

void
InitialI::opDerivedException_async(const ::Test::AMD_Initial_opDerivedExceptionPtr& cb,
                                   const IceUtil::Optional< ::Ice::Int>& a,
                                   const IceUtil::Optional< ::std::string>& b,
                                   const IceUtil::Optional<Test::OneOptionalPtr>& o,
                                   const Ice::Current&)
{
    DerivedException ex;
    ex.a = a;
    ex.b = b;
    ex.o = o;
    ex.ss = b;
    ex.o2 = o;
    cb->ice_exception(ex);
}

void
InitialI::opRequiredException_async(const ::Test::AMD_Initial_opRequiredExceptionPtr& cb,
                                    const IceUtil::Optional< ::Ice::Int>& a,
                                    const IceUtil::Optional< ::std::string>& b,
                                    const IceUtil::Optional<Test::OneOptionalPtr>& o,
                                    const Ice::Current&)
{
    RequiredException ex;
    ex.a = a;
    ex.b = b;
    ex.o = o;
    if(b)
    {
        ex.ss = b.get();
    }
    if(o)
    {
        ex.o2 = o.get();
    }
    cb->ice_exception(ex);
}

void
InitialI::opByte_async(const ::Test::AMD_Initial_opBytePtr& cb,
                       const IceUtil::Optional< ::Ice::Byte>& p1,
                       const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}


void
InitialI::opBool_async(const ::Test::AMD_Initial_opBoolPtr& cb,
                       const IceUtil::Optional<bool>& p1,
                       const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opShort_async(const ::Test::AMD_Initial_opShortPtr& cb,
                        const IceUtil::Optional< ::Ice::Short>& p1,
                        const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opInt_async(const ::Test::AMD_Initial_opIntPtr& cb,
                      const IceUtil::Optional< ::Ice::Int>& p1,
                      const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opLong_async(const ::Test::AMD_Initial_opLongPtr& cb,
                       const IceUtil::Optional< ::Ice::Long>& p1,
                       const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opFloat_async(const ::Test::AMD_Initial_opFloatPtr& cb,
                        const IceUtil::Optional< ::Ice::Float>& p1,
                        const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opDouble_async(const ::Test::AMD_Initial_opDoublePtr& cb,
                         const IceUtil::Optional< ::Ice::Double>& p1,
                         const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opString_async(const ::Test::AMD_Initial_opStringPtr& cb,
                         const IceUtil::Optional< ::std::string>& p1,
                         const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opCustomString_async(const ::Test::AMD_Initial_opCustomStringPtr& cb,
                               const IceUtil::Optional< Util::string_view>& p1,
                               const ::Ice::Current&)
{
    Optional<Util::string_view> p3;
    if(p1)
    {
        p3 = p1->to_string();
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opMyEnum_async(const ::Test::AMD_Initial_opMyEnumPtr& cb,
                         const IceUtil::Optional<Test::MyEnum>& p1,
                         const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opSmallStruct_async(const ::Test::AMD_Initial_opSmallStructPtr& cb,
                              const IceUtil::Optional<Test::SmallStruct>& p1,
                              const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opFixedStruct_async(const ::Test::AMD_Initial_opFixedStructPtr& cb,
                              const IceUtil::Optional<Test::FixedStruct>& p1,
                              const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opVarStruct_async(const ::Test::AMD_Initial_opVarStructPtr& cb,
                            const IceUtil::Optional<Test::VarStruct>& p1,
                            const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opOneOptional_async(const ::Test::AMD_Initial_opOneOptionalPtr& cb,
                              const IceUtil::Optional< Test::OneOptionalPtr>& p1,
                              const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opOneOptionalProxy_async(const ::Test::AMD_Initial_opOneOptionalProxyPtr& cb,
                                   const IceUtil::Optional< Test::OneOptionalPrx>& p1,
                                   const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opByteSeq_async(const ::Test::AMD_Initial_opByteSeqPtr& cb,
                          const IceUtil::Optional< ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> >& p1,
                          const ::Ice::Current&)
{
    Optional<pair<const Ice::Byte*, const Ice::Byte*> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opBoolSeq_async(const ::Test::AMD_Initial_opBoolSeqPtr& cb,
                          const IceUtil::Optional< ::std::pair<const bool*, const bool*> >& p1,
                          const ::Ice::Current&)
{
    Optional<pair<const bool*, const bool*> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opShortSeq_async(const ::Test::AMD_Initial_opShortSeqPtr& cb,
                           const IceUtil::Optional< ::std::pair<const ::Ice::Short*, const ::Ice::Short*> >& p1,
                           const ::Ice::Current&)
{
    Optional<pair<const Ice::Short*, const Ice::Short*> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opIntSeq_async(const ::Test::AMD_Initial_opIntSeqPtr& cb,
                         const IceUtil::Optional< ::std::pair<const ::Ice::Int*, const ::Ice::Int*> >& p1,
                         const ::Ice::Current&)
{
    Optional<pair<const Ice::Int*, const Ice::Int*> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opLongSeq_async(const ::Test::AMD_Initial_opLongSeqPtr& cb,
                          const IceUtil::Optional< ::std::pair<const ::Ice::Long*, const ::Ice::Long*> >& p1,
                          const ::Ice::Current&)
{
    Optional<pair<const Ice::Long*, const Ice::Long*> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opFloatSeq_async(const ::Test::AMD_Initial_opFloatSeqPtr& cb,
                           const IceUtil::Optional< ::std::pair<const ::Ice::Float*, const ::Ice::Float*> >& p1,
                           const ::Ice::Current&)
{
    Optional<pair<const Ice::Float*, const Ice::Float*> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opDoubleSeq_async(const ::Test::AMD_Initial_opDoubleSeqPtr& cb,
                            const IceUtil::Optional< ::std::pair<const ::Ice::Double*, const ::Ice::Double*> >& p1,
                            const ::Ice::Current&)
{
    Optional<pair<const Ice::Double*, const Ice::Double*> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opStringSeq_async(const ::Test::AMD_Initial_opStringSeqPtr& cb,
                            const IceUtil::Optional< ::std::pair< ::Test::StringSeq::const_iterator,
                                                                  ::Test::StringSeq::const_iterator> >& p1,
                            const ::Ice::Current&)
{
    Optional<pair<Test::StringSeq::const_iterator, Test::StringSeq::const_iterator> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opSmallStructSeq_async(const ::Test::AMD_Initial_opSmallStructSeqPtr& cb,
                                 const IceUtil::Optional< ::std::pair<const ::Test::SmallStruct*,
                                                                      const ::Test::SmallStruct*> >& p1,
                                 const ::Ice::Current&)
{
    Optional<pair<const Test::SmallStruct*, const Test::SmallStruct*> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opSmallStructList_async(const ::Test::AMD_Initial_opSmallStructListPtr& cb,
                                  const IceUtil::Optional< ::std::pair<const ::Test::SmallStruct*,
                                                                       const ::Test::SmallStruct*> >& p1,
                                  const ::Ice::Current&)
{
    Optional<pair<const Test::SmallStruct*, const Test::SmallStruct*> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opFixedStructSeq_async(const ::Test::AMD_Initial_opFixedStructSeqPtr& cb,
                                 const IceUtil::Optional< ::std::pair<const ::Test::FixedStruct*,
                                                                      const ::Test::FixedStruct*> >& p1,
                                 const ::Ice::Current&)
{
    Optional<pair<const Test::FixedStruct*, const Test::FixedStruct*> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opFixedStructList_async(const ::Test::AMD_Initial_opFixedStructListPtr& cb,
                                  const IceUtil::Optional< ::std::pair<const ::Test::FixedStruct*,
                                                                       const ::Test::FixedStruct*> >& p1,
                                  const ::Ice::Current&)
{
    Optional<pair<const Test::FixedStruct*, const Test::FixedStruct*> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opVarStructSeq_async(const ::Test::AMD_Initial_opVarStructSeqPtr& cb,
                               const IceUtil::Optional< ::std::pair< ::Test::VarStructSeq::const_iterator,
                                                                     ::Test::VarStructSeq::const_iterator> >& p1,
                               const ::Ice::Current&)
{
    Optional<pair<Test::VarStructSeq::const_iterator, Test::VarStructSeq::const_iterator> > p3;
    if(p1)
    {
        p3 = p1;
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opSerializable_async(const ::Test::AMD_Initial_opSerializablePtr& cb,
                               const IceUtil::Optional< ::Test::Serializable>& p1,
                               const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opIntIntDict_async(const ::Test::AMD_Initial_opIntIntDictPtr& cb,
                             const IceUtil::Optional< ::Test::IntIntDict>& p1,
                             const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opStringIntDict_async(const ::Test::AMD_Initial_opStringIntDictPtr& cb,
                                const IceUtil::Optional< ::Test::StringIntDict>& p1,
                                const ::Ice::Current&)
{
    cb->ice_response(p1, p1);
}

void
InitialI::opCustomIntStringDict_async(const ::Test::AMD_Initial_opCustomIntStringDictPtr& cb,
                                      const IceUtil::Optional<std::map<int, Util::string_view> >& p1,
                                      const ::Ice::Current&)
{
    Optional<std::map<int, Util::string_view> > p3;
    if(p1)
    {
        p3 = std::map<int, Util::string_view>();
        for(std::map<int, Util::string_view>::const_iterator p = p1->begin();
            p != p1->end(); ++p)
        {
            (*p3)[p->first] = p->second.to_string();
        }
    }
    cb->ice_response(p3, p3);
}

void
InitialI::opClassAndUnknownOptional_async(const ::Test::AMD_Initial_opClassAndUnknownOptionalPtr& cb,
                                          const Test::APtr&,
                                          const Ice::Current&)
{
    cb->ice_response();
}

void
InitialI::sendOptionalClass_async(const ::Test::AMD_Initial_sendOptionalClassPtr& cb,
                                  bool,
                                  const IceUtil::Optional<Test::OneOptionalPtr>&,
                                  const Ice::Current&)
{
    cb->ice_response();
}

void
InitialI::returnOptionalClass_async(const ::Test::AMD_Initial_returnOptionalClassPtr& cb,
                                    bool,
                                    const Ice::Current&)
{
    Optional<OneOptionalPtr> o = new OneOptional(53);
    cb->ice_response(o);
}

void
InitialI::supportsRequiredParams_async(const ::Test::AMD_Initial_supportsRequiredParamsPtr& cb,
                                       const Ice::Current&)
{
    cb->ice_response(false);
}

void
InitialI::supportsJavaSerializable_async(const ::Test::AMD_Initial_supportsJavaSerializablePtr& cb,
                                         const Ice::Current&)
{
    cb->ice_response(true);
}

void
InitialI::supportsCsharpSerializable_async(const ::Test::AMD_Initial_supportsCsharpSerializablePtr& cb,
                                           const Ice::Current&)
{
    cb->ice_response(true);
}

void
InitialI::supportsCppStringView_async(const ::Test::AMD_Initial_supportsCppStringViewPtr& cb,
                                      const Ice::Current&)
{
    cb->ice_response(true);
}