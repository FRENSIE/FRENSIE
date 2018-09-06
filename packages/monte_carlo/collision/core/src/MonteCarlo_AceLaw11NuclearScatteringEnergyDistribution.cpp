//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw11NuclearScatteringEnergyDistribution.cpp
//! \author Eli Moll
//! \brief  The nuclear law 11 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_AceLaw11NuclearScatteringEnergyDistribution.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_WattDistribution.hpp"

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
double AceLaw11NuclearScatteringEnergyDistribution::sampleEnergy(
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0 );
  testPrecondition( energy < std::numeric_limits<double>::infinity() );

  double outgoing_energy;
  double a_sampled;
  double b_sampled;

  // Sample the distribution of a(E)
  if( energy >= Utility::get<0>(d_a_distribution.front()) &&
      energy <= Utility::get<0>(d_a_distribution.back()) )
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
    double interpolation_fraction =
      (energy - Utility::get<0>(*lower_bin_boundary))/
      (Utility::get<0>(*upper_bin_boundary) - Utility::get<0>(*lower_bin_boundary));

    a_sampled = interpolation_fraction*
      (Utility::get<1>(*upper_bin_boundary) - Utility::get<1>(*lower_bin_boundary)) +
      Utility::get<1>(*lower_bin_boundary);
  }
  else if( energy < Utility::get<0>(d_a_distribution.front()) )
  {
    // If below the energy grid, use the lowest possible energy
    a_sampled = Utility::get<1>(d_a_distribution.front());
  }
  else
  {
    // If above the energy grid, use the highest possible energy
    a_sampled = Utility::get<1>(d_a_distribution.back());
  }


  // Sample the distribution of b(E)
  if( energy >= Utility::get<0>(d_b_distribution.front()) &&
      energy <= Utility::get<0>(d_b_distribution.back()) )
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
    double interpolation_fraction =
      (energy - Utility::get<0>(*lower_bin_boundary))/
      (Utility::get<0>(*upper_bin_boundary) -
       Utility::get<0>(*lower_bin_boundary));

    b_sampled = interpolation_fraction*
      (Utility::get<1>(*upper_bin_boundary) - Utility::get<1>(*lower_bin_boundary)) +
      Utility::get<1>(*lower_bin_boundary);
  }
  else if( energy < Utility::get<0>(d_b_distribution.front()) )
  {
    // If below the energy grid, use the lowest possible energy
    b_sampled = Utility::get<1>(d_b_distribution.front());
  }
  else
  {
    // If above the energy grid, use the highest possible energy
    b_sampled = Utility::get<1>(d_b_distribution.back());
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
