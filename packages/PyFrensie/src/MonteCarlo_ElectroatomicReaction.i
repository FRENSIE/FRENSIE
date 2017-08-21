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

// Add use of std::shared_ptr
%shared_ptr(MonteCarlo::AtomicReaction)
%shared_ptr(MonteCarlo::ElectroatomicReaction)
%shared_ptr(MonteCarlo::CoupledElasticElectroatomicReaction)

// Ignore react
%ignore *::react( ElectronState&, ParticleBank&, Data::SubshellType& ) const;
%ignore *::react( ElectronState&, ParticleBank&, Data::SubshellType&, unsigned& ) const;
// Ignore getReactionType
%ignore *::getReactionType() const;
// Ignore getCrossSection
%ignore *::getCrossSection( double const, unsigned const) const;

//---------------------------------------------------------------------------//
// Add support for the Atomic and Electroatomic Reaction classes
//---------------------------------------------------------------------------//

%include "MonteCarlo_AtomicReaction.hpp"
%include "MonteCarlo_ElectroatomicReaction.hpp"

// Atomic reaction interface setup
%electroatomic_reaction_interface_setup( AtomicReaction )
%electroatomic_reaction_interface_setup( ElectroatomicReaction )

//---------------------------------------------------------------------------//
// Add support for the Electroatomic Reaction native factory helpers
//---------------------------------------------------------------------------//

%include "MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.hpp"

%feature("docstring")
MonteCarlo::ElectroatomicReactionNativeFactoryHelpers
"The Electroatomic Reaction Native Factory Helpers"

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
//%include "MonteCarlo_CutoffElasticElectroatomicReaction.hpp"
//%include "MonteCarlo_MomentPreservingElasticElectroatomicReaction.hpp"

////---------------------------------------------------------------------------//
//// Add support for the bremsstrahlung electroatomic reactions
////---------------------------------------------------------------------------//

//%include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"

////---------------------------------------------------------------------------//
//// Add support for the electroionization subshell electroatomic reactions*/
////---------------------------------------------------------------------------//

//%include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"

///*//---------------------------------------------------------------------------//*/
///*// Add support for the atomic excitation electroatomic reactions*/
///*//---------------------------------------------------------------------------//*/

//%include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReaction.i
//---------------------------------------------------------------------------//
