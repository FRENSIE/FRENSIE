//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomACEFactory.hpp
//! \author Alex Robinson
//! \brief  The photoatom ace factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOM_ACE_FACTORY_HPP
#define MONTE_CARLO_PHOTOATOM_ACE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Photoatom.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The Photoatomic factory class that uses ACE data
class PhotoatomACEFactory
{

public:

  //! Create a photoatom (and store the atomic relaxation model)
  static void createPhotoatom( 
                  const XSSEPRDataExtractor& raw_photoatom_data,
		  Teuchos::RCP<Photoatom>& photoatom,
		  Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
		  const bool use_doppler_broadening_data,
		  const bool use_atomic_relaxation_data );

  //! Create a photoatom (using the provided atomic relaxation model)
  static void createPhotomatom(
            const raw_photoatom_data& raw_photoatom_data,
	    Teuchos::RCP<Photoatom>& photoatom,
	    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	    const bool use_doppler_broadening_data );
private:

  //! Create the subshell relaxation models
  static void createSubshellRelaxationModels(
		  const Teuchos::Array<SubshellType>& subshell_designators,
		  const Teuchos::ArrayView<const double>& subshell_transitions,
		  const Teuchos::ArrayView<const double>& relo_block,
		  const Teuchos::ArrayView<const double>& xprob_block,
		  Teuchos::Array<Teuchos::RCP<SubshellRelaxationModel> >&
		  subshell_relaxation_models );

  // Constructor
  PhotoatomACEFactory();
};

} // end MonteCarlo

#endif // end MONTE_CARLO_PHOTOATOM_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomACEFactory.hpp
//---------------------------------------------------------------------------//
