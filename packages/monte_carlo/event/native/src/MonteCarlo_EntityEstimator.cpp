//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EntityEstimator.cpp
//! \author Alex Robinson
//! \brief  The Entity estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EntityEstimator.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( EntityEstimator<Geometry::ModuleTraits::InternalCellHandle> );
EXPLICIT_TEMPLATE_CLASS_INST( EntityEstimator<moab::EntityHandle> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EntityEstimator.cpp
//---------------------------------------------------------------------------//
