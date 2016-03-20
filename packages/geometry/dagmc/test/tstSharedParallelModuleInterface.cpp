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
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Geometry_ModuleInterface_DagMC.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_Tuple.hpp"
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

      Geometry::ModuleTraits::InternalCellHandle start_cell =
        Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingStartRay(
                                                                         ray );
    
      Geometry::ModuleInterface<Geometry::DagMC>::setInternalRay( 
                                                             ray, start_cell );
    }

    // Find the cell that contains the ray
    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].first = 
      Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingInternalRay();

    // Fire the ray
    Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
    double distance_to_surface_hit = 
      Geometry::ModuleInterface<Geometry::DagMC>::fireInternalRay( surface_hit );

    surface_ids[Utility::GlobalOpenMPSession::getThreadId()].first = 
      surface_hit;

    distances[Utility::GlobalOpenMPSession::getThreadId()].first = 
      distance_to_surface_hit;

    double surface_normal[3];

    reflection[Utility::GlobalOpenMPSession::getThreadId()].first = 
      Geometry::ModuleInterface<Geometry::DagMC>::advanceInternalRayToCellBoundary( surface_normal );

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].second = 
      Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingInternalRay();

    distance_to_surface_hit = 
      Geometry::ModuleInterface<Geometry::DagMC>::fireInternalRay( surface_hit );

    surface_ids[Utility::GlobalOpenMPSession::getThreadId()].second = 
      surface_hit;

    distances[Utility::GlobalOpenMPSession::getThreadId()].second = 
      distance_to_surface_hit;
    
    // Advance the ray to the boundary surface (reflecting)
    reflection[Utility::GlobalOpenMPSession::getThreadId()].second = 
      Geometry::ModuleInterface<Geometry::DagMC>::advanceInternalRayToCellBoundary( surface_normal );

    cell_ids[Utility::GlobalOpenMPSession::getThreadId()].third = 
      Geometry::ModuleInterface<Geometry::DagMC>::findCellContainingInternalRay();

    distance_to_surface_hit = Geometry::ModuleInterface<Geometry::DagMC>::fireInternalRay( surface_hit );
    
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
  
  // Initialize DagMC
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );

  Geometry::DagMCInstanceFactory::initializeDagMC( *geom_rep );

  // Initialize the interface
  Geometry::ModuleInterface<Geometry::DagMC>::initialize();
  
  // Enable thread support with the interface
  Geometry::ModuleInterface<Geometry::DagMC>::enableThreadSupport( threads );
  
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
