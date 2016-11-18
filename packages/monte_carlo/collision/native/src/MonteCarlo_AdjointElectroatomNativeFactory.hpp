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
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_Array.hpp>

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

private:

  // Typedef for this type
  typedef AdjointElectroatomNativeFactory ThisType;

public:

  //! Create an adjoint electroatom core
  static void createAdjointElectroatomCore(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        Teuchos::RCP<AdjointElectroatomCore>& adjoint_electroatom_core,
        const double cutoff_angle_cosine,
        const unsigned hash_grid_bins );

  //! Create an adjoint  electroatom
  static void createAdjointElectroatom(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const std::string& adjoint_electroatom_name,
        const double atomic_weight,
        Teuchos::RCP<AdjointElectroatom>& adjoint_electroatom,
        const double cutoff_angle_cosine,
        const unsigned hash_grid_bins );
};

} // end MonteCarlo

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomNativeFactory.hpp
//---------------------------------------------------------------------------//
