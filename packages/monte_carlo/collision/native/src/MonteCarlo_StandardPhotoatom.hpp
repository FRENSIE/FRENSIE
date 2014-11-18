//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardPhotoatom.hpp
//! \author Alex Robinson
//! \brief  The standard photoatom class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PHOTOATOM_HPP
#define MONTE_CARLO_STANDARD_PHOTOATOM_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Photoatom.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_AbsorptionPhotoatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_PhotoatomicReactionType.hpp"

namespace MonteCarlo{

/*! The standard photoatom class
 * \details Use the InterpPolicy template parameter and the 
 * process_cross_section template parameter to customize the behavior of
 * this class. Raw cross section data from the EPDL library would use
 * a LogLog policy with processed_cross_section = false. Processed cross
 * section data from an ACE library would use a LogLog policy with
 * processed_cross_section = true. When data is processed, the policy is
 * used to indicate how the data was processed.
 */
template<typename InterpPolicy, bool processed_cross_section = true>
class StandardPhotoatom : public Photoatom
{
  
public:
  
  //! Constructor 
  StandardPhotoatom(
	  const std::string& name,
	  const unsigned atomic_number,
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const Photoatom::ReactionMap& standard_scattering_reactions,
	  const Photoatom::ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model );

  //! Destructor
  ~StandardPhotoatom()
  { /* ... */ }

  //! Return the total cross section at the desired energy
  double getTotalCrossSection( const double energy ) const;

  //! Return the total absorption cross section at the desired energy
  double getAbsorptionCrossSection( const double energy ) const;

private:

  // Calculate the total absorption cross section
  void calculateTotalAbsorptionCrossSection(
				const Teuchos::ArrayRCP<double>& energy_grid );

  // Calculate the processed total absorption cross section
  void calculateProcessedTotalAbsorptionCrossSection(
			        const Teuchos::ArrayRCP<double>& energy_grid );

  // Calculate the total cross section
  void calculateTotalCrossSection( 
				const Teuchos::ArrayRCP<double>& energy_grid );
  
  // Calculate the processed total absorption cross section
  void calculateProcessedTotalCrossSection(
				const Teuchos::ArrayRCP<double>& energy_grid );

  // The total reaction
  Teuchos::RCP<PhotoatomicReaction> d_total_reaction;
  
  // The total absorption reaction
  Teuchos::RCP<PhotoatomicReaction> d_total_absorption_reaction;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardPhotoatom_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_PHOTOATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardPhotoatom.hpp
//---------------------------------------------------------------------------//
