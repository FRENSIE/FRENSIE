//---------------------------------------------------------------------------//
//!
//! \file   decay_verification_simple_problem.cpp
//! \author Alex Bennett
//! \brief  decay verication simple problem
//!
//---------------------------------------------------------------------------//

// Boost includes
#include <boost/unordered_map.hpp>

// Trilinos includes
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE includes
#include "Transmutation_IsotopesArray.hpp"
#include "Transmutation_DecayMatrix.hpp"
#include "Utility_ODESolver.hpp"

//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( decay_verification, simple_problem )
{
   // Initialize map of initial number densities
   boost::unordered_map<int,double> initial_number_densities;
   
   // Add tritium to the map of number densities
   initial_number_densities.insert( std::pair<int,double>(1003,100) );
   
   // Initialize array of number densities to be used
   Teuchos::Array<double> number_densities_array;
   
   // Add the initial number densities into the array of number densities
   Transmutation::IsotopesArray::getOrderedIsotopesArray( initial_number_densities, number_densities_array );
   
   // Initialize the decay matrix
   Teuchos::SerialDenseMatrix<int,double> decay_matrix;
   
   // Fill the decay matrix
   Transmutation::DecayMatrix::getDecayMatrix(decay_matrix);
   
   // Set the time isotope will decay for about ten years
   double time = 10.0*3600.0*24.0*365.25;
 
   // Initialize the solver instance
   Utility::ODESolver solver_instance;
   
   // Solve for the new number densities
   solver_instance.solve(decay_matrix, number_densities_array, time);
   
   // Initialize map of new number densities
   boost::unordered_map<int,double> new_number_densities;
   
   // Copy the calculated number densities into an map
   Transmutation::IsotopesArray::getIsotopesNumberDensityMap( new_number_densities, number_densities_array); 
  
   double total_number_density = 0;
 
   // Sum the results
   std::cout << std::endl;
   for(boost::unordered_map<int,double>::iterator i = new_number_densities.begin();
                                                  i != new_number_densities.end();
                                                  ++i)
   {
      total_number_density += i->second;
   }

   // Test Results
   TEST_COMPARE(new_number_densities.size() ,==, 2)
   TEST_FLOATING_EQUALITY(total_number_density , 100.0 , 1e-15);
   TEST_FLOATING_EQUALITY(new_number_densities.find(2003)->second , 43.0276 , 1e-3);
   TEST_FLOATING_EQUALITY(new_number_densities.find(1003)->second , 56.9724 , 1e-4);
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
// end decay_verification_simple_problem.cpp
//---------------------------------------------------------------------------//
