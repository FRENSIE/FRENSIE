//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EfficientCoherentScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The efficient scattering distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_EFFICIENT_COHERENT_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_EFFICIENT_COHERENT_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistribution.hpp"

namespace MonteCarlo{

/*! The efficient coherent scattering distribution class
 * \details The sampling routines use the efficient method outlined by
 * Persliden.
 */
class EfficientCoherentScatteringDistribution : public CoherentScatteringDistribution
{

public:

  //! Constructor
  EfficientCoherentScatteringDistribution(
		    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    form_factor_function_squared );

  //! Destructor
  ~EfficientCoherentScatteringDistribution()
  { /* ... */ }

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
	       double& outgoing_energy,
	       double& scattering_angle_cosine,
	       SubshellType& shell_of_interaction ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      SubshellType& shell_of_interaction,
			      unsigned& trials ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_EFFICIENT_COHERENT_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EfficientCoherentScatteringDistribution.hpp
//---------------------------------------------------------------------------//
