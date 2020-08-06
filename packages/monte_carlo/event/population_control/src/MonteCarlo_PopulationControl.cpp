//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PopulationControl.cpp
//! \author Philip Britt
//! \brief  Population Control class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE includes
#include "MonteCarlo_PopulationControl.hpp"

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

};

// Return the default weight window - used when there are no population controllers applied
std::shared_ptr<const PopulationControl> PopulationControl::getDefault()
{
  return std::shared_ptr<const PopulationControl>( new DefaultPopulationController );
}

// Method that splits particle into equal number of weights based on number of particles split into
void PopulationControl::splitParticle( ParticleState& particle,
                      ParticleBank& bank,
                      unsigned number_of_particles ) const
{
  
}

// Method that splits particles with weights based on the expectation weight of particles
void PopulationControl::splitParticle( ParticleState& particle,
                    ParticleBank& bank,
                    unsigned number_of_particles,
                    double expectation_weight) const
{

}

// Method that terminates particle 
void PopulationControl::terminateParticle( ParticleState& particle,
                        ParticleBank& bank,
                        double termination_probability) const
{

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