//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FissionNeutronMultiplicityDistributionACEFactory.hpp
//! \author Alex Robinson
//! \brief  The fission neutron multiplicity distribution factory class decl
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_ACE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_FissionNeutronMultiplicityDistribution.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The fission neutron multiplicity distribution factory
class FissionNeutronMultiplicityDistributionACEFactory
{

public:
  
  //! Constructor
  FissionNeutronMultiplicityDistributionACEFactory( 
			   const std::string& table_name,
			   const Teuchos::ArrayView<const double>& nu_block,
			   const Teuchos::ArrayView<const double>& dnu_block );

  //! Destructor
  ~FissionNeutronMultiplicityDistributionACEFactory()
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

  //! Return if a prompt distribution exists
  bool doesPromptDistExist() const;

  //! Return if a delayed distribution exists
  bool doesDelayedDistExist() const;

  //! Return if a total distribution exists
  bool doesTotalDistExist() const;

  //! Return the prompt multiplicity distribution
  const Teuchos::RCP<Utility::OneDDistribution>& getPromptMultDist() const;

  //! Return the delayed multiplicity distribution
  const Teuchos::RCP<Utility::OneDDistribution>& getDelayedMultDist() const;

  //! Return the total multiplicity distribution
  const Teuchos::RCP<Utility::OneDDistribution>& getTotalMultDist() const;

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

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FissionNeutronMultiplicityDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
