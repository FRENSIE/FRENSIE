//---------------------------------------------------------------------------//
//!
//! \file   RandomNumberGenerator_def.hpp
//! \author Alex Robinson
//! \brief  Random number generation wrapper struct declaration
//!
//---------------------------------------------------------------------------//

#ifndef RANDOM_NUMBER_GENERATOR_DEF_HPP
#define RANDOM_NUMBER_GENERATOR_DEF_HPP

// Trilinos Includes
#include <Teuchos_GlobalMPISession.hpp>

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Initialize the stored generator pointer
#if defined(HAVE_FACEMC_MPI) && !defined(NDEBUG)
template<typename ScalarType>
Teuchos::RCP<LinearCongruentialGenerator<ScalarType> > 
RandomNumberGenerator<ScalarType>::generator;
#else
template<typename ScalarType>
Teuchos::RCP<sprng::LCG64> RandomNumberGenerator<ScalarType>::generator;
#endif

// Initialize the generator
template<typename ScalarType>
void RandomNumberGenerator<ScalarType>::initialize( 
				      const unsigned long long history_number )
{
#if defined(HAVE_FACEMC_MPI) && !defined(NDEBUG)
  if( generator.is_null() )
    generator.reset( new LinearCongruentialGenerator<ScalarType> );
  
  generator->changeHistory( history_number );

#else
  if( generator.is_null() )
  {  
    generator.reset( new sprng::LCG64 );
    generator->init_rng( Teuchos::GlobalMPISession::getRank(), 
			 Teuchos::GlobalMPISession::getNProc(), 
			 0, 
			 0 );
  }
#endif

  // Make sure that the generator has been created
  testPostcondition( !generator.is_null() );
}

// Reset the generator to its initial state
template<typename ScalarType>
void RandomNumberGenerator<ScalarType>::reset()
{
#if defined(HAVE_FACEMC_MPI) && !defined(NDEBUG)
  generator.reset( new LinearCongruentialGenerator<ScalarType> );
  generator->changeHistory( 0ULL );

#else
  generator.reset( new sprng::LCG64 );
  generator->init_rng( Teuchos::GlobalMPISession::getRank(), 
		       Teuchos::GlobalMPISession::getNProc(), 
		       0, 
		       0 );
#endif

  // Make sure that the generator has been created
  testPostcondition( !generator.is_null() );
}

// Return a random number in interval [0,1)
template<typename ScalarType>
inline ScalarType RandomNumberGenerator<ScalarType>::getRandomNumber()
{
  // Make sure that the generator has been initialized
  testPrecondition( !generator.is_null() );
  
#if defined(HAVE_FACEMC_MPI) && !defined(NDEBUG)
  return generator->rnd();

#else
  return SprngPolicy<ScalarType>::getSprngRandomNumber( generator );

#endif
}

} // end FACEMC namespace

#endif // RANDOM_NUMBER_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end RandomNumberGenerator_def.hpp
//---------------------------------------------------------------------------//
