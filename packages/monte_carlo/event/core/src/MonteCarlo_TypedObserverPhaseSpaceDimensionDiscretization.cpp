//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Typed observer phase space dimension discretization base class
//!         template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> );

//---------------------------------------------------------------------------//
// end MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
