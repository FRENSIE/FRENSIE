//---------------------------------------------------------------------------//
//!
//! \file   tstCellTransmutationData.cpp
//! \author Alex Bennett
//! \brief  Cell Transmutation Data unit test
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FRENSIE Includes
#include "Transmutation_CellTransmutationData.hpp"
#include "Transmutation_IsotopesForDepletion.hpp"

//---------------------------------------------------------------------------//
// Testing Variables 
//---------------------------------------------------------------------------//
 

//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( CellTransmutationData, getCellID )
{
   Teuchos::Array<std::pair<int,double> > number_densities;

   // Initialize the cell transmutation data instance
   Transmutation::CellTransmutationData cell_data(5,number_densities);
  
   TEST_COMPARE( cell_data.getCellID() ,==, 5);
}

TEUCHOS_UNIT_TEST( CellTransmutationData, getNumberDensities )
{
   Teuchos::Array<std::pair<int,double> > initial_number_densities(2);

   initial_number_densities[0] = std::pair<int,double>(1001,5.0);
   initial_number_densities[1] = std::pair<int,double>(2005,15.0);

   // Initialize the cell transmutation data instance
   Transmutation::CellTransmutationData cell_data(5,initial_number_densities);

   Teuchos::Array<double> number_densities;
  
   cell_data.getNumberDensities(number_densities);

   TEST_FLOATING_EQUALITY(number_densities[0], 5.0, 1e-15);
   TEST_FLOATING_EQUALITY(number_densities[9],15.0, 1e-15); 
}

TEUCHOS_UNIT_TEST( CellTransmutationData, populateMatrix )
{
   Teuchos::Array<std::pair<int,double> > number_densities(5);

   number_densities[0] = std::pair<int,double>(2004,5.0);
   number_densities[1] = std::pair<int,double>(6012,15.0);
   number_densities[2] = std::pair<int,double>(92235,15.0);
   number_densities[3] = std::pair<int,double>(92238,15.0);
   number_densities[4] = std::pair<int,double>(94239,15.0);

   // Initialize the cell transmutation data instance
   Transmutation::CellTransmutationData cell_data(1,number_densities);

   // Set the reaction rates
   Teuchos::Array<std::pair<int,double> > reaction_rates(2);

   reaction_rates[0].first = 2004;
   reaction_rates[0].second = 5;
   reaction_rates[1].first = 6012;
   reaction_rates[1].second = 10;

   cell_data.setReactionRates( MonteCarlo::N__GAMMA_REACTION, reaction_rates );

   reaction_rates[0].second = 4;

   cell_data.setReactionRates( MonteCarlo::N__2N_REACTION, reaction_rates );

   reaction_rates[0].second = 3;

   cell_data.setReactionRates( MonteCarlo::N__P_REACTION, reaction_rates );
  
   // Set the fission fragments
   Teuchos::Array<std::pair<int,double> > fission_fragments(2);

   fission_fragments[0].first = 26056;
   fission_fragments[0].second = 10;
   fission_fragments[1].first = 26058;
   fission_fragments[1].second = 15;

   cell_data.setFissionReactionRates(92235,7,fission_fragments);

   cell_data.setFissionReactionRates(92238,11,fission_fragments);

   cell_data.setFissionReactionRates(94239,13,fission_fragments);

   // Populate the matrix
   Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> > matrix( new Teuchos::SerialDenseMatrix<int,double>);

   // Set up the zaids array
   Teuchos::Array<int> zaids;
   Transmutation::IsotopesForDepletion::getIsotopes( zaids ); 

   // Allocate the matrix
   matrix->shape(zaids.length(),zaids.length());

   cell_data.populateMatrix(matrix);

   int parent_zaid;
   int parent_zaid_2;
   int parent_zaid_3;
   int daughter_zaid_1;
   int daughter_zaid_2;
   int daughter_zaid_3;
   int daughter_zaid_4;
   int daughter_zaid_5;
   int daughter_zaid_6;

   // Test the reaction rates
   parent_zaid = Transmutation::IsotopesForDepletion::getLocation( 2004 , zaids ); 
   daughter_zaid_1 = Transmutation::IsotopesForDepletion::getLocation( 2005 , zaids ); 
   daughter_zaid_2 = Transmutation::IsotopesForDepletion::getLocation( 2003 , zaids ); 
   daughter_zaid_3 = Transmutation::IsotopesForDepletion::getLocation( 1005 , zaids );

   parent_zaid_2 = Transmutation::IsotopesForDepletion::getLocation( 6012 , zaids ); 
   daughter_zaid_4 = Transmutation::IsotopesForDepletion::getLocation( 6013 , zaids ); 
   daughter_zaid_5 = Transmutation::IsotopesForDepletion::getLocation( 6011 , zaids ); 
   daughter_zaid_6 = Transmutation::IsotopesForDepletion::getLocation( 5013 , zaids );

   TEST_FLOATING_EQUALITY((*matrix)(parent_zaid,parent_zaid), -12.0, 1e-15); 
   TEST_FLOATING_EQUALITY((*matrix)(daughter_zaid_1,parent_zaid), 5.0, 1e-15); 
   TEST_FLOATING_EQUALITY((*matrix)(daughter_zaid_2,parent_zaid), 4.0, 1e-15); 
   TEST_FLOATING_EQUALITY((*matrix)(daughter_zaid_3,parent_zaid), 3.0, 1e-15); 

   TEST_FLOATING_EQUALITY((*matrix)(parent_zaid_2,parent_zaid_2), -30.0, 1e-15); 
   TEST_FLOATING_EQUALITY((*matrix)(daughter_zaid_4,parent_zaid_2), 10.0, 1e-15); 
   TEST_FLOATING_EQUALITY((*matrix)(daughter_zaid_5,parent_zaid_2), 10.0, 1e-15); 
   TEST_FLOATING_EQUALITY((*matrix)(daughter_zaid_6,parent_zaid_2), 10.0, 1e-15);

   // Test the fission fragment reaction rates
   parent_zaid = Transmutation::IsotopesForDepletion::getLocation( 92235 , zaids ); 
   parent_zaid_2 = Transmutation::IsotopesForDepletion::getLocation( 92238 , zaids ); 
   parent_zaid_3 = Transmutation::IsotopesForDepletion::getLocation( 94239 , zaids );
 
   daughter_zaid_1 = Transmutation::IsotopesForDepletion::getLocation( 26056 , zaids );
   daughter_zaid_2 = Transmutation::IsotopesForDepletion::getLocation( 26058 , zaids );

   TEST_FLOATING_EQUALITY((*matrix)(parent_zaid,parent_zaid), -7.0, 1e-15); 
   TEST_FLOATING_EQUALITY((*matrix)(parent_zaid_2,parent_zaid_2), -11.0, 1e-15); 
   TEST_FLOATING_EQUALITY((*matrix)(parent_zaid_3,parent_zaid_3), -13.0, 1e-13);

   TEST_FLOATING_EQUALITY((*matrix)(daughter_zaid_1,parent_zaid), 10.0, 1e-15); 
   TEST_FLOATING_EQUALITY((*matrix)(daughter_zaid_2,parent_zaid), 15.0, 1e-15); 

   TEST_FLOATING_EQUALITY((*matrix)(daughter_zaid_1,parent_zaid_2), 10.0, 1e-15); 
   TEST_FLOATING_EQUALITY((*matrix)(daughter_zaid_2,parent_zaid_2), 15.0, 1e-15); 

   TEST_FLOATING_EQUALITY((*matrix)(daughter_zaid_1,parent_zaid_3), 10.0, 1e-15); 
   TEST_FLOATING_EQUALITY((*matrix)(daughter_zaid_2,parent_zaid_3), 15.0, 1e-15); 
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
// end tstCellTransmutationData.cpp 
//---------------------------------------------------------------------------//
