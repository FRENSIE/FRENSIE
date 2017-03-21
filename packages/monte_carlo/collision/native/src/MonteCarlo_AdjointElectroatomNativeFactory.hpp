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
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"

namespace MonteCarlo{

//! The AdjointElectroatomic factory class that uses Native data
class AdjointElectroatomNativeFactory
{

private:

  // Typedef for this type
  typedef AdjointElectroatomNativeFactory ThisType;

public:

  //! Create an adjoint electroatom core
  template <typename SecondInterpPolicy = Utility::LinLinLog>
  static void createAdjointElectroatomCore(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const SimulationElectronProperties& properties,
        Teuchos::RCP<AdjointElectroatomCore>& adjoint_electroatom_core );

  //! Create an adjoint  electroatom
  static void createAdjointElectroatom(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const std::string& adjoint_electroatom_name,
        const double atomic_weight,
        const SimulationElectronProperties& properties,
        Teuchos::RCP<AdjointElectroatom>& adjoint_electroatom );
};

} // end MonteCarlo

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AdjointElectroatomNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomNativeFactory.hpp
//---------------------------------------------------------------------------//
