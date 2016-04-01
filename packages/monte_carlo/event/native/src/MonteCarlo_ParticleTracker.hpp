//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleTracker.hpp
//! \author Eli Moll
//! \brief  Particle tracking routine declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_TRACKER_HPP
#define MONTE_CARLO_PARTICLE_TRACKER_HPP

// Boost Includes
#include <boost/mpl/vector.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp"
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "MonteCarlo_ParticleTrackerHDF5FileHandler.hpp"

// Trilinos Includes 
#include <Teuchos_Tuple.hpp>
#include <Teuchos_any.hpp>

namespace MonteCarlo{

/*! The particle tracking class, similar to the PTRAC function in MCNP
 */
class ParticleTracker : public ParticleSubtrackEndingGlobalEventObserver,
  public ParticleHistoryObserver
{

public:

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleSubtrackEndingGlobalEventObserver::EventTag>
  EventTags;
  
  //! Constructor
  ParticleTracker( const ParticleHistoryObserver::idType id,
                   const unsigned number_of_histories = 100 );
  
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

  //! Get the x position data
  void getXPositionData( std::vector< double >& array );
  
  //! Get the y position data
  void getYPositionData( std::vector< double >& array );
  
  //! Get the z position data
  void getZPositionData( std::vector< double >& array );
  
  //! Get the x direction data
  void getXDirectionData( std::vector< double >& array );
  
  //! Get the y direction data
  void getYDirectionData( std::vector< double >& array );
  
  //! Get the z direction data
  void getZDirectionData( std::vector< double >& array );
  
  //! Get the energy data
  void getEnergyData( std::vector< double >& array );
  
  //! Get the collision number data
  void getCollisionNumberData( std::vector< double >& array );
  
  //! Get the weight data
  void getWeightData( std::vector< double >& array );
  
  //! Check if particle is reset 
  bool isParticleReset();

  //! Get the data map
  void getDataMap( ParticleTrackerHDF5FileHandler::OverallHistoryMap&
                                                                history_map );

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads );

  //! Check if the observer has uncommitted history contributions
  bool hasUncommittedHistoryContribution() const;

  //! Commit History Contribution
  void commitHistoryContribution();

  //! Reset data
  void resetData();
  
  //! Reduce estimator data in multiple nodes
  void reduceData( 
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process );

  //! Export the particle tracker data via hdf5
  void exportData( const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                   const bool process_data ) const;
                   
  //! Print a summary of the data
  void printSummary( std::ostream& os ) const;

  //! Serialize the data and pack it into a string
  std::string packDataInString();
  
  //! Unpack the data from the serialized string
  void unpackDataFromString( 
              std::string& packed_string,
              ParticleTrackerHDF5FileHandler::OverallHistoryMap& history_map );

private:

  //! Initialize the data maps
  void initialize( unsigned thread );

  //! Contribute the data from the workers
  void contributeDataFromWorkers( std::string packaged_data );
  
  // Flag for new particle 
  std::unordered_map< unsigned, bool > d_particle_reset;

  // Number of histories to be tracked
  const unsigned d_number_of_histories;

  // Position data set - x
  std::unordered_map< unsigned, std::vector< double > > d_x_pos;
  
  // Position data set - y
  std::unordered_map< unsigned, std::vector< double > > d_y_pos;
  
  // Position data set - z
  std::unordered_map< unsigned, std::vector< double > > d_z_pos;
  
  // Direction data set - u
  std::unordered_map< unsigned, std::vector< double > > d_x_dir;
  
  // Direction data set - v
  std::unordered_map< unsigned, std::vector< double > > d_y_dir;
  
  // Direction data set - w
  std::unordered_map< unsigned, std::vector< double > > d_z_dir;
  
  // Energy data set
  std::unordered_map< unsigned, std::vector< double > > d_energy;
  
  // Collision Number data set
  std::unordered_map< unsigned, std::vector< double > > d_col_num;
  
  // Weight data set
  std::unordered_map< unsigned, std::vector< double > > d_weight;
  
  // History Number
  std::unordered_map< unsigned, unsigned > d_history_number;
  
  // Generation Number
  std::unordered_map< unsigned, unsigned > d_generation_number;
  
  // Particle Type
  std::unordered_map< unsigned, unsigned > d_particle_type;
       
  // Map of history number to particle type
  ParticleTrackerHDF5FileHandler::OverallHistoryMap d_history_number_map;
  
  // First particle
  bool d_first_particle;
  
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
        ar & d_history_number_map;
  }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_TRACKER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleTracker.hpp
//---------------------------------------------------------------------------//
