//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardGenericAtomicReaction.hpp
//! \author Alex Robinson
//! \brief  The standard generic atomic reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_GENERIC_ATOMIC_REACTION_HPP
#define MONTE_CARLO_GENERIC_ATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_HashBasedGridSearcher.hpp"

namespace MonteCarlo{

/*! The standard generic atomic reaction class
 * \details This class inherits from the desired base class and implements
 * some standard features that are used by many atomic reaction classes (
 * e.g. MonteCarlo::PhotoatomicReaction, MonteCarlo::AdjointPhotoatomicReaction
 * ). Use the InterpPolicy template parameter and the processed_cross_section
 * template parameter to customize the behavior of this class. Raw cross
 * section data from the EPDL library would use the Utility::LogLog policy with
 * processed_cross_section = false. Processed cross section data from an
 * ACE library would use the Utility::LogLog policy with
 * processed_cross_section = true. Cross section data from a native library
 * would use Utility::LinLin with processed_cross_section = false.
 */
template<typename AtomicReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
class StandardGenericAtomicReaction : public AtomicReactionBase
{

public:

  //! Basic constructor
  StandardGenericAtomicReaction(
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index );

  //! Constructor
  StandardGenericAtomicReaction(
     const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
     const Teuchos::ArrayRCP<const double>& cross_section,
     const unsigned threshold_energy_index,
     const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher );

  //! Destructor
  virtual ~StandardGenericAtomicReaction()
  { /* ... */ }

  //! Test if the energy falls within the energy grid
  bool isEnergyWithinEnergyGrid( const double energy ) const;

  //! Return the cross section at the given energy
  virtual double getCrossSection( const double energy ) const;

  //! Return the cross section at the given energy (efficient)
  virtual double getCrossSection( const double energy,
                                  const unsigned bin_index ) const;

  //! Return the max energy
  double getMaxEnergy() const;

  //! Return the threshold energy
  double getThresholdEnergy() const;

protected:

  //! Return the head of the energy grid
  const double* getEnergyGridHead() const;

private:

  // The processed incoming energy grid
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The processed cross section values evaluated on the incoming e. grid
  Teuchos::ArrayRCP<const double> d_cross_section;

  // The threshold energy
  unsigned d_threshold_energy_index;

  // The hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> d_grid_searcher;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardGenericAtomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_GENERIC_ATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardGenericAtomicReaction.hpp
//---------------------------------------------------------------------------//

