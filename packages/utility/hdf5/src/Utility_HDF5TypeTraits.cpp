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
                                           const ExternalType* const,
                                           const size_t size ) -> InternalType*
{
  return new InternalType[size];
}

// Convert external type data to internal type data
void HDF5TypeTraits<bool>::convertExternalDataToInternalData(
                                           const ExternalType* const raw_data,
                                           const size_t size,
                                           const InternalType* converted_data )
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
                                           const InternalType* const raw_data,
                                           const size_t size,
                                           const ExternalType* converted_data )
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

// Returns the HDF5 data type object corresponding to bool
H5::PredType HDF5TypeTraits<boost::serialization::collection_size_type>::dataType()
{
  return HDF5TypeTraits<typename boost::serialization::collection_size_type::base_type>::dataType();
}

// Initialize internal data
InternalType* HDF5TypeTraits<boost::serialization::collection_size_type>::initializeInternalData(
                                                     const ExternalType* const,
                                                     const size_t size )
{
  return new InternalType[size];
}

// Convert external type data to internal type data
void HDF5TypeTraits<boost::serialization::collection_size_type>::convertExternalDataToInternalData(
                                           const ExternalType* const raw_data,
                                           const size_t size,
                                           const InternalType* converted_data )
{
  for( size_t i = 0; i < size; ++i )
    converted_data[i] = raw_data[i];
}
  
// Covert inner type to outer type
void HDF5TypeTraits<boost::serialization::collection_size_type>::convertInternalDataToExternalData(
                                           const InternalType* const raw_data,
                                           const size_t size,
                                           const ExternalType* converted_data )
{
  for( size_t i = 0; i < size; ++i )
  {
    converted_data[i] =
      boost::serialization::collection_size_type( raw_data[i] );
  }
}
  
// Free the inner data created from outer data
void HDF5TypeTraits<boost::serialization::collection_size_type>::freeInternalData( InternalType*& data )
{
  delete[] data;
  data = NULL;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HDF5TypeTraits.cpp
//---------------------------------------------------------------------------//

