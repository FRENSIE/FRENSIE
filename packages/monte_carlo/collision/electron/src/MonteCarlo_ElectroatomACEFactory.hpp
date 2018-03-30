//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomACEFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatom ace factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_ACE_FACTORY_HPP
#define MONTE_CARLO_ELECTROATOM_ACE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_ElectroatomCore.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The Electroatomic factory class that uses ACE data
class ElectroatomACEFactory
{

public:

  //! Create a electroatom core (using the provided atomic relaxation model)
  static void createElectroatomCore(
            const Data::XSSEPRDataExtractor& raw_electroatom_data,
            const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
            const SimulationElectronProperties& properties,
            std::shared_ptr<const ElectroatomCore>& electroatom_core );

  //! Create a electroatom (using the provided atomic relaxation model)
  static void createElectroatom(
            const Data::XSSEPRDataExtractor& raw_electroatom_data,
            const std::string& electroatom_name,
            const double atomic_weight,
            const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
            const SimulationElectronProperties& properties,
            std::shared_ptr<const Electroatom>& electroatom );

private:

  // Constructor
  ElectroatomACEFactory();
};

} // end MonteCarlo

#endif // end MONTE_CARLO_ELECTROATOM_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomACEFactory.hpp
//---------------------------------------------------------------------------//
