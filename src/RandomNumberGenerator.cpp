//---------------------------------------------------------------------------//
//!
//! \file   RandomNumberGenerator.cpp
//! \author Alex Robinson
//! \brief  Random number generator wrapper struct declaration.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "RandomNumberGenerator.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Initialize the stored generator pointer
#if defined(HAVE_FACEMC_MPI) && !defined(NDEBUG)
Teuchos::RCP<LinearCongruentialGenerator> RandomNumberGenerator::generator;
#else
Teuchos::RCP<sprng::LCG64> RandomNumberGenerator::generator;
#endif

// Initialize the generator
void RandomNumberGenerator::initialize( 
				      const unsigned long long history_number )
{
#if defined(HAVE_FACEMC_MPI) && !defined(NDEBUG)
  if( generator.is_null() )
    generator.reset( new LinearCongruentialGenerator() );
  
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
void RandomNumberGenerator::reset()
{
#if defined(HAVE_FACEMC_MPI) && !defined(NDEBUG)
  generator.reset( new LinearCongruentialGenerator() );
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

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end RandomNumberGenerator.cpp
//---------------------------------------------------------------------------//
