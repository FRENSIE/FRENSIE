//---------------------------------------------------------------------------//
//!
//! \file   FACEMC_Assertion.hpp
//! \author Alex Robinson
//! \brief  FACEMC assertion and assertion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ASSERTION_HPP
#define FACEMC_ASSERTION_HPP

// Std Lib Includes
#include <exception>
#include <string>

// Trilinos Includes
#include <Teuchos_TestForException.hpp>

namespace FACEMC
{

class Assertion : public std::logic_error
{
public:
  Assertion( const std::string& msg )
    : std::logic_error( msg )
  { /* ... */ }

  virtual ~Assertion() throw()
  { /* ... */ }
};

class CriticalAssertion : public std::runtime_error
{
public:
  CriticalAssertion( const std::string& msg )
    : std::runtime_error( msg )
  { /* ... */ }

  virtual ~CriticalAssertion() throw()
  { /* ... */ }
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Assertion macros
//---------------------------------------------------------------------------//
/*! \page assert FACEMC Assertion
 *
 * Two types of assertions are often needed: assertions used to check for
 * coding errors (debugging assertions) and assertions that check for user
 * error. Debugging assertions will only be activated when the code has been
 * compiled in debug mode. When compiled in release mode, the macro NDEBUG
 * is set by the compiler, which will prevent the execution of degubbing
 * assertion code. 
 *
 * Use assertions in parts of the code where Design-by-Contract is not used,
 * when writing new pieces of code that have not been unit tested and when
 * correct user input is extremely critical to the execution of the program.
*/

#define FACEMC_ASSERT_ALWAYS(c) \
  TEUCHOS_TEST_FOR_EXCEPTION( !(c),		\
                              FACEMC::CriticalAssertion,		\
                              "FACEMC critical assertion failed" << std::endl )

#define FACEMC_ASSERT_ALWAYS_MSG( c, msg ) \
  TEUCHOS_TEST_FOR_EXCEPTION( !(c), \
			      FACEMC::CriticalAssertion, \
			      msg << std::endl )

#if NDEBUG

#define FACEMC_ASSERT(c)

#else

#define FACEMC_ASSERT(c) \
  TEUCHOS_TEST_FOR_EXCEPTION( !(c),		\
			      FACEMC::Assertion,			\
			      "FACEMC assertion failed" << std::endl )

#endif

#endif // end FACEMC_ASSERTION_HPP

//---------------------------------------------------------------------------//
// end FACEMC_Assertion.hpp
//---------------------------------------------------------------------------//

