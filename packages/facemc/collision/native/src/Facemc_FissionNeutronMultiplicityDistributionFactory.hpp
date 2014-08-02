//---------------------------------------------------------------------------//
//!
//! \file   Facemc_FissionNeutronMultiplicityDistributionFactory.hpp
//! \author Alex Robinson
//! \brief  The fission neutron multiplicity distribution factory class decl
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_FACTORY_HPP
#define FACEMC_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "Facemc_FissionNeutronMultiplicityDistribution.hpp"
#include "Utility_OneDDistribution.hpp"

namespace Facemc{

//! The fission neutron multiplicity distribution factory
class FissionNeutronMultiplicityDistributionFactory
{

public:
  
  //! Constructor
  FissionNeutronMultiplicityDistributionFactory( 
			   const std::string& table_name,
			   const Teuchos::ArrayView<const double>& nu_block,
			   const Teuchos::ArrayView<const double>& dnu_block );

  //! Destructor
  ~FissionNeutronMultiplicityDistributionFactory()
  { /* ... */ }

  //! Create the fission neutron multiplicity distribution
  void createDistribution( 
    Teuchos::RCP<FissionNeutronMultiplicityDistribution>& distribution ) const;

protected:
  
  //! Create the partial distribution from a raw distribution array
  void createPartialDistribution( 
	 const std::string& table_name,
	 const Teuchos::ArrayView<const double>& distribution_array,
	 Teuchos::RCP<Utility::OneDDistribution>& partial_distribution ) const;

private:

  // The prompt multiplicity distribution exists
  bool d_prompt_dist_exists;

  // The delayed multiplicity distribution exists
  bool d_delayed_dist_exists;

  // The total multiplicity distribution exists
  bool d_total_dist_exists;

  // The prompt multiplicity distribution
  Teuchos::RCP<Utility::OneDDistribution> d_prompt_multiplicity_distribution;

  // The delayed multiplicity distribution
  Teuchos::RCP<Utility::OneDDistribution> d_delayed_multiplicity_distribution;

  // The total multiplicity distribution
  Teuchos::RCP<Utility::OneDDistribution> d_total_multiplicity_distribution;
};

} // end Facemc namespace

#endif // end FACEMC_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Facemc_FissionNeutronMultiplicityDistributionFactory.hpp
//---------------------------------------------------------------------------//
