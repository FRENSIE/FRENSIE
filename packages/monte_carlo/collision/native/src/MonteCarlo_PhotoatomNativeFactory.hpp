//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The photoatom native factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOM_NATIVE_FACTORY_HPP
#define MONTE_CARLO_PHOTOATOM_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Photoatom.hpp"
#include "MonteCarlo_PhotoatomCore.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The photoatomic factory class that uses native data
class PhotoatomNativeFactory
{

public:

  //! Create a photoatom core (using the provided atomic relaxation model)
  static void createPhotoatomCore(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
         const SimulationPhotonProperties& properties,
	 Teuchos::RCP<PhotoatomCore>& photoatom_core );

  //! Create a photoatom (using the provided atomic relaxation model)
  static void createPhotoatom(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 const std::string& photoatom_name,
	 const double atomic_weight,
	 const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
         const SimulationPhotonProperties& properties,
	 Teuchos::RCP<Photoatom>& photoatom );

private:

  // Constructor
  PhotoatomNativeFactory();
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOM_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomNativeFactory.hpp
//---------------------------------------------------------------------------//
