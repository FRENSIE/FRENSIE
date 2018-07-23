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
#include "Utility_SerializationHelpers.hpp"

using namespace MonteCarlo;
%}

// ---------------------------------------------------------------------------//
// Add ParticleDistribution support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_ParticleDistribution.hpp"

// ---------------------------------------------------------------------------//
// Add StandardParticleDistribution support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_StandardParticleDistribution.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleDistribution.i
//---------------------------------------------------------------------------//
