//---------------------------------------------------------------------------//
//!
//! \file   tstODEPACKHelpers.cpp
//! \author Alex Bennett
//! \brief  ODEPACK Helper unit test
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FRENSIE Includes
#include "Utility_ODEPACKHelperWrapper.hpp"

//---------------------------------------------------------------------------//
// Testing Variables 
//---------------------------------------------------------------------------//
 
//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( ODEPACKHelper, lsodesSolver )
{
  Teuchos::SerialDenseMatrix<int,double> matrix;
  matrix.shape(2,2);

  matrix(0,0) = -1.0;
  matrix(1,0) = -1.0;
  matrix(0,1) =  95.0;
  matrix(1,1) = -97.0;

  Teuchos::Array<double> number_densities;
  number_densities.resize(2);

  number_densities[0] = 1;
  number_densities[1] = 1;

   int matrix_dimension = number_densities.length();
   int length_working_array = 100;

   double time = 1.0;
   double relative_tol = 1e-10;
   double absolute_tol = 1e-10;

  lsodesSolver(matrix.values(),
               number_densities.getRawPtr(),
               matrix_dimension,
               &time,
               &relative_tol,
               &absolute_tol, 
               &length_working_array);

  TEST_FLOATING_EQUALITY(number_densities[0],0.273550,1e-3);
  TEST_FLOATING_EQUALITY(number_densities[1],-2.8790e-3,1e-3);
}

//---------------------------------------------------------------------------//
// Custom Main Function 
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
   Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

   Teuchos::GlobalMPISession mpiSession( &argc, &argv );
   return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}



//---------------------------------------------------------------------------//
// end tstODEPACKHelpers.hpp
//---------------------------------------------------------------------------//
 
