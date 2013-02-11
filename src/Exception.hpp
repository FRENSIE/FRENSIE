//---------------------------------------------------------------------------//
/*!
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * \file Exception.hpp
 * \author Alex Robinson
 * \brief FAPMC exception handling and error policy declaration.
 */
//---------------------------------------------------------------------------//

#ifndef FAPMC_EXCEPTION_HPP
#define FAPMC_EXCEPTION_HPP

// Std Lib Includes
#include <stdexcept>
#include <string>

namespace FAPMC
{

/*!
 * \brief Exception class to be thrown when function preconditions are not
 * met.
 */
class PreconditionException : public std::runtime_error
{
public:
  PreconditionException( const std::string &msg )
    : std::runtime_error( msg )
  { /* ... */ }
};
  
/*!
 * \brief Exception class to be thrown when function postconditions are not
 * met.
 */
class PostconditionException : public std::runtime_error
{
public:
  PostconditionException( const std::string &msg )
    : std::runtime_error( msg )
  { /* ... */ }
};
  
/*!
 * \brief Exception class to be thrown when function postconditions are not
 * met
 */
class PostconditionException : public std::runtime_error
{
public:
  PostconditionException( const std::string &msg )
    : std::runtime_error( msg )
  { /* ... */ }
};
  
/*!
 * \brief Exception class to be thrown when function alters an invariant
 */
class InvariantException : public std::runtime_error
{
public:
  InvariantException( const std::string &msg )
    : std::runtime_error( msg )
  { /* ... */ }
};

/*!
 * \brief Exception class to be thrown when there is an error doing HDF5
 * operations.
 */
class HDF5Exception : public std::runtime_error
{
public:
  HDF5Exception( const std::string &msg )
    : std::runtime_error( msg )
  { /* ... */ }
};

/*!
 * \brief Exception class to be thrown when there is an unexpected 
 * interpolation flag in an EPDL data file
 */
class InterpFlagException : public std::runtime_error
{
public:
  InterpFlagException( const std::string &msg )
    : std::runtime_error( msg )
  { /* ... */ }
};

/*!
 * \brief Exception class to be thrown when a file cannot be opened
 */
class FileOpenException : public std::runtime_error
{
public:
  FileOpenException( const std::string &msg )
    : std::runtime_error( msg )
  { /* ... */ }

/*
 * \brief Exception class to be thrown when an invalid electron shell is 
 * encountered
 */
class InvalidShellException : public std::runtime_error
{
public:
  InvalidShellException( const std::string &msg )
    : std::runtime_error( msg )
  { /* ... */ }

};
  
// Test for precondition exception
void testPrecondition( bool throw_if_false, const std::string &msg );
  
// Test for a postcondition exception
void testPostcondition( bool throw_if_false, const std::string &msg );

// Test for an Invariant exception
void testInvariant( bool throw_if_false, const std::string &msg );

// Test for a HDF5 exception
void testHDF5Status( bool throw_if_false, const std::string &msg );

// Test for an interpolation flag exception
void testInterpFlagException( bool throw_if_false, const std::string &msg );

// Test for a file open exception
void testFileOpen( bool throw_if_false, const std::string &msg );

// Test for an invalid electron shell
void testInvalidShell( bool throw_if_false, const std::string &msg );

} // end namespace FAPMC

#endif // end FAPMC_EXCEPTION_HPP

//---------------------------------------------------------------------------//
// end Exception.hpp
//---------------------------------------------------------------------------//
