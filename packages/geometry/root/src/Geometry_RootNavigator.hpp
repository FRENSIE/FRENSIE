//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootNavigator.hpp
//! \author Alex Robinson
//! \brief  The Root navigator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ROOT_NAVIGATOR_HPP
#define GEOMETRY_ROOT_NAVIGATOR_HPP

// Std Lib Includes
#include <memory>
#include <functional>

// Root Includes
#include <TGeoManager.h>

// FRENSIE Includes
#include "Geometry_Navigator.hpp"

namespace Geometry{

// Forward declare the RootModel
class RootModel;

/*! The Root ray tracer
 * \details Ray tracing can be done in two ways: With Geometry::Ray objects or
 * with internal rays, which are completely hidden from the user. The
 * ray tracing performance of internal rays will almost always be better than
 * the ray tracing performance of Geometry::Ray objects.
 */
class RootNavigator : public Navigator
{

public:

  //! Constructor
  RootNavigator(
          const std::shared_ptr<const RootModel>& root_model,
          const Navigator::AdvanceCompleteCallback& advance_complete_callback =
          Navigator::AdvanceCompleteCallback() );

  //! Destructor
  ~RootNavigator();

  //! Get the point location w.r.t. a given cell
  PointLocation getPointLocation(
                             const Length position[3],
                             const double direction[3],
                             const EntityId cell_id ) const override;

  //! Get the surface normal at a point on the surface
  void getSurfaceNormal( const EntityId surface_id,
                         const Length position[3],
                         const double direction[3],
                         double normal[3] ) const override;

  //! Find the cell that contains a given ray
  EntityId findCellContainingRay(
                                  const Length position[3],
                                  const double direction[3],
                                  CellIdSet& found_cell_cache ) const override;

  //! Find the cell that contains the ray
  EntityId findCellContainingRay(
                                    const Length position[3],
                                    const double direction[3] ) const override;

  //! Check if the internal ray is set
  bool isStateSet() const override;

  //! Initialize (or reset) an internal Root ray
  void setState( const Length x_position,
                 const Length y_position,
                 const Length z_position,
                 const double x_direction,
                 const double y_direction,
                 const double z_direction ) override;


  //! Initialize (or reset) an internal Root ray
  void setState( const Length x_position,
                 const Length y_position,
                 const Length z_position,
                 const double x_direction,
                 const double y_direction,
                 const double z_direction,
                 const EntityId current_cell ) override;

  //! Initialize (or reset) the state (base overloads)
  using Navigator::setState;

  //! Get the internal Root ray position
  const Length* getPosition() const override;

  //! Get the internal Root ray direction
  const double* getDirection() const override;

  //! Get the cell containing the internal Root ray position
  EntityId getCurrentCell() const override;

  //! Get the distance from the internal Root ray pos. to the nearest boundary in all directions
  Length getDistanceToClosestBoundary() override;

  //! Get the distance from the internal Root ray pos. to the nearest boundary
  Length fireRay( EntityId* surface_hit ) override;

  //! Change the internal ray direction (without changing its location)
  void changeDirection( const double x_direction,
                        const double y_direction,
                        const double z_direction ) override;

  //! Clone the navigator
  RootNavigator* clone( const AdvanceCompleteCallback& advance_complete_callback ) const override;

  //! Clone the navigator
  RootNavigator* clone() const override;

protected:

  //! Copy constructor
  RootNavigator( const RootNavigator& other );

  //! Advance the internal Root ray to the next boundary
  bool advanceToCellBoundaryImpl( double* surface_normal,
                                  Length& distance_traveled ) override;

  //! Advance the internal Root ray a substep
  void advanceBySubstepImpl( const Length substep_distance ) override;

private:

  // Deep copy an array
  template<typename T>
  static void deepCopy( T* copy_array, const T* orig_array );

  // Default constructor
  RootNavigator();

  // Find the node containing the point
  TGeoNode* findNodeContainingRay( const Length position[3],
                                   const double direction[3] ) const;

  // Set the internal ray set flag
  void stateSet();

  // Create internal ray
  static TGeoNavigator* createInternalRay( TGeoManager* manager );

  // Free internal ray
  void freeInternalRay();

  // The tolerance used to determine the location of points within cells
  static const double s_tol;

  // The Root model
  std::shared_ptr<const RootModel> d_root_model;

  // Keeps track of whether or not the navigator rays have been set
  bool d_internal_ray_set;

  // The geometry navigator
  TGeoNavigator* d_navigator;
};

// Deep copy an array
template<typename T>
inline void RootNavigator::deepCopy( T* copy_array, const T* orig_array )
{
  copy_array[0] = orig_array[0];
  copy_array[1] = orig_array[1];
  copy_array[2] = orig_array[2];
}

/*! The Root geometry error
 * \details This error class can be used to record geometry gaps.
 */
class RootGeometryError : public GeometryError
{

public:

  RootGeometryError( const std::string& what )
    : GeometryError( what )
  { /* ... */ }
};

} // end Geometry namespace

#endif // end GEOMETRY_ROOT_NAVIGATOR_HPP

//---------------------------------------------------------------------------//
// end Geometry_RootNavigator.hpp
//---------------------------------------------------------------------------//
