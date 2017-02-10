//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers.hpp
//! \author Luke Kersting
//! \brief  The electron scattering distribution native factory helpers declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HELPERS_HPP
#define MONTE_CARLO_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HELPERS_HPP

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution> createAnalogElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const bool use_linlinlog_interpolation = true );

//! Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution> createAnalogElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const bool use_linlinlog_interpolation = true );


//! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
std::shared_ptr<const MonteCarlo::HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool use_linlinlog_interpolation = true );

//! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
std::shared_ptr<const MonteCarlo::HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool use_linlinlog_interpolation = true );


//! Create a cutoff elastic distribution
std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine = 1.0,
    const bool use_linlinlog_interpolation = true );

//! Create a cutoff elastic distribution
std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine = 1.0,
    const bool use_linlinlog_interpolation = true );


//! Create a moment preserving elastic distribution
std::shared_ptr<const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine = 0.9,
    const bool use_linlinlog_interpolation = true );

//! Create a moment preserving elastic distribution
std::shared_ptr<const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine = 0.9,
    const bool use_linlinlog_interpolation = true );

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a simple dipole bremsstrahlung distribution
std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const bool use_linlinlog_interpolation,
    const bool use_weighted_sampling );

//! Create a detailed 2BS bremsstrahlung distribution
std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const int atomic_number,
    const bool use_linlinlog_interpolation,
    const bool use_weighted_sampling );

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a electroionization subshell distribution
std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution> createElectroionizationSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const unsigned subshell,
    const double binding_energy,
    const bool use_linlinlog_interpolation = true,
    const bool use_weighted_sampling = true );

//----------------------------------------------------------------------------//
//      ****ATOMIC EXCITATION DISTRIBUTION****
//----------------------------------------------------------------------------//

//! Create a atomic excitation distribution
std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution> createAtomicExcitationDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers.hpp
//---------------------------------------------------------------------------//
