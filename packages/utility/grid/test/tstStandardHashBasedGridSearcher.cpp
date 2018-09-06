//---------------------------------------------------------------------------//
//!
//! \file   tstHashBasedGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Hash-based grid searcher unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//

std::unique_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher;

std::unique_ptr<Utility::HashBasedGridSearcher<quantity<MegaElectronVolt> > > energy_grid_searcher;

std::unique_ptr<Utility::HashBasedGridSearcher<double> > processed_grid_searcher;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a value can be tested for containment within the grid
FRENSIE_UNIT_TEST( HashBasedGridSearcher, isValueWithinGridBounds )
{
  FRENSIE_CHECK( !grid_searcher->isValueWithinGridBounds( 0.5 ) );
  FRENSIE_CHECK( grid_searcher->isValueWithinGridBounds( 1.0 ) );
  FRENSIE_CHECK( grid_searcher->isValueWithinGridBounds( 500.0 ) );
  FRENSIE_CHECK( grid_searcher->isValueWithinGridBounds( 1000.0 ) );
  FRENSIE_CHECK( !grid_searcher->isValueWithinGridBounds( 1000.5 ) );

  FRENSIE_CHECK( !energy_grid_searcher->isValueWithinGridBounds( 0.5*MeV ) );
  FRENSIE_CHECK( energy_grid_searcher->isValueWithinGridBounds( 1.0*MeV ) );
  FRENSIE_CHECK( energy_grid_searcher->isValueWithinGridBounds( 500.0*MeV ) );
  FRENSIE_CHECK( energy_grid_searcher->isValueWithinGridBounds( 1000.0*MeV ) );
  FRENSIE_CHECK( !energy_grid_searcher->isValueWithinGridBounds( 1000.5*MeV ) );

  FRENSIE_CHECK( !processed_grid_searcher->isValueWithinGridBounds( 0.5 ) );
  FRENSIE_CHECK( processed_grid_searcher->isValueWithinGridBounds( 1.0 ) );
  FRENSIE_CHECK( processed_grid_searcher->isValueWithinGridBounds( 500.0 ) );
  FRENSIE_CHECK( processed_grid_searcher->isValueWithinGridBounds( 1000.0 ) );
  FRENSIE_CHECK( !processed_grid_searcher->isValueWithinGridBounds( 1000.5 ) );
}

//---------------------------------------------------------------------------//
// Check that the index of the lower bin boundary of a value can be found
FRENSIE_UNIT_TEST( HashBasedGridSearcher, findLowerBinIndex )
{
  size_t grid_index = grid_searcher->findLowerBinIndex( 1.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 0u );

  grid_index = grid_searcher->findLowerBinIndex( 1.5 );

  FRENSIE_CHECK_EQUAL( grid_index, 0u );

  grid_index = grid_searcher->findLowerBinIndex( 10.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 9u );

  grid_index = grid_searcher->findLowerBinIndex( 10.5 );

  FRENSIE_CHECK_EQUAL( grid_index, 9u );

  grid_index = grid_searcher->findLowerBinIndex( 100.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 99u );

  grid_index = grid_searcher->findLowerBinIndex( 100.5 );

  FRENSIE_CHECK_EQUAL( grid_index, 99u );

  grid_index = grid_searcher->findLowerBinIndex( 1000.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 998u );
}

//---------------------------------------------------------------------------//
// Check that the index of the lower bin boundary of a quantity can be found
FRENSIE_UNIT_TEST( HashBasedGridSearcher, findLowerBinIndex_quantity )
{
  size_t grid_index = energy_grid_searcher->findLowerBinIndex( 1.0*MeV );

  FRENSIE_CHECK_EQUAL( grid_index, 0u );

  grid_index = energy_grid_searcher->findLowerBinIndex( 1.5*MeV );

  FRENSIE_CHECK_EQUAL( grid_index, 0u );

  grid_index = energy_grid_searcher->findLowerBinIndex( 10.0*MeV );

  FRENSIE_CHECK_EQUAL( grid_index, 9u );

  grid_index = energy_grid_searcher->findLowerBinIndex( 10.5*MeV );

  FRENSIE_CHECK_EQUAL( grid_index, 9u );

  grid_index = energy_grid_searcher->findLowerBinIndex( 100.0*MeV );

  FRENSIE_CHECK_EQUAL( grid_index, 99u );

  grid_index = energy_grid_searcher->findLowerBinIndex( 100.5*MeV );

  FRENSIE_CHECK_EQUAL( grid_index, 99u );

  grid_index = energy_grid_searcher->findLowerBinIndex( 1000.0*MeV );

  FRENSIE_CHECK_EQUAL( grid_index, 998u );
}

//---------------------------------------------------------------------------//
// Check that the index of the lower bin boundary of a value can be found
FRENSIE_UNIT_TEST( HashBasedGridSearcher, findLowerBinIndex_processed )
{
  size_t grid_index = processed_grid_searcher->findLowerBinIndex( 1.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 0u );

  grid_index = processed_grid_searcher->findLowerBinIndex( 1.5 );

  FRENSIE_CHECK_EQUAL( grid_index, 0u );

  grid_index = processed_grid_searcher->findLowerBinIndex( 10.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 9u );

  grid_index = processed_grid_searcher->findLowerBinIndex( 10.5 );

  FRENSIE_CHECK_EQUAL( grid_index, 9u );

  grid_index = processed_grid_searcher->findLowerBinIndex( 100.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 99u );

  grid_index = processed_grid_searcher->findLowerBinIndex( 100.5 );

  FRENSIE_CHECK_EQUAL( grid_index, 99u );

  grid_index = processed_grid_searcher->findLowerBinIndex( 1000.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 998u );
}

//---------------------------------------------------------------------------//
// Check that hte index of the lower bin boundary of a value can be found
FRENSIE_UNIT_TEST( HashBasedGridSearcher,
                   findLowerBinIndexIncludingUpperBound )
{
  size_t grid_index =
    grid_searcher->findLowerBinIndexIncludingUpperBound( 1.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 0u );

  grid_index = grid_searcher->findLowerBinIndexIncludingUpperBound( 1.5 );

  FRENSIE_CHECK_EQUAL( grid_index, 0u );

  grid_index = grid_searcher->findLowerBinIndexIncludingUpperBound( 2.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 0u );

  grid_index = grid_searcher->findLowerBinIndexIncludingUpperBound( 2.5 );

  FRENSIE_CHECK_EQUAL( grid_index, 1u );

  grid_index = grid_searcher->findLowerBinIndexIncludingUpperBound( 10.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 8u );

  grid_index = grid_searcher->findLowerBinIndexIncludingUpperBound( 10.5 );

  FRENSIE_CHECK_EQUAL( grid_index, 9u );

  grid_index = grid_searcher->findLowerBinIndexIncludingUpperBound( 100.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 98u );

  grid_index = grid_searcher->findLowerBinIndexIncludingUpperBound( 100.5 );

  FRENSIE_CHECK_EQUAL( grid_index, 99u );

  grid_index = grid_searcher->findLowerBinIndexIncludingUpperBound( 1000.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 998u );
}

//---------------------------------------------------------------------------//
// Test that a grid searcher can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( HashBasedGridSearcher,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_standard_hash_based_grid_searcher" );
  std::ostringstream archive_ostream;

  // Create and archive some grid searchers
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    std::vector<double> grid( 1000 );
    std::vector<quantity<MegaElectronVolt> > energy_grid( grid.size() );

    for( size_t i = 0; i < grid.size(); ++i )
    {
      grid[i] = i+1;
      energy_grid[i] = Utility::QuantityTraits<quantity<MegaElectronVolt> >::initializeQuantity( i+1 );
    }

    std::shared_ptr<Utility::StandardHashBasedGridSearcher<std::vector<double>,false> > shared_grid_searcher( new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>( grid, 100 ) );

    std::shared_ptr<Utility::HashBasedGridSearcher<double> >
      shared_base_grid_searcher = shared_grid_searcher;

    std::shared_ptr<Utility::StandardHashBasedGridSearcher<std::vector<quantity<MegaElectronVolt> >,false> > shared_energy_grid_searcher( new Utility::StandardHashBasedGridSearcher<std::vector<quantity<MegaElectronVolt> >,false>( energy_grid, 100 ) );

    std::shared_ptr<Utility::HashBasedGridSearcher<quantity<MegaElectronVolt> > >
      shared_base_energy_grid_searcher = shared_energy_grid_searcher;

    FRENSIE_REQUIRE_NO_THROW(
                     (*oarchive) << BOOST_SERIALIZATION_NVP( grid_searcher ) );
    FRENSIE_REQUIRE_NO_THROW(
              (*oarchive) << BOOST_SERIALIZATION_NVP( energy_grid_searcher ) );
    FRENSIE_REQUIRE_NO_THROW(
           (*oarchive) << BOOST_SERIALIZATION_NVP( processed_grid_searcher ) );
    FRENSIE_REQUIRE_NO_THROW(
              (*oarchive) << BOOST_SERIALIZATION_NVP( shared_grid_searcher ) );
    FRENSIE_REQUIRE_NO_THROW(
         (*oarchive) << BOOST_SERIALIZATION_NVP( shared_base_grid_searcher ) );
    FRENSIE_REQUIRE_NO_THROW(
       (*oarchive) << BOOST_SERIALIZATION_NVP( shared_energy_grid_searcher ) );
    FRENSIE_REQUIRE_NO_THROW(
       (*oarchive) << BOOST_SERIALIZATION_NVP( shared_base_energy_grid_searcher ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::unique_ptr<Utility::HashBasedGridSearcher<double> > local_grid_searcher;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "grid_searcher", local_grid_searcher ) );
  FRENSIE_CHECK( local_grid_searcher.get() != NULL );

  std::unique_ptr<Utility::HashBasedGridSearcher<quantity<MegaElectronVolt> > >
    local_energy_grid_searcher;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "energy_grid_searcher", local_energy_grid_searcher ) );
  FRENSIE_CHECK( local_energy_grid_searcher.get() != NULL );

  std::unique_ptr<Utility::HashBasedGridSearcher<double> > local_processed_grid_searcher;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "processed_grid_searcher", local_processed_grid_searcher ) );
  FRENSIE_CHECK( local_processed_grid_searcher.get() != NULL );

  std::shared_ptr<Utility::StandardHashBasedGridSearcher<std::vector<double>,false> > shared_grid_searcher;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_grid_searcher ) );
  FRENSIE_CHECK( shared_grid_searcher.get() != NULL );

  std::shared_ptr<Utility::HashBasedGridSearcher<double> >
    shared_base_grid_searcher;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_base_grid_searcher ) );
  FRENSIE_CHECK( shared_base_grid_searcher.get() != NULL );
  
  std::shared_ptr<Utility::StandardHashBasedGridSearcher<std::vector<quantity<MegaElectronVolt> >,false> > shared_energy_grid_searcher;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_energy_grid_searcher ) );
  FRENSIE_CHECK( shared_energy_grid_searcher.get() != NULL );

  std::shared_ptr<Utility::HashBasedGridSearcher<quantity<MegaElectronVolt> > >
    shared_base_energy_grid_searcher;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( shared_base_energy_grid_searcher ) );
  FRENSIE_CHECK( shared_base_energy_grid_searcher.get() != NULL );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the grid and processed grid
  std::vector<double> grid( 1000 );
  
  std::shared_ptr<std::vector<double> >
    processed_grid( new std::vector<double>( grid.size() ) );
  
  for( size_t i = 0; i < grid.size(); ++i )
  {
    grid[i] = i+1;
    
    (*processed_grid)[i] = std::log( i+1 );
  }

  // Copy the grid internally
  grid_searcher.reset(
              new Utility::StandardHashBasedGridSearcher<std::vector<double> >(
						       grid,
						       grid.front(),
						       grid.back(),
						       100 ) );

  // Use the shared grid
  processed_grid_searcher.reset(
          new Utility::StandardHashBasedGridSearcher<std::vector<double>,true>(
				       processed_grid,
				       processed_grid->front(),
				       processed_grid->back(),
				       100 ) );

  // Create the energy grid
  std::shared_ptr<std::vector<quantity<MegaElectronVolt> > >
    energy_grid( new std::vector<quantity<MegaElectronVolt> >( grid.size() ) );

  for( size_t i = 0; i < energy_grid->size(); ++i )
  {
    (*energy_grid)[i] =
      Utility::QuantityTraits<quantity<MegaElectronVolt> >::initializeQuantity( i+1 );
  }

  // Use the shared energy grid
  energy_grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<std::vector<quantity<MegaElectronVolt> >,false>( energy_grid, 10 ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHashBasedGridSearcher.cpp
//---------------------------------------------------------------------------//
