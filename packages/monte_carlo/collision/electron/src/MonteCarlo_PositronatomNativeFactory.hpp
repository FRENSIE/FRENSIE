//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The positron-atom native factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONATOM_NATIVE_FACTORY_HPP
#define MONTE_CARLO_POSITRONATOM_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_Positronatom.hpp"
#include "MonteCarlo_PositronatomCore.hpp"
#include "MonteCarlo_PositronatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"

namespace MonteCarlo{

//! The Positronatomic factory class that uses Native data
class PositronatomNativeFactory
{

public:

  using ThisType = PositronatomNativeFactory;

  //! Create a positron-atom core (using the provided atomic relaxation model)
  template <typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createPositronatomCore(
   const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
   const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
   const SimulationElectronProperties& properties,
   std::shared_ptr<const PositronatomCore>& positronatom_core );
  
  //! Create a positron-atom (using the provided atomic relaxation model)
  static void createPositronatom(
   const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
   const std::string& positronatom_name,
   const double atomic_weight,
   const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
   const SimulationElectronProperties& properties,
   std::shared_ptr<const Positronatom>& positronatom );

private:

  //! Create the elastic reaction for a positron-atom core
  template <typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createElasticPositronatomCore(
      const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      const SimulationElectronProperties& properties,
      Positronatom::ConstReactionMap& scattering_reactions );

  // Constructor
  PositronatomNativeFactory();
};

} // end MonteCarlo

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_PositronatomNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_POSITRONATOM_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomNativeFactory.hpp
//---------------------------------------------------------------------------//
