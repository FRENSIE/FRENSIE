//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_NumpyImporter.hpp
//! \author Alex Robinson
//! \brief  The numpy import class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PYFRENSIE_NUMPY_IMPORTER_HPP
#define PYFRENSIE_NUMPY_IMPORTER_HPP

// Numpy includes
#include "numpy_include.h"

namespace PyFrensie{

/*! Numpy importer class
 * 
 * Before any numpy macros/functions get called import_array() must be
 * called (once and only once). This singleton class makes this call and
 * ensures that it is only made once.
 */
class NumpyImporter
{

public:

  //! Check if the import was successful
  static bool success();

protected:

  //! Constructor
  NumpyImporter();

  //! Destructor
  ~NumpyImporter()
  { /* ... */ }

private:

  static NumpyImporter s_instance;
};
  
} // end PyFrensie namespace

#endif // end PYFRENSIE_NUMPY_IMPORTER_HPP

//---------------------------------------------------------------------------//
// end PyFrensie_NumpyImporter.hpp
//---------------------------------------------------------------------------//
