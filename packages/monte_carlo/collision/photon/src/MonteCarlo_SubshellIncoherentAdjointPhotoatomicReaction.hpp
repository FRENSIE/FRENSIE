//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentAdjointPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The subshell incoherent adjoint photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The subshell incoherent adjoint photoatomic reaction class
template<typename InterpPolicy, bool processed_cross_section>
class SubshellIncoherentAdjointPhotoatomicReaction : public IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
  typedef IncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section> BaseType;

  // Typedef for this type
  typedef SubshellIncoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section> ThisType;

public:

  //! Basic Contructor
  SubshellIncoherentAdjointPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>&
       scattering_distribution );

  //! Constructor
  SubshellIncoherentAdjointPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const std::shared_ptr<SubshellIncoherentAdjointPhotonScatteringDistribution>&
       scattering_distribution );

  //! Destructor
  ~SubshellIncoherentAdjointPhotoatomicReaction()
  { /* ... */ }

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const override;

  //! Return the cross section at the given energy (efficient)
  double getCrossSection( const double energy,
                          const size_t bin_index ) const override;
  
  //! Return the reaction type
  virtual AdjointPhotoatomicReactionType getReactionType() const override;

  //! Get the interaction subshell (non-standard interface)
  Data::SubshellType getSubshell() const;

  //! Get the subshell binding energy (non-standard interface)
  double getSubshellBindingEnergy() const;

private:

  // The subshell incoherent adjoint scattering distribution
  std::shared_ptr<const SubshellIncoherentAdjointPhotonScatteringDistribution>
  d_scattering_distribution;

  // The reaction type
  AdjointPhotoatomicReactionType d_reaction_type;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_SubshellIncoherentAdjointPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellIncoherentAdjointPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
