//---------------------------------------------------------------------------//
//!
//! \file   tstObserverCollisionNumberDimensionDiscretization.cpp
//! \author Alex Robison
//! \brief  Observer collision number dimension discretization unit tests
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
FRENSIE_UNIT_TEST( ObserverCollisionNumberDimensionDiscretization,
                   getDimension )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getDimension(),
                       MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the name of the discretized dimension can be returned
FRENSIE_UNIT_TEST( ObserverCollisionNumberDimensionDiscretization,
                   getDimensionName )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getDimensionName(),
                       "Collision Number" );
}

//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST( ObserverCollisionNumberDimensionDiscretization,
                   getNumberOfBins )
{
  FRENSIE_CHECK_EQUAL( dimension_discretization->getNumberOfBins(), 4 );
}

//---------------------------------------------------------------------------//
// Check if a value is in the discretization
FRENSIE_UNIT_TEST( ObserverCollisionNumberDimensionDiscretization,
                   isValueInDiscretization_any )
{
  typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>::dimensionType DimensionType;
  
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any((DimensionType)0) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any((DimensionType)1) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any((DimensionType)2) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any((DimensionType)3) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any((DimensionType)4) ) );
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( boost::any((DimensionType)5) ) );
  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( boost::any((DimensionType)6) ) );
}

//---------------------------------------------------------------------------//
// Check if a value is contained in the discretization
FRENSIE_UNIT_TEST( ObserverCollisionNumberDimensionDiscretization,
                   isValueInDiscretization_wrapper )
{
  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.incrementCollisionNumber();

  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.incrementCollisionNumber();
  
  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.incrementCollisionNumber();

  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.incrementCollisionNumber();

  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.incrementCollisionNumber();

  FRENSIE_CHECK( dimension_discretization->isValueInDiscretization( photon_wrapper ) );

  photon.incrementCollisionNumber();

  FRENSIE_CHECK( !dimension_discretization->isValueInDiscretization( photon_wrapper ) );
}

//---------------------------------------------------------------------------//
// Check if a range intersects the discretization
FRENSIE_UNIT_TEST( ObserverCollisionNumberDimensionDiscretization,
                   doesRangeIntersectDiscretization )
{
  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.incrementCollisionNumber();

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.incrementCollisionNumber();
  
  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.incrementCollisionNumber();

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.incrementCollisionNumber();

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.incrementCollisionNumber();

  FRENSIE_CHECK( dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );

  photon.incrementCollisionNumber();

  FRENSIE_CHECK( !dimension_discretization->doesRangeIntersectDiscretization( photon_wrapper ) );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverCollisionNumberDimensionDiscretization,
                   calculateBinIndicesOfValue_any )
{
  typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>::dimensionType DimensionType;
  
  MonteCarlo::ObserverCollisionNumberDimensionDiscretization::BinIndexArray
    bin_indices;

  dimension_discretization->calculateBinIndicesOfValue( boost::any((DimensionType)0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any((DimensionType)1), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any((DimensionType)2), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any((DimensionType)3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any((DimensionType)4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );

  dimension_discretization->calculateBinIndicesOfValue( boost::any((DimensionType)5), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverCollisionNumberDimensionDiscretization,
                   calculateBinIndicesOfValue_wrapper )
{
  MonteCarlo::ObserverCollisionNumberDimensionDiscretization::BinIndexArray
    bin_indices;

  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverCollisionNumberDimensionDiscretization,
                   calculateBinIndicesOfValue_weights_wrapper )
{
  MonteCarlo::ObserverCollisionNumberDimensionDiscretization::BinIndexWeightPairArray
    bin_indices_and_weights;

  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 3 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfValue( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 3 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST( ObserverCollisionNumberDimensionDiscretization,
                   calculateBinIndicesOfRange )
{
  MonteCarlo::ObserverCollisionNumberDimensionDiscretization::BinIndexWeightPairArray
    bin_indices_and_weights;

  MonteCarlo::PhotonState photon( 0 );
  MonteCarlo::ObserverParticleStateWrapper photon_wrapper( photon );

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 0 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 2 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 3 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );

  photon.incrementCollisionNumber();

  dimension_discretization->calculateBinIndicesOfRange( photon_wrapper, bin_indices_and_weights );

  FRENSIE_REQUIRE_EQUAL( bin_indices_and_weights.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().first, 3 );
  FRENSIE_CHECK_EQUAL( bin_indices_and_weights.front().second, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the boundaries of a bin can be printed
FRENSIE_UNIT_TEST( ObserverCollisionNumberDimensionDiscretization,
                   printBoundariesOfBin )
{
  std::ostringstream oss;

  dimension_discretization->printBoundariesOfBin( oss, 0 );

  FRENSIE_CHECK( oss.str().find( "Collision Number Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "[" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  dimension_discretization->printBoundariesOfBin( oss, 1 );

  FRENSIE_CHECK( oss.str().find( "Collision Number Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "[" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  dimension_discretization->printBoundariesOfBin( oss, 2 );

  FRENSIE_CHECK( oss.str().find( "Collision Number Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "[" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  dimension_discretization->printBoundariesOfBin( oss, 3 );

  FRENSIE_CHECK( oss.str().find( "Collision Number Bin:" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "[" ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "," ) < oss.str().size() );
  FRENSIE_CHECK( oss.str().find( "]" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the discretization can be printed
FRENSIE_UNIT_TEST( ObserverCollisionNumberDimensionDiscretization, print )
{
  std::ostringstream oss;

  dimension_discretization->print( oss );

  FRENSIE_CHECK( oss.str().find( "Collision Number Bin Boundaries:" ) <
                 oss.str().size() );

  std::cout << oss.str() << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a discretization can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ObserverCollisionNumberDimensionDiscretization,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_observer_collision_number_dimension_discretization" );
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

  FRENSIE_CHECK_EQUAL( discretization->getNumberOfBins(), 4 );

  typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>::dimensionType DimensionType;
  
  MonteCarlo::ObserverCollisionNumberDimensionDiscretization::BinIndexArray
    bin_indices;

  discretization->calculateBinIndicesOfValue( boost::any((DimensionType)0), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  discretization->calculateBinIndicesOfValue( boost::any((DimensionType)1), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  discretization->calculateBinIndicesOfValue( boost::any((DimensionType)2), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  discretization->calculateBinIndicesOfValue( boost::any((DimensionType)3), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  discretization->calculateBinIndicesOfValue( boost::any((DimensionType)4), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );

  discretization->calculateBinIndicesOfValue( boost::any((DimensionType)5), bin_indices );

  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  MonteCarlo::ObserverCollisionNumberDimensionDiscretization::InputDataType discretization( 4 );

  discretization[0] = 1;
  discretization[1] = 2;
  discretization[2] = 3;
  discretization[3] = 5;

  dimension_discretization.reset( new MonteCarlo::ObserverCollisionNumberDimensionDiscretization( discretization ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstObserverCollisionNumberDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
