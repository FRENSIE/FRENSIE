//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw1NuclearScatteringEnergyDistribution.cpp
//! \author Alex Bennett
//! \brief  The nuclear equiprobable bin scattering energy distribution class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <math.h>

// FRENSIE Includes
#include "MonteCarlo_AceLaw1NuclearScatteringEnergyDistribution.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

// Constructor
AceLaw1NuclearScatteringEnergyDistribution::AceLaw1NuclearScatteringEnergyDistribution(
						 EnergyDistArray& energy_grid )
  : NuclearScatteringEnergyDistribution( 1u ),
    d_energy_grid( energy_grid )
{
  // Check to make sure the energy grid is filled
  testPrecondition( d_energy_grid.size() > 0 );
}

// Sample a scattering energy
double AceLaw1NuclearScatteringEnergyDistribution::sampleEnergy(
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0 );
  testPrecondition( energy < std::numeric_limits<double>::infinity() );

  // Sample an energy bin
  double bin_location =
    Utility::RandomNumberGenerator::getRandomNumber<double>() *
    (Utility::get<1>(d_energy_grid.front()).size() - 1);

  int bin_index = (int)floor(bin_location);

  double outgoing_energy;

  // Check if energy is outside the grid
  if( energy < Utility::get<0>( d_energy_grid.front() ) )
  {
    outgoing_energy = Utility::get<1>(d_energy_grid.front())[bin_index] +
      (bin_location - bin_index) *
      (Utility::get<1>(d_energy_grid.front())[bin_index + 1] -
       Utility::get<1>(d_energy_grid.front())[bin_index]);
  }
  else if( energy >= Utility::get<0>( d_energy_grid.back() ) )
  {
    outgoing_energy = Utility::get<1>(d_energy_grid.back())[bin_index] +
      (bin_location - bin_index) *
      (Utility::get<1>(d_energy_grid.back())[bin_index + 1] -
       Utility::get<1>(d_energy_grid.back())[bin_index]);
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
    double interpolation_fraction =
      (energy - Utility::get<0>(*lower_bin_boundary))/
      (Utility::get<0>(*upper_bin_boundary) - Utility::get<0>(*lower_bin_boundary));

    // Calculate the energy bounds
    double energy_lower = Utility::get<1>(*lower_bin_boundary).front() +
      interpolation_fraction *
      (Utility::get<1>(*upper_bin_boundary).front() -
       Utility::get<1>(*lower_bin_boundary).front());

    double energy_upper = Utility::get<1>(*lower_bin_boundary).back() +
      interpolation_fraction *
      (Utility::get<1>(*upper_bin_boundary).back() -
       Utility::get<1>(*lower_bin_boundary).back());

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
    double energy_location = Utility::get<1>(*sampled_energy_dist)[bin_index] +
      Utility::RandomNumberGenerator::getRandomNumber<double>() *
      (Utility::get<1>(*sampled_energy_dist)[bin_index + 1] -
       Utility::get<1>(*sampled_energy_dist)[bin_index]);

    // Calculate the outgoing energy
    outgoing_energy = energy_lower +
      (energy_location - Utility::get<1>(*sampled_energy_dist).front()) *
      (energy_upper - energy_lower) /
      (Utility::get<1>(*sampled_energy_dist).back() -
       Utility::get<1>(*sampled_energy_dist).front());
  }

  return outgoing_energy;

}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw1NuclearScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
