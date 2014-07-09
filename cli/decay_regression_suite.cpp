//---------------------------------------------------------------------------//
//!
//! \file   decay_regression_suite.cpp
//! \author Alex Bennett
//! \brief  decay regresssion suite
//!
//---------------------------------------------------------------------------//

// Boost includes
#include <boost/unordered_map.hpp>

// Trilinos includes
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FRENSIE includes
#include "Transmutation_IsotopesArray.hpp"
#include "Transmutation_DecayMatrix.hpp"
#include "Utility_ODESolver.hpp"

int main(int argc, char** argv) 
{

   // Initialize map of initial number densities
   boost::unordered_map<int,double> initial_number_densities;
   
   // Add tritium to the map of number densities
 //  initial_number_densities.insert( std::pair<int,double>(1003,100) );
//   initial_number_densities.insert( std::pair<int,double>(98252,100) );
   initial_number_densities.insert( std::pair<int,double>(94240,100) );
   
   // Initialize array of number densities to be used
   Teuchos::Array<double> number_densities_array;
   
   // Add the initial number densities into the array of number densities
   Transmutation::IsotopesArray::getOrderedIsotopesArray( initial_number_densities, number_densities_array );
   
   // Initialize the decay matrix
   Teuchos::SerialDenseMatrix<int,double> decay_matrix;
   
   // Fill the decay matrix
   Transmutation::DecayMatrix::getDecayMatrix(decay_matrix);
   
   // Set the time isotope will decay for about ten years
   double time = 1000.0*3600.0*24.0*365.25;
 
   // Initialize the solver instance
   Utility::ODESolver solver_instance;
   
   // Solve for the new number densities
   solver_instance.solve(decay_matrix, number_densities_array, time);
   
   // Initialize map of new number densities
   boost::unordered_map<int,double> new_number_densities;
   
   // Copy the calculated number densities into an map
   Transmutation::IsotopesArray::getIsotopesNumberDensityMap( new_number_densities, number_densities_array); 
  
   double total_number_density = 0;
 
   // Print the results
   std::cout << std::endl;
   for(boost::unordered_map<int,double>::iterator i = new_number_densities.begin();
                                                  i != new_number_densities.end();
                                                  ++i)
   {
      std::cout << "Isotope: " << i->first << " now has: " << i->second << "%" << std::endl;
      total_number_density += i->second;
   }
   std::cout << "Total number density: " << total_number_density << std::endl;
   return 0;

}


//---------------------------------------------------------------------------//
// end decay_regression_suite.cpp
//---------------------------------------------------------------------------//
