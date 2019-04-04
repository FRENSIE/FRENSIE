//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_LineEnergyAdjointPhotonScatteringDistributionNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The line energy adjoint photon scattering distribution native
//!         factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_LINE_ENERGY_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_LINE_ENERGY_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_LineEnergyAdjointPhotonScatteringDistribution.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

/*! \brief The line energy adjoint photon scattering distribution factory
 * class that uses native data
 */
class LineEnergyAdjointPhotonScatteringDistributionNativeFactory
{

private:

  // This type
  typedef LineEnergyAdjointPhotonScatteringDistributionNativeFactory ThisType;

public:

  //! Create the pair production distribution
  static void createPairProductionDistribution(
         const Data::AdjointElectronPhotonRelaxationDataContainer&
         raw_adjoint_photoatom_data,
         std::shared_ptr<LineEnergyAdjointPhotonScatteringDistribution>&
         pair_production_distribution,
         double& cross_section_value,
         const double max_energy );

  //! Create the triplet production distribution
  static void createTripletProductionDistribution(
         const Data::AdjointElectronPhotonRelaxationDataContainer&
         raw_adjoint_photoatom_data,
         std::shared_ptr<LineEnergyAdjointPhotonScatteringDistribution>&
         triplet_production_distribution,
         double& cross_section_value,
         const double max_energy );

private:

  // Create an energy distribution from the raw distribution data
  static void createEnergyDistributionFromRawDistData(
                       std::shared_ptr<const Utility::TabularUnivariateDistribution>&
                       energy_distribution,
                       const std::vector<double>& energy_grid,
                       const std::vector<double>& energy_dist_values,
                       const double max_energy );

  // Calculate the cross section value
  static void calculateCrossSectionValue(
                          const std::vector<double>& norm_constant_energy_grid,
                          const std::vector<double>& norm_constant_values,
                          const double max_energy,
                          double& cross_section_value );
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_LINE_ENERGY_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_LineEnergyAdjointPhotonScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//
