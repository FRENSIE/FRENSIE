//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleDistribution.i
//! \author Luke Kersting
//! \brief  The ParticleDistribution classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "MonteCarlo_ParticleDistribution.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"

#include "Utility_ToStringTraits.hpp"
#include "Utility_ToStringTraitsDecl.hpp"

using namespace MonteCarlo;
%}

// Import the ToStringTraitsDecl
%import "Utility_ToStringTraitsDecl.hpp"

// Ignore certian functions that use DimensionCounterMap
%ignore *::initializeDimensionCounters;
%ignore *::sampleAndRecordTrials;
%ignore *::sampleWithDimensionValueAndRecordTrials;


// ---------------------------------------------------------------------------//
// Add ParticleDistribution support
// ---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::ParticleDistribution )
%include "MonteCarlo_ParticleDistribution.hpp"

// ---------------------------------------------------------------------------//
// Add StandardParticleDistribution support
// ---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::StandardParticleDistribution )
%include "MonteCarlo_StandardParticleDistribution.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleDistribution.i
//---------------------------------------------------------------------------//
