//---------------------------------------------------------------------------//
//!
//! \file   tstACEStandardNuclideProperties.cpp
//! \author Alex Robinson
//! \brief  StandardNuclideProperties class unit tests using ACE data props
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <memory>
#include <iostream>

// FRENSIE Includes
#include "Data_StandardNuclideProperties.hpp"
#include "Data_ACENuclearDataProperties.hpp"
#include "Data_ACEThermalNuclearDataProperties.hpp"
#include "Data_ACEPhotonuclearDataProperties.hpp"
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
std::shared_ptr<const Data::ScatteringCenterProperties> basic_nuclide_properties;
std::shared_ptr<const Data::ScatteringCenterProperties> nuclide_properties_with_photonuc_data;
std::shared_ptr<const Data::ScatteringCenterProperties> nuclide_properties_with_thermal_data;
std::shared_ptr<const Data::ScatteringCenterProperties> complete_nuclide_properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if this is an atom
FRENSIE_UNIT_TEST( StandardNuclideProperties, isAtom )
{
  FRENSIE_CHECK( basic_nuclide_properties->isAtom() );
  FRENSIE_CHECK( nuclide_properties_with_photonuc_data->isAtom() );
  FRENSIE_CHECK( nuclide_properties_with_thermal_data->isAtom() );
  FRENSIE_CHECK( complete_nuclide_properties->isAtom() );
}

//---------------------------------------------------------------------------//
// Check if this is a nuclide
FRENSIE_UNIT_TEST( StandardNuclideProperties, isNuclide )
{
  FRENSIE_CHECK( basic_nuclide_properties->isNuclide() );
  FRENSIE_CHECK( nuclide_properties_with_photonuc_data->isNuclide() );
  FRENSIE_CHECK( nuclide_properties_with_thermal_data->isNuclide() );
  FRENSIE_CHECK( complete_nuclide_properties->isNuclide() );
}

//---------------------------------------------------------------------------//
// Check that the name of the properties can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, name )
{
  FRENSIE_CHECK_EQUAL( basic_nuclide_properties->name(), "H1" );
  FRENSIE_CHECK_EQUAL( nuclide_properties_with_photonuc_data->name(), "H1" );
  FRENSIE_CHECK_EQUAL( nuclide_properties_with_thermal_data->name(), "H1 in Benzene" );
  FRENSIE_CHECK_EQUAL( complete_nuclide_properties->name(), "H1 in Benzene" );
}

//---------------------------------------------------------------------------//
// Check that the zaid can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, zaid )
{
  FRENSIE_CHECK_EQUAL( basic_nuclide_properties->zaid(), Data::ZAID(1001) );
  FRENSIE_CHECK_EQUAL( nuclide_properties_with_photonuc_data->zaid(), Data::ZAID(1001) );
  FRENSIE_CHECK_EQUAL( nuclide_properties_with_thermal_data->zaid(), Data::ZAID(1001) );
  FRENSIE_CHECK_EQUAL( complete_nuclide_properties->zaid(), Data::ZAID(1001) );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, atomicWeightRatio )
{
  FRENSIE_CHECK_EQUAL( basic_nuclide_properties->atomicWeightRatio(), 1.0 );
  FRENSIE_CHECK_EQUAL( nuclide_properties_with_photonuc_data->atomicWeightRatio(), 1.0 );
  FRENSIE_CHECK_EQUAL( nuclide_properties_with_thermal_data->atomicWeightRatio(), 1.0 );
  FRENSIE_CHECK_EQUAL( complete_nuclide_properties->atomicWeightRatio(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, atomicWeight )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( basic_nuclide_properties->atomicWeight(), 1.008664916004299972, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( nuclide_properties_with_photonuc_data->atomicWeight(), 1.008664916004299972, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( nuclide_properties_with_thermal_data->atomicWeight(), 1.008664916004299972, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( complete_nuclide_properties->atomicWeight(), 1.008664916004299972, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check if there is any nuclear data available
FRENSIE_UNIT_TEST( StandardNuclideProperties, nuclearDataAvailable )
{
  FRENSIE_CHECK( basic_nuclide_properties->nuclearDataAvailable() );
  FRENSIE_CHECK( nuclide_properties_with_photonuc_data->nuclearDataAvailable() );
  FRENSIE_CHECK( nuclide_properties_with_thermal_data->nuclearDataAvailable() );
  FRENSIE_CHECK( complete_nuclide_properties->nuclearDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the nuclear data properties can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, getNuclearDataProperties )
{
  const Data::NuclearDataProperties* properties =
    basic_nuclide_properties->getNuclearDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( properties->atomicWeightRatio(), 1.0 );
  FRENSIE_CHECK_EQUAL( properties->evaluationTemperatureInMeV(),
                       2.5301e-8 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(),
                       "neutron_data/h_data.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 70 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1001.70c" );

  properties =
    nuclide_properties_with_photonuc_data->getNuclearDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( properties->atomicWeightRatio(), 1.0 );
  FRENSIE_CHECK_EQUAL( properties->evaluationTemperatureInMeV(),
                       2.5301e-8 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(),
                       "neutron_data/h_data.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 70 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1001.70c" );

  properties =
    nuclide_properties_with_thermal_data->getNuclearDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( properties->atomicWeightRatio(), 1.0 );
  FRENSIE_CHECK_EQUAL( properties->evaluationTemperatureInMeV(),
                       2.5301e-8 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(),
                       "neutron_data/h_data.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 70 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1001.70c" );

  properties =
    complete_nuclide_properties->getNuclearDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( properties->atomicWeightRatio(), 1.0 );
  FRENSIE_CHECK_EQUAL( properties->evaluationTemperatureInMeV(),
                       2.5301e-8 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(),
                       "neutron_data/h_data.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 70 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1001.70c" );
}

//---------------------------------------------------------------------------//
// Check if there is any thermal nuclear data available
FRENSIE_UNIT_TEST( StandardNuclideProperties, thermalNuclearDataAvailable )
{
  FRENSIE_CHECK( !basic_nuclide_properties->thermalNuclearDataAvailable() );
  FRENSIE_CHECK( !nuclide_properties_with_photonuc_data->thermalNuclearDataAvailable() );
  FRENSIE_CHECK( nuclide_properties_with_thermal_data->thermalNuclearDataAvailable() );
  FRENSIE_CHECK( complete_nuclide_properties->thermalNuclearDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the thermal nuclear data properties can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, getThermalNuclearDataProperties )
{
  const Data::ThermalNuclearDataProperties* properties =
    basic_nuclide_properties->getThermalNuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties =
    nuclide_properties_with_photonuc_data->getThermalNuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties =
    nuclide_properties_with_thermal_data->getThermalNuclearDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->name(), "benz" );
  FRENSIE_CHECK_EQUAL( properties->zaids(), std::set<Data::ZAID>( {Data::ZAID(1001), Data::ZAID(6000), Data::ZAID(6012)} ) );
  FRENSIE_CHECK_EQUAL( properties->evaluationTemperatureInMeV(), 2.5301e-8 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(), "sab_data/benz.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "benz.12t" );

  properties =
    complete_nuclide_properties->getThermalNuclearDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->name(), "benz" );
  FRENSIE_CHECK_EQUAL( properties->zaids(), std::set<Data::ZAID>( {Data::ZAID(1001), Data::ZAID(6000), Data::ZAID(6012)} ) );
  FRENSIE_CHECK_EQUAL( properties->evaluationTemperatureInMeV(), 2.5301e-8 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(), "sab_data/benz.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "benz.12t" );
}

//---------------------------------------------------------------------------//
// Check if there is any adjoint nuclear data available
FRENSIE_UNIT_TEST( StandardNuclideProperties, adjointNuclearDataAvailable )
{
  FRENSIE_CHECK( !basic_nuclide_properties->adjointNuclearDataAvailable() );
  FRENSIE_CHECK( !nuclide_properties_with_photonuc_data->adjointNuclearDataAvailable() );
  FRENSIE_CHECK( !nuclide_properties_with_thermal_data->adjointNuclearDataAvailable() );
  FRENSIE_CHECK( !complete_nuclide_properties->adjointNuclearDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the adjoint nuclear data properties can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, getAdjointNuclearDataProperties )
{
  const Data::AdjointNuclearDataProperties* properties =
    basic_nuclide_properties->getAdjointNuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = nuclide_properties_with_photonuc_data->getAdjointNuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = nuclide_properties_with_thermal_data->getAdjointNuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = complete_nuclide_properties->getAdjointNuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );
}

//---------------------------------------------------------------------------//
// Check if there is any adjoint thermal nuclear data available
FRENSIE_UNIT_TEST( StandardNuclideProperties, adjointThermalNuclearDataAvailable )
{
  FRENSIE_CHECK( !basic_nuclide_properties->adjointThermalNuclearDataAvailable() );
  FRENSIE_CHECK( !nuclide_properties_with_photonuc_data->adjointThermalNuclearDataAvailable() );
  FRENSIE_CHECK( !nuclide_properties_with_thermal_data->adjointThermalNuclearDataAvailable() );
  FRENSIE_CHECK( !complete_nuclide_properties->adjointThermalNuclearDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the adjoint nuclear data properties can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, getAdjointThermalNuclearDataProperties )
{
  const Data::AdjointThermalNuclearDataProperties* properties =
    basic_nuclide_properties->getAdjointThermalNuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = nuclide_properties_with_photonuc_data->getAdjointThermalNuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = nuclide_properties_with_thermal_data->getAdjointThermalNuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = complete_nuclide_properties->getAdjointThermalNuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );
}

//---------------------------------------------------------------------------//
// Check if there is any photonuclear data available
FRENSIE_UNIT_TEST( StandardNuclideProperties, photonuclearDataAvailable )
{
  FRENSIE_CHECK( !basic_nuclide_properties->photonuclearDataAvailable() );
  FRENSIE_CHECK( nuclide_properties_with_photonuc_data->photonuclearDataAvailable() );
  FRENSIE_CHECK( !nuclide_properties_with_thermal_data->photonuclearDataAvailable() );
  FRENSIE_CHECK( complete_nuclide_properties->photonuclearDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the photonuclear data properties can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, getPhotonuclearDataProperties )
{
  const Data::PhotonuclearDataProperties* properties =
    basic_nuclide_properties->getPhotonuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties =
    nuclide_properties_with_photonuc_data->getPhotonuclearDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( properties->atomicWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(),
                       "photonuclear_data/h_data.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 2 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 70 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1001.70u" );

  properties =
    nuclide_properties_with_thermal_data->getPhotonuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = complete_nuclide_properties->getPhotonuclearDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( properties->atomicWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(),
                       "photonuclear_data/h_data.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 2 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 70 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1001.70u" );
}

//---------------------------------------------------------------------------//
// Check if there is any adjoint nuclear data available
FRENSIE_UNIT_TEST( StandardNuclideProperties, adjointPhotonuclearDataAvailable )
{
  FRENSIE_CHECK( !basic_nuclide_properties->adjointPhotonuclearDataAvailable() );
  FRENSIE_CHECK( !nuclide_properties_with_photonuc_data->adjointPhotonuclearDataAvailable() );
  FRENSIE_CHECK( !nuclide_properties_with_thermal_data->adjointPhotonuclearDataAvailable() );
  FRENSIE_CHECK( !complete_nuclide_properties->adjointPhotonuclearDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the adjoint nuclear data properties can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, getAdjointPhotonuclearDataProperties )
{
  const Data::AdjointPhotonuclearDataProperties* properties =
    basic_nuclide_properties->getAdjointPhotonuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = nuclide_properties_with_photonuc_data->getAdjointPhotonuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = nuclide_properties_with_thermal_data->getAdjointPhotonuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = complete_nuclide_properties->getAdjointPhotonuclearDataProperties();

  FRENSIE_CHECK( properties == NULL );
}

//---------------------------------------------------------------------------//
// Check if there is any photoatomic data available
FRENSIE_UNIT_TEST( StandardNuclideProperties, photoatomicDataAvailable )
{
  FRENSIE_CHECK( basic_nuclide_properties->photoatomicDataAvailable() );
  FRENSIE_CHECK( nuclide_properties_with_photonuc_data->photoatomicDataAvailable() );
  FRENSIE_CHECK( nuclide_properties_with_thermal_data->photoatomicDataAvailable() );
  FRENSIE_CHECK( complete_nuclide_properties->photoatomicDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the photoatomic data properties can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, getPhotoatomicDataProperties )
{
  const Data::PhotoatomicDataProperties* properties =
    basic_nuclide_properties->getPhotoatomicDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( properties->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1000.12p" );

  properties =
    nuclide_properties_with_photonuc_data->getPhotoatomicDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( properties->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1000.12p" );

  properties =
    nuclide_properties_with_thermal_data->getPhotoatomicDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( properties->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1000.12p" );

  properties =
    complete_nuclide_properties->getPhotoatomicDataProperties();

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
FRENSIE_UNIT_TEST( StandardNuclideProperties, adjointPhotoatomicDataAvailable )
{
  FRENSIE_CHECK( !basic_nuclide_properties->adjointPhotoatomicDataAvailable() );
  FRENSIE_CHECK( !nuclide_properties_with_photonuc_data->adjointPhotoatomicDataAvailable() );
  FRENSIE_CHECK( !nuclide_properties_with_thermal_data->adjointPhotoatomicDataAvailable() );
  FRENSIE_CHECK( !complete_nuclide_properties->adjointPhotoatomicDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the adjoint photoatomic data properties can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, getAdjointPhotoatomicDataProperties )
{
  const Data::AdjointPhotoatomicDataProperties* properties =
    basic_nuclide_properties->getAdjointPhotoatomicDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = nuclide_properties_with_photonuc_data->getAdjointPhotoatomicDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = nuclide_properties_with_thermal_data->getAdjointPhotoatomicDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = complete_nuclide_properties->getAdjointPhotoatomicDataProperties();

  FRENSIE_CHECK( properties == NULL );
}

//---------------------------------------------------------------------------//
// Check if there is any electroatomic data available
FRENSIE_UNIT_TEST( StandardNuclideProperties, electroatomicDataAvailable )
{
  FRENSIE_CHECK( basic_nuclide_properties->electroatomicDataAvailable() );
  FRENSIE_CHECK( nuclide_properties_with_photonuc_data->electroatomicDataAvailable() );
  FRENSIE_CHECK( nuclide_properties_with_thermal_data->electroatomicDataAvailable() );
  FRENSIE_CHECK( complete_nuclide_properties->electroatomicDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the electroatomic data properties can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, getElectroatomicDataProperties )
{
  const Data::ElectroatomicDataProperties* properties =
    basic_nuclide_properties->getElectroatomicDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( properties->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1000.12p" );

  properties =
    nuclide_properties_with_photonuc_data->getElectroatomicDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( properties->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1000.12p" );

  properties =
    nuclide_properties_with_thermal_data->getElectroatomicDataProperties();

  FRENSIE_REQUIRE( properties != NULL );
  FRENSIE_CHECK_EQUAL( properties->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( properties->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( properties->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( properties->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( properties->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( properties->tableName(), "1000.12p" );

  properties =
    complete_nuclide_properties->getElectroatomicDataProperties();

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
FRENSIE_UNIT_TEST( StandardNuclideProperties, adjointElectroatomicDataAvailable )
{
  FRENSIE_CHECK( !basic_nuclide_properties->adjointElectroatomicDataAvailable() );
  FRENSIE_CHECK( !nuclide_properties_with_photonuc_data->adjointElectroatomicDataAvailable() );
  FRENSIE_CHECK( !nuclide_properties_with_thermal_data->adjointElectroatomicDataAvailable() );
  FRENSIE_CHECK( !complete_nuclide_properties->adjointElectroatomicDataAvailable() );
}

//---------------------------------------------------------------------------//
// Check that the adjoint electroatomic data properties can be returned
FRENSIE_UNIT_TEST( StandardNuclideProperties, getAdjointElectroatomicDataProperties )
{
  const Data::AdjointElectroatomicDataProperties* properties =
    basic_nuclide_properties->getAdjointElectroatomicDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = nuclide_properties_with_photonuc_data->getAdjointElectroatomicDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = nuclide_properties_with_thermal_data->getAdjointElectroatomicDataProperties();

  FRENSIE_CHECK( properties == NULL );

  properties = complete_nuclide_properties->getAdjointElectroatomicDataProperties();

  FRENSIE_CHECK( properties == NULL );
}

//---------------------------------------------------------------------------//
// Check that the nuclide properties can be cloned
FRENSIE_UNIT_TEST( StandardNuclideProperties, clone )
{
  std::unique_ptr<const Data::ScatteringCenterProperties>
    nuclide_properties_clone( basic_nuclide_properties->clone() );

  FRENSIE_REQUIRE( nuclide_properties_clone.get() != NULL );
  FRENSIE_CHECK( nuclide_properties_clone.get() != basic_nuclide_properties.get() );
  FRENSIE_CHECK( nuclide_properties_clone->getNuclearDataProperties() ==
                 basic_nuclide_properties->getNuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getPhotoatomicDataProperties() ==
                 basic_nuclide_properties->getPhotoatomicDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getElectroatomicDataProperties() ==
                 basic_nuclide_properties->getElectroatomicDataProperties() );

  nuclide_properties_clone.reset( nuclide_properties_with_photonuc_data->clone() );

  FRENSIE_REQUIRE( nuclide_properties_clone.get() != NULL );
  FRENSIE_CHECK( nuclide_properties_clone.get() != nuclide_properties_with_photonuc_data.get() );
  FRENSIE_CHECK( nuclide_properties_clone->getNuclearDataProperties() ==
                 nuclide_properties_with_photonuc_data->getNuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getPhotonuclearDataProperties() ==
                 nuclide_properties_with_photonuc_data->getPhotonuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getPhotoatomicDataProperties() ==
                 nuclide_properties_with_photonuc_data->getPhotoatomicDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getElectroatomicDataProperties() ==
                 nuclide_properties_with_photonuc_data->getElectroatomicDataProperties() );

  nuclide_properties_clone.reset( nuclide_properties_with_thermal_data->clone() );

  FRENSIE_REQUIRE( nuclide_properties_clone.get() != NULL );
  FRENSIE_CHECK( nuclide_properties_clone.get() != nuclide_properties_with_thermal_data.get() );
  FRENSIE_CHECK( nuclide_properties_clone->getNuclearDataProperties() ==
                 nuclide_properties_with_thermal_data->getNuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getThermalNuclearDataProperties() ==
                 nuclide_properties_with_thermal_data->getThermalNuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getPhotoatomicDataProperties() ==
                 nuclide_properties_with_thermal_data->getPhotoatomicDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getElectroatomicDataProperties() ==
                 nuclide_properties_with_thermal_data->getElectroatomicDataProperties() );

  nuclide_properties_clone.reset( complete_nuclide_properties->clone() );

  FRENSIE_REQUIRE( nuclide_properties_clone.get() != NULL );
  FRENSIE_CHECK( nuclide_properties_clone.get() != complete_nuclide_properties.get() );
  FRENSIE_CHECK( nuclide_properties_clone->getNuclearDataProperties() ==
                 complete_nuclide_properties->getNuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getThermalNuclearDataProperties() ==
                 complete_nuclide_properties->getThermalNuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getPhotonuclearDataProperties() ==
                 complete_nuclide_properties->getPhotonuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getPhotoatomicDataProperties() ==
                 complete_nuclide_properties->getPhotoatomicDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getElectroatomicDataProperties() ==
                 complete_nuclide_properties->getElectroatomicDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that the nuclide properties can be cloned
FRENSIE_UNIT_TEST( StandardNuclideProperties, deepClone )
{
  std::unique_ptr<const Data::ScatteringCenterProperties>
    nuclide_properties_clone( basic_nuclide_properties->deepClone() );

  FRENSIE_REQUIRE( nuclide_properties_clone.get() != NULL );
  FRENSIE_CHECK( nuclide_properties_clone.get() != basic_nuclide_properties.get() );
  FRENSIE_CHECK( nuclide_properties_clone->getNuclearDataProperties() !=
                 basic_nuclide_properties->getNuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getPhotoatomicDataProperties() !=
                 basic_nuclide_properties->getPhotoatomicDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getElectroatomicDataProperties() !=
                 basic_nuclide_properties->getElectroatomicDataProperties() );

  nuclide_properties_clone.reset( nuclide_properties_with_photonuc_data->deepClone() );

  FRENSIE_REQUIRE( nuclide_properties_clone.get() != NULL );
  FRENSIE_CHECK( nuclide_properties_clone.get() != nuclide_properties_with_photonuc_data.get() );
  FRENSIE_CHECK( nuclide_properties_clone->getNuclearDataProperties() !=
                 nuclide_properties_with_photonuc_data->getNuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getPhotonuclearDataProperties() !=
                 nuclide_properties_with_photonuc_data->getPhotonuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getPhotoatomicDataProperties() !=
                 nuclide_properties_with_photonuc_data->getPhotoatomicDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getElectroatomicDataProperties() !=
                 nuclide_properties_with_photonuc_data->getElectroatomicDataProperties() );

  nuclide_properties_clone.reset( nuclide_properties_with_thermal_data->deepClone() );

  FRENSIE_REQUIRE( nuclide_properties_clone.get() != NULL );
  FRENSIE_CHECK( nuclide_properties_clone.get() != nuclide_properties_with_thermal_data.get() );
  FRENSIE_CHECK( nuclide_properties_clone->getNuclearDataProperties() !=
                 nuclide_properties_with_thermal_data->getNuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getThermalNuclearDataProperties() !=
                 nuclide_properties_with_thermal_data->getThermalNuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getPhotoatomicDataProperties() !=
                 nuclide_properties_with_thermal_data->getPhotoatomicDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getElectroatomicDataProperties() !=
                 nuclide_properties_with_thermal_data->getElectroatomicDataProperties() );

  nuclide_properties_clone.reset( complete_nuclide_properties->deepClone() );

  FRENSIE_REQUIRE( nuclide_properties_clone.get() != NULL );
  FRENSIE_CHECK( nuclide_properties_clone.get() != complete_nuclide_properties.get() );
  FRENSIE_CHECK( nuclide_properties_clone->getNuclearDataProperties() !=
                 complete_nuclide_properties->getNuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getThermalNuclearDataProperties() !=
                 complete_nuclide_properties->getThermalNuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getPhotonuclearDataProperties() !=
                 complete_nuclide_properties->getPhotonuclearDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getPhotoatomicDataProperties() !=
                 complete_nuclide_properties->getPhotoatomicDataProperties() );
  FRENSIE_CHECK( nuclide_properties_clone->getElectroatomicDataProperties() !=
                 complete_nuclide_properties->getElectroatomicDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardNuclideProperties,
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

    std::unique_ptr<const Data::StandardNuclideProperties> local_nuclide_properties(
                                                                                     dynamic_cast<Data::StandardNuclideProperties*>(complete_nuclide_properties->deepClone()));

    std::shared_ptr<const Data::ScatteringCenterProperties>
      shared_nuclide_properties( complete_nuclide_properties->deepClone() );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( local_nuclide_properties ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( shared_nuclide_properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<const Data::StandardNuclideProperties> local_nuclide_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( local_nuclide_properties ) );

  FRENSIE_REQUIRE( local_nuclide_properties.get() != NULL );
  
  FRENSIE_CHECK( local_nuclide_properties->nuclearDataAvailable() );
  FRENSIE_REQUIRE( local_nuclide_properties->getNuclearDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getNuclearDataProperties()->zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getNuclearDataProperties()->atomicWeightRatio(), 1.0 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getNuclearDataProperties()->evaluationTemperatureInMeV(),
                       2.5301e-8 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getNuclearDataProperties()->filePath().string(),
                       "neutron_data/h_data.txt" );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getNuclearDataProperties()->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getNuclearDataProperties()->fileVersion(), 70 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getNuclearDataProperties()->tableName(), "1001.70c" );
  
  FRENSIE_CHECK( local_nuclide_properties->thermalNuclearDataAvailable() );
  FRENSIE_REQUIRE( local_nuclide_properties->getThermalNuclearDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getThermalNuclearDataProperties()->name(), "benz" );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getThermalNuclearDataProperties()->zaids(), std::set<Data::ZAID>( {Data::ZAID(1001), Data::ZAID(6000), Data::ZAID(6012)} ) );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getThermalNuclearDataProperties()->evaluationTemperatureInMeV(), 2.5301e-8 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getThermalNuclearDataProperties()->filePath().string(), "sab_data/benz.txt" );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getThermalNuclearDataProperties()->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getThermalNuclearDataProperties()->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getThermalNuclearDataProperties()->tableName(), "benz.12t" );
  
  FRENSIE_CHECK( !local_nuclide_properties->adjointNuclearDataAvailable() );
  FRENSIE_CHECK( local_nuclide_properties->getAdjointNuclearDataProperties() == NULL );
  FRENSIE_CHECK( !local_nuclide_properties->adjointThermalNuclearDataAvailable() );
  FRENSIE_CHECK( local_nuclide_properties->getAdjointThermalNuclearDataProperties() == NULL );
  FRENSIE_CHECK( local_nuclide_properties->photonuclearDataAvailable() );
  FRENSIE_REQUIRE( local_nuclide_properties->getPhotonuclearDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getPhotonuclearDataProperties()->zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getPhotonuclearDataProperties()->atomicWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getPhotonuclearDataProperties()->filePath().string(),
                       "photonuclear_data/h_data.txt" );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getPhotonuclearDataProperties()->fileStartLine(), 2 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getPhotonuclearDataProperties()->fileVersion(), 70 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getPhotonuclearDataProperties()->tableName(), "1001.70u" );
  
  FRENSIE_CHECK( !local_nuclide_properties->adjointPhotonuclearDataAvailable() );
  FRENSIE_CHECK( local_nuclide_properties->getAdjointPhotonuclearDataProperties() == NULL );
  
  FRENSIE_CHECK( local_nuclide_properties->photoatomicDataAvailable() );
  FRENSIE_REQUIRE( local_nuclide_properties->getPhotoatomicDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getPhotoatomicDataProperties()->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getPhotoatomicDataProperties()->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getPhotoatomicDataProperties()->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getPhotoatomicDataProperties()->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getPhotoatomicDataProperties()->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getPhotoatomicDataProperties()->tableName(), "1000.12p" );
  
  FRENSIE_CHECK( !local_nuclide_properties->adjointPhotoatomicDataAvailable() );
  FRENSIE_CHECK( local_nuclide_properties->getAdjointPhotoatomicDataProperties() == NULL );
  
  FRENSIE_CHECK( local_nuclide_properties->electroatomicDataAvailable() );
  FRENSIE_REQUIRE( local_nuclide_properties->getElectroatomicDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getElectroatomicDataProperties()->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getElectroatomicDataProperties()->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getElectroatomicDataProperties()->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getElectroatomicDataProperties()->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getElectroatomicDataProperties()->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( local_nuclide_properties->getElectroatomicDataProperties()->tableName(), "1000.12p" );
  
  FRENSIE_CHECK( !local_nuclide_properties->adjointElectroatomicDataAvailable() );
  FRENSIE_CHECK( local_nuclide_properties->getAdjointElectroatomicDataProperties() == NULL );

  std::shared_ptr<const Data::ScatteringCenterProperties> shared_nuclide_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_nuclide_properties ) );

  FRENSIE_REQUIRE( shared_nuclide_properties.get() != NULL );

  FRENSIE_CHECK( shared_nuclide_properties->nuclearDataAvailable() );
  FRENSIE_REQUIRE( shared_nuclide_properties->getNuclearDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getNuclearDataProperties()->zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getNuclearDataProperties()->atomicWeightRatio(), 1.0 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getNuclearDataProperties()->evaluationTemperatureInMeV(),
                       2.5301e-8 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getNuclearDataProperties()->filePath().string(),
                       "neutron_data/h_data.txt" );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getNuclearDataProperties()->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getNuclearDataProperties()->fileVersion(), 70 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getNuclearDataProperties()->tableName(), "1001.70c" );
  
  FRENSIE_CHECK( shared_nuclide_properties->thermalNuclearDataAvailable() );
  FRENSIE_REQUIRE( shared_nuclide_properties->getThermalNuclearDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getThermalNuclearDataProperties()->name(), "benz" );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getThermalNuclearDataProperties()->zaids(), std::set<Data::ZAID>( {Data::ZAID(1001), Data::ZAID(6000), Data::ZAID(6012)} ) );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getThermalNuclearDataProperties()->evaluationTemperatureInMeV(), 2.5301e-8 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getThermalNuclearDataProperties()->filePath().string(), "sab_data/benz.txt" );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getThermalNuclearDataProperties()->fileStartLine(), 10 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getThermalNuclearDataProperties()->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getThermalNuclearDataProperties()->tableName(), "benz.12t" );
  
  FRENSIE_CHECK( !shared_nuclide_properties->adjointNuclearDataAvailable() );
  FRENSIE_CHECK( shared_nuclide_properties->getAdjointNuclearDataProperties() == NULL );
  FRENSIE_CHECK( !shared_nuclide_properties->adjointThermalNuclearDataAvailable() );
  FRENSIE_CHECK( shared_nuclide_properties->getAdjointThermalNuclearDataProperties() == NULL );
  FRENSIE_CHECK( shared_nuclide_properties->photonuclearDataAvailable() );
  FRENSIE_REQUIRE( shared_nuclide_properties->getPhotonuclearDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getPhotonuclearDataProperties()->zaid(), Data::ZAID( 1001 ) );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getPhotonuclearDataProperties()->atomicWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getPhotonuclearDataProperties()->filePath().string(),
                       "photonuclear_data/h_data.txt" );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getPhotonuclearDataProperties()->fileStartLine(), 2 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getPhotonuclearDataProperties()->fileVersion(), 70 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getPhotonuclearDataProperties()->tableName(), "1001.70u" );
  
  FRENSIE_CHECK( !shared_nuclide_properties->adjointPhotonuclearDataAvailable() );
  FRENSIE_CHECK( shared_nuclide_properties->getAdjointPhotonuclearDataProperties() == NULL );
  
  FRENSIE_CHECK( shared_nuclide_properties->photoatomicDataAvailable() );
  FRENSIE_REQUIRE( shared_nuclide_properties->getPhotoatomicDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getPhotoatomicDataProperties()->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getPhotoatomicDataProperties()->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getPhotoatomicDataProperties()->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getPhotoatomicDataProperties()->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getPhotoatomicDataProperties()->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getPhotoatomicDataProperties()->tableName(), "1000.12p" );
  
  FRENSIE_CHECK( !shared_nuclide_properties->adjointPhotoatomicDataAvailable() );
  FRENSIE_CHECK( shared_nuclide_properties->getAdjointPhotoatomicDataProperties() == NULL );
  
  FRENSIE_CHECK( shared_nuclide_properties->electroatomicDataAvailable() );
  FRENSIE_REQUIRE( shared_nuclide_properties->getElectroatomicDataProperties() != NULL );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getElectroatomicDataProperties()->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getElectroatomicDataProperties()->atomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getElectroatomicDataProperties()->filePath().string(), "atom_data/h.txt" );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getElectroatomicDataProperties()->fileStartLine(), 5 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getElectroatomicDataProperties()->fileVersion(), 12 );
  FRENSIE_CHECK_EQUAL( shared_nuclide_properties->getElectroatomicDataProperties()->tableName(), "1000.12p" );
  
  FRENSIE_CHECK( !shared_nuclide_properties->adjointElectroatomicDataAvailable() );
  FRENSIE_CHECK( shared_nuclide_properties->getAdjointElectroatomicDataProperties() == NULL );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  std::shared_ptr<Data::StandardNuclideProperties>
    local_basic_nuclide_properties( new Data::StandardNuclideProperties(
                                               "H1", Data::ZAID(1001), 1.0 ) );
  
  std::shared_ptr<Data::StandardNuclideProperties>
    local_nuclide_properties_with_photonuc_data( new Data::StandardNuclideProperties(
                                               "H1", Data::ZAID(1001), 1.0 ) );
  
  std::shared_ptr<Data::StandardNuclideProperties>
    local_nuclide_properties_with_thermal_data( new Data::StandardNuclideProperties(
                                               "H1 in Benzene", Data::ZAID(1001), 1.0 ) );
  
  std::shared_ptr<Data::StandardNuclideProperties>
    local_complete_nuclide_properties( new Data::StandardNuclideProperties(
                                    "H1 in Benzene", Data::ZAID(1001), 1.0 ) );

  // Set the nuclear data properties
  {
    std::shared_ptr<const Data::NuclearDataProperties> nuclear_properties(
                 new Data::ACENuclearDataProperties( 1.0,
                                                     2.5301e-8,
                                                     "neutron_data/h_data.txt",
                                                     10,
                                                     "1001.70c" ) );

    local_basic_nuclide_properties->setNuclearDataProperties( nuclear_properties );
    local_nuclide_properties_with_photonuc_data->setNuclearDataProperties( nuclear_properties );
    local_nuclide_properties_with_thermal_data->setNuclearDataProperties( nuclear_properties );
    local_complete_nuclide_properties->setNuclearDataProperties( nuclear_properties );
  }

  // Set the thermal nuclear data properties
  {
    std::shared_ptr<const Data::ThermalNuclearDataProperties>
      thermal_nuclear_properties( new Data::ACEThermalNuclearDataProperties(
                        {Data::ZAID(1001), Data::ZAID(6000), Data::ZAID(6012)},
                        2.5301e-8,
                        "sab_data/benz.txt",
                        10,
                        "benz.12t" ) );

    local_nuclide_properties_with_thermal_data->setThermalNuclearDataProperties( thermal_nuclear_properties );
    local_complete_nuclide_properties->setThermalNuclearDataProperties( thermal_nuclear_properties );
  }

  // Set the photonuclear data properties
  {
    std::shared_ptr<const Data::PhotonuclearDataProperties>
      photonuclear_properties( new Data::ACEPhotonuclearDataProperties(
                                                1.0,
                                                "photonuclear_data/h_data.txt",
                                                2,
                                                "1001.70u" ) );

    local_nuclide_properties_with_photonuc_data->setPhotonuclearDataProperties( photonuclear_properties );
    local_complete_nuclide_properties->setPhotonuclearDataProperties( photonuclear_properties );
  }

  // Set the photoatomic data properties
  {
    std::shared_ptr<const Data::PhotoatomicDataProperties> photoatomic_properties(
                     new Data::ACEPhotoatomicDataProperties( "atom_data/h.txt",
                                                             5,
                                                             "1000.12p" ) );

    local_basic_nuclide_properties->setPhotoatomicDataProperties( photoatomic_properties );
    local_nuclide_properties_with_photonuc_data->setPhotoatomicDataProperties( photoatomic_properties );
    local_nuclide_properties_with_thermal_data->setPhotoatomicDataProperties( photoatomic_properties );
    local_complete_nuclide_properties->setPhotoatomicDataProperties( photoatomic_properties );
  }

  // Set the electroatomic data properties
  {
    std::shared_ptr<const Data::ElectroatomicDataProperties> electroatomic_properties(
                   new Data::ACEElectroatomicDataProperties( "atom_data/h.txt",
                                                             5,
                                                             "1000.12p" ) );

    local_basic_nuclide_properties->setElectroatomicDataProperties( electroatomic_properties );
    local_nuclide_properties_with_photonuc_data->setElectroatomicDataProperties( electroatomic_properties );
    local_nuclide_properties_with_thermal_data->setElectroatomicDataProperties( electroatomic_properties );
    local_complete_nuclide_properties->setElectroatomicDataProperties( electroatomic_properties );
  }

  basic_nuclide_properties = local_basic_nuclide_properties;
  
  nuclide_properties_with_photonuc_data =
    local_nuclide_properties_with_photonuc_data;
  
  nuclide_properties_with_thermal_data =
    local_nuclide_properties_with_thermal_data;
  
  complete_nuclide_properties = local_complete_nuclide_properties;
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstACEStandardNuclideProperties.cpp
//---------------------------------------------------------------------------//
