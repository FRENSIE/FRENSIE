//---------------------------------------------------------------------------//
//!
//! \file   tstSloanRadauQuadrature.cpp
//! \author Luke Kersting
//! \brief  Sloan implentation of Gauss-Radau quadrature unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_SloanRadauQuadrature.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the Radau moments can be returned
TEUCHOS_UNIT_TEST( SloanRadauQuadrature,
		           getRadauMoments )
{
  int number_of_moments = 2;
  Teuchos::Array<double> legendre_moments( number_of_moments+1 );
  Teuchos::Array<double> radau_moments( number_of_moments );

  legendre_moments[0] = 1.0;
  legendre_moments[1] = 5.0;
  legendre_moments[2] = 10.0;

  Utility::SloanRadauQuadrature quadrature1( legendre_moments, 1 );

  quadrature1.getRadauMoments( legendre_moments, radau_moments );

  TEST_FLOATING_EQUALITY( radau_moments[0], -4.0, 1e-15);;
  TEST_FLOATING_EQUALITY( radau_moments[1], -2.0, 1e-15);


  number_of_moments = 4;
  legendre_moments.resize( number_of_moments );
  radau_moments.resize( number_of_moments );
  Teuchos::Array<double> legendre_moment( number_of_moments+1 );
  Teuchos::Array<double> radau_moment( number_of_moments );

  legendre_moment[0] = 1.00000000000000;
  legendre_moment[1] = 2.00000000000000;
  legendre_moment[2] = 4.00000000000000;
  legendre_moment[3] = 8.00000000000000;
  legendre_moment[4] = 10.00000000000000;

  Utility::SloanRadauQuadrature quadrature2( legendre_moments, 2 );

  quadrature2.getRadauMoments( legendre_moment, radau_moment );

  TEST_FLOATING_EQUALITY( radau_moment[0], -1.0, 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[1], -1.0, 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[2], -7.0/5.0, 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[3], -13.0/35.0, 1e-14);

}

//---------------------------------------------------------------------------//
// end tstSloanRadauQuadrature.cpp
//---------------------------------------------------------------------------//
