//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Floating point ordered typed observer phase space dimension
//!         discretization template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );

//---------------------------------------------------------------------------//
// end MonteCarlo_FloatingPointTypedObserverPhaseSpaceDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
