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

using namespace MonteCarlo;
%}

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
