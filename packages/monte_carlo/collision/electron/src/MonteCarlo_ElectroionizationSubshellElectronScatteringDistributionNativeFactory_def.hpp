//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The electroionization subshell scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP


// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a electroionization subshell distribution
template <typename TwoDInterpPolicy,
          template<typename> class TwoDGridPolicy>
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroionization_data,
    const unsigned subshell,
    const double binding_energy,
    std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
      electroionization_subshell_distribution,
    const double evaluation_tol,
    const unsigned max_number_of_iterations,
    const bool renormalize_max_knock_on_energy )
{
  // Make sure the subshell is valid
  testPrecondition( subshell >= 0 );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );

  // Create the subshell distribution
  ThisType::createElectroionizationSubshellDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    raw_electroionization_data.getElectroionizationRecoilEnergy( subshell ),
    raw_electroionization_data.getElectroionizationRecoilPDF( subshell ),
    raw_electroionization_data.getElectroionizationEnergyGrid( subshell ),
    binding_energy,
    electroionization_subshell_distribution,
    evaluation_tol,
    max_number_of_iterations,
    raw_electroionization_data.isElectroionizationInRatioForm(),
    renormalize_max_knock_on_energy );
}

// Create a electroionization subshell distribution
template <typename TwoDInterpPolicy,
          template<typename> class TwoDGridPolicy>
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution(
    const std::map<double,std::vector<double> >& recoil_energy_data,
    const std::map<double,std::vector<double> >& recoil_pdf_data,
    const std::vector<double> energy_grid,
    const double binding_energy,
    std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
      electroionization_subshell_distribution,
    const double evaluation_tol,
    const unsigned max_number_of_iterations,
    const bool in_ratio_form,
    const bool renormalize_max_knock_on_energy )
{
  // Make sure the energy_grid is valid
  testPrecondition( energy_grid.size() > 1 );
  // Make sure the recoil data is valid
  testPrecondition( recoil_energy_data.size() == energy_grid.size() );
  testPrecondition( recoil_pdf_data.size() == energy_grid.size() );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );
  // Make sure both in_ratio_form and renormalize_max_knock_on_energy are not true
  testPrecondition( in_ratio_form != true ||
                    renormalize_max_knock_on_energy != true );

  // Subshell distribution
  std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>
    subshell_distribution;

  // Create the subshell distribution
  ThisType::createSubshellDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
            recoil_energy_data,
            recoil_pdf_data,
            energy_grid,
            binding_energy,
            subshell_distribution,
            evaluation_tol,
            max_number_of_iterations,
            renormalize_max_knock_on_energy );

  electroionization_subshell_distribution.reset(
    new ElectroionizationSubshellElectronScatteringDistribution(
            subshell_distribution,
            binding_energy,
            in_ratio_form ) );
}

// Create the subshell recoil distribution
template<typename TwoDInterpPolicy,
         template<typename> class TwoDGridPolicy>
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createSubshellDistribution(
    const std::map<double,std::vector<double> >& recoil_energy_data,
    const std::map<double,std::vector<double> >& recoil_pdf_data,
    const std::vector<double> energy_grid,
    const double binding_energy,
    std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>&
        subshell_distribution,
    const double evaluation_tol,
    const unsigned max_number_of_iterations,
    const bool renormalize_max_knock_on_energy )
{
  // Make sure the energy_grid is valid
  testPrecondition( energy_grid.size() > 1 );
  // Make sure the recoil data is valid
  testPrecondition( recoil_energy_data.size() == energy_grid.size() );
  testPrecondition( recoil_pdf_data.size() == energy_grid.size() );
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );

  // Create the scattering function
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  for( size_t n = 0; n < energy_grid.size(); ++n )
  {
    primary_grid[n] = energy_grid[n];

    // Get the energy of the knock-on electron energy at the incoming energy
    std::vector<double> knock_on_energy( recoil_energy_data.find( energy_grid[n] )->second );

    if( renormalize_max_knock_on_energy )
    {
      // If the grid point is not greater than the binding energy assumes for interpolation only
      if( energy_grid[n] <= binding_energy )
        primary_grid[n] = binding_energy + 2.0*knock_on_energy.back();

      // Make sure the max knock-on energy matches the incoming energy
      else
        knock_on_energy.back() = 0.5*(primary_grid[n] - binding_energy);
    }

    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>( knock_on_energy,
                                                               recoil_pdf_data.find( energy_grid[n] )->second ) );
  }

  // Create the scattering function
  subshell_distribution.reset(
    new Utility::InterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy<TwoDInterpPolicy> >(
            primary_grid,
            secondary_dists,
            1e-6,
            evaluation_tol,
            1e-16,
            max_number_of_iterations ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
