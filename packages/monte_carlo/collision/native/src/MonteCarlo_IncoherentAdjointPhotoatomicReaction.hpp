//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardGenericAtomicReaction.hpp"
#include "MonteCarlo_AdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The incoherent adjoint photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = true>
class IncoherentAdjointPhotoatomicReaction : public StandardGenericAtomicReaction<AdjointPhotoatomicReaction,InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
  typedef StandardGenericAtomicReaction<AdjointPhotoatomicReaction,InterpPolicy,processed_cross_section> BaseType;

  // Typedef for this type
  typedef IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section> ThisType;

public:

  //! Basic Contructor
  IncoherentAdjointPhotoatomicReaction(
          const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
          const Teuchos::ArrayRCP<const double>& cross_section,
          const unsigned threshold_energy_index,
	  const std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
          scattering_distribution );

  //! Constructor
  IncoherentAdjointPhotoatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    const std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
    scattering_distribution );

  //! Destructor
  virtual ~IncoherentAdjointPhotoatomicReaction()
  { /* ... */ }

  //! Set the critical line energies
  void setCriticalLineEnergies(
               const Teuchos::ArrayRCP<const double>& critical_line_energies );

  //! Get the critical line energies
  const Teuchos::ArrayRCP<const double>& getCriticalLineEnergies() const;

  //! Return the number of adjoint photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the number of adjoint electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the reaction type
  virtual AdjointPhotoatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( AdjointPhotonState& adjoint_photon,
	      ParticleBank& bank,
	      Data::SubshellType& shell_of_interaction ) const;

private:

  // Adapter for the getCrossSection method for use with the scattering dist
  double getCrossSectionAdapter( const double energy,
                                 const double max_energy,
                                 const double precision ) const;

  // The incoherent scattering distribution
  std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>
  d_scattering_distribution;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_IncoherentAdjointPhotoatomicReaction_def.hpp"

#endif // end MONTE_CARLO_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//