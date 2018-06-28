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
  // Typedef for the base estimator type
  typedef StandardEntityEstimator<Geometry::Model::InternalSurfaceHandle>
  BaseEstimatorType;

public:

  //! Typedef for the surface id type
  typedef Geometry::Model::InternalSurfaceHandle SurfaceIdType;

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleCrossingSurfaceEventObserver::EventTag>
  EventTags;

  //! Constructor (for flux estimators)
  StandardSurfaceEstimator( const Estimator::idType id,
                            const double multiplier,
                            const std::vector<SurfaceIdType>& surface_ids,
                            const std::vector<double>& surface_areas );

  //! Constructor (for non-flux estimators)
  StandardSurfaceEstimator( const Estimator::idType id,
                            const double multiplier,
                            const std::vector<SurfaceIdType>& surface_ids );

  //! Destructor
  virtual ~StandardSurfaceEstimator()
  { /* ... */ }

protected:

  //! Default constructor
  StandardSurfaceEstimator();

  //! Assign the particle type to the estimator
  void assignParticleType( const ParticleType particle_type ) final override;

private:

  // Serialize the entity estimator
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

// Serialize the entity estimator
template<typename Archive>
void StandardSurfaceEstimator::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseEstimatorType );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleCrossingSurfaceEventObserver );
}

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::StandardSurfaceEstimator, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::StandardSurfaceEstimator );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::StandardSurfaceEstimator );

#endif // end MONTE_CARLO_STANDARD_SURFACE_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardSurfaceEstimator.hpp
//---------------------------------------------------------------------------//
