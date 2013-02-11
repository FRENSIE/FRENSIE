//---------------------------------------------------------------------------//
/*!
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * \file Exception.cpp
 * \author Alex Robinson
 * \brief FAPMC exception handling and error policy definition
 */
//---------------------------------------------------------------------------//

#include <iostream>

#include "Exception.hpp"

#include <Teuchos_TestForException.hpp>

namespace FAPMC
{

/*!
 * \brief Test for a precondition exception
 */
void testPrecondition( bool throw_if_false, const std::string &msg )
{
  TEUCHOS_TEST_FOR_EXCEPTION( !throw_if_false,
			      PreconditionException,
			      msg << std::endl; );
}

/*!
 * \brief Test for a postcondition exception
 */
void testPostcondition( bool throw_if_false, const std::string &msg )
{
  TEUCHOS_TEST_FOR_EXCEPTION( !throw_if_false,
			      PostconditionException,
			      msg << std::endl );
}

/*!
 * \brief Test for an Invariant exception
 */
void testInvariant( bool throw_if_false, const std::string &msg )
{
  TEUCHOS_TEST_FOR_EXCEPTION( !throw_if_false,
			      InvariantException,
			      msg << std::endl );
}

/*!
 * \brief Test for a HDF5 exception
 */
void testHDF5Status( bool throw_if_false, const std::string &msg )
{
  TEUCHOS_TEST_FOR_EXCEPTION( !throw_if_false,
			      HDF5Exception,
			      msg << std::endl );
}

/*!
 * \brief Test for an interpolation flag exception
 */
void testInterpFlagException( bool throw_if_false, const std::string &msg )
{
  TEUCHOS_TEST_FOR_EXCEPTION( !throw_if_false,
			      InterpFlagException,
			      msg << std::endl );
}

/*!
 * \brief Test for a file open exception
 */
void testFileOpen( bool throw_if_false, const std::string &msg )
{
  TEUCHOS_TEST_FOR_EXCEPTION( !throw_if_false,
			      InterpFlagException,
			      msg << std::endl );
}

/*!
 * \brief Test for an invalid electron shell
 */
void testInvalidShell( bool throw_if_false, const std::string &msg )
{
  TEUCHOS_TEST_FOR_EXCEPTION( !throw_if_false,
			      InvalidShellException,
			      msg << std::endl );
}

} //end FACEMC namespace

//---------------------------------------------------------------------------//
// end Exception.cpp
//---------------------------------------------------------------------------//
