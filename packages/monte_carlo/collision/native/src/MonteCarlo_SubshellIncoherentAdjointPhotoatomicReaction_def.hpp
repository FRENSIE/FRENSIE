//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentAdjointPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The subshell incoherent adjoint photoatomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic Contructor
template<typename InterpPolicy, bool processed_cross_section>
SubshellIncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::SubshellIncoherentAdjointPhotoatomicReaction(
          const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
          const Teuchos::ArrayRCP<const double>& cross_section,
          const unsigned threshold_energy_index,
          const std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>&
          scattering_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              scattering_distribution ),
    d_scattering_distribution( scattering_distribution ),
    d_reaction_type()
{ 
  d_reaction_type =
    convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum(
				    d_scattering_distribution->getSubshell() );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
SubshellIncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::SubshellIncoherentAdjointPhotoatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       const std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>&
       scattering_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher,
              scattering_distribution ),
    d_scattering_distribution( scattering_distribution )
{ 
  d_reaction_type = convertSubshellEnumToIncoherentPhotoatomicReactionEnum(
				    d_scattering_distribution->getSubshell() );
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
AdjointPhotoatomicReactionType SubshellIncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return d_reaction_type;
}

// Get the interaction subshell (non-standard interface)
template<typename InterpPolicy, bool processed_cross_section>
Data::SubshellType SubshellIncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getSubshell() const
{
  return d_scattering_distribution->getSubshell();
}

// Get the subshell binding energy (non-standard interface)
template<typename InterpPolicy, bool processed_cross_section>
double SubshellIncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getSubshellBindingEnergy() const
{
  return d_scattering_distribution->getSubshellBindingEnergy();
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellIncoherentAdjointPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
