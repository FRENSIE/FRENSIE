//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom native factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTOATOM_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ADJOINT_PHOTOATOM_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatom.hpp"
#include "MonteCarlo_AdjointPhotoatomCore.hpp"
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The adjoint photoatomic factory class that uses native data
class AdjointPhotoatomNativeFactory
{
  // Typedef for this type
  typedef AdjointPhotoatomNativeFactory ThisType;

public:

  //! Create an adjoint photoatom core
  static void createAdjointPhotoatomCore(
                const Data::AdjointElectronPhotonRelaxationDataContainer&
                raw_adjoint_photoatom_data,
                const SimulationAdjointPhotonProperties& properties,
                std::shared_ptr<const AdjointPhotoatomCore>& adjoint_photoatom_core );

  //! Create an adjoint photoatom
  static void createAdjointPhotoatom(
                const Data::AdjointElectronPhotonRelaxationDataContainer&
                raw_adjoint_photoatom_data,
                const std::string& adjoint_photoatom_name,
                const double atomic_weight,
                const SimulationAdjointPhotonProperties& properties,
                std::shared_ptr<const AdjointPhotoatom>& adjoint_photoatom );

protected:

  //! Add critical line energyies based on available reactions
  static std::shared_ptr<const std::vector<double> > addCriticalLineEnergies(
                   const Data::AdjointElectronPhotonRelaxationDataContainer&
                   raw_adjoint_photoatom_data,
                   const double max_energy,
                   const std::vector<double>& user_critical_line_energies );
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTOATOM_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomNativeFactory.hpp
//---------------------------------------------------------------------------//
