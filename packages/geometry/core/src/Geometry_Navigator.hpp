//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Navigator.hpp
//! \author Alex Robinson
//! \brief  The geometry model navigator base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_NAVIGATOR_HPP
#define GEOMETRY_NAVIGATOR_HPP

// Std Lib Includes
#include <set>
#include <sstream>

// FRENSIE Includes
#include "Geometry_PointLocation.hpp"
#include "Geometry_Ray.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Geometry{

/*! The navigator base class
 * \details Navigators are used to do geometric queries on a model and
 * to ray trace on a model.
 */
class Navigator
{

public:

  //! The cell id set
  typedef std::set<ModuleTraits::InternalCellHandle> CellIdSet;
  
  //! Constructor
  Navigator()
  { /* ... */ }

  //! Destructor
  virtual ~Navigator()
  { /* ... */ }

  /*! Get the location of a point w.r.t. a given cell
   *
   * The direction can be used to help determine if the point is inside or
   * outside of the cell when close to a boundary.
   */
  virtual PointLocation getPointLocation(
                       const double position[3],
                       const double direction[3],
                       const ModuleTraits::InternalCellHandle cell ) const = 0;
  
  /*! Get the location of a cell w.r.t. a given cell
   *
   * The direction can be used to help determine if the point is inside or
   * outside of the cell when close to a boundary.
   */
  PointLocation getPointLocation(
                           const Ray& ray,
                           const ModuleTraits::InternalCellHandle cell ) const;

  /*! Get the surface normal at a point on the surface
   *
   * The dot product of the direction and normal must be positive defined.
   */
  virtual void getSurfaceNormal(
                          const ModuleTraits::InternalSurfaceHandle surface_id,
                          const double position[3],
                          const double direction[3],
                          double normal[3] ) const = 0;

  /*! Get the surface normal at a point on the surface
   *
   * The dot product of the direction and normal will be positive defined.
   */
  void getSurfaceNormal( const ModuleTraits::InternalSurfaceHandle surface_id,
                         const Ray& ray,
                         double normal[3] ) const;

  /*! Find the cell that contains a given ray
   *
   * The direction can be used to help determine the cell that contains
   * the point when close to a boundary. The cells in the found cell cache
   * will be checked first. If a new cell is found it will be added to the
   * cache. A std::runtime_error (or class derived from it) will be thrown if 
   * an error occurs.
   */
  ModuleTraits::InternalCellHandle findCellContainingRay(
                                           const double position[3],
                                           const double direction[3],
                                           CellIdSet& found_cell_cache ) const;

  /*! Find the cell that contains a given ray
   *
   * The direction can be used to help determine the cell that contains
   * the point when close to a boundary. The cells in the found cell cache
   * will be checked first. If a new cell is found it will be added to the
   * cache. A std::runtime_error (or class derived from it) will be thrown if 
   * an error occurs.
   */
  ModuleTraits::InternalCellHandle findCellContainingRay(
                                           const Ray& ray,
                                           CellIdSet& found_cell_cache ) const;

  /*! Find the cell that contains a given ray
   *
   * The direction can be used to help determine the cell that contains
   * the point when close to a boundary. A std::runtime_error (or class 
   * derived from it) must be thrown if an error occurs.
   */
  virtual ModuleTraits::InternalCellHandle findCellContainingRay(
                                         const double position[3],
                                         const double direction[3] ) const = 0;
  
  /*! Find the cell that contains a given ray
   *
   * The direction can be used to help determine the cell that contains
   * the point when close to a boundary. A std::runtime_error (or class 
   * derived from it) must be thrown if an error occurs.
   * A std::runtime_error (or class derived from it) will be thrown if an error
   * occurs.
   */
  ModuleTraits::InternalCellHandle findCellContainingRay(
                                                        const Ray& ray ) const;

  //! Check if an internal ray has been set
  virtual bool isInternalRaySet() const = 0;

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

  /*! Set the internal ray with unknown starting cell
   *
   * A std::runtime_error (or class derived from it) must be thrown if
   * an error occurs.
   */
  void setInternalRay( const Ray& ray );

  /*! Set the internal ray with known starting cell
   *
   * Failure to provide the correct starting cell will result in undefined 
   * behavior. A std::runtime_error (or class derived from it) must be thrown
   * if an error occurs.
   */
  virtual void setInternalRay(
                       const double x_position,
                       const double y_position,
                       const double z_position,
                       const double x_direction,
                       const double y_direction,
                       const double z_direction,
                       const ModuleTraits::InternalCellHandle start_cell ) = 0;

  /*! Set the internal ray with known starting cell
   *
   * Failure to provide the correct starting cell will result in undefined 
   * behavior. A std::runtime_error (or class derived from it) must be thrown
   * if an error occurs.
   */
  void setInternalRay( const double position[3],
                       const double direction[3],
                       const ModuleTraits::InternalCellHandle start_cell );

  /*! Set the internal ray with known starting cell
   *
   * Failure to provide the correct starting cell will result in undefined 
   * behavior. A std::runtime_error (or class derived from it) must be thrown
   * if an error occurs.
   */
  void setInternalRay( const Ray& ray,
                       const ModuleTraits::InternalCellHandle start_cell );

  //! Get the internal ray position
  virtual const double* getInternalRayPosition() const = 0;

  //! Get the internal ray direction
  virtual const double* getInternalRayDirection() const = 0;

  /*! Get the cell that contains the internal ray
   *
   * A std::runtime_error (or class derived from it) must be thrown
   * if an error occurs.
   */
  virtual ModuleTraits::InternalCellHandle getCellContainingInternalRay() const = 0;

  /*! Fire the internal ray through the geometry
   *
   * A std::runtime_error (or class derived from it) must be thrown if a ray 
   * tracing error occurs.
   */
  virtual double fireInternalRay(
                        ModuleTraits::InternalSurfaceHandle* surface_hit ) = 0;

  /*! Fire the internal ray through the geometry
   *
   * A std::runtime_error (or class derived from it) must be thrown if a ray 
   * tracing error occurs.
   */
  double fireInternalRay();

  /*! Advance the internal ray to the cell boundary
   *
   * If a reflecting surface is hit "true" will be returned. Passing NULL
   * to this function must be allowed.
   */
  virtual bool advanceInternalRayToCellBoundary( double* surface_normal ) = 0;

  /*! Advance the internal ray to the cell boundary
   *
   * If a reflecting surface is hit "true" will be returned. Passing NULL
   * to this function must be allowed.
   */
  bool advanceInternalRayToCellBoundary();

  //! Advance the internal ray by a substep (less than distance to boundary)
  virtual void advanceInternalRayBySubstep( const double step_size ) = 0;

  //! Change the internal ray direction
  virtual void changeInternalRayDirection( const double x_direction,
                                           const double y_direction,
                                           const double z_direction ) = 0;

  // Change the internal ray direction
  void changeInternalRayDirection( const double direction[3] );

protected:

  // Convert an array to a string
  static std::string arrayToString( const double data[3] );
};

// Get the location of a cell w.r.t. a given cell
inline PointLocation Navigator::getPointLocation(
                            const Ray& ray,
                            const ModuleTraits::InternalCellHandle cell ) const
{
  return this->getPointLocation( ray.getPosition(), ray.getDirection(), cell );
}

// Get the surface normal at a point on the surface
inline void Navigator::getSurfaceNormal(
                          const ModuleTraits::InternalSurfaceHandle surface_id,
                          const Ray& ray,
                          double normal[3] ) const
{
  this->getSurfaceNormal( surface_id,
                          ray.getPosition(),
                          ray.getDirection(),
                          normal );
}

// Find the cell that contains a given ray
inline ModuleTraits::InternalCellHandle Navigator::findCellContainingRay(
                                            const double position[3],
                                            const double direction[3],
                                            CellIdSet& found_cell_cache ) const
{
  // Test the cells in the cache first
  CellIdSet::const_iterator cell_cache_it, cell_cache_end;
  cell_cache_it = found_cell_cache.begin();
  cell_cache_end = found_cell_cache.end();

  while( cell_cache_it != cell_cache_end )
  {
    PointLocation test_point_location =
      this->getPointLocation( position, direction, *cell_cache_it );

    if( test_point_location == POINT_INSIDE_CELL )
      return *cell_cache_it;

    ++cell_cache_it;
  }

  // Check all other cells
  ModuleTraits::InternalCellHandle found_cell =
    this->findCellContainingRay( position, direction );

  // Add the new cell to the cache
  found_cell_cache.insert( found_cell );

  return found_cell;
}

// Find the cell that contains a given ray
inline ModuleTraits::InternalCellHandle Navigator::findCellContainingRay(
                                            const Ray& ray,
                                            CellIdSet& found_cell_cache ) const
{
  return this->findCellContainingRay( ray.getPosition(),
                                      ray.getDirection(),
                                      found_cell_cache );
}

// Find the cell that contains a given ray
inline ModuleTraits::InternalCellHandle Navigator::findCellContainingRay(
                                                         const Ray& ray ) const
{
  return this->findCellContainingRay( ray.getPosition(), ray.getDirection() );
}

// Set the internal ray with unknown starting cell
inline void Navigator::setInternalRay( const double position[3],
                                       const double direction[3] )
{
  this->setInternalRay( position[0],
                        position[1],
                        position[2],
                        direction[0],
                        direction[1],
                        direction[2] );
}

// Set the internal ray with unknown starting cell
inline void Navigator::setInternalRay( const Ray& ray )
{
  this->setInternalRay( ray.getPosition(), ray.getDirection() );
}

// Set the internal ray with known starting cell
inline void Navigator::setInternalRay(
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

// Set the internal ray with known starting cell
inline void Navigator::setInternalRay(
                            const Ray& ray,
                            const ModuleTraits::InternalCellHandle start_cell )
{
  this->setInternalRay( ray.getPosition(), ray.getDirection() );
}

// Fire the internal ray through the geometry
inline double Navigator::fireInternalRay()
{
  return this->fireInternalRay( NULL );
}

// Advance the internal ray to the cell boundary
inline bool Navigator::advanceInternalRayToCellBoundary()
{
  return this->advanceInternalRayToCellBoundary( NULL );
}

// Change the internal ray direction
inline void Navigator::changeInternalRayDirection( const double direction[3] )
{
  this->changeInternalRayDirection( direction[0],
                                    direction[1],
                                    direction[2] );
}

// Convert an array to a string
inline std::string Navigator::arrayToString( const double data[3] )
{
  std::ostringstream oss;

  oss << "{" << data[0] << "," << data[1] << "," << data[2] << "}";

  return oss.str();
}
  
} // end Geometry namespace

#endif // end GEOMETRY_NAVIGATOR_HPP

//---------------------------------------------------------------------------//
// end Geometry_Navigator.hpp
//---------------------------------------------------------------------------//
