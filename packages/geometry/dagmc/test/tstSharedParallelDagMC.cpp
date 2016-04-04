//---------------------------------------------------------------------------//
//!
//! \file   tstSharedParallelDagMC.cpp
//! \author Alex Robinson
//! \brief  DagMC wrapper class shared parallel unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Geometry_DagMC.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a parallel external ray trace can be done
TEUCHOS_UNIT_TEST( DagMC, parallel_external_ray_trace )
{
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Pair<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Pair<double,double> >
    distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  {
    std::shared_ptr<Geometry::Ray> ray;
    
    // Initialize the ray
    if( Utility::GlobalOpenMPSession::getThreadId()%6 == 0 )
      ray.reset( new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 1 )
      ray.reset( new Geometry::Ray( -41.0, -41.0, 59.0, 0.0, 0.0, 1.0 ) );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 2 )
      ray.reset( new Geometry::Ray( -39.0, -39.0, 59.0, 0.0, 0.0, 1.0 ) );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 3 )
      ray.reset( new Geometry::Ray( -38.0, -38.0, 59.0, 0.0, 0.0, 1.0 ) );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 4)
      ray.reset( new Geometry::Ray( -37.0, -37.0, 59.0, 0.0, 0.0, 1.0 ) );
    else
      ray.reset( new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

    // Find the cell that contains the ray
    Geometry::ModuleTraits::InternalCellHandle cell =
      Geometry::DagMC::findCellContainingExternalRay( *ray );

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].first = cell;

    // Fire the ray
    Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
    double distance_to_surface_hit = 
      Geometry::DagMC::fireExternalRay( *ray, cell, surface_hit );

    surface_ids[Utility::GlobalOpenMPSession::getThreadId()].first = 
      surface_hit;

    distances[Utility::GlobalOpenMPSession::getThreadId()].first = 
      distance_to_surface_hit;

    // Advance the ray to the boundary surface
    ray->advanceHead( distance_to_surface_hit );

    // Find the cell on the other side of the boundary surface
    cell = Geometry::DagMC::getBoundaryCell( cell, surface_hit );

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].second = cell;
    
    // Fire the ray
    distance_to_surface_hit = 
      Geometry::DagMC::fireExternalRay( *ray, cell, surface_hit );

    surface_ids[Utility::GlobalOpenMPSession::getThreadId()].second = 
      surface_hit;
    
    distances[Utility::GlobalOpenMPSession::getThreadId()].second = 
      distance_to_surface_hit;

    // Advance the ray to the boundary surface
    ray->advanceHead( distance_to_surface_hit );

    // Find the cell on the other side of the boundary surface
    cell = Geometry::DagMC::getBoundaryCell( cell, surface_hit );

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].third = cell;
  }

  // Check that each of the rays traces were successful
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    correct_cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_cell_ids[i]( 53, 54, 55 );
  
  UTILITY_TEST_COMPARE_ARRAYS( cell_ids, correct_cell_ids );

  Teuchos::Array<Utility::Pair<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    correct_surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_surface_ids[i]( 242, 248 );

  UTILITY_TEST_COMPARE_ARRAYS( surface_ids, correct_surface_ids );

  Teuchos::Array<Utility::Pair<double,double> >
    correct_distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_distances.size(); ++i )
    correct_distances[i]( 1.959999084, 2.54 );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( distances, correct_distances, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that a parallel internal ray trace can be done
TEUCHOS_UNIT_TEST( DagMC, parallel_internal_ray_trace )
{
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Quad<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Quad<double,double,double,double> >
    distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  {
    {
      std::shared_ptr<Geometry::Ray> ray;
    
      // Initialize the ray
      if( Utility::GlobalOpenMPSession::getThreadId()%6 == 0 )
        ray.reset( new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );
      else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 1 )
        ray.reset( new Geometry::Ray( -41.0, -41.0, 59.0, 0.0, 0.0, 1.0 ) );
      else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 2 )
        ray.reset( new Geometry::Ray( -39.0, -39.0, 59.0, 0.0, 0.0, 1.0 ) );
      else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 3 )
        ray.reset( new Geometry::Ray( -38.0, -38.0, 59.0, 0.0, 0.0, 1.0 ) );
      else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 4)
        ray.reset( new Geometry::Ray( -37.0, -37.0, 59.0, 0.0, 0.0, 1.0 ) );
      else
        ray.reset( new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

      Geometry::DagMC::setInternalRay( *ray );
    }

    // Find the cell that contains the ray
    Geometry::ModuleTraits::InternalCellHandle cell = 
      Geometry::DagMC::findCellContainingInternalRay();

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].first = cell;

    // Fire the ray
    Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
    double distance_to_surface_hit = 
      Geometry::DagMC::fireInternalRay( surface_hit );

    surface_ids[Utility::GlobalOpenMPSession::getThreadId()].first =
      surface_hit;

    distances[Utility::GlobalOpenMPSession::getThreadId()].first = 
      distance_to_surface_hit;

    // Advance the ray to the boundary surface
    Geometry::DagMC::advanceInternalRayToCellBoundary();

    cell = Geometry::DagMC::findCellContainingInternalRay();

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].second = cell;

    // Fire the ray
    distance_to_surface_hit = Geometry::DagMC::fireInternalRay( surface_hit );

    surface_ids[Utility::GlobalOpenMPSession::getThreadId()].second =
      surface_hit;

    distances[Utility::GlobalOpenMPSession::getThreadId()].second = 
      distance_to_surface_hit;

    // Advance the ray to the boundary surface
    Geometry::DagMC::advanceInternalRayToCellBoundary();

    cell = Geometry::DagMC::findCellContainingInternalRay();

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].third = cell;

    // Fire the ray
    distance_to_surface_hit = Geometry::DagMC::fireInternalRay( surface_hit );

    surface_ids[Utility::GlobalOpenMPSession::getThreadId()].third = 
      surface_hit;

    distances[Utility::GlobalOpenMPSession::getThreadId()].third = 
      distance_to_surface_hit;
    
    // Advance the ray a substep
    Geometry::DagMC::advanceInternalRayBySubstep( 0.5*distance_to_surface_hit);

    // Change the ray direction
    Geometry::DagMC::changeInternalRayDirection( 0.0, 0.0, -1.0 );

    // Fire the ray
    distance_to_surface_hit = Geometry::DagMC::fireInternalRay( surface_hit );

    surface_ids[Utility::GlobalOpenMPSession::getThreadId()].fourth = 
      surface_hit;

    distances[Utility::GlobalOpenMPSession::getThreadId()].fourth = 
      distance_to_surface_hit;
  }

  // Check that each of the rays traces were successful
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    correct_cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_cell_ids[i]( 53, 54, 55 );
  
  UTILITY_TEST_COMPARE_ARRAYS( cell_ids, correct_cell_ids );

  Teuchos::Array<Utility::Quad<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    correct_surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_surface_ids[i]( 242, 248, 254, 248 );

  UTILITY_TEST_COMPARE_ARRAYS( surface_ids, correct_surface_ids );

  Teuchos::Array<Utility::Quad<double,double,double,double> >
    correct_distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_distances.size(); ++i )
    correct_distances[i]( 1.959999084, 2.54, 2.54, 1.27 );
  
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( distances, correct_distances, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that a parallel internal ray trace can be done
TEUCHOS_UNIT_TEST( DagMC, parallel_internal_ray_trace_with_reflection )
{
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Trip<double,double,double> >
    distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Pair<int,int> >
    reflection( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  {
    // Initialize the ray
    {
      Geometry::Ray ray( -40.0, -40.0, 108.0, 0.0, 0.0, 1.0 );
    
      Geometry::DagMC::setInternalRay( ray );
    }
    
    // Find the cell that contains the ray
    Geometry::ModuleTraits::InternalCellHandle cell = 
      Geometry::DagMC::findCellContainingInternalRay();

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].first = cell;

    // Fire the ray
    Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
    double distance_to_surface_hit = 
      Geometry::DagMC::fireInternalRay( surface_hit );

    surface_ids[Utility::GlobalOpenMPSession::getThreadId()].first = 
      surface_hit;

    distances[Utility::GlobalOpenMPSession::getThreadId()].first = 
      distance_to_surface_hit;

    // Advance the ray to the boundary surface
    reflection[Utility::GlobalOpenMPSession::getThreadId()].first = 
      Geometry::DagMC::advanceInternalRayToCellBoundary();
    
    cell = Geometry::DagMC::findCellContainingInternalRay();
    
    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].second = cell;
    
    distance_to_surface_hit = Geometry::DagMC::fireInternalRay( surface_hit );

    surface_ids[Utility::GlobalOpenMPSession::getThreadId()].second = 
      surface_hit;
    
    distances[Utility::GlobalOpenMPSession::getThreadId()].second = 
      distance_to_surface_hit;
    
    // Advance the ray to the boundary surface (reflecting)
    reflection[Utility::GlobalOpenMPSession::getThreadId()].second = 
      Geometry::DagMC::advanceInternalRayToCellBoundary();

    cell = Geometry::DagMC::findCellContainingInternalRay();

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].third = cell;
    
    distance_to_surface_hit = Geometry::DagMC::fireInternalRay( surface_hit );

    surface_ids[Utility::GlobalOpenMPSession::getThreadId()].third = 
      surface_hit;

    distances[Utility::GlobalOpenMPSession::getThreadId()].third = 
      distance_to_surface_hit;
  }

  // Check that each of the rays traces were successful
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    correct_cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_cell_ids[i]( 82, 83, 83 );
  
  UTILITY_TEST_COMPARE_ARRAYS( cell_ids, correct_cell_ids );

  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    correct_surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_surface_ids[i]( 394, 408, 394 );

  UTILITY_TEST_COMPARE_ARRAYS( surface_ids, correct_surface_ids );

  Teuchos::Array<Utility::Trip<double,double,double> >
    correct_distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_distances.size(); ++i )
    correct_distances[i]( 1.474, 17.526, 17.526 );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( distances, correct_distances, 1e-6 );
      
  Teuchos::Array<Utility::Pair<int,int> >
    correct_reflection( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_reflection.size(); ++i )
    correct_reflection[i]( false, true );

  UTILITY_TEST_COMPARE_ARRAYS( reflection, correct_reflection );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  std::string test_dagmc_geom_file_name;

  int threads = 1;

  clp.setOption( "test_cad_file",
                 &test_dagmc_geom_file_name,
		 "Test cad file name" );

  clp.setOption( "threads",
		 &threads,
		 "Number of threads to use" );
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );
  out->setOutputToRootOnly( 0 );

  // Initialize DagMC
  Geometry::DagMC::setTerminationCellPropertyName( "graveyard" );
  Geometry::DagMC::setMaterialPropertyName( "mat" );
  Geometry::DagMC::setDensityPropertyName( "rho" );
  Geometry::DagMC::setEstimatorPropertyName( "tally" );
  
  Geometry::DagMC::initialize( test_dagmc_geom_file_name, 1e-3, false );
  Geometry::DagMC::enableThreadSupport( threads );

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );
  
  mpiSession.barrier();
  
  // Run the unit tests
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstSharedParallelDagMC.cpp
//---------------------------------------------------------------------------//
