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
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution> createCoupledElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const MonteCarlo::CoupledElasticSamplingMethod method,
    const double evaluation_tol );

//! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

//! Create a cutoff elastic distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

//! Create a screened rutherford elastic distribution
std::shared_ptr<const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution> createScreenedRutherfordElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container );

//! Create a moment preserving elastic distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a simple dipole bremsstrahlung distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double evaluation_tol = 1e-7 );

//! Create a detailed 2BS bremsstrahlung distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const int atomic_number,
    const double evaluation_tol = 1e-7 );

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a electroionization subshell distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution> createElectroionizationSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const unsigned subshell,
    const double binding_energy,
    const double evaluation_tol = 1e-7 );

//----------------------------------------------------------------------------//
//      ****ATOMIC EXCITATION DISTRIBUTION****
//----------------------------------------------------------------------------//

//! Create a atomic excitation distribution
std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution> createAtomicExcitationDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers.hpp
//---------------------------------------------------------------------------//
