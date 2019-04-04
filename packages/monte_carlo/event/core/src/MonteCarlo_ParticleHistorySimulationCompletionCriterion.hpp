//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleHistorySimulationCompletionCriterion.hpp
//! \author Alex Robinson
//! \brief  The particle history simulation completion criterion class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_HISTORY_SIMULATION_COMPLETION_CRITERION_HPP
#define MONTE_CARLO_PARTICLE_HISTORY_SIMULATION_COMPLETION_CRITERION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

//! The particle history simulation completion criterion
class ParticleHistorySimulationCompletionCriterion : public ParticleHistoryObserver
{

public:

  //! Get a history count completion criterion
  static std::shared_ptr<ParticleHistorySimulationCompletionCriterion>
  createHistoryCountCriterion( const uint64_t history_wall );

  //! Get a wall time (s) completion criterion
  static std::shared_ptr<ParticleHistorySimulationCompletionCriterion>
  createWallTimeCriterion( const double wall_time );

  //! Create a mixed criterion (# histories || wall time)
  static std::shared_ptr<ParticleHistorySimulationCompletionCriterion>
  createMixedCriterion( const uint64_t history_wall,
                        const double wall_time );

  //! Constructor
  ParticleHistorySimulationCompletionCriterion()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleHistorySimulationCompletionCriterion()
  { /* ... */ }

  //! Check if the simulation is complete
  virtual bool isSimulationComplete() const = 0;

  //! Start the criterion
  virtual void start() = 0;

  //! Stop the criterion
  virtual void stop() = 0;

  //! Clear cached criterion data
  virtual void clearCache() = 0;

  //! Take a snapshot
  void takeSnapshot( const uint64_t histories,
                     const double time ) final override;

  //! Print a summary of the data
  void printSummary( std::ostream& os ) const final override;

  //! Get a description of the criterion
  virtual std::string description() const = 0;

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleHistoryObserver ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};
  
} // end MonteCarlo namespace

//! Create a mixed criterion using the || operator
std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion> operator||(
    const std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>& lhs,
    const std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>& rhs );

//! Create a mixed criterion using the && operator
std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion> operator&&(
    const std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>& lhs,
    const std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>& rhs );

BOOST_SERIALIZATION_CLASS_VERSION( ParticleHistorySimulationCompletionCriterion, MonteCarlo, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::ParticleHistorySimulationCompletionCriterion );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST_ALWAYS( MonteCarlo, ParticleHistorySimulationCompletionCriterion );

#endif // end MONTE_CARLO_PARTICLE_HISTORY_SIMULATION_COMPLETION_CRITERION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleHistorySimulationCompletionCriterion.hpp
//---------------------------------------------------------------------------//
