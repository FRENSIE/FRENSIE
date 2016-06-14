//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HardElasticElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The single scattering elastic electroatomic reaction class decl.
//! 
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HARD_ELASTIC_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ELECTROIONIZATION_ELECTROATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardElectroatomicReaction.hpp"
#include "MonteCarlo_HardElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The hard elastic electroatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class HardElasticElectroatomicReaction : public StandardElectroatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Constructor
  HardElasticElectroatomicReaction( 
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cross_section,
	  const unsigned threshold_energy_index,
      const int atomic_number,
      const HardElasticElectronScatteringDistribution::ElasticDistribution& 
         elastic_scattering_distribution );


  //! Destructor
  ~HardElasticElectroatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( ElectronState& electron, 
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;

private:

  // The hard_elastic scattering distribution
  HardElasticElectronScatteringDistribution d_scattering_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_HardElasticElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROIONIZATION_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
