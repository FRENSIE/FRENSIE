//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FreeGasElasticMarginalBetaFunction.hpp
//! \author Alex Robinson
//! \brief  Free gas elastic marginal beta function declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_FREE_GAS_ELASTIC_MARGINAL_BETA_FUNCTION_HPP
#define DATA_GEN_FREE_GAS_ELASTIC_MARGINAL_BETA_FUNCTION_HPP

// Std Lib Includes
#include <list>

// Boost Includes
#include <boost/function.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

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
	      const Teuchos::RCP<Utility::OneDDistribution>& 
	      zero_temp_elastic_cross_section,
              const Teuchos::RCP<MonteCarlo::NuclearScatteringAngularDistribution>&
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
  
  //! Get the normalization constant
  double getNormalizationConstant() const;

  //! Evaluate the marginal PDF
  double operator()( const double beta );

  //! Evaluate the marginal CDF
  double evaluateCDF( const double beta );

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
  std::list<Utility::Pair<double,double> > d_cached_cdf_values;
};

} // end DataGen namespace

#endif // end DATA_GEN_FREE_GAS_ELASTIC_MARGINAL_BETA_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end DataGen_FreeGasElasticMarginalBetaFunction.hpp
//---------------------------------------------------------------------------//
