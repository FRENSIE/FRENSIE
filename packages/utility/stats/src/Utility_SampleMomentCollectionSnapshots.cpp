//---------------------------------------------------------------------------//
//!
//! \file   Utility_SampleMomentCollectionSnapshots.cpp
//! \author Alex Robinson
//! \brief  The sample moment collection snapshots class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_SampleMomentCollectionSnapshots.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollectionSnapshots<double,std::list,1,2> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::SampleMomentCollectionSnapshots<double,std::list,1,2> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollectionSnapshots<double,std::list,2,1> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::SampleMomentCollectionSnapshots<double,std::list,2,1> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollectionSnapshots<double,std::list,1,2,3,4> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::SampleMomentCollectionSnapshots<double,std::list,1,2,3,4> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollectionSnapshots<double,std::list,4,3,2,1> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::SampleMomentCollectionSnapshots<double,std::list,4,3,2,1> );

//---------------------------------------------------------------------------//
// end Utility_SampleMomentCollectionSnapshots.cpp
//---------------------------------------------------------------------------//
