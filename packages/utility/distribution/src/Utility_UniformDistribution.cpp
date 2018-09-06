//---------------------------------------------------------------------------//
//!
//! \file   Utility_UniformDistribution.cpp
//! \author Alex Robinson
//! \brief  The uniform distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_UniformDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareUniformDistribution<void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareUniformDistribution<void,void> );

//---------------------------------------------------------------------------//
// end Utility_UniformDistribution.cpp
//---------------------------------------------------------------------------//
