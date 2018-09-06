//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussRadauQuadratureSet_def.hpp
//! \author Luke Kersting
//! \brief  Gauss-Radau quadrature set
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_RADAU_QUADRATURE_SET_DEF_HPP
#define UTILITY_GAUSS_RADAU_QUADRATURE_SET_DEF_HPP

// std Includes
#include <cmath>

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"

namespace Utility{

// Function wrapper for evaluating the functor
template<typename Functor>
double GaussRadauQuadratureSet::functorWrapper( const double x,
						     void* indirected_functor )
{
  // Make sure the functor is valid
  testPrecondition( indirected_functor );

  Functor* functor = (Functor*)( indirected_functor );

  return (*functor)( x );
}

// Integrate the function
template<typename Functor>
void GaussRadauQuadratureSet::integrate(
        Functor& integrand,
        double fixed_point,
        double lower_limit,
        double upper_limit,
        double& result ) const
{
  // Make sure fixed_point is either -1 or 1
  testPrecondition( fabs(fixed_point) == 1.0 );
  // Make sure the integration limits are valid
  testPrecondition( lower_limit < upper_limit );
  // Make sure the integration limits are bounded
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( lower_limit ) );
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( upper_limit ) );

  // Get the Radau quadrature weights and nodes
  std::vector<double> nodes( d_polynomial_order + 1 ),
                      weights( d_polynomial_order + 1 );

  findNodesAndWeights( fixed_point, nodes, weights );

  result = 0.0;

  for (int i = 0; i < nodes.size(); ++i)
  {
    result += integrand( nodes[i])*weights[i];
  }

  if ( result < 1e-15 )
  {
    result = 0.0;
  }

}

} // end Utility namespace

#endif // end UTILITY_GAUSS_RADAU_QUADRATURE_SET_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussRadauQuadratureSet_def.hpp
//---------------------------------------------------------------------------//
