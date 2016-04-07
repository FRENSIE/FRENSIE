//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCInstanceFactory.cpp
//! \author Alex Robinson
//! \brief  DagMC instance factory class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Include
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Geometry_DagMC.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_Tuple.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string test_geom_xml_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that DagMC can be properly initialized
TEUCHOS_UNIT_TEST( DagMCInstanceFactory, initializeDagMC )
{
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );
  
  Geometry::DagMCInstanceFactory::initializeDagMC( *geom_rep );

  TEST_EQUALITY_CONST( Geometry::DagMC::getTerminationCellPropertyName(),
		       "graveyard" );
  TEST_EQUALITY_CONST( Geometry::DagMC::getReflectingSurfacePropertyName(),
                       "spec.reflect" );
  TEST_EQUALITY_CONST( Geometry::DagMC::getMaterialPropertyName(),
		       "mat" );
  TEST_EQUALITY_CONST( Geometry::DagMC::getDensityPropertyName(),
		       "rho" );
  TEST_EQUALITY_CONST( Geometry::DagMC::getEstimatorPropertyName(),
		       "tally" );
  TEST_EQUALITY_CONST( Geometry::DagMC::getSurfaceCurrentName(),
		       "surf.cur" );
  TEST_EQUALITY_CONST( Geometry::DagMC::getSurfaceFluxName(),
		       "surf.flux" );
  TEST_EQUALITY_CONST( Geometry::DagMC::getCellPulseHeightName(),
		       "c.pulse" );
  TEST_EQUALITY_CONST( Geometry::DagMC::getCellTrackLengthFluxName(),
		       "c.tl.f" );
  TEST_EQUALITY_CONST( Geometry::DagMC::getCellCollisionFluxName(),
		       "c.c.f" );

  TEST_ASSERT( Geometry::DagMC::isTerminationCell( 188 ) );

  TEST_ASSERT( Geometry::DagMC::isVoidCell( 189 ) );

  TEST_ASSERT( Geometry::DagMC::isReflectingSurface( 408 ) );

  std::map<Geometry::ModuleTraits::InternalCellHandle,unsigned>
    cell_id_mat_id_map;

  Geometry::DagMC::getCellMaterialIds( cell_id_mat_id_map );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.size(), 54 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 9 )->second, 1 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 88 )->second, 1 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 136 )->second, 2 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 19 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 41 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 63 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 82 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 152 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 166 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 184 )->second, 3 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 3 )->second, 4 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 7 )->second, 4 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 13 )->second, 7 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 83 )->second, 7 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 154 )->second, 7 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 168 )->second, 7 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 1 )->second, 8 );
  
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 26 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 27 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 28 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 29 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 30 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 31 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 32 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 33 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 34 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 35 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 36 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 37 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 48 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 49 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 50 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 51 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 52 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 53 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 54 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 55 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 56 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 57 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 58 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 59 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 70 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 71 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 72 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 73 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 74 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 75 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 76 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 77 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 78 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 79 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 80 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 81 )->second, 9 );
  
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 5 )->second, 10 );

  std::map<Geometry::ModuleTraits::InternalCellHandle,double>
    cell_id_density_map;

  TEST_NOTHROW( Geometry::DagMC::getCellDensities( cell_id_density_map ) );

  TEST_EQUALITY_CONST( cell_id_density_map.size(), 54 );

  TEST_EQUALITY_CONST( cell_id_density_map.size(), 54 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 9 )->second, -8.027 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 88 )->second, -8.027 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 136 )->second, -7.75 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 19 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 41 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 63 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 82 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 152 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 166 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 184 )->second, -0.001633 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 3 )->second, -0.99823 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 7 )->second, -0.99823 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 13 )->second, -5.65 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 83 )->second, -5.65 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 154 )->second, -5.65 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 168 )->second, -5.65 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 1 )->second, -1.8583 );
  
  TEST_EQUALITY_CONST( cell_id_density_map.find( 26 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 27 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 28 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 29 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 30 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 31 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 32 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 33 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 34 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 35 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 36 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 37 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 48 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 49 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 50 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 51 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 52 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 53 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 54 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 55 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 56 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 57 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 58 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 59 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 70 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 71 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 72 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 73 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 74 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 75 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 76 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 77 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 78 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 79 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 80 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 81 )->second, -7.83 );
  
  TEST_EQUALITY_CONST( cell_id_density_map.find( 5 )->second, -13.31 );

  std::map<unsigned,Utility::Trip<std::string,std::string,std::vector<Geometry::ModuleTraits::InternalCellHandle> > > cell_estimator_id_data_map;

  TEST_NOTHROW( Geometry::DagMC::getCellEstimatorData( 
                                                cell_estimator_id_data_map ) );

  TEST_EQUALITY_CONST( cell_estimator_id_data_map.size(), 5 );
  TEST_ASSERT( cell_estimator_id_data_map.count( 0 ) );
  TEST_ASSERT( cell_estimator_id_data_map.count( 1 ) );
  TEST_ASSERT( cell_estimator_id_data_map.count( 2 ) );
  TEST_ASSERT( cell_estimator_id_data_map.count( 3 ) );
  TEST_ASSERT( cell_estimator_id_data_map.count( 4 ) );

  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 0 )->second.first,
                       "c.tl.f" );
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 0 )->second.second,
                       "n" );
  TEST_EQUALITY_CONST( 
                     cell_estimator_id_data_map.find( 0 )->second.third.size(),
                     55 );
  
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 1 )->second.first,
                       "c.tl.f" );
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 1 )->second.second,
                       "p" );
  TEST_EQUALITY_CONST( 
                     cell_estimator_id_data_map.find( 1 )->second.third.size(),
                     55 );

  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 2 )->second.first,
                       "c.c.f" );
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 2 )->second.second,
                       "n" );
  TEST_EQUALITY_CONST( 
                     cell_estimator_id_data_map.find( 2 )->second.third.size(),
                     36 );

  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 3 )->second.first,
                       "c.c.f" );
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 3 )->second.second,
                       "p" );
  TEST_EQUALITY_CONST( 
                     cell_estimator_id_data_map.find( 3 )->second.third.size(),
                     36 );
  
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 4 )->second.first,
                       "c.pulse" );
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 4 )->second.second,
                       "p" );
  TEST_EQUALITY_CONST( 
                     cell_estimator_id_data_map.find( 4 )->second.third.size(),
                     2 );

  std::map<unsigned,Utility::Trip<std::string,std::string,std::vector<Geometry::ModuleTraits::InternalSurfaceHandle> > > surface_estimator_id_data_map;

  TEST_NOTHROW( Geometry::DagMC::getSurfaceEstimatorData( 
                                             surface_estimator_id_data_map ) );

  TEST_EQUALITY_CONST( surface_estimator_id_data_map.size(), 4 );
  TEST_ASSERT( surface_estimator_id_data_map.count( 5 ) );
  TEST_ASSERT( surface_estimator_id_data_map.count( 6 ) );
  TEST_ASSERT( surface_estimator_id_data_map.count( 7 ) );
  TEST_ASSERT( surface_estimator_id_data_map.count( 8 ) );

  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 5 )->second.first,
                       "surf.flux" );
  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 5 )->second.second,
                       "n" );
  TEST_EQUALITY_CONST( 
                  surface_estimator_id_data_map.find( 5 )->second.third.size(),
                  7 );

  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 6 )->second.first,
                       "surf.flux" );
  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 6 )->second.second,
                       "p" );
  TEST_EQUALITY_CONST( 
                  surface_estimator_id_data_map.find( 6 )->second.third.size(),
                  7 );

  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 7 )->second.first,
                       "surf.cur" );
  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 7 )->second.second,
                       "n" );
  TEST_EQUALITY_CONST( 
                  surface_estimator_id_data_map.find( 7 )->second.third.size(),
                  7 );

  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 8 )->second.first,
                       "surf.cur" );
  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 8 )->second.second,
                       "p" );
  TEST_EQUALITY_CONST( 
                  surface_estimator_id_data_map.find( 8 )->second.third.size(),
                  7 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char* argv[] )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_xml_file",
		 &test_geom_xml_file_name,
		 "Test xml geometry file name" );
  
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstDagMCInstanceFactory.cpp
//---------------------------------------------------------------------------//
