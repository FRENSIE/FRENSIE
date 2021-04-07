//---------------------------------------------------------------------------//
//!
//! \file   tstObserverTimeDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Observer source time dimension discretization unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
dimension_discretization;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the discretized dimension can be returned
FRENSIE_UNIT_TEST( ObserverTimeDimensionDiscretization, getDimension )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getDimension(),
                       MonteCarlo::OBSERVER_TIME_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the name of the discretized dimension can be returned
FRENSIE_UNIT_TEST( ObserverTimeDimensionDiscretization, getDimensionName )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getDimensionName(), "Time" );
}

//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST( ObserverTimeDimensionDiscretization, getNumberOfBins )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getNumberOfBins(), 3 );
}

//---------------------------------------------------------------------------//
// Check if a value is in the discretization
FRENSIE_UNIT_TEST( ObserverTimeDimensionDiscretization,
                   isValueInDiscretization_any )
{
  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( boost::any(0.0) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any(1e-6) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any(1e-3) ) );
  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( boost::any(5e-3) ) );
}

//---------------------------------------------------------------------------//
// Check if a value is in the discretization
FRENSIE_UNIT_TEST( ObserverTimeDimensionDiscretization,
                   isValueInDiscretization_wrapper )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setTime( 0.0 );

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.setTime( 1e-6 );

  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );
  
  photon.setTime( 1e-3 );
  
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.setTime( 5e-3 );
  
  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( photon_wrapper ) );
}

//---------------------------------------------------------------------------//
// Check if a range intersects the discretization
FRENSIE_UNIT_TEST( ObserverTimeDimensionDiscretization,
                   doesRangeIntersectDiscretization )
{
  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  // The range is below the lowest bin boundary
  photon.setTime( 0.0 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 2997.92458 );

  FRENSIE_CHECK( !dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  // The range ends on the lowest bin boundary
  photon.setTime( 1e-6 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsEndTime( 1.0 );

  FRENSIE_CHECK( !dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  // The lowest bin boundary intersects the range
  photon.setTime( 0.0 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896.22900000002 );

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  // The range lies within the lowest and highest bin boundaries
  photon.setTime( 5e-6 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 14839726.671 );

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  // The range extends below lowest bin boundary and above highest bin boundary
  photon.setTime( 0.0 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896229.0 );

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  // The highest bin boundary intersects the range
  photon.setTime( 1e-4 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 146898304.42 );

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  // The range starts on the highest bin boundary
  photon.setTime( 1e-3 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 1.0 );

  FRENSIE_CHECK( !dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  // The range is above the highest bin boundary
  photon.setTime( 5e-3 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 1.0 );

  FRENSIE_CHECK( !dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverTimeDimensionDiscretization,
                   calculateBinIndicesOfValue_any )
{
  MonteCarlo::ObserverTimeDimensionDiscretization::BinIndexArray
    bin_indices;

  dimension_discretization->calculateBinIndicesOfValue( boost::any(1e-6), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(1e-5), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(5e-5), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(1e-4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(5e-4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any(1e-3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverTimeDimensionDiscretization,
                   calculateBinIndicesOfValue_wrapper )
{
  MonteCarlo::ObserverTimeDimensionDiscretization::BinIndexArray
    bin_indices;

  MonteCarlo::PhotonState photon( 0 );
  photon.setTime( 1e-6 );
  
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon.setTime( 1e-5 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon.setTime( 5e-5 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  photon.setTime( 1e-4 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  photon.setTime( 5e-4 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  photon.setTime( 1e-3 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverTimeDimensionDiscretization,
                   calculateBinIndicesOfValue_weights_wrapper )
{
  MonteCarlo::ObserverTimeDimensionDiscretization::BinIndexWeightPairArray
    bin_indices_and_weights;

  MonteCarlo::PhotonState photon( 0 );
  photon.setTime( 1e-6 );
  
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setTime( 1e-5 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setTime( 5e-5 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setTime( 1e-4 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setTime( 5e-4 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.setTime( 1e-3 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the bin indices of a range can be calculated
FRENSIE_UNIT_TEST( ObserverTimeDimensionDiscretization,
                   calculateBinIndicesOfRange )
{
  MonteCarlo::ObserverTimeDimensionDiscretization::BinIndexWeightPairArray
    bin_indices_and_weights;
  
  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  // The lowest bin boundary intersects the range
  photon.setTime( 0.0 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896.22900000002 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights.front().second,
                                   0.8,
                                   1e-15 );

  // The range is completely inside of the first bin
  photon.setTime( 2e-6 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 179875.4748 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  // The second bin boundary intersects the range
  photon.setTime( 2e-6 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 539626.4244 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights.front().second,
                                   0.44444444444444453,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.back().first, 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights.back().second,
                                   0.5555555555555556,
                                   1e-15 );
  

  // The highest bin boundary intersects the range
  photon.setTime( 5e-4 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 134906606.10000002 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights.front().second,
                                   0.1111111111111111,
                                   1e-15 );

  // The range extends below lowest bin boundary and above highest bin boundary
  photon.setTime( 0.0 );
  photon_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 149896229.0 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 3 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[0].second,
                                   0.0018,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[1].second,
                                   0.018,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[2].first, 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bin_indices_and_weights[2].second,
                                   0.18,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the boundaries of a bin can be printed
FRENSIE_UNIT_TEST( ObserverTimeDimensionDiscretization,
                   printBoundariesOfBin )
{
  std::ostringstream oss;

  dimension_discretization->printBoundariesOfBin( oss, 0 );

  FRENSIE_CHECK( oss.str().find( "Time Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "[" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  dimension_discretization->printBoundariesOfBin( oss, 1 );

  FRENSIE_CHECK( oss.str().find( "Time Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "(" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  dimension_discretization->printBoundariesOfBin( oss, 2 );

  FRENSIE_CHECK( oss.str().find( "Time Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "(" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the discretization can be printed
FRENSIE_UNIT_TEST( ObserverTimeDimensionDiscretization, print )
{
  std::ostringstream oss;

  dimension_discretization->print( oss );

  FRENSIE_CHECK( oss.str().find( "Time Bin Boundaries:" ) <
                 oss.str().size() );

  std::cout << oss.str() << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a discretization can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ObserverTimeDimensionDiscretization,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_observer_time_dimension_discretization" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
      discretization = dimension_discretization;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( discretization ) )
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
    discretization;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( discretization ) );

  iarchive.reset();

  FRENSIE_CHECK_EQUAL( discretization->getNumberOfBins(), 3 );

  MonteCarlo::ObserverTimeDimensionDiscretization::BinIndexArray
    bin_indices;

  discretization->calculateBinIndicesOfValue( boost::any(1e-6), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  discretization->calculateBinIndicesOfValue( boost::any(1e-5), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  discretization->calculateBinIndicesOfValue( boost::any(5e-5), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  discretization->calculateBinIndicesOfValue( boost::any(1e-4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  discretization->calculateBinIndicesOfValue( boost::any(5e-4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  discretization->calculateBinIndicesOfValue( boost::any(1e-3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  MonteCarlo::ObserverTimeDimensionDiscretization::InputDataType discretization( 4 );

  discretization[0] = 1e-6;
  discretization[1] = 1e-5;
  discretization[2] = 1e-4;
  discretization[3] = 1e-3;

  dimension_discretization.reset( new MonteCarlo::ObserverTimeDimensionDiscretization( discretization ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstObserverTimeDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
