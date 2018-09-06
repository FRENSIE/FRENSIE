//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw9NuclearScatteringEnergyDistribution.cpp
//! \author Eli Moll
//! \brief  The nuclear law 9 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_AceLaw9NuclearScatteringEnergyDistribution.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_EvaporationDistribution.hpp"

namespace MonteCarlo{

// Constructor
AceLaw9NuclearScatteringEnergyDistribution::AceLaw9NuclearScatteringEnergyDistribution(
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
double AceLaw9NuclearScatteringEnergyDistribution::sampleEnergy(
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0 );
  testPrecondition( energy < std::numeric_limits<double>::infinity() );

  double outgoing_energy;

  // Check if energy is outside the grid
  if( energy >= Utility::get<0>( d_energy_distribution.front() ) &&
      energy <= Utility::get<0>( d_energy_distribution.back() ) )
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
    double interpolation_fraction =
      (energy - Utility::get<0>(*lower_bin_boundary))/
      (Utility::get<0>(*upper_bin_boundary) - Utility::get<0>( *lower_bin_boundary));

    double T = interpolation_fraction*
      (Utility::get<1>(*upper_bin_boundary) - Utility::get<1>(*lower_bin_boundary)) +
      Utility::get<1>(*lower_bin_boundary);

    outgoing_energy = Utility::EvaporationDistribution::sample(
                                              energy,
                                              T,
                                              d_restriction_energy );
  }
  else if( energy < Utility::get<0>( d_energy_distribution.front() ) )
  {
    // If below the energy grid, use the lowest possible energy
    double T = Utility::get<1>( d_energy_distribution.front() );

    outgoing_energy = Utility::EvaporationDistribution::sample(
                                              energy,
                                              T,
                                              d_restriction_energy );

  }
  else
  {
    // If above the energy grid, use the highest possible energy
    double T = Utility::get<1>( d_energy_distribution.back() );

    outgoing_energy = Utility::EvaporationDistribution::sample(
                                              energy,
                                              T,
                                              d_restriction_energy );
  }

  return outgoing_energy;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw9NuclearScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
