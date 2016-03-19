//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCRay.hpp
//! \author Alex Robinson
//! \brief  The DagMC ray declaration.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_RAY_HPP
#define GEOMETRY_DAGMC_RAY_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>

// Moab Includes
#include <DagMC.hpp>

// FRENSIE Includes
#include "Geometry_Ray.hpp"

namespace Geometry{

//! The DagMCRay used for efficient ray tracing
class DagMCRay
{

public:
  
  //! Constructor
  DagMCRay();

  //! Constructor
  DagMCRay( const Ray& ray, moab::EntityHandle cell_handle );

  //! Constructor
  DagMCRay( const double position[3],
            const double direction[3],
            const moab::EntityHandle cell_handle );

  // Copy constructor
  DagMCRay( const DagMCRay& ray );

  //! Destructor
  ~DagMCRay()
  { /* ... */ }
  
  //! Check if the ray is ready (basic ray data, current cell handle set)
  bool isReady() const;

  //! Set the ray (minimum data required)
  void set( const Ray& ray, const moab::EntityHandle cell_handle );

  //! Set the ray (minimum data required)
  void set( const double position[3], 
            const double direction[3],
            const moab::EntityHandle cell_handle );

  //! change the direction
  void changeDirection( const double direction[3] );

  //! change the direction
  void changeDirection( const double x_direction,
                        const double y_direction,
                        const double z_direction );

  //! Get the position
  const double* getPosition() const;

  //! Get the direction
  const double* getDirection() const;

  //! Get the current cell handle
  moab::EntityHandle getCurrentCell() const;

  //! Check if the ray knows the surface it will hit
  bool knowsIntersectionSurface() const;

  //! Set the intersection surface data
  void setIntersectionSurfaceData( const moab::EntityHandle surface_handle,
                                   const double distance );

  //! Rest the intersection surface data
  void resetIntersectionSurfaceData();

  //! Get the distance to the intersection surface
  double getDistanceToIntersectionSurface() const;

  //! Get the boundary surface 
  moab::EntityHandle getIntersectionSurface() const;

  //! Get the ray history
  const moab::DagMC::RayHistory& getHistory() const;

  //! Get the ray history
  moab::DagMC::RayHistory& getHistory();

  //! Advance the ray to the intersection surface
  void advanceToIntersectionSurface( 
                                   const moab::EntityHandle next_cell_handle );

  //! Advance the ray a substep
  void advanceSubstep( const double substep_distance );

private:

  // The basic ray
  boost::scoped_ptr<Ray> d_basic_ray;
  
  // The current cell handle
  moab::EntityHandle d_cell_handle;
  
  // The ray history
  moab::DagMC::RayHistory d_history;
  
  // The distance to the next surface (-1 for not known)
  double d_intersection_distance;
  
  // The boundary surface that will be intersected (0 for not known)
  moab::EntityHandle d_intersection_surface_handle;
};

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_RAY_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCRay.hpp
//---------------------------------------------------------------------------//
