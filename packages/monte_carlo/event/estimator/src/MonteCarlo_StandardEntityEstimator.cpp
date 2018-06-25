//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEntityEstimator.cpp
//! \author Alex Robinson
//! \brief  The standard entity estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardEntityEstimator.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( StandardEntityEstimator<Geometry::Model::InternalCellHandle> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardEntityEstimator<moab::EntityHandle> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEntityEstimator.cpp
//---------------------------------------------------------------------------//
