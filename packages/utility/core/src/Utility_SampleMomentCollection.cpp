//---------------------------------------------------------------------------//
//!
//! \file   Utility_SampleMomentCollection.cpp
//! \author Alex Robinson
//! \brief  The sample moment collection class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SampleMomentCollection.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_TEMPLATE_CLASS_INST( SampleMomentCollection<double,1,2> );
EXPLICIT_TEMPLATE_CLASS_INST( SampleMomentCollection<double,2,1> );
EXPLICIT_TEMPLATE_CLASS_INST( SampleMomentCollection<double,1,2,3,4> );
EXPLICIT_TEMPLATE_CLASS_INST( SampleMomentCollection<double,4,3,2,1> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_SampleMomentCollection.cpp
//---------------------------------------------------------------------------//
