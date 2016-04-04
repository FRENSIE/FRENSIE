//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleTracker.cpp
//! \author Eli Moll
//! \brief  Particle tracking routine definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleTracker.hpp"
#include "MonteCarlo_ParticleType.hpp"
#include "Utility_CommHelpers.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleTracker::ParticleTracker( const ParticleHistoryObserver::idType id,
                                  const unsigned number_of_histories )
  : ParticleHistoryObserver( id ),
    d_particle_reset(),
    d_number_of_histories( number_of_histories ),
    d_x_pos(),
    d_y_pos(),
    d_z_pos(),
    d_x_dir(),
    d_y_dir(),
    d_z_dir(),
    d_energy(),
    d_col_num(),
    d_weight(),
    d_history_number(),
    d_generation_number(),
    d_particle_type(),
    d_history_number_map(),
    d_first_particle()
{
  // Make sure there are some particles being tracked
  testPrecondition( d_number_of_histories >= 0 );
  
  // Initialize the data maps
  this->initialize( 0u );
}

// Initialize the data maps
void ParticleTracker::initialize( unsigned thread )
{
  d_particle_reset.insert( std::pair<unsigned,bool>(thread, true) );
  d_x_pos.insert( std::pair<unsigned, std::vector<double> >(thread, 
                                                    std::vector<double>() ) );
  d_y_pos.insert( std::pair<unsigned, std::vector<double> >(thread, 
                                                    std::vector<double>() ) );
  d_z_pos.insert( std::pair<unsigned, std::vector<double> >(thread, 
                                                    std::vector<double>() ) );
  d_x_dir.insert( std::pair<unsigned, std::vector<double> >(thread, 
                                                    std::vector<double>() ) );
  d_y_dir.insert( std::pair<unsigned, std::vector<double> >(thread, 
                                                    std::vector<double>() ) );
  d_z_dir.insert( std::pair<unsigned, std::vector<double> >(thread, 
                                                    std::vector<double>() ) );
  d_energy.insert( std::pair<unsigned, std::vector<double> >(thread, 
                                                    std::vector<double>() ) );
  d_col_num.insert( std::pair<unsigned, std::vector<double> >(thread, 
                                                    std::vector<double>() ) );
  d_weight.insert( std::pair<unsigned, std::vector<double> >(thread, 
                                                    std::vector<double>() ) );
  d_history_number.insert( std::pair<unsigned, unsigned>(thread, 0u) );
  d_generation_number.insert( std::pair<unsigned, unsigned>(thread, 0u) );
  d_particle_type.insert( std::pair<unsigned, unsigned>(thread, 0u) );
  
  d_first_particle = true;
}

// Add current history estimator contribution
void ParticleTracker::updateFromGlobalParticleSubtrackEndingEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  
  // Check if we still need to be tracking particles
  if ( particle.getHistoryNumber() <= d_number_of_histories )
  {
    // Get the lifetime information of a newly generated particle
    if ( d_particle_reset[thread_id] )
    {
      // History Number
      d_history_number[thread_id] = particle.getHistoryNumber();
      
      // Generation Number
      d_generation_number[thread_id] = particle.getGenerationNumber();
      
      // Particle Type
      d_particle_type[thread_id] = particle.getParticleType();
      
      // Flag that we are working on an existing particle
      d_particle_reset[thread_id] = false;
    }

    // Append the initial position data
    d_x_pos[thread_id].push_back( start_point[0] );
    d_y_pos[thread_id].push_back( start_point[1] );
    d_z_pos[thread_id].push_back( start_point[2] );
    
    // Append the initial direction data
    d_x_dir[thread_id].push_back( particle.getXDirection() );
    d_y_dir[thread_id].push_back( particle.getYDirection() );
    d_z_dir[thread_id].push_back( particle.getZDirection() );
    
    // Append the initial energy data
    d_energy[thread_id].push_back( particle.getEnergy() );
    
    // Append the initial collision number data
    d_col_num[thread_id].push_back( static_cast< double >( particle.getCollisionNumber() ) );
    
    // Append the initial weight data
    d_weight[thread_id].push_back( particle.getWeight() );

    // Check if the particle is gone and commit data if isGone == true
    if ( particle.isGone() )
    {
      // Commit particle track data
      commitParticleTrackData();
      
      // Reset particle track data
      resetParticleTrackData();
    }
  }
  
  // Test that there is a valid history/generation number
  testPostcondition( d_history_number[thread_id] >= 0 );
  testPostcondition( d_generation_number[thread_id] >= 0 );
}

void ParticleTracker::commitParticleTrackData()
{
  #pragma omp critical
  {
    unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
    
    ParticleTrackerHDF5FileHandler::ParticleDataTwoDArray particle_data;

    // Start by adding the arrays of data to the total particle array
    particle_data.push_back( d_x_pos[thread_id] );
    particle_data.push_back( d_y_pos[thread_id] );
    particle_data.push_back( d_z_pos[thread_id] );
    particle_data.push_back( d_x_dir[thread_id] );
    particle_data.push_back( d_y_dir[thread_id] );
    particle_data.push_back( d_z_dir[thread_id] );
    particle_data.push_back( d_energy[thread_id] );
    particle_data.push_back( d_col_num[thread_id] );
    particle_data.push_back( d_weight[thread_id] );
    
    unsigned history_number = d_history_number[thread_id];
    unsigned particle_type = d_particle_type[thread_id];
    unsigned generation_number = d_generation_number[thread_id];
    
    // Begin the process of narrowing down where to add new data
    if ( d_first_particle )
    {
      // If this is the first particle, initialize the history map

      // Map of individual particles to array of particle data
      ParticleTrackerHDF5FileHandler::IndividualParticleSubmap individual_particle_map;
      individual_particle_map[ 0u ] = particle_data;

      // Map of generation number to individual particles
      ParticleTrackerHDF5FileHandler::GenerationNumberSubmap generation_number_map;
      generation_number_map[ generation_number ] = individual_particle_map;
        
      // Map of particle type to generation number
      ParticleTrackerHDF5FileHandler::ParticleTypeSubmap particle_type_map;
      particle_type_map[ particle_type ] = generation_number_map;
      
      // Map of the history number to the particle type map
      d_history_number_map[ history_number ] = particle_type_map;
      
      d_first_particle = false;
    }
    else if ( d_history_number_map.find( history_number ) != d_history_number_map.end()  )
    {
      // If we find the history number, check if the particle type exists yet
      if ( d_history_number_map[ history_number ].count( particle_type ) )
      {

        // If we find the particle type, check if the generation number exists yet
        if ( d_history_number_map[ history_number ][ particle_type ].count( generation_number ) )
        {
          unsigned i = 0u;
                
          // If the generation number exists, add it to the list of particles
          while ( d_history_number_map[ history_number ][ particle_type ][ generation_number ].count( i ) )
          {
            ++i;
          }
          
          // Assign the data
          d_history_number_map[ history_number ][ particle_type ][ generation_number ][ i ] =
            particle_data;  
        }
        else
        {
          // Map of individual particles to array of particle data
          ParticleTrackerHDF5FileHandler::IndividualParticleSubmap individual_particle_map;
          individual_particle_map[ 0u ] = particle_data;
            
          d_history_number_map[ history_number ][ particle_type ][ generation_number ] =
            individual_particle_map;
        } 
      }
      else
      {
        // Map of individual particles to array of particle data
        ParticleTrackerHDF5FileHandler::IndividualParticleSubmap individual_particle_map;
        individual_particle_map[ 0u ] = particle_data;

        // Map of generation number to individual particles
        ParticleTrackerHDF5FileHandler::GenerationNumberSubmap generation_number_map;
        generation_number_map[ generation_number ] = individual_particle_map;
          
        d_history_number_map[ history_number ][ particle_type ] =
          generation_number_map;
      }
    }
    else
    {
      // If the history number does not yet exist, then no more checking needs to
      //   be done. We can be confident no submaps exist.

      // Map of individual particles to array of particle data
      ParticleTrackerHDF5FileHandler::IndividualParticleSubmap individual_particle_map;
      individual_particle_map[ 0u ] = particle_data;

      // Map of generation number to individual particles
      ParticleTrackerHDF5FileHandler::GenerationNumberSubmap generation_number_map;
      generation_number_map[ generation_number ] = individual_particle_map;
        
      // Map of particle type to generation number
      ParticleTrackerHDF5FileHandler::ParticleTypeSubmap particle_type_map;
      particle_type_map[ particle_type ] = generation_number_map;
    
      // Map of the history number to the particle type map
      d_history_number_map[ history_number ] = particle_type_map;
    }
  }
}

void ParticleTracker::resetParticleTrackData()
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();

  // Clear the arrays to prepare for a new particle
  d_x_pos[thread_id].clear();
  d_y_pos[thread_id].clear();
  d_z_pos[thread_id].clear();
  d_x_dir[thread_id].clear();
  d_y_dir[thread_id].clear();
  d_z_dir[thread_id].clear();
  d_energy[thread_id].clear();
  d_col_num[thread_id].clear();
  d_weight[thread_id].clear();
  
  // Clear the particle lifetime data
  d_history_number[thread_id] = 0u;
  d_generation_number[thread_id] = 0u;
  
  // Flag that the particle is reset and lifetime information should be found
  d_particle_reset[thread_id] = true;
}

void ParticleTracker::exportData(  const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                                   const bool process_data ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  ParticleTrackerHDF5FileHandler ptrac_hdf5_file( hdf5_file );
  
  ptrac_hdf5_file.setParticleTrackerData( d_history_number_map );
}

void ParticleTracker::enableThreadSupport( const unsigned num_threads )
{
  for( unsigned i = 1u; i < num_threads; ++i )
  {
    this->initialize( i );
  }
}

// Get the x position data
void ParticleTracker::getXPositionData( std::vector< double >& array )
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  array = d_x_pos[thread_id];
}

// Get the y position data
void ParticleTracker::getYPositionData( std::vector< double >& array )
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  array = d_y_pos[thread_id];
}

// Get the z position data
void ParticleTracker::getZPositionData( std::vector< double >& array )
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  array = d_z_pos[thread_id];
}

// Get the x direction data
void ParticleTracker::getXDirectionData( std::vector< double >& array )
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  array = d_x_dir[thread_id];
}

// Get the y direction data
void ParticleTracker::getYDirectionData( std::vector< double >& array )
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  array = d_y_dir[thread_id];
}

// Get the z direction data
void ParticleTracker::getZDirectionData( std::vector< double >& array )
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  array = d_z_dir[thread_id];
}

// Get the energy data
void ParticleTracker::getEnergyData( std::vector< double >& array )
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  array = d_energy[thread_id];
}

// Get the collision number data
void ParticleTracker::getCollisionNumberData( std::vector< double >& array )
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  array = d_col_num[thread_id];
}

// Get the weight data
void ParticleTracker::getWeightData( std::vector< double >& array )
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  array = d_weight[thread_id];
}

// Get the data map
void ParticleTracker::getDataMap( 
                ParticleTrackerHDF5FileHandler::OverallHistoryMap& history_map )
{
  history_map = d_history_number_map;
}

// Check if particle is reset 
bool ParticleTracker::isParticleReset()
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  return d_particle_reset[thread_id];
}

// Reset data
void ParticleTracker::resetData()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  ParticleTracker::resetParticleTrackData();
  
  d_history_number_map.clear();
}

// Has Uncommited History Contribution
bool ParticleTracker::hasUncommittedHistoryContribution() const
{ 
  return false;
}

// Commit History Contribution
void ParticleTracker::commitHistoryContribution()
{ /*...*/ }

// Serialize and pack into string
std::string ParticleTracker::packDataInString()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  // Serialize the history number map
  std::ostringstream output_stream("ptrack_data_map");
  boost::archive::binary_oarchive output_archive(output_stream);
  output_archive << d_history_number_map;
    
  return output_stream.str();
}

// Unpack the data from a string and store into a container
void ParticleTracker::unpackDataFromString( 
              std::string& packed_string,
              ParticleTrackerHDF5FileHandler::OverallHistoryMap& history_map )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  std::istringstream input_stream( packed_string );
  boost::archive::binary_iarchive input_archive( input_stream );
  input_archive >> history_map;
}

// Reduce data
void ParticleTracker::reduceData( 
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure the comm is valid
  testPrecondition( !comm.is_null() );
  // Make sure the root process is valid
  testPrecondition( root_process < comm->getSize() );

  // Only do the reduction if there is more than one process
  if( comm->getSize() > 1 )
  {
    // Handle the master
    if( comm->getRank() == root_process )
    {
      // Start at one since the root process does not need to report
      int nodes_reporting = 1; 
      
      while( nodes_reporting < comm->getSize() )
      {
        Teuchos::RCP<Teuchos::CommStatus<unsigned long long> > status;
        
        // Probe for incoming sends to determine message size
        try{
          Utility::probe( *comm, status );
        }
        EXCEPTION_CATCH_RETHROW( std::runtime_error,
                                 "Error: Root process (" << root_process <<
                                 " was unable to probe for particle tracker "
                                 "data sent by non-root processes!" );
        
        // Get the size of the incoming message
        std::string packaged_data;
        
        try{
          int message_size = Utility::getMessageSize<char>( *status );
          
          packaged_data.resize( message_size );
        }
        EXCEPTION_CATCH_RETHROW( std::runtime_error,
                                 "Error: Root process (" << root_process <<
                                 " was unable to determine the size of the "
                                 "particle tracker data sent from process "
                                 << status->getSourceRank() << "!" );
        
        // Get the message
        try{
          Teuchos::receive( *comm,
                            status->getSourceRank(),
                            (unsigned long long)packaged_data.size(),
                            &packaged_data[0] );
        }
        EXCEPTION_CATCH_RETHROW( std::runtime_error,
                                 "Error: Root process (" << root_process <<
                                 " was unable to receive particle tracker data"
                                 " from process "
                                 << status->getSourceRank() << "!" );
              
        // Contribute the data from this worker to the node map.       
        this->contributeDataFromWorkers( packaged_data );
        
        ++nodes_reporting;
      }
    }
    else // Handle the workers
    {
      std::string packaged_data = this->packDataInString();
      
      try{
        Teuchos::send( *comm,
                       (unsigned long long)packaged_data.size(),
                       &packaged_data[0],
                       root_process );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Error: Process " << comm->getRank() <<
                               " was unable to send particle tracker data "
                               "to the root process ("
                               << root_process << "!" );
      
      // Reset the non-root process data
      this->resetData();
    }
  }

  comm->barrier();
}

// Print a summary of the data
void ParticleTracker::printSummary( std::ostream& os ) const
{ 
  os << "Particle tracker " << this->getId() << ": " << std::endl
     << "\t Histories tracked: " << d_number_of_histories << std::endl;
}

void ParticleTracker::contributeDataFromWorkers( std::string packaged_data )
{
  ParticleTrackerHDF5FileHandler::OverallHistoryMap worker_history_map;
  
  unpackDataFromString( packaged_data, worker_history_map );
  
  ParticleTrackerHDF5FileHandler::OverallHistoryMap::const_iterator
    history_number, end_history_number;
  history_number = worker_history_map.begin();
  end_history_number = worker_history_map.end();
  
  while( history_number != end_history_number )
  {
    d_history_number_map[ history_number->first ] = history_number->second;
    
    ++history_number;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleTracker.cpp
//---------------------------------------------------------------------------//
