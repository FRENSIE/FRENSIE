//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_LineEnergyAdjointPhotonScatteringDistributionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  The line energy adjoint photon scattering distribution native
//!         factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_LineEnergyAdjointPhotonScatteringDistributionNativeFactory.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create the pair production distribution
/*! \details The cross section will be multiplied by two to account for the
 * two annihilation photons that are created in the forward reaction.
 */
void LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createPairProductionDistribution(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          std::shared_ptr<LineEnergyAdjointPhotonScatteringDistribution>&
          pair_production_distribution,
          double& cross_section_value,
          const double max_energy )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy >
                    raw_adjoint_photoatom_data.getAdjointPairProductionEnergyDistributionGrid().front() );
  testPrecondition( max_energy <=
                    raw_adjoint_photoatom_data.getAdjointPairProductionEnergyDistributionGrid().back() );

  // Construct the energy distribution
  std::shared_ptr<const Utility::TabularUnivariateDistribution> energy_distribution;

  ThisType::createEnergyDistributionFromRawDistData(
       energy_distribution,
       raw_adjoint_photoatom_data.getAdjointPairProductionEnergyDistributionGrid(),
       raw_adjoint_photoatom_data.getAdjointPairProductionEnergyDistribution(),
       max_energy );

  // Evaluate the cross section
  ThisType::calculateCrossSectionValue(
       raw_adjoint_photoatom_data.getAdjointPairProductionEnergyDistributionNormConstantGrid(),
       raw_adjoint_photoatom_data.getAdjointPairProductionEnergyDistributionNormConstant(),
       max_energy,
       cross_section_value );

  // Multiply the cross section by 2 to account for the two annihilation
  // photons
  cross_section_value *= 2.0;

  // Construct the scattering distribution
  pair_production_distribution.reset(
            new LineEnergyAdjointPhotonScatteringDistribution(
                         Utility::PhysicalConstants::electron_rest_mass_energy,
                         cross_section_value,
                         energy_distribution ) );
}

// Create the triplet production distribution
/*! \details The cross section will be multiplied by two to account for the
 * two annihilation photons that are created in the forward reaction.
 */
void LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createTripletProductionDistribution(
          const Data::AdjointElectronPhotonRelaxationDataContainer&
          raw_adjoint_photoatom_data,
          std::shared_ptr<LineEnergyAdjointPhotonScatteringDistribution>&
          triplet_production_distribution,
          double& cross_section_value,
          const double max_energy )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy >
                    raw_adjoint_photoatom_data.getAdjointTripletProductionEnergyDistributionGrid().front() );
  testPrecondition( max_energy <=
                    raw_adjoint_photoatom_data.getAdjointTripletProductionEnergyDistributionGrid().back() );

  // Construct the energy distribution
  std::shared_ptr<const Utility::TabularUnivariateDistribution> energy_distribution;

  ThisType::createEnergyDistributionFromRawDistData(
       energy_distribution,
       raw_adjoint_photoatom_data.getAdjointTripletProductionEnergyDistributionGrid(),
       raw_adjoint_photoatom_data.getAdjointTripletProductionEnergyDistribution(),
       max_energy );

  // Evaluate the cross section
  ThisType::calculateCrossSectionValue(
       raw_adjoint_photoatom_data.getAdjointTripletProductionEnergyDistributionNormConstantGrid(),
       raw_adjoint_photoatom_data.getAdjointTripletProductionEnergyDistributionNormConstant(),
       max_energy,
       cross_section_value );

  // Multiply the cross section by 2 to account for the two annihilation
  // photons
  cross_section_value *= 2.0;

  // Construct the scattering distribution
  triplet_production_distribution.reset(
            new LineEnergyAdjointPhotonScatteringDistribution(
                         Utility::PhysicalConstants::electron_rest_mass_energy,
                         cross_section_value,
                         energy_distribution ) );
}

// Create an energy distribution from the raw distribution data
void LineEnergyAdjointPhotonScatteringDistributionNativeFactory::createEnergyDistributionFromRawDistData(
                       std::shared_ptr<const Utility::TabularUnivariateDistribution>&
                       energy_distribution,
                       const std::vector<double>& energy_grid,
                       const std::vector<double>& energy_dist_values,
                       const double max_energy )
{
  if( max_energy < energy_grid.back() )
  {
    // Find the bin that contains the max energy
    size_t bin_index = Utility::Search::binaryLowerBoundIndex(
                                                           energy_grid.begin(),
                                                           energy_grid.end(),
                                                           max_energy );

    // Determine the energy distribution value at the max energy
    double energy_dist_value_at_max_energy =
      Utility::LinLin::interpolate( energy_grid[bin_index],
                                    energy_grid[bin_index+1],
                                    max_energy,
                                    energy_dist_values[bin_index],
                                    energy_dist_values[bin_index+1] );

    // Create the new energy grid and distribution values
    std::vector<double> sliced_energy_grid( energy_grid.begin(),
                                            energy_grid.begin()+bin_index+1 );
    sliced_energy_grid.push_back( max_energy );

    std::vector<double> sliced_energy_dist_values(
                                      energy_dist_values.begin(),
                                      energy_dist_values.begin()+bin_index+1 );
    sliced_energy_dist_values.push_back( energy_dist_value_at_max_energy );

    energy_distribution.reset(
                          new Utility::TabularDistribution<Utility::LinLin>(
                                                 sliced_energy_grid,
                                                 sliced_energy_dist_values ) );
  }
  else if( max_energy == energy_grid.back() )
  {
    energy_distribution.reset(
                           new Utility::TabularDistribution<Utility::LinLin>(
                                                        energy_grid,
                                                        energy_dist_values ) );
  }
  // else: throw exception?
}

// Calculate the cross section value
void LineEnergyAdjointPhotonScatteringDistributionNativeFactory::calculateCrossSectionValue(
                          const std::vector<double>& norm_constant_energy_grid,
                          const std::vector<double>& norm_constant_values,
                          const double max_energy,
                          double& cross_section_value )
{
  // Construct the norm constant distribution
  Utility::TabularDistribution<Utility::LinLin> norm_constant_dist(
                                                     norm_constant_energy_grid,
                                                     norm_constant_values );

  cross_section_value = norm_constant_dist.evaluate( max_energy );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_LineEnergyAdjointPhotonScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
