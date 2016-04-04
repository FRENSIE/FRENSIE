//---------------------------------------------------------------------------//
//!
//! \file   tstSharedParallelRoot.cpp
//! \author Alex Robinson
//! \brief  Root wrapper class shared parallel unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>
#include <map>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Geometry_Root.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Check that a parallel external ray trace can be done
TEUCHOS_UNIT_TEST( Root, parallel_external_ray_trace )
{
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  {
    std::shared_ptr<Geometry::Ray> ray;
    // Initialize the ray
    if( Utility::GlobalOpenMPSession::getThreadId()%6 == 0 )
      ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 ) );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 1 )
      ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 ) );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 2 )
      ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 3 )
      ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, -1.0, 0.0, 0.0 ) );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 4)
      ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, -1.0, 0.0 ) );
    else
      ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, -1.0 ) );

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].first = 
      Geometry::Root::findCellContainingExternalRay( *ray );
    
    // Fire a ray through the geometry
    double distance_to_boundary = Geometry::Root::fireExternalRay( *ray );
 
    ray->advanceHead( distance_to_boundary );
  
    // Find the new cell
    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].second = 
      Geometry::Root::findCellContainingExternalRay( *ray );
  
    // Fire a ray through the geometry
    distance_to_boundary = Geometry::Root::fireExternalRay( *ray );

    ray->advanceHead( distance_to_boundary );
  
    // Find the new cell
    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].third =
      Geometry::Root::findCellContainingExternalRay( *ray );
  }

  // Check that each of the rays traces were successful
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    correct_cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_cell_ids[i]( 2, 1, 3 );
  
  UTILITY_TEST_COMPARE_ARRAYS( cell_ids, correct_cell_ids );
}

//---------------------------------------------------------------------------//
// Check that a parallel internal ray trace can be done
TEUCHOS_UNIT_TEST( Root, parallel_internal_ray_trace )
{
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Trip<double,double,double> >
    distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  {
    { 
      std::shared_ptr<Geometry::Ray> ray;
      // Initialize the ray
      if( Utility::GlobalOpenMPSession::getThreadId()%6 == 0 )
        ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 ) );
      else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 1 )
        ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 ) );
      else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 2 )
        ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );
      else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 3 )
        ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, -1.0, 0.0, 0.0 ) );
      else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 4)
        ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, -1.0, 0.0 ) );
      else
        ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, -1.0 ) );

      Geometry::Root::setInternalRay( *ray );
    }

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].first = 
      Geometry::Root::findCellContainingInternalRay();

    // Fire a ray through the geometry
    double distance_to_boundary = Geometry::Root::fireInternalRay();

    distances[Utility::GlobalOpenMPSession::getThreadId()].first = 
      distance_to_boundary;
 
    // Advance the ray to the cell boundary
    Geometry::Root::advanceInternalRayToCellBoundary();
    
    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].second = 
      Geometry::Root::findCellContainingInternalRay();

    // Fire a ray through the geometry
    distance_to_boundary = Geometry::Root::fireInternalRay();

    distances[Utility::GlobalOpenMPSession::getThreadId()].second = 
      distance_to_boundary;

    // Advance the ray a substep
    Geometry::Root::advanceInternalRayBySubstep( 0.5*distance_to_boundary );

    // Change the ray direction
    double new_direction[3];

    Utility::rotateDirectionThroughPolarAndAzimuthalAngle( 
                                     0.0, 
                                     0.0,
                                     Geometry::Root::getInternalRayDirection(),
                                     new_direction );

    Geometry::Root::changeInternalRayDirection( new_direction );

    // Fire a ray through the geometry
    distance_to_boundary = Geometry::Root::fireInternalRay();

    distances[Utility::GlobalOpenMPSession::getThreadId()].third = 
      distance_to_boundary;
  
    // Advance the ray to the cell boundary
    Geometry::Root::advanceInternalRayToCellBoundary();

    // Find the new cell
    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].third =
      Geometry::Root::findCellContainingInternalRay();
  } 

  // Check that each of the rays traces were successful
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    correct_cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_cell_ids[i]( 2, 1, 3 );
  
  UTILITY_TEST_COMPARE_ARRAYS( cell_ids, correct_cell_ids );

  Teuchos::Array<Utility::Trip<double,double,double> >
    correct_distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_distances.size(); ++i )
    correct_distances[i]( 2.5, 2.5, 5.0 );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( distances, correct_distances, 1e-6 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  std::string test_root_geom_file_name;

  int threads = 1;

  clp.setOption( "test_root_file",
		 &test_root_geom_file_name,
		 "Test root geometry file name" );

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

  // Initialize root
  Geometry::Root::initialize( test_root_geom_file_name );
  Geometry::Root::enableThreadSupport( threads );

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
// end tstSharedParallelRoot.cpp
//---------------------------------------------------------------------------//
