//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FreeGasElasticScatteringKernelFactor.hpp
//! \author Alex Robinson
//! \brief  Free gas elastic scattering gkq_set factor decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_FREE_GAS_ELASTIC_SCATTERING_KERNEL_FACTOR_HPP
#define DATA_GEN_FREE_GAS_ELASTIC_SCATTERING_KERNEL_FACTOR_HPP

// Boost Includes
#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/multiprecision/float128.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringAngularDistribution.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace DataGen{

//! The free gas elastic scattering gkq_set factor class
class FreeGasElasticScatteringKernelFactor
{
  
private:

  // Typedef for bessel function error policy
  typedef boost::math::policies::domain_error<
    boost::math::policies::throw_on_error> domain_error;
  typedef boost::math::policies::pole_error<
    boost::math::policies::throw_on_error> pole_error;
  typedef boost::math::policies::overflow_error<
    boost::math::policies::throw_on_error> overflow_error;
  typedef boost::math::policies::evaluation_error<
    boost::math::policies::throw_on_error> evaluation_error;
  
  typedef boost::math::policies::policy<
    domain_error,
    pole_error,
    overflow_error,
    evaluation_error> Policy;
  
  // Typedef for extended precision floating point values
  typedef boost::multiprecision::float128 BoostLongDouble;

public:

  //! Constructor
  FreeGasElasticScatteringKernelFactor( 
	  const Teuchos::RCP<Utility::OneDDistribution>& 
	  zero_temp_elastic_cross_section,
          const Teuchos::RCP<MonteCarlo::NuclearScatteringAngularDistribution>&
	  cm_scattering_distribution,
	  const double A,
	  const double kT,
	  const double alpha,
	  const double beta,
	  const double E );
  
  //! Destructor
  ~FreeGasElasticScatteringKernelFactor()
  { /* ... */ }

  //! Set the alpha, beta, and energy values
  void setIndependentVariables( const double alpha,
				const double beta,
				const double E );

  //! Evaluate the factor at a desired value of the center-of-mass angle cosine
  double operator()( const double mu_cm ) const;

  //! Get the integrated value (over all mu_cm => [-1,1])
  double getIntegratedValue( double& error_estimate ) const;

private:

  // Calculate the cached values
  void calculateCachedValues();

  // Find limits to integrate over
  void findLimits( double& lower_limit, double& upper_limit ) const;

  // Find a CM scattering angle cosine where the function is non-zero
  double findCMScatteringAngleCosineWithNonZeroFunctionValue(
					std::list<double>& grid_points ) const;

  // The neutron kinetic energy multiplier
  static double neutron_kinetic_energy_multiplier;

  // The min exponential argument that can be used before returning zero
  static double min_exp_arg;

  // The integration gkq_set
  Utility::GaussKronrodIntegrator<double> d_gkq_set;

  // The zero temperature cross section
  Teuchos::RCP<Utility::OneDDistribution> d_zero_temp_elastic_cross_section;

  // The cm scattering angle PDF
  Teuchos::RCP<MonteCarlo::NuclearScatteringAngularDistribution>
  d_cm_scattering_distribution;

  // The atomic weight ratio
  double d_A;

  // The temperature value (MeV)
  double d_kT;

  // The alpha value
  double d_alpha;

  // The beta value
  double d_beta;

  // The energy value (MeV)
  double d_E;

  // Cached energy ratio
  double d_energy_ratio;

  // Cached exponential argument multiplier
  double d_exponential_arg_mult;

  // Cached exponential arg constant
  double d_exponential_arg_const;

  // Cached bessel argument multiplier
  double d_bessel_arg_mult;

  // Cached relative velocity multiplier
  double d_relative_velocity_mult;
};

} // end DataGen namespace

#endif // end DATA_GEN_FREE_GAS_ELASTIC_SCATTERING_KERNEL_FACTOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_FreeGasElasticScatteringKernelFactor.hpp
//---------------------------------------------------------------------------//
