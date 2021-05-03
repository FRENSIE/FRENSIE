//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SAlphaBetaNuclideACEFactory.hpp
//! \author Eli Moll
//! \brief  The S(alpha,beta) nuclide ace factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_S_ALPHA_BETA_NUCLIDE_ACE_FACTORY_HPP
#define MONTE_CARLO_S_ALPHA_BETA_NUCLIDE_ACE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_Nuclide.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Data_XSSSabDataExtractor.hpp"

namespace MonteCarlo{

//! The nuclide factory class that uses ACE data
class SAlphaBetaNuclideACEFactory
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
			 std::shared_ptr<Nuclide>& nuclide,
			 const bool use_unresolved_resonance_data,
			 const bool use_photon_production_data,
			 const std::string& sab_alias,
			 const Data::XSSSabDataExtractor& sab_nuclide_data,
			 const SimulationProperties& properties  );

private:

  // Constructor
  SAlphaBetaNuclideACEFactory();
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLIDE_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclideACEFactory.hpp
//---------------------------------------------------------------------------//
