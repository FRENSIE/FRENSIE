//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers.hpp
//! \author Luke Kersting
//! \brief  The adjoint electron scattering distribution native factory helpers declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HELPERS_HPP
#define MONTE_CARLO_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HELPERS_HPP

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create an adjoint coupled elastic distribution ( combined Cutoff and Screened Rutherford )
std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution> createCoupledElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

//! Create an adjoint hybrid elastic distribution ( combined Cutoff and Moment Preserving )
std::shared_ptr<const MonteCarlo::HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

//! Create an adjoint cutoff elastic distribution
std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

//! Create an adjoint moment preserving elastic distribution
std::shared_ptr<const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create an adjoint bremsstrahlung distribution
std::shared_ptr<const MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol = 1e-7 );

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create an adjoint electroionization subshell distribution
std::shared_ptr<const MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution> createElectroionizationSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const unsigned subshell,
    const double binding_energy,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol = 1e-7 );

//----------------------------------------------------------------------------//
//      ****ATOMIC EXCITATION DISTRIBUTION****
//----------------------------------------------------------------------------//

//! Create an adjoint atomic excitation distribution
std::shared_ptr<const MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution> createAtomicExcitationDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers.hpp
//---------------------------------------------------------------------------//
