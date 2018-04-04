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

  //! The trials counter type
  typedef CoherentScatteringDistribution::Counter Counter;

  //! Constructor
  BasicCoherentScatteringDistribution(
                                const std::shared_ptr<const FormFactorSquared>&
                                form_factor_function_squared );

  //! Destructor
  ~BasicCoherentScatteringDistribution()
  { /* ... */ }

private:

  // Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
				  double& scattering_angle_cosine,
				  Counter& trials ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BASIC_COHERENT_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BasicCoherentScatteringDistribution.hpp
//---------------------------------------------------------------------------//
