//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardSurfaceEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Standard surface estimator class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_SURFACE_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_STANDARD_SURFACE_ESTIMATOR_DEF_HPP

namespace MonteCarlo{

// Constructor (for flux estimators)
template<template<typename,typename...> class STLCompliantArrayA,
         template<typename,typename...> class STLCompliantArrayB>
StandardSurfaceEstimator::StandardSurfaceEstimator(
                          const Estimator::idType id,
                          const double multiplier,
                          const STLCompliantArrayA<surfaceIdType>& surface_ids,
                          const STLCompliantArrayB<double>& surface_areas )
  : StandardEntityEstimator<surfaceIdType>( id,
					    multiplier,
					    surface_ids,
					    surface_areas ),
    ParticleCrossingSurfaceEventObserver()
{ /* ... */ }

// Constructor (for non-flux estimators)
template<typename<typename,typename...> class STLCompliantArray>
StandardSurfaceEstimator::StandardSurfaceEstimator(
                          const Estimator::idType id,
                          const double multiplier,
                          const STLCompliantArray<surfaceIdType>& surface_ids )
  : StandardEntityEstimator<surfaceIdType>( id, multiplier, surface_ids ),
    ParticleCrossingSurfaceEventObserver()
{ /* ... */ }
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_SURFACE_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardSurfaceEstimator_def.hpp
//---------------------------------------------------------------------------//
