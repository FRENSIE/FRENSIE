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
	 Teuchos::RCP<PhotoatomCore>& photoatom_core,
	 const unsigned hash_grid_bins,
	 const double min_problem_energy,
	 const double max_problem_energy,
	 const bool use_impulse_approximation_data,
	 const bool use_doppler_broadening_data,
	 const bool use_detailed_pair_production_data,
	 const bool use_atomic_relaxation_data );

  //! Create a photoatom (using the provided atomic relaxation model)
  static void createPhotoatom(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 const std::string& photoatom_name,
	 const double atomic_weight,
	 const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	 Teuchos::RCP<Photoatom>& photoatom,
	 const unsigned hash_grid_bins,
	 const double min_problem_energy,
	 const double max_problem_energy,
	 const bool use_impulse_approximation_data,
	 const bool use_doppler_broadening_data,
	 const bool use_detailed_pair_production_data,
	 const bool use_atomic_relaxation_data );

private:

  // Constructor
  PhotoatomNativeFactory();
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOM_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomNativeFactory.hpp
//---------------------------------------------------------------------------//
