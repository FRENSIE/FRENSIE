//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleTrackerHDF5FileHandler.hpp
//! \author Eli Moll
//! \brief  Particle tracker hdf5 file handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_TRACKER_HDF5_FILE_HANDLER_HPP
#define MONTE_CARLO_PARTICLE_TRACKER_HDF5_FILE_HANDLER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_HDF5FileHandler.hpp"
#include "Utility_HDF5TypeTraits.hpp"
#include "MonteCarlo_ParticleType.hpp"

namespace MonteCarlo{

//! The Estimator hdf5 file handler
class ParticleTrackerHDF5FileHandler
{

public:
    
  typedef Teuchos::Array< Teuchos::Array< double > >
    ParticleDataTwoDArray;
    
  typedef boost::unordered_map< unsigned, ParticleDataTwoDArray >
    IndividualParticleSubmap;
    
  typedef boost::unordered_map< unsigned, IndividualParticleSubmap >
    GenerationNumberSubmap;
        
  typedef boost::unordered_map< ParticleType, GenerationNumberSubmap >
    ParticleTypeSubmap;
    
  typedef boost::unordered_map< unsigned, ParticleTypeSubmap >
    OverallHistoryMap;

  //! Enum for file operations
  enum ParticleTrackerHDF5FileOps{
    OVERWRITE_PTRACK_HDF5_FILE = 0,
    APPEND_PTRACK_HDF5_FILE,
    READ_ONLY_PTRACK_HDF5_FILE
  };

  //! Constructor (file ownership)
  ParticleTrackerHDF5FileHandler( 
	  const std::string& hdf5_file_name,
	  const ParticleTrackerHDF5FileOps file_op = OVERWRITE_PTRACK_HDF5_FILE );

  //! Constructor (file sharing)
  ParticleTrackerHDF5FileHandler( 
		     const Teuchos::RCP<Utility::HDF5FileHandler>& hdf5_file );

  //! Destructor
  ~ParticleTrackerHDF5FileHandler();

  //! Assign particle tracker data to HDF5 file
  void setParticleTrackerData( OverallHistoryMap particle_tracker_data_map );
  
  //! Get particle tracker data from HDF5 file
  void getXPositionData( std::string particle_data_location,
                         Teuchos::Array< double >& data );
                         
  //! Get particle tracker data from HDF5 file
  void getYPositionData( std::string particle_data_location,
                         Teuchos::Array< double >& data );
                         
  //! Get particle tracker data from HDF5 file
  void getZPositionData( std::string particle_data_location,
                         Teuchos::Array< double >& data );

  //! Get particle tracker data from HDF5 file
  void getXDirectionData( std::string particle_data_location,
                         Teuchos::Array< double >& data );
                         
  //! Get particle tracker data from HDF5 file
  void getYDirectionData( std::string particle_data_location,
                         Teuchos::Array< double >& data );
                         
  //! Get particle tracker data from HDF5 file
  void getZDirectionData( std::string particle_data_location,
                         Teuchos::Array< double >& data );

  //! Get particle tracker data from HDF5 file
  void getEnergyData( std::string particle_data_location,
                         Teuchos::Array< double >& data );
                         
  //! Get particle tracker data from HDF5 file
  void getCollisionNumberData( std::string particle_data_location,
                         Teuchos::Array< double >& data );
                         
  //! Get particle tracker data from HDF5 file
  void getWeightData( std::string particle_data_location,
                         Teuchos::Array< double >& data );

private:

  // The estimator group location and name
  static const std::string particle_tracker_group_loc_name;

  // The HDF5 file handler
  Teuchos::RCP<Utility::HDF5FileHandler> d_hdf5_file;

  // The ownership flag
  bool d_hdf5_file_ownership;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_TRACKER_HDF5_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleTrackerHDF5FileHandler.hpp
//---------------------------------------------------------------------------//
