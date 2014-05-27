//---------------------------------------------------------------------------//
//!
//! \file   RandomNumberGenerator_def.hpp
//! \author Alex Robinson
//! \brief  Random number generation wrapper struct definition
//!
//---------------------------------------------------------------------------//

#ifndef RANDOM_NUMBER_GENERATOR_DEF_HPP
#define RANDOM_NUMBER_GENERATOR_DEF_HPP

// Trilinos Includes
#include <Teuchos_GlobalMPISession.hpp>

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Return a random number in interval [0,1)
template<typename ScalarType>
inline ScalarType RandomNumberGenerator::getRandomNumber()
{
  // Make sure that the generator has been initialized
  testPrecondition( generator );
  
  return static_cast<ScalarType>( generator->getRandomNumber() );
}

} // end FACEMC namespace

#endif // RANDOM_NUMBER_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end RandomNumberGenerator_def.hpp
//---------------------------------------------------------------------------//
