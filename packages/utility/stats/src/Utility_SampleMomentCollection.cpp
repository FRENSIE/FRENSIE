//---------------------------------------------------------------------------//
//!
//! \file   Utility_SampleMomentCollection.cpp
//! \author Alex Robinson
//! \brief  The sample moment collection class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_SampleMomentCollection.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollection<double,1,2> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::SampleMomentCollection<double,1,2> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollection<double,2,1> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::SampleMomentCollection<double,2,1> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollection<double,1,2,3,4> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::SampleMomentCollection<double,1,2,3,4> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollection<double,4,3,2,1> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::SampleMomentCollection<double,4,3,2,1> );

//---------------------------------------------------------------------------//
// end Utility_SampleMomentCollection.cpp
//---------------------------------------------------------------------------//
