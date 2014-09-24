//---------------------------------------------------------------------------//
//!
//! \file   Utility_ContractException.hpp
//! \author Alex Robinson (aprobinson@wisc.edu)
//! \brief  Design-by-Contract exception handling and error policy declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_CONTRACT_EXCEPTION_HPP
#define UTILITY_CONTRACT_EXCEPTION_HPP

// Std Lib Includes
#include <stdexcept>
#include <string>

// Boost Includes
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

// FRENSIE Includes
#include "FRENSIE_config.hpp"
#include "Utility_ExceptionTestMacros.hpp"

/*! \defgroup contract_exceptions_macros Design-By-Contract Exceptions and Macros
 *
 * Design-By-Contract is a powerful way to ensure that certain function
 * preconditions and postconditions are explicit. When Design-By-Contract
 * functionality is enabled, the program will exit whenever one of these
 * conditions is not met. This functionality is made possible through a series
 * of macros and an exception class.
 */

namespace Utility{

//---------------------------------------------------------------------------//
// Design-By-Contract Exceptions
//---------------------------------------------------------------------------//

/*! Exception class to be thrown when function contract is not met.
 *
 * The ContractExpection class is a key part of \ref DBC.
 * \ingroup contract_exceptions_macros
 */
class ContractException : public std::logic_error
{
public:
  ContractException( const std::string &msg )
    : std::logic_error( msg )
  { /* ... */ }
  
  virtual ~ContractException() throw()
  { /* ... */ }
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Design-by-Contract Macros.
//---------------------------------------------------------------------------//
#if HAVE_FRENSIE_DBC

/*! Test a function precondition
 * \ingroup contract_exceptions_macros 
 */
#define testPrecondition(c)						\
  TEST_FOR_EXCEPTION( !(c),						\
		      Utility::ContractException,			\
		      "Precondition exception" << std::endl ) 

/*! Test a function postcondition
 * \ingroup contract_exceptions_macros
 */
#define testPostcondition(c)					\
  TEST_FOR_EXCEPTION( !(c),					\
		      Utility::ContractException,		\
		      "Postcondition exception" << std::endl ) 

/*! Test a function invariant
 * \ingroup contract_exceptions_macros
 */
#define testInvariant(c)						\
  TEST_FOR_EXCEPTION( !(c),						\
		      Utility::ContractException,			\
		      "Invariant exception" << std::endl )

/*! Remember a variable that is needed for testing DBC conditions
 * \ingroup contract_exceptions_macros
 */
#define remember(c) c

#else
			      
#define testPrecondition(c)
#define testPostcondition(c)
#define testInvariant(c)
#define remember(c)

#endif // end HAVE_FRENSIE_DBC

/*! test a templated function static precondition
 * \ingroup contract_exceptions_macros
 */
#define testStaticPrecondition(c) \
  BOOST_STATIC_ASSERT( (c) )

#endif // end UTILITY_CONTRACT_EXCEPTION_HPP

//---------------------------------------------------------------------------//
// end Utility_ContractException.hpp
//---------------------------------------------------------------------------//
