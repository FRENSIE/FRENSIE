//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearReaction.hpp
//! \author Alex Robinson
//! \brief  The nuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_REACTION_HPP
#define MONTE_CARLO_NUCLEAR_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearReactionType.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! The nuclear reaction base class
class NuclearReaction
{

private:
  
  // Teuchos ScalarTraits typedef
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  NuclearReaction( const NuclearReactionType reaction_type,
		   const double temperature,
		   const double q_value,
		   const unsigned threshold_energy_index,
	           const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section );

  //! Destructor
  virtual ~NuclearReaction()
  { /* ... */ }

  //! Return the reaction type
  NuclearReactionType getReactionType() const;

  //! Return the temperature (in MeV) at which the reaction occurs 
  double getTemperature() const;

  //! Return the reaction Q value
  double getQValue() const;

  //! Return the threshold energy
  double getThresholdEnergy() const;

  //! Return the cross section at a given energy
  double getCrossSection( const double energy ) const;
  
  //! Return the number of neutrons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedNeutrons( const double energy ) const = 0;

  //! Return the average number of neutron emitted from the rxn
  virtual double getAverageNumberOfEmittedNeutrons( const double energy) const;

  //! Simulate the reaction
  virtual void react( NeutronState& neutron, ParticleBank& bank ) const = 0;

  // Update the threshold energy index for S(alpha,beta) replacement
  void updateThresholdEnergyIndex( const unsigned index );

protected:

  //! Return an integer number of emitted neutrons given a non-integer value
  unsigned sampleNumberOfEmittedNeutrons( 
				     const double average_multiplicity ) const;
  
private:

  // The nuclear reaction type
  NuclearReactionType d_reaction_type;

  // The temperature at which the reaction occurs
  double d_temperature;

  // The Q value for the reaction
  double d_q_value;

  // The reaction threshold energy grid index
  unsigned d_threshold_energy_index;

  // The incoming energy grid
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The cross section values evaluated on the incoming energy grid
  Teuchos::ArrayRCP<const double> d_cross_section;
};

// Return the temperature (in MeV) at which the reaction occurs
inline double NuclearReaction::getTemperature() const
{
  return d_temperature;
}

// Return the threshold energy
inline double NuclearReaction::getThresholdEnergy() const
{
  return d_incoming_energy_grid[d_threshold_energy_index];
}

// Return the average number of neutron emitted from the rxn
/*! \details If the neutron multiplicity for the reaction is not an integer
 * at the desired energy, this function should be overridden in the derived
 * class. It will be used in implicit multiplication weighting games.
 */
inline double NuclearReaction::getAverageNumberOfEmittedNeutrons( 
						    const double energy ) const
{
  return this->getNumberOfEmittedNeutrons( energy );
}

// Return an integer number of emitted neutrons given a non-integer value
/*! In reality, only an integer number of neutrons can be released per
 * reaction. The integer return type of this function reflects this reality. 
 * The integer value is sampled so that the expected value is the average
 * multiplicity.
 */
inline unsigned NuclearReaction::sampleNumberOfEmittedNeutrons( 
				      const double average_multiplicity ) const
{
  // Make sure the average multiplicity is valid
  testPrecondition( average_multiplicity >= 0.0 );

  double floor_multiplicity;
  double round_down_prob = 1.0 - modf( average_multiplicity, 
				       &floor_multiplicity );
  
  if( Utility::RandomNumberGenerator::getRandomNumber<double>() <
      round_down_prob )
    return (unsigned)floor_multiplicity;
  else
    return (unsigned)floor_multiplicity + 1u;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReaction.hpp
//---------------------------------------------------------------------------//
