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
#include <functional>
#include <sstream>

#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/cgs/volume.hpp>

// FRENSIE Includes
#include "Geometry_PointLocation.hpp"
#include "Geometry_Ray.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_Set.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Geometry{

/*! The navigator base class
 * \details Navigators are used to do geometric queries on a model and
 * to ray trace on a model.
 */
class Navigator
{

public:

  //! The entity (cell or surface) id type
  typedef uint64_t EntityId;

  //! The length unit
  typedef boost::units::cgs::length LengthUnit;

  //! The length quantity
  typedef boost::units::quantity<LengthUnit> Length;

  //! The ray type used by the navigator
  typedef UnitAwareRay<LengthUnit> Ray;

  //! The cell id set
  typedef std::set<EntityId> CellIdSet;

  //! The advance callback
  typedef std::function<void(const Length)> AdvanceCompleteCallback;

  //! Constructor
  Navigator( const AdvanceCompleteCallback& advance_complete_callback =
             AdvanceCompleteCallback() );

  //! Destructor
  virtual ~Navigator()
  { /* ... */ }

  /*! Get the location of a point w.r.t. a given cell
   *
   * The direction can be used to help determine if the point is inside or
   * outside of the cell when close to a boundary.
   */
  virtual PointLocation getPointLocation(
                                     const Length position[3],
                                     const double direction[3],
                                     const EntityId cell ) const = 0;

  /*! Get the location of a cell w.r.t. a given cell
   *
   * The direction can be used to help determine if the point is inside or
   * outside of the cell when close to a boundary.
   */
  PointLocation getPointLocation( const Ray& ray,
                                  const EntityId cell ) const;

  /*! Get the surface normal at a point on the surface
   *
   * The dot product of the direction and normal must be positive defined.
   */
  virtual void getSurfaceNormal( const EntityId surface_id,
                                 const Length position[3],
                                 const double direction[3],
                                 double normal[3] ) const = 0;

  /*! Get the surface normal at a point on the surface
   *
   * The dot product of the direction and normal will be positive defined.
   */
  void getSurfaceNormal( const EntityId surface_id,
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
  virtual EntityId findCellContainingRay(
                                       const Length position[3],
                                       const double direction[3],
                                       CellIdSet& found_cell_cache ) const = 0;

  /*! Find the cell that contains a given ray
   *
   * The direction can be used to help determine the cell that contains
   * the point when close to a boundary. The cells in the found cell cache
   * will be checked first. If a new cell is found it will be added to the
   * cache. A std::runtime_error (or class derived from it) will be thrown if
   * an error occurs.
   */
  EntityId findCellContainingRay(
                                           const Ray& ray,
                                           CellIdSet& found_cell_cache ) const;

  /*! Find the cell that contains a given ray
   *
   * The direction can be used to help determine the cell that contains
   * the point when close to a boundary. A std::runtime_error (or class
   * derived from it) must be thrown if an error occurs.
   */
  virtual EntityId findCellContainingRay(
                                         const Length position[3],
                                         const double direction[3] ) const = 0;

  /*! Find the cell that contains a given ray
   *
   * The direction can be used to help determine the cell that contains
   * the point when close to a boundary. A std::runtime_error (or class
   * derived from it) must be thrown if an error occurs.
   * A std::runtime_error (or class derived from it) will be thrown if an error
   * occurs.
   */
  EntityId findCellContainingRay( const Ray& ray ) const;

  //! Check if an internal ray has been set
  virtual bool isStateSet() const = 0;

  /*! Set the internal ray with unknown starting cell
   *
   * A std::runtime_error (or class derived from it) must be thrown if
   * an error occurs.
   */
  virtual void setState( const Length x_position,
                         const Length y_position,
                         const Length z_position,
                         const double x_direction,
                         const double y_direction,
                         const double z_direction ) = 0;

  /*! Set the internal ray with unknown starting cell
   *
   * A std::runtime_error (or class derived from it) must be thrown if
   * an error occurs.
   */
  void setState( const Length position[3], const double direction[3] );

  /*! Set the internal ray with unknown starting cell
   *
   * A std::runtime_error (or class derived from it) must be thrown if
   * an error occurs.
   */
  void setState( const Ray& ray );

  /*! Set the internal ray with known starting cell
   *
   * Failure to provide the correct starting cell will result in undefined
   * behavior. A std::runtime_error (or class derived from it) must be thrown
   * if an error occurs.
   */
  virtual void setState( const Length x_position,
                         const Length y_position,
                         const Length z_position,
                         const double x_direction,
                         const double y_direction,
                         const double z_direction,
                         const EntityId start_cell ) = 0;

  /*! Set the internal ray with known starting cell
   *
   * Failure to provide the correct starting cell will result in undefined
   * behavior. A std::runtime_error (or class derived from it) must be thrown
   * if an error occurs.
   */
  void setState( const Length position[3],
                 const double direction[3],
                 const EntityId start_cell );

  /*! Set the internal ray with known starting cell
   *
   * Failure to provide the correct starting cell will result in undefined
   * behavior. A std::runtime_error (or class derived from it) must be thrown
   * if an error occurs.
   */
  void setState( const Ray& ray,
                 const EntityId start_cell );

  //! Get the internal ray position
  virtual const Length* getPosition() const = 0;

  //! Get the internal ray direction
  virtual const double* getDirection() const = 0;

  /*! Get the cell that contains the internal ray
   *
   * A std::runtime_error (or class derived from it) must be thrown
   * if an error occurs.
   */
  virtual EntityId getCurrentCell() const = 0;

  /*! Get the distance from the internal ray pos. to the nearest boundary in all directions
   *
   * A std::runtime_error (or class derived from it) must be thrown if a ray
   * tracing error occurs.
   */
  virtual Length getDistanceToClosestBoundary() = 0;

  /*! Fire the internal ray through the geometry
   *
   * A std::runtime_error (or class derived from it) must be thrown if a ray
   * tracing error occurs.
   */
  virtual Length fireRay( EntityId* surface_hit ) = 0;

  /*! Fire the internal ray through the geometry
   *
   * A std::runtime_error (or class derived from it) must be thrown if a ray
   * tracing error occurs.
   */
  Length fireRay( EntityId& surface_hit );

  /*! Fire the internal ray through the geometry
   *
   * A std::runtime_error (or class derived from it) must be thrown if a ray
   * tracing error occurs.
   */
  Length fireRay();

  /*! Advance the internal ray to the cell boundary
   *
   * If a reflecting surface is hit "true" will be returned. Passing NULL
   * to this function must be allowed.
   */
  bool advanceToCellBoundary( double* surface_normal );

  /*! Advance the internal ray to the cell boundary
   *
   * If a reflecting surface is hit "true" will be returned. Passing NULL
   * to this function must be allowed.
   */
  bool advanceToCellBoundary();

  //! Advance the internal ray by a substep (less than distance to boundary)
  void advanceBySubstep( const Length step_size );

  //! Change the internal ray direction
  virtual void changeDirection( const double x_direction,
                                const double y_direction,
                                const double z_direction ) = 0;

  //! Change the internal ray direction
  void changeDirection( const double direction[3] );

  //! The invalid cell id
  static EntityId invalidCellId();

  //! The invalid surface id
  static EntityId invalidSurfaceId();

  /*! Clone the navigator
   *
   * The returned pointer must be heap allocated.
   */
  virtual Navigator* clone( const AdvanceCompleteCallback& advance_complete_callback ) const = 0;

  /*! Clone the navigator
   *
   * The returned pointer must be heap allocated.
   */
  virtual Navigator* clone() const = 0;

protected:

  //! Copy constructor
  Navigator( const Navigator& other );

  // Convert an array to a string
  template<typename T>
  static std::string arrayToString( const T* data );

  //! Advance the internal ray to the cell boundary implementation
  virtual bool advanceToCellBoundaryImpl( double* surface_normal,
                                          Length& distance_traveled ) = 0;

  //! Advance the internal ray by a substep (less than distance to boundary) implementation
  virtual void advanceBySubstepImpl( const Length step_size ) = 0;

private:

  // The onAdvanceComplete method
  AdvanceCompleteCallback d_on_advance_complete;
};

// Get the location of a cell w.r.t. a given cell
inline PointLocation Navigator::getPointLocation(
                                          const Ray& ray,
                                          const EntityId cell ) const
{
  return this->getPointLocation( ray.getPosition(), ray.getDirection(), cell );
}

// Get the surface normal at a point on the surface
inline void Navigator::getSurfaceNormal(
                                        const EntityId surface_id,
                                        const Ray& ray,
                                        double normal[3] ) const
{
  this->getSurfaceNormal( surface_id,
                          ray.getPosition(),
                          ray.getDirection(),
                          normal );
}

/* SWIG has limitations with the auto function return type. To avoid a syntax
 * error the following functions will not be defined for SWIG.
 */
#if !defined SWIG
// Find the cell that contains a given ray
inline auto Navigator::findCellContainingRay(
                      const Ray& ray,
                      CellIdSet& found_cell_cache ) const -> EntityId
{
  return this->findCellContainingRay( ray.getPosition(),
                                      ray.getDirection(),
                                      found_cell_cache );
}

// Find the cell that contains a given ray
inline auto Navigator::findCellContainingRay( const Ray& ray ) const -> EntityId
{
  return this->findCellContainingRay( ray.getPosition(), ray.getDirection() );
}
#endif // end !defined SWIG

// Set the internal ray with unknown starting cell
inline void Navigator::setState( const Length position[3],
                                 const double direction[3] )
{
  this->setState( position[0], position[1], position[2],
                  direction[0], direction[1], direction[2] );
}

// Set the internal ray with unknown starting cell
inline void Navigator::setState( const Ray& ray )
{
  this->setState( ray.getPosition(), ray.getDirection() );
}

// Set the internal ray with known starting cell
inline void Navigator::setState( const Length position[3],
                                 const double direction[3],
                                 const EntityId start_cell )
{
  this->setState( position[0], position[1], position[2],
                  direction[0], direction[1], direction[2],
                  start_cell );
}

// Set the internal ray with known starting cell
inline void Navigator::setState( const Ray& ray,
                                 const EntityId start_cell )
{
  this->setState( ray.getPosition(), ray.getDirection() );
}

// Fire the internal ray through the geometry
inline auto Navigator::fireRay( EntityId& surface_hit ) -> Length
{
  return this->fireRay( &surface_hit );
}

// Fire the internal ray through the geometry
inline auto Navigator::fireRay() -> Length
{
  return this->fireRay( NULL );
}

// Advance the internal ray to the cell boundary
inline bool Navigator::advanceToCellBoundary( double* surface_normal )
{
  Length distance_traveled;
  const bool reflection = this->advanceToCellBoundaryImpl( surface_normal,
                                                           distance_traveled );

  if( d_on_advance_complete )
    d_on_advance_complete( distance_traveled );

  return reflection;
}

// Advance the internal ray to the cell boundary
inline bool Navigator::advanceToCellBoundary()
{
  return this->advanceToCellBoundary( NULL );
}

// Advance the internal ray by a substep (less than distance to boundary)
inline void Navigator::advanceBySubstep( const Length step_size )
{
  this->advanceBySubstepImpl( step_size );

  if( d_on_advance_complete )
    d_on_advance_complete( step_size );
}

// Change the internal ray direction
inline void Navigator::changeDirection( const double direction[3] )
{
  this->changeDirection( direction[0], direction[1], direction[2] );
}

// Convert an array to a string
template<typename T>
inline std::string Navigator::arrayToString( const T* data )
{
  return Utility::toString( Utility::ArrayView<const T>( data, data+3 ) );
}

/*! The geometry error
 * \details This error can be used to record geometry gaps/tacking errors
 */
class GeometryError : public std::runtime_error
{

public:

  GeometryError( const std::string& what )
    : std::runtime_error( what )
  { /* ... */ }
};

} // end Geometry namespace

#endif // end GEOMETRY_NAVIGATOR_HPP

//---------------------------------------------------------------------------//
// end Geometry_Navigator.hpp
//---------------------------------------------------------------------------//
