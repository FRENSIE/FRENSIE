//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointFreeGasElasticSAlphaBetaFunction.hpp
//! \author Eli Moll
//! \brief  Free gas elastic scattering S(alpha,beta) function decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_FREE_GAS_ELASTIC_S_ALPHA_BETA_FUNCTION_HPP
#define DATA_GEN_ADJOINT_FREE_GAS_ELASTIC_S_ALPHA_BETA_FUNCTION_HPP

// Boost Includes
#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/multiprecision/float128.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>


// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringAngularDistribution.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace DataGen{

//! The free gas elastic s(alpha,beta) function
class AdjointFreeGasElasticSAlphaBetaFunction
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
  AdjointFreeGasElasticSAlphaBetaFunction(
	  const std::shared_ptr<Utility::UnivariateDistribution>& 
	  zero_temp_elastic_cross_section,
          const std::shared_ptr<MonteCarlo::NuclearScatteringAngularDistribution>&
	  cm_scattering_distribution,
	  const double A,
	  const double kT );

  //! Destructor
  ~AdjointFreeGasElasticSAlphaBetaFunction()
  { /* ... */ }
  
  //! Return the atomic weight ratio
  double getAtomicWeightRatio() const;
  
  //! Return the temperature
  double getTemperature() const;

  //! Evaluate the gkq_set factor integrand
  double evaluateIntegrand( const double alpha,
			    const double beta,
			    const double E,
			    const double mu_cm ) const;

  //! Evaluate the function at a desired alpha, beta and E
  double operator()( const double alpha,
		     const double beta,
		     const double E ) const;

private:

  // Calculate the exponential argument constant
  double calculateExpArgConst( const double alpha,
			       const double beta,
			       const double E ) const;

  // Calculate the exponential argument multiplier
  double calculateExpArgMult( const double alpha ) const;

  // Calculate the bessel argument multiplier
  double calculateBesselArgMult( const double alpha,
				 const double beta,
				 const double E ) const;

  // Find the limits to integrate over
  void findLimits( const double alpha,
		   const double beta,
		   const double E,
		   double& lower_limit, 
		   double& upper_limit ) const;

  // Find a CM scattering angle cosine where the function is non-zero
  double findCMScatteringAngleCosineWithNonZeroIntegrandValue(
				        const double alpha,
					const double beta,
					const double E,
					std::list<double>& grid_points ) const;

  // The neutron kinetic energy multiplier
  static double neutron_kinetic_energy_multiplier;

  // The min exponential argument that can be used before returning zero
  static double min_exp_arg;

  // The integration gkq_set
  Utility::GaussKronrodIntegrator<double> d_gkq_set;

  // The zero temperature cross section
  std::shared_ptr<Utility::UnivariateDistribution> d_zero_temp_elastic_cross_section;

  // The cm scattering angle PDF
  std::shared_ptr<MonteCarlo::NuclearScatteringAngularDistribution>
  d_cm_scattering_distribution;

  // The atomic weight ratio
  double d_A;

  // The temperature (MeV)
  double d_kT;

  // The average zero temperature cross section
  double d_average_zero_temp_elastic_cross_section;

  double d_jacobian_normalization;
};

} // end DataGen namespace

#endif // end DATA_GEN_FREE_GAS_ELASTIC_S_ALPHA_BETA_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointFreeGasElasticSAlphaBetaFunction.hpp
//---------------------------------------------------------------------------//
