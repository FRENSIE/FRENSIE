//---------------------------------------------------------------------------//
//!
//! \file   tstObserverSourceIdDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Observer source id dimension discretization unit tests
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
FRENSIE_UNIT_TEST( ObserverSourceIdDimensionDiscretization, getDimension )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getDimension(),
                       MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the name of the discretized dimension can be returned
FRENSIE_UNIT_TEST( ObserverSourceIdDimensionDiscretization,
                   getDimensionName )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getDimensionName(),
                       "Source Id" );
}

//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST( ObserverSourceIdDimensionDiscretization, getNumberOfBins )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getNumberOfBins(), 3 );
}

//---------------------------------------------------------------------------//
// Check if a value is in the discretization
FRENSIE_UNIT_TEST( ObserverSourceIdDimensionDiscretization,
                   isValueInDiscretization_any )
{
  typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION>::dimensionType DimensionType;

  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any((DimensionType)0) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any((DimensionType)1) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any((DimensionType)2) ) );
  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( boost::any((DimensionType)3) ) );
}

//---------------------------------------------------------------------------//
// Check if a value is in the discretization
FRENSIE_UNIT_TEST( ObserverSourceIdDimensionDiscretization,
                   isValueInDiscretization_wrapper )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setSourceId( 0 );

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.setSourceId( 1 );

  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.setSourceId( 2 );

  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.setSourceId( 3 );

  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( photon_wrapper ) );
}

//---------------------------------------------------------------------------//
// Check if a range intersects the discretization
FRENSIE_UNIT_TEST( ObserverSourceIdDimensionDiscretization,
                   doesRangeIntersectDiscretization )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setSourceId( 0 );

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.setSourceId( 1 );

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.setSourceId( 2 );

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.setSourceId( 3 );

  FRENSIE_CHECK( !dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverSourceIdDimensionDiscretization,
                   calculateBinIndicesOfValue_any )
{
  typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION>::dimensionType DimensionType;

  MonteCarlo::ObserverSourceIdDimensionDiscretization::BinIndexArray
    bin_indices;

  dimension_discretization->calculateBinIndicesOfValue( boost::any((DimensionType)0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
  FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );
  FRENSIE_CHECK_EQUAL( bin_indices[1], 1 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any((DimensionType)1), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
  FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );
  FRENSIE_CHECK_EQUAL( bin_indices[1], 2 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any((DimensionType)2), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverSourceIdDimensionDiscretization,
                   calculateBinIndicesOfValue_wrapper )
{
  MonteCarlo::ObserverSourceIdDimensionDiscretization::BinIndexArray
    bin_indices;

  MonteCarlo::PhotonState photon( 0 );
  photon.setSourceId( 0 );

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
  FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );
  FRENSIE_CHECK_EQUAL( bin_indices[1], 1 );

  photon.setSourceId( 1 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
  FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );
  FRENSIE_CHECK_EQUAL( bin_indices[1], 2 );

  photon.setSourceId( 2 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverSourceIdDimensionDiscretization,
                   calculateBinIndicesOfValue_weights_wrapper )
{
  MonteCarlo::ObserverSourceIdDimensionDiscretization::BinIndexWeightPairArray
    bin_indices_and_weights;

  MonteCarlo::PhotonState photon( 0 );
  photon.setSourceId( 0 );

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].second, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].second, 1.0 );

  photon.setSourceId( 1 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].second, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].second, 1.0 );

  photon.setSourceId( 2 );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].second, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverSourceIdDimensionDiscretization,
                   calculateBinIndicesOfRange )
{
  MonteCarlo::ObserverSourceIdDimensionDiscretization::BinIndexWeightPairArray
    bin_indices_and_weights;

  MonteCarlo::PhotonState photon( 0 );
  photon.setSourceId( 0 );

  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].second, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].second, 1.0 );

  photon.setSourceId( 1 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].second, 1.0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[1].second, 1.0 );

  photon.setSourceId( 2 );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights[0].second, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the boundaries of a bin can be printed
FRENSIE_UNIT_TEST( ObserversSourceIdDimensionDiscretization,
                   printBoundariesOfBin )
{
  std::ostringstream oss;

  dimension_discretization->printBoundariesOfBin( oss, 0 );

  FRENSIE_CHECK( oss.str().find( "Source Id Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "{" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "}" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  dimension_discretization->printBoundariesOfBin( oss, 1 );

  FRENSIE_CHECK( oss.str().find( "Source Id Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "{" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "}" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  dimension_discretization->printBoundariesOfBin( oss, 2 );

  FRENSIE_CHECK( oss.str().find( "Source Id Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "{" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "}" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the discretization can be printed
FRENSIE_UNIT_TEST( ObserverSourceIdDimensionDiscretization, print )
{
  std::ostringstream oss;

  dimension_discretization->print( oss );

  FRENSIE_CHECK( oss.str().find( "Source Id Bins:" ) <
                 oss.str().size() );

  std::cout << oss.str() << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a discretization can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ObserverSourceIdDimensionDiscretization,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_observer_source_id_dimension_discretization" );
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

  typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION>::dimensionType DimensionType;

  MonteCarlo::ObserverSourceIdDimensionDiscretization::BinIndexArray
    bin_indices;

  discretization->calculateBinIndicesOfValue( boost::any((DimensionType)0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
  FRENSIE_CHECK_EQUAL( bin_indices[0], 0 );
  FRENSIE_CHECK_EQUAL( bin_indices[1], 1 );

  discretization->calculateBinIndicesOfValue( boost::any((DimensionType)1), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 2 );
  FRENSIE_CHECK_EQUAL( bin_indices[0], 1 );
  FRENSIE_CHECK_EQUAL( bin_indices[1], 2 );

  discretization->calculateBinIndicesOfValue( boost::any((DimensionType)2), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices[0], 2 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  MonteCarlo::ObserverSourceIdDimensionDiscretization::InputDataType discretization( 3 );

  discretization[0].insert( 0 );
  
  discretization[1].insert( 0 );
  discretization[1].insert( 1 );

  discretization[2].insert( 1 );
  discretization[2].insert( 2 );

  dimension_discretization.reset( new MonteCarlo::ObserverSourceIdDimensionDiscretization( discretization ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstObserverSourceIdDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
