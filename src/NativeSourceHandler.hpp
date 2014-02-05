//---------------------------------------------------------------------------//
//!
//! \file   NativeSourceHandler.hpp
//! \author Alex Robinson
//! \brief  Native source handler class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef NATIVE_SOURCE_HANDLER_HPP
#define NATIVE_SOURCE_HANDLER_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "SpatialDistribution.hpp"

namespace FACEMC{

//! Native source handler class
class NativeSourceHandler
{

public:

  //! Typedef for NativeSourceHandler pointer
  typedef Teuchos::RCP<NativeSourceHandler> Pointer;

  //! Get an instance of the handler (singleton pattern)
  static Pointer getInstance();

  //! Destructor
  ~NativeSourceHandler()
  { /* ... */ }
}

} // end FACEMC namespace

#endif // end NATIVE_SOURCE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end NativeSourceHandler.hpp
//---------------------------------------------------------------------------//
