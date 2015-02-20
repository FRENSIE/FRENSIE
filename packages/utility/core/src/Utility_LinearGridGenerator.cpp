//---------------------------------------------------------------------------//
//! 
//! \file   Utility_LinearGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Linear grid generator class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <deque>

// FRENSIE Includes
#include "Utility_LinearGridGenerator.hpp"

namespace Utility{

// Constructor
LinearGridGenerator::LinearGridGenerator( 
			   const boost::function<double (double x)>& function )
  : d_function( function )
{
  // Make sure the function wrapper is not empty
  testPrecondition( !function.empty() );
}

// Reset the function
void LinearGridGenerator::resetFunction( 
			   const boost::function<double (double x)>& function )
{
  // Make sure the function wrapper is not empty
  testPrecondition( !function.empty() );

  d_function = function;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_LinearGridGenerator.cpp
//---------------------------------------------------------------------------//
