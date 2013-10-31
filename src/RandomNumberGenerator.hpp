//---------------------------------------------------------------------------//
//!
//! \file   RandomNumberGenerator.hpp
//! \author Alex Robinson
//! \brief  Random number generation wrapper struct declaration
//!
//---------------------------------------------------------------------------//

#ifndef RANDOM_NUMBER_GENERATOR_HPP
#define RANDOM_NUMBER_GENERATOR_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// SPRNG includes
#include <Sprng.hpp>
#include <LCG64.hpp>
#include <LCG.hpp>

// FACEMC includes
#include "LinearCongruentialGenerator.hpp"
#include "FACEMC_mpi_config.hpp"

namespace FACEMC{

//! Struct that is used to obtain random numbers
template<typename ScalarType>
struct RandomNumberGenerator
{
  //! Initialize the generator
  static void initialize( const unsigned long long history_number = 0ULL );

  //! Reset the generator to its initial state
  static void reset();

  //! Return a random number in interval [0,1)
  static ScalarType getRandomNumber();

private:

#if defined(HAVE_FACEMC_MPI) && !defined(NDEBUG)
  // Pointer to generator with reproducible parallel streams
  static Teuchos::RCP<LinearCongruentialGenerator<ScalarType> > generator;

#else
  // Pointer to generator
  static Teuchos::RCP<sprng::LCG64> generator;

#endif
};

//! Policy struct for getting SPRNG float random numbers
template<typename ScalarType>
struct SprngPolicy
{
  static inline ScalarType getSprngRandomNumber( 
					Teuchos::RCP<sprng::LCG64> &generator )
  { return generator->get_rn_flt(); }
};

//! Policy struct for getting SPRNG double random numbers
template<>
struct SprngPolicy<double>
{
  static inline double getSprngRandomNumber(
					Teuchos::RCP<sprng::LCG64> &generator )
  { return generator->get_rn_dbl(); }
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "RandomNumberGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end RANDOM_NUMBER_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end RandomNumberGenerator.hpp
//---------------------------------------------------------------------------//
