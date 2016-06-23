//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclideACEFactory_SAlphaBeta.hpp
//! \author Eli Moll
//! \brief  The S(a,b) nuclide ace factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLIDE_ACE_FACTORY_SALPHABETA_HPP
#define MONTE_CARLO_NUCLIDE_ACE_FACTORY_SALPHABETA_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclideACEFactory.hpp"

namespace MonteCarlo{

namespace MonteCarlo{

//! The S(a,b) nuclide factory class that uses ACE data
class NuclideACeFactory_SAlphaBeta : public NuclideACEFactory
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
			 Teuchos::RCP<Nuclide>& nuclide,
			 const bool use_unresolved_resonance_data,
			 const bool use_photon_production_data,
			 const Data::XSSSabDataExtractor& raw_sab_data );

private:

  // Constructor
  NuclideACEFactory_SAlphaBeta();
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLIDE_ACE_FACTORY_SALPHABETA_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclideACEFactory_SAlphaBeta.hpp
//---------------------------------------------------------------------------//
