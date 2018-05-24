//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardSurfaceEstimator.hpp
//! \author Alex Robinson
//! \brief  Standard surface estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_SURFACE_ESTIMATOR_HPP
#define MONTE_CARLO_STANDARD_SURFACE_ESTIMATOR_HPP

// Boost Includes
#include <boost/mpl/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventObserver.hpp"
#include "Geometry_Model.hpp"

namespace MonteCarlo{

//! The standard surface estimator base class
class StandardSurfaceEstimator : public StandardEntityEstimator<Geometry::Model::InternalSurfaceHandle>,
				 public ParticleCrossingSurfaceEventObserver
{

private:

  // Typedef for the base estimator type
  typedef StandardEntityEstimator<Geometry::Model::InternalSurfaceHandle>
  BaseEstimatorType;

public:

  //! Typedef for the surface id type
  typedef Geometry::Model::InternalSurfaceHandle surfaceIdType;

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleCrossingSurfaceEventObserver::EventTag>
  EventTags;

  //! Constructor (for flux estimators)
  template<template<typename,typename...> class STLCompliantArrayA,
           template<typename,typename...> class STLCompliantArrayB>
  StandardSurfaceEstimator(
                          const Estimator::idType id,
                          const double multiplier,
			  const STLCompliantArrayA<surfaceIdType>& surface_ids,
                          const STLCompliantArrayB<double>& surface_areas );

  //! Constructor (for non-flux estimators)
  template<typename<typename,typename...> class STLCompliantArray>
  StandardSurfaceEstimator(
                         const Estimator::idType id,
                         const double multiplier,
			 const STLCompliantArray<surfaceIdType>& surface_ids );

  //! Destructor
  virtual ~StandardSurfaceEstimator()
  { /* ... */ }

protected:

  //! Assign the particle type to the estimator
  virtual void assignParticleType( const ParticleType particle_type ) override;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardSurfaceEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_SURFACE_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardSurfaceEstimator.hpp
//---------------------------------------------------------------------------//
