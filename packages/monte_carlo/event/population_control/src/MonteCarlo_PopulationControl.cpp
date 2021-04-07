//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PopulationControl.cpp
//! \author Philip Britt
//! \brief  Population Control class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_PopulationControl.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

//! The default weight window
class DefaultPopulationController : public PopulationControl
{

public:

  //! Constructor
  DefaultPopulationController()
  { /* ... */ }

  //! Destructor
  ~DefaultPopulationController()
  { /* ... */ }

  //! Does nothing
  void checkParticleWithPopulationController( ParticleState&, ParticleBank& ) const final override
  { /* ... */ }

private:

  // Serialize the population controller data to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( PopulationControl ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

};

// Return the default weight window - used when there are no population controllers applied
std::shared_ptr<PopulationControl> PopulationControl::getDefault()
{
  return std::make_shared<DefaultPopulationController>();
}

// Method that splits particle into equal number of weights based on number of particles split into
void PopulationControl::splitParticle( ParticleState& particle,
                                       ParticleBank& bank,
                                       unsigned number_of_particles ) const
{
  particle.multiplyWeight(1/static_cast<double>(number_of_particles));

  this->pushSplitParticlesToBank(particle,
                                 bank,
                                 number_of_particles);

}

// Method that splits particles with weights based on the expectation weight of particles
void PopulationControl::splitParticle( ParticleState& particle,
                                       ParticleBank& bank,
                                       unsigned number_of_particles,
                                       double weight_factor) const
{

  particle.multiplyWeight(weight_factor);

  this->pushSplitParticlesToBank(particle,
                                 bank,
                                 number_of_particles);

}

// Method that terminates particle 
void PopulationControl::terminateParticle( ParticleState& particle,
                                           double termination_probability) const
{
  double random_number = Utility::RandomNumberGenerator::getRandomNumber<double>();

  if( random_number < termination_probability )
  {
    particle.setAsGone();
  }else
  {
    particle.multiplyWeight(1/(1-termination_probability));
  }
}

void PopulationControl::pushSplitParticlesToBank( ParticleState& particle,
                                                  ParticleBank& bank,
                                                  unsigned number_of_particles) const
{
  for(unsigned i = 0; i < number_of_particles - 1; ++i)
  {
    std::shared_ptr<ParticleState> split_particle( particle.clone() );
    
    bank.push( split_particle );
  }
}

/* The below functions should not be used */
void PopulationControl::enableThreadSupport( const unsigned num_threads )
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for population controllers")
}

bool PopulationControl::hasUncommittedHistoryContribution() const
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for population controllers")
}

void PopulationControl::commitHistoryContribution()
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for population controllers")
}

void PopulationControl::takeSnapshot( const uint64_t num_histories_since_last_snapshot,
                            const double time_since_last_snapshot )
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for population controllers")
}

void PopulationControl::resetData()
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for population controllers")
}

void PopulationControl::reduceData( const Utility::Communicator& comm,
                          const int root_process )
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for population controllers")
}

void PopulationControl::printSummary( std::ostream& os ) const
{
  THROW_EXCEPTION(std::runtime_error, "This method should not be used for population controllers")
}

}// end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::DefaultPopulationController, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( DefaultPopulationController, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( DefaultPopulationController, MonteCarlo );

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::PopulationControl );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DefaultPopulationController );