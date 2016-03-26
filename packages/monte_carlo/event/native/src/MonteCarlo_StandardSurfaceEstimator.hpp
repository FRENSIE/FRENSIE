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
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

//! The standard surface estimator base class
class StandardSurfaceEstimator : public StandardEntityEstimator<Geometry::ModuleTraits::InternalSurfaceHandle>,
				 public ParticleCrossingSurfaceEventObserver
{

public:

  //! Typedef for the surface id type
  typedef Geometry::ModuleTraits::InternalSurfaceHandle surfaceIdType;

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleCrossingSurfaceEventObserver::EventTag>
  EventTags;

  //! Constructor (for flux estimators)
  StandardSurfaceEstimator( const Estimator::idType id,
			    const double multiplier,
			    const Teuchos::Array<surfaceIdType>& surface_ids,
			    const Teuchos::Array<double>& surface_areas );

  //! Constructor (for non-flux estimators)
  StandardSurfaceEstimator( const Estimator::idType id,
			    const double multiplier,
			    const Teuchos::Array<surfaceIdType>& surface_ids );

  //! Destructor
  virtual ~StandardSurfaceEstimator()
  { /* ... */ }

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const Teuchos::Array<ParticleType>& particle_types );

  //! Export the estimator data
  void exportData( const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
		   const bool process_data ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_SURFACE_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardSurfaceEstimator.hpp
//---------------------------------------------------------------------------//
