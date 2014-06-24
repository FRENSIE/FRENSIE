//---------------------------------------------------------------------------//
//!
//! \file   tstDecayMatrix.cpp
//! \author Alex Bennett
//! \brief  Decay Matrix unit test
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>

// FRENSIE Includes
#include "Transmutation_DecayMatrix.hpp"
#include "Transmutation_IsotopesForDepletion.hpp"

//---------------------------------------------------------------------------//
// Testing Variables 
//---------------------------------------------------------------------------//
 

//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
// Check read ENDF Fission Yields Header
TEUCHOS_UNIT_TEST( DecayMatrix, getDecayMatrix )
{
   Teuchos::Array<int> zaids;

   Transmutation::IsotopesForDepletion::getIsotopes( zaids ); 

   Teuchos::Array<Teuchos::Array<double> > decay_matrix;
   std::string data_file = "endf7.dk.xml";

   Transmutation::DecayMatrix::getDecayMatrix(zaids,decay_matrix,data_file);

   TEST_COMPARE(decay_matrix.length() ,==, 2328);
   TEST_COMPARE(decay_matrix[1].length() ,==, 2328);
   TEST_FLOATING_EQUALITY(decay_matrix[2][2] , -1.7828336471961835e-09 , 1e-15);
   TEST_FLOATING_EQUALITY(decay_matrix[3][2] ,  1.7828336471961835e-09 , 1e-15);
   TEST_FLOATING_EQUALITY(decay_matrix[7][7] , -1.507428938751673e-07 , 1e-15);
   TEST_FLOATING_EQUALITY(decay_matrix[6][7] ,  1.507428938751673e-07 , 1e-15);
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
// end tstDecayMatrix.cpp 
//---------------------------------------------------------------------------//
