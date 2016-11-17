//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom native factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatom.hpp"
#include "MonteCarlo_AdjointElectroatomCore.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The AdjointElectroatomic factory class that uses Native data
class AdjointElectroatomNativeFactory
{

public:

  //! Create a adjoint electroatom core (using the provided atomic relaxation model)
  static void createAdjointElectroatomCore(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
        Teuchos::RCP<AdjointElectroatomCore>& adjoint_electroatom_core,
        const unsigned hash_grid_bins,
        const bool use_atomic_relaxation_data = false,
        const double cutoff_angle_cosine = 1.0 );

  //! Create a electroatom (using the provided atomic relaxation model)
  static void createAdjointElectroatom(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const std::string& electroatom_name,
        const double atomic_weight,
        const unsigned hash_grid_bins,
        const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
        Teuchos::RCP<AdjointElectroatom>& electroatom,
        const bool use_atomic_relaxation_data = false,
        const double cutoff_angle_cosine = 1.0 );
private:

  // Constructor
  AdjointElectroatomNativeFactory();
};

} // end MonteCarlo

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomNativeFactory.hpp
//---------------------------------------------------------------------------//
