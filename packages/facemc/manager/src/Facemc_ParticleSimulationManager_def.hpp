//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleSimulationManager_def.hpp
//! \author Alex Robinson
//! \brief  The particle simulation manager class definition.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_SIMULATION_MANAGER_DEF_HPP
#define FACEMC_PARTICLE_SIMULATION_MANAGER_DEF_HPP

// Std Lib Includes
#include <time.h>

// FRENSIE Includes
#include "Facemc_ParticleBank.hpp"
#include "Facemc_SourceModuleInterface.hpp"
#include "Facemc_EstimatorModuleInterface.hpp"
#include "Facemc_CollisionModuleInterface.hpp"
#include "Geometry_ModuleInterface.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
template<typename GeometryHandler,
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
ParticleSimulationManager<GeometryHandler,
			  SourceHandler,
			  EstimatorHandler,
			  CollisionHandler>::ParticleSimulationManager( 
					   const unsigned number_of_histories )
  : d_history_number_wall( number_of_histories ),
    d_histories_completed( 0u ),
    d_end_simulation( false )			      
{
  // At least one history must be simulated
  testPrecondition( number_of_histories > 0 );
}

// Run the simulation set up by the user
template<typename GeometryHandler,
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void ParticleSimulationManager<GeometryHandler,
			       SourceHandler,
			       EstimatorHandler,
			       CollisionHandler>::runSimulation()
{
  // Set the start time
  d_start_time = clock()/((double)CLOCKS_PER_SEC);

  for( unsigned history = 0; history < d_history_number_wall; ++history )
  {
    // Initialize the random number generator for this history
    Utility::RandomNumberGenerator::initialize( history );
    
    // Sample a particle state from the source
    SMI::sampleParticleState( d_bank );

    // Determine the starting cell of the particle
    for( unsigned i = 0; i < d_bank.size(); ++i )
    {
      typename GMI::InternalCellHandle start_cell;
      
      try{
	start_cell = GMI::findCellContainingPoint( d_bank.top()->ray() );
      }
      CATCH_LOST_SOURCE_PARTICLE_AND_CONTINUE( d_bank );

      d_bank.top()->setCell( start_cell );
    
      EMI::updateEstimatorsFromParticleGenerationEvent( *d_bank.top() );
    }
    
    // This history only ends when the particle bank is empty
    while( d_bank.size() > 0 )
    {
      simulateParticle( *d_bank.top(), d_bank );

      d_bank.pop();
    }

    // Commit all estimator history contributions
    EMI::commitEstimatorHistoryContributions();

    // Increment the number of histories completed
    ++d_histories_completed;

    // Check for user requested end of simulation
    if( d_end_simulation )
      break;
  }

  // Set the end time
  d_end_time = clock()/((double)CLOCKS_PER_SEC);
}

// Set the number of particle histories to simulate
template<typename GeometryHandler,
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void ParticleSimulationManager<GeometryHandler,
			       SourceHandler,
			       EstimatorHandler,
			       CollisionHandler>::simulateParticle( 
				                       ParticleState& particle,
				                       ParticleBank& bank )
{
  // Particle tracking information
  double distance_to_surface_hit, op_to_surface_hit, remaining_subtrack_op;
  double subtrack_start_time;

  // Surface information
  typename GMI::InternalSurfaceHandle surface_hit;
  Teuchos::Array<double> surface_normal( 3 );

  // Cell information
  typename GMI::InternalCellHandle cell_entering, cell_leaving;
  double cell_total_macro_cross_section;
  
  while( !particle.isLost() && !particle.isGone() )
  {
    // Sample the mfp traveled by the particle on this subtrack
    remaining_subtrack_op = CMI::sampleOpticalPathLength();
    
    // Ray trace until the necessary number of optical paths have be traveled
    while( true )
    {
      // Fire a ray at the cell currently containing the particle
      try{
	distance_to_surface_hit = 0.0;
	
	GMI::fireRay( particle.ray(),
		      particle.getCell(),
		      surface_hit,
		      distance_to_surface_hit );
      }
      CATCH_LOST_PARTICLE_AND_BREAK( particle );

      // Get the total cross section for the cell
      if( !CMI::isCellVoid( particle.getCell() ) )
      {
	cell_total_macro_cross_section = 
	  CMI::getMacroscopicTotalCrossSection( particle );
      }
      else
	cell_total_macro_cross_section = 0.0;

      // Convert the distance to the surface to optical path
      op_to_surface_hit = 
	distance_to_surface_hit*cell_total_macro_cross_section;

      // Get the start time of this subtrack
      subtrack_start_time = particle.getTime();

      if( op_to_surface_hit < remaining_subtrack_op )
      {
	// Advance the particle to the cell boundary
	particle.advance( distance_to_surface_hit );

	// Get the surface normal at the intersection point
	GMI::getSurfaceNormal( surface_hit,
			       particle.getPosition(),
			       surface_normal.getRawPtr() );		       

	cell_leaving = particle.getCell();
	
	// Find the cell on the other side of the surface hit
	try{
	  cell_entering = GMI::findCellContainingPoint( particle.ray(),
							cell_leaving,
							surface_hit );
	}
	CATCH_LOST_PARTICLE_AND_BREAK( particle );

	particle.setCell( cell_entering );

	// Update estimators
	EMI::updateEstimatorsFromParticleCrossingSurfaceEvent(
						  particle,
						  cell_entering,
						  cell_leaving,
						  surface_hit,
						  distance_to_surface_hit,
						  subtrack_start_time,
						  surface_normal.getRawPtr() );

	// Check if a termination cell was encountered
	if( GMI::isTerminationCell( particle.getCell() ) )
	{
	  particle.setAsGone();

	  break;
	}

	// Update the remaining subtrack mfp
	remaining_subtrack_op -= op_to_surface_hit;
      } 
      
      // A collision occurs in this cell
      else
      {
	// Advance the particle to the collision site
	double distance = remaining_subtrack_op/cell_total_macro_cross_section;
	
	particle.advance( distance );
	
	// Update estimators
	EMI::updateEstimatorsFromParticleCollidingInCellEvent(
					  particle,
					  distance,
					  subtrack_start_time,
					  1.0/cell_total_macro_cross_section );

	// Undergo a collision with the material in the cell
	CMI::collideWithCellMaterial( particle, bank, true );

	// Indicate that a collision has occurred
	GMI::newRay();

	// Make sure the energy is above the cutoff
	if( particle.getEnergy() < 1e-11 )
	  particle.setAsGone();

	// This subtrack is finished
	break;
      }
    }	     
  } 
}

// Print the data in all estimators to the desired stream
template<typename GeometryHandler,
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void ParticleSimulationManager<GeometryHandler,
			       SourceHandler,
			       EstimatorHandler,
			       CollisionHandler>::printSimulationSummary( 
						       std::ostream &os ) const
{
  os << "!!!Particle Simulation Finished!!!" << std::endl;
  os << "Number of histories completed: " << d_histories_completed <<std::endl;
  os << "Simulation Time (s): " << d_end_time - d_start_time << std::endl;
  os << std::endl;
  os << "/*---------------------------------------------------------------*/";
  os << "Estimator Data" << std::endl;
  os << "/*---------------------------------------------------------------*/";
  EMI::printEstimators( os,
			d_histories_completed,
			d_start_time,
			d_end_time );
}

// Signal handler
template<typename GeometryHandler,
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void ParticleSimulationManager<GeometryHandler,
			       SourceHandler,
			       EstimatorHandler,
			       CollisionHandler>::signalHandler(int signal)
{
  // Record the current time
  double time = 0.0;
  
  // Ask the user what to do
  std::cerr << " Status (s), End (e), Kill (k)" << std::endl;
  std::string option;
  std::cin >> option;
  
  if( option.compare( "s" ) == 0 )
  {
    printSimulationStateInfo();
  }
  else if( option.compare( "e" ) == 0 )
  {
    d_end_simulation = true;
  }
  else if( option.compare( "k" ) == 0 )
  {
    exit(0);
  }
}

// Print simulation state info in collision handler
template<typename GeometryHandler,
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void ParticleSimulationManager<GeometryHandler,
			       SourceHandler,
			       EstimatorHandler,
			       CollisionHandler>::printSimulationStateInfo()
{
  double time = clock()/((double)(CLOCKS_PER_SEC));
  
  if( d_bank.size() > 0 )
  {
      std::cerr << " History: " << d_bank.top()->getHistoryNumber()
		<< " Collision: " << d_bank.top()->getCollisionNumber()
		<< " Run Time: " << time - d_start_time
		<< std::endl;
  }
  else
  {
    std::cerr << " History: " << d_histories_completed
		<< " Collision: " << 0
		<< " Run Time: " << time - d_start_time
		<< std::endl;
  }
}

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_SIMULATION_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleSimulationManager_def.hpp
//---------------------------------------------------------------------------//
