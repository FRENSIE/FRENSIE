//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardENDLDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The standard endl data generator class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_ENDL_DATA_GENERATOR_HPP
#define DATA_GEN_STANDARD_ENDL_DATA_GENERATOR_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_ENDLDataGenerator.hpp"
#include "Data_ENDLFileHandler.hpp"

namespace DataGen{

//! The endl electron-photon-relaxation data generator class
class StandardENDLDataGenerator : public ENDLDataGenerator
{

public:

  //! Constructor
  StandardENDLDataGenerator(
    const unsigned atomic_number,
    const std::string eadl_file_name,
    const std::string epdl_file_name,
    const std::string eedl_file_name );

  //! Destructor
  ~StandardENDLDataGenerator()
  { /* ... */ }

  //! Populate the EEDL data container
  void populateENDLDataContainer(
        Data::ENDLVolatileDataContainer&
        data_container ) const;

  //! Populate the EADL data container
  void populateEADLDataContainer(
        Data::ENDLVolatileDataContainer&
        data_container ) const;

  //! Populate the EPDL data container
  void populateEPDLDataContainer(
        Data::ENDLVolatileDataContainer&
        data_container ) const;

  //! Populate the EEDL data container
  void populateEEDLDataContainer(
        Data::ENDLVolatileDataContainer&
        data_container ) const;

protected:

  // Set the atomic data
  void setRelaxationData( Data::ENDLVolatileDataContainer&
        data_container ) const;

  // Set the photon data
  void setPhotonData( Data::ENDLVolatileDataContainer&
        data_container ) const;

  // Set the electron data
  void setElectronData( Data::ENDLVolatileDataContainer&
        data_container ) const;

private:

  // Test if a value is greater than or equal to one
  static bool greaterThanOrEqualToOne( const double value );

  // Test if a value is greater than one
  static bool greaterThanOne( const double value );

  // The if a value is not equal to zero
  static bool notEqualZero( const double value );
/*
  // Set the screened rutherford data
  void setScreenedRutherfordData(
    const Teuchos::RCP<const Utility::OneDDistribution>&
        cutoff_elastic_cross_section,
    const Teuchos::RCP<const Utility::OneDDistribution>&
        total_elastic_cross_section,
    const std::vector<double>& elastic_energy_grid,
    const std::map<double,std::vector<double> >& elastic_pdf,
    Data::ENDLVolatileDataContainer& data_container ) const;
*/

  // The EADL file name
  std::string d_eadl_file_name;

  // The EPDL file name
  std::string d_epdl_file_name;

  // The EEDL file name
  std::string d_eedl_file_name;

};

// Test if a value is greater than or equal to one
inline bool
StandardENDLDataGenerator::greaterThanOrEqualToOne(
							   const double value )
{
  return value >= 1.0;
}

// Test if a value is greater than one
inline bool
StandardENDLDataGenerator::greaterThanOne(
							   const double value )
{
  return value > 1.0;
}

// The if a value is not equal to zero
inline bool StandardENDLDataGenerator::notEqualZero(
							   const double value )
{
  return value != 0.0;
}

} // end DataGen namespace

#endif // end DATA_GEN_STANDARD_ENDL_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardENDLDataGenerator.hpp
//---------------------------------------------------------------------------//
