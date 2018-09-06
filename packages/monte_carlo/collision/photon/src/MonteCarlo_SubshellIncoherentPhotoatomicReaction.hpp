//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The subshell incoherent photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The subshell incoherent photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = true>
class SubshellIncoherentPhotoatomicReaction : public StandardReactionBaseImpl<PhotoatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<PhotoatomicReaction,InterpPolicy,processed_cross_section> BaseType;

public:

  //! Basic constructor
  SubshellIncoherentPhotoatomicReaction(
   const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
   const std::shared_ptr<const std::vector<double> >& cross_section,
   const size_t threshold_energy_index,
   const std::shared_ptr<const SubshellIncoherentPhotonScatteringDistribution>&
   scattering_distribution );

  //! Constructor
  SubshellIncoherentPhotoatomicReaction(
   const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
   const std::shared_ptr<const std::vector<double> >& cross_section,
   const size_t threshold_energy_index,
   const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
   grid_searcher,
   const std::shared_ptr<const SubshellIncoherentPhotonScatteringDistribution>&
   scattering_distribution );

  //! Destructor
  ~SubshellIncoherentPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const override;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const override;

  //! Return the number of positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPositrons( const double energy ) const override;

  //! Return the reaction type
  PhotoatomicReactionType getReactionType() const override;

  //! Simulate the reaction
  void react( PhotonState& photon,
	      ParticleBank& bank,
	      Data::SubshellType& shell_of_interaction ) const override;

  //! Get the interaction subshell (non-standard interface)
  Data::SubshellType getSubshell() const;

  //! Get the subshell binding energy (non-standard interface)
  double getSubshellBindingEnergy() const;

private:

  // The incoherent scattering distribution
  std::shared_ptr<const SubshellIncoherentPhotonScatteringDistribution>
  d_scattering_distribution;

  // The reaction type
  PhotoatomicReactionType d_reaction_type;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_SubshellIncoherentPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end SubshellIncoherentPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
