//---------------------------------------------------------------------------//
//!
//! \file   tstJustInTimeInitializer.cpp
//! \author Alex Robinson
//! \brief  Just-in-time initializer unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/unique_ptr.hpp>

// FRENSIE Includes
#include "Utility_JustInTimeInitializer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Classes
//---------------------------------------------------------------------------//
class TestClassA
{
public:

  //! Default constructor
  TestClassA()
  { /* ... */ }

  //! Constructor
  TestClassA( const std::string& data )
    : d_data( std::make_unique<std::string>( data ) )
  { /* ... */ }

  //! Destructor
  ~TestClassA()
  { /* ... */ }

  //! Check if the object has been initialized
  bool isInitialized() const
  { return (bool)d_data; }
  
private:

  // Initialize just-in-time
  void initializeJustInTime()
  {
    FRENSIE_LOG_NOTIFICATION( "Initializing test object of type A" );
    
    d_data = std::make_unique<std::string>( "test data" );
  }

  // Save the object to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  { /* ... */ }

  // Load the object from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  { Utility::JustInTimeInitializer::getInstance().addObject( *this ); }

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the Utility::JustInTimeInitializer object as a friend
  friend class Utility::JustInTimeInitializer;

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The data that can be initialized just-in-time
  std::unique_ptr<std::string> d_data;
};

class TestClassB
{
public:

  //! Default contructor
  TestClassB()
    : d_initialized( false ),
      d_data()
  { /* ... */ }

  //! Constructor
  TestClassB( const std::string& data )
    : d_initialized( true ),
      d_data( std::make_unique<TestClassA>( data ) )
  { /* ... */ }

  //! Destructor
  ~TestClassB()
  { /* ... */ }

  //! Check if the object has been initialized
  bool isInitialized() const
  { return d_initialized; }
  
private:

  // Initialize just-in-time
  void initializeJustInTime()
  {
    FRENSIE_LOG_NOTIFICATION( "Initializing test object of type B" );

    if( !d_data )
      d_data = std::make_unique<TestClassA>( "Test Data" );
    
    TEST_FOR_EXCEPTION( !d_data->isInitialized(),
                        std::runtime_error,
                        "TestClassA was not initialized before TestClassB!" );

    d_initialized = true;
  }

  // Save the object to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  { ar & BOOST_SERIALIZATION_NVP( d_data ); }

  // Load the object from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_NVP( d_data );
    
    Utility::JustInTimeInitializer::getInstance().addObject( *this );
  }

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the Utility::JustInTimeInitializer object as a friend
  friend class Utility::JustInTimeInitializer;

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // Flag that get set when initializeJustInTime is called
  bool d_initialized;

  // The stored data
  std::unique_ptr<TestClassA> d_data;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the JustInTimeInitializer class can be retrieved
FRENSIE_UNIT_TEST( JustInTimeInitializer, getInstance )
{
  FRENSIE_CHECK_NO_THROW( Utility::JustInTimeInitializer::getInstance() );
}

//---------------------------------------------------------------------------//
// Check that the JustInTimeInitializer class can be activated/deactivated
FRENSIE_UNIT_TEST( JustInTimeInitializer, activate_deactivate )
{
  FRENSIE_CHECK( !Utility::JustInTimeInitializer::getInstance().isActive() );

  Utility::JustInTimeInitializer::getInstance().activate();
  
  FRENSIE_CHECK( Utility::JustInTimeInitializer::getInstance().isActive() );

  Utility::JustInTimeInitializer::getInstance().deactivate();
  
  FRENSIE_CHECK( !Utility::JustInTimeInitializer::getInstance().isActive() );
}

//---------------------------------------------------------------------------//
// Check that objects can be assigned to the JustInTimeInitializer
FRENSIE_UNIT_TEST( JustInTimeInitializer, addObject )
{
  TestClassA test_obj_a;
  TestClassB test_obj_b;

  Utility::JustInTimeInitializer& initializer =
    Utility::JustInTimeInitializer::getInstance();

  // Before the initializer is active, objects will not be added
  FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 0 );

  initializer.addObject( test_obj_a );

  FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 0 );

  initializer.addObject( test_obj_b );

  FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 0 );

  // Activate the initializer
  initializer.activate();

  initializer.addObject( test_obj_a );

  FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 1 );

  initializer.addObject( test_obj_b );

  FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 2 );

  initializer.clear();

  FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 0 );

  initializer.deactivate();
}

//---------------------------------------------------------------------------//
// Check that objects can be initialized using the JustInTimeInitializer
FRENSIE_UNIT_TEST( JustInTimeInitializer, initializeObjects )
{
  // Initialization of objects will occur immediately when the
  // just-in-time initializer is inactive
  {
    TestClassA test_obj_a;
    TestClassB test_obj_b;

    Utility::JustInTimeInitializer& initializer =
      Utility::JustInTimeInitializer::getInstance();

    FRENSIE_CHECK( !test_obj_a.isInitialized() );
    
    initializer.addObject( test_obj_a );

    FRENSIE_CHECK( test_obj_a.isInitialized() );

    FRENSIE_CHECK( !test_obj_b.isInitialized() );
    
    initializer.addObject( test_obj_b );
    
    FRENSIE_CHECK( test_obj_b.isInitialized() );

    FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 0 );
    
    initializer.initializeObjects();
    
    FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 0 );
    
    initializer.clear();
  }

  // Initialization will be deferred when the just-in-time initializer is
  // active
  {
    TestClassA test_obj_a;
    TestClassB test_obj_b;

    Utility::JustInTimeInitializer& initializer =
      Utility::JustInTimeInitializer::getInstance();

    initializer.activate();

    initializer.addObject( test_obj_a );
    initializer.addObject( test_obj_b );
    
    FRENSIE_CHECK( !test_obj_a.isInitialized() );
    FRENSIE_CHECK( !test_obj_b.isInitialized() );
    
    initializer.initializeObjects();
    
    FRENSIE_CHECK( test_obj_a.isInitialized() );
    FRENSIE_CHECK( test_obj_b.isInitialized() );
    FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 2 );
    
    initializer.clear();

    initializer.deactivate();
  }
}

//---------------------------------------------------------------------------//
// Check that objects can be initialized and cleared from the
// JustInTimeInitializer
FRENSIE_UNIT_TEST( JustInTimeInitializer, initializeObjectsAndClear )
{
  // Initialization of objects will occur immediately when the
  // just-in-time initializer is inactive
  {
    TestClassA test_obj_a;
    TestClassB test_obj_b;
    
    Utility::JustInTimeInitializer& initializer =
      Utility::JustInTimeInitializer::getInstance();

    FRENSIE_CHECK( !test_obj_a.isInitialized() );
    
    initializer.addObject( test_obj_a );

    FRENSIE_CHECK( test_obj_a.isInitialized() );

    FRENSIE_CHECK( !test_obj_b.isInitialized() );
    
    initializer.addObject( test_obj_b );
    
    FRENSIE_CHECK( test_obj_b.isInitialized() );

    FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 0 );
    
    initializer.initializeObjectsAndClear();
    
    FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 0 );
  }

  // Initialization will be deferred when the just-in-time initializer is
  // active
  {
    TestClassA test_obj_a;
    TestClassB test_obj_b;
    
    Utility::JustInTimeInitializer& initializer =
      Utility::JustInTimeInitializer::getInstance();

    initializer.activate();
    
    initializer.addObject( test_obj_a );
    initializer.addObject( test_obj_b );
    
    FRENSIE_CHECK( !test_obj_a.isInitialized() );
    FRENSIE_CHECK( !test_obj_b.isInitialized() );
    
    initializer.initializeObjectsAndClear();
    
    FRENSIE_CHECK( test_obj_a.isInitialized() );
    FRENSIE_CHECK( test_obj_b.isInitialized() );
    FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 0 );

    initializer.deactivate();
  }
}

//---------------------------------------------------------------------------//
// Check that the JustInTimeInitializer works correctly when combined with
// the boost serialization system
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( JustInTimeInitializer,
                                   archive_inactive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_basic_cartesian_coordinate_conversion_policy" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    TestClassA test_object_a( "test data a" );
    TestClassB test_object_b( "test data b" );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( test_object_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( test_object_b ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  TestClassA test_object_a;
  TestClassB test_object_b;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( test_object_a ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( test_object_b ) );

  FRENSIE_CHECK( test_object_a.isInitialized() );
  FRENSIE_CHECK( test_object_b.isInitialized() );
}

//---------------------------------------------------------------------------//
// Check that the JustInTimeInitializer works correctly when combined with
// the boost serialization system
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( JustInTimeInitializer,
                                   archive_active,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_basic_cartesian_coordinate_conversion_policy" );
  std::ostringstream archive_ostream;

  // Create and archive some uniform distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    TestClassA test_object_a( "test data a" );
    TestClassB test_object_b( "test data b" );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( test_object_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( test_object_b ) );
  }

  Utility::JustInTimeInitializer& initializer =
    Utility::JustInTimeInitializer::getInstance();

  initializer.activate();

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  TestClassA test_object_a;
  TestClassB test_object_b;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( test_object_a ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( test_object_b ) );

  FRENSIE_CHECK( !test_object_a.isInitialized() );
  FRENSIE_CHECK( !test_object_b.isInitialized() );
    
  FRENSIE_CHECK_EQUAL( initializer.getNumberOfObjects(), 3 );

  initializer.initializeObjectsAndClear();

  FRENSIE_CHECK( test_object_a.isInitialized() );
  FRENSIE_CHECK( test_object_b.isInitialized() );
}

//---------------------------------------------------------------------------//
// end tstJustInTimeInitializer.cpp
//---------------------------------------------------------------------------//
