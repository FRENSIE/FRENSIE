//---------------------------------------------------------------------------//
//!
//! \file   StateSource.hpp
//! \author Alex Robinson
//! \brief  State source class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef STATE_SOURCE_HPP
#define STATE_SOURCE_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "ParticleSource.hpp"

/*! The state source class
 * \details This class takes an array of particle states and assigns on of
 * the states in the array to the particle state of interest. This is similar
 * to the surface source in MCNP (but more general).
 */
template<typename ParticleState>
class StateSource
