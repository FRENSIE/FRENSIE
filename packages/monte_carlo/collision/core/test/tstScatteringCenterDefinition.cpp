//---------------------------------------------------------------------------//
//!
//! \file   tstScatteringCenterDefinition.cpp
//! \author Alex Robinson
//! \brief  Scattering center definition unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "MonteCarlo_ScatteringCenterDefinition.hpp"
#include "Data_NativeEPRPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointPhotoatomicDataProperties.hpp"
#include "Data_NativeEPRElectroatomicDataProperties.hpp"
#include "Data_NativeEPRAdjointElectroatomicDataProperties.hpp"
#include "Data_ACENuclearDataProperties.hpp"
#include "Data_ACEThermalNuclearDataProperties.hpp"
#include "Data_ACEPhotonuclearDataProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types.
//---------------------------------------------------------------------------//

using Utility::Units::MeV;
using Utility::Units::amu;

typedef TestArchiveHelper::TestArchives TestArchives;

namespace Data{

//! The adjoint nuclear data properties test class
class TestAdjointNuclearDataProperties : public AdjointNuclearDataProperties
{
  typedef AdjointNuclearDataProperties BaseProperties;

public:

  //! Default constructor
  TestAdjointNuclearDataProperties()
  { /* ... */ }

  //! Constructor
  TestAdjointNuclearDataProperties(
                  const Data::ZAID& zaid,
                  const double atomic_weight_ratio,
                  const typename BaseProperties::Energy evaluation_temperature,
                  const typename BaseProperties::FileType file_type,
                  const unsigned version )
    : d_zaid( zaid ),
      d_atomic_weight_ratio( atomic_weight_ratio ),
      d_evaluation_temperature( evaluation_temperature ),
      d_file_type( file_type ),
      d_version( version )
  { /* ... */ }

  //! Destructor
  ~TestAdjointNuclearDataProperties()
  { /* ... */ }

  //! Get the ZAID that the file specifies data for
  Data::ZAID zaid() const override
  { return d_zaid; }

  //! Get the atomic weight ratio of the nuclide that the file specifies data for
  double atomicWeightRatio() const override
  { return d_atomic_weight_ratio; }

  //! Get the nuclear data evaluation temperature (MeV)
  typename BaseProperties::Energy evaluationTemperatureInMeV() const override
  { return d_evaluation_temperature; }

  //! Get the nuclear data evaluation temperature (Kelvin)
  typename BaseProperties::Temperature evaluationTemperature() const
  { return d_evaluation_temperature/Utility::PhysicalConstants::boltzmann_constant_q; }

  //! Get the nuclear data file type
  typename BaseProperties::FileType fileType() const override
  { return d_file_type; }

  //! Get the nuclear data file path (relative to the data directory)
  boost::filesystem::path filePath() const override
  { return boost::filesystem::current_path(); }

  //! Get the nuclear data file start line
  size_t fileStartLine() const override
  { return 0; }

  //! Get the nuclear data file version
  unsigned fileVersion() const override
  { return d_version; }

  //! Get the nuclear data file major version
  unsigned fileMajorVersion() const
  { return d_version; }

  //! Get the nuclear data file table name
  std::string tableName() const override
  { return "test"; }

  //! Clone the properties
  TestAdjointNuclearDataProperties* clone() const override
  {
    return new TestAdjointNuclearDataProperties( d_zaid,
                                                 d_atomic_weight_ratio,
                                                 d_evaluation_temperature,
                                                 d_file_type,
                                                 d_version );
  }

private:

  // Save the properties to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { 
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseProperties );
    ar & BOOST_SERIALIZATION_NVP( d_zaid );
    ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
    ar & BOOST_SERIALIZATION_NVP( d_evaluation_temperature );
    ar & BOOST_SERIALIZATION_NVP( d_file_type );
    ar & BOOST_SERIALIZATION_NVP( d_version );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The zaid
  Data::ZAID d_zaid;

  // The atomic weight ratio
  double d_atomic_weight_ratio;

  // The evaluation temperature
  typename BaseProperties::Energy d_evaluation_temperature;

  // The file type
  typename BaseProperties::FileType d_file_type;

  // The file version
  unsigned d_version;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( TestAdjointNuclearDataProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TestAdjointNuclearDataProperties, Data );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( TestAdjointNuclearDataProperties, Data );

namespace Data{

//! The adjoint thermal nuclear data properties test class
class TestAdjointThermalNuclearDataProperties : public AdjointThermalNuclearDataProperties
{
  typedef AdjointThermalNuclearDataProperties BaseProperties;

public:

  //! Default constructor
  TestAdjointThermalNuclearDataProperties()
  { /* ... */ }

  //! Constructor
  TestAdjointThermalNuclearDataProperties(
                  const std::string& name,
                  const std::set<Data::ZAID>& zaids,
                  const typename BaseProperties::Energy evaluation_temperature,
                  const typename BaseProperties::FileType file_type,
                  const unsigned version )
    : d_name( name ),
      d_zaids( zaids ),
      d_evaluation_temperature( evaluation_temperature ),
      d_file_type( file_type ),
      d_version( version )
  { /* ... */ }

  //! Destructor
  ~TestAdjointThermalNuclearDataProperties()
  { /* ... */ }

  //! Get the name of the properties
  std::string name() const override
  { return d_name; }

  //! Check if the file specifies data for the ZAID of interest
  bool hasDataForZAID( const Data::ZAID& zaid ) const override
  { return d_zaids.find( zaid ) != d_zaids.end(); }

  //! Get the ZAIDS that the file specifies data for
  std::set<Data::ZAID> zaids() const override
  { return d_zaids; }

  //! Get the nuclear data evaluation temperature (MeV)
  typename BaseProperties::Energy evaluationTemperatureInMeV() const override
  { return d_evaluation_temperature; }

  //! Get the nuclear data evaluation temperature (Kelvin)
  typename BaseProperties::Temperature evaluationTemperature() const
  { return d_evaluation_temperature/Utility::PhysicalConstants::boltzmann_constant_q; }

  //! Get the nuclear data file type
  typename BaseProperties::FileType fileType() const override
  { return d_file_type; }

  //! Get the nuclear data file path (relative to the data directory)
  boost::filesystem::path filePath() const override
  { return boost::filesystem::current_path(); }

  //! Get the nuclear data file start line
  size_t fileStartLine() const override
  { return 0; }
  
  //! Get the nuclear data file version
  unsigned fileVersion() const override
  { return d_version; }

  //! Get the nuclear data file table name
  std::string tableName() const override
  { return "test"; }

  //! Clone the properties
  TestAdjointThermalNuclearDataProperties* clone() const override
  {
    return new TestAdjointThermalNuclearDataProperties( d_name,
                                                        d_zaids,
                                                        d_evaluation_temperature,
                                                        d_file_type,
                                                        d_version );
  }
  
private:

  // Save the properties to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseProperties );
    ar & BOOST_SERIALIZATION_NVP( d_name );
    ar & BOOST_SERIALIZATION_NVP( d_zaids );
    ar & BOOST_SERIALIZATION_NVP( d_evaluation_temperature );
    ar & BOOST_SERIALIZATION_NVP( d_file_type );
    ar & BOOST_SERIALIZATION_NVP( d_version );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The name
  std::string d_name;

  // The zaids
  std::set<Data::ZAID> d_zaids;

  // The evaluation temperature
  typename BaseProperties::Energy d_evaluation_temperature;

  // The file type
  typename BaseProperties::FileType d_file_type;

  // The file version
  unsigned d_version;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( TestAdjointThermalNuclearDataProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TestAdjointThermalNuclearDataProperties, Data );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( TestAdjointThermalNuclearDataProperties, Data );

namespace Data{

//! The adjoint photonuclear data properties test class
class TestAdjointPhotonuclearDataProperties : public AdjointPhotonuclearDataProperties
{
  typedef AdjointPhotonuclearDataProperties BaseProperties;
  
public:

  //! Default constructor
  TestAdjointPhotonuclearDataProperties()
  { /* ... */ }

  //! Constructor
  TestAdjointPhotonuclearDataProperties(
                             const Data::ZAID& zaid,
                             const double atomic_weight_ratio,
                             const typename BaseProperties::FileType file_type,
                             const unsigned version )
    : d_zaid( zaid ),
      d_atomic_weight_ratio( atomic_weight_ratio ),
      d_file_type( file_type ),
      d_version( version )
  { /* ... */ }

  //! Destructor
  ~TestAdjointPhotonuclearDataProperties()
  { /* ... */ }

  //! Get the ZAID that the file specifies data for
  Data::ZAID zaid() const override
  { return d_zaid; }

  //! Get the atomic weight of the nuclide that the file specifies data for
  typename BaseProperties::AtomicWeight atomicWeight() const override
  { return d_atomic_weight_ratio*Utility::PhysicalConstants::neutron_rest_mass_amu_q; }

  //! Get the nuclear data file type
  typename BaseProperties::FileType fileType() const override
  { return d_file_type; }

  //! Get the nuclear data file path (relative to the data directory)
  boost::filesystem::path filePath() const override
  { return boost::filesystem::current_path(); }

  //! Get the nuclear data file start line
  size_t fileStartLine() const override
  { return 0; }

  //! Get the nuclear data file version
  unsigned fileVersion() const override
  { return d_version; }

  //! Get the nuclear data file table name
  std::string tableName() const override
  { return "test"; }

  //! Clone the properties
  TestAdjointPhotonuclearDataProperties* clone() const override
  {
    return new TestAdjointPhotonuclearDataProperties( d_zaid,
                                                      d_atomic_weight_ratio,
                                                      d_file_type,
                                                      d_version );
  }

private:

  // Save the properties to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { 
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseProperties );
    ar & BOOST_SERIALIZATION_NVP( d_zaid );
    ar & BOOST_SERIALIZATION_NVP( d_atomic_weight_ratio );
    ar & BOOST_SERIALIZATION_NVP( d_file_type );
    ar & BOOST_SERIALIZATION_NVP( d_version );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The zaid
  Data::ZAID d_zaid;

  // The atomic weight ratio
  double d_atomic_weight_ratio;

  // The file type
  typename BaseProperties::FileType d_file_type;

  // The version
  unsigned d_version;
};
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( TestAdjointPhotonuclearDataProperties, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TestAdjointPhotonuclearDataProperties, Data );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( TestAdjointPhotonuclearDataProperties, Data );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the name can be returned
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, getName )
{
  std::unique_ptr<MonteCarlo::ScatteringCenterDefinition>
    definition( new MonteCarlo::ScatteringCenterDefinition( "H-Native", 1000 ) );

  FRENSIE_CHECK_EQUAL( definition->getName(), "H-Native" );

  definition.reset( new MonteCarlo::ScatteringCenterDefinition( 1000 ) );

  FRENSIE_CHECK_EQUAL( definition->getName(), "H" );

  definition.reset( new MonteCarlo::ScatteringCenterDefinition( "He3-Native", 2003 ) );

  FRENSIE_CHECK_EQUAL( definition->getName(), "He3-Native" );

  definition.reset( new MonteCarlo::ScatteringCenterDefinition( 2003 ) );

  FRENSIE_CHECK_EQUAL( definition->getName(), "He3" );

  FRENSIE_CHECK_THROW( definition.reset( new MonteCarlo::ScatteringCenterDefinition( "", 1000 ) ),
                       std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that the zaid can be returned
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, getZAID )
{
  std::unique_ptr<MonteCarlo::ScatteringCenterDefinition>
    definition( new MonteCarlo::ScatteringCenterDefinition( "H-Native", 1000 ) );

  FRENSIE_CHECK_EQUAL( definition->getZAID(), Data::ZAID(1000) );

  definition.reset( new MonteCarlo::ScatteringCenterDefinition( 2003 ) );

  FRENSIE_CHECK_EQUAL( definition->getZAID(), Data::ZAID(2003) );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight can be set
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, setAtomicWeight )
{
  MonteCarlo::ScatteringCenterDefinition definition( "H1", 1001 );

  FRENSIE_CHECK( !definition.isAtomicWeightSet() );
  FRENSIE_CHECK_THROW( definition.getAtomicWeight(), std::runtime_error );
  FRENSIE_CHECK_THROW( definition.getAtomicWeightRatio(), std::runtime_error );
  
  definition.setAtomicWeight( 1.0 );

  FRENSIE_CHECK( definition.isAtomicWeightSet() );
  FRENSIE_CHECK_EQUAL( definition.getAtomicWeight(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( definition.getAtomicWeightRatio(),
                                   9.914095197851978680e-01,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be set
FRENSIE_UNIT_TEST( ScatteringCenterDefintion, setAtomicWeightRatio )
{
  MonteCarlo::ScatteringCenterDefinition definition( "H1", 1001 );

  FRENSIE_CHECK( !definition.isAtomicWeightSet() );
  FRENSIE_CHECK_THROW( definition.getAtomicWeightRatio(), std::runtime_error );
  FRENSIE_CHECK_THROW( definition.getAtomicWeight(), std::runtime_error );
  
  definition.setAtomicWeightRatio( 9.914095197851978680e-01 );

  FRENSIE_CHECK( definition.isAtomicWeightSet() );
  FRENSIE_CHECK_EQUAL( definition.getAtomicWeightRatio(),
                       9.914095197851978680e-01 );
  FRENSIE_CHECK_FLOATING_EQUALITY( definition.getAtomicWeight(), 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that photoatomic data properties can be set
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, setPhotoatomicDataProperties )
{
  MonteCarlo::ScatteringCenterDefinition definition( "H-Native", 1000 );

  FRENSIE_CHECK( !definition.hasPhotoatomicDataProperties() );
  
  std::shared_ptr<const Data::PhotoatomicDataProperties> properties(
               new Data::NativeEPRPhotoatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

  definition.setPhotoatomicDataProperties( properties );

  FRENSIE_CHECK( definition.hasPhotoatomicDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getPhotoatomicDataProperties() );

  double atomic_weight;
  
  definition.getPhotoatomicDataProperties( &atomic_weight );

  FRENSIE_CHECK_EQUAL( atomic_weight, 1.0 );

  definition.setAtomicWeight( 1.1 );

  definition.getPhotoatomicDataProperties( &atomic_weight );

  FRENSIE_CHECK_EQUAL( atomic_weight, 1.1 );  

  // A NULL pointer should be ignored
  definition.setPhotoatomicDataProperties( std::shared_ptr<const Data::PhotoatomicDataProperties>() );

  FRENSIE_CHECK( definition.hasPhotoatomicDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getPhotoatomicDataProperties() );

  // Properties for a different atom will result in a warning
  properties.reset( new Data::NativeEPRPhotoatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::He_ATOM ) );

  definition.setDataProperties( properties );

  FRENSIE_CHECK( definition.hasPhotoatomicDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getPhotoatomicDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that adjoint photoatomic data properties can be set
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, setAdjointPhotoatomicDataProperties )
{
  MonteCarlo::ScatteringCenterDefinition definition( "H-Native", 1000 );

  FRENSIE_CHECK( !definition.hasAdjointPhotoatomicDataProperties() );
  
  std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> properties(
               new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

  definition.setAdjointPhotoatomicDataProperties( properties );

  FRENSIE_CHECK( definition.hasAdjointPhotoatomicDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointPhotoatomicDataProperties() );

  double atomic_weight;

  definition.getAdjointPhotoatomicDataProperties( &atomic_weight );

  FRENSIE_CHECK_EQUAL( atomic_weight, 1.0 );

  definition.setAtomicWeight( 1.1 );

  definition.getAdjointPhotoatomicDataProperties( &atomic_weight );

  FRENSIE_CHECK_EQUAL( atomic_weight, 1.1 );

  // A NULL pointer should be ignored
  definition.setAdjointPhotoatomicDataProperties( std::shared_ptr<const Data::AdjointPhotoatomicDataProperties>() );

  FRENSIE_CHECK( definition.hasAdjointPhotoatomicDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointPhotoatomicDataProperties() );

  // Properties for a different atom will result in a warning
  properties.reset( new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                             4.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::He_ATOM ) );

  definition.setDataProperties( properties );

  FRENSIE_CHECK( definition.hasAdjointPhotoatomicDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointPhotoatomicDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that electroatomic data properties can be set
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, setElectroatomicDataProperties )
{
  MonteCarlo::ScatteringCenterDefinition definition( "H-Native", 1000 );

  FRENSIE_CHECK( !definition.hasElectroatomicDataProperties() );
  
  std::shared_ptr<const Data::ElectroatomicDataProperties> properties(
               new Data::NativeEPRElectroatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

  definition.setElectroatomicDataProperties( properties );

  FRENSIE_CHECK( definition.hasElectroatomicDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getElectroatomicDataProperties() );

  double atomic_weight;

  definition.getElectroatomicDataProperties( &atomic_weight );

  FRENSIE_CHECK_EQUAL( atomic_weight, 1.0 );

  definition.setAtomicWeight( 1.1 );

  definition.getElectroatomicDataProperties( &atomic_weight );

  FRENSIE_CHECK_EQUAL( atomic_weight, 1.1 );

  // A NULL pointer should be ignored
  definition.setElectroatomicDataProperties( std::shared_ptr<const Data::ElectroatomicDataProperties>() );

  FRENSIE_CHECK( definition.hasElectroatomicDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getElectroatomicDataProperties() );

  // Properties for a different atom will result in a warning
  properties.reset( new Data::NativeEPRElectroatomicDataProperties(
                                             4.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::He_ATOM ) );

  definition.setDataProperties( properties );

  FRENSIE_CHECK( definition.hasElectroatomicDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getElectroatomicDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that adjoint electroatomic data properties can be set
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, setAdjointElectroatomicDataProperties )
{
  MonteCarlo::ScatteringCenterDefinition definition( "H-Native", 1000 );

  FRENSIE_CHECK( !definition.hasAdjointElectroatomicDataProperties() );
  
  std::shared_ptr<const Data::AdjointElectroatomicDataProperties> properties(
               new Data::NativeEPRAdjointElectroatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

  definition.setAdjointElectroatomicDataProperties( properties );

  FRENSIE_CHECK( definition.hasAdjointElectroatomicDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointElectroatomicDataProperties() );

  double atomic_weight;

  definition.getAdjointElectroatomicDataProperties( &atomic_weight );

  FRENSIE_CHECK_EQUAL( atomic_weight, 1.0 );

  definition.setAtomicWeight( 1.1 );

  definition.getAdjointElectroatomicDataProperties( &atomic_weight );

  FRENSIE_CHECK_EQUAL( atomic_weight, 1.1 );

  // A NULL pointer should be ignored
  definition.setAdjointElectroatomicDataProperties( std::shared_ptr<const Data::AdjointElectroatomicDataProperties>() );

  FRENSIE_CHECK( definition.hasAdjointElectroatomicDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointElectroatomicDataProperties() );

  // Properties for a different atom will result in a warning
  properties.reset( new Data::NativeEPRAdjointElectroatomicDataProperties(
                                             4.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::He_ATOM ) );

  definition.setDataProperties( properties );

  FRENSIE_CHECK( definition.hasAdjointElectroatomicDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointElectroatomicDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that nuclear data properties can be set
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, setNuclearDataProperties )
{
  MonteCarlo::ScatteringCenterDefinition definition( "H1-293.1K", 1001 );

  FRENSIE_CHECK( !definition.hasNuclearDataProperties() );
  
  std::shared_ptr<const Data::NuclearDataProperties> properties(
               new Data::ACENuclearDataProperties(
                                             1.0,
                                             2.52574e-8*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "1001.71c" ) );

  definition.setNuclearDataProperties( properties );

  FRENSIE_CHECK( definition.hasNuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getNuclearDataProperties() );

  double atomic_weight_ratio;

  definition.getNuclearDataProperties( &atomic_weight_ratio );

  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 1.0 );

  definition.setAtomicWeightRatio( 0.9 );

  definition.getNuclearDataProperties( &atomic_weight_ratio );

  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 0.9 );

  // A NULL pointer should be ignored
  definition.setNuclearDataProperties( std::shared_ptr<const Data::NuclearDataProperties>() );

  FRENSIE_CHECK( definition.hasNuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getNuclearDataProperties() );

  // Properties for a different nuclide will result in a warning
  properties.reset( new Data::ACENuclearDataProperties(
                                             2.0,
                                             2.52574e-8*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "2003.71c" ) );

  definition.setDataProperties( properties );

  FRENSIE_CHECK( definition.hasNuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getNuclearDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that adjoint nuclear data properties can be set
FRENSIE_UNIT_TEST( ScatteringCenterDefinition,
                   setAdjointNuclearDataProperties )
{
  MonteCarlo::ScatteringCenterDefinition definition( "H1-293.1K", 1001 );

  FRENSIE_CHECK( !definition.hasAdjointNuclearDataProperties() );
  
  std::shared_ptr<const Data::AdjointNuclearDataProperties> properties(
               new Data::TestAdjointNuclearDataProperties(
                               1001,
                               1.0,
                               2.52574e-8*MeV,
                               Data::AdjointNuclearDataProperties::Native_FILE,
                               0 ) );

  definition.setAdjointNuclearDataProperties( properties );

  FRENSIE_CHECK( definition.hasAdjointNuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointNuclearDataProperties() );

  double atomic_weight_ratio;
  
  definition.getAdjointNuclearDataProperties( &atomic_weight_ratio );

  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 1.0 );

  definition.setAtomicWeightRatio( 0.9 );

  definition.getAdjointNuclearDataProperties( &atomic_weight_ratio );

  FRENSIE_CHECK_EQUAL( atomic_weight_ratio, 0.9 );

  // A NULL pointer should be ignored
  definition.setAdjointNuclearDataProperties( std::shared_ptr<const Data::AdjointNuclearDataProperties>() );

  FRENSIE_CHECK( definition.hasAdjointNuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointNuclearDataProperties() );

  // Properties for a different nuclide will result in a warning
  properties.reset( new Data::TestAdjointNuclearDataProperties(
                               2003,
                               1.0,
                               2.52574e-8*MeV,
                               Data::AdjointNuclearDataProperties::Native_FILE,
                               0 ) );
                               
  definition.setDataProperties( properties );

  FRENSIE_CHECK( definition.hasAdjointNuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointNuclearDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that thermal nuclear data properties can be set
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, setThermalNuclearDataProperties )
{
  MonteCarlo::ScatteringCenterDefinition definition( "H1 in H2O-293.1K", 1001 );

  FRENSIE_CHECK( !definition.hasThermalNuclearDataProperties() );
  
  std::shared_ptr<const Data::ThermalNuclearDataProperties> properties(
               new Data::ACEThermalNuclearDataProperties(
                                             {1001, 1002, 8016},
                                             2.52574e-8*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "ltwtr.71t" ) );

  definition.setThermalNuclearDataProperties( properties );

  FRENSIE_CHECK( definition.hasThermalNuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getThermalNuclearDataProperties() );

  // A NULL pointer should be ignored
  definition.setThermalNuclearDataProperties( std::shared_ptr<const Data::ThermalNuclearDataProperties>() );

  FRENSIE_CHECK( definition.hasThermalNuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getThermalNuclearDataProperties() );

  // Properties for a different nuclide will result in a warning
  properties.reset( new Data::ACEThermalNuclearDataProperties(
                                             {1002, 8016},
                                             2.52574e-8*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "hvwtr.71t" ) );

  definition.setDataProperties( properties );

  FRENSIE_CHECK( definition.hasThermalNuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getThermalNuclearDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that adjoint thermal nuclear data properties can be set
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, setAdjointThermalNuclearDataProperties )
{
  MonteCarlo::ScatteringCenterDefinition definition( "H1 in H2O-293.1K", 1001 );

  FRENSIE_CHECK( !definition.hasAdjointThermalNuclearDataProperties() );
  
  std::shared_ptr<const Data::AdjointThermalNuclearDataProperties> properties(
               new Data::TestAdjointThermalNuclearDataProperties(
                        "light water",
                        {1001, 1002, 8016},
                        2.52574e-8*MeV,
                        Data::AdjointThermalNuclearDataProperties::Native_FILE,
                        0 ) );

  definition.setAdjointThermalNuclearDataProperties( properties );

  FRENSIE_CHECK( definition.hasAdjointThermalNuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointThermalNuclearDataProperties() );

  // A NULL pointer should be ignored
  definition.setAdjointThermalNuclearDataProperties( std::shared_ptr<const Data::AdjointThermalNuclearDataProperties>() );

  FRENSIE_CHECK( definition.hasAdjointThermalNuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointThermalNuclearDataProperties() );

  // Properties for a different nuclide will result in a warning
  properties.reset( new Data::TestAdjointThermalNuclearDataProperties(
                        "heavy water",
                        {1002, 8016},
                        2.52574e-8*MeV,
                        Data::AdjointThermalNuclearDataProperties::Native_FILE,
                        0 ) );

  definition.setDataProperties( properties );

  FRENSIE_CHECK( definition.hasAdjointThermalNuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointThermalNuclearDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that photonuclear data properties can be set
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, setPhotonuclearDataProperties )
{
  MonteCarlo::ScatteringCenterDefinition definition( "H1-293.1K", 1001 );

  FRENSIE_CHECK( !definition.hasPhotonuclearDataProperties() );
  
  std::shared_ptr<const Data::PhotonuclearDataProperties> properties(
               new Data::ACEPhotonuclearDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             "1001.10u" ) );

  definition.setPhotonuclearDataProperties( properties );

  FRENSIE_CHECK( definition.hasPhotonuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getPhotonuclearDataProperties() );

  double atomic_weight;

  definition.getPhotonuclearDataProperties( &atomic_weight );

  FRENSIE_CHECK_EQUAL( atomic_weight, 1.0 );

  definition.setAtomicWeight( 1.1 );

  definition.getPhotonuclearDataProperties( &atomic_weight );

  FRENSIE_CHECK_EQUAL( atomic_weight, 1.1 );

  // A NULL pointer should be ignored
  definition.setPhotonuclearDataProperties( std::shared_ptr<const Data::PhotonuclearDataProperties>() );

  FRENSIE_CHECK( definition.hasPhotonuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getPhotonuclearDataProperties() );

  // Properties for a different nuclide will result in a warning
  properties.reset( new Data::ACEPhotonuclearDataProperties(
                                             2.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             "2003.10u" ) );

  definition.setDataProperties( properties );

  FRENSIE_CHECK( definition.hasPhotonuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getPhotonuclearDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that adjoint aphotonuclear data properties can be set
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, setAdjointPhotonuclearDataProperties )
{
  MonteCarlo::ScatteringCenterDefinition definition( "H1-293.1K", 1001 );

  FRENSIE_CHECK( !definition.hasAdjointPhotonuclearDataProperties() );
  
  std::shared_ptr<const Data::AdjointPhotonuclearDataProperties> properties(
               new Data::TestAdjointPhotonuclearDataProperties(
                          1001,
                          1.0,
                          Data::AdjointPhotonuclearDataProperties::Native_FILE,
                          0 ) );

  definition.setAdjointPhotonuclearDataProperties( properties );

  FRENSIE_CHECK( definition.hasAdjointPhotonuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointPhotonuclearDataProperties() );

  double atomic_weight;

  definition.getAdjointPhotonuclearDataProperties( &atomic_weight );

  FRENSIE_CHECK_FLOATING_EQUALITY( atomic_weight,
                                   1.008664916004299972e+00,
                                   1e-15 );

  definition.setAtomicWeight( 1.1 );

  definition.getAdjointPhotonuclearDataProperties( &atomic_weight );

  FRENSIE_CHECK_EQUAL( atomic_weight, 1.1 );

  // A NULL pointer should be ignored
  definition.setAdjointPhotonuclearDataProperties( std::shared_ptr<const Data::AdjointPhotonuclearDataProperties>() );

  FRENSIE_CHECK( definition.hasAdjointPhotonuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointPhotonuclearDataProperties() );

  // Properties for a different nuclide will result in a warning
  properties.reset( new Data::TestAdjointPhotonuclearDataProperties(
                          2003,
                          2.0,
                          Data::AdjointPhotonuclearDataProperties::Native_FILE,
                          0 ) );

  definition.setDataProperties( properties );

  FRENSIE_CHECK( definition.hasAdjointPhotonuclearDataProperties() );
  FRENSIE_CHECK( properties.get() == &definition.getAdjointPhotonuclearDataProperties() );
}

//---------------------------------------------------------------------------//
// Check that setting nuclear data properties with different temperature
// evaluations will trigger a warning
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, warn_different_temps )
{
  // Set the nuclear data first
  {
    MonteCarlo::ScatteringCenterDefinition definition( "H1-293.1K", 1001 );

    std::shared_ptr<const Data::NuclearDataProperties> nuclear_properties(
               new Data::ACENuclearDataProperties(
                                             1.0,
                                             2.52574e-8*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "1001.71c" ) );

    definition.setDataProperties( nuclear_properties );

    std::shared_ptr<const Data::ThermalNuclearDataProperties> thermal_nuclear_properties(
               new Data::ACEThermalNuclearDataProperties(
                                             {1001, 1002, 8016},
                                             2.52574e-7*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "ltwtr.81t" ) );

    definition.setDataProperties( thermal_nuclear_properties );

    std::shared_ptr<const Data::AdjointNuclearDataProperties> adjoint_nuclear_properties(
               new Data::TestAdjointNuclearDataProperties(
                               1001,
                               1.0,
                               2.52574e-7*MeV,
                               Data::AdjointNuclearDataProperties::Native_FILE,
                               0 ) );

    definition.setDataProperties( adjoint_nuclear_properties );

    std::shared_ptr<const Data::AdjointThermalNuclearDataProperties> adjoint_thermal_nuclear_properties(
               new Data::TestAdjointThermalNuclearDataProperties(
                        "light water",
                        {1001, 1002, 8016},
                        2.52574e-7*MeV,
                        Data::AdjointThermalNuclearDataProperties::Native_FILE,
                        0 ) );

    definition.setDataProperties( adjoint_thermal_nuclear_properties );
  }

  // Set the thermal nuclear data first
  {
    MonteCarlo::ScatteringCenterDefinition definition( "H1-293.1K", 1001 );

    std::shared_ptr<const Data::ThermalNuclearDataProperties> thermal_nuclear_properties(
               new Data::ACEThermalNuclearDataProperties(
                                             {1001, 1002, 8016},
                                             2.52574e-8*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "ltwtr.81t" ) );

    definition.setDataProperties( thermal_nuclear_properties );

    std::shared_ptr<const Data::NuclearDataProperties> nuclear_properties(
               new Data::ACENuclearDataProperties(
                                             1.0,
                                             2.52574e-7*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "1001.71c" ) );

    definition.setDataProperties( nuclear_properties );

    std::shared_ptr<const Data::AdjointNuclearDataProperties> adjoint_nuclear_properties(
               new Data::TestAdjointNuclearDataProperties(
                               1001,
                               1.0,
                               2.52574e-7*MeV,
                               Data::AdjointNuclearDataProperties::Native_FILE,
                               0 ) );

    definition.setDataProperties( adjoint_nuclear_properties );

    std::shared_ptr<const Data::AdjointThermalNuclearDataProperties> adjoint_thermal_nuclear_properties(
               new Data::TestAdjointThermalNuclearDataProperties(
                        "light water",
                        {1001, 1002, 8016},
                        2.52574e-7*MeV,
                        Data::AdjointThermalNuclearDataProperties::Native_FILE,
                        0 ) );

    definition.setDataProperties( adjoint_thermal_nuclear_properties );
  }

  // Set the adjoint nuclear data first
  {
    MonteCarlo::ScatteringCenterDefinition definition( "H1-293.1K", 1001 );

    std::shared_ptr<const Data::AdjointNuclearDataProperties> adjoint_nuclear_properties(
               new Data::TestAdjointNuclearDataProperties(
                               1001,
                               1.0,
                               2.52574e-8*MeV,
                               Data::AdjointNuclearDataProperties::Native_FILE,
                               0 ) );

    definition.setDataProperties( adjoint_nuclear_properties );

    std::shared_ptr<const Data::NuclearDataProperties> nuclear_properties(
               new Data::ACENuclearDataProperties(
                                             1.0,
                                             2.52574e-7*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "1001.71c" ) );

    definition.setDataProperties( nuclear_properties );

    std::shared_ptr<const Data::ThermalNuclearDataProperties> thermal_nuclear_properties(
               new Data::ACEThermalNuclearDataProperties(
                                             {1001, 1002, 8016},
                                             2.52574e-7*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "ltwtr.81t" ) );

    definition.setDataProperties( thermal_nuclear_properties );

    std::shared_ptr<const Data::AdjointThermalNuclearDataProperties> adjoint_thermal_nuclear_properties(
               new Data::TestAdjointThermalNuclearDataProperties(
                        "light water",
                        {1001, 1002, 8016},
                        2.52574e-7*MeV,
                        Data::AdjointThermalNuclearDataProperties::Native_FILE,
                        0 ) );

    definition.setDataProperties( adjoint_thermal_nuclear_properties );
  }

  // Set the adjoint thermal nuclear data first
  {
    MonteCarlo::ScatteringCenterDefinition definition( "H1-293.1K", 1001 );

    std::shared_ptr<const Data::AdjointThermalNuclearDataProperties> adjoint_thermal_nuclear_properties(
               new Data::TestAdjointThermalNuclearDataProperties(
                        "light water",
                        {1001, 1002, 8016},
                        2.52574e-8*MeV,
                        Data::AdjointThermalNuclearDataProperties::Native_FILE,
                        0 ) );

    definition.setDataProperties( adjoint_thermal_nuclear_properties );

    std::shared_ptr<const Data::NuclearDataProperties> nuclear_properties(
               new Data::ACENuclearDataProperties(
                                             1.0,
                                             2.52574e-7*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "1001.71c" ) );

    definition.setDataProperties( nuclear_properties );

    std::shared_ptr<const Data::ThermalNuclearDataProperties> thermal_nuclear_properties(
               new Data::ACEThermalNuclearDataProperties(
                                             {1001, 1002, 8016},
                                             2.52574e-7*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "ltwtr.81t" ) );

    definition.setDataProperties( thermal_nuclear_properties );

    std::shared_ptr<const Data::AdjointNuclearDataProperties> adjoint_nuclear_properties(
               new Data::TestAdjointNuclearDataProperties(
                               1001,
                               1.0,
                               2.52574e-7*MeV,
                               Data::AdjointNuclearDataProperties::Native_FILE,
                               0 ) );

    definition.setDataProperties( adjoint_nuclear_properties );
  }
}

//---------------------------------------------------------------------------//
// Check that a scattering center definition can be placed in a stream
FRENSIE_UNIT_TEST( ScatteringCenterDefinition, toStream )
{
  MonteCarlo::ScatteringCenterDefinition h_definition( 1000 );
    
  MonteCarlo::ScatteringCenterDefinition h1_definition( "H1-293.1K", 1001 );

  {
    std::shared_ptr<const Data::PhotoatomicDataProperties> properties(
               new Data::NativeEPRPhotoatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

    h_definition.setDataProperties( properties );
    h1_definition.setDataProperties( properties );
  }
  
  {
    std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> properties(
               new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

    h_definition.setDataProperties( properties );
    h1_definition.setDataProperties( properties );
  }
  
  {
    std::shared_ptr<const Data::ElectroatomicDataProperties> properties(
               new Data::NativeEPRElectroatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

    h_definition.setDataProperties( properties );
    h1_definition.setDataProperties( properties );
  }

  {
    std::shared_ptr<const Data::AdjointElectroatomicDataProperties> properties(
               new Data::NativeEPRAdjointElectroatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );
    
    h_definition.setDataProperties( properties );
    h1_definition.setDataProperties( properties );
  }

  {
    std::shared_ptr<const Data::NuclearDataProperties> properties(
               new Data::ACENuclearDataProperties(
                                             1.0,
                                             2.52574e-8*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "1001.71c" ) );

    h1_definition.setDataProperties( properties );
  }

  {
    std::shared_ptr<const Data::AdjointNuclearDataProperties> properties(
               new Data::TestAdjointNuclearDataProperties(
                               1001,
                               1.0,
                               2.52574e-8*MeV,
                               Data::AdjointNuclearDataProperties::Native_FILE,
                               0 ) );

    h1_definition.setDataProperties( properties );
  }

  {
    std::shared_ptr<const Data::ThermalNuclearDataProperties> properties(
               new Data::ACEThermalNuclearDataProperties(
                                             {1001, 1002, 8016},
                                             2.52574e-8*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "ltwtr.71t" ) );

    h1_definition.setDataProperties( properties );
  }

  {
    std::shared_ptr<const Data::AdjointThermalNuclearDataProperties> properties(
               new Data::TestAdjointThermalNuclearDataProperties(
                        "light water",
                        {1001, 1002, 8016},
                        2.52574e-8*MeV,
                        Data::AdjointThermalNuclearDataProperties::Native_FILE,
                        0 ) );

    h1_definition.setDataProperties( properties );
  }

  {
    std::shared_ptr<const Data::PhotonuclearDataProperties> properties(
               new Data::ACEPhotonuclearDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             "1001.10u" ) );

    h1_definition.setDataProperties( properties );
  }
  
  {
    std::shared_ptr<const Data::AdjointPhotonuclearDataProperties> properties(
               new Data::TestAdjointPhotonuclearDataProperties(
                          1001,
                          1.0,
                          Data::AdjointPhotonuclearDataProperties::Native_FILE,
                          0 ) );

    h1_definition.setDataProperties( properties );
  }

  FRENSIE_CHECK_NO_THROW( std::cout << h_definition << std::endl; );
  FRENSIE_CHECK_NO_THROW( std::cout << h1_definition << std::endl; );
}

//---------------------------------------------------------------------------//
// Check that a definition can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ScatteringCenterDefinition,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_scattering_center_definition" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::ScatteringCenterDefinition h_definition( 1000 );
    
    MonteCarlo::ScatteringCenterDefinition h1_definition( "H1-293.1K", 1001 );
    h1_definition.setAtomicWeight( 1.0 );

    {
      std::shared_ptr<const Data::PhotoatomicDataProperties> properties(
               new Data::NativeEPRPhotoatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

      h_definition.setDataProperties( properties );
      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> properties(
               new Data::NativeEPRAdjointPhotoatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

      h_definition.setDataProperties( properties );
      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::ElectroatomicDataProperties> properties(
               new Data::NativeEPRElectroatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

      h_definition.setDataProperties( properties );
      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::AdjointElectroatomicDataProperties> properties(
               new Data::NativeEPRAdjointElectroatomicDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             Data::H_ATOM ) );

      h_definition.setDataProperties( properties );
      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::NuclearDataProperties> properties(
               new Data::ACENuclearDataProperties(
                                             1.0,
                                             2.52574e-8*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "1001.71c" ) );

      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::AdjointNuclearDataProperties> properties(
               new Data::TestAdjointNuclearDataProperties(
                               1001,
                               1.0,
                               2.52574e-8*MeV,
                               Data::AdjointNuclearDataProperties::Native_FILE,
                               0 ) );

      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::ThermalNuclearDataProperties> properties(
               new Data::ACEThermalNuclearDataProperties(
                                             {1001, 1002, 8016},
                                             2.52574e-8*MeV,
                                             boost::filesystem::current_path(),
                                             0,
                                             "ltwtr.71t" ) );

      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::AdjointThermalNuclearDataProperties> properties(
               new Data::TestAdjointThermalNuclearDataProperties(
                        "light water",
                        {1001, 1002, 8016},
                        2.52574e-8*MeV,
                        Data::AdjointThermalNuclearDataProperties::Native_FILE,
                        0 ) );

      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::PhotonuclearDataProperties> properties(
               new Data::ACEPhotonuclearDataProperties(
                                             1.0*amu,
                                             boost::filesystem::current_path(),
                                             0,
                                             "1001.10u" ) );

      h1_definition.setDataProperties( properties );
    }

    {
      std::shared_ptr<const Data::AdjointPhotonuclearDataProperties> properties(
               new Data::TestAdjointPhotonuclearDataProperties(
                          1001,
                          1.0,
                          Data::AdjointPhotonuclearDataProperties::Native_FILE,
                          0 ) );

      h1_definition.setDataProperties( properties );
    }

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( h_definition ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( h1_definition ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::ScatteringCenterDefinition h_definition( "dummy", 10000 );
  MonteCarlo::ScatteringCenterDefinition h1_definition( "dummy", 8016 );

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( h_definition ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( h1_definition ) );

  iarchive.reset();

  FRENSIE_CHECK_EQUAL( h_definition.getName(), "H" );
  FRENSIE_CHECK_EQUAL( h_definition.getZAID(), Data::ZAID(1000) );
  FRENSIE_CHECK( !h_definition.isAtomicWeightSet() );
  FRENSIE_REQUIRE( h_definition.hasPhotoatomicDataProperties() );
  FRENSIE_REQUIRE( h_definition.hasAdjointPhotoatomicDataProperties() );
  FRENSIE_REQUIRE( h_definition.hasElectroatomicDataProperties() );
  FRENSIE_REQUIRE( h_definition.hasAdjointElectroatomicDataProperties() );
  FRENSIE_CHECK( !h_definition.hasNuclearDataProperties() );
  FRENSIE_CHECK( !h_definition.hasAdjointNuclearDataProperties() );
  FRENSIE_CHECK( !h_definition.hasThermalNuclearDataProperties() );
  FRENSIE_CHECK( !h_definition.hasAdjointThermalNuclearDataProperties() );
  FRENSIE_CHECK( !h_definition.hasPhotonuclearDataProperties() );
  FRENSIE_CHECK( !h_definition.hasAdjointPhotonuclearDataProperties() );

  FRENSIE_CHECK_EQUAL( h1_definition.getName(), "H1-293.1K" );
  FRENSIE_CHECK_EQUAL( h1_definition.getZAID(), Data::ZAID(1001) );
  FRENSIE_REQUIRE( h1_definition.isAtomicWeightSet() );
  FRENSIE_CHECK_EQUAL( h1_definition.getAtomicWeight(), 1.0 );
  FRENSIE_REQUIRE( h1_definition.hasPhotoatomicDataProperties() );
  FRENSIE_REQUIRE( h1_definition.hasAdjointPhotoatomicDataProperties() );
  FRENSIE_REQUIRE( h1_definition.hasElectroatomicDataProperties() );
  FRENSIE_REQUIRE( h1_definition.hasAdjointElectroatomicDataProperties() );
  FRENSIE_CHECK( h1_definition.hasNuclearDataProperties() );
  FRENSIE_CHECK( h1_definition.hasAdjointNuclearDataProperties() );
  FRENSIE_CHECK( h1_definition.hasThermalNuclearDataProperties() );
  FRENSIE_CHECK( h1_definition.hasAdjointThermalNuclearDataProperties() );
  FRENSIE_CHECK( h1_definition.hasPhotonuclearDataProperties() );
  FRENSIE_CHECK( h1_definition.hasAdjointPhotonuclearDataProperties() );

  FRENSIE_CHECK( &h_definition.getPhotoatomicDataProperties() ==
                 &h1_definition.getPhotoatomicDataProperties() );
  FRENSIE_CHECK( &h_definition.getAdjointPhotoatomicDataProperties() ==
                 &h1_definition.getAdjointPhotoatomicDataProperties() );
  FRENSIE_CHECK( &h_definition.getElectroatomicDataProperties() ==
                 &h1_definition.getElectroatomicDataProperties() );
  FRENSIE_CHECK( &h_definition.getAdjointElectroatomicDataProperties() ==
                 &h1_definition.getAdjointElectroatomicDataProperties() );
}

//---------------------------------------------------------------------------//
// end tstScatteringCenterDefinition.cpp
//---------------------------------------------------------------------------//
