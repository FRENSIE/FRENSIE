//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodIntegration.cpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod integration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GaussKronrodIntegration.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Initialize static member data

// 7 point Gauss quadrature weights
const double GaussKronrodIntegration::gauss_weights_7[4] =
{
  0.129484966168869693270611432679082,
  0.279705391489276667901467771423780,
  0.381830050505118944950369775488975,
  0.417959183673469387755102040816327
};


// 7 point Gauss quadrature abscissae
const double GaussKronrodIntegration::gauss_abscissae_7[4] =
{
  0.949107912342758524526189684047851,
  0.741531185599394439863864773280788,
  0.405845151377397166906606412076961,
  0.000000000000000000000000000000000
};

// 15 point Gauss Kronrad quadrature weights
//const Teuchos::Array<double> GaussKronrodIntegration::kronrod_weights_15( 8 ); 
const double GaussKronrodIntegration::kronrod_weights_15[8] =
{
  0.022935322010529224963732008058970,
  0.063092092629978553290700663189204,
  0.104790010322250183839876322541518,
  0.140653259715525918745189590510238,
  0.169004726639267902826583426598550,
  0.190350578064785409913256402421014,
  0.204432940075298892414161999234649,
  0.209482141084727828012999174891714
};


// 15 point Gauss Kronrad quadrature abscissae
//Teuchos::Array<double> GaussKronrodIntegration::kronrod_abscissae_15( 8 ); 
const double GaussKronrodIntegration::kronrod_abscissae_15[8] =
{
  0.991455371120812639206854697526329,
  0.949107912342758524526189684047851,
  0.864864423359769072789712788640926,
  0.741531185599394439863864773280788,
  0.586087235467691130294144838258730,
  0.405845151377397166906606412076961,
  0.207784955007898467600689403773245,
  0.000000000000000000000000000000000
};

// 21 point Gauss Kronrad quadrature weights and abscissae
Teuchos::Array<double> kronrod_weights_21(11);

// 21 point Gauss Kronrad quadrature abscissae
Teuchos::Array<double> kronrod_abscissae_21(11);

// 31 point Gauss Kronrad quadrature weights and abscissae
Teuchos::Array<double> kronrod_weights_31(16);

// 31 point Gauss Kronrad quadrature abscissae
Teuchos::Array<double> kronrod_abscissae_31(16);

// 41 point Gauss Kronrad quadrature weights and abscissae
Teuchos::Array<double> kronrod_weights_41(21);

// 41 point Gauss Kronrad quadrature abscissae
Teuchos::Array<double> kronrod_abscissae_41(21);

// 51 point Gauss Kronrad quadrature weights and abscissae
Teuchos::Array<double> kronrod_weights_51(26);

// 51 point Gauss Kronrad quadrature abscissae
Teuchos::Array<double> kronrod_abscissae_51(26);

// Constructor
GaussKronrodIntegration::GaussKronrodIntegration( 
    const double relative_error_tol,
    const double absolute_error_tol )
  : d_relative_error_tol( relative_error_tol ),
    d_absolute_error_tol( absolute_error_tol )
{
  // Make sure the error tolerances are valid
  testPrecondition( relative_error_tol >= 0.0 );
  testPrecondition( absolute_error_tol >= 0.0 );

  std::cout << "weight 1 = " << kronrod_weights_15[0] << std::endl;
}

// Destructor
GaussKronrodIntegration::~GaussKronrodIntegration()
{ /* ... */ }

// Normalize absolute error from integration
void GaussKronrodIntegration::normalizeAbsoluteError( 
    double& absolute_error, 
    double result_abs, 
    double result_asc ) const
{
  if ( result_asc != 0.0 && absolute_error != 0.0 )
    {
      absolute_error = result_asc * 
        std::min( 1.0, pow( 200.0 * absolute_error/result_asc, 1.5 ) );
    };

  if ( result_abs > std::numeric_limits<double>::min() / ( 50.0 *
                    std::numeric_limits<double>::epsilon() ) )
    {
      absolute_error = std::max( absolute_error,
         50.0*std::numeric_limits<double>::epsilon() * result_abs );
    };
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegration.cpp
//---------------------------------------------------------------------------//
