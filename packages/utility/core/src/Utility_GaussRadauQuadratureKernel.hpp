//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussRadauQuadratureKernel.hpp
//! \author Luke Kersting
//! \brief  Gauss-Radau quadrature kernel
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_RADAU_QUADRATURE_KERNEL_HPP
#define UTILITY_GAUSS_RADAU_QUADRATURE_KERNEL_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

namespace Utility{

//! The Gauss-Radau quadrature kernel
class GaussRadauQuadratureKernel
{

public:

  //! Constructor
  GaussRadauQuadratureKernel( boost::function<double (double, int)>
                                polynomial_expansion_function,
                              const double error_tol,
                              const int polynomial_order );

  //! Destructor
  ~GaussRadauQuadratureKernel()
  { /* ... */ }

  //! Integrate the function
  template<typename Functor>
  void integrate( Functor& integrand,
                  double end_point, 
                  double lower_limit, 
                  double upper_limit,
                  double& result ) const;

  //! Caluclate the Jacobi Polynomial at x
  double getJacobiPolynomial( double x,
                              int n = 1, 
                              int alpha = 0,
                              int beta = 1 ) const;

  //! Caluclate the Legendre Polynomial at x
  double getLegendrePolynomial( double x,
                              int n = 1) const;
  
  //! Calculate the derivative of the nth order Jacobi Polynomial at x
  double getJacobiPolynomialDerivative( double x,
                                        int n = 1, 
                                        int alpha = 0,
                                        int beta = 1 ) const;

  //! Caluclate the roots of the Jacobi Polynomial
  void getJacobiPolynomialRoots( Teuchos::Array<double>& roots,
                                 const int n = 1, 
                                 int alpha = 0,
                                 int beta = 1 ) const;

  //! Find the Radau nodes and wieghts including at end point -1 or 1
  void findNodesAndWeights( double end_point, 
                            Teuchos::Array<double>& nodes,
                            Teuchos::Array<double>& weights ) const;

  //! Find the Radau nodes and wieghts including at end point -1 or 1
  void findNodesAndPositiveWeights( double end_point, 
                                    Teuchos::Array<double>& nodes,
                                    Teuchos::Array<double>& weights ) const;

private:

  // Create the integrand function for the weight at a given node with end point -1 or 1
  double getWeightIntegrand( double x,
                             double node,
                             double end_point, 
                             int n ) const;

  // Create the integrand function for the weight at the end point -1 or 1
  double getFixedWeightIntegrand( double x, int n ) const;


  // Find the Radau wieght for the function at the given node with end point -1 or 1
  double findWeightAtNode( double node, double end_point, int n ) const;

  // Find the Radau wieght for the function at the end point -1 or 1
  double findWeightAtEndPoint( double end_point, int n ) const;

  // Polynomial expansion function
  boost::function<double (double, int)> d_polynomial_expansion_function;

  // Polynomial order
  int d_polynomial_order;

  // Error Tolerence
  double d_error_tol;

  // Function wrapper for evaluating the functor
  template<typename Functor>
  static double functorWrapper( const double x, void* indirected_functor );
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_GaussRadauQuadratureKernel_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_GUASS_RADAU_QUADRATURE_KERNEL_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussRadauQuadratureKernel.hpp
//---------------------------------------------------------------------------//
