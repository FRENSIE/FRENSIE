//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Navigator.hpp
//! \author Alex Robinson
//! \brief  The geometry model navigator base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_NAVIGATOR_HPP
#define GEOMETRY_NAVIGATOR_HPP

// FRENSIE Includes
#include "Geometry_PointLocation.hpp"
#include "Geometry_Ray.hpp"

namespace Geometry{

/*! The navigator base class
 * \details Navigators are used to do geometric queries on a model and
 * to ray trace on a model.
 */
class Navigator
{

public:
  
  //! Constructor
  Navigator()
  { /* ... */ }

  //! Destructor
  virtual ~Navigator()
  { /* ... */ }
  
  //! Enable support for multiple threads
  virtual void enableThreadSupport( const size_t num_threads ) = 0;

  //! Get the location of a cell w.r.t. a given cell
  virtual PointLocation getPointLocation(
                       const Ray& ray,
                       const ModuleTraits::InternalCellHandle cell ) const = 0;

  //! Get the surface normal at a point on the surface
  virtual void getSurfaceNormal(
                          const ModuleTraits::InternalSurfaceHandle surface_id,
                          const double position[3],
                          double normal[3] ) const = 0;

  /*! Find the cell that contains a given start ray
   *
   * A std::runtime_error (or class derived from it) must be thrown if an error
   * occurs.
   */
  virtual ModuleTraits::InternalCellHandle findCellContainingStartRay(
                                         const Ray& ray,
                                         CellSet& start_cell_cache ) const = 0;

  /*! Find the cell that contains a given ray
   *
   * A std::runtime_error (or class derived from it) must be thrown if an error
   * occurs.
   */
  virtual ModeulTraits::InternalCellHandle findCellContainingRay(
                                                    const Ray& ray ) const = 0;

  /*! Fire the ray through the geometry
   *
   * A std::runtime_error (or class derived from it) must be thrown if a ray
   * tracing error occurs.
   */
  virtual double fireRay(
                  const Ray& ray,
                  ModuleTraits::InternalSurfaceHandle& surface_hit ) const = 0;

  //! Check if an internal ray has been set
  virtual bool isInternalRaySet();

  /*! Set the internal ray with unknown starting cell
   *
   * A std::runtime_error (or class derived from it) must be thrown if
   * an error occurs.
   */
  virtual void setInternalRay( const double x_position,
                               const double y_position,
                               const double z_position,
                               const double x_direction,
                               const double y_direction,
                               const double z_direction ) = 0;

  /*! Set the internal ray with unknown starting cell
   *
   * A std::runtime_error (or class derived from it) must be thrown if
   * an error occurs.
   */
  void setInternalRay( const double position[3], const double direction[3] );

  /*! Set the internal ray with known starting cell
   *
   * A std::runtime_error (or class derived from it) must be thrown if
   * an error occurs.
   */
  virtual void setInternalRay(
                       const double x_position,
                       const double y_position,
                       const double z_position,
                       const double x_direction,
                       const double y_direction,
                       const ModuleTraits::InternalCellHandle start_cell ) = 0;

  /*! Set the internal ray with known starting cell
   *
   * A std::runtime_error (or class derived from it) must be thrown if
   * an error occurs.
   */
  void setInternalRay( const double position[3],
                       const double direction[3],
                       const ModuleTraits::InternalCellHandle start_cell );

  //! Get the internal ray position
  virtual const double* getInternalRayPosition() const = 0;

  //! Get the internal ray direction
  virtual const double* getInternalRayDirection() const = 0;

  /*! Find the cell that contains the internal ray
   *
   * A std::runtime_error (or class derived from it) must be thrown
   * if an error occurs.
   */
  virtual ModuleTraits::InternalCellHandle findCellContainingInternalRay() const = 0;

  /*! Fire the internal ray through the geometry
   *
   * A std::runtime_error (or class derived from it) must be thrown if a ray 
   * tracing error occurs.
   */
  virtual double fireInternalRay(
                  ModuleTraits::InternalSurfaceHandle& surface_hit ) const = 0;

  /*! Advance the internal ray to the cell boundary
   *
   * If a reflecting surface is hit "true" will be returned. Passing NULL
   * to this function must be allowed.
   */
  virtual bool advanceInternalRayToCellBoundary( double* surface_normal ) = 0;

  //! Advance the internal ray by a substep (less than distance to boundary)
  virtual bool advanceInternalRayBySubstep( const double step_size ) = 0;

  //! Change the internal ray direction
  virtual void changeInternalRayDirection( const double x_direction,
                                           const double y_direction,
                                           const double z_direction ) = 0;

  // Change the internal ray direction
  void changeInternalRayDirection( const double direction[3] );
};

// Set the internal ray with unknown starting cell
void Navigator::setInternalRay( const double position[3],
                                const double direction[3] )
{
  this->setInternalRay( position[0],
                        position[1],
                        position[2],
                        direction[0],
                        direction[1],
                        direction[2] );
}

// Set the internal ray with known starting cell
void Navigator::setInternalRay(
                            const double position[3],
                            const double direction[3],
                            const ModuleTraits::InternalCellHandle start_cell )
{
  this->setInternalRay( position[0],
                        position[1],
                        position[2],
                        direction[0],
                        direction[1],
                        direction[2],
                        start_cell );
}

// Change the internal ray direction
inline void Navigator::changeInternalRayDirection( const double direction[3] )
{
  this->changeInternalRayDirection( direction[0],
                                    direction[1],
                                    direction[2] );
}
  
} // end Geometry namespace

#endif // end GEOMETRY_NAVIGATOR_HPP

//---------------------------------------------------------------------------//
// end Geometry_Navigator.hpp
//---------------------------------------------------------------------------//
