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
HDF5_ENABLED_LINE(std::unique_ptr<H5::EnumType> HDF5TypeTraits<bool>::s_data_type);

// Returns the HDF5 data type object corresponding to bool
HDF5_ENABLED_DISABLED_SWITCH(const H5::EnumType&,int) HDF5TypeTraits<bool>::dataType()
{
#ifdef HAVE_FRENSIE_HDF5
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
  }
  
  return *s_data_type;
#else
  return 0;
#endif // end HAVE_FRENSIE_HDF5
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

// Calculate the size of an internal array of data
size_t HDF5TypeTraits<bool>::calculateInternalDataSize( const size_t external_size )
{
  return external_size;
}

// Calculate the size of an external array of data
size_t HDF5TypeTraits<bool>::calculateExternalDataSize( const size_t internal_size )
{
  return internal_size;
}

// Free the inner data created from outer data
void HDF5TypeTraits<bool>::freeInternalData( InternalType*& data )
{
  delete[] data;
  data = NULL;
}

// Initialize static member data
HDF5_ENABLED_LINE(std::unique_ptr<H5::StrType> HDF5TypeTraits<std::string>::s_data_type);

// Returns the HDF5 data type object corresponding to std::string
HDF5_ENABLED_DISABLED_SWITCH(const H5::StrType&,int) HDF5TypeTraits<std::string>::dataType()
{
#ifdef HAVE_FRENSIE_HDF5
  if( !s_data_type )
    s_data_type.reset( new H5::StrType( H5::PredType::C_S1, H5T_VARIABLE ) );

  return *s_data_type;
#else
  return 0;
#endif
}

// Initialize internal data
auto HDF5TypeTraits<std::string>::initializeInternalData( const ExternalType*,
                                                          const size_t size ) -> InternalType*
{
  return new InternalType[size];
}

// Convert external type data to internal type data
void HDF5TypeTraits<std::string>::convertExternalDataToInternalData(
                                          const ExternalType* raw_data,
                                          const size_t size,
                                          InternalType* converted_data )
{
  for( size_t i = 0; i < size; ++i )
    converted_data[i] = raw_data[i].c_str();
}
  
// Covert inner type to outer type
void HDF5TypeTraits<std::string>::convertInternalDataToExternalData(
                                          const InternalType* raw_data,
                                          const size_t size,
                                          ExternalType* converted_data )
{
  for( size_t i = 0; i < size; ++i )
    converted_data[i] = std::string( raw_data[i] );
}

// Calculate the size of an internal array of data
size_t HDF5TypeTraits<std::string>::calculateInternalDataSize( const size_t external_size )
{
  return external_size;
}

// Calculate the size of an external array of data
size_t HDF5TypeTraits<std::string>::calculateExternalDataSize( const size_t internal_size )
{
  return internal_size;
}
  
// Free the inner data created from outer data
void HDF5TypeTraits<std::string>::freeInternalData( InternalType*& data )
{
  delete[] data;
  data = NULL;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HDF5TypeTraits.cpp
//---------------------------------------------------------------------------//

