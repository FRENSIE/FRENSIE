//---------------------------------------------------------------------------//
//!
//! \file   fission_reaction_rate_verification_problem.cpp
//! \author Alex Bennett
//! \brief  fission reaction rate verification problem
//!
//---------------------------------------------------------------------------//

// Boost includes
#include <boost/unordered_map.hpp>

// Trilinos includes
#include <Teuchos_Array.hpp>
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE includes
#include "Transmutation_ModuleInterface_ODESolver.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Facemc_NuclearReactionType.hpp"


//---------------------------------------------------------------------------//
// Tests 
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( fission_reaction_rate, fission_reaction_rate )
{
   // Initialize number densitiy map
   boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,Teuchos::Array<std::pair<int,double> > > number_density_map;

   // Initialize number density arrays and fission reaction rates
   Teuchos::Array<std::pair<int,double> > number_densities(1);
   Teuchos::Array<std::pair<int,double> > fission_reaction_rates(3);

   // Fill number density arrays
   number_densities[0] = std::pair<int,double>(92235,1.0);

   // Fill fission reaction rates
   fission_reaction_rates[0] = std::pair<int,double>(26056,0.3);
   fission_reaction_rates[1] = std::pair<int,double>(27059,0.2);
   fission_reaction_rates[2] = std::pair<int,double>(28062,0.1);

   // Fill number density map
   number_density_map[ 1 ] = number_densities;

   // Set number densities
   Transmutation::ModuleInterface<Utility::ODESolver>::setNumberDensities( number_density_map );

   // Set reaction rates
   Transmutation::ModuleInterface<Utility::ODESolver>::setFissionReactionRates( 92235, 0.6, fission_reaction_rates, 1 ); 

   number_density_map.clear();

   // Burn the materials
   Transmutation::ModuleInterface<Utility::ODESolver>::burn( 1.0, number_density_map );

   TEST_FLOATING_EQUALITY(number_density_map[1].back().second, 0.5488116, 1e-6);
   TEST_FLOATING_EQUALITY(number_density_map[1][0].second, 0.2255942, 1e-6);
   TEST_FLOATING_EQUALITY(number_density_map[1][1].second, 0.1503961, 1e-6);
   TEST_FLOATING_EQUALITY(number_density_map[1][2].second, 0.0751981, 1e-6);
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
// end fission_reaction_rate_verification_problem.cpp
//---------------------------------------------------------------------------//
