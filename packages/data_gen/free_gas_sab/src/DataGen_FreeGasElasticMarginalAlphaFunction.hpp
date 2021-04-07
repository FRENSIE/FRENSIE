//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FreeGasElasticMarginalAlphaFunction.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Free gas elastic marginal alpha function declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_FREE_GAS_ELASTIC_MARGINAL_ALPHA_FUNCTION_HPP
#define DATA_GEN_FREE_GAS_ELASTIC_MARGINAL_ALPHA_FUNCTION_HPP

// Std Lib Includes
#include <list>

// FRENSIE Includes
#include "DataGen_FreeGasElasticSAlphaBetaFunction.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_Tuple.hpp"

namespace DataGen{

//! The free gas elastic marginal alpha function
class FreeGasElasticMarginalAlphaFunction
{

public:

  //! Constructor
  FreeGasElasticMarginalAlphaFunction(
         const std::shared_ptr<Utility::UnivariateDistribution>&
         zero_temp_elastic_cross_section,
         const std::shared_ptr<MonteCarlo::NuclearScatteringAngularDistribution>&
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

  // The integration gkq_set
  Utility::GaussKronrodIntegrator<double> d_gkq_set;

  // The free gas elastic S(alpha,beta) function
  FreeGasElasticSAlphaBetaFunction d_sab_function;

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
  std::list<std::pair<double,double> > d_cached_cdf_values;
};

} // end DataGen namespace

#endif // end DATA_GEN_FREE_GAS_ELASTIC_MARGINAL_ALPHA_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end DataGen_FreeGasElasticMarginalAlphaFunction.hpp
//---------------------------------------------------------------------------//
