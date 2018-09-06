//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomACEFactory.hpp
//! \author Luke Kersting
//! \brief  The positron-atom ace factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONATOM_ACE_FACTORY_HPP
#define MONTE_CARLO_POSITRONATOM_ACE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_Positronatom.hpp"
#include "MonteCarlo_PositronatomCore.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The Positronatomic factory class that uses ACE data
class PositronatomACEFactory
{

public:

  //! Create a positron-atom core (using the provided atomic relaxation model)
  static void createPositronatomCore(
         const Data::XSSEPRDataExtractor& raw_positronatom_data,
         const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
         const SimulationElectronProperties& properties,
         std::shared_ptr<const PositronatomCore>& positronatom_core );

  //! Create a positron-atom (using the provided atomic relaxation model)
  static void createPositronatom(
         const Data::XSSEPRDataExtractor& raw_positronatom_data,
         const std::string& positronatom_name,
         const double atomic_weight,
         const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
         const SimulationElectronProperties& properties,
         std::shared_ptr<const Positronatom>& positronatom );

private:

  // Constructor
  PositronatomACEFactory();
};

} // end MonteCarlo

#endif // end MONTE_CARLO_POSITRONATOM_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomACEFactory.hpp
//---------------------------------------------------------------------------//
