//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReaction.i
//! \author Luke Kersting
//! \brief  The Electroatomic Reaction class interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_MasslessParticleState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Geometry_AdvancedModel.hpp"

#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "MonteCarlo_Reaction.hpp"
#include "MonteCarlo_AtomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_AdjointAtomicReaction.hpp"
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"

#include "MonteCarlo_CoupledElasticElectroatomicReaction.hpp"
#include "MonteCarlo_DecoupledElasticElectroatomicReaction.hpp"
#include "MonteCarlo_HybridElasticElectroatomicReaction.hpp"
// #include "MonteCarlo_CutoffElasticElectroatomicReaction.hpp"
// #include "MonteCarlo_MomentPreservingElasticElectroatomicReaction.hpp"
// #include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
// #include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
// #include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"



// #include "MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"
// #include "MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers.hpp"
// #include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
// #include "MonteCarlo_CoupledElasticAdjointElectroatomicReaction.hpp"
// #include "MonteCarlo_HybridElasticAdjointElectroatomicReaction.hpp"
// #include "MonteCarlo_CutoffElasticAdjointElectroatomicReaction.hpp"
// #include "MonteCarlo_MomentPreservingElasticAdjointElectroatomicReaction.hpp"
// #include "MonteCarlo_BremsstrahlungAdjointElectroatomicReaction.hpp"
// #include "MonteCarlo_ElectroionizationSubshellAdjointElectroatomicReaction.hpp"
// #include "MonteCarlo_AtomicExcitationAdjointElectroatomicReaction.hpp"

using namespace MonteCarlo;
%}

// Include std::string support
%include <std_string.i>

// C++ STL support
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// ParticleState handling
%import(module="PyFrensie.MonteCarlo") MonteCarlo_ParticleState.i

// shared_ptr Data Container handling
%shared_ptr(Data::XSSEPRDataExtractor);
%shared_ptr(Data::ElectronPhotonRelaxationDataContainer);

// Import the explicit template instantiation helpers
%import "Utility_ExplicitTemplateInstantiationMacros.hpp"

// Include the electroatomic reaction helpers
%include "MonteCarlo_ElectroatomicReactionHelpers.i"
%include "MonteCarlo_ElectronTemplateHelpers.i"

// Add a typemap for Data::SubshellType& shell_of_interaction
%typemap(in,numinputs=0) Data::SubshellType& shell_of_interaction (Data::SubshellType temp) "$1 = &temp;"

%typemap(argout) Data::SubshellType& shell_of_interaction {
  %append_output(PyInt_FromLong( *$1 ));
}

// Ignore the operator <<()
%ignore *::operator<<;

//---------------------------------------------------------------------------//
// Add support for the ElectroatomicReactionType enum
//---------------------------------------------------------------------------//

%include "MonteCarlo_ElectroatomicReactionType.hpp"

//---------------------------------------------------------------------------//
// Add support for the Reaction class
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::Reaction)
// Include class
%include "MonteCarlo_Reaction.hpp"

//---------------------------------------------------------------------------//
// Add support for the Atomic Reaction class
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::AtomicReaction)
// Include class
%include "MonteCarlo_AtomicReaction.hpp"

//---------------------------------------------------------------------------//
// Add support for the ElectroatomicReaction class
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::ElectroatomicReaction)
// Include class
%include "MonteCarlo_ElectroatomicReaction.hpp"

// //---------------------------------------------------------------------------//
// // Add support for the Adjoint Atomic Reaction class
// //---------------------------------------------------------------------------//

// // Add use of std::shared_ptr
// %shared_ptr(MonteCarlo::AdjointAtomicReaction)
// // Include class
// %include "MonteCarlo_AdjointAtomicReaction.hpp"

// //---------------------------------------------------------------------------//
// // Add support for the AdjointElectroatomicReaction class
// //---------------------------------------------------------------------------//

// // Add use of std::shared_ptr
// %shared_ptr(MonteCarlo::AdjointElectroatomicReaction)
// // Include class
// %include "MonteCarlo_AdjointElectroatomicReaction.hpp"

//---------------------------------------------------------------------------//
// Add support for the StandardReactionBaseImpl class
//---------------------------------------------------------------------------//

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::StandardReactionBaseImpl<MonteCarlo::ElectroatomicReaction, Utility::LogLog, false>)
%shared_ptr(MonteCarlo::StandardReactionBaseImpl<MonteCarlo::ElectroatomicReaction, Utility::LinLog, false>)
%shared_ptr(MonteCarlo::StandardReactionBaseImpl<MonteCarlo::ElectroatomicReaction, Utility::LinLin, false>)

// Include class
%include "MonteCarlo_StandardReactionBaseImpl.hpp"

%template(StandardElectroatomicReactionLogLog) MonteCarlo::StandardReactionBaseImpl<MonteCarlo::ElectroatomicReaction, Utility::LogLog, false>;
%template(StandardElectroatomicReactionLinLog) MonteCarlo::StandardReactionBaseImpl<MonteCarlo::ElectroatomicReaction, Utility::LinLog, false>;
%template(StandardElectroatomicReactionLinLin) MonteCarlo::StandardReactionBaseImpl<MonteCarlo::ElectroatomicReaction, Utility::LinLin, false>;

//---------------------------------------------------------------------------//
// Use this general setup macro with all templated elastic reactions
//---------------------------------------------------------------------------//
%define %elastic_reaction_before_setup( REACTION )

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::REACTION ## ElasticElectroatomicReaction<Utility::LogLog, false>)
%shared_ptr(MonteCarlo::REACTION ## ElasticElectroatomicReaction<Utility::LinLog, false>)
%shared_ptr(MonteCarlo::REACTION ## ElasticElectroatomicReaction<Utility::LinLin, false>)

%enddef

//---------------------------------------------------------------------------//
%define %elastic_reaction_after_setup( REACTION )

%template(REACTION ## ElasticElectroatomicReaction_LogLog) MonteCarlo::REACTION ## ElasticElectroatomicReaction<Utility::LogLog, false>;
%template(REACTION ## ElasticElectroatomicReaction_LinLog) MonteCarlo::REACTION ## ElasticElectroatomicReaction<Utility::LinLog, false>;
%template(REACTION ## ElasticElectroatomicReaction_LinLin) MonteCarlo::REACTION ## ElasticElectroatomicReaction<Utility::LinLin, false>;

%enddef

//---------------------------------------------------------------------------//
%define %elastic_reaction_template_after_setup( REACTION )

  // Add templates for the Correlated REACTION ElasticReaction
  %template(create ## REACTION ## ElasticReaction_LogLogCorrelated) create ## REACTION ## ElasticReaction<Utility::LogNudgedLogCosLog, Utility::Correlated>;
  %template(create ## REACTION ## ElasticReaction_LinLogCorrelated) create ## REACTION ## ElasticReaction<Utility::LinLinLog, Utility::Correlated>;
  %template(create ## REACTION ## ElasticReaction_LinLinCorrelated) create ## REACTION ## ElasticReaction<Utility::LinLinLin, Utility::Correlated>;
  // Add templates for the Direct REACTION ElasticReaction
  %template(create ## REACTION ## ElasticReaction_LogLogDirect) create ## REACTION ## ElasticReaction<Utility::LogNudgedLogCosLog, Utility::Direct>;
  %template(create ## REACTION ## ElasticReaction_LinLogDirect) create ## REACTION ## ElasticReaction<Utility::LinLinLog, Utility::Direct>;
  %template(create ## REACTION ## ElasticReaction_LinLinDirect) create ## REACTION ## ElasticReaction<Utility::LinLinLin, Utility::Direct>;

%enddef

//---------------------------------------------------------------------------//
// Add support for the ElasticElectroatomicReaction classes
//---------------------------------------------------------------------------//

%elastic_reaction_before_setup( Coupled )
%elastic_reaction_before_setup( Decoupled )
%elastic_reaction_before_setup( Hybrid )
%elastic_reaction_before_setup( Cutoff )
%elastic_reaction_before_setup( MomentPreserving )

// Include classes
%include "MonteCarlo_CoupledElasticElectroatomicReaction.hpp"
%include "MonteCarlo_DecoupledElasticElectroatomicReaction.hpp"
%include "MonteCarlo_HybridElasticElectroatomicReaction.hpp"
%include "MonteCarlo_CutoffElasticElectroatomicReaction.hpp"
%include "MonteCarlo_MomentPreservingElasticElectroatomicReaction.hpp"

%elastic_reaction_after_setup( Coupled )
%elastic_reaction_after_setup( Decoupled )
%elastic_reaction_after_setup( Hybrid )
%elastic_reaction_after_setup( Cutoff )
%elastic_reaction_after_setup( MomentPreserving )

//---------------------------------------------------------------------------//
// Add support for the Electroatomic Reaction native factory
//---------------------------------------------------------------------------//

%inline %{

  // Create an coupled elastic scattering electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated>
  std::shared_ptr<const MonteCarlo::CoupledElasticElectroatomicReaction<Utility::LogLog> > createCoupledElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const MonteCarlo::CoupledElasticSamplingMethod& sampling_method,
    const double evaluation_tol )
  {
    // Extract the common energy grid
    std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
    energy_grid->assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                         raw_electroatom_data.getElectronEnergyGrid().end() );

    // Construct the hash-based grid searcher
    std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                energy_grid,
                                energy_grid->size()/10 ) );

    // Create the reaction
    std::shared_ptr<const MonteCarlo::CoupledElasticElectroatomicReaction<Utility::LogLog> > reaction;
    MonteCarlo::ElectroatomicReactionNativeFactory::createCoupledElasticReaction<TwoDInterpPolicy,TwoDGridPolicy, MonteCarlo::CoupledElasticElectroatomicReaction<Utility::LogLog> >(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        sampling_method,
        evaluation_tol );

    // Make sure the reaction was created correctly
    testPostcondition( reaction.use_count() > 0 );

    return reaction;
  }

  // Create a decoupled elastic scattering electroatomic reaction
  template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
  std::shared_ptr<const MonteCarlo::DecoupledElasticElectroatomicReaction<Utility::LogLog> >
  createDecoupledElasticReaction(
      const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
      const double evaluation_tol )
  {
    // Extract the common energy grid
    std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
    energy_grid->assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                         raw_electroatom_data.getElectronEnergyGrid().end() );

    // Construct the hash-based grid searcher
    std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                energy_grid,
                                energy_grid->size()/10 ) );

    // Create the reaction
  std::shared_ptr<const MonteCarlo::DecoupledElasticElectroatomicReaction<Utility::LogLog> > reaction;
    MonteCarlo::ElectroatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDInterpPolicy,TwoDGridPolicy, MonteCarlo::DecoupledElasticElectroatomicReaction<Utility::LogLog> >(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        evaluation_tol );

    // Make sure the reaction was created correctly
    testPostcondition( reaction.use_count() > 0 );

    return reaction;
  }

  // Create a hybrid elastic scattering electroatomic reaction
  template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
  std::shared_ptr<const MonteCarlo::ElectroatomicReaction>
  createHybridElasticReaction(
      const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
      const double cutoff_angle_cosine,
      const double evaluation_tol )
  {
    // Extract the common energy grid
    std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
    energy_grid->assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                         raw_electroatom_data.getElectronEnergyGrid().end() );

    // Construct the hash-based grid searcher
    std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                energy_grid,
                                energy_grid->size()/10 ) );

    // Create the reaction
    std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;
    MonteCarlo::ElectroatomicReactionNativeFactory::createHybridElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        cutoff_angle_cosine,
        evaluation_tol );

    // Make sure the reaction was created correctly
    testPostcondition( reaction.use_count() > 0 );

    return reaction;
  }

  // Create an cutoff elastic scattering electroatomic reaction
  template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
  std::shared_ptr<const MonteCarlo::ElectroatomicReaction>
  createCutoffElasticReaction(
      const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
      const double cutoff_angle_cosine,
      const double evaluation_tol )
  {
    // Extract the common energy grid
    std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
    energy_grid->assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                         raw_electroatom_data.getElectronEnergyGrid().end() );

    // Construct the hash-based grid searcher
    std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                energy_grid,
                                energy_grid->size()/10 ) );

    // Create the reaction
    std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;
    MonteCarlo::ElectroatomicReactionNativeFactory::createCutoffElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        cutoff_angle_cosine,
        evaluation_tol );

    // Make sure the reaction was created correctly
    testPostcondition( reaction.use_count() > 0 );

    return reaction;
  }

  // Create the moment preserving elastic scattering electroatomic reaction
  template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
  std::shared_ptr<const MonteCarlo::ElectroatomicReaction>
  createMomentPreservingElasticReaction(
      const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
      const double cutoff_angle_cosine,
      const double evaluation_tol )
  {
    // Extract the common energy grid
    std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
    energy_grid->assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                         raw_electroatom_data.getElectronEnergyGrid().end() );

    // Construct the hash-based grid searcher
    std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                energy_grid,
                                energy_grid->size()/10 ) );

    // Create the reaction
    std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;
    MonteCarlo::ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        cutoff_angle_cosine,
        evaluation_tol );

    // Make sure the reaction was created correctly
    testPostcondition( reaction.use_count() > 0 );

    return reaction;
  }

  //----------------------------------------------------------------------------//
  //      ****ELECTROIONIZATION SUBSHELL REACTIONS****
  //----------------------------------------------------------------------------//

  // Create the subshell electroionization electroatomic reaction
  template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
  std::shared_ptr<const MonteCarlo::ElectroatomicReaction>
  createSubshellElectroionizationReaction(
      const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
      const unsigned subshell,
      const double evaluation_tol )
  {
    // Extract the common energy grid
    std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
    energy_grid->assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                         raw_electroatom_data.getElectronEnergyGrid().end() );

    // Construct the hash-based grid searcher
    std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                energy_grid,
                                energy_grid->size()/10 ) );

    // Create the reaction
    std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;
    MonteCarlo::ElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction<TwoDInterpPolicy,TwoDGridPolicy>(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        subshell,
        reaction,
        evaluation_tol );

    // Make sure the reaction was created correctly
    testPostcondition( reaction.use_count() > 0 );

    return reaction;
  }

  // Create the subshell electroionization electroatomic reactions
  template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
  std::vector<std::shared_ptr<const MonteCarlo::ElectroatomicReaction> >
  createSubshellElectroionizationReactions(
      const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
      const double evaluation_tol )
  {
    // Extract the common energy grid
    std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
    energy_grid->assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                         raw_electroatom_data.getElectronEnergyGrid().end() );

    // Construct the hash-based grid searcher
    std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                energy_grid,
                                energy_grid->size()/10 ) );


    MonteCarlo::ElectroionizationSamplingType sampling_type = MonteCarlo::KNOCK_ON_SAMPLING;

    // Create the reaction
    std::vector<std::shared_ptr<const MonteCarlo::ElectroatomicReaction> > reactions;
    MonteCarlo::ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<TwoDInterpPolicy,TwoDGridPolicy>(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        reactions,
        sampling_type,
        evaluation_tol );

    return reactions;
  }

  //----------------------------------------------------------------------------//
  //      ****BREMSSTRAHLUNG REACTIONS****
  //----------------------------------------------------------------------------//

  // Create the bremsstrahlung electroatomic reaction
  template<typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
  std::shared_ptr<const MonteCarlo::ElectroatomicReaction>
  createBremsstrahlungReaction(
      const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
      const bool dipole_distribution_mode_on,
      const double evaluation_tol )
  {
    // Extract the common energy grid
    std::shared_ptr<std::vector<double> > energy_grid(
      new std::vector<double>( raw_electroatom_data.getElectronEnergyGrid() ) );

    // Construct the hash-based grid searcher
    std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                energy_grid,
                                energy_grid->size()/10 ) );


    MonteCarlo::BremsstrahlungAngularDistributionType photon_distribution_function;

    if ( dipole_distribution_mode_on )
    {
      photon_distribution_function = DIPOLE_DISTRIBUTION;
    }
    else
    {
      photon_distribution_function = TWOBS_DISTRIBUTION;
    }

    // Create the reaction
    std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;
    MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<TwoDInterpPolicy,TwoDGridPolicy>(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        photon_distribution_function,
        evaluation_tol );

    // Make sure the reaction was created correctly
    testPostcondition( reaction.use_count() > 0 );

    return reaction;
  }
%}

%elastic_reaction_template_after_setup( Coupled )
%elastic_reaction_template_after_setup( Decoupled )
%elastic_reaction_template_after_setup( Hybrid )
%elastic_reaction_template_after_setup( MomentPreserving )
%elastic_reaction_template_after_setup( Cutoff )

// //---------------------------------------------------------------------------//
// // Add support for the Adjoint Electroatomic Reaction native factory helpers
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"

// %feature("docstring")
// MonteCarlo::AdjointElectroatomicReactionNativeFactoryHelpers
// "The Adjoint Electroatomic Reaction Native Factory Helpers"

//---------------------------------------------------------------------------//
// Add support for the templated factory helpers
//---------------------------------------------------------------------------//

// %cos_electron_function_interface_setup( CoupledElasticReaction )
// %cos_electron_function_interface_setup( DecoupledElasticReaction )
// %cos_electron_function_interface_setup( HybridElasticReaction )
// %cos_electron_function_interface_setup( CutoffElasticReaction )
// %cos_electron_function_interface_setup( MomentPreservingElasticReaction )
// %electron_function_interface_setup( SubshellElectroionizationReaction )
// %electron_function_interface_setup( BremsstrahlungReaction )

//---------------------------------------------------------------------------//
// Add support for the Electroatomic Reaction native factory
//---------------------------------------------------------------------------//

%inline %{

  // Create a decoupled elastic scattering electroatomic reaction
  std::shared_ptr<const MonteCarlo::DecoupledElasticElectroatomicReaction<Utility::LogLog> >
  createDecoupledElasticReaction(
      const Data::XSSEPRDataExtractor& raw_electroatom_data )
  {
    // Extract the common energy grid
    std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
    energy_grid->assign( raw_electroatom_data.extractElectronEnergyGrid().begin(),
                         raw_electroatom_data.extractElectronEnergyGrid().end() );

    // Construct the hash-based grid searcher
    std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                energy_grid,
                                energy_grid->size()/10 ) );

    // Create the reaction
    std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;
    MonteCarlo::ElectroatomicReactionACEFactory::createDecoupledElasticReaction(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction );

    // Make sure the reaction was created correctly
    testPostcondition( reaction.use_count() > 0 );

    return std::dynamic_pointer_cast<const MonteCarlo::DecoupledElasticElectroatomicReaction<Utility::LogLog> >(reaction);
  }
%}

/*//---------------------------------------------------------------------------//*/
/*// Add support for the electron scattering distribution ACE factory helpers*/
/*//---------------------------------------------------------------------------//*/

/*%include "MonteCarlo_ElectroatomicReactionACEFactoryHelpers.hpp"*/

/*%feature("docstring")*/
/*MonteCarlo::ElectroatomicReactionACEFactoryHelpers*/
/*"The Electron Scattering Distribution ACE Factory Helpers"*/

/*//---------------------------------------------------------------------------//*/
/*// Add support for the adjoint electron scattering distribution native factory helpers*/
/*//---------------------------------------------------------------------------//*/

/*%include "MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers.hpp"*/

/*%feature("docstring")*/
/*MonteCarlo::AdjointElectroatomicReactionNativeFactoryHelpers*/
/*"The Adjoint Electron Scattering Distribution Native Factory Helpers"*/

//---------------------------------------------------------------------------//
// Add support for the elastic electroatomic reactions
//---------------------------------------------------------------------------//

// %cos_electron_function_interface_setup( CoupledElasticReaction )
// %include "MonteCarlo_CoupledElasticElectroatomicReaction.hpp"


// %cos_electron_function_interface_setup( DecoupledElasticReaction )
// %include "MonteCarlo_DeCoupledElasticElectroatomicReaction.hpp"

// %include "MonteCarlo_HybridElasticElectroatomicReaction.hpp"
// %include "MonteCarlo_CutoffElasticElectroatomicReaction.hpp"
// %include "MonteCarlo_MomentPreservingElasticElectroatomicReaction.hpp"

// //---------------------------------------------------------------------------//
// // Add support for the bremsstrahlung electroatomic reactions
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"

// //---------------------------------------------------------------------------//
// // Add support for the electroionization subshell electroatomic reactions*/
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"

// //---------------------------------------------------------------------------//
// // Add support for the atomic excitation electroatomic reactions*/
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"


// //---------------------------------------------------------------------------//
// // Add support for the elastic adjoint electroatomic reactions
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_CoupledElasticAdjointElectroatomicReaction.hpp"
// %include "MonteCarlo_HybridElasticAdjointElectroatomicReaction.hpp"
// %include "MonteCarlo_CutoffElasticAdjointElectroatomicReaction.hpp"
// %include "MonteCarlo_MomentPreservingElasticAdjointElectroatomicReaction.hpp"

// //---------------------------------------------------------------------------//
// // Add support for the bremsstrahlung adjoint electroatomic reactions
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_BremsstrahlungAdjointElectroatomicReaction.hpp"

// //---------------------------------------------------------------------------//
// // Add support for the electroionization subshell adjoint electroatomic reactions
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_ElectroionizationSubshellAdjointElectroatomicReaction.hpp"

// //---------------------------------------------------------------------------//
// // Add support for the atomic excitation adjoint electroatomic reactions
// //---------------------------------------------------------------------------//

// %include "MonteCarlo_AtomicExcitationAdjointElectroatomicReaction.hpp"

// //---------------------------------------------------------------------------//
// // end MonteCarlo_ElectroatomicReaction.i
// //---------------------------------------------------------------------------//
