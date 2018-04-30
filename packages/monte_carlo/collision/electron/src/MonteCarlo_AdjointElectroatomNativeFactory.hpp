//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom native factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatom.hpp"
#include "MonteCarlo_AdjointElectroatomCore.hpp"
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_TwoDGridPolicy.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The adjoint electroatom native factory class that uses Native data
class AdjointElectroatomNativeFactory
{
  // Typedef for this type
  typedef AdjointElectroatomNativeFactory ThisType;

public:

  //! Create an adjoint electroatom core
  static void createAdjointElectroatomCore(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const SimulationAdjointElectronProperties& properties,
        std::shared_ptr<const AdjointElectroatomCore>& adjoint_electroatom_core );

  //! Create an adjoint  electroatom
  static void createAdjointElectroatom(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const std::string& adjoint_electroatom_name,
        const double atomic_weight,
        const SimulationAdjointElectronProperties& properties,
        std::shared_ptr<const AdjointElectroatom>& adjoint_electroatom );

private:

  //! Create the elastic reaction for a electroatom core
  template <typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createElasticElectroatomCore(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const std::shared_ptr<const std::vector<double> >& energy_grid,
        const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
        const SimulationAdjointElectronProperties& properties,
        std::shared_ptr<const AdjointElectroatomicReaction>& elastic_reaction,
        AdjointElectroatom::ConstReactionMap& scattering_reactions );
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
