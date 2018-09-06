//---------------------------------------------------------------------------//
//!
//! \file   tstUniqueIdManager.cpp
//! \author Alex Robinson
//! \brief  Unique id manager unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_UniqueIdManager.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types.
//---------------------------------------------------------------------------//

//! A simple test struct that stores a unique id
template<typename IdType>
struct TestStruct
{
  //! Constructor
  TestStruct( const IdType id )
    : d_id( id )
  { /* ... */ }

  //! Destructor
  ~TestStruct()
  { /* ... */ }

  //! Return the id
  IdType getId() const
  { return d_id; }

  //! Return the id manager
  const MonteCarlo::UniqueIdManager<TestStruct,IdType>& getIdManager() const
  { return d_id; }

private:

  // Serialize the test struct
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_NVP( d_id ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The id
  MonteCarlo::UniqueIdManager<TestStruct<IdType>,IdType> d_id;
};

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that unique ids are constructed correctly
FRENSIE_UNIT_TEST( UniqueIdManager, constructor )
{
  std::unique_ptr<TestStruct<int> > test_obj_int;

  FRENSIE_CHECK_NO_THROW( test_obj_int.reset( new TestStruct<int>( 0 ) ) );

  FRENSIE_CHECK_THROW( TestStruct<int> bad_test_obj_int( 0 ),
                       std::runtime_error );

  test_obj_int.reset();

  FRENSIE_CHECK_NO_THROW( TestStruct<int> good_test_obj_int( 0 ) );

  // The manager should only be aware of ids used with its owner type
  test_obj_int.reset( new TestStruct<int>( 0 ) );

  std::unique_ptr<TestStruct<size_t> > test_obj_size_t;

  FRENSIE_CHECK_NO_THROW( test_obj_size_t.reset( new TestStruct<size_t>( 0 ) ) );

  FRENSIE_CHECK_THROW( TestStruct<size_t> bad_test_obj_size_t( 0 ),
                       std::runtime_error );

  test_obj_size_t.reset();

  FRENSIE_CHECK_NO_THROW( TestStruct<size_t> good_test_obj_size_t( 0 ) );
}

//---------------------------------------------------------------------------//
// Check that the id can be returned
FRENSIE_UNIT_TEST( UniqueIdManager, getId )
{
  TestStruct<int> test_obj_0( 0 );

  FRENSIE_CHECK_EQUAL( test_obj_0.getIdManager().getId(), 0 );
  FRENSIE_CHECK_EQUAL( test_obj_0.getId(), 0 );

  TestStruct<int> test_obj_1( 1 );

  FRENSIE_CHECK_EQUAL( test_obj_1.getIdManager().getId(), 1 );
  FRENSIE_CHECK_EQUAL( test_obj_1.getId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the id can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UniqueIdManager, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_unique_id_manager" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    TestStruct<int> test_obj_int_0( 0 );
    TestStruct<int> test_obj_int_1( 1 );

    TestStruct<size_t> test_obj_size_t_0( 0 );
    TestStruct<size_t> test_obj_size_t_1( 1 );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( test_obj_int_0 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( test_obj_int_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( test_obj_size_t_0 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( test_obj_size_t_1 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  TestStruct<int> test_obj_int_0( 10 ), test_obj_int_1( 11 );
  TestStruct<size_t> test_obj_size_t_0( 10 ), test_obj_size_t_1( 11 );

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( test_obj_int_0 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( test_obj_int_1 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( test_obj_size_t_0 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( test_obj_size_t_1 ) );

  FRENSIE_CHECK_EQUAL( test_obj_int_0.getId(), 0 );
  FRENSIE_CHECK_EQUAL( test_obj_int_1.getId(), 1 );

  FRENSIE_CHECK_EQUAL( test_obj_size_t_0.getId(), 0 );
  FRENSIE_CHECK_EQUAL( test_obj_size_t_1.getId(), 1 );
}

//---------------------------------------------------------------------------//
// end tstUniqueIdManager.cpp
//---------------------------------------------------------------------------//
