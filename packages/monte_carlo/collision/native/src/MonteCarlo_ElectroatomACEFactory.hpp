//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomACEFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatom ace factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_ACE_FACTORY_HPP
#define MONTE_CARLO_ELECTROATOM_ACE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_ElectroatomCore.hpp"
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The Electroatomic factory class that uses ACE data
class ElectroatomACEFactory
{

public:

  //! Create a electroatom core (using the provided atomic relaxation model)
  static void createElectroatomCore(
	    const Data::XSSEPRDataExtractor& raw_electroatom_data,
	    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	    Teuchos::RCP<ElectroatomCore>& electroatom_core,
	    const unsigned hash_grid_bins,
        const BremsstrahlungAngularDistributionType
                photon_distribution_function,
	    const bool use_atomic_relaxation_data,
        const double cutoff_angle_cosine = 1.0 );

  //! Create a electroatom (using the provided atomic relaxation model)
  static void createElectroatom(
	    const Data::XSSEPRDataExtractor& raw_electroatom_data,
	    const std::string& electroatom_name,
        const double atomic_weight,
	    const unsigned hash_grid_bins,
	    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	    Teuchos::RCP<Electroatom>& electroatom,
        const BremsstrahlungAngularDistributionType
                photon_distribution_function,
	    const bool use_atomic_relaxation_data,
        const double cutoff_angle_cosine = 1.0 );

private:

  // Constructor
  ElectroatomACEFactory();
};

} // end MonteCarlo

#endif // end MONTE_CARLO_ELECTROATOM_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomACEFactory.hpp
//---------------------------------------------------------------------------//
