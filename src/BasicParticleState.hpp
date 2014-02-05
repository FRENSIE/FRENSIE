//---------------------------------------------------------------------------//
//!
//! \file   BasicParticleState.hpp
//! \author Alex Robinson
//! \brief  Basic particle state struct declaration
//!
//---------------------------------------------------------------------------//

#ifndef BASIC_PARTICLE_STATE_HPP
#define BASIC_PARTICLE_STATE_HPP

namespace FACEMC{

//! The basic particle state struct
struct BasicParticleState
{
  //! Energy of the particle
  double energy;

  //! Position of the particle
  double position[3];

  //! Direction of the particle
  double direction[3];

  //! Time of the particle
  double time;

  //! Weight o the particle
  double weight;
};

} // end FACEMC namespace
