//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatomic reaction native factory helpers declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HELPERS_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HELPERS_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_CoupledElasticAdjointElectroatomicReaction.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC REACTIONS****
//----------------------------------------------------------------------------//

//! Create an coupled elastic scattering adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const AdjointElectroatomicReaction>
createCoupledElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const CoupledElasticSamplingMethod method,
    const double evaluation_tol );

//! Create a decoupled elastic scattering adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const AdjointElectroatomicReaction>
createDecoupledElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const double evaluation_tol );

//! Create a hybrid elastic scattering adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const AdjointElectroatomicReaction>
createHybridElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

//! Create an cutoff elastic scattering adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const AdjointElectroatomicReaction>
createCutoffElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

//! Create a screened Rutherford elastic scattering adjoint electroatomic reaction
std::shared_ptr<const AdjointElectroatomicReaction>
createScreenedRutherfordElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data );

//! Create the moment preserving elastic scattering adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const AdjointElectroatomicReaction>
createMomentPreservingElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

//----------------------------------------------------------------------------//
//      ****ATOMIC EXCITATION DISTRIBUTION****
//----------------------------------------------------------------------------//

//! Create an atomic excitation scattering adjoint electroatomic reaction
std::shared_ptr<const AdjointElectroatomicReaction>
createAtomicExcitationReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data );

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL REACTIONS****
//----------------------------------------------------------------------------//

//! Create the subshell electroionization adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const AdjointElectroatomicReaction>
createSubshellElectroionizationReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const unsigned subshell,
    const double evaluation_tol );

//! Create the subshell electroionization adjoint electroatomic reactions
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::vector<std::shared_ptr<const AdjointElectroatomicReaction> >
createSubshellElectroionizationReactions(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const double evaluation_tol );

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG REACTIONS****
//----------------------------------------------------------------------------//

//! Create the bremsstrahlung adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const AdjointElectroatomicReaction>
createBremsstrahlungReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const bool dipole_distribution_mode_on,
    const double evaluation_tol );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers.hpp
//---------------------------------------------------------------------------//
