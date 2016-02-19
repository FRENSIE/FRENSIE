//---------------------------------------------------------------------------//
//!
//! \file   tstObserverRegistrationHelpers.cpp
//! \author Alex Robinson
//! \brief  Observer registration helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_ObserverRegistrationHelpers.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator_1;

std::shared_ptr<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_2;

std::shared_ptr<MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator_3;

std::shared_ptr<MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_4;

std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> >
estimator_5;

std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_6;

std::shared_ptr<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator_7;

std::shared_ptr<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_8;

std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> >
estimator_9;

std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
estimator_10;

Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> cell_ids( 2 );

Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> surface_ids(2);

std::shared_ptr<MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> >
tet_mesh_estimator;

std::string test_input_mesh_file_name;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize a cell estimator
template<typename CellEstimator>
void initializeCellEstimator( 
    const unsigned estimator_id,
    const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids,
    std::shared_ptr<CellEstimator>& estimator )
{  
  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  Teuchos::Array<double> cell_volumes( cell_ids.size(), 1.0 );
  
  estimator.reset( new CellEstimator( estimator_id,
				      estimator_multiplier,
				      cell_ids,
				      cell_volumes ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
  
  estimator->setParticleTypes( particle_types );
}

// Initialize a cell pulse height estimator
template<typename CellPulseHeightEstimator>
void initializeCellPulseHeightEstimator(
    const unsigned estimator_id,
    const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cell_ids,
    std::shared_ptr<CellPulseHeightEstimator>& estimator )
{  
  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new CellPulseHeightEstimator( estimator_id,
						 estimator_multiplier,
						 cell_ids ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
  
  estimator->setParticleTypes( particle_types );
}

// Initialize a surface estimator
template<typename SurfaceEstimator>
void initializeSurfaceFluxEstimator( 
	   const unsigned estimator_id,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   surface_ids,
	   std::shared_ptr<SurfaceEstimator>& estimator )
{
  Teuchos::Array<double> surface_areas( surface_ids.size(), 1.0 );

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new SurfaceEstimator( estimator_id,
					 estimator_multiplier,
					 surface_ids,
					 surface_areas ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;

  estimator->setParticleTypes( particle_types );
}

// Initialize a surface estimator
template<typename SurfaceEstimator>
void initializeSurfaceCurrentEstimator( 
	   const unsigned estimator_id,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   surface_ids,
	   std::shared_ptr<SurfaceEstimator>& estimator )
{
  Teuchos::Array<double> surface_areas( surface_ids.size(), 1.0 );

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new SurfaceEstimator( estimator_id,
					 estimator_multiplier,
					 surface_ids ) );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;

  estimator->setParticleTypes( particle_types );
}

// Initialize the estimator
void initializeTetMeshEstimator( const unsigned estimator_id )
{

  tet_mesh_estimator.reset(
  new MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(
                         estimator_id,
                         1.0,
                         test_input_mesh_file_name,
                         "unit_cube_output.vtk" ) );
    
  // Assign energy bins
  Teuchos::Array<double> energy_bin_boundaries( 2 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1.0;
    
  tet_mesh_estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
                             energy_bin_boundaries );     
                             
  // Set the particle types
  Teuchos::Array<MonteCarlo::ParticleType> particle_types ( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
    
  tet_mesh_estimator->setParticleTypes( particle_types );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the estimators can be registered with the correct dispatchers
TEUCHOS_UNIT_TEST( ObserverRegistrationHelpers, register_macro )
{
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_1, cell_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_2, cell_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_3, cell_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_4, cell_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_5, cell_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_6, cell_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_7, surface_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_8, surface_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_9, surface_ids );
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator_10, surface_ids );
  REGISTER_GLOBAL_OBSERVER_WITH_DISPATCHERS( tet_mesh_estimator );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 0 ).getNumberOfObservers(), 4 );

  TEST_EQUALITY_CONST( MonteCarlo::ParticleCollidingInCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleSubtrackEndingInCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleEnteringCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleLeavingCellEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleCrossingSurfaceEventDispatcherDB::getDispatcher( 1 ).getNumberOfObservers(), 4 );
  
  TEST_EQUALITY_CONST( MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::getNumberOfObservers(), 1 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_input_mesh_file_name",
		 &test_input_mesh_file_name,
		 "Test input mesh file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize all estimators
  initializeCellEstimator( 0u, cell_ids, estimator_1 );
  initializeCellEstimator( 1u, cell_ids, estimator_2 );
  initializeCellEstimator( 2u, cell_ids, estimator_3 );
  initializeCellEstimator( 3u, cell_ids, estimator_4 );
  initializeCellPulseHeightEstimator( 4u, cell_ids, estimator_5 );
  initializeCellPulseHeightEstimator( 5u, cell_ids, estimator_6 );
  
  initializeSurfaceFluxEstimator( 6u, surface_ids, estimator_7 );
  initializeSurfaceFluxEstimator( 7u, surface_ids, estimator_8 );
  initializeSurfaceCurrentEstimator( 8u, surface_ids, estimator_9 );
  initializeSurfaceCurrentEstimator( 9u, surface_ids, estimator_10 );
  
  cell_ids[0] = 0;
  cell_ids[1] = 1;

  surface_ids[0] = 0;
  surface_ids[1] = 1;
  
  initializeTetMeshEstimator( 10u );
  
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstObserverRegistrationHelpers.cpp
//---------------------------------------------------------------------------//
