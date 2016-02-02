//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleTracker.cpp
//! \author Eli Moll
//! \brief  Particle tracking routine definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleTracker.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleTracker::ParticleTracker( const unsigned number_of_histories )
{
  // Make sure there are some particles being tracked
  testPrecondition( number_of_histories > 0 );
  
  d_number_of_histories = number_of_histories;
}

// Add current history estimator contribution
void ParticleTracker::updateFromGlobalParticleSubtrackEndingEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  // Get the lifetime information of a newly generated particle
  if ( d_particle_reset )
  {
    // History Number
    d_history_number = particle.getHistoryNumber();
    
    // Generation Number
    d_generation_number = particle.getGenerationNumber();
    
    // Particle Type
    d_particle_type = particle.getParticleType();

    // Append the initial position data
    d_x_pos.push_back( start_point[0] );
    d_y_pos.push_back( start_point[1] );
    d_z_pos.push_back( start_point[2] );
    
    // Append the initial direction data
    d_x_dir.push_back( particle.getXDirection() );
    d_y_dir.push_back( particle.getYDirection() );
    d_z_dir.push_back( particle.getZDirection() );
    
    // Append the initial energy data
    d_energy.push_back( particle.getEnergy() );
    
    // Append the initial collision number data
    d_col_num.push_back( static_cast<double>( particle.getCollisionNumber() ) );
    
    // Append the initial weight data
    d_weight.push_back( particle.getWeight() );
    
    // Flag that we are working on an existing particle
    d_particle_reset = false;
  }
  else
  {
    // Append the new position data
    d_x_pos.push_back( start_point[0] );
    d_y_pos.push_back( start_point[1] );
    d_z_pos.push_back( start_point[2] );
    
    // Append the new direction data
    d_x_dir.push_back( particle.getXDirection() );
    d_y_dir.push_back( particle.getYDirection() );
    d_z_dir.push_back( particle.getZDirection() );
    
    // Append the new energy data
    d_energy.push_back( particle.getEnergy() );
    
    // Append the new collision number data
    d_col_num.push_back( static_cast<double>( particle.getCollisionNumber() ) );
    
    // Append the new weight data
    d_weight.push_back( particle.getWeight() );
  }

  // Check if the particle is gone and commit data if isGone == true
  if ( particle.isGone() )
  {
    // Commit particle track data
    commitParticleTrackData();
    
    // Reset particle track data
    resetParticleTrackData();
  }
}

void ParticleTracker::commitParticleTrackData()
{
  Teuchos::Array< Teuchos::Array< double > > particle_data;

  // Start by adding the arrays of data to the total particle array
  particle_data.push_back( d_x_pos );
  particle_data.push_back( d_y_pos );
  particle_data.push_back( d_z_pos );
  particle_data.push_back( d_x_dir );
  particle_data.push_back( d_y_dir );
  particle_data.push_back( d_z_dir );
  particle_data.push_back( d_energy );
  particle_data.push_back( d_col_num );
  particle_data.push_back( d_weight );
  
  // Begin the process of narrowing down where to add new data
  if ( d_history_number_map.count( d_history_number ) == 1 )
  {
  
    // If we find the history number, check if the particle type exists yet
    if ( d_history_number_map[ d_history_number ].count( d_particle_type ) == 1 )
    {
      
      // If we find the particle type, check if the generation number exists yet
      if ( d_history_number_map[ d_history_number ][ d_particle_type ].count( d_generation_number ) == 1 )
      {
      
        unsigned i = 1;
              
        // If the generation number exists, add it to the list of particles
        while ( d_history_number_map[ d_history_number ][ d_particle_type ][ d_generation_number ].count( i ) == 1 )
        {
          ++i;
        }
        
        // Assign the data
        d_history_number_map[ d_history_number ][ d_particle_type ][ d_generation_number ][ i ] =
          particle_data;
          
      }
      else
      {
      
        // Map of individual particles to array of particle data
        boost::unordered_map< unsigned, Teuchos::Array< Teuchos::Array< double > > > 
          individual_particle_map[ 1 ] = particle_data;

        // Map of generation number to individual particles
        boost::unordered_map< unsigned, boost::unordered_map< unsigned, Teuchos::Array< Teuchos::Array< double > > > >
          generation_number_map[ d_generation_number ] = individual_particle_map;
          
        d_history_number_map[ d_history_number ][ d_particle_type ][ d_generation_number ] =
          generation_number_map;
          
      } 
    }
    else
    {
      // Map of individual particles to array of particle data
      boost::unordered_map< unsigned, Teuchos::Array< Teuchos::Array< double > > > 
        individual_particle_map[ 1 ] = particle_data;

      // Map of generation number to individual particles
      boost::unordered_map< unsigned, boost::unordered_map< unsigned, Teuchos::Array< Teuchos::Array< double > > > >
        generation_number_map[ d_generation_number ] = individual_particle_map;
        
      // Map of particle type to generation number
      boost::unordered_map< ParticleType, boost::unordered_map< unsigned, boost::unordered_map< unsigned, Teuchos::Array< Teuchos::Array< double > > > > >
        particle_type_map[ d_particle_type ] = generation_number_map;
        
      d_history_number_map[ d_history_number ][ d_particle_type ] =
        particle_type_map;
    }
  
  }
  else
  {
  
    // If the history number does not yet exist, then no more checking needs to
    //   be done. We can be confident no submaps exist.
  
    // Map of individual particles to array of particle data
    boost::unordered_map< unsigned, Teuchos::Array< Teuchos::Array< double > > > 
      individual_particle_map[ 1 ] = particle_data;

    // Map of generation number to individual particles
    boost::unordered_map< unsigned, boost::unordered_map< unsigned, Teuchos::Array< Teuchos::Array< double > > > >
      generation_number_map[ d_generation_number ] = individual_particle_map;
      
    // Map of particle type to generation number
    boost::unordered_map< ParticleType, boost::unordered_map< unsigned, boost::unordered_map< unsigned, Teuchos::Array< Teuchos::Array< double > > > > >
      particle_type_map[ d_particle_type ] = generation_number_map;
  
    // Map of the history number to the particle type map
    d_history_number_map[ d_history_number ] = particle_type_map;
    
  }
}

void ParticleTracker::resetParticleTrackData()
{
  // Clear the arrays to prepare for a new particle
  d_x_pos.clear();
  d_y_pos.clear();
  d_z_pos.clear();
  d_x_dir.clear();
  d_y_dir.clear();
  d_z_dir.clear();
  d_energy.clear();
  d_col_num.clear();
  d_weight.clear();
  
  // Flag that the particle is reset and lifetime information should be found
  d_particle_reset = true;
}

void ParticleTracker::exportData( ParticleTrackerHDF5FileHandler& hdf5_file,
                 const bool process_data ) const
{
  hdf5_file.setParticleTrackerData( d_history_number_map );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleTracker.cpp
//---------------------------------------------------------------------------//
