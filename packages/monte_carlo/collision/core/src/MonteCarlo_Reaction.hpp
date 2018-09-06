//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Reaction.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_REACTION_HPP
#define MONTE_CARLO_REACTION_HPP

#include <cstddef>

namespace MonteCarlo{

//! The reaction base class
class Reaction
{

public:

  //! Constructor
  Reaction()
  { /* ... */ }

  //! Destructor
  virtual ~Reaction()
  { /* ... */ }

  //! Test if two Atomic reactions share the same energy grid
  virtual bool isEnergyGridShared( const Reaction& other_reaction ) const;

  //! Test if the energy falls within the energy grid
  virtual bool isEnergyWithinEnergyGrid( const double energy ) const = 0;

  //! Return the threshold energy
  virtual double getThresholdEnergy() const = 0;

  //! Return the max energy
  virtual double getMaxEnergy() const = 0;

  //! Return the cross section at the given energy
  virtual double getCrossSection( const double energy ) const = 0;

  //! Return the cross section at the given energy (efficient)
  virtual double getCrossSection( const double energy,
                                  const size_t bin_index ) const = 0;

protected:

  //! Return the head of the energy grid
  virtual const double* getEnergyGridHead() const = 0;
};

// Test if two reactions share the same energy grid (union grid)
inline bool Reaction::isEnergyGridShared( const Reaction& other_reaction ) const
{
  return this->getEnergyGridHead() == other_reaction.getEnergyGridHead();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Reaction.hpp
//---------------------------------------------------------------------------//
