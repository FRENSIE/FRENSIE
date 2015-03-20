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
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

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
   Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> > decay_matrix( new Teuchos::SerialDenseMatrix<int,double>);

   Transmutation::DecayMatrix::getDecayMatrix(decay_matrix);

   TEST_COMPARE(decay_matrix->numRows() ,==, 3255);
   TEST_COMPARE(decay_matrix->numCols() ,==, 3255);
   TEST_FLOATING_EQUALITY((*decay_matrix)(2,2) , -1.7828336471961835e-09 , 1e-15);
   TEST_FLOATING_EQUALITY((*decay_matrix)(7,2) ,  1.7828336471961835e-09 , 1e-15);
   TEST_FLOATING_EQUALITY((*decay_matrix)(25,25) , -1.507428938751673e-07 , 1e-15);
   TEST_FLOATING_EQUALITY((*decay_matrix)(18,25) ,  1.507428938751673e-07 , 1e-15);
}
 
//---------------------------------------------------------------------------//
// end tstDecayMatrix.cpp 
//---------------------------------------------------------------------------//
