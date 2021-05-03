//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.cpp
//! \author Alex Bennett
//! \brief  The nuclear law 4 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp"
#include "Utility_TwoDGridPolicy.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

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
  size_t incoming_index, outgoing_index;

  double energy_prime;

  return this->sampleEnergy( energy, incoming_index, outgoing_index, energy_prime );
}

void AceLaw4NuclearScatteringEnergyDistribution::getDistribution( AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution& energy_distribution )
{
  energy_distribution = d_energy_distribution;
}

// Sample a scattering energy
double AceLaw4NuclearScatteringEnergyDistribution::sampleEnergy(
						    const double energy,
						    size_t& incoming_index,
						    size_t& outgoing_index,
						    double& energy_prime) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0 );
  testPrecondition( energy < std::numeric_limits<double>::infinity() );

  double outgoing_energy;
  
  // Check if the energy is outside of the grid
  if( energy >= Utility::get<0>( d_energy_distribution.front() ) &&
      energy < Utility::get<0>( d_energy_distribution.back() ) )
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

    EnergyDistribution::const_iterator sampled_bin_boundary;
        
    auto sample_functor = std::bind<double>(
              &Utility::TabularUnivariateDistribution::sampleAndRecordBinIndex,
              std::placeholders::_1,
              std::ref(outgoing_index) );

    auto lower_bound_functor = std::bind<double>( &Utility::UnitBase<Utility::LinLinLin>::calculateLowerBound<double,double,EnergyDistribution::const_iterator>,
                                                  std::placeholders::_1,
                                                  lower_bin_boundary,
                                                  upper_bin_boundary );

    auto upper_bound_functor = std::bind<double>( &Utility::UnitBase<Utility::LinLinLin>::calculateUpperBound<double,double,EnergyDistribution::const_iterator>,
                                                  std::placeholders::_1,
                                                  lower_bin_boundary,
                                                  upper_bin_boundary );

    outgoing_energy = Utility::UnitBase<Utility::LinLinLin>::sampleDetailed(
                                                          sample_functor,
                                                          lower_bound_functor,
                                                          upper_bound_functor,
                                                          energy,
                                                          lower_bin_boundary,
                                                          upper_bin_boundary,
                                                          sampled_bin_boundary,
                                                          energy_prime );

    incoming_index = std::distance( d_energy_distribution.begin(),
                                    sampled_bin_boundary );
  }
  else if( energy < Utility::get<0>( d_energy_distribution.front() ) )
  {
    outgoing_energy =
      Utility::get<1>(d_energy_distribution.front())->sampleAndRecordBinIndex(
        						      outgoing_index );

    energy_prime = outgoing_energy;
    incoming_index = 0;
  }
  else
  {
    outgoing_energy =
      Utility::get<1>(d_energy_distribution.back())->sampleAndRecordBinIndex(
        						      outgoing_index );

    energy_prime = outgoing_energy;
    incoming_index = d_energy_distribution.size() - 1;
  }
  
  return outgoing_energy;

  // // Check if energy is outside the grid
  // if( energy >= Utility::get<0>( d_energy_distribution.front() ) &&
  //     energy < Utility::get<0>( d_energy_distribution.back() ) )
  // {
  //   EnergyDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;

  //   lower_bin_boundary = d_energy_distribution.begin();
  //   upper_bin_boundary = d_energy_distribution.end();

  //   lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>(
  //       						    lower_bin_boundary,
  //       						    upper_bin_boundary,
  //       						    energy );

  //   upper_bin_boundary = lower_bin_boundary;
  //   ++upper_bin_boundary;

  //   // Calculate the interpolation fraction
  //   double interpolation_fraction =
  //     (energy - Utility::get<0>(*lower_bin_boundary))/
  //     (Utility::get<0>(*upper_bin_boundary) - Utility::get<0>(*lower_bin_boundary));

  //   double random_num =
  //     Utility::RandomNumberGenerator::getRandomNumber<double>();

  //   if( random_num < interpolation_fraction )
  //   {
  //     energy_prime =
  //       Utility::get<1>(*upper_bin_boundary)->sampleAndRecordBinIndex( outgoing_index );

  //     incoming_index = std::distance( d_energy_distribution.begin(),
  //       			      upper_bin_boundary);
  //   }
  //   else
  //   {
  //     energy_prime =
  //       Utility::get<1>(*lower_bin_boundary)->sampleAndRecordBinIndex( outgoing_index );

  //     incoming_index = std::distance( d_energy_distribution.begin(),
  //       			      lower_bin_boundary);
  //   }

  //   // Calculate the energy bounds
  //   double energy_lower = Utility::get<1>(*lower_bin_boundary)->getLowerBoundOfIndepVar()
  //     + interpolation_fraction*
  //     (Utility::get<1>(*upper_bin_boundary)->getLowerBoundOfIndepVar() -
  //      Utility::get<1>(*lower_bin_boundary)->getLowerBoundOfIndepVar());

  //   double energy_upper = Utility::get<1>(*upper_bin_boundary)->getUpperBoundOfIndepVar()
  //     + interpolation_fraction*
  //     (Utility::get<1>(*upper_bin_boundary)->getUpperBoundOfIndepVar() -
  //      Utility::get<1>(*lower_bin_boundary)->getUpperBoundOfIndepVar());

  //   // Calculate the outgoing energy
  //   if ( energy_upper == energy_lower )
  //   {
  //     // This is a case which occurs when two delta distributions at
  //     // neighboring neutron energies produce photons of the same energy.
  //     // An example case can be see in MT-102001, H-1_250.0K-v8.

  //     outgoing_energy = energy_lower;
  //   }
  //   else if( random_num < interpolation_fraction )
  //   {
  //     outgoing_energy = energy_lower +
  //       (energy_prime - Utility::get<1>(*upper_bin_boundary)->getLowerBoundOfIndepVar())*
  //       (energy_upper - energy_lower) /
  //       (Utility::get<1>(*upper_bin_boundary)->getUpperBoundOfIndepVar() -
  //        Utility::get<1>(*lower_bin_boundary)->getLowerBoundOfIndepVar());
  //   }
  //   else
  //   {
  //     outgoing_energy = energy_lower +
  //       (energy_prime - Utility::get<1>(*lower_bin_boundary)->getLowerBoundOfIndepVar())*
  //       (energy_upper - energy_lower) /
  //       (Utility::get<1>(*upper_bin_boundary)->getUpperBoundOfIndepVar() -
  //        Utility::get<1>(*lower_bin_boundary)->getLowerBoundOfIndepVar());
  //   }
  // }
  // else if( energy < Utility::get<0>(d_energy_distribution.front() ) )
  // {
  //   outgoing_energy =
  //     Utility::get<1>(d_energy_distribution.front() )->sampleAndRecordBinIndex(
  //       						       outgoing_index);

  //   energy_prime = outgoing_energy;
  //   incoming_index = 0;
  // }
  // else
  // {
  //   outgoing_energy =
  //     Utility::get<1>(d_energy_distribution.back())->sampleAndRecordBinIndex(
  //       						      outgoing_index );

  //   energy_prime = outgoing_energy;
  //   incoming_index = d_energy_distribution.size() - 1;
  // }

  // return outgoing_energy;
  
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
