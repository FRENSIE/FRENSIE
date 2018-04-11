//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearReaction.hpp
//! \author Alex Robinson
//! \brief  The nuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_REACTION_HPP
#define MONTE_CARLO_NUCLEAR_REACTION_HPP

namespace MonteCarlo{

//! The nuclear reaction base class
class NuclearReaction
{

public:

  //! Constructor
  NuclearReaction()
  { /* ... */ }

  //! Destructor
  virtual ~NuclearReaction()
  { /* ... */ }

  //! Test if two Atomic reactions share the same energy grid
  bool isEnergyGridShared( const NuclearReaction& other_reaction ) const;

  //! Test if the energy falls within the energy grid
  virtual bool isEnergyWithinEnergyGrid( const double energy ) const = 0;

  //! Return the reaction Q value
  virtual double getQValue() const = 0;

  //! Return the threshold energy
  virtual double getThresholdEnergy() const = 0;

  //! Return the max energy
  virtual double getMaxEnergy() const = 0;

  //! Return the cross section at the given energy
  virtual double getCrossSection( const double energy ) const = 0;

  //! Return the cross section at the given energy (efficient)
  virtual double getCrossSection( const double energy,
                                  const size_t bin_index ) const = 0;

  //! Return the number of emitted primary outgoing particles
  virtual unsigned getNumberOfEmittedParticles( const double energy ) const = 0;

  //! Return the average number of emitted primary outgoing particles
  virtual double getAverageNumberOfEmittedParticles( const double energy ) const;

protected:

  //! Return an integer number of emitted particles given an average value
  unsigned sampleNumberOfEmittedParticles(
                      const double average_number_of_emitted_particles ) const;

  //! Return the head of the energy grid
  virtual const double* getEnergyGridHead() const = 0;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReaction.hpp
//---------------------------------------------------------------------------//
