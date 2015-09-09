//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatom native factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_ElectroatomCore.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "Data_EvaluatedElectronDataContainer.hpp"

namespace MonteCarlo{

//! The Electroatomic factory class that uses Native data
class ElectroatomNativeFactory
{

public:

  //! Create a electroatom core (using the provided atomic relaxation model)
  static void createElectroatomCore( 
	    const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
	    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	    Teuchos::RCP<ElectroatomCore>& electroatom_core,
        const Teuchos::Array<double>& binding_energy,
        const double atomic_weight,
        const BremsstrahlungAngularDistributionType 
                photon_distribution_function,
	    const bool use_atomic_relaxation_data,
        const double cutoff_angle = 1.0e-6 );

  //! Create a electroatom (using the provided atomic relaxation model)
  static void createElectroatom(
	    const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
	    const std::string& electroatom_name,
        const Teuchos::Array<double>& binding_energy,
        const double atomic_weight,
	    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	    Teuchos::RCP<Electroatom>& electroatom,
        const BremsstrahlungAngularDistributionType 
                photon_distribution_function,
	    const bool use_atomic_relaxation_data,
        const double cutoff_angle = 1.0e-6 );
private:

  // Constructor
  ElectroatomNativeFactory();
};

} // end MonteCarlo

#endif // end MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomNativeFactory.hpp
//---------------------------------------------------------------------------//
