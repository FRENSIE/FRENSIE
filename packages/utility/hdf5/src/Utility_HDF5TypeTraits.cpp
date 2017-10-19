//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5TypeTraits.cpp
//! \author Alex Robinson
//! \brief  HDF5 Type Traits specialization definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_HDF5TypeTraits.hpp"

namespace Utility{

// Initialize static member data
std::unique_ptr<H5::EnumType> HDF5TypeTraits<bool>::s_data_type;

// Returns the HDF5 data type object corresponding to bool
H5::EnumType HDF5TypeTraits<bool>::dataType()
{
  if( !s_data_type )
  {
    s_data_type.reset( new H5::EnumType( sizeof(BoolEnumType) ) );
    
    // Insert the false value
    HDF5TypeTraits<bool>::BoolEnumType enum_type =
      HDF5TypeTraits<bool>::False;
    
    s_data_type->insert( "False", &enum_type );
    
    // Insert the true value
    enum_type = HDF5TypeTraits<bool>::True;
    
    s_data_type->insert( "True", &enum_type );
    
    // Lock the data type
    s_data_type->lock();
  }
  
  return *s_data_type;
}

// Initialize internal data
auto HDF5TypeTraits<bool>::initializeInternalData(
                                           const ExternalType*,
                                           const size_t size ) -> InternalType*
{
  return new InternalType[size];
}

// Convert external type data to internal type data
void HDF5TypeTraits<bool>::convertExternalDataToInternalData(
                                           const ExternalType* raw_data,
                                           const size_t size,
                                           InternalType* converted_data )
{
  for( size_t i = 0; i < size; ++i )
  {
    if( raw_data[i] == true )
      converted_data[i] = HDF5TypeTraits<bool>::True;
    else
      converted_data[i] = HDF5TypeTraits<bool>::False;
  }
}
  
// Covert inner type to outer type
void HDF5TypeTraits<bool>::convertInternalDataToExternalData(
                                           const InternalType* raw_data,
                                           const size_t size,
                                           ExternalType* converted_data )
{
  for( size_t i = 0; i < size; ++i )
  {
    if( raw_data[i] == HDF5TypeTraits<bool>::True )
      converted_data[i] = true;
    else
      converted_data[i] = false;
  }
}

// Free the inner data created from outer data
void HDF5TypeTraits<bool>::freeInternalData( InternalType*& data )
{
  delete[] data;
  data = NULL;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HDF5TypeTraits.cpp
//---------------------------------------------------------------------------//

