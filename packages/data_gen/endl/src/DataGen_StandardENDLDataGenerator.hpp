//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardENDLDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The standard endl data generator class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_ENDL_DATA_GENERATOR_HPP
#define DATA_GEN_STANDARD_ENDL_DATA_GENERATOR_HPP

// Boost Includes
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "DataGen_ENDLDataGenerator.hpp"

namespace DataGen{

//! The endl electron-photon-relaxation data generator class
class StandardENDLDataGenerator : public ENDLDataGenerator
{

public:

  //! Constructor
  StandardENDLDataGenerator( const boost::filesystem::path& eadl_file_name,
                             const boost::filesystem::path& epdl_file_name,
                             const boost::filesystem::path& eedl_file_name );

  //! Destructor
  ~StandardENDLDataGenerator()
  { /* ... */ }

  //! Populate the EEDL data container
  void populateENDLDataContainer() final override;

  //! Populate the EADL data container
  void populateEADLDataContainer() final override;

  //! Populate the EPDL data container
  void populateEPDLDataContainer() final override;

  //! Populate the EEDL data container
  void populateEEDLDataContainer() final override;

private:

  // Test if a value is greater than or equal to one
  static bool greaterThanOrEqualToOne( const double value );

  // Test if a value is greater than one
  static bool greaterThanOne( const double value );

  // The if a value is not equal to zero
  static bool notEqualZero( const double value );

  // The EADL file name with path
  boost::filesystem::path d_eadl_file_name;

  // The EPDL file name with path
  boost::filesystem::path d_epdl_file_name;

  // The EEDL file name with path
  boost::filesystem::path d_eedl_file_name;
};

// Test if a value is greater than or equal to one
inline bool StandardENDLDataGenerator::greaterThanOrEqualToOne( const double value )
{
  return value >= 1.0;
}

// Test if a value is greater than one
inline bool StandardENDLDataGenerator::greaterThanOne( const double value )
{
  return value > 1.0;
}

// The if a value is not equal to zero
inline bool StandardENDLDataGenerator::notEqualZero( const double value )
{
  return value != 0.0;
}

} // end DataGen namespace

#endif // end DATA_GEN_STANDARD_ENDL_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardENDLDataGenerator.hpp
//---------------------------------------------------------------------------//
