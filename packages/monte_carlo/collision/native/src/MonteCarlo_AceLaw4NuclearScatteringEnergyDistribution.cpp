//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.cpp
//! \author Alex Bennett
//! \brief  The nuclear law 4 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

// Constructor
AceLaw4NuclearScatteringEnergyDistribution::AceLaw4NuclearScatteringEnergyDistribution( EnergyDistribution& energy_distribution )
  : NuclearScatteringEnergyDistribution( 4u ),
    d_energy_distribution( energy_distribution )
{
  // Check to make sure the energy grid is filled
  testPrecondition( d_energy_distribution.size() > 0 );
}


// Sample a scattering energy
double AceLaw4NuclearScatteringEnergyDistribution::sampleEnergy( const double energy ) const
{
  unsigned incoming_index, outgoing_index;

  double energy_prime;

  return this->sampleEnergy( energy, incoming_index, outgoing_index, energy_prime );
}


// Sample a scattering energy
double AceLaw4NuclearScatteringEnergyDistribution::sampleEnergy( 
						    const double energy, 
						    unsigned& incoming_index, 
						    unsigned& outgoing_index,
						    double& energy_prime) const
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

    double random_num = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( random_num < interpolation_fraction )
    {
      energy_prime = 
	upper_bin_boundary->second->sampleAndRecordBinIndex( outgoing_index );

      incoming_index = std::distance( d_energy_distribution.begin(), 
				      upper_bin_boundary);
    }
    else
    {
      energy_prime = 
	lower_bin_boundary->second->sampleAndRecordBinIndex( outgoing_index );
   
      incoming_index = std::distance( d_energy_distribution.begin(), 
				      lower_bin_boundary);
    }

    // Calculate the energy bounds
    double energy_lower = lower_bin_boundary->second->getLowerBoundOfIndepVar()
      + interpolation_fraction*
      (upper_bin_boundary->second->getLowerBoundOfIndepVar() - 
       lower_bin_boundary->second->getLowerBoundOfIndepVar());

    double energy_upper = upper_bin_boundary->second->getUpperBoundOfIndepVar()
      + interpolation_fraction*
      (upper_bin_boundary->second->getUpperBoundOfIndepVar() - 
       lower_bin_boundary->second->getUpperBoundOfIndepVar());

    // Calculate the outgoing energy
    if ( energy_upper == energy_lower )
    {
      // This is a case which occurs when two delta distributions at
      // neighboring neutron energies produce photons of the same energy.
      // An example case can be see in MT-102001, H-1_250.0K-v8.
      
      outgoing_energy = energy_lower;
    }
    else if( random_num < interpolation_fraction )
    {
      outgoing_energy = energy_lower + 
	(energy_prime - upper_bin_boundary->second->getLowerBoundOfIndepVar())*
	(energy_upper - energy_lower) / 
	(upper_bin_boundary->second->getUpperBoundOfIndepVar() - 
	 lower_bin_boundary->second->getLowerBoundOfIndepVar());
    }
    else
    {
      outgoing_energy = energy_lower + 
	(energy_prime - lower_bin_boundary->second->getLowerBoundOfIndepVar())*
	(energy_upper - energy_lower) / 
	(upper_bin_boundary->second->getUpperBoundOfIndepVar() - 
	 lower_bin_boundary->second->getLowerBoundOfIndepVar());
    }
  }
  else if( energy < d_energy_distribution.front().first ) 
  {  
    outgoing_energy = 
      d_energy_distribution.front().second->sampleAndRecordBinIndex( 
							       outgoing_index);
    
    energy_prime = outgoing_energy;
    incoming_index = 0;
  }
  else
  {    
    outgoing_energy = 
      d_energy_distribution.back().second->sampleAndRecordBinIndex( 
							      outgoing_index );
    
    energy_prime = outgoing_energy;
    incoming_index = d_energy_distribution.size() - 1; 
  }

  return outgoing_energy;

}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
