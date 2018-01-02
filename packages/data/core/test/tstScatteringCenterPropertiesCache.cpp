//---------------------------------------------------------------------------//
//!
//! \file   tstScatteringCenterPropertiesCache.cpp
//! \author Alex Robinson
//! \brief  Scattering center properties cache unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_ScatteringCenterPropertiesCache.hpp"
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

class TestScatteringCenterProperties : public Data::ScatteringCenterProperties
{

public:

  //! Default constructor
  TestScatteringCenterProperties( const std::string& name = "" )
    : d_name( name )
  { /* ... */ }

  //! Destructor
  ~TestScatteringCenterProperties()
  { /* ... */ }

  //! Check if the scattering center is an atom
  bool isAtom() const override
  { return false; }

  //! Check if the scattering center is a nuclide
  bool isNuclide() const override
  { return false; }

  /*! \brief Check if the scattering center is a mixture, compound or lattice
   * (or a single nuclide within one of these).
   */
  bool isMixture() const override
  { return false; }

  //! Get the name of the properties
  std::string name() const override
  { return d_name; }

  //! Get the atomic number(s)
  std::vector<unsigned> atomicNumbers() const override
  { return {1}; }

  //! Get the atomic mass number(s)
  std::vector<unsigned> atomicMassNumbers() const override
  { return {2}; }

  //! Get the isomer number(s)
  std::vector<unsigned> isomerNumbers() const override
  { return {0}; }

  //! Get the atomic weight(s)
  std::vector<double> atomicWeights() const override
  { return {2.0}; }

  //! Check if there is nuclear data
  bool nuclearDataAvailable() const override
  { return false; }

  //! Get the nuclear data properties
  const Data::NuclearDataProperties* getNuclearDataProperties() const override
  { return NULL; }

  //! Check if there is adjoint nuclear data
  bool adjointNuclearDataAvailable() const override
  { return false; }

  //! Get the adjoint nuclear data
  const Data::AdjointNuclearDataProperties* getAdjointNuclearDataProperties() const override
  { return NULL; }

  //! Check if there is photoatomic data
  bool photoatomicDataAvailable() const override
  { return false; }

  //! Get the photoatomic data
  const Data::PhotoatomicDataProperties* getPhotoatomicDataProperties() const override
  { return NULL; }

  //! Check if there is adjoint photoatomic data
  bool adjointPhotoatomicDataAvailable() const override
  { return false; }

  //! Get the adjoint photoatomic data properties
  const Data::AdjointPhotoatomicDataProperties* getAdjointPhotoatomicDataProperties() const override
  { return NULL; }

  //! Check if there is electroatomic data
  bool electroatomicDataAvailable() const override
  { return false; }

  //! Get the electroatomic data properties
  const Data::ElectroatomicDataProperties* getElectroatomicDataProperties() const override
  { return NULL; }

  //! Check if there is adjoint electroatomic data
  bool adjointElectroatomicDataAvailable() const override
  { return false; }

  //! Get the adjoint electroatomic data properties
  const Data::AdjointElectroatomicDataProperties* getAdjointElectroatomicDataProperties() const override
  { return NULL; }

  //! Clone the properties
  TestScatteringCenterProperties* clone() const override
  { return new TestScatteringCenterProperties( d_name ); }

  //! Deep clone the properties
  TestScatteringCenterProperties* deepClone() const override
  { return this->clone(); }

private:

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  {
    ar & boost::serialization::make_nvp( "ScatteringCenterProperties", boost::serialization::base_object<Data::ScatteringCenterProperties>(*this) );
    ar & BOOST_SERIALIZATION_NVP( d_name );
  }

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  {
    ar & boost::serialization::make_nvp( "ScatteringCenterProperties", boost::serialization::base_object<Data::ScatteringCenterProperties>(*this) );
    ar & BOOST_SERIALIZATION_NVP( d_name );
  }

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  std::string d_name;
};

BOOST_SERIALIZATION_CLASS_VERSION( TestScatteringCenterProperties, , 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TestScatteringCenterProperties, );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( TestScatteringCenterProperties, );

//EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( TestScatteringCenterProperties );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that scattering center properties can be added to a cache
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesCache, addProperties )
{
  Data::ScatteringCenterPropertiesCache cache;

  {
    TestScatteringCenterProperties h1_properties( "H1" );
    TestScatteringCenterProperties h2_properties( "H2" );

    cache.addProperties( h1_properties );
    cache.addProperties( h2_properties );

    FRENSIE_CHECK_EQUAL( cache.getNumberOfProperties(), 2 );
  }

  FRENSIE_REQUIRE( cache.doPropertiesExist( "H1" ) );

  {
    const Data::ScatteringCenterProperties& properties =
      cache.getProperties( "H1" );

    FRENSIE_CHECK_EQUAL( properties.name(), "H1" );
  }

  FRENSIE_REQUIRE( cache.doPropertiesExist( "H2" ) );

  {
    const Data::ScatteringCenterProperties& properties =
      cache.getProperties( "H2" );

    FRENSIE_CHECK_EQUAL( properties.name(), "H2" );
  }
}

//---------------------------------------------------------------------------//
// Check that scattering center properties can be removed from the cache
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesCache, removeProperties )
{
  Data::ScatteringCenterPropertiesCache cache;

  {
    TestScatteringCenterProperties h1_properties( "H1" );
    TestScatteringCenterProperties h2_properties( "H2" );

    cache.addProperties( h1_properties );
    cache.addProperties( h2_properties );

    FRENSIE_CHECK_EQUAL( cache.getNumberOfProperties(), 2 );
  }

  FRENSIE_REQUIRE( cache.doPropertiesExist( "H1" ) );

  cache.removeProperties( "H1" );

  FRENSIE_REQUIRE( !cache.doPropertiesExist( "H1" ) );
  FRENSIE_CHECK_EQUAL( cache.getNumberOfProperties(), 1 );

  cache.removeProperties( "H2" );

  FRENSIE_REQUIRE( !cache.doPropertiesExist( "H2" ) );
  FRENSIE_CHECK_EQUAL( cache.getNumberOfProperties(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the cached property names can be listed
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesCache, listPropertiesNames )
{
  Data::ScatteringCenterPropertiesCache cache;

  {
    TestScatteringCenterProperties h1_properties( "H1" );
    TestScatteringCenterProperties h2_properties( "H2" );

    cache.addProperties( h1_properties );
    cache.addProperties( h2_properties );
  }

  std::ostringstream oss;

  cache.listPropertiesNames( oss );

  FRENSIE_CHECK( oss.str().find( "H1" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "H2" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that aliases can be added
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesCache, addPropertiesAlias )
{
  Data::ScatteringCenterPropertiesCache cache;

  {
    TestScatteringCenterProperties h1_properties( "H1" );
    TestScatteringCenterProperties h2_properties( "H2" );

    cache.addProperties( h1_properties );
    cache.addProperties( h2_properties );
  }

  FRENSIE_CHECK_THROW( cache.addPropertiesAlias( "H1", "H1" ),
                       std::runtime_error );
  FRENSIE_CHECK_THROW( cache.addPropertiesAlias( "h", "h" ),
                       std::runtime_error );
  FRENSIE_CHECK_THROW( cache.addPropertiesAlias( "h", "H3" ),
                       std::runtime_error );

  FRENSIE_REQUIRE_NO_THROW( cache.addPropertiesAlias( "h", "H1" ) );
  FRENSIE_REQUIRE( cache.doesAliasExist( "h" ) );
  FRENSIE_REQUIRE( cache.doPropertiesExist( "h" ) );
  
  {
    const Data::ScatteringCenterProperties& properties =
      cache.getProperties( "h" );

    FRENSIE_CHECK_EQUAL( properties.name(), "H1" );
  }

  FRENSIE_REQUIRE_NO_THROW( cache.addPropertiesAlias( "Deuterium", "H2" ) );
  FRENSIE_REQUIRE( cache.doesAliasExist( "Deuterium" ) );
  FRENSIE_REQUIRE( cache.doPropertiesExist( "Deuterium" ) );

  {
    const Data::ScatteringCenterProperties& properties =
      cache.getProperties( "Deuterium" );

    FRENSIE_CHECK_EQUAL( properties.name(), "H2" );
  }

  FRENSIE_CHECK_EQUAL( cache.getNumberOfAliases(), 2 );
}

//---------------------------------------------------------------------------//
// Check that properties aliases can be removed
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesCache, removePropertiesAlias )
{
  Data::ScatteringCenterPropertiesCache cache;

  {
    TestScatteringCenterProperties h1_properties( "H1" );
    TestScatteringCenterProperties h2_properties( "H2" );

    cache.addProperties( h1_properties );
    cache.addProperties( h2_properties );
  }

  FRENSIE_REQUIRE_NO_THROW( cache.addPropertiesAlias( "h", "H1" ) );
  FRENSIE_REQUIRE( cache.doesAliasExist( "h" ) );

  FRENSIE_CHECK_EQUAL( cache.getNumberOfAliases(), 1 );

  cache.removePropertiesAlias( "h" );

  FRENSIE_CHECK_EQUAL( cache.getNumberOfAliases(), 0 );

  // Check that the aliases are removed if the properties are removed
  cache.addPropertiesAlias( "h", "H1" );
  cache.addPropertiesAlias( "Hydrogen", "H1" );

  FRENSIE_CHECK( cache.doesAliasExist( "h" ) );
  FRENSIE_CHECK( cache.doesAliasExist( "Hydrogen" ) );
  FRENSIE_CHECK_EQUAL( cache.getNumberOfAliases(), 2 );

  cache.removeProperties( "H1" );

  FRENSIE_CHECK( !cache.doesAliasExist( "h" ) );
  FRENSIE_CHECK( !cache.doesAliasExist( "Hydrogen" ) );
  FRENSIE_CHECK_EQUAL( cache.getNumberOfAliases(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the aliases can be listed
FRENSIE_UNIT_TEST( ScatteringCenterPropertiesCache, listAliases )
{
  Data::ScatteringCenterPropertiesCache cache;

  {
    TestScatteringCenterProperties h1_properties( "H1" );
    TestScatteringCenterProperties h2_properties( "H2" );

    cache.addProperties( h1_properties );
    cache.addProperties( h2_properties );
  }

  FRENSIE_REQUIRE_NO_THROW( cache.addPropertiesAlias( "h", "H1" ) );
  FRENSIE_REQUIRE_NO_THROW( cache.addPropertiesAlias( "Deuterium", "H2" ) );

  std::ostringstream oss;

  cache.listAliases( oss );

  FRENSIE_CHECK( oss.str().find( "h" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "Deuterium" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the cache can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ScatteringCenterPropertiesCache,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_scattering_center_properties_cache" );
  std::ostringstream archive_ostream;

  // Create and archive a cache
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Data::ScatteringCenterPropertiesCache cache;

    TestScatteringCenterProperties h1_properties( "H1" );
    TestScatteringCenterProperties h2_properties( "H2" );

    cache.addProperties( h1_properties );
    cache.addProperties( h2_properties );

    cache.addPropertiesAlias( "h", "H1" );
    cache.addPropertiesAlias( "Deuterium", "H2" );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << boost::serialization::make_nvp( cache.getArchiveName(), cache ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  // Load the cache from the archive
  Data::ScatteringCenterPropertiesCache cache;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( cache.getArchiveName(), cache ) );
  
  FRENSIE_CHECK_EQUAL( cache.getNumberOfProperties(), 2 );
  FRENSIE_CHECK( cache.doPropertiesExist( "H1" ) );
  FRENSIE_CHECK( cache.doPropertiesExist( "H2" ) );
  
  FRENSIE_CHECK_EQUAL( cache.getNumberOfAliases(), 2 );
  FRENSIE_CHECK( cache.doesAliasExist( "h" ) );
  FRENSIE_CHECK( cache.doPropertiesExist( "h" ) );
  FRENSIE_CHECK( cache.doesAliasExist( "Deuterium" ) );
  FRENSIE_CHECK( cache.doPropertiesExist( "Deuterium" ) );
  
  {
    const Data::ScatteringCenterProperties& properties =
      cache.getProperties( "h" );

    FRENSIE_CHECK_EQUAL( properties.name(), "H1" );
  }

  {
    const Data::ScatteringCenterProperties& properties =
      cache.getProperties( "Deuterium" );

    FRENSIE_CHECK_EQUAL( properties.name(), "H2" );
  }
}

//---------------------------------------------------------------------------//
// Check that scattering center properties cache can be exported and imported
FRENSIE_DATA_UNIT_TEST_DECL( ScatteringCenterPropertiesCache, save_load )
{
  FETCH_FROM_TABLE( std::string, cache_name );
  
  {
    Data::ScatteringCenterPropertiesCache cache;
    
    TestScatteringCenterProperties h1_properties( "H1" );
    TestScatteringCenterProperties h2_properties( "H2" );
    
    cache.addProperties( h1_properties );
    cache.addProperties( h2_properties );
    
    cache.addPropertiesAlias( "h", "H1" );
    cache.addPropertiesAlias( "Deuterium", "H2" );

    cache.saveToFile( cache_name );
  }

  Data::ScatteringCenterPropertiesCache cache( cache_name );

  FRENSIE_CHECK_EQUAL( cache.getNumberOfProperties(), 2 );
  FRENSIE_CHECK( cache.doPropertiesExist( "H1" ) );
  FRENSIE_CHECK( cache.doPropertiesExist( "H2" ) );
  
  FRENSIE_CHECK_EQUAL( cache.getNumberOfAliases(), 2 );
  FRENSIE_CHECK( cache.doesAliasExist( "h" ) );
  FRENSIE_CHECK( cache.doesAliasExist( "Deuterium" ) );

  cache.clear();

  FRENSIE_CHECK_EQUAL( cache.getNumberOfProperties(), 0 );
  FRENSIE_CHECK_EQUAL( cache.getNumberOfAliases(), 0 );

  cache.loadFromFile( cache_name );

  FRENSIE_CHECK_EQUAL( cache.getNumberOfProperties(), 2 );
  FRENSIE_CHECK( cache.doPropertiesExist( "H1" ) );
  FRENSIE_CHECK( cache.doPropertiesExist( "H2" ) );
  
  FRENSIE_CHECK_EQUAL( cache.getNumberOfAliases(), 2 );
  FRENSIE_CHECK( cache.doesAliasExist( "h" ) );
  FRENSIE_CHECK( cache.doesAliasExist( "Deuterium" ) );
}

FRENSIE_DATA_UNIT_TEST_INST( ScatteringCenterPropertiesCache, save_load )
{
  COLUMNS()         << "cache_name";
  NEW_ROW( "xml" )  << "test_scattering_center_properties_cache.xml";
  NEW_ROW( "txt" )  << "test_scattering_center_properties_cache.txt";
  NEW_ROW( "bin" )  << "test_scattering_center_properties_cache.bin";
  NEW_ROW( "h5fa" ) << "test_scattering_center_properties_cache.h5fa";
}

//---------------------------------------------------------------------------//
// end tstScatteringCenterPropertiesCache.hpp
//---------------------------------------------------------------------------//
