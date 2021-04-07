//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Integral ordered typed observer phase space dimension
//!         discretization declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> );

//---------------------------------------------------------------------------//
// end MonteCarlo_IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
