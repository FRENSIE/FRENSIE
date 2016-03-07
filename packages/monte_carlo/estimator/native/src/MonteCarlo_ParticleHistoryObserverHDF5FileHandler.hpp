//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleHistoryObserverHDF5FileHandler.hpp
//! \author Alex Robinson
//! \brief  The particle history observer hdf5 file handler class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_HISTORY_OBSERVER_HDF5_FILE_HANDLER_HPP
#define MONTE_CARLO_PARTICLE_HISTORY_OBSERVER_HDF5_FILE_HANDLER_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_HDF5FileHandler.hpp"
#include "Utility_HDF5TypeTraits.hpp"

namespace MonteCarlo{

//! The particle history observer hdf5 file handler
class ParticleHistoryObserverHDF5FileHandler
{

public:

  //! Enum for file operations
  enum ParticleHistoryObserverHDF5FileOps{
    OVERWRITE_PHO_HDF5_FILE = 0,
    APPEND_PHO_HDF5_FILE,
    READ_ONLY_PHO_HDF5_FILE
  };

  //! Constructor (file ownership)
  ParticleHistoryObserverHDF5FileHandler(
                             const std::string& hdf5_file_name,
                             const ParticleHistoryObserverHDF5FileOps file_op =
                             OVERWRITE_PHO_HDF5_FILE );

  //! Constructor (file sharing)
  ParticleHistoryObserverHDF5FileHandler(
                  const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file );

  //! Destructor
  ~ParticleHistoryObserverHDF5FileHandler();

  //! Set the simulation time
  void setSimulationTime( const double simulation_time );

  //! Get the simulation time
  void getSimulationTime( double& simulation_time ) const;

  //! Set the last history simulated
  void setLastHistorySimulated( 
			     const unsigned long long last_history_simulated );

  //! Get the last history simulated
  void getLastHistorySimulated( 
			    unsigned long long& last_history_simulated ) const;

  //! Set the number of histories simulated
  void setNumberOfHistoriesSimulated(
		   const unsigned long long number_histories_simulated );

  //! Get the number of histories simulated
  void getNumberOfHistoriesSimulated(
		        unsigned long long& number_histories_simulated ) const;

private:

  // The particle history observer group location and name
  static const std::string s_pho_group_loc_name;

  // The HDF5 file handler
  std::shared_ptr<Utility::HDF5FileHandler> d_hdf5_file;

  // The ownership flag
  bool d_hdf5_file_ownership;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_HISTORY_OBSERVER_HDF5_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleHistoryObserverHDF5FileHandler.hpp
//---------------------------------------------------------------------------//
