//---------------------------------------------------------------------------//
//!
//! \file   Utility_Assertion.hpp
//! \author Alex Robinson
//! \brief  Special assertion and assertion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ASSERTION_HPP
#define UTILITY_ASSERTION_HPP

// Std Lib Includes
#include <exception>
#include <string>

// Trilinos Includes
#include <Teuchos_TestForException.hpp>

/*! \defgroup assertion_exceptions_macros FRNECS Assertion Exceptions and Macros
 *
 * Use these assertions to check for coding errors (debugging assertions) or
 * to verify user input in parts of the code where Design-By-Contract is not
 * appropriate. This assertion functionality is implemented with two exception
 * classes and three macros.
 */

namespace Utility
{

/*! Exception class to be thrown when degub assertion condition is not met.
 *
 * This Assertion class is a key part of \ref assert.
 * \ingroup assertion_exceptions_macros
 */
class Assertion : public std::logic_error
{
public:
  Assertion( const std::string& msg )
    : std::logic_error( msg )
  { /* ... */ }

  virtual ~Assertion() throw()
  { /* ... */ }
};

/*! Exception class to be thrown when a critical (user input) assertion condition is not met.
 *
 * This Assertion class is a key part of \ref assert.
 * \ingroup assertion_exceptions_macros
 */
class CriticalAssertion : public std::runtime_error
{
public:
  CriticalAssertion( const std::string& msg )
    : std::runtime_error( msg )
  { /* ... */ }

  virtual ~CriticalAssertion() throw()
  { /* ... */ }
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Assertion macros
//---------------------------------------------------------------------------//
/*! \page assert FRNECS Assertion
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
 *
 * Developers whould refer to the \ref assertion_exceptions_macros page
 * for more on how this functionality is implemented.
 */

/*! Assert that a critical (user input) condition is always met.
 * \ingroup assertion_exceptions_macros
 */
#define ASSERT_ALWAYS(c) \
  TEUCHOS_TEST_FOR_EXCEPTION( !(c),		\
                              Utility::CriticalAssertion,		\
                              "FRNECS critical assertion failed" << std::endl )

/*! Assert that a critical (user input) condition is always met.
 *
 * This macro will print the desired message when the condition is not met.
 * \ingroup assertion_exceptions_macros
 */
#define ASSERT_ALWAYS_MSG( c, msg ) \
  TEUCHOS_TEST_FOR_EXCEPTION( !(c), \
			      Utility::CriticalAssertion, \
			      msg << std::endl )

#if NDEBUG

#define ASSERT(c)

#else

/*! Assert that a condition is always met.
 *
 * This macro should be used during code development to test that certain 
 * conditions are met in pieces of code where Design-By-Contract is not
 * appropriate. 
 * \ingroup assertion_exceptions_macros
 */
#define ASSERT(c) \
  TEUCHOS_TEST_FOR_EXCEPTION( !(c),		\
			      Utility::Assertion,			\
			      "FRNECS assertion failed" << std::endl )

#endif // end NDEBUG

#endif // end UTILITY_ASSERTION_HPP

//---------------------------------------------------------------------------//
// end Utility_Assertion.hpp
//---------------------------------------------------------------------------//

