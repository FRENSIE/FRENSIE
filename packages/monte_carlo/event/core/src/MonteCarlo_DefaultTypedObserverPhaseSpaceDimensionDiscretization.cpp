//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Default observer dimension discretization class declarations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ObserverCosineDimensionDiscretization );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ObserverSourceEnergyDimensionDiscretization );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ObserverEnergyDimensionDiscretization );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ObserverSourceTimeDimensionDiscretization );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ObserverTimeDimensionDiscretization );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ObserverCollisionNumberDimensionDiscretization );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ObserverSourceIdDimensionDiscretization );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> );

//---------------------------------------------------------------------------//
// end MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
