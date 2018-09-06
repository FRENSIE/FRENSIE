//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatom native factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_ElectroatomCore.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The Electroatomic factory class that uses Native data
class ElectroatomNativeFactory
{

public:

  using ThisType = ElectroatomNativeFactory;

  //! Create a electroatom core (using the provided atomic relaxation model)
  template <typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createElectroatomCore(
       const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
       const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
       const SimulationElectronProperties& properties,
       std::shared_ptr<const ElectroatomCore>& electroatom_core );

  //! Create a electroatom (using the provided atomic relaxation model)
  static void createElectroatom(
       const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
       const std::string& electroatom_name,
       const double atomic_weight,
       const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
       const SimulationElectronProperties& properties,
       std::shared_ptr<const Electroatom>& electroatom );

private:

  //! Create the elastic reaction for a electroatom core
  template <typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createElasticElectroatomCore(
        const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const std::shared_ptr<const std::vector<double> >& energy_grid,
        const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
        const SimulationElectronProperties& properties,
        Electroatom::ConstReactionMap& scattering_reactions );

  // Constructor
  ElectroatomNativeFactory();
};

} // end MonteCarlo

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElectroatomNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomNativeFactory.hpp
//---------------------------------------------------------------------------//
