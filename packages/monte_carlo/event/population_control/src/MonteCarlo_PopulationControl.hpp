//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PopulationControl.hpp
//! \author Philip Britt
//! \brief  Population Control class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POPULATION_CONTROL_HPP
#define MONTE_CARLO_POPULATION_CONTROL_HPP

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_DiscretizableParticleHistoryObserver.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

//! The population control base class
class PopulationControl : public DiscretizableParticleHistoryObserver
{

public:

  //! Constructor
  PopulationControl()
  { /* ... */ }

  //! Destructor
  virtual ~PopulationControl()
  { /* ... */ }

  virtual void checkParticleWithPopulationController( ParticleState& particle, 
                                                      ParticleBank& bank ) const = 0;

  static std::shared_ptr<PopulationControl> getDefault();

protected: 

  //! Split particle (purely based on number of splits)
  void splitParticle( ParticleState& particle,
                      ParticleBank& bank,
                      unsigned number_of_particles ) const;

  //! Split particle based on expectation weight
  void splitParticle( ParticleState& particle,
                      ParticleBank& bank,
                      unsigned number_of_particles,
                      double weight_factor) const;

  //! Terminate particle
  void terminateParticle( ParticleState& particle,
                         double termination_probability) const; 

private:

  void pushSplitParticlesToBank( ParticleState& particle,
                                 ParticleBank& bank,
                                 unsigned number_of_particles) const;

  /* The below methods are not used for weight windows but must be defined due to being pure virtual in the Particle History Observer
     class. At some point, this will need to be fixed and these methods removed */
  void enableThreadSupport( const unsigned num_threads ) final override;

  bool hasUncommittedHistoryContribution() const final override;

  void commitHistoryContribution();

  void takeSnapshot( const uint64_t num_histories_since_last_snapshot,
                     const double time_since_last_snapshot ) final override;

  void resetData() final override;

  void reduceData( const Utility::Communicator& comm,
                   const int root_process ) final override;

  void printSummary( std::ostream& os ) const final override;
                         
  // Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { 
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( DiscretizableParticleHistoryObserver );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

};
  
} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::PopulationControl, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::PopulationControl );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, PopulationControl );

#endif // end MONTE_CARLO_POPULATION_CONTROL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PopulationControl.hpp
//---------------------------------------------------------------------------//
