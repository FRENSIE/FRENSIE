//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw11NuclearScatteringEnergyDistribution.cpp
//! \author Eli Moll
//! \brief  The nuclear law 11 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_AceLaw9NuclearScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_MaxwellFissionDistribution.hpp"

namespace MonteCarlo{

// Constructor
AceLaw11NuclearScatteringEnergyDistribution::AceLaw11NuclearScatteringEnergyDistribution( 
						 EnergyDistribution& a_distribution, 
						 EnergyDistribution& b_distribution,
						 double restriction_energy )
  : NuclearScatteringEnergyDistribution( 1u ),
    d_a_distribution( a_distribution ),
    d_b_distribution( b_distribution ),
    d_restriction_energy( restriction_energy )
{
  // Check to make sure the energy grid is filled
  testPrecondition( d_a_distribution.size() > 0 );
  testPrecondition( d_b_distribution.size() > 0 );
}

// Sample a scattering energy
double AceLaw1NuclearScatteringEnergyDistribution::sampleEnergy( 
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0 );
  testPrecondition( energy < std::numeric_limits<double>::infinity() );
  
  double outgoing_energy;
  double a_sampled;
  double b_sampled;
  
  // Check if energy is outside the (a) grid
  if( energy >= d_a_distribution.front().first and 
      energy <= d_a_distribution.back().first )
  {
    EnergyDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;

    lower_bin_boundary = d_a_distribution.begin();
    upper_bin_boundary = d_a_distribution.end();
    
    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							    lower_bin_boundary,
							    upper_bin_boundary,
							    energy );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Calculate the interpolation fraction
    double interpolation_fraction = (energy - lower_bin_boundary->first)/
      (upper_bin_boundary->first - lower_bin_boundary->first);
      
    a_sampled = (upper_bin_boundary->second -
                lower_bin_boundary->second)*interpolation_fraction + 
                lower_bin_boundary->second;
  }
  else if( energy < d_a_distribution.front().first ) 
  {
    // If below the energy grid, use the lowest possible energy  
    a_sampled = d_a_distribution.front().second;
  }
  else
  {  
    // If above the energy grid, use the highest possible energy
    a_sampled = d_a_distribution.back().second;
  }
  
  // Check if energy is outside the (b) grid
  if( energy >= d_b_distribution.front().first and 
      energy <= d_b_distribution.back().first )
  {
    EnergyDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;

    lower_bin_boundary = d_b_distribution.begin();
    upper_bin_boundary = d_b_distribution.end();
    
    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							    lower_bin_boundary,
							    upper_bin_boundary,
							    energy );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Calculate the interpolation fraction
    double interpolation_fraction = (energy - lower_bin_boundary->first)/
      (upper_bin_boundary->first - lower_bin_boundary->first);
      
    b_sampled = (upper_bin_boundary->second -
                lower_bin_boundary->second)*interpolation_fraction + 
                lower_bin_boundary->second;
  }
  else if( energy < d_b_distribution.front().first ) 
  {
    // If below the energy grid, use the lowest possible energy  
    b_sampled = d_b_distribution.front().second;
  }
  else
  {  
    // If above the energy grid, use the highest possible energy
    b_sampled = d_b_distribution.back().second;
  }  
  
  outgoing_energy = Utility::WattDistribution::sample( 
                                              energy, 
                                              a_sampled,
                                              b_sampled,
                                              d_restriction_energy );  
  
  return outgoing_energy;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw11NuclearScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
