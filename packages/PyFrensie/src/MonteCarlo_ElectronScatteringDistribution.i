//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronScatteringDistribution.i
//! \author Luke Kersting
//! \brief  The ElectronScatteringDistribution class interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "MonteCarlo_ScatteringDistribution.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_PositronScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"

#include "MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"

#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"

#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"

#include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp"

// #include "MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers.hpp"
// #include "MonteCarlo_ElectronScatteringDistributionACEFactoryHelpers.hpp"

#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp"

#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.hpp"

#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp"

// #include "MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers.hpp"

#include "Utility_ToStringTraitsDecl.hpp"
%}

// Include std::string support
%include <std_string.i>

// C++ STL support
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Import the ToStringTraitsDecl
%import "Utility_ToStringTraitsDecl.hpp"

// shared_ptr Data Container handling
%shared_ptr(Data::ElectronPhotonRelaxationDataContainer);
%shared_ptr(Data::AdjointElectronPhotonRelaxationDataContainer);

// // Import the explicit template instantiation helpers
// %import "Utility_ExplicitTemplateInstantiationMacros.hpp"

// Include the electron scattering distribution distribution helpers
%include "MonteCarlo_ElectronScatteringDistributionHelpers.i"
%include "MonteCarlo_ElectronTemplateHelpers.i"

// Add use of std::shared_ptr
// %shared_ptr(MonteCarlo::CoupledElasticElectronScatteringDistribution)
// %shared_ptr(MonteCarlo::HybridElasticElectronScatteringDistribution)
// %shared_ptr(MonteCarlo::CutoffElasticElectronScatteringDistribution)
// %shared_ptr(MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution)
// %shared_ptr(MonteCarlo::MomentPreservingElasticElectronScatteringDistribution)
// %shared_ptr(MonteCarlo::BremsstrahlungElectronScatteringDistribution)
// %shared_ptr(MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution)
// %shared_ptr(MonteCarlo::AtomicExcitationElectronScatteringDistribution)
// %shared_ptr(MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution)
// %shared_ptr(MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution)
// %shared_ptr(MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution)

// Ignore scatter electron
%ignore *::scatterElectron( ElectronState&, ParticleBank&, Data::SubshellType& ) const;
// Ignore scatter positron
%ignore *::scatterPositron( PositronState&, ParticleBank&, Data::SubshellType& ) const;
// Ignore scatter adjoint electron
%ignore *::scatterAdjointElectron( AdjointElectronState&, ParticleBank&, Data::SubshellType& ) const;
// Ignore operator <<
%ignore *::operator<<;


// Add a general typemap for sampling
%apply double& OUTPUT { double& outgoing_energy };
%apply double& OUTPUT { double& scattering_angle_cosine };
%apply double& OUTPUT { double& outgoing_angle_cosine };

//---------------------------------------------------------------------------//
// Add support for the ElasticElectronDistributionType enum
//---------------------------------------------------------------------------//

%include "MonteCarlo_ElasticElectronDistributionType.hpp"

//---------------------------------------------------------------------------//
// Add support for the ScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::ScatteringDistribution)
// Include the class
%include "MonteCarlo_ScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Add support for the ElectronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::ElectronScatteringDistribution)
// Include the class
%include "MonteCarlo_ElectronScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Add support for the PositronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::PositronScatteringDistribution)
// Include the class
%include "MonteCarlo_PositronScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Add support for the AdjointElectronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::AdjointElectronScatteringDistribution)
// Include the class
%include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Add support for the CoupledElasticElectronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::CoupledElasticElectronScatteringDistribution)
// Include the class
%include "MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp"

%inline %{

// Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution> createCoupledElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const MonteCarlo::CoupledElasticSamplingMethod method,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution>
    distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      distribution,
      data_container,
      method,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

// Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution> createCoupledElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const MonteCarlo::CoupledElasticSamplingMethod method,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution>
    distribution;

  // Assign the cutoff and total elastic cross section and electron energy grid
  auto cutoff_cross_section = std::make_shared<std::vector<double>>(
    data_container.getAdjointCutoffElasticCrossSection() );

  auto total_cross_section = std::make_shared<std::vector<double>>(
    data_container.getAdjointTotalElasticCrossSection() );

  auto energy_grid = std::make_shared<std::vector<double>>(
    data_container.getAdjointElectronEnergyGrid() );

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      distribution,
      energy_grid,
      cutoff_cross_section,
      total_cross_section,
      data_container,
      method,
      evaluation_tol );

  return distribution;
}

%}

// Add templates for the CoupledElasticDistribution
%elastic_template_setup( Coupled )

//---------------------------------------------------------------------------//
// Add support for the HybridElasticElectronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::HybridElasticElectronScatteringDistribution)
// Include the class
%include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"

%inline %{

// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  // Extract the common energy grid used for this atom
  std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
  energy_grid->assign( data_container.getElectronEnergyGrid().begin(),
                       data_container.getElectronEnergyGrid().end() );

  // Cutoff elastic cross section
  std::shared_ptr<std::vector<double> >
    cutoff_cross_section( new std::vector<double> );
  cutoff_cross_section->assign(
    data_container.getCutoffElasticCrossSection().begin(),
    data_container.getCutoffElasticCrossSection().end() );

  // Cutoff elastic cross section threshold energy bin index
  size_t cutoff_threshold_energy_index =
    data_container.getCutoffElasticCrossSectionThresholdEnergyIndex();

  // Moment preserving elastic cross section
  std::shared_ptr<std::vector<double> >
    mp_cross_section( new std::vector<double> );
  size_t mp_threshold_energy_index;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::calculateMomentPreservingCrossSections<TwoDInterpPolicy,TwoDGridPolicy>(
                               *mp_cross_section,
                               mp_threshold_energy_index,
                               data_container,
                               energy_grid,
                               evaluation_tol );

  // Create the hybrid elastic scattering distribution
  std::shared_ptr<const MonteCarlo::HybridElasticElectronScatteringDistribution>
    distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      distribution,
      energy_grid,
      cutoff_cross_section,
      mp_cross_section,
      data_container,
      cutoff_angle_cosine,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}


// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  // Extract the common energy grid used for this atom
  auto energy_grid = std::make_shared<std::vector<double>>(
    data_container.getAdjointElectronEnergyGrid() );

  // Cutoff elastic cross section
  auto cutoff_cross_section = std::make_shared<std::vector<double>>(
    data_container.getAdjointCutoffElasticCrossSection() );

  // Cutoff elastic cross section threshold energy bin index
  size_t cutoff_threshold_energy_index =
    data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

  // Moment preserving elastic cross section
  std::shared_ptr<std::vector<double> >
    mp_cross_section( new std::vector<double> );
  size_t mp_threshold_energy_index;
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::calculateMomentPreservingCrossSections<TwoDInterpPolicy,TwoDGridPolicy>(
                               *mp_cross_section,
                               mp_threshold_energy_index,
                               data_container,
                               energy_grid,
                               evaluation_tol );

  // Create the hybrid elastic scattering distribution
  std::shared_ptr<const MonteCarlo::HybridElasticElectronScatteringDistribution>
    distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      distribution,
      energy_grid,
      cutoff_cross_section,
      mp_cross_section,
      data_container,
      cutoff_angle_cosine,
      evaluation_tol );

  return distribution;
}

%}

// Add templates for the HybridElasticDistribution
%elastic_template_setup( Hybrid )

//---------------------------------------------------------------------------//
// Add support for the CutoffElasticElectronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::CutoffElasticElectronScatteringDistribution)
// Include the class
%include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"

%inline %{

// Create a cutoff elastic distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      distribution,
      data_container,
      cutoff_angle_cosine,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

// Create a cutoff elastic distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      distribution,
      data_container,
      cutoff_angle_cosine,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}
%}

// Add templates for the CutoffElasticDistribution
%elastic_template_setup( Cutoff )

//---------------------------------------------------------------------------//
// Add support for the MomentPreservingElasticElectronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::MomentPreservingElasticElectronScatteringDistribution)
// Include the class
%include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"

%inline %{

// Create a moment preserving elastic distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution>
    distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      distribution,
      data_container,
      cutoff_angle_cosine,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

// Create a moment preserving elastic distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::MomentPreservingElasticElectronScatteringDistribution>
    distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      distribution,
      data_container,
      cutoff_angle_cosine,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}
%}

// Add templates for the MomentPreservingElasticDistribution
%elastic_template_setup( MomentPreserving )

//---------------------------------------------------------------------------//
// Add support for the AtomicExcitationElectronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::AtomicExcitationElectronScatteringDistribution)
// Include the class
%include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"

%inline %{

// Create a atomic excitation distribution
std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution> createAtomicExcitationDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container )
{
  std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
    distribution;

  MonteCarlo::AtomicExcitationElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
    data_container, distribution );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}
%}

//---------------------------------------------------------------------------//
// Add support for the BremsstrahlungElectronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::BremsstrahlungElectronScatteringDistribution)
// Include the class
%include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"

%inline %{

// Create a simple dipole bremsstrahlung distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
    distribution;

  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      data_container,
      distribution,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

//! Create a detailed 2BS bremsstrahlung distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const int atomic_number,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
    distribution;

  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      data_container,
      data_container.getAtomicNumber(),
      distribution,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}
%}

//---------------------------------------------------------------------------//
// Add support for the ElectroionizationSubshellElectronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution)
// Include the class
%include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"

%inline %{

// Create a electroionization subshell distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution> createElectroionizationSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const unsigned subshell,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
    distribution;

  MonteCarlo::ElectroionizationSamplingType sampling_type =
    MonteCarlo::KNOCK_ON_SAMPLING;

  MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      data_container,
      subshell,
      data_container.getSubshellBindingEnergy(subshell),
      distribution,
      sampling_type,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}
%}

//---------------------------------------------------------------------------//
// Add support for the AtomicExcitationAdjointElectronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution)
// Include the class
%include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.hpp"

%inline %{

// Create a atomic excitation distribution
std::shared_ptr<MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution> createAtomicExcitationDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container )
{
  std::shared_ptr<MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
    distribution;

  MonteCarlo::AtomicExcitationAdjointElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
    data_container, distribution );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}
%}

//---------------------------------------------------------------------------//
// Add support for the BremsstrahlungAdjointElectronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution)
// Include the class
%include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"

%inline %{

// Create a simple dipole bremsstrahlung distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double evaluation_tol )
{
  std::shared_ptr<MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution>
    distribution;

  MonteCarlo::BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      data_container,
      data_container.getAdjointElectronBremsstrahlungEnergyGrid(),
      distribution,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}
%}

%electron_template_setup( Bremsstrahlung )

//---------------------------------------------------------------------------//
// Add support for the ElectroionizationSubshellAdjointElectronScatteringDistribution
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution)
// Include the class
%include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp"

%inline %{

//! Create a electroionization subshell distribution
template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
std::shared_ptr<MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution> createElectroionizationSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const unsigned subshell,
    const double evaluation_tol )
{
  std::shared_ptr<MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution>
    distribution;

  MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
      data_container,
      subshell,
      data_container.getSubshellBindingEnergy(subshell),
      distribution,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}
%}

%electron_template_setup( ElectroionizationSubshell )



// //---------------------------------------------------------------------------//
// // Add support for the electron scattering distribution native factory helpers
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers.hpp"

// %feature("docstring")
// MonteCarlo::ElectronScatteringDistributionNativeFactoryHelpers
// "The Electron Scattering Distribution Native Factory Helpers"

// //---------------------------------------------------------------------------//
// // Add support for the electron scattering distribution ACE factory helpers
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_ElectronScatteringDistributionACEFactoryHelpers.hpp"

// %feature("docstring")
// MonteCarlo::ElectronScatteringDistributionACEFactoryHelpers
// "The Electron Scattering Distribution ACE Factory Helpers"

// //---------------------------------------------------------------------------//
// // Add support for the adjoint electron scattering distribution native factory helpers
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers.hpp"

// %feature("docstring")
// MonteCarlo::AdjointElectronScatteringDistributionNativeFactoryHelpers
// "The Adjoint Electron Scattering Distribution Native Factory Helpers"

// //---------------------------------------------------------------------------//
// // Add support for the templated factory helpers
// //---------------------------------------------------------------------------//

// %cos_electron_function_interface_setup( CoupledElasticDistribution )
// %cos_electron_function_interface_setup( HybridElasticDistribution )
// %cos_electron_function_interface_setup( CutoffElasticDistribution )
// %cos_electron_function_interface_setup( MomentPreservingElasticDistribution )
// %electron_function_interface_setup( ElectroionizationSubshellDistribution )
// %electron_function_interface_setup( BremsstrahlungDistribution )

// //---------------------------------------------------------------------------//
// // Add support for the elastic electron scattering distributions (forward and adjoint)
// //---------------------------------------------------------------------------//

// // Add a general typemap for sampling
// %apply double& OUTPUT { double& outgoing_energy };
// %apply double& OUTPUT { double& scattering_angle_cosine };

// %ignore *::evaluateCDFAtCutoff( const double, const double );

// %include "MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp"
// %include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
// %include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
// %include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
// %include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"

// // Electron scattering distribution interface setup
// %electron_distribution_interface_setup( CoupledElasticElectronScatteringDistribution )
// %electron_distribution_interface_setup( HybridElasticElectronScatteringDistribution )
// %electron_distribution_interface_setup( CutoffElasticElectronScatteringDistribution )
// %electron_distribution_interface_setup( ScreenedRutherfordElasticElectronScatteringDistribution )
// %electron_distribution_interface_setup( MomentPreservingElasticElectronScatteringDistribution )

// //---------------------------------------------------------------------------//
// // Add support for the bremsstrahlung electron scattering distribution
// //---------------------------------------------------------------------------//

// // Add a typemap for sampling bremsstrahlung distribution
// %apply double& OUTPUT { double& photon_energy };
// %apply double& OUTPUT { double& photon_angle_cosine };

// %include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"

// // Electron scattering distribution interface setup
// %electron_distribution_interface_setup( BremsstrahlungElectronScatteringDistribution )

// //---------------------------------------------------------------------------//
// // Add support for the electroionization subshell electron scattering distribution
// //---------------------------------------------------------------------------//

// // Add a typemap for sampling electroionization subshell distribution
// %apply double& OUTPUT { double& knock_on_energy };
// %apply double& OUTPUT { double& knock_on_angle_cosine };

// %include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"

// %feature("autodoc",
// "sample(ElectroionizationSubshellElectronScatteringDistribution self, const double incoming_energy) -> double, double, double, double")
// MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistributio::sample;

// // Basic electron scattering distribution interface setup
// %electron_distribution_interface_setup( ElectroionizationSubshellElectronScatteringDistribution )

// //---------------------------------------------------------------------------//
// // Add support for the atomic excitation electron scattering distribution
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"

// // Electron scattering distribution interface setup
// %electron_distribution_interface_setup( AtomicExcitationElectronScatteringDistribution )

// //---------------------------------------------------------------------------//
// // Add support for the adjoint bremsstrahlung electron scattering distribution
// //---------------------------------------------------------------------------//

// // Add a typemap for sampling adjoint bremsstrahlung distribution
// %apply double& OUTPUT { double& outgoing_energy };
// %apply double& OUTPUT { double& outgoing_angle_cosine };

// %include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"

// // Electron scattering distribution interface setup
// %electron_distribution_interface_setup( BremsstrahlungAdjointElectronScatteringDistribution )

// //---------------------------------------------------------------------------//
// // Add support for the adjoint electroionization subshell electron scattering distribution
// //---------------------------------------------------------------------------//

// // Add a typemap for sampling adjoint electroionization subshell distribution
// %apply double& OUTPUT { double& outgoing_energy };
// %apply double& OUTPUT { double& outgoing_angle_cosine };

// %include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp"

// // Electron scattering distribution interface setup
// %electron_distribution_interface_setup( ElectroionizationSubshellAdjointElectronScatteringDistribution )

// //---------------------------------------------------------------------------//
// // Add support for the adjoint atomic excitation electron scattering distribution
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.hpp"

// // Electron scattering distribution interface setup
// %electron_distribution_interface_setup( AtomicExcitationAdjointElectronScatteringDistribution )

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronScatteringDistribution.i
//---------------------------------------------------------------------------//
