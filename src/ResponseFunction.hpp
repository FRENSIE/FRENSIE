//---------------------------------------------------------------------------//
//!
//! \file   ResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Response function base class declaration 
//!
//---------------------------------------------------------------------------//

#ifndef RESPONSE_FUNCTION_HPP
#define RESPONSE_FUNCTION_HPP

namespace FACEMC{

//! The response function base class
class ResponseFunction
{

public:

  //! Default constructor
  ResponseFunction();

  //! Destructor
  ~ResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired energy
  virtual double evaluate( const double energy ) = 0;

};

} // end FACEMC namespace

#endif // end RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end ResponseFunction.hpp
//---------------------------------------------------------------------------//
