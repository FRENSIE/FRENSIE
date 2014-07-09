//---------------------------------------------------------------------------//
//!
//! \file   tstModuleInterface.cpp
//! \author Alex Bennett
//! \brief  Module Interface unit test
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Transmutation_ModuleInterface_ODESolver.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Facemc_NuclearReactionType.hpp"

//---------------------------------------------------------------------------//
// Testing Variables 
//---------------------------------------------------------------------------//
 

//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( ModuleInterface, burn )
{
   // Initialize number densitiy map
   boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,Teuchos::Array<std::pair<int,double> > > number_density_map;

   // Initialize number density arrays
   Teuchos::Array<std::pair<int,double> > number_densities_1(1);
   Teuchos::Array<std::pair<int,double> > number_densities_2(1);

   // Fill number density arrays
   number_densities_1[0] = std::pair<int,double>(1001,1.0);
   number_densities_2[0] = std::pair<int,double>(1002,1.0);

   // Fill number density map
   number_density_map[ 1 ] = number_densities_1;
   number_density_map[ 5 ] = number_densities_2;

   // Set number densities
   Transmutation::ModuleInterface<Utility::ODESolver>::setNumberDensities( number_density_map );

   // Initialize reaction rate array
   Teuchos::Array<std::pair<int,double> > reaction_rates(1);

   // Fill reaction rate array
   reaction_rates[0] = std::pair<int,double>(1001,5e-10);

   // Set reaction rates
   Transmutation::ModuleInterface<Utility::ODESolver>::setReactionRates( Facemc::N__GAMMA_REACTION, reaction_rates, 1);

   reaction_rates[0] = std::pair<int,double>(1002,5e-10);

   Transmutation::ModuleInterface<Utility::ODESolver>::setReactionRates( Facemc::N__GAMMA_REACTION, reaction_rates, 5);

   number_density_map.clear();

   // Burn the materials
   Transmutation::ModuleInterface<Utility::ODESolver>::burn( 1000000000.0, number_density_map );   
 
//   // print out the results
//   boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,Teuchos::Array<std::pair<int,double> > >::iterator i;
//   for(i = number_density_map.begin(); i != number_density_map.end(); ++i)
//   {
//      std::cout << "cell number : " << i->first << std::endl;
//      for(Teuchos::Array<std::pair<int,double> >::iterator j = i->second.begin(); j != i->second.end(); ++j)
//      {
//         std::cout << j->first << " " << j->second << std::endl;
//      }
//      std::cout << std::endl;
//   }

   // Test results
   TEST_FLOATING_EQUALITY(number_density_map[1][0].second,0.60653066,1e-10)
   TEST_FLOATING_EQUALITY(number_density_map[1][1].second,0.39346934,1e-9)
   TEST_FLOATING_EQUALITY(number_density_map[5][0].second,0.60653066,1e-9)
   TEST_FLOATING_EQUALITY(number_density_map[5][1].second,0.17086004,1e-6)
   TEST_FLOATING_EQUALITY(number_density_map[5][2].second,0.22260930,1e-6)
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
// end tstModuleInterface.cpp 
//---------------------------------------------------------------------------//
