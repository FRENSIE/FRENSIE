//---------------------------------------------------------------------------//
//!
//! \file   Utility_ParameterListCompatibleObject_def.hpp
//! \author Alex Robinson
//! \brief  ParameterList compatible object base class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PARAMETER_LIST_COMPATIBLE_OBJECT_DEF_HPP
#define UTILITY_PARAMETER_LIST_COMPATIBLE_OBJECT_DEF_HPP

// Trilinos Includes
#include <Teuchos_StandardParameterEntryXMLConverters.hpp>
#include <Teuchos_ParameterEntryXMLConverterDB.hpp>

// FRENSIE Includes
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

// Constructor
template<typename DerivedType>
ParameterListCompatibleObject<DerivedType>::ParameterListCompatibleObject()
{
  TEUCHOS_ADD_TYPE_CONVERTER( DerivedType );
}

} // end Utility namespace

#endif // end UTILITY_PARAMETER_LIST_COMPATIBLE_OBJECT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_ParameterListCompatibleObject_def.hpp
//---------------------------------------------------------------------------//
