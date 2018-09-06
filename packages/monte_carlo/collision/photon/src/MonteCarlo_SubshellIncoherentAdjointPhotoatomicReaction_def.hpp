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
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Contructor
template<typename InterpPolicy, bool processed_cross_section>
SubshellIncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::SubshellIncoherentAdjointPhotoatomicReaction(
  const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
  const std::shared_ptr<const std::vector<double> >& cross_section,
  const size_t threshold_energy_index,
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
  const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
  const std::shared_ptr<const std::vector<double> >& cross_section,
  const size_t threshold_energy_index,
  const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
  grid_searcher,
  const std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>&
  scattering_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher,
              scattering_distribution ),
    d_scattering_distribution( scattering_distribution )
{ 
  d_reaction_type =
    convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum(
				    d_scattering_distribution->getSubshell() );
}

// Return the cross section at the given energy
/*! \details The subshell incoherent cross section goes to zero at
 * E_max - E_b. Because the max energy will likely change every time this
 * class is used it is unlikely that this grid point is actually in the 
 * union energy grid. This method will ensure that the cross section goes
 * to zero at the correct energy so that this reaction type does not occur
 * at an energy that isn't physically possible. Note that if the grid point
 * is not in the union energy grid there will be a jump discontinuity at the
 * energy of interest.
 */
template<typename InterpPolicy, bool processed_cross_section>
double SubshellIncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection( const double energy ) const
{
  if( energy < this->getMaxEnergy() - this->getSubshellBindingEnergy() )
    return BaseType::getCrossSection( energy );
  else
    return 0.0;
}

// Return the cross section at the given energy (efficient)
/*! \details The subshell incoherent cross section goes to zero at
 * E_max - E_b. Because the max energy will likely change every time this
 * class is used it is unlikely that this grid point is actually in the 
 * union energy grid. This method will ensure that the cross section goes
 * to zero at the correct energy so that this reaction type does not occur
 * at an energy that isn't physically possible. Note that if the grid point
 * is not in the union energy grid there will be a jump discontinuity at the
 * energy of interest.
 */
template<typename InterpPolicy, bool processed_cross_section>
double SubshellIncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
                                               const double energy,
                                               const size_t bin_index ) const
{
  if( energy < this->getMaxEnergy() - this->getSubshellBindingEnergy() )
    return BaseType::getCrossSection( energy, bin_index );
  else
    return 0.0;
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

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellIncoherentAdjointPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
