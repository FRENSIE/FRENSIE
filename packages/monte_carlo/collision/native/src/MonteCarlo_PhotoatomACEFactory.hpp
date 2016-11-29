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
#include "MonteCarlo_PhotoatomCore.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The Photoatomic factory class that uses ACE data
class PhotoatomACEFactory
{

public:

  //! Create a photoatom core (using the provided atomic relaxation model)
  static void createPhotoatomCore(
	    const Data::XSSEPRDataExtractor& raw_photoatom_data,
	    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
            const SimulationPhotonProperties& properties,
	    Teuchos::RCP<PhotoatomCore>& photoatom_core );

  //! Create a photoatom (using the provided atomic relaxation model)
  static void createPhotoatom(
	    const Data::XSSEPRDataExtractor& raw_photoatom_data,
	    const std::string& photoatom_name,
	    const double atomic_weight,
	    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
            const SimulationPhotonProperties& properties,
	    Teuchos::RCP<Photoatom>& photoatom );
private:

  // Constructor
  PhotoatomACEFactory();
};

} // end MonteCarlo

#endif // end MONTE_CARLO_PHOTOATOM_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomACEFactory.hpp
//---------------------------------------------------------------------------//
