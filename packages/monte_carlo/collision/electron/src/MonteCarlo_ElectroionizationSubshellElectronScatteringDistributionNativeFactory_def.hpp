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
    const ElectroionizationSamplingType sampling_type,
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

  if( !raw_electroionization_data.hasElectroionizationOutgoingEnergyData() ||
      sampling_type == KNOCK_ON_SAMPLING )
  {
    ThisType::createElectroionizationSubshellDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      raw_electroionization_data.getElectroionizationRecoilEnergy( subshell ),
      raw_electroionization_data.getElectroionizationRecoilPDF( subshell ),
      raw_electroionization_data.getElectroionizationEnergyGrid( subshell ),
      binding_energy,
      electroionization_subshell_distribution,
      sampling_type,
      evaluation_tol,
      max_number_of_iterations,
      renormalize_max_knock_on_energy );
  }
  else if( sampling_type == OUTGOING_ENERGY_SAMPLING )
  {
    // Subshell distribution
    std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>
      subshell_distribution;

    // Create the subshell outgoing energy distribution
    ThisType::createOutgoingDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      raw_electroionization_data.getElectroionizationOutgoingEnergy( subshell ),
      raw_electroionization_data.getElectroionizationOutgoingPDF( subshell ),
      raw_electroionization_data.getElectroionizationEnergyGrid( subshell ),
      binding_energy,
      subshell_distribution,
      evaluation_tol,
      max_number_of_iterations );

    electroionization_subshell_distribution.reset(
      new ElectroionizationSubshellElectronScatteringDistribution(
              subshell_distribution,
              sampling_type,
              binding_energy ) );
  }
  else if( sampling_type == OUTGOING_ENERGY_RATIO_SAMPLING )
  {
    // Subshell distribution
    std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>
      subshell_distribution;

    // Create the subshell outgoing energy ratio distribution
    ThisType::createOutgoingRatioDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      raw_electroionization_data.getElectroionizationOutgoingEnergy( subshell ),
      raw_electroionization_data.getElectroionizationOutgoingPDF( subshell ),
      raw_electroionization_data.getElectroionizationEnergyGrid( subshell ),
      binding_energy,
      subshell_distribution,
      evaluation_tol,
      max_number_of_iterations );

    electroionization_subshell_distribution.reset(
      new ElectroionizationSubshellElectronScatteringDistribution(
              subshell_distribution,
              sampling_type,
              binding_energy ) );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                    "The ElectroionizationSamplingType " <<
                    sampling_type <<
                    " is invalid or currently not supported!" );
  }
}

// Create a electroionization subshell distribution
template <typename TwoDInterpPolicy,
          template<typename> class TwoDGridPolicy>
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution(
    const std::map<double,std::vector<double> >& recoil_energy_data,
    const std::map<double,std::vector<double> >& recoil_pdf_data,
    const std::vector<double>& energy_grid,
    const double binding_energy,
    std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>&
      electroionization_subshell_distribution,
    const ElectroionizationSamplingType sampling_type,
    const double evaluation_tol,
    const unsigned max_number_of_iterations,
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

  // Subshell distribution
  std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>
    subshell_distribution;

  if( sampling_type == KNOCK_ON_SAMPLING )
  {
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
  }
  else
  {
    std::map<double,std::vector<double> > processed_energy_data, processed_pdf_data;
    std::vector<double> processed_energy_grid;

    // Process the recoil energy to outgoing energy data
    ThisType::calculateOutgoingEnergyAndPDFBins(
              recoil_energy_data,
              recoil_pdf_data,
              energy_grid,
              binding_energy,
              true,
              processed_energy_data,
              processed_pdf_data,
              processed_energy_grid );

    if( sampling_type == OUTGOING_ENERGY_SAMPLING )
    {
      // Create the subshell distribution
      ThisType::createOutgoingDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
              processed_energy_data,
              processed_pdf_data,
              processed_energy_grid,
              binding_energy,
              subshell_distribution,
              evaluation_tol,
              max_number_of_iterations );
    }
    else if( sampling_type == OUTGOING_ENERGY_RATIO_SAMPLING )
    {
      // Create the subshell distribution
      ThisType::createOutgoingRatioDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
              processed_energy_data,
              processed_pdf_data,
              processed_energy_grid,
              binding_energy,
              subshell_distribution,
              evaluation_tol,
              max_number_of_iterations );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                      "The ElectroionizationSamplingType " <<
                      sampling_type <<
                      " is invalid or currently not supported!" );
    }
  }

  electroionization_subshell_distribution.reset(
    new ElectroionizationSubshellElectronScatteringDistribution(
            subshell_distribution,
            sampling_type,
            binding_energy ) );
}

// Create the subshell recoil distribution
template<typename TwoDInterpPolicy,
         template<typename> class TwoDGridPolicy>
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createSubshellDistribution(
    const std::map<double,std::vector<double> >& recoil_energy_data,
    const std::map<double,std::vector<double> >& recoil_pdf_data,
    const std::vector<double>& energy_grid,
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

// Create the subshell outgoing energy distribution
template<typename TwoDInterpPolicy,
         template<typename> class TwoDGridPolicy>
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createOutgoingDistribution(
    const std::map<double,std::vector<double> >& processed_energy_data,
    const std::map<double,std::vector<double> >& processed_pdf_data,
    const std::vector<double>& processed_energy_grid,
    const double binding_energy,
    std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>&
        subshell_distribution,
    const double evaluation_tol,
    const unsigned max_number_of_iterations )
{
  // Make sure the energy_grid is valid
  testPrecondition( processed_energy_grid.size() > 1 );
  // Make sure the data is valid
  testPrecondition( processed_energy_data.size() == processed_energy_grid.size() );
  testPrecondition( processed_pdf_data.size() == processed_energy_grid.size() );
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );

  // Create the scattering function
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( processed_energy_grid.size() );

  for( size_t n = 0; n < processed_energy_grid.size(); ++n )
  {
    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>(
          processed_energy_data.find( processed_energy_grid[n] )->second,
          processed_pdf_data.find( processed_energy_grid[n] )->second ) );
  }

  // Create the scattering function
  subshell_distribution.reset(
    new Utility::InterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy<TwoDInterpPolicy> >(
            processed_energy_grid,
            secondary_dists,
            1e-6,
            evaluation_tol,
            1e-16,
            max_number_of_iterations ) );
}

// Create the subshell outgoing energy ratio distribution
template<typename TwoDInterpPolicy,
         template<typename> class TwoDGridPolicy>
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createOutgoingRatioDistribution(
    const std::map<double,std::vector<double> >& processed_energy_data,
    const std::map<double,std::vector<double> >& processed_pdf_data,
    const std::vector<double>& processed_energy_grid,
    const double binding_energy,
    std::shared_ptr<const Utility::FullyTabularBasicBivariateDistribution>&
        subshell_distribution,
    const double evaluation_tol,
    const unsigned max_number_of_iterations )
{
  // Make sure the energy_grid is valid
  testPrecondition( processed_energy_grid.size() > 1 );
  // Make sure the data is valid
  testPrecondition( processed_energy_data.size() == processed_energy_grid.size() );
  testPrecondition( processed_pdf_data.size() == processed_energy_grid.size() );
  // Make sure the evaluation tol is valid
  testPrecondition( evaluation_tol > 0.0 );

  // Create the scattering function
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( processed_energy_grid.size() );

  for( size_t n = 0; n < processed_energy_grid.size(); ++n )
  {
    std::vector<double> ratio_bins =
      processed_energy_data.find( processed_energy_grid[n] )->second;

    // Divide bins by the incoming_energy
    std::transform(ratio_bins.begin(), ratio_bins.end(), ratio_bins.begin(),
      [max = processed_energy_grid[n]](double& bin){ return bin /= max;});

    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>(
          ratio_bins,
          processed_pdf_data.find( processed_energy_grid[n] )->second ) );
  }

  // Create the scattering function
  subshell_distribution.reset(
    new Utility::InterpolatedFullyTabularBasicBivariateDistribution<TwoDGridPolicy<TwoDInterpPolicy> >(
            processed_energy_grid,
            secondary_dists,
            1e-6,
            evaluation_tol,
            1e-16,
            max_number_of_iterations ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//
