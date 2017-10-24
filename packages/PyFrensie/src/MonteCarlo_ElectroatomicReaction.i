//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReaction.i
//! \author Luke Kersting
//! \brief  The Electroatomic Reaction class interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "MonteCarlo_AtomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_CoupledElasticElectroatomicReaction.hpp"
#include "MonteCarlo_HybridElasticElectroatomicReaction.hpp"
#include "MonteCarlo_CutoffElasticElectroatomicReaction.hpp"
#include "MonteCarlo_MomentPreservingElasticElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_CoupledElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_HybridElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_CutoffElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_MomentPreservingElasticAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectroatomicReaction.hpp"
%}

// Include std::string support
%include <std_string.i>

// C++ STL support
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Import the PyFrensie Teuchos Array conversion helpers
%import "PyFrensie_ArrayConversionHelpers.hpp"

// Import the explicit template instantiation helpers
%import "Utility_ExplicitTemplateInstantiationMacros.hpp"

// Include the electroatomic reaction helpers
%include "MonteCarlo_ElectroatomicReactionHelpers.i"
%include "MonteCarlo_ElectronTemplateHelpers.i"

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::AtomicReaction)
%shared_ptr(MonteCarlo::ElectroatomicReaction)
%shared_ptr(MonteCarlo::AdjointElectroatomicReaction)
%shared_ptr(MonteCarlo::CoupledElasticElectroatomicReaction)
%shared_ptr(MonteCarlo::BremsstrahlungAdjointElectroatomicReaction)

// Ignore react
%ignore *::react( ElectronState&, ParticleBank&, Data::SubshellType& ) const;
%ignore *::react( ElectronState&, ParticleBank&, Data::SubshellType&, unsigned& ) const;
%ignore *::react( AdjointElectronState&, ParticleBank&, Data::SubshellType& ) const;
%ignore *::react( AdjointElectronState&, ParticleBank&, Data::SubshellType&, unsigned& ) const;
// Ignore getReactionType
%ignore *::getReactionType() const;
// Ignore getCrossSection
%ignore *::getCrossSection( double const, unsigned const) const;

//---------------------------------------------------------------------------//
// Add support for the Atomic, Electroatomic, and AdjointElectroatomic Reaction classes
//---------------------------------------------------------------------------//

%include "MonteCarlo_AtomicReaction.hpp"
%include "MonteCarlo_ElectroatomicReaction.hpp"
%include "MonteCarlo_AdjointElectroatomicReaction.hpp"

// Atomic reaction interface setup
%electroatomic_reaction_interface_setup( AtomicReaction )
%electroatomic_reaction_interface_setup( ElectroatomicReaction )
%electroatomic_reaction_interface_setup( AdjointElectroatomicReaction )

//---------------------------------------------------------------------------//
// Add support for the Electroatomic Reaction native factory helpers
//---------------------------------------------------------------------------//

%include "MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.hpp"

%feature("docstring")
MonteCarlo::ElectroatomicReactionNativeFactoryHelpers
"The Electroatomic Reaction Native Factory Helpers"

//---------------------------------------------------------------------------//
// Add support for the Adjoint Electroatomic Reaction native factory helpers
//---------------------------------------------------------------------------//

%include "MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers.hpp"

%feature("docstring")
MonteCarlo::AdjointElectroatomicReactionNativeFactoryHelpers
"The Adjoint Electroatomic Reaction Native Factory Helpers"

//---------------------------------------------------------------------------//
// Add support for the templated factory helpers
//---------------------------------------------------------------------------//

%cos_electron_function_interface_setup( CoupledElasticReaction )
%cos_electron_function_interface_setup( DecoupledElasticReaction )
%cos_electron_function_interface_setup( HybridElasticReaction )
%cos_electron_function_interface_setup( CutoffElasticReaction )
%cos_electron_function_interface_setup( MomentPreservingElasticReaction )
%electron_function_interface_setup( SubshellElectroionizationReaction )
%electron_function_interface_setup( BremsstrahlungReaction )

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

%include "MonteCarlo_CoupledElasticElectroatomicReaction.hpp"
%include "MonteCarlo_HybridElasticElectroatomicReaction.hpp"
%include "MonteCarlo_CutoffElasticElectroatomicReaction.hpp"
%include "MonteCarlo_MomentPreservingElasticElectroatomicReaction.hpp"

//---------------------------------------------------------------------------//
// Add support for the bremsstrahlung electroatomic reactions
//---------------------------------------------------------------------------//

%include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"

//---------------------------------------------------------------------------//
// Add support for the electroionization subshell electroatomic reactions*/
//---------------------------------------------------------------------------//

%include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"

//---------------------------------------------------------------------------//
// Add support for the atomic excitation electroatomic reactions*/
//---------------------------------------------------------------------------//

%include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"


//---------------------------------------------------------------------------//
// Add support for the elastic adjoint electroatomic reactions
//---------------------------------------------------------------------------//

%include "MonteCarlo_CoupledElasticAdjointElectroatomicReaction.hpp"
%include "MonteCarlo_HybridElasticAdjointElectroatomicReaction.hpp"
%include "MonteCarlo_CutoffElasticAdjointElectroatomicReaction.hpp"
%include "MonteCarlo_MomentPreservingElasticAdjointElectroatomicReaction.hpp"

//---------------------------------------------------------------------------//
// Add support for the bremsstrahlung adjoint electroatomic reactions
//---------------------------------------------------------------------------//

%include "MonteCarlo_BremsstrahlungAdjointElectroatomicReaction.hpp"

//---------------------------------------------------------------------------//
// Add support for the electroionization subshell adjoint electroatomic reactions
//---------------------------------------------------------------------------//

%include "MonteCarlo_ElectroionizationSubshellAdjointElectroatomicReaction.hpp"

//---------------------------------------------------------------------------//
// Add support for the atomic excitation adjoint electroatomic reactions
//---------------------------------------------------------------------------//

%include "MonteCarlo_AtomicExcitationAdjointElectroatomicReaction.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReaction.i
//---------------------------------------------------------------------------//
