//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw7NuclearScatteringEnergyDistribution.cpp
//! \author Eli Moll
//! \brief  The nuclear law 7 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_AceLaw7NuclearScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_MaxwellFissionDistribution.hpp"

namespace MonteCarlo{

// Constructor
AceLaw7NuclearScatteringEnergyDistribution::AceLaw7NuclearScatteringEnergyDistribution( 
						 EnergyDistribution& energy_distribution, 
						 double restriction_energy )
  : NuclearScatteringEnergyDistribution( 1u ),
    d_energy_distribution( energy_distribution ),
    d_restriction_energy( restriction_energy )
{
  // Check to make sure the energy grid is filled
  testPrecondition( d_energy_distribution.size() > 0 );
}

// Sample a scattering energy
double AceLaw1NuclearScatteringEnergyDistribution::sampleEnergy( 
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0 );
  testPrecondition( energy < std::numeric_limits<double>::infinity() );
  
  double outgoing_energy;
  
  // Check if energy is outside the grid
  if( energy >= d_energy_distribution.front().first and 
      energy <= d_energy_distribution.back().first )
  {
    EnergyDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;

    lower_bin_boundary = d_energy_distribution.begin();
    upper_bin_boundary = d_energy_distribution.end();
    
    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							    lower_bin_boundary,
							    upper_bin_boundary,
							    energy );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Calculate the interpolation fraction
    double interpolation_fraction = (energy - lower_bin_boundary->first)/
      (upper_bin_boundary->first - lower_bin_boundary->first);
      
    double T = (upper_bin_boundary->second -
                lower_bin_boundary->second)*interpolation_fraction + 
                lower_bin_boundary->second;
               
    outgoing_energy = Utility::MaxwellFissionDistribution::sample( 
                                              energy, 
                                              T,
                                              d_restriction_energy );
  }
  else if( energy < d_energy_distribution.front().first ) 
  {
    // If below the energy grid, use the lowest possible energy  
    double T = d_energy_distribution.front().second;
    
    outgoing_energy = Utility::MaxwellFissionDistribution::sample( 
                                              energy, 
                                              T,
                                              d_restriction_energy );
  }
  else
  {  
    // If above the energy grid, use the highest possible energy
    double T = d_energy_distribution.back().second;
    
    outgoing_energy = Utility::MaxwellFissionDistribution::sample( 
                                              energy, 
                                              T,
                                              d_restriction_energy );
  }
  
  return outgoing_energy;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw7NuclearScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
