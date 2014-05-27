//---------------------------------------------------------------------------//
//!
//! \file   ExceptionTestMacros.hpp
//! \author Alex Robinson
//! \brief  Macros that test if an exception has occured and throw if so
//!
//---------------------------------------------------------------------------//

#ifndef EXCEPTION_TEST_MACROS_HPP
#define EXCEPTION_TEST_MACROS_HPP

// Std Lib Includes
#include <sstream>
#include <string>

/*! Exception test macro used to throw an exception when a required condition
 * fails.
 *
 * This macro is based off of the Teuchos_TestForException macro. This macro
 * should be used anywhere that the failure of a specified conditions 
 * warrants the throwing of an exception.
 * \ingroup execption_macros
 */
#define TEST_FOR_EXCEPTION(throw_exception_test, Exception, msg)	\
{									\
 const bool throw_exception = (throw_exception_test);			\
 if( throw_exception ){							\
   std::ostringstream detailed_msg;					\
   detailed_msg << __FILE__ << ":" << __LINE__ << ":\n\n"		\
       << "Throw test that evaluated to true: "#throw_exception_test	\
       << "\n\n" << msg;						\
   const std::string &detailed_msg_str = detailed_msg.str();		\
   throw Exception(detailed_msg_str);					\
 }									\
} 

#endif // end EXCEPTION_TEST_MACROS_HPP

//---------------------------------------------------------------------------//
// end ExceptionTestMacros.hpp
//---------------------------------------------------------------------------//

