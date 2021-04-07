//---------------------------------------------------------------------------//
//!
//! \file   Utility_StreamableObject.hpp
//! \author Alex Robinson
//! \brief  Streamable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STREAMABLE_OBJECT_HPP
#define UTILITY_STREAMABLE_OBJECT_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_OStreamableObject.hpp"
#include "Utility_IStreamableObject.hpp"

namespace Utility{

//! The base class for input/output streamable objects
class StreamableObject : public OStreamableObject, public IStreamableObject
{ /* ... */ };
  
} // end Utility namespace

#endif // end UTILITY_STREAMABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_StreamableObject.hpp
//---------------------------------------------------------------------------//
