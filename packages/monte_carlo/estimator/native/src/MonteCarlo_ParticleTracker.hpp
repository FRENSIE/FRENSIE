//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleTracker.hpp
//! \author Eli Moll
//! \brief  Particle tracking routine declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_TRACKER_HPP
#define MONTE_CARLO_PARTICLE_TRACKER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_any.hpp>
#include <Teuchos_Comm.hpp>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/mpl/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp"
#include "MonteCarlo_ParticleType.hpp"
#include "MonteCarlo_ParticleTrackerHDF5FileHandler.hpp"

namespace MonteCarlo{

/*! The particle tracking class, similar to the PTRAC function in MCNP
 */
class ParticleTracker : public ParticleSubtrackEndingGlobalEventObserver
{

public:

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleSubtrackEndingGlobalEventObserver::EventTag>
  EventTags;
  
  //! Constructor
  ParticleTracker( const unsigned number_of_histories = 100 );
  
  //! Destructor
  ~ParticleTracker()
  { /* ... */ }
  
  //! Add current history contribution
  void updateFromGlobalParticleSubtrackEndingEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );

  //! Commit current history data to overall maps
  void commitParticleTrackData();
  
  //! Reset particle track data for next particle
  void resetParticleTrackData();

  //! Export the particle tracker data via hdf5
  void exportData( ParticleTrackerHDF5FileHandler& hdf5_file,
                   const bool process_data ) const;

  //! Get the x position data
  void getXPositionData( Teuchos::Array< double >& array );
  
  //! Get the y position data
  void getYPositionData( Teuchos::Array< double >& array );
  
  //! Get the z position data
  void getZPositionData( Teuchos::Array< double >& array );
  
  //! Get the x direction data
  void getXDirectionData( Teuchos::Array< double >& array );
  
  //! Get the y direction data
  void getYDirectionData( Teuchos::Array< double >& array );
  
  //! Get the z direction data
  void getZDirectionData( Teuchos::Array< double >& array );
  
  //! Get the energy data
  void getEnergyData( Teuchos::Array< double >& array );
  
  //! Get the collision number data
  void getCollisionNumberData( Teuchos::Array< double >& array );
  
  //! Get the weight data
  void getWeightData( Teuchos::Array< double >& array );
  
  //! Check if particle is reset 
  bool isParticleReset();

  //! Get the data map
  void getDataMap( ParticleTrackerHDF5FileHandler::OverallHistoryMap&
                                                                history_map );

  //! Reset data
  void resetData();
  
  //! Commit History Contribution
  void commitHistoryContribution();
  
  //! Reduce estimator data in multiple nodes
  void reduceData( 
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process );

private:

  // Flag for new particle 
  bool d_particle_reset;

  // Number of histories to be tracked
  const unsigned d_number_of_histories;

  // Position data set - x
  Teuchos::Array< double > d_x_pos;
  
  // Position data set - y
  Teuchos::Array< double > d_y_pos;
  
  // Position data set - z
  Teuchos::Array< double > d_z_pos;
  
  // Direction data set - u
  Teuchos::Array< double > d_x_dir;
  
  // Direction data set - v
  Teuchos::Array< double > d_y_dir;
  
  // Direction data set - w
  Teuchos::Array< double > d_z_dir;
  
  // Energy data set
  Teuchos::Array< double > d_energy;
  
  // Collision Number data set
  Teuchos::Array< double > d_col_num;
  
  // Weight data set
  Teuchos::Array< double > d_weight;
  
  // History Number
  unsigned d_history_number;
  
  // Generation Number
  unsigned d_generation_number;
  
  // Particle Type
  ParticleType d_particle_type;
       
  // Map of history number to particle type
  ParticleTrackerHDF5FileHandler::OverallHistoryMap d_history_number_map;
  
  // First particle
  bool d_first_particle;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_TRACKER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleTracker.hpp
//---------------------------------------------------------------------------//
