//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw1NeutronScatteringEnergyDistribution.cpp
//! \author Alex Bennett
//! \brief  The neutron equiprobable bin scattering energy distribution class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <math.h>

// FRENSIE Includes
#include "MonteCarlo_AceLaw1NeutronScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

// Constructor
AceLaw1NeutronScatteringEnergyDistribution::AceLaw1NeutronScatteringEnergyDistribution( 
						 EnergyDistArray& energy_grid )
  : NeutronScatteringEnergyDistribution( 1u ),
    d_energy_grid( energy_grid )
{
  // Check to make sure the energy grid is filled
  testPrecondition( d_energy_grid.size() > 0 );
}

// Sample a scattering energy
double AceLaw1NeutronScatteringEnergyDistribution::sampleEnergy( 
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0 );
  testPrecondition( energy < std::numeric_limits<double>::infinity() );

  // Sample an energy bin
  double bin_location = Utility::RandomNumberGenerator::getRandomNumber<double>() * 
                        (d_energy_grid.front().second.size() - 1);

  int bin_index = (int)floor(bin_location);

  double outgoing_energy;

  // Check if energy is outside the grid
  if( energy < d_energy_grid.front().first ) 
  {
    outgoing_energy = d_energy_grid.front().second[bin_index] + (bin_location - bin_index) * 
                   (d_energy_grid.front().second[bin_index + 1] - d_energy_grid.front().second[bin_index]);
  }
  else if( energy > d_energy_grid.back().first )
  {  
    outgoing_energy = d_energy_grid.back().second[bin_index] + (bin_location - bin_index) *
                   (d_energy_grid.back().second[bin_index + 1] - d_energy_grid.back().second[bin_index]);
  }
  else
  {

    EnergyDistArray::const_iterator lower_bin_boundary, upper_bin_boundary;

    lower_bin_boundary = d_energy_grid.begin();
    upper_bin_boundary = d_energy_grid.end();

    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( lower_bin_boundary,
                                                                            upper_bin_boundary,
                                                                            energy);

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;
 
    // Calculate the interpolation fraction
    double interpolation_fraction = ( energy - lower_bin_boundary->first )/
                                    ( upper_bin_boundary->first - lower_bin_boundary->first );

    // Calculate the energy bounds
    double energy_lower = lower_bin_boundary->second.front() + interpolation_fraction *
                   (upper_bin_boundary->second.front() - lower_bin_boundary->second.front());

    double energy_upper = lower_bin_boundary->second.back() + interpolation_fraction *
                   (upper_bin_boundary->second.back() - lower_bin_boundary->second.back());

    // Sample the energy grid
    EnergyDistArray::const_iterator sampled_energy_dist;
    if( Utility::RandomNumberGenerator::getRandomNumber<double>() < interpolation_fraction )
    {
      sampled_energy_dist = upper_bin_boundary;
    }
    else
    {
      sampled_energy_dist = lower_bin_boundary;
    }

    // Sample the energy location
    double energy_location = sampled_energy_dist->second[bin_index] + 
                    Utility::RandomNumberGenerator::getRandomNumber<double>() * 
                    (sampled_energy_dist->second[bin_index + 1] - sampled_energy_dist->second[bin_index]);

    // Calculate the outgoing energy
    outgoing_energy = energy_lower + (energy_location - sampled_energy_dist->second.front()) *
                    (energy_upper - energy_lower) / 
                    (sampled_energy_dist->second.back() - sampled_energy_dist->second.front());
  }

  return outgoing_energy;

}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw1NeutronScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
