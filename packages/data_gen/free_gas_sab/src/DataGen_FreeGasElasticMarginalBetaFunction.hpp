//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FreeGasElasticMarginalBetaFunction.hpp
//! \author Eli Moll
//! \brief  Free gas elastic marginal beta function declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_FREE_GAS_ELASTIC_MARGINAL_BETA_FUNCTION_HPP
#define DATA_GEN_FREE_GAS_ELASTIC_MARGINAL_BETA_FUNCTION_HPP

// Std Lib Includes
#include <list>

// Boost Includes
#include <boost/function.hpp>

// FRENSIE Includes
#include "DataGen_FreeGasElasticSAlphaBetaFunction.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_Tuple.hpp"

namespace DataGen{

//! The Free gas elastic marginal beta function
class FreeGasElasticMarginalBetaFunction
{

public:

  //! Constructor
  FreeGasElasticMarginalBetaFunction(
	      const std::shared_ptr<Utility::UnivariateDistribution>&
	      zero_temp_elastic_cross_section,
              const std::shared_ptr<MonteCarlo::NuclearScatteringAngularDistribution>&
	      cm_scattering_distribution,
	      const double A,
	      const double kT,
	      const double E );

  //! Destructor
  ~FreeGasElasticMarginalBetaFunction()
  { /* ... */ }

  //! Set the beta and energy values
  void setIndependentVariables( const double E );
  
  //! Get the lower beta limit
  double getBetaMin() const;

  double getBetaMax();
  
  //! Get the normalization constant
  double getNormalizationConstant();

  //! Evaluate the marginal PDF
  double operator()( const double beta );

  //! Evaluate the marginal CDF
  double evaluateCDF( const double beta );

  void populatePDF( std::vector<double>& energy_array );

  void getPDF( std::vector<double>& pdf_array );

  void populateCDF( std::vector<double>& energy_array );

  void getCDF( std::vector<double>& cdf_array );

private:

  // Update the cached values
  void updateCachedValues();

  // Function that represents the integral of S(alpha,beta) over all alpha
  // multiplied by exp(-beta/2)
  double integratedSAlphaBetaFunction( const double beta );

  // The integration gkq_set for integrating over alpha values
  Utility::GaussKronrodIntegrator<double> d_alpha_gkq_set;

  // The integration gkq_set for integrating over beta values
  Utility::GaussKronrodIntegrator<double> d_beta_gkq_set;

  // The free gas elastic S(alpha,beta) function
  FreeGasElasticSAlphaBetaFunction d_sab_function;

  // The energy value (MeV)
  double d_E;

  // The atomic weight ratio
  double d_A;

  // The temperature (MeV)
  double d_kT;

  // The beta min value
  double d_beta_min;

  // The normalization constant
  double d_norm_constant;

  // Cached CDF values (first = beta, second = CDF)
  std::list<std::pair<double,double> > d_cached_cdf_values;

  std::vector<double> d_pdf_array;
  std::vector<double> d_cdf_array;
};

} // end DataGen namespace

#endif // end DATA_GEN_FREE_GAS_ELASTIC_MARGINAL_BETA_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end DataGen_FreeGasElasticMarginalBetaFunction.hpp
//---------------------------------------------------------------------------//
