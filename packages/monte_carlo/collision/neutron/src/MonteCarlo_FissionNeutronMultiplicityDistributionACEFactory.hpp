//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FissionNeutronMultiplicityDistributionACEFactory.hpp
//! \author Alex Robinson
//! \brief  The fission neutron multiplicity distribution factory class decl
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_FissionNeutronMultiplicityDistribution.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_ArrayView.hpp"

namespace MonteCarlo{

//! The fission neutron multiplicity distribution factory
class FissionNeutronMultiplicityDistributionACEFactory
{

public:

  //! Constructor
  FissionNeutronMultiplicityDistributionACEFactory(
			   const std::string& table_name,
			   const Utility::ArrayView<const double>& nu_block,
			   const Utility::ArrayView<const double>& dnu_block );

  //! Destructor
  ~FissionNeutronMultiplicityDistributionACEFactory()
  { /* ... */ }

  //! Create the fission neutron multiplicity distribution
  void createDistribution(
    std::shared_ptr<const FissionNeutronMultiplicityDistribution>& distribution ) const;

protected:

  //! Create the partial distribution from a raw distribution array
  void createPartialDistribution(
	 const std::string& table_name,
	 const Utility::ArrayView<const double>& distribution_array,
	 std::shared_ptr<const Utility::UnivariateDistribution>& partial_distribution ) const;

  //! Return if a prompt distribution exists
  bool doesPromptDistExist() const;

  //! Return if a delayed distribution exists
  bool doesDelayedDistExist() const;

  //! Return if a total distribution exists
  bool doesTotalDistExist() const;

  //! Return the prompt multiplicity distribution
  const std::shared_ptr<const Utility::UnivariateDistribution>& getPromptMultDist() const;

  //! Return the delayed multiplicity distribution
  const std::shared_ptr<const Utility::UnivariateDistribution>& getDelayedMultDist() const;

  //! Return the total multiplicity distribution
  const std::shared_ptr<const Utility::UnivariateDistribution>& getTotalMultDist() const;

private:

  // The prompt multiplicity distribution exists
  bool d_prompt_dist_exists;

  // The delayed multiplicity distribution exists
  bool d_delayed_dist_exists;

  // The total multiplicity distribution exists
  bool d_total_dist_exists;

  // The prompt multiplicity distribution
  std::shared_ptr<const Utility::UnivariateDistribution> d_prompt_multiplicity_distribution;

  // The delayed multiplicity distribution
  std::shared_ptr<const Utility::UnivariateDistribution> d_delayed_multiplicity_distribution;

  // The total multiplicity distribution
  std::shared_ptr<const Utility::UnivariateDistribution> d_total_multiplicity_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FissionNeutronMultiplicityDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
