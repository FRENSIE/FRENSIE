//---------------------------------------------------------------------------//
// \file ContractException.hpp
// \author Alex Robinson
// \brief Design-by-Contract exception handling and error policy declaration.
//---------------------------------------------------------------------------//

#ifndef CONTRACT_EXCEPTION_HPP
#define CONTRACT_EXCEPTION_HPP

// Std Lib Includes
#include <stdexcept>
#include <string>

// Trilinos Includes
#include <Teuchos_TestForException.hpp>

// FACEMC Includes
#include "FACEMC_config.hpp"

namespace FACEMC
{

//---------------------------------------------------------------------------//
// Design-By-Contract Exceptions
//---------------------------------------------------------------------------//

/*!
 * \brief Exception class to be thrown when function contract is not met
 * met.
 */
class ContractException : public std::logic_error
{
public:
  ContractException( const std::string &msg )
    : std::runtime_error( msg )
  { /* ... */ }
  
  virtual ~ContractException()
  { /* ... */ }
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Design-by-Contract macros.
//---------------------------------------------------------------------------//
/*!
  \page FACEMC Design-by-Contract

  Design-by-Contract (DBC) functionality is provided to verify function
  preconditions, postconditions, and invariants. These checks are separated
  from the debug build and can be activated for both release and debug
  builds. They can be activated by setting the following in a CMake
  configure:
 
  -D FACEMC_ENABLE_DBC:BOOL=ON
 
  By default, DBC is deactivated. Although they will require additional
  computational overhead, these checks provide a mechanism for veryifing
  library input arguments. Note that the bounds-checking functionality used
  within the Chimera is only provided by a debug build.
 
  In addition, remember is provided to store values used only for DBC
  checks and no other place in executed code.
 */

#if HAVE_FACEMC_DBC

#define testPrecondition(c) \
  TEUCHOS_TEST_FOR_EXCEPTION( !(c),					\
			      ContractException,			\
			      "Precondition exception" << std::endl ) 
#define testPostcondition(c) \
  TEUCHOS_TEST_FOR_EXCEPTION( !(c),					\
			      ContractException,			\
			      "Postcondition exception" << std::endl ) 
#define testInvariant(c) \
  TEUCHOS_TEST_FOR_EXCEPTION( !(c),					\
                              ContractException,			\
			      "Invariant exception" << std::endl )
#define remember(c) c

#else
			      
#define testPrecondition(c)
#define testPostcondition(c)
#define testInvariant(c)
#define remember(c)

#endif

#endif // end CONTRACT_EXCEPTION_HPP

//---------------------------------------------------------------------------//
// end Exception.hpp
//---------------------------------------------------------------------------//
