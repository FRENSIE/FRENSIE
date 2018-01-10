//---------------------------------------------------------------------------//
//!
//! \file   tstACEStandardAtomProperties.cpp
//! \author Alex Robinson
//! \brief  StandardAtomProperties class unit tests using ACE data props
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <memory>
#include <iostream>

// FRENSIE Includes
#include "Data_StandardAtomProperties.hpp"
#include "Data_ACEPhotoatomicDataProperties.hpp"
#include "Data_ACEElectroatomicDataProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef std::tuple<
  std::tuple<boost::archive::xml_oarchive,boost::archive::xml_iarchive>,
  std::tuple<boost::archive::text_oarchive,boost::archive::text_iarchive>,
  std::tuple<boost::archive::binary_oarchive,boost::archive::binary_iarchive>,
  std::tuple<Utility::HDF5OArchive,Utility::HDF5IArchive>,
  std::tuple<boost::archive::polymorphic_oarchive*,boost::archive::polymorphic_iarchive*>
  > TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Data::ScatteringCenterProperties> atom_properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if this is an atom
FRENSIE_UNIT_TEST( StandardAtomProperties, isAtom )
{
  FRENSIE_CHECK( atom_properties->isAtom() );
}

//---------------------------------------------------------------------------//
// Check if this is a nuclide
FRENSIE_UNIT_TEST( StandardAtomProperties, isNuclide )
{
  FRENSIE_CHECK( !atom_properties->isNuclide() );
}

//---------------------------------------------------------------------------//
// Check that the name of the propeties can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, name )
{
  FRENSIE_CHECK_EQUAL( atom_properties->name(), "H", SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that the zaid can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, zaid )
{
  FRENSIE_CHECK_EQUAL( atom_properties->zaid(), Data::ZAID(1000) );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, atomicWeight )
{
  FRENSIE_CHECK_EQUAL( atom_properties->atomicWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, atomicWeightRatio )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( atom_properties->atomicWeightRatio(), 0.9914095197851978680, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check if there is any nuclear data available
FRENSIE_UNIT_TEST( StandardAtomProperties, nuclearDataAvailable )
{
  FRENSIE_CHECK( !atom_properties->nuclearDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the nuclear data properties can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, getNuclearDataProperties )
{
  FRENSIE_CHECK( atom_properties->getNuclearDataProperties() == NULL );
}

//---------------------------------------------------------------------------//
// Check if there is any thermal nuclear data available
FRENSIE_UNIT_TEST( StandardAtomProperties, thermalNuclearDataAvailable )
{
  FRENSIE_CHECK( !atom_properties->thermalNuclearDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the thermal nuclear data properties can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, getThermalNuclearDataProperties )
{
  FRENSIE_CHECK( atom_properties->getThermalNuclearDataProperties() == NULL );
}

//---------------------------------------------------------------------------//
// Check if there is any adjoint nuclear data available
FRENSIE_UNIT_TEST( StandardAtomProperties, adjointNuclearDataAvailable )
{
  FRENSIE_CHECK( !atom_properties->adjointNuclearDataAvailable() )
}

//---------------------------------------------------------------------------//
// Check that the adjoint nuclear data properties can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, getAdjointNuclearDataProperties )
{
  FRENSIE_CHECK( atom_properties->getAdjointNuclearDataProperties() == NULL );
}

//---------------------------------------------------------------------------//
// Check if there is any thermal adjoint nuclear data available
FRENSIE_UNIT_TEST( StandardAtomProperties, adjointThermalNuclearDataAvailable )
{
  FRENSIE_CHECK( !atom_properties->adjointThermalNuclearDataAvailable() )
}

//---------------------------------------------------------------------------//
// Check that the adjoint thermal nuclear data properties can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, getAdjointThermalNuclearDataProperties )
{
  FRENSIE_CHECK( atom_properties->getAdjointThermalNuclearDataProperties() == NULL );
}

//---------------------------------------------------------------------------//
// Check if there is any photonuclear data available
FRENSIE_UNIT_TEST( StandardAtomProperties, photonuclearDataAvailable )
{
  FRENSIE_CHECK( !atom_properties->photonuclearDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the photonuclear data properties can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, getPhotonuclearDataProperties )
{
  FRENSIE_CHECK( atom_properties->getPhotonuclearDataProperties() == NULL );
}

//---------------------------------------------------------------------------//
// Check if there is any adjoint photonuclear data available
FRENSIE_UNIT_TEST( StandardAtomProperties, adjointPhotonuclearDataAvailable )
{
  FRENSIE_CHECK( !atom_properties->adjointPhotonuclearDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the adjoint photonuclear data properties can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, getAdjointPhotonuclearDataProperties )
{
  FRENSIE_CHECK( atom_properties->getAdjointPhotonuclearDataProperties() == NULL );
}

//---------------------------------------------------------------------------//
// Check if there is any photoatomic data available
FRENSIE_UNIT_TEST( StandardAtomProperties, photoatomicDataAvailable )
{
  FRENSIE_CHECK( atom_properties->photoatomicDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the photoatomic data properties can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, getPhotoatomicDataProperties )
{
  const Data::PhotoatomicDataProperties* properties =
    atom_properties->getPhotoatomicDataProperties();
  
  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( properties->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1000.12p" );
}

//---------------------------------------------------------------------------//
// Check if there is any adjoint photoatomic data available
FRENSIE_UNIT_TEST( StandardAtomProperties, adjointPhotoatomicDataAvailable )
{
  FRENSIE_CHECK( !atom_properties->adjointPhotoatomicDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the adjoint photoatomic data properties can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, getAdjointPhotoatomicDataProperties )
{
  FRENSIE_CHECK( atom_properties->getAdjointPhotoatomicDataProperties() == NULL );
}

//---------------------------------------------------------------------------//
// Check if there is any electroatomic data available
FRENSIE_UNIT_TEST( StandardAtomProperties, electroatomicDataAvailable )
{
  FRENSIE_CHECK( atom_properties->electroatomicDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the electroatomic data properties can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, getElectroatomicDataProperties )
{
  const Data::ElectroatomicDataProperties* properties =
    atom_properties->getElectroatomicDataProperties();
  
  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( properties->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1000.12p" );
}

//---------------------------------------------------------------------------//
// Check if there is any adjoint electroatomic data available
FRENSIE_UNIT_TEST( StandardAtomProperties, adjointElectroatomicDataAvailable )
{
  FRENSIE_CHECK( !atom_properties->adjointElectroatomicDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the adjoint electroatomic data properties can be returned
FRENSIE_UNIT_TEST( StandardAtomProperties, getAdjointElectroatomicDataProperties )
{
  FRENSIE_CHECK( atom_properties->getAdjointElectroatomicDataProperties() == NULL );
}

//---------------------------------------------------------------------------//
// Check that the atom properties can be cloned
FRENSIE_UNIT_TEST( StandardAtomProperties, clone )
{
  std::unique_ptr<const Data::ScatteringCenterProperties>
    atom_properties_clone( atom_properties->clone() );

  FRENSIE_REQUIRE( atom_properties_clone.get() != NULL );
  FRENSIE_CHECK( atom_properties_clone.get() != atom_properties.get() );
  FRENSIE_CHECK( atom_properties_clone->getPhotoatomicDataProperties() ==
                 atom_properties->getPhotoatomicDataProperties() );
  FRENSIE_CHECK( atom_properties_clone->getElectroatomicDataProperties() ==
                 atom_properties->getElectroatomicDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that the atom properties can be cloned
FRENSIE_UNIT_TEST( StandardAtomProperties, deepClone )
{
  std::unique_ptr<const Data::ScatteringCenterProperties>
    atom_properties_clone( atom_properties->deepClone() );

  FRENSIE_REQUIRE( atom_properties_clone.get() != NULL );
  FRENSIE_CHECK( atom_properties_clone.get() != atom_properties.get() );
  FRENSIE_CHECK( atom_properties_clone->getPhotoatomicDataProperties() !=
                 atom_properties->getPhotoatomicDataProperties() );
  FRENSIE_CHECK( atom_properties_clone->getElectroatomicDataProperties() !=
                 atom_properties->getElectroatomicDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardAtomProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_ace_standard_atom_properties" );
  std::ostringstream archive_ostream;

  // Create and archive some properties
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::unique_ptr<const Data::StandardAtomProperties> local_atom_properties(
     dynamic_cast<Data::StandardAtomProperties*>(atom_properties->deepClone()));
    
    std::shared_ptr<const Data::ScatteringCenterProperties>
      shared_atom_properties( atom_properties->deepClone() );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( local_atom_properties ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_atom_properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<const Data::StandardAtomProperties> local_atom_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( local_atom_properties ) );

  FRENSIE_REQUIRE( local_atom_properties.get() != NULL );
  FRENSIE_CHECK( !local_atom_properties->nuclearDataAvailable() );
  FRENSIE_CHECK( local_atom_properties->getNuclearDataProperties() == NULL );
  FRENSIE_CHECK( !local_atom_properties->thermalNuclearDataAvailable() );
  FRENSIE_CHECK( local_atom_properties->getThermalNuclearDataProperties() == NULL );
  FRENSIE_CHECK( !local_atom_properties->adjointNuclearDataAvailable() );
  FRENSIE_CHECK( local_atom_properties->getAdjointNuclearDataProperties() == NULL );
  FRENSIE_CHECK( !local_atom_properties->adjointThermalNuclearDataAvailable() );
  FRENSIE_CHECK( local_atom_properties->getAdjointThermalNuclearDataProperties() == NULL );
  FRENSIE_CHECK( !local_atom_properties->photonuclearDataAvailable() );
  FRENSIE_CHECK( local_atom_properties->getPhotonuclearDataProperties() == NULL );
  FRENSIE_CHECK( !local_atom_properties->adjointPhotonuclearDataAvailable() );
  FRENSIE_CHECK( local_atom_properties->getAdjointPhotonuclearDataProperties() == NULL );
  FRENSIE_CHECK( local_atom_properties->photoatomicDataAvailable() );
  FRENSIE_REQUIRE( local_atom_properties->getPhotoatomicDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( local_atom_properties->getPhotoatomicDataProperties()->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( local_atom_properties->getPhotoatomicDataProperties()->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( local_atom_properties->getPhotoatomicDataProperties()->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( local_atom_properties->getPhotoatomicDataProperties()->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( local_atom_properties->getPhotoatomicDataProperties()->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( local_atom_properties->getPhotoatomicDataProperties()->tableName(), "1000.12p" );
  FRENSIE_CHECK( !local_atom_properties->adjointPhotoatomicDataAvailable() );
  FRENSIE_CHECK( local_atom_properties->getAdjointPhotoatomicDataProperties() == NULL );
  FRENSIE_CHECK( local_atom_properties->electroatomicDataAvailable() );
  FRENSIE_REQUIRE( local_atom_properties->getElectroatomicDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( local_atom_properties->getElectroatomicDataProperties()->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( local_atom_properties->getElectroatomicDataProperties()->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( local_atom_properties->getElectroatomicDataProperties()->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( local_atom_properties->getElectroatomicDataProperties()->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( local_atom_properties->getElectroatomicDataProperties()->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( local_atom_properties->getElectroatomicDataProperties()->tableName(), "1000.12p" );
  FRENSIE_CHECK( !local_atom_properties->adjointElectroatomicDataAvailable() );
  FRENSIE_CHECK( local_atom_properties->getAdjointElectroatomicDataProperties() == NULL );

  std::shared_ptr<const Data::ScatteringCenterProperties> shared_atom_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_atom_properties ) );

  FRENSIE_REQUIRE( shared_atom_properties.get() != NULL );
  FRENSIE_CHECK( !shared_atom_properties->nuclearDataAvailable() );
  FRENSIE_CHECK( shared_atom_properties->getNuclearDataProperties() == NULL );
  FRENSIE_CHECK( !shared_atom_properties->thermalNuclearDataAvailable() );
  FRENSIE_CHECK( shared_atom_properties->getThermalNuclearDataProperties() == NULL );
  FRENSIE_CHECK( !shared_atom_properties->adjointNuclearDataAvailable() );
  FRENSIE_CHECK( shared_atom_properties->getAdjointNuclearDataProperties() == NULL );
  FRENSIE_CHECK( !shared_atom_properties->adjointThermalNuclearDataAvailable() );
  FRENSIE_CHECK( shared_atom_properties->getAdjointThermalNuclearDataProperties() == NULL );
  FRENSIE_CHECK( !shared_atom_properties->photonuclearDataAvailable() );
  FRENSIE_CHECK( shared_atom_properties->getPhotonuclearDataProperties() == NULL );
  FRENSIE_CHECK( !shared_atom_properties->adjointPhotonuclearDataAvailable() );
  FRENSIE_CHECK( shared_atom_properties->getAdjointPhotonuclearDataProperties() == NULL );
  FRENSIE_CHECK( shared_atom_properties->photoatomicDataAvailable() );
  FRENSIE_REQUIRE( shared_atom_properties->getPhotoatomicDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( shared_atom_properties->getPhotoatomicDataProperties()->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( shared_atom_properties->getPhotoatomicDataProperties()->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( shared_atom_properties->getPhotoatomicDataProperties()->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( shared_atom_properties->getPhotoatomicDataProperties()->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( shared_atom_properties->getPhotoatomicDataProperties()->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( shared_atom_properties->getPhotoatomicDataProperties()->tableName(), "1000.12p" );
  FRENSIE_CHECK( !shared_atom_properties->adjointPhotoatomicDataAvailable() );
  FRENSIE_CHECK( shared_atom_properties->getAdjointPhotoatomicDataProperties() == NULL );
  FRENSIE_CHECK( shared_atom_properties->electroatomicDataAvailable() );
  FRENSIE_REQUIRE( shared_atom_properties->getElectroatomicDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( shared_atom_properties->getElectroatomicDataProperties()->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( shared_atom_properties->getElectroatomicDataProperties()->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( shared_atom_properties->getElectroatomicDataProperties()->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( shared_atom_properties->getElectroatomicDataProperties()->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( shared_atom_properties->getElectroatomicDataProperties()->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( shared_atom_properties->getElectroatomicDataProperties()->tableName(), "1000.12p" );
  FRENSIE_CHECK( !shared_atom_properties->adjointElectroatomicDataAvailable() );
  FRENSIE_CHECK( shared_atom_properties->getAdjointElectroatomicDataProperties() == NULL );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  std::shared_ptr<Data::StandardAtomProperties> local_atom_properties(
                           new Data::StandardAtomProperties( "H",
                                                              Data::ZAID(1000),
                                                              1.0 ) );
  // Set the photoatomic data properties
  {
    std::shared_ptr<const Data::PhotoatomicDataProperties> photoatomic_properties(
                     new Data::ACEPhotoatomicDataProperties( "atom_data/h.txt",
                                                             5,
                                                             "1000.12p" ) );

    local_atom_properties->setPhotoatomicDataProperties( photoatomic_properties );
  }

  // Set the electroatomic data properties
  {
    std::shared_ptr<const Data::ElectroatomicDataProperties> electroatomic_properties(
                   new Data::ACEElectroatomicDataProperties( "atom_data/h.txt",
                                                             5,
                                                             "1000.12p" ) );

    local_atom_properties->setElectroatomicDataProperties( electroatomic_properties );
  }

  atom_properties = local_atom_properties;
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstACEStandardAtomProperties.cpp
//---------------------------------------------------------------------------//
