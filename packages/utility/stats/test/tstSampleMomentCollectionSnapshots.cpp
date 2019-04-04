//---------------------------------------------------------------------------//
//!
//! \file   tstSampleMomentCollectionSnapshots.cpp
//! \author Alex Robinson
//! \brief  The sample moment collection snapshots unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

// FRENSIE Includes
#include "Utility_SampleMomentCollectionSnapshots.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Template Typedefs
//---------------------------------------------------------------------------//
typedef std::tuple<double,
                   boost::units::quantity<boost::units::cgs::length>,
                   boost::units::quantity<boost::units::si::length> > TestingTypes;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the size of a collection can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollectionSnapshots, size, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::SampleMomentCollectionSnapshots<T,std::list,1,2,3,4> empty_moment_snapshot_collection;

  FRENSIE_CHECK_EQUAL( empty_moment_snapshot_collection.size(), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,2,3,4>&>( empty_moment_snapshot_collection ).size()), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,3,4>&>( empty_moment_snapshot_collection ).size()), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,4>&>( empty_moment_snapshot_collection ).size()), 0 );

  Utility::SampleMomentCollectionSnapshots<T,std::list,4,3,2,1> moment_snapshot_collection( 10 );

  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.size(), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,3,2,1>&>( moment_snapshot_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,2,1>&>( moment_snapshot_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,1>&>( moment_snapshot_collection ).size()), 10 );
}

//---------------------------------------------------------------------------//
// Check that the collection snapshots can be cleared
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollectionSnapshots, clear, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::SampleMomentCollectionSnapshots<T,std::list,1,2,3,4> moment_snapshot_collection( 10 );

  moment_snapshot_collection.clear();

  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.size(), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,2,3,4>&>( moment_snapshot_collection ).size()), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,3,4>&>( moment_snapshot_collection ).size()), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,4>&>( moment_snapshot_collection ).size()), 0 );
}

//---------------------------------------------------------------------------//
// Check that the collection snapshots can be resized
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollectionSnapshots, resize, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::SampleMomentCollectionSnapshots<T,std::list,1,2,3,4> moment_snapshot_collection;

  moment_snapshot_collection.resize( 10 );

  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.size(), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,2,3,4>&>( moment_snapshot_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,3,4>&>( moment_snapshot_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,4>&>( moment_snapshot_collection ).size()), 10 );
}

//---------------------------------------------------------------------------//
// Check that the collection snapshots can be resized
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollectionSnapshots, takeSnapshot, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  typedef typename Utility::SampleMomentCollectionSnapshots<T,std::list,1,2,3,4>::MomentSnapshotContainerType MomentSnapshotContainerType1;
  typedef typename Utility::SampleMomentCollectionSnapshots<T,std::list,2,3,4>::MomentSnapshotContainerType MomentSnapshotContainerType2;
  typedef typename Utility::SampleMomentCollectionSnapshots<T,std::list,3,4>::MomentSnapshotContainerType MomentSnapshotContainerType3;
  typedef typename Utility::SampleMomentCollectionSnapshots<T,std::list,4>::MomentSnapshotContainerType MomentSnapshotContainerType4;

  Utility::SampleMomentCollectionSnapshots<T,std::list,1,2,3,4> moment_snapshot_collection( 2 );

  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getNumberOfSnapshots(), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,2,3,4>&>( moment_snapshot_collection ).getNumberOfSnapshots()), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,3,4>&>( moment_snapshot_collection ).getNumberOfSnapshots()), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,4>&>( moment_snapshot_collection ).getNumberOfSnapshots()), 0 );
  FRENSIE_CHECK( moment_snapshot_collection.getSnapshotIndices().empty() );
  FRENSIE_CHECK( moment_snapshot_collection.getSnapshotSamplingTimes().empty() );

  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 2 );
  moment_collection.addRawScore( Utility::QuantityTraits<T>::one()*10. );

  moment_snapshot_collection.takeSnapshot( 1, 1.0, moment_collection );

  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getNumberOfSnapshots(), 1 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,2,3,4>&>( moment_snapshot_collection ).getNumberOfSnapshots()), 1 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,3,4>&>( moment_snapshot_collection ).getNumberOfSnapshots()), 1 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,4>&>( moment_snapshot_collection ).getNumberOfSnapshots()), 1 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getSnapshotIndices().size(), 1 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getSnapshotIndices().front(), 1 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getSnapshotSamplingTimes().size(), 1 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getSnapshotSamplingTimes().front(), 1.0 );

  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<4>(moment_snapshot_collection, 0)),
                       MomentSnapshotContainerType4({Utility::getCurrentScore<4>(moment_collection, 0)}) );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshots<4>(moment_snapshot_collection, 1),
                       MomentSnapshotContainerType4({Utility::getCurrentScore<4>(moment_collection, 1)}) );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshots<3>(moment_snapshot_collection, 0),
                       MomentSnapshotContainerType3({Utility::getCurrentScore<3>(moment_collection, 0)}) );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshots<3>(moment_snapshot_collection, 1),
                       MomentSnapshotContainerType3({Utility::getCurrentScore<3>(moment_collection, 1)}) );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshots<2>(moment_snapshot_collection, 0),
                       MomentSnapshotContainerType2({Utility::getCurrentScore<2>(moment_collection, 0)}) );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshots<2>(moment_snapshot_collection, 1),
                       MomentSnapshotContainerType2({Utility::getCurrentScore<2>(moment_collection, 1)}) );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshots<1>(moment_snapshot_collection, 0),
                       MomentSnapshotContainerType1({Utility::getCurrentScore<1>(moment_collection, 0)}) );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshots<1>(moment_snapshot_collection, 1),
                       MomentSnapshotContainerType1({Utility::getCurrentScore<1>(moment_collection, 1)}) );

  moment_collection.addRawScore( Utility::QuantityTraits<T>::one()*2. );
  moment_collection.addRawScore( Utility::QuantityTraits<T>::one()*5. );
  moment_snapshot_collection.takeSnapshot( 2, 2.0, moment_collection );

  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getNumberOfSnapshots(), 2 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,2,3,4>&>( moment_snapshot_collection ).getNumberOfSnapshots()), 2 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,3,4>&>( moment_snapshot_collection ).getNumberOfSnapshots()), 2 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollectionSnapshots<T,std::list,4>&>( moment_snapshot_collection ).getNumberOfSnapshots()), 2 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getSnapshotIndices().size(), 2 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getSnapshotIndices().front(), 1 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getSnapshotIndices().back(), 3 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getSnapshotSamplingTimes().size(), 2 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getSnapshotSamplingTimes().front(), 1.0 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection.getSnapshotSamplingTimes().back(), 3.0 );

  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<3>(moment_snapshot_collection, 0)).size(), 2 );
  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<3>(moment_snapshot_collection, 1)).size(), 2 );

  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<3>(moment_snapshot_collection, 0)).back(),
                       (Utility::getCurrentScore<3>(moment_collection, 0)) );
  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<3>(moment_snapshot_collection, 1)).back(),
                       (Utility::getCurrentScore<3>(moment_collection, 1)) );

  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<2>(moment_snapshot_collection, 0)).size(), 2 );
  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<2>(moment_snapshot_collection, 1)).size(), 2 );

  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<2>(moment_snapshot_collection, 0)).back(),
                       (Utility::getCurrentScore<2>(moment_collection, 0)) );
  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<2>(moment_snapshot_collection, 1)).back(),
                       (Utility::getCurrentScore<2>(moment_collection, 1)) );

  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<1>(moment_snapshot_collection, 0)).size(), 2 );
  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<1>(moment_snapshot_collection, 1)).size(), 2 );

  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<1>(moment_snapshot_collection, 0)).back(),
                       (Utility::getCurrentScore<1>(moment_collection, 0)) );
  FRENSIE_CHECK_EQUAL( (Utility::getScoreSnapshots<1>(moment_snapshot_collection, 1)).back(),
                       (Utility::getCurrentScore<1>(moment_collection, 1)) );
}

//---------------------------------------------------------------------------//
// Check that two collection snapshots can be merged
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollectionSnapshots, mergeSnapshots, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  typedef typename Utility::SampleMomentCollectionSnapshots<T,std::list,1,2,3,4>::MomentValueType MomentValueType1;
  typedef typename Utility::SampleMomentCollectionSnapshots<T,std::list,2,3,4>::MomentValueType MomentValueType2;
  typedef typename Utility::SampleMomentCollectionSnapshots<T,std::list,3,4>::MomentValueType MomentValueType3;
  typedef typename Utility::SampleMomentCollectionSnapshots<T,std::list,4>::MomentValueType MomentValueType4;

  Utility::SampleMomentCollectionSnapshots<T,std::list,1,2,3,4> moment_snapshot_collection_a( 2 );
  Utility::SampleMomentCollectionSnapshots<T,std::list,1,2,3,4> moment_snapshot_collection_b( 2 );

  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection_a( 2 );
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection_b( 2 );
  
  moment_collection_a.addRawScore( Utility::QuantityTraits<T>::one()*10. );
  moment_collection_b.addRawScore( Utility::QuantityTraits<T>::one()*5. );

  moment_snapshot_collection_a.takeSnapshot( 1, 1.0, moment_collection_a );
  moment_snapshot_collection_b.takeSnapshot( 1, 1.0, moment_collection_b );

  FRENSIE_CHECK_EQUAL( moment_snapshot_collection_a.getNumberOfSnapshots(), 1 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection_b.getNumberOfSnapshots(), 1 );

  moment_collection_a.addRawScore( Utility::QuantityTraits<T>::one()*8. );
  moment_collection_a.addRawScore( Utility::QuantityTraits<T>::one()*12. );
  
  moment_collection_b.addRawScore( Utility::QuantityTraits<T>::one()*3. );
  moment_collection_b.addRawScore( Utility::QuantityTraits<T>::one()*7. );

  moment_snapshot_collection_a.takeSnapshot( 2, 2.0, moment_collection_a );
  moment_snapshot_collection_b.takeSnapshot( 2, 2.0, moment_collection_b );

  FRENSIE_CHECK_EQUAL( moment_snapshot_collection_a.getNumberOfSnapshots(), 2 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection_b.getNumberOfSnapshots(), 2 );

  moment_snapshot_collection_a.mergeSnapshots( moment_snapshot_collection_b );

  FRENSIE_CHECK_EQUAL( moment_snapshot_collection_a.getNumberOfSnapshots(), 4 );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection_a.getSnapshotIndices(),
                       std::list<uint64_t>({1, 3, 4, 6}) );
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection_a.getSnapshotSamplingTimes(),
                       std::list<double>({1.0, 3.0, 4.0, 6.0}) );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<4>( moment_snapshot_collection_a, 0, 0 ),
                       Utility::QuantityTraits<MomentValueType4>::one()*10000. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<4>( moment_snapshot_collection_a, 0, 1 ),
                       Utility::QuantityTraits<MomentValueType4>::one()*34832. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<4>( moment_snapshot_collection_a, 0, 2 ),
                       Utility::QuantityTraits<MomentValueType4>::one()*35457. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<4>( moment_snapshot_collection_a, 0, 3 ),
                       Utility::QuantityTraits<MomentValueType4>::one()*37939. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<4>( moment_snapshot_collection_a, 1, 0 ),
                       Utility::QuantityTraits<MomentValueType4>::one()*10000. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<4>( moment_snapshot_collection_a, 1, 1 ),
                       Utility::QuantityTraits<MomentValueType4>::one()*34832. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<4>( moment_snapshot_collection_a, 1, 2 ),
                       Utility::QuantityTraits<MomentValueType4>::one()*35457. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<4>( moment_snapshot_collection_a, 1, 3 ),
                       Utility::QuantityTraits<MomentValueType4>::one()*37939. );
  
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<3>( moment_snapshot_collection_a, 0, 0 ),
                       Utility::QuantityTraits<MomentValueType3>::one()*1000. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<3>( moment_snapshot_collection_a, 0, 1 ),
                       Utility::QuantityTraits<MomentValueType3>::one()*3240. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<3>( moment_snapshot_collection_a, 0, 2 ),
                       Utility::QuantityTraits<MomentValueType3>::one()*3365. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<3>( moment_snapshot_collection_a, 0, 3 ),
                       Utility::QuantityTraits<MomentValueType3>::one()*3735. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<3>( moment_snapshot_collection_a, 1, 0 ),
                       Utility::QuantityTraits<MomentValueType3>::one()*1000. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<3>( moment_snapshot_collection_a, 1, 1 ),
                       Utility::QuantityTraits<MomentValueType3>::one()*3240. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<3>( moment_snapshot_collection_a, 1, 2 ),
                       Utility::QuantityTraits<MomentValueType3>::one()*3365. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<3>( moment_snapshot_collection_a, 1, 3 ),
                       Utility::QuantityTraits<MomentValueType3>::one()*3735. );

  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<2>( moment_snapshot_collection_a, 0, 0 ),
                       Utility::QuantityTraits<MomentValueType2>::one()*100. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<2>( moment_snapshot_collection_a, 0, 1 ),
                       Utility::QuantityTraits<MomentValueType2>::one()*308. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<2>( moment_snapshot_collection_a, 0, 2 ),
                       Utility::QuantityTraits<MomentValueType2>::one()*333. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<2>( moment_snapshot_collection_a, 0, 3 ),
                       Utility::QuantityTraits<MomentValueType2>::one()*391. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<2>( moment_snapshot_collection_a, 1, 0 ),
                       Utility::QuantityTraits<MomentValueType2>::one()*100. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<2>( moment_snapshot_collection_a, 1, 1 ),
                       Utility::QuantityTraits<MomentValueType2>::one()*308. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<2>( moment_snapshot_collection_a, 1, 2 ),
                       Utility::QuantityTraits<MomentValueType2>::one()*333. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<2>( moment_snapshot_collection_a, 1, 3 ),
                       Utility::QuantityTraits<MomentValueType2>::one()*391. );

  FRENSIE_CHECK_EQUAL( Utility::getMomentSnapshot<1>( moment_snapshot_collection_a, 0, 0 ).getCurrentScore(),
                       Utility::QuantityTraits<MomentValueType1>::one()*10. );
  FRENSIE_CHECK_EQUAL( Utility::getMomentSnapshot<1>( moment_snapshot_collection_a, 0, 1 ).getCurrentScore(),
                       Utility::QuantityTraits<MomentValueType1>::one()*30. );
  FRENSIE_CHECK_EQUAL( Utility::getMomentSnapshot<1>( moment_snapshot_collection_a, 0, 2 ).getCurrentScore(),
                       Utility::QuantityTraits<MomentValueType1>::one()*35. );
  FRENSIE_CHECK_EQUAL( Utility::getMomentSnapshot<1>( moment_snapshot_collection_a, 0, 3 ).getCurrentScore(),
                       Utility::QuantityTraits<MomentValueType1>::one()*45. );
                      
  FRENSIE_CHECK_EQUAL( moment_snapshot_collection_b.getNumberOfSnapshots(), 2 );
}

//---------------------------------------------------------------------------//
// Check that a moment collection can be archived
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollectionSnapshots, archive, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  typedef typename Utility::SampleMomentCollectionSnapshots<T,std::list,1,2,3,4>::MomentValueType MomentValueType1;
  typedef typename Utility::SampleMomentCollectionSnapshots<T,std::list,2,3,4>::MomentValueType MomentValueType2;
  typedef typename Utility::SampleMomentCollectionSnapshots<T,std::list,3,4>::MomentValueType MomentValueType3;
  typedef typename Utility::SampleMomentCollectionSnapshots<T,std::list,4>::MomentValueType MomentValueType4;

  Utility::SampleMomentCollectionSnapshots<T,std::list,1,2,3,4> moment_snapshot_collection( 2 );

  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 2 );
  
  moment_collection.addRawScore( Utility::QuantityTraits<T>::one()*10. );
  
  moment_snapshot_collection.takeSnapshot( 1, 1.0, moment_collection );

  moment_collection.addRawScore( Utility::QuantityTraits<T>::one()*8. );
  moment_collection.addRawScore( Utility::QuantityTraits<T>::one()*12. );

  moment_snapshot_collection.takeSnapshot( 2, 2.0, moment_collection );

  std::ostringstream archive_ostream;
  
  {
    boost::archive::xml_oarchive archive( archive_ostream );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "collection_snapshots", moment_snapshot_collection ) );
  }
  
  Utility::SampleMomentCollectionSnapshots<T,std::list,1,2,3,4> extracted_moment_snapshot_collection;

  {
    std::istringstream iss( archive_ostream.str() );

    boost::archive::xml_iarchive archive( iss );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "collection_snapshots", extracted_moment_snapshot_collection ) );
  }

  // Check that the first moment snapshots were archived successfully
  FRENSIE_CHECK_EQUAL( extracted_moment_snapshot_collection.getNumberOfSnapshots(), 2 );
  FRENSIE_CHECK_EQUAL( extracted_moment_snapshot_collection.getSnapshotIndices(),
                       std::list<uint64_t>({1, 3}) );
  FRENSIE_CHECK_EQUAL( extracted_moment_snapshot_collection.getSnapshotSamplingTimes(),
                       std::list<double>({1.0, 3.0}) );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<4>( extracted_moment_snapshot_collection, 0, 0 ),
                       Utility::QuantityTraits<MomentValueType4>::one()*10000. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<4>( extracted_moment_snapshot_collection, 0, 1 ),
                       Utility::QuantityTraits<MomentValueType4>::one()*34832. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<4>( extracted_moment_snapshot_collection, 1, 0 ),
                       Utility::QuantityTraits<MomentValueType4>::one()*10000. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<4>( extracted_moment_snapshot_collection, 1, 1 ),
                       Utility::QuantityTraits<MomentValueType4>::one()*34832. );
  
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<3>( extracted_moment_snapshot_collection, 0, 0 ),
                       Utility::QuantityTraits<MomentValueType3>::one()*1000. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<3>( extracted_moment_snapshot_collection, 0, 1 ),
                       Utility::QuantityTraits<MomentValueType3>::one()*3240. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<3>( extracted_moment_snapshot_collection, 1, 0 ),
                       Utility::QuantityTraits<MomentValueType3>::one()*1000. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<3>( extracted_moment_snapshot_collection, 1, 1 ),
                       Utility::QuantityTraits<MomentValueType3>::one()*3240. );

  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<2>( extracted_moment_snapshot_collection, 0, 0 ),
                       Utility::QuantityTraits<MomentValueType2>::one()*100. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<2>( extracted_moment_snapshot_collection, 0, 1 ),
                       Utility::QuantityTraits<MomentValueType2>::one()*308. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<2>( extracted_moment_snapshot_collection, 1, 0 ),
                       Utility::QuantityTraits<MomentValueType2>::one()*100. );
  FRENSIE_CHECK_EQUAL( Utility::getScoreSnapshot<2>( extracted_moment_snapshot_collection, 1, 1 ),
                       Utility::QuantityTraits<MomentValueType2>::one()*308. );

  FRENSIE_CHECK_EQUAL( Utility::getMomentSnapshot<1>( extracted_moment_snapshot_collection, 0, 0 ).getCurrentScore(),
                       Utility::QuantityTraits<MomentValueType1>::one()*10. );
  FRENSIE_CHECK_EQUAL( Utility::getMomentSnapshot<1>( extracted_moment_snapshot_collection, 0, 1 ).getCurrentScore(),
                       Utility::QuantityTraits<MomentValueType1>::one()*30. );
}

//---------------------------------------------------------------------------//
// end tstSampleMomentCollectionSnapshots.cpp
//---------------------------------------------------------------------------//
