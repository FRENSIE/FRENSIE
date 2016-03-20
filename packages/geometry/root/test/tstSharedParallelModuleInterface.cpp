//---------------------------------------------------------------------------//
//!
//! \file   tstSharedParallelModuleInterface.cpp
//! \author Alex Robinson
//! \brief  Geometry module interface shared parallel unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

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
#include "Geometry_RootInstanceFactory.hpp"
#include "Geometry_ModuleInterface_Root.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a parallel ray trace can be done
TEUCHOS_UNIT_TEST( ModuleInterface, parallel_ray_trace )
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

      Geometry::ModuleTraits::InternalCellHandle start_cell =
        Geometry::ModuleInterface<Geometry::Root>::findCellContainingStartRay(
                                                                        *ray );

      Geometry::ModuleInterface<Geometry::Root>::setInternalRay( 
                                                            *ray, start_cell );
    }

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].first = 
      Geometry::ModuleInterface<Geometry::Root>::findCellContainingInternalRay();

    // Fire a ray through the geometry
    Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
    
    double distance_to_boundary = 
      Geometry::ModuleInterface<Geometry::Root>::fireInternalRay( surface_hit );

    distances[Utility::GlobalOpenMPSession::getThreadId()].first = 
      distance_to_boundary;
 
    // Advance the ray to the cell boundary
    double surface_normal[3];
    
    bool reflection = Geometry::ModuleInterface<Geometry::Root>::advanceInternalRayToCellBoundary( surface_normal );
    
    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].second = 
      Geometry::Root::findCellContainingInternalRay();

    // Fire a ray through the geometry
    distance_to_boundary = 
      Geometry::ModuleInterface<Geometry::Root>::fireInternalRay( surface_hit );

    distances[Utility::GlobalOpenMPSession::getThreadId()].second = 
      distance_to_boundary;

    // Advance the ray a substep
    Geometry::ModuleInterface<Geometry::Root>::advanceInternalRayBySubstep( 0.5*distance_to_boundary );

    // Change the ray direction
    double new_direction[3];

    Utility::rotateDirectionThroughPolarAndAzimuthalAngle( 
          0.0, 
          0.0,
          Geometry::ModuleInterface<Geometry::Root>::getInternalRayDirection(),
          new_direction );

    Geometry::ModuleInterface<Geometry::Root>::changeInternalRayDirection(
                                                               new_direction );

    // Fire a ray through the geometry
    distance_to_boundary = Geometry::ModuleInterface<Geometry::Root>::fireInternalRay( surface_hit );

    distances[Utility::GlobalOpenMPSession::getThreadId()].third = 
      distance_to_boundary;
  
    // Advance the ray to the cell boundary
    reflection = Geometry::ModuleInterface<Geometry::Root>::advanceInternalRayToCellBoundary( surface_normal );

    // Find the new cell
    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].third =
      Geometry::ModuleInterface<Geometry::Root>::findCellContainingInternalRay();
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

  std::string test_geom_xml_file_name;

  int threads = 1;

  clp.setOption( "test_xml_file",
		 &test_geom_xml_file_name,
		 "Test xml geometry file name" );

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

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );

  // Initialize Root
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );
  
  Geometry::RootInstanceFactory::initializeRoot( *geom_rep );

  // Initialize the interface
  Geometry::ModuleInterface<Geometry::Root>::initialize();
  
  // Enable thread support with the interface
  Geometry::ModuleInterface<Geometry::Root>::enableThreadSupport( threads );
  
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
// end tstSharedParallelModuleInterface.cpp
//---------------------------------------------------------------------------//
