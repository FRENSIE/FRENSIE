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
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/any.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp"
#include "MonteCarlo_ParticleGoneGlobalEventObserver.hpp"
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "MonteCarlo_UniqueIdManager.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_Array.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! The particle tracking class, similar to the PTRAC function in MCNP
 */
class ParticleTracker : public ParticleSubtrackEndingGlobalEventObserver,
                        public ParticleGoneGlobalEventObserver,
                        public ParticleHistoryObserver
{

public:

  //! Typedef for the id type
  typedef uint32_t Id;

  //! Typedef for the particle data array
  // 0 = position,
  // 1 = direction,
  // 2 = energy,
  // 3 = time,
  // 4 = weight,
  // 5 = collision number
  typedef std::vector<std::tuple<std::array<double,3>,std::array<double,3>,double,double,double,ParticleState::collisionNumberType> >
    ParticleDataArray;

  //! Typedef for the individual particle submap
  typedef std::unordered_map<unsigned,ParticleDataArray>
    IndividualParticleSubmap;

  //! Typedef for the generation number submap
  typedef std::unordered_map<ParticleState::generationNumberType,IndividualParticleSubmap>
    GenerationNumberSubmap;

  //! Typedef for the particle type submap
  typedef std::map<ParticleType,GenerationNumberSubmap>
    ParticleTypeSubmap;

  //! Typedef for the history map
  typedef std::unordered_map<ParticleState::historyNumberType,ParticleTypeSubmap>
    OverallHistoryMap;

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleSubtrackEndingGlobalEventObserver::EventTag,ParticleGoneGlobalEventObserver::EventTag>
  EventTags;

  //! Constructor
  ParticleTracker( const Id id,
                   const uint64_t number_of_histories );

  //! Constructor
  ParticleTracker( const Id id,
                   const std::set<uint64_t>& history_numbers );

  //! Destructor
  ~ParticleTracker()
  { /* ... */ }

  //! Return the estimator id
  Id getId() const;

  //! Return the histories that will be tracked
  const std::set<uint64_t>& getTrackedHistories() const;

  //! Add current history contribution
  void updateFromGlobalParticleSubtrackEndingEvent(
                                    const ParticleState& particle,
                                    const double start_point[3],
                                    const double end_point[3] ) final override;

  //! Update the observer
  void updateFromGlobalParticleGoneEvent(
                                const ParticleState& particle ) final override;


  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads ) final override;

  //! Check if the observer has uncommitted history contributions
  bool hasUncommittedHistoryContribution() const final override;

  //! Commit History Contribution
  void commitHistoryContribution() final override;

  //! Take a snapshot
  void takeSnapshot( const uint64_t num_histories_since_last_snapshot,
                     const double time_since_last_snapshot ) final override;

  //! Reset data
  void resetData() final override;

  //! Reduce estimator data in multiple nodes
  void reduceData( const Utility::Communicator& comm,
                   const int root_process ) final override;

  //! Print a summary of the data
  void printSummary( std::ostream& os ) const final override;

  //! Get the data map
  void getHistoryData( OverallHistoryMap& history_map ) const;

private:

  // Default constructor
  ParticleTracker();

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The estimator id
  UniqueIdManager<ParticleTracker,Id> d_id;

  // The histories to be tracked
  std::set<uint64_t> d_histories_to_track;

  // The partial tracked history info
  typedef std::map<const ParticleState*,ParticleDataArray> PartialHistorySubmap;
  std::vector<PartialHistorySubmap> d_partial_history_map;

  // The tracked history info
  OverallHistoryMap d_history_number_map;
};

// Save the estimator data
template<typename Archive>
void ParticleTracker::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSubtrackEndingGlobalEventObserver );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleGoneGlobalEventObserver );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleHistoryObserver );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_id );
  ar & BOOST_SERIALIZATION_NVP( d_histories_to_track );
  ar & BOOST_SERIALIZATION_NVP( d_history_number_map );
}

// Load the estimator data
template<typename Archive>
void ParticleTracker::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSubtrackEndingGlobalEventObserver );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleGoneGlobalEventObserver );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleHistoryObserver );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_id );
  ar & BOOST_SERIALIZATION_NVP( d_histories_to_track );
  ar & BOOST_SERIALIZATION_NVP( d_history_number_map );

  d_partial_history_map.resize( 1 );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( ParticleTracker, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleTracker, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ParticleTracker );

#endif // end MONTE_CARLO_PARTICLE_TRACKER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleTracker.hpp
//---------------------------------------------------------------------------//
