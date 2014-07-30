//---------------------------------------------------------------------------//
//!
//! \file   tstReactionRateMatrix.cpp
//! \author Alex Bennett
//! \brief  Reaction Rate Matrix unit test
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FRENSIE Includes
#include "Transmutation_ReactionRateMatrix.hpp"
#include "Transmutation_IsotopesForDepletion.hpp"

//---------------------------------------------------------------------------//
// Testing Variables 
//---------------------------------------------------------------------------//
 

//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( ReactionRateMatrix, addFissionFragments )
{
   Teuchos::Array<int> zaids;
   Transmutation::IsotopesForDepletion::getIsotopes( zaids );

   Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> > reaction_rate_matrix( new Teuchos::SerialDenseMatrix<int,double>);

   reaction_rate_matrix->shape(zaids.length(),zaids.length());

   int fission_zaid = 92235;
   double fission_reaction_rate = 5.0;

   Teuchos::Array<std::pair<int,double> > fission_fragments(1);

   fission_fragments[0].first = 1001;
   fission_fragments[0].second = 3.0;

   Transmutation::ReactionRateMatrix::addFissionFragments(reaction_rate_matrix,
                                                          fission_zaid,
                                                          fission_reaction_rate,
                                                          fission_fragments);

   int zaid_loc = Transmutation::IsotopesForDepletion::getLocation( 92235 , zaids ); 

   TEST_COMPARE(reaction_rate_matrix->numRows() ,==, 3255);
   TEST_COMPARE(reaction_rate_matrix->numCols() ,==, 3255);
   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(0,zaid_loc), 3.0, 1e-15);
   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(zaid_loc,zaid_loc), -5.0, 1e-15);
}

TEUCHOS_UNIT_TEST( ReactionRateMatrix, addReactionRates )
{
   Teuchos::Array<int> zaids;
   Transmutation::IsotopesForDepletion::getIsotopes( zaids );

   Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> > reaction_rate_matrix( new Teuchos::SerialDenseMatrix<int,double>);

   reaction_rate_matrix->shape(zaids.length(),zaids.length());

   Teuchos::Array<std::pair<int,double> > reaction_rates(1);
   
   // Test the N 2N Reaction
   reaction_rates[0].first = 1004;
   reaction_rates[0].second = 5.0;

   Transmutation::ReactionRateMatrix::addReactionRates(reaction_rate_matrix,
                                                       reaction_rates,
                                                       Facemc::N__2N_REACTION);

   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(3,3), -5.0, 1e-15);
   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(2,3),  5.0, 1e-15);

   // Test the N Gamma Reaction
   reaction_rates[0].first = 1001;

   Transmutation::ReactionRateMatrix::addReactionRates(reaction_rate_matrix,
                                                       reaction_rates,
                                                       Facemc::N__GAMMA_REACTION);

   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(0,0), -5.0, 1e-15);
   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(1,0),  5.0, 1e-15);

   // Test the N P Reaction
   reaction_rates[0].first = 3006;

   Transmutation::ReactionRateMatrix::addReactionRates(reaction_rate_matrix,
                                                       reaction_rates,
                                                       Facemc::N__P_REACTION);

   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(17,17), -5.0, 1e-15);
   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(11,17),  5.0, 1e-15);

   // Test the N D Reaction
   reaction_rates[0].first = 6012;

   Transmutation::ReactionRateMatrix::addReactionRates(reaction_rate_matrix,
                                                       reaction_rates,
                                                       Facemc::N__D_REACTION);

   int parent_zaid;
   int daughter_zaid;

   parent_zaid = Transmutation::IsotopesForDepletion::getLocation( 6012 , zaids ); 
   daughter_zaid = Transmutation::IsotopesForDepletion::getLocation( 5011 , zaids ); 

   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(parent_zaid,parent_zaid), -5.0, 1e-15);
   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(daughter_zaid,parent_zaid),  5.0, 1e-15);

   // Test the N T Reaction
   reaction_rates[0].first = 11023;

   Transmutation::ReactionRateMatrix::addReactionRates(reaction_rate_matrix,
                                                       reaction_rates,
                                                       Facemc::N__T_REACTION);

   parent_zaid = Transmutation::IsotopesForDepletion::getLocation( 11023 , zaids ); 
   daughter_zaid = Transmutation::IsotopesForDepletion::getLocation( 10021 , zaids ); 

   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(parent_zaid,parent_zaid), -5.0, 1e-15);
   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(daughter_zaid,parent_zaid),  5.0, 1e-15);

   // Test the N ALPHA Reaction
   reaction_rates[0].first = 16034;

   Transmutation::ReactionRateMatrix::addReactionRates(reaction_rate_matrix,
                                                       reaction_rates,
                                                       Facemc::N__ALPHA_REACTION);

   parent_zaid = Transmutation::IsotopesForDepletion::getLocation( 16034 , zaids ); 
   daughter_zaid = Transmutation::IsotopesForDepletion::getLocation( 14031 , zaids ); 

   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(parent_zaid,parent_zaid), -5.0, 1e-15);
   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(daughter_zaid,parent_zaid),  5.0, 1e-15);

   // Test the N HE3 Reaction
   reaction_rates[0].first = 26056;

   Transmutation::ReactionRateMatrix::addReactionRates(reaction_rate_matrix,
                                                       reaction_rates,
                                                       Facemc::N__HE3_REACTION);

   parent_zaid = Transmutation::IsotopesForDepletion::getLocation( 26056 , zaids ); 
   daughter_zaid = Transmutation::IsotopesForDepletion::getLocation( 24054 , zaids ); 

   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(parent_zaid,parent_zaid), -5.0, 1e-15);
   TEST_FLOATING_EQUALITY((*reaction_rate_matrix)(daughter_zaid,parent_zaid),  5.0, 1e-15);
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
// end tstReactionRateMatrix.cpp 
//---------------------------------------------------------------------------//
