//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FreeGasElasticMarginalAlphaFunction.hpp
//! \author Alex Robinson
//! \brief  Free gas elastic marginal alpha function declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FREE_GAS_ELASTIC_MARGINAL_ALPHA_FUNCTION_HPP
#define MONTE_CARLO_FREE_GAS_ELASTIC_MARGINAL_ALPHA_FUNCTION_HPP

// Std Lib Includes
#include <list>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_FreeGasElasticSAlphaBetaFunction.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The free gas elastic marginal alpha function 
class FreeGasElasticMarginalAlphaFunction
{

public:

  //! Constructor
  FreeGasElasticMarginalAlphaFunction(
         const Teuchos::RCP<Utility::OneDDistribution>& 
	 zero_temp_elastic_cross_section,
         const Teuchos::RCP<MonteCarlo::ParticleScatteringAngularDistribution>&
	 cm_scattering_distribution,
	 const double A,
	 const double kT,
	 const double beta,
	 const double E );

  //! Destructor
  ~FreeGasElasticMarginalAlphaFunction()
  { /* ... */ }

  //! Set the beta and energy values
  void setIndependentVariables( const double beta, const double E );

  //! Get the lower alpha limit
  double getAlphaMin() const;

  //! Get the upper alpha limit
  double getAlphaMax() const;

  //! Get the normalization constant
  double getNormalizationConstant() const;

  //! Evaluate the marginal PDF
  double operator()( const double alpha );
  
  //! Evaluate the marginal CDF
  double evaluateCDF( const double alpha );

private:

  // Update cached values
  void updateCachedValues();

  // The integration kernel
  Utility::GaussKronrodQuadratureKernel d_kernel;

  // The free gas elastic S(alpha,beta) function
  MonteCarlo::FreeGasElasticSAlphaBetaFunction d_sab_function;

  // The beta value
  double d_beta;

  // The energy value (MeV)
  double d_E;

  // The alpha min value
  double d_alpha_min;

  // The alpha max value
  double d_alpha_max;

  // The normalization constant
  double d_norm_constant;

  // Cached CDF values (first = alpha, second = CDF)
  std::list<Utility::Pair<double,double> > d_cached_cdf_values;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_FREE_GAS_ELASTIC_MARGINAL_ALPHA_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FreeGasElasticMarginalAlphaFunction.hpp
//---------------------------------------------------------------------------//
