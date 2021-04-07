//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_OrderedTypedObserverPhaseSpaceDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Ordered typed observer phase space dimension discretization
//!         template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_OrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::OrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );

//---------------------------------------------------------------------------//
// end MonteCarlo_OrderedTypedObserverPhaseSpaceDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
