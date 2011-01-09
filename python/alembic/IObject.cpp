//-*****************************************************************************
//
// Copyright (c) 2009-2010,
//  Sony Pictures Imageworks Inc. and
//  Industrial Light & Magic, a division of Lucasfilm Entertainment Company Ltd.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Sony Pictures Imageworks, nor
// Industrial Light & Magic, nor the names of their contributors may be used
// to endorse or promote products derived from this software without specific
// prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//-*****************************************************************************

#include <boost/python/detail/wrap_python.hpp>

#include <Alembic/Abc/All.h>

#include <boost/python.hpp>


//#include <Python.h>

using namespace boost::python;

namespace Abc = ::Alembic::Abc;
namespace AbcA = ::Alembic::AbcCoreAbstract::v1;

//-*****************************************************************************
void register_iobject()
{
    // overloads
    Abc::IObject ( Abc::IObject::*getChildByIndex )( size_t ) = \
        &Abc::IObject::getChild;
    Abc::IObject ( Abc::IObject::*getChildByName )( const std::string& ) = \
        &Abc::IObject::getChild;

    const AbcA::ObjectHeader&
        ( Abc::IObject::*getChildHeaderByIndex )( size_t ) = \
        &Abc::IObject::getChildHeader;

    const AbcA::ObjectHeader*
        ( Abc::IObject::*getChildHeaderByName )( const std::string & ) = \
        &Abc::IObject::getChildHeader;


    class_<Abc::IObject>( "IObject",
                          init<Abc::IObject, const std::string&>() )
        .def( init<>() )
        .def( "getHeader", &Abc::IObject::getHeader,
              return_internal_reference<1>() )
        .def( "getName", &Abc::IObject::getName )
        .def( "getFullName", &Abc::IObject::getFullName )
        .def( "getNumChildren", &Abc::IObject::getNumChildren )
        .def( "getChildHeader", getChildHeaderByIndex,
              return_internal_reference<1>() )
        .def( "getChildHeader", getChildHeaderByName,
              return_value_policy<reference_existing_object>() )
        .def( "getProperties", &Abc::IObject::getProperties )
        .def( "getChild", getChildByIndex )
        .def( "getChild", getChildByName )
        .def( "valid", &Abc::IObject::valid )
        .def( "getArchive", &Abc::IObject::getArchive )
        .def( "getParent", &Abc::IObject::getParent )
        .def( "getMetaData", &Abc::IObject::getMetaData,
              return_internal_reference<1>() )
        .def( "reset", &Abc::IObject::reset )
        .def( "__str__", &Abc::IObject::getFullName )
        .def( "__nonzero__", &Abc::IObject::valid )
        ;
}
