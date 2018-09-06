//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CompleteFissionNeutronMultiplicityDistribution.hpp
//! \author Alex Robinson
//! \brief  The complete fission neutron multiplicity distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPLETE_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_HPP
#define MONTE_CARLO_COMPLETE_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_FissionNeutronMultiplicityDistribution.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace MonteCarlo{

//! The complete fission neutron multiplicity distribution class
class CompleteFissionNeutronMultiplicityDistribution : public FissionNeutronMultiplicityDistribution
{

public:

  //! Constructor
  CompleteFissionNeutronMultiplicityDistribution(
		  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  prompt_multiplicity_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  delayed_multiplicity_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  total_multiplicity_distribution );
  
  //! Destructor
  ~CompleteFissionNeutronMultiplicityDistribution()
  { /* ... */ }

  //! Return the average number of neutrons emitted
  double getAverageNumberOfEmittedNeutrons( const double energy) const final override;

  //! Return the average number of prompt neutrons emitted
  double getAverageNumberOfPromptNeutrons( const double energy ) const final override;

  //! Return the average number of delayed neutrons emitted
  double getAverageNumberOfDelayedNeutrons( const double energy) const final override;

private:

  // The prompt multiplicity distribution (prompt nu-bar)
  std::shared_ptr<const Utility::UnivariateDistribution> d_prompt_multiplicity_distribution;

  // The delayed multiplicity distribution (delayed nu-bar)
  std::shared_ptr<const Utility::UnivariateDistribution> d_delayed_multiplicity_distribution;

  // The total multiplicity distribution (total nu-bar)
  std::shared_ptr<const Utility::UnivariateDistribution> d_total_multiplicity_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPLETE_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CompleteFissionNeutronMultiplicityDistribution.hpp
//---------------------------------------------------------------------------//
