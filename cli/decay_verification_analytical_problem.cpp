//---------------------------------------------------------------------------//
//!
//! \file   decay_verification_analytical_problem.cpp
//! \author Alex Bennett
//! \brief  decay verication analytical problem
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
TEUCHOS_UNIT_TEST( decay_verification, analytical_problem )
{
   // Initialize map of initial number densities
   boost::unordered_map<int,double> initial_number_densities;
   
   // Add tritium to the map of number densities
   initial_number_densities.insert( std::pair<int,double>(98249,1) );
   
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
  
   // Test Results

   TEST_FLOATING_EQUALITY(new_number_densities.find(81205)->second   ,  1.40394e-28  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(81209)->second   ,  1.94062e-20  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(82209)->second   ,  7.82636e-17  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(83209)->second   ,  2.58695e-11  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(83213)->second   ,  1.82795e-17  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(84213)->second   ,  2.74513e-26  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(85217)->second   ,  2.15862e-22  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(86217)->second   ,  2.52619e-28  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(87221)->second   ,  1.96482e-18  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(88225)->second   ,  8.60504e-15  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(89225)->second   ,  5.77415e-15  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(90229)->second   ,  1.54871e-09  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(91233)->second   ,  6.11819e-10  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(92233)->second   ,  1.65585e-06  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(92237)->second   ,  4.32577e-11  , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(93237)->second   ,  0.0177657    , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(94241)->second   ,  0.00136527   , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(95241)->second   ,  0.0254561    , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(96245)->second   ,  0.816619      , 1e-10);
   TEST_FLOATING_EQUALITY(new_number_densities.find(98249)->second   ,  0.138792      , 1e-10);


   TEST_FLOATING_EQUALITY(  0.0          ,  1.40394e-28  , 1e-10);
   TEST_FLOATING_EQUALITY(  1.94061e-20  ,  1.94062e-20  , 1e-10);
   TEST_FLOATING_EQUALITY(  7.82634e-17  ,  7.82636e-17  , 1e-10);
   TEST_FLOATING_EQUALITY(  2.58698e-11  ,  2.58695e-11  , 1e-10);
   TEST_FLOATING_EQUALITY(  1.82795e-17  ,  1.82795e-17  , 1e-10);
   TEST_FLOATING_EQUALITY(  2.74512e-26  ,  2.74513e-26  , 1e-10);
   TEST_FLOATING_EQUALITY(  2.15862e-22  ,  2.15862e-22  , 1e-10);
   TEST_FLOATING_EQUALITY(  2.52618e-28  ,  2.52619e-28  , 1e-10);
   TEST_FLOATING_EQUALITY(  1.96481e-18  ,  1.96482e-18  , 1e-10);
   TEST_FLOATING_EQUALITY(  8.60501e-15  ,  8.60504e-15  , 1e-10);
   TEST_FLOATING_EQUALITY(  5.77414e-15  ,  5.77415e-15  , 1e-10);
   TEST_FLOATING_EQUALITY(  1.5487e-09   ,  1.54871e-09  , 1e-10);
   TEST_FLOATING_EQUALITY(  6.1182e-10   ,  6.11819e-10  , 1e-10);
   TEST_FLOATING_EQUALITY(  1.65585e-06  ,  1.65585e-06  , 1e-10);
   TEST_FLOATING_EQUALITY(  4.32577e-11  ,  4.32577e-11  , 1e-10);
   TEST_FLOATING_EQUALITY(  0.0177657    ,  0.0177657    , 1e-10);
   TEST_FLOATING_EQUALITY(  0.00136527   ,  0.00136527   , 1e-10);
   TEST_FLOATING_EQUALITY(  0.0254561    ,  0.0254561    , 1e-10);
   TEST_FLOATING_EQUALITY(  0.81662      ,  0.816619      , 1e-10);
   TEST_FLOATING_EQUALITY(  0.138792     ,  0.138792      , 1e-10);

// 98252
//   TEST_FLOATING_EQUALITY(new_number_densities.find(81208)->second   ,  2.69414e-31    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(82212)->second   ,  1.5675e-28     , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(83212)->second   ,  1.48672e-29    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(84212)->second   ,  7.83831e-40    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(84216)->second   ,  5.93384e-34    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(86220)->second   ,  2.27532e-31    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(88224)->second   ,  1.29408e-27    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(88228)->second   ,  7.50892e-25    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(89228)->second   ,  9.16181e-29    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(90228)->second   ,  2.46936e-25    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(90232)->second   ,  1.89607e-15    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(92236)->second   ,  2.55855e-10    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(92240)->second   ,  3.48586e-14    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(93240)->second   ,  3.06064e-18    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(94240)->second   ,  7.22889e-09    , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(94244)->second   ,  0.00175978     , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(96248)->second   ,  0.967159       , 1e-10);
//   TEST_FLOATING_EQUALITY(new_number_densities.find(1093240)->second ,  2.97493e-16     , 1e-10);
//
//
//   TEST_FLOATING_EQUALITY(  3.73042e-31   ,  2.69414e-31    , 1e-10);
//   TEST_FLOATING_EQUALITY(  2.17021e-28   ,  1.5675e-28     , 1e-10);
//   TEST_FLOATING_EQUALITY(  1.96908e-29   ,  1.48672e-29    , 1e-10);
//   TEST_FLOATING_EQUALITY(  1.03814e-39   ,  7.83831e-40    , 1e-10);
//   TEST_FLOATING_EQUALITY(  8.21576e-34   ,  5.93384e-34    , 1e-10);
//   TEST_FLOATING_EQUALITY(  3.15015e-31   ,  2.27532e-31    , 1e-10);
//   TEST_FLOATING_EQUALITY(  1.94746e-27   ,  1.29408e-27    , 1e-10);
//   TEST_FLOATING_EQUALITY(  1.16225e-24   ,  7.50892e-25    , 1e-10);
//   TEST_FLOATING_EQUALITY(  1.25459e-28   ,  9.16181e-29    , 1e-10);
//   TEST_FLOATING_EQUALITY(  3.56743e-25   ,  2.46936e-25    , 1e-10);
//   TEST_FLOATING_EQUALITY(  2.5121e-15    ,  1.89607e-15    , 1e-10);
//   TEST_FLOATING_EQUALITY(  2.55855e-10   ,  2.55855e-10    , 1e-10);
//   TEST_FLOATING_EQUALITY(  3.48586e-14   ,  3.48586e-14    , 1e-10);
//   TEST_FLOATING_EQUALITY(  3.06064e-18   ,  3.06064e-18    , 1e-10);
//   TEST_FLOATING_EQUALITY(  7.22889e-09   ,  7.22889e-09    , 1e-10);
//   TEST_FLOATING_EQUALITY(  0.00175978    ,  0.00175978     , 1e-10);
//   TEST_FLOATING_EQUALITY(  0.967159      ,  0.967159       , 1e-10);
//   TEST_FLOATING_EQUALITY(  2.97493e-16   ,  2.97493e-16     , 1e-10);

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
// end decay_verification_analytical_problem.cpp
//---------------------------------------------------------------------------//
