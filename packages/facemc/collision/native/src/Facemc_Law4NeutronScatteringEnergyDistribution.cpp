//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_Law4NeutronScatteringEnergyDistribution.cpp
//! \author Alex Bennett
//! \brief  The neutron law 4 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Facemc_Law4NeutronScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace Facemc{

// Constructor
Law4NeutronScatteringEnergyDistribution::Law4NeutronScatteringEnergyDistribution( EnergyDistribution& energy_distribution )
  : NeutronScatteringEnergyDistribution( false ),
    d_energy_distribution( energy_distribution )
{
  // Check to make sure the energy grid is filled
  testPrecondition( d_energy_distribution.size() > 0 );
}


// Sample a scattering energy
double Law4NeutronScatteringEnergyDistribution::sampleEnergy( const double energy ) const
{
  unsigned sampled_index, incoming_index;

  return this->sampleEnergy( energy, sampled_index, incoming_index );
}


// Sample a scattering energy
double Law4NeutronScatteringEnergyDistribution::sampleEnergy( const double energy, 
                                                              unsigned& sampled_index, 
                                                              unsigned& incoming_index) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0 );
  testPrecondition( energy < std::numeric_limits<double>::infinity() );

  double outgoing_energy;

  // Check if energy is outside the grid
  if( energy < d_energy_distribution.front().first ) 
  {
    outgoing_energy = d_energy_distribution.front().second->sample();
  }
  else if( energy > d_energy_distribution.back().first )
  {  
    outgoing_energy = d_energy_distribution.back().second->sample(); 
  }
  else
  {

    EnergyDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;

    lower_bin_boundary = d_energy_distribution.begin();
    upper_bin_boundary = d_energy_distribution.end();

    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( lower_bin_boundary,
                                                                            upper_bin_boundary,
                                                                            energy);

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Calculate incoming bin index
    incoming_index = std::distance(d_energy_distribution.begin(), lower_bin_boundary);
 
    // Calculate the interpolation fraction
    double interpolation_fraction = ( energy - lower_bin_boundary->first )/
                                    ( upper_bin_boundary->first - lower_bin_boundary->first );

    double random_num = Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( random_num < interpolation_fraction )
      outgoing_energy = upper_bin_boundary->second->sample( sampled_index );
    else
      outgoing_energy = lower_bin_boundary->second->sample( sampled_index );

    // Calculate the energy bounds
    double energy_lower = lower_bin_boundary->second->getLowerBoundOfIndepVar() + interpolation_fraction *
                   (upper_bin_boundary->second->getLowerBoundOfIndepVar() - lower_bin_boundary->second->getLowerBoundOfIndepVar());

    double energy_upper = lower_bin_boundary->second->getUpperBoundOfIndepVar() + interpolation_fraction *
                   (upper_bin_boundary->second->getUpperBoundOfIndepVar() - lower_bin_boundary->second->getUpperBoundOfIndepVar());


    // Calculate the outgoing energy
    if( random_num < interpolation_fraction )
      outgoing_energy = energy_lower + (outgoing_energy - upper_bin_boundary->second->getLowerBoundOfIndepVar()) *
                      (energy_upper - energy_lower) / 
                      (upper_bin_boundary->second->getUpperBoundOfIndepVar() - 
                       upper_bin_boundary->second->getLowerBoundOfIndepVar());
    else
      outgoing_energy = energy_lower + (outgoing_energy - lower_bin_boundary->second->getLowerBoundOfIndepVar()) *
                      (energy_upper - energy_lower) / 
                      (lower_bin_boundary->second->getUpperBoundOfIndepVar() - 
                       lower_bin_boundary->second->getLowerBoundOfIndepVar());
  }

  return outgoing_energy;

}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_Law4NeutronScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
