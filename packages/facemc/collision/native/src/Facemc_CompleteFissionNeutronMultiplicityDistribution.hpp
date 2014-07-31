//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CompleteFissionNeutronMultiplicityDistribution.hpp
//! \author Alex Robinson
//! \brief  The complete fission neutron multiplicity distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_COMPLETE_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_HPP
#define FACEMC_COMPLETE_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Facemc_FissionNeutronMultiplicityDistribution.hpp"
#include "Utility_OneDDistribution.hpp"

namespace Facemc{

//! The complete fission neutron multiplicity distribution class
class CompleteFissionNeutronMultiplicityDistribution : public FissionNeutronMultiplicityDistribution
{
  
public:
  
  //! Constructor
  CompleteFissionNeutronMultiplicityDistribution(
				 const Teuchos::RCP<Utility::OneDDistribution>&
				 prompt_multiplicity_distribution,
				 const Teuchos::RCP<Utility::OneDDistribution>&
				 delayed_multiplicity_distribution,
				 const Teuchos::RCP<Utility::OneDDistribution>&
				 total_multiplicity_distribution );

  //! Destructor
  ~CompleteFissionNeutronMultiplicityDistribution()
  { /* ... */ }

  //! Return the average number of neutrons emitted
  double getAverageNumberOfEmittedNeutrons( const double energy) const;

  //! Return the average number of prompt neutrons emitted
  double getAverageNumberOfPromptNeutrons( const double energy ) const;

  //! Return the average number of delayed neutrons emitted
  double getAverageNumberOfDelayedNeutrons( const double energy) const;

private:

  // The prompt multiplicity distribution (prompt nu-bar)
  Teuchos::RCP<Utility::OneDDistribution> d_prompt_multiplicity_distribution;

  // The delayed multiplicity distribution (delayed nu-bar)
  Teuchos::RCP<Utility::OneDDistribution> d_delayed_multiplicity_distribution;

  // The total multiplicity distribution (total nu-bar)
  Teuchos::RCP<Utility::OneDDistribution> d_total_multiplicity_distribution;  
};

} // end Facemc namespace

#endif // end FACEMC_COMPLETE_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_HPP 

//---------------------------------------------------------------------------//
// end Facemc_CompleteFissionNeutronMultiplicityDistribution.hpp
//---------------------------------------------------------------------------//
