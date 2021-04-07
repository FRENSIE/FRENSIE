//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//! \author Alex Robinson
//! \brief  Default observer dimension discretization class definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP
#define MONTE_CARLO_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ObserverCosineDimensionDiscretization, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ObserverSourceEnergyDimensionDiscretization, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ObserverEnergyDimensionDiscretization, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ObserverSourceTimeDimensionDiscretization, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ObserverTimeDimensionDiscretization, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ObserverCollisionNumberDimensionDiscretization, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ObserverSourceIdDimensionDiscretization, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> );

#endif // end MONTE_CARLO_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization_def.hpp
//---------------------------------------------------------------------------//
