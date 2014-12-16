//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomicReactionACEFactory.hpp
//! \author Alex Robinson
//! \brief  The incoherent photoatomic reaction ACE data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOMIC_REACTION_ACE_FACTORY_HPP
#define MONTE_CARLO_PHOTOATOMIC_REACTION_ACE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The incoherent photoatomic reaction factory class that uses ACE data
class PhotoatomicReactionACEFactory
{

public:

  //! Create an incoherent scattering photoatomic reaction
  static void createIncoherentReaction(
			const Data::XSSEPRDataExtractor& raw_photoatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
			Teuchos::RCP<PhotoatomicReaction>& incoherent_reaction,
			const bool use_doppler_broadening_data );

  //! Create a coherent scattering photoatomic reaction
  static void createCoherentReaction(
			const Data::XSSEPRDataExtractor& raw_photoatom_data,
			const Teuchos::ArrayRCP<const double>& energy_grid,
			Teuchos::RCP<PhotoatomicReaction>& coherent_reaction );

  //! Create a pair production photoatomic reaction
  static void createPairProductionReaction(
		   const Data::XSSEPRDataExtractor& raw_photoatom_data,
		   const Teuchos::ArrayRCP<const double>& energy_grid,
		   Teuchos::RCP<PhotoatomicReaction>& pair_production_reaction,
		   const bool use_detailed_pair_production_data );

  //! Create the total photoelectric photoatomic reaction
  static void createTotalPhotoelectricReaction(
		   const Data::XSSEPRDataExtractor& raw_photoatom_data,
		   const Teuchos::ArrayRCP<const double>& energy_grid,
		   Teuchos::RCP<PhotoatomicReaction>& photoelectric_reaction );

  //! Create the subshell photoelectric photoatomic reactions
  static void createSubshellPhotoelectricReactions(
		const Data::XSSEPRDataExtractor& raw_photoatom_data,
		const Teuchos::ArrayRCP<const double>& energy_grid,
		Teuchos::Array<Teuchos::RCP<PhotoatomicReaction> >&
		subshell_photoelectric_reactions );

  //! Create the heating photoatomic reaction
  static void createHeatingReaction(
		   const Data::XSSEPRDataExtractor& raw_photoatom_data,
		   const Teuchos::ArrayRCP<const double>& energy_grid,
		   Teuchos::RCP<PhotoatomicReaction>& heating_reaction );

protected:
  
  //! Remove the zeros from a processed cross section
  static void removeZerosFromProcessedCrossSection(
		     const Teuchos::ArrayRCP<const double>& energy_grid,
		     const Teuchos::ArrayView<const double>& raw_cross_section,
		     Teuchos::ArrayRCP<double>& cross_section,
		     unsigned& threshold_energy_index );

private:

  // Check if a value is not equal to zero
  static bool notEqualZero( double value );

  // Constructor
  PhotoatomicReactionACEFactory();
};

// Check if a value is not equal to zero
inline bool PhotoatomicReactionACEFactory::notEqualZero( double value )
{
  return value != 0.0;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOMIC_REACTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomicReactionACEFactory.hpp
//---------------------------------------------------------------------------//
