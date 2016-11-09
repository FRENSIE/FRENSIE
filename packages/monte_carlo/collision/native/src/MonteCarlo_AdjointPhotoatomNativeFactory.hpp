//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom native factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTOATOM_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ADJOINT_PHOTOATOM_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatom.hpp"
#include "MonteCarlo_AdjointPhotoatomCore.hpp"
#include "MonteCarlo_IncoherentAdjointModelType.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The adjoint photoatomic factory class that uses native data
class AdjointPhotoatomNativeFactory
{

private:

  // Typedef for this type
  typedef AdjointPhotoatomNativeFactory ThisType;

public:

  //! Create an adjoint photoatom core
  static void createAdjointPhotoatomCore(
                const Data::AdjointElectronPhotonRelaxationDataContainer&
                raw_adjoint_photoatom_data,
                Teuchos::RCP<AdjointPhotoatomCore>& adjoint_photoatom_core,
                const double max_energy,
                const unsigned hash_grid_bins,
                const IncoherentAdjointModelType incoherent_adjoint_model,
                const Teuchos::Array<double>& user_critical_line_energies );

  //! Create an adjoint photoatom
  static void createAdjointPhotoatom(
                const Data::AdjointElectronPhotonRelaxationDataContainer&
                raw_adjoint_photoatom_data,
                const std::string& adjoint_photoatom_name,
                const double atomic_weight,
                Teuchos::RCP<AdjointPhotoatom>& adjoint_photoatom,
                const double max_energy,
                const unsigned hash_grid_bins,
                const IncoherentAdjointModelType incoherent_adjoint_model,
                const Teuchos::Array<double>& user_critical_line_energies );

protected:

  //! Add critical line energyies based on available reactions
  static Teuchos::ArrayRCP<const double> addCriticalLineEnergies(
                   const Data::AdjointElectronPhotonRelaxationDataContainer&
                   raw_adjoint_photoatom_data,
                   const double max_energy,
                   const Teuchos::Array<double>& user_critical_line_energies );
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTOATOM_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomNativeFactory.hpp
//---------------------------------------------------------------------------//
