//---------------------------------------------------------------------------//
//!
//! \file   tstBoostSolver.cpp
//! \author Alex Bennett
//! \brief  Boost Solver unit test
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FRENSIE Includes
#include "Utility_BoostSolver.hpp"

//---------------------------------------------------------------------------//
// Testing Variables 
//---------------------------------------------------------------------------//
 
//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( BoostSolver, solve )
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

  Utility::BoostSolver solver_instance(matrix,number_densities);
  solver_instance.Solve(time);
  solver_instance.getNumberDensities(number_densities);

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
 
