//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Hashed floating point ordered typed observer phase space dimension
//!         discretization template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );

//---------------------------------------------------------------------------//
// end MonteCarlo_HashedFloatingPointTypedObserverPhaseSpaceDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
