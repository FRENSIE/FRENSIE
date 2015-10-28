//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_YieldBasePhotonProductionReaction.hpp
//! \author Alex Robinson
//! \brief  The photon production reaction with yield data declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_YIELD_BASED_PHOTON_PRODUCTION_REACTION_HPP
#define MONTE_CARLO_YIELD_BASED_PHOTON_PRODUCTION_REACTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonProductionReaction.hpp"
#include "MonteCarlo_NuclearReaction.hpp"

namespace MonteCarlo{

//! THe photon production reaction with yield data (for MFTYPE=12 or MFTYPE=16)
class YieldBasedPhotonProductionReaction : public PhotonProductionReaction
{

private:

  // Teuchos ScalarTraits typedef
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor 
  YieldBasedPhotonProductionReaction(
	 const NuclearReactionType base_reaction_type,
	 const unsigned photon_production_id,
	 const double temperature,
	 const Teuchos::ArrayView<const double>& yield_energy_grid,
	 const Teuchos::ArrayView<const double>& yield,
	 const Teuchos::RCP<NuclearReaction>& base_reaction,
	 const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,PhotonState> >& 
	 photon_production_distribution );

  //! Destructor
  ~YieldBasedPhotonProductionReaction()
  { /* ... */ }
  
  //! Return the threshold energy
  double getThresholdEnegy() const;

  //! Return the cross section at a given energy
  double getCrossSection( const double energy ) const;

private:

  // The photon production yield energy grid
  Teuchos::Array<double> d_yield_energy_grid;

  // The photon production yield
  Teuchos::Array<double> d_yield;

  // The base neutron absorption reaction
  Teuchos::RCP<NuclearReaction> d_base_reaction;
};

// Return the threshold energy
inline double YieldBasedPhotonProductionReaction::getThresholdEnegy() const
{
  return d_yield_energy_grid[0];
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_YIELD_BASED_PHOTON_PRODUCTION_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_YieldBasedPhotonProductionReaction.hpp
//---------------------------------------------------------------------------//
