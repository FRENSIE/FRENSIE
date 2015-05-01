//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BasicCoherentScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The basic coherent scattering distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BASIC_COHERENT_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_BASIC_COHERENT_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistribution.hpp"

namespace MonteCarlo{

/*! The basic coherent scattering distribution class
 * \details The sampling routines use a probability mixing technique with
 * a rejection function, which is very simple but not very efficient.
 */
class BasicCoherentScatteringDistribution : public CoherentScatteringDistribution
{

public:

  //! Constructor
  BasicCoherentScatteringDistribution(
		    const Teuchos::RCP<const Utility::TabularOneDDistribution>&
		    form_factor_function_squared );

  //! Destructor
  ~BasicCoherentScatteringDistribution()
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

#endif // end MONTE_CARLO_BASIC_COHERENT_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BasicCoherentScatteringDistribution.hpp
//---------------------------------------------------------------------------//
