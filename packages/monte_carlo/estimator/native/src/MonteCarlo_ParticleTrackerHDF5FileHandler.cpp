//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorHDF5FileHandler.hpp
//! \author Alex Robinson
//! \brief  Estimator hdf5 file handler class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_ParticleTrackerHDF5FileHandler.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize static member data
const std::string ParticleTrackerHDF5FileHandler::particle_tracker_group_loc_name( 
							      "/Particle_Tracker/" );

// Constructor (file ownership)
/*! \details The ParticleTrackerHDF5FileOps enum will determine how the HDF5
 * file is opened. If the read only option is used, calling any of the set
 * methods will result in an exception.
 */
ParticleTrackerHDF5FileHandler::ParticleTrackerHDF5FileHandler( 
					   const std::string& hdf5_file_name,
					   const ParticleTrackerHDF5FileOps file_op )
  : d_hdf5_file( new Utility::HDF5FileHandler ),
    d_hdf5_file_ownership( true )
{
  // Make sure the name is valid
  testPrecondition( hdf5_file_name.size() > 0 );
  
  Utility::HDF5FileHandler::throwExceptions();

  try{
    switch( file_op )
    {
    case OVERWRITE_PTRACK_HDF5_FILE:
      d_hdf5_file->openHDF5FileAndOverwrite( hdf5_file_name );
      break;
    case APPEND_PTRACK_HDF5_FILE:
      d_hdf5_file->openHDF5FileAndAppend( hdf5_file_name );
      break;
    case READ_ONLY_PTRACK_HDF5_FILE:
      d_hdf5_file->openHDF5FileAndReadOnly( hdf5_file_name );
      break;
    }
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Ownership Constructor Error" );
}

// Constructor (file sharing)
ParticleTrackerHDF5FileHandler::ParticleTrackerHDF5FileHandler( 
		      const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file )
  : d_hdf5_file( hdf5_file ),
    d_hdf5_file_ownership( false )
{
  // Make sure the file is valid
  testPrecondition( hdf5_file.get() );
  testPrecondition( hdf5_file->hasOpenFile() );
  
  Utility::HDF5FileHandler::throwExceptions();
}

// Destructor
ParticleTrackerHDF5FileHandler::~ParticleTrackerHDF5FileHandler()
{
  if( d_hdf5_file_ownership )
    d_hdf5_file->closeHDF5File();
}

// Assign particle tracker data to HDF5 file 
void ParticleTrackerHDF5FileHandler::setParticleTrackerData(
       ParticleTrackerHDF5FileHandler::OverallHistoryMap 
         particle_tracker_data_map )
{
  ParticleTrackerHDF5FileHandler::OverallHistoryMap::const_iterator
    history_number, end_history_number;
  history_number = particle_tracker_data_map.begin();
  end_history_number = particle_tracker_data_map.end();
  
  while( history_number != end_history_number )
  {
    std::string history_location = particle_tracker_group_loc_name + 
                                std::to_string( history_number->first ) + "/";
                                     
    ParticleTrackerHDF5FileHandler::ParticleTypeSubmap::const_iterator
      particle_type, end_particle_type;
    particle_type = history_number->second.begin();
    end_particle_type = history_number->second.end();
    
    while( particle_type != end_particle_type )
    {
      std::string particle_location = history_location + 
                                  std::to_string( particle_type->first ) + "/";
                                        
      ParticleTrackerHDF5FileHandler::GenerationNumberSubmap::const_iterator
        generation_number, end_generation_number;
      generation_number = particle_type->second.begin();
      end_generation_number = particle_type->second.end();
      
      while( generation_number != end_generation_number )
      {      
        std::string generation_location = particle_location + 
                              std::to_string( generation_number->first ) + "/";
                                    
        ParticleTrackerHDF5FileHandler::IndividualParticleSubmap::const_iterator
          particle_number, end_particle_number;
        particle_number = generation_number->second.begin();
        end_particle_number = generation_number->second.end();
        
        while( particle_number != end_particle_number )
        {
          
          std::string individual_particle_location = generation_location +
                                std::to_string( particle_number->first ) + "/";
        
          // Extract the particle information
          std::vector< double > x_pos = particle_number->second[0];
          std::vector< double > y_pos = particle_number->second[1];
          std::vector< double > z_pos = particle_number->second[2];
          
          std::vector< double > x_dir = particle_number->second[3];
          std::vector< double > y_dir = particle_number->second[4];
          std::vector< double > z_dir = particle_number->second[5];
          
          std::vector< double > energy = particle_number->second[6];
          std::vector< double > col_num = particle_number->second[7];
          std::vector< double > weight = particle_number->second[8];
          
          // Construct data set folders for data
          std::string x_pos_dataset = individual_particle_location += "x_position";
          std::string y_pos_dataset = individual_particle_location += "y_position";
          std::string z_pos_dataset = individual_particle_location += "z_position";
          
          std::string x_dir_dataset = individual_particle_location += "x_direction";
          std::string y_dir_dataset = individual_particle_location += "y_direction";
          std::string z_dir_dataset = individual_particle_location += "z_direction";
          
          std::string energy_dataset = individual_particle_location += "energy";
          std::string col_num_dataset = individual_particle_location += "collision_number";
          std::string weight_dataset = individual_particle_location += "weight";
          
          // Write the arrays to data sets
          try{
            d_hdf5_file->writeArrayToDataSet( x_pos, x_pos_dataset );
          }
          EXCEPTION_CATCH_RETHROW( std::runtime_error,
            "Error writing particle tracking x position data to HDF5 dataset" );
          
          try{  
          d_hdf5_file->writeArrayToDataSet( y_pos, y_pos_dataset );
                    }
          EXCEPTION_CATCH_RETHROW( std::runtime_error,
            "Error writing particle tracking y position data to HDF5 dataset" );
          
          try{  
          d_hdf5_file->writeArrayToDataSet( z_pos, z_pos_dataset );
                              }
          EXCEPTION_CATCH_RETHROW( std::runtime_error,
            "Error writing particle tracking z position data to HDF5 dataset" );
          
          try{
          d_hdf5_file->writeArrayToDataSet( x_dir, x_dir_dataset );
                              }
          EXCEPTION_CATCH_RETHROW( std::runtime_error,
            "Error writing particle tracking x_direction data to HDF5 dataset" );
          
          try{  
          d_hdf5_file->writeArrayToDataSet( y_dir, y_dir_dataset );
                              }
          EXCEPTION_CATCH_RETHROW( std::runtime_error,
            "Error writing particle tracking y direction data to HDF5 dataset" );
          
          try{  
          d_hdf5_file->writeArrayToDataSet( z_dir, z_dir_dataset );
                              }
          EXCEPTION_CATCH_RETHROW( std::runtime_error,
            "Error writing particle tracking z direction data to HDF5 dataset" );
          
          try{
          d_hdf5_file->writeArrayToDataSet( energy, energy_dataset );
                              }
          EXCEPTION_CATCH_RETHROW( std::runtime_error,
            "Error writing particle tracking energy data to HDF5 dataset" );
          
          try{  
          d_hdf5_file->writeArrayToDataSet( col_num, col_num_dataset );
                              }
          EXCEPTION_CATCH_RETHROW( std::runtime_error,
            "Error writing particle tracking collision number data to HDF5 dataset" );
          
          try{  
          d_hdf5_file->writeArrayToDataSet( weight, weight_dataset );
                              }
          EXCEPTION_CATCH_RETHROW( std::runtime_error,
            "Error writing particle tracking weight data to HDF5 dataset" );
          
          ++particle_number;
        }
        ++generation_number;
      }
      ++particle_type;
    }
    ++history_number;
  }
}

// Get the particle tracker data history map
void ParticleTrackerHDF5FileHandler::getXPositionData( 
                                std::string particle_data_location,
                                std::vector< double >& data )
{  
  try{
    d_hdf5_file->readArrayFromDataSet(
			       data, 
             particle_data_location + "x_position" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get x position error" );
}

// Get the particle tracker data history map
void ParticleTrackerHDF5FileHandler::getYPositionData( 
                                std::string particle_data_location,
                                std::vector< double >& data )
{  
  try{
    d_hdf5_file->readArrayFromDataSet(
			       data, 
             particle_data_location + "y_position" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get y position error" );
}

// Get the particle tracker data history map
void ParticleTrackerHDF5FileHandler::getZPositionData( 
                                std::string particle_data_location,
                                std::vector< double >& data )
{  
  try{
    d_hdf5_file->readArrayFromDataSet(
			       data, 
             particle_data_location + "z_position" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get z position error" );
}

// Get the particle tracker data history map
void ParticleTrackerHDF5FileHandler::getXDirectionData( 
                                std::string particle_data_location,
                                std::vector< double >& data )
{  
  try{
    d_hdf5_file->readArrayFromDataSet(
			       data, 
             particle_data_location + "x_direction" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get x direction error" );
}

// Get the particle tracker data history map
void ParticleTrackerHDF5FileHandler::getYDirectionData( 
                                std::string particle_data_location,
                                std::vector< double >& data )
{  
  try{
    d_hdf5_file->readArrayFromDataSet(
			       data, 
             particle_data_location + "y_direction" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get y direction error" );
}

// Get the particle tracker data history map
void ParticleTrackerHDF5FileHandler::getZDirectionData( 
                                std::string particle_data_location,
                                std::vector< double >& data )
{  
  try{
    d_hdf5_file->readArrayFromDataSet(
			       data, 
             particle_data_location + "z_direction" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get z direction error" );
}

// Get the particle tracker data history map
void ParticleTrackerHDF5FileHandler::getEnergyData( 
                                std::string particle_data_location,
                                std::vector< double >& data )
{  
  try{
    d_hdf5_file->readArrayFromDataSet(
			       data, 
             particle_data_location + "energy" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get energy error" );
}

// Get the particle tracker data history map
void ParticleTrackerHDF5FileHandler::getCollisionNumberData( 
                                std::string particle_data_location,
                                std::vector< double >& data )
{  
  try{
    d_hdf5_file->readArrayFromDataSet(
			       data, 
             particle_data_location + "collision_number" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get collision number error" );
}

// Get the particle tracker data history map
void ParticleTrackerHDF5FileHandler::getWeightData( 
                                std::string particle_data_location,
                                std::vector< double >& data )
{  
  try{
    d_hdf5_file->readArrayFromDataSet(
			       data, 
             particle_data_location + "weight" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get weight error" );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
