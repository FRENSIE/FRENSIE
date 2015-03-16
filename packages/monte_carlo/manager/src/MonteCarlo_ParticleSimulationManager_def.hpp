//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManager_def.hpp
//! \author Alex Robinson
//! \brief  The particle simulation manager class definition.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_SIMULATION_MANAGER_DEF_HPP
#define FACEMC_PARTICLE_SIMULATION_MANAGER_DEF_HPP

// Boost Includes
#include <boost/bind.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_SourceModuleInterface.hpp"
#include "MonteCarlo_EstimatorModuleInterface.hpp"
#include "MonteCarlo_CollisionModuleInterface.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Geometry_ModuleInterface.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_SimulationProperties.hpp"


namespace MonteCarlo{

// Constructor for multiple threads
/*! \details If OpenMP is not being used, the number of threads requested will
 * be ignored.
 */
template<typename GeometryHandler,
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
ParticleSimulationManager<GeometryHandler,
			  SourceHandler,
			  EstimatorHandler,
			  CollisionHandler>::ParticleSimulationManager( 
				const unsigned number_of_histories,
				const unsigned start_history,
				const unsigned previously_completed_histories,
				const double previous_run_time )
  : d_start_history( start_history ),
    d_history_number_wall( start_history + number_of_histories ),
    d_histories_completed( previously_completed_histories ),
    d_end_simulation( false ),
    d_previous_run_time( previous_run_time ),
    d_start_time( 0.0 ),
    d_end_time( 0.0 )
{
  // At least one history must be simulated
  testPrecondition( number_of_histories > 0 );

  // Assign the functions based on the mode
  ParticleModeType mode = SimulationProperties::getParticleMode();
  
  switch( mode )
  {
  case NEUTRON_MODE:
  {
    d_simulate_neutron = boost::bind<void>( &ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::simulateParticle<NeutronState>,
					    boost::cref( *this ),
					    _1,
					    _2 );
    d_simulate_photon = boost::bind<void>( &ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::ignoreParticle<PhotonState>,
					    boost::cref( *this ),
					    _1,
					    _2 );
    d_simulate_electron = boost::bind<void>( &ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::ignoreParticle<ElectronState>,
					    boost::cref( *this ),
					    _1,
					    _2 );		   
    break;
  }
  case PHOTON_MODE:
  {
    d_simulate_photon = boost::bind<void>( &ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::simulateParticle<PhotonState>,
					    boost::cref( *this ),
					    _1,
					    _2 );
    d_simulate_neutron = boost::bind<void>( &ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::ignoreParticle<NeutronState>,
					    boost::cref( *this ),
					    _1,
					    _2 );
    d_simulate_electron = boost::bind<void>( &ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::ignoreParticle<ElectronState>,
					    boost::cref( *this ),
					    _1,
					    _2 );
    break;
  }
  case ELECTRON_MODE:
  {
    d_simulate_electron = boost::bind<void>( &ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::simulateParticle<ElectronState>,
					     boost::cref( *this ),
					     _1,
					     _2 );
    d_simulate_neutron = boost::bind<void>( &ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::ignoreParticle<NeutronState>,
					    boost::cref( *this ),
					    _1,
					    _2 );
    d_simulate_photon = boost::bind<void>( &ParticleSimulationManager<GeometryHandler,SourceHandler,EstimatorHandler,CollisionHandler>::ignoreParticle<PhotonState>,
					   boost::cref( *this ),
					   _1,
					   _2 );
    break;
  }
  default:
    THROW_EXCEPTION( std::runtime_error,
		     "Error: particle mode " << mode << " is not currently "
		     << "supported by the particle simulation manager." );
  }
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
  std::cout << "Starting simulation ... ";
  std::cout.flush();
  
  // Set up the random number generator for the number of threads requested
  Utility::RandomNumberGenerator::createStreams();

  // Set up the geometry module interface for the number of threads requested
  GMI::initialize();

  // Enable estimator thread support
  EMI::enableThreadSupport( 
		 Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  // Set the start time
  d_start_time = Utility::GlobalOpenMPSession::getTime();

  #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  { 
    // Create a bank for each thread
    ParticleBank bank;

    #pragma omp for
    for( unsigned history = d_start_history; history < d_history_number_wall; ++history )
    {
      // Do useful work unless the user requests an end to the simulation
      #pragma omp flush( d_end_simulation )
      if( !d_end_simulation )
      {
	// Initialize the random number generator for this history
	Utility::RandomNumberGenerator::initialize( history );
	
	// Sample a particle state from the source
	SMI::sampleParticleState( bank, history );
	
	// Determine the starting cell of the particle
	for( unsigned i = 0; i < bank.size(); ++i )
	{
	  typename GMI::InternalCellHandle start_cell;
	  
	  try{
	    start_cell = GMI::findCellContainingPoint( bank.top()->ray() );
	  }
	  CATCH_LOST_SOURCE_PARTICLE_AND_CONTINUE( bank );
	  
	  bank.top()->setCell( start_cell );
	  
	  EMI::updateEstimatorsFromParticleGenerationEvent( *bank.top() );
	}
	
	// This history only ends when the particle bank is empty
	while( bank.size() > 0 )
	{
	  switch( bank.top()->getParticleType() )
	  {
	  case NEUTRON: 
	    d_simulate_neutron( dynamic_cast<NeutronState&>( *bank.top() ),
				bank );
	    // simulateParticle( dynamic_cast<NeutronState&>( *bank.top() ), 
            //               bank );
	    break;
	  case PHOTON:
	    d_simulate_photon( dynamic_cast<PhotonState&>( *bank.top() ),
			       bank );
	    // simulateParticle( dynamic_cast<PhotonState&>( *bank.top() ),
            //               bank );
	    break;
	  case ELECTRON:
	    d_simulate_electron( dynamic_cast<ElectronState&>( *bank.top() ),
				 bank );
	    // simulateParticle( dynamic_cast<ElectronState&>( *bank.top() ),
            //               bank );
	    break;
	  default:
	    THROW_EXCEPTION( std::logic_error,
			     "Error: particle type "
			     << bank.top()->getParticleType() <<
			     " is not currently supported!" );
	  }
  
	  bank.pop();
	}
	
	// Commit all estimator history contributions
	EMI::commitEstimatorHistoryContributions();
        
	// Increment the number of histories completed
        #pragma omp atomic
	++d_histories_completed;
      }
    }
  }
    
  // Set the end time
  d_end_time = Utility::GlobalOpenMPSession::getTime();

  std::cout << "done." << std::endl;
}

// Set the number of particle histories to simulate
template<typename GeometryHandler,
         typename SourceHandler,
         typename EstimatorHandler,
         typename CollisionHandler>
template<typename ParticleStateType>
void ParticleSimulationManager<GeometryHandler,
                               SourceHandler,
                               EstimatorHandler,
                               CollisionHandler>::simulateParticle( 
                                                   ParticleStateType& particle,
						   ParticleBank& bank ) const
{
  // Particle tracking information
  double distance_to_surface_hit, op_to_surface_hit, remaining_subtrack_op;
  double subtrack_start_time;
  double ray_start_point[3];
  
  // Cache the start point of the ray
  ray_start_point[0] = particle.getXPosition();
  ray_start_point[1] = particle.getYPosition();
  ray_start_point[2] = particle.getZPosition();

  // Surface information
  typename GMI::InternalSurfaceHandle surface_hit;
  Teuchos::Array<double> surface_normal( 3 );

  // Cell information
  typename GMI::InternalCellHandle cell_entering, cell_leaving;
  double cell_total_macro_cross_section;

  // Check if the particle energy is below the cutoff
  if( particle.getEnergy() < SimulationProperties::getMinParticleEnergy<ParticleStateType>() )
    particle.setAsGone();
  
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
      if( !CMI::isCellVoid( particle.getCell(), particle.getParticleType() ) )
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

	

	EMI::updateEstimatorsFromParticleCollidingGlobalEvent(
						      particle,
						      ray_start_point,
						      particle.getPosition() );

	// Undergo a collision with the material in the cell
	CMI::collideWithCellMaterial( particle, bank, true );

	// Indicate that a collision has occurred
	GMI::newRay();

	// Cache the current position of the new ray
	ray_start_point[0] = particle.getXPosition();
	ray_start_point[1] = particle.getYPosition();
	ray_start_point[2] = particle.getZPosition();

	// Make sure the energy is above the cutoff
	if( particle.getEnergy() < SimulationProperties::getMinParticleEnergy<ParticleStateType>() )
	  particle.setAsGone();

	// This subtrack is finished
	break;
      }
    }	     
  }

  // Update the global estimators
  EMI::updateEstimatorsFromParticleCollidingGlobalEvent(
						      particle,
						      ray_start_point,
						      particle.getPosition() );

  // Indicate that this particle history is complete
  GMI::newRay();
}

// Set the number of particle histories to simulate
template<typename GeometryHandler,
         typename SourceHandler,
         typename EstimatorHandler,
         typename CollisionHandler>
template<typename ParticleStateType>
void ParticleSimulationManager<GeometryHandler,
                               SourceHandler,
                               EstimatorHandler,
                               CollisionHandler>::ignoreParticle( 
                                                   ParticleStateType& particle,
						   ParticleBank& bank ) const
{
  particle.setAsGone();
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
  os << "Previous Simulation Time (s): " << d_previous_run_time << std::endl;
  os << std::endl;
  os << "/*---------------------------------------------------------------*/";
  os << "Estimator Data" << std::endl;
  os << "/*---------------------------------------------------------------*/";
  EMI::printEstimators( os,
			d_histories_completed,
			d_start_time,
			d_end_time+d_previous_run_time );
}

// Print the data in all estimators to a parameter list
template<typename GeometryHandler,
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
void ParticleSimulationManager<GeometryHandler,
			       SourceHandler,
			       EstimatorHandler,
			       CollisionHandler>::exportSimulationData(
				      const std::string& data_file_name ) const
{
  std::cout << "Exporting simulation data ... ";
  std::cout.flush();
  
  EMI::exportEstimatorData( data_file_name,
  			    d_start_history+d_histories_completed,
  			    d_histories_completed,
  			    d_start_time,
  			    d_end_time+d_previous_run_time,
			    true );

  std::cout << "done." << std::endl;
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
  double time = Utility::GlobalOpenMPSession::getTime();
  
  #pragma omp critical( ostream_update )
  {
    #pragma omp flush( d_histories_completed )
    std::cerr << " History: " << d_histories_completed
	      << " Run Time: " << time - d_start_time
	      << std::endl;
  }
}

} // end MonteCarlo namespace

#endif // end FACEMC_PARTICLE_SIMULATION_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager_def.hpp
//---------------------------------------------------------------------------//
