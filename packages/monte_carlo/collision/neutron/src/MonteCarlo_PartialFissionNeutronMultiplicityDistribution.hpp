//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PartialFissionNeutronMultiplicityDistribution.hpp
//! \author Alex Robinson
//! \brief  The partial fission neutron multiplicity distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTIAL_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_HPP
#define MONTE_CARLO_PARTIAL_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_FissionNeutronMultiplicityDistribution.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace MonteCarlo{

//! The partial fission neutron multiplicity distribution class
template<typename FissionNeutronMultiplicityDistributionPolicy>
class PartialFissionNeutronMultiplicityDistribution : public FissionNeutronMultiplicityDistribution
{

public:

  //! Constructor (prompt and total)
  PartialFissionNeutronMultiplicityDistribution(
		  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  first_multiplicity_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  second_multiplicity_distribution );
  
  //! Destructor
  ~PartialFissionNeutronMultiplicityDistribution()
  { /* ... */ }

  //! Return the average number of neutrons emitted
  double getAverageNumberOfEmittedNeutrons( const double energy) const final override;

  //! Return the average number of prompt neutrons emitted
  double getAverageNumberOfPromptNeutrons( const double energy ) const final override;

  //! Return the average number of delayed neutrons emitted
  double getAverageNumberOfDelayedNeutrons( const double energy) const final override;

private:

  // The first multiplicity distribution
  std::shared_ptr<const Utility::UnivariateDistribution>
  d_first_multiplicity_distribution;

  // The second multiplicity distribution
  std::shared_ptr<const Utility::UnivariateDistribution>
  d_second_multiplicity_distribution;
};

//! The prompt-total policy
struct PromptTotalFissionNeutronMultiplicityPolicy
{
  //! Return the total nu-bar
  static inline double getTotalNuBar(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_prompt_multiplicity_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_total_multiplicity_distribution,
                  const double energy )
  {
    return d_total_multiplicity_distribution->evaluate( energy );
  }

  //! Return the prompt nu-bar
  static inline double getPromptNuBar(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_prompt_multiplicity_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_total_multiplicity_distribution,
                  const double energy )
  {
    return d_prompt_multiplicity_distribution->evaluate( energy );
  }

  //! Return the delayed nu-bar
  static inline double getDelayedNuBar(
		  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_prompt_multiplicity_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_total_multiplicity_distribution,
                  const double energy )
  {
    return d_total_multiplicity_distribution->evaluate( energy ) -
      d_prompt_multiplicity_distribution->evaluate( energy );
  }
};

//! The delayed-total policy
struct DelayedTotalFissionNeutronMultiplicityPolicy
{
  //! Return the total nu-bar
  static inline double getTotalNuBar(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_delayed_multiplicity_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_total_multiplicity_distribution,
                  const double energy )
  {
    return d_total_multiplicity_distribution->evaluate( energy );
  }

  //! Return the prompt nu-bar
  static inline double getPromptNuBar(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_delayed_multiplicity_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_total_multiplicity_distribution,
                              const double energy )
  {
    return d_total_multiplicity_distribution->evaluate( energy ) -
      d_delayed_multiplicity_distribution->evaluate( energy );
  }

  //! Return the delayed nu-bar
  static inline double getDelayedNuBar(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_delayed_multiplicity_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_total_multiplicity_distribution,
                  const double energy )
  {
    return d_delayed_multiplicity_distribution->evaluate( energy );
  }
};

//! The delayed-prompt policy
struct DelayedPromptFissionNeutronMultiplicityPolicy
{
  //! Return the total nu-bar
  static inline double getTotalNuBar(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_delayed_multiplicity_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_prompt_multiplicity_distribution,
                  const double energy )
  {
    return d_delayed_multiplicity_distribution->evaluate( energy ) +
      d_prompt_multiplicity_distribution->evaluate( energy );
  }

  //! Return the prompt nu-bar
  static inline double getPromptNuBar(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_delayed_multiplicity_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_prompt_multiplicity_distribution,
                  const double energy )
  {
    return d_prompt_multiplicity_distribution->evaluate( energy );
  }

  //! Return the delayed nu-bar
  static inline double getDelayedNuBar(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_delayed_multiplicity_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  d_prompt_multiplicity_distribution,
                  const double energy )
  {
    return d_delayed_multiplicity_distribution->evaluate( energy );
  }
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_PartialFissionNeutronMultiplicityDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTIAL_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PartialFissionNeutronMultiplicityDistribution.hpp
//---------------------------------------------------------------------------//
