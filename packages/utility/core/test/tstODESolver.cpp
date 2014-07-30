//---------------------------------------------------------------------------//
//!
//! \file   tstODESolver.cpp
//! \author Alex Bennett
//! \brief  ODE Solver unit test
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FRENSIE Includes
#include "Utility_ODESolver.hpp"

//---------------------------------------------------------------------------//
// Testing Variables 
//---------------------------------------------------------------------------//
 
//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( ODESolver, solve )
{
  Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> > matrix( new Teuchos::SerialDenseMatrix<int,double>);
  matrix->shape(2,2);

  (*matrix)(0,0) = -1.0;
  (*matrix)(1,0) = -1.0;
  (*matrix)(0,1) =  95.0;
  (*matrix)(1,1) = -97.0;

  Teuchos::Array<double> number_densities;
  number_densities.resize(2);

  number_densities[0] = 1;
  number_densities[1] = 1;

  double time = 1.0;

  Utility::ODESolver solver_instance;
  solver_instance.solve(matrix,number_densities,time);

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
// end tstODESolver.cpp
//---------------------------------------------------------------------------//
 
