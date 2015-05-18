//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.hpp
//! \author Alex Robinson
//! \brief  The incoherent photon scattering distribution ACE factory decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_IncoherentPhotonScatteringDistributionFactory.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

/*! The incoherent photon scattering distribution factory class that uses ACE 
 * data
 */
class IncoherentPhotonScatteringDistributionACEFactory : public IncoherentPhotonScatteringDistributionFactory
{

public:

  //! Create a basic incoherent distribution
  static void createIncoherentDistribution( 
		    const Data::XSSEPRDataExtractor& raw_photoatom_data,
		    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
		    incoherent_distribution,
		    const double kahn_sampling_cutoff_energy );

  //! Create a basic Doppler broadened incoherent distribution
  static void createBasicDopplerBroadenedIncoherentDistribution(
		    const Data::XSSEPRDataExtractor& raw_photoatom_data,
		    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
		    incoherent_distribution,
		    const double kahn_sampling_cutoff_energy );

  //! Create an advanced Doppler broadened incoherent distribution
  static void createAdvancedDopplerBroadenedIncoherentDistribution(
		    const Data::XSSEPRDataExtractor& raw_photoatom_data,
		    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
		    incoherent_distribution,
		    const double kahn_sampling_cutoff_energy );

protected:

  //! Create the scattering function
  static void createScatteringFunction( 
	  const Data::XSSEPRDataExtractor& raw_photoatom_data,
	  Teuchos::RCP<const Utility::OneDDistribution>& scattering_function );

  //! Create the subshell order array
  static void createSubshellOrderArray(
			   const Data::XSSEPRDataExtractor& raw_photoatom_data,
			   Teuchos::Array<SubshellType>& subshell_order );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//

