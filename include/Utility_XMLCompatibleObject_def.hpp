//---------------------------------------------------------------------------//
//!
//! \file   Utility_XMLCompatibleObject_def.hpp
//! \author Alex Robinson
//! \brief  XML compatible object base class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_XML_COMPATIBLE_OBJECT_DEF_HPP
#define UTILITY_XML_COMPATIBLE_OBJECT_DEF_HPP

// Trilinos Includes
#include <Teuchos_StandardParameterEntryXMLConverters.hpp>
#include <Teuchos_ParameterEntryXMLConverterDB.hpp>

// FRENSIE Includes
#include "Utility_XMLCompatibleObject.hpp"

namespace Utility{

// Constructor
template<typename DerivedType>
XMLCompatibleObject<DerivedType>::XMLCompatibleObject()
{
  TEUCHOS_ADD_TYPE_CONVERTER( DerivedType );
}

} // end Utility namespace

#endif // end UTILITY_XML_COMPATIBLE_OBJECT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_XMLCompatibleObject_def.hpp
//---------------------------------------------------------------------------//
