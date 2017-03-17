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
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Geometry_RootNavigator.hpp"
#include "Geometry_RootModel.hpp"
#include "Geometry_RootModelPropertiesFactory.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::RootModel> model;

//---------------------------------------------------------------------------//
// Check that a parallel internal ray trace can be done
TEUCHOS_UNIT_TEST( Root, parallel_ray_trace )
{
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Trip<double,double,double> >
    distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  {
    // Create the thread navigators
    std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
    
    // Initialize the ray
    if( Utility::GlobalOpenMPSession::getThreadId()%6 == 0 )
      navigator->setInternalRay( 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 1 )
      navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 2 )
      navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 3 )
      navigator->setInternalRay( 0.0, 0.0, 0.0, -1.0, 0.0, 0.0 );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 4)
      navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, -1.0, 0.0 );
    else
      navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, -1.0 );

    Utility::get<0>(cell_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      navigator->getCellContainingInternalRay();

    // Fire a ray through the geometry
    Utility::get<0>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      navigator->fireInternalRay();

    // Advance the ray to the cell boundary
    navigator->advanceInternalRayToCellBoundary();

    Utility::get<1>(cell_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      navigator->getCellContainingInternalRay();

    // Fire a ray through the geometry
    double distance_to_boundary = navigator->fireInternalRay();
    
    Utility::get<1>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      distance_to_boundary;

    // Advance the ray a substep
    navigator->advanceInternalRayBySubstep( 0.5*distance_to_boundary );

    // Change the ray direction
    double new_direction[3];

    Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
                                     0.0,
                                     0.0,
                                     navigator->getInternalRayDirection(),
                                     new_direction );

    navigator->changeInternalRayDirection( new_direction );

    // Fire a ray through the geometry
    Utility::get<2>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      navigator->fireInternalRay();

    // Advance the ray to the cell boundary
    navigator->advanceInternalRayToCellBoundary();

    // Find the new cell
    Utility::get<2>(cell_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      navigator->getCellContainingInternalRay();
  }

  // Check that each of the rays traces were successful
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    correct_cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_cell_ids[i] = std::make_tuple( 2, 1, 3 );

  UTILITY_TEST_COMPARE_ARRAYS( cell_ids, correct_cell_ids );

  Teuchos::Array<Utility::Trip<double,double,double> >
    correct_distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_distances.size(); ++i )
    correct_distances[i] = std::make_tuple( 2.5, 2.5, 5.0 );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( distances, correct_distances, 1e-6 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string xml_file_name;
int threads = 1;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_xml_file",
                   &xml_file_name,
                   "Model properties xml file name" );

  clp().setOption( "threads",
                   &threads,
                   "Number of threads to use" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  Teuchos::RCP<const Teuchos::ParameterList> raw_model_properties =
    Teuchos::getParametersFromXmlFile( xml_file_name );

  std::shared_ptr<const Geometry::RootModelProperties> model_properties =
    Geometry::RootModelPropertiesFactory::createProperties(
                                                       *raw_model_properties );

  std::shared_ptr<Geometry::RootModel> tmp_model =
    Geometry::RootModel::getInstance();

  tmp_model->initialize( *model_properties );

  model = tmp_model;

  // Set the number of threads to use
  Utility::GlobalOpenMPSession::setNumberOfThreads( threads );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSharedParallelRoot.cpp
//---------------------------------------------------------------------------//
