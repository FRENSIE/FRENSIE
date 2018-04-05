//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclideACEFactory.hpp
//! \author Alex Robinson
//! \brief  The nuclide ace factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLIDE_ACE_FACTORY_HPP
#define MONTE_CARLO_NUCLIDE_ACE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_Nuclide.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

namespace MonteCarlo{

//! The nuclide factory class that uses ACE data
class NuclideACEFactory
{

public:

  //! Create a nuclide
  static void createNuclide(
			 const Data::XSSNeutronDataExtractor& raw_nuclide_data,
			 const std::string& nuclide_alias,
			 const unsigned atomic_number,
			 const unsigned atomic_mass_number,
			 const unsigned isomer_number,
			 const double atomic_weight_ratio,
			 const double temperature,
                         const SimulationProperties& properties,
			 std::shared_ptr<Nuclide>& nuclide,
                         std::ostream* os_message = &std::cerr );

private:

  // Constructor
  NuclideACEFactory();
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLIDE_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclideACEFactory.hpp
//---------------------------------------------------------------------------//
