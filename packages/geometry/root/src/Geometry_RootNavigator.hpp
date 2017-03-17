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
#include "Geometry_ModuleTraits.hpp"

namespace Geometry{

/*! The Root ray tracer
 * \details Ray tracing can be done in two ways: With Geometry::Ray objects or
 * with internal rays, which are completely hidden from the user. The
 * ray tracing performance of internal rays will almost always be better than 
 * the ray tracing performance of Geometry::Ray objects.
 */
class RootNavigator : public Navigator
{

public:

  //! The cell id to TGeoVolume* conversion function
  typedef std::function<TGeoVolume*(const ModuleTraits::InternalCellHandle&)>
  CellIdToTGeoVolumeFunction;

  //! Constructor
  RootNavigator( TGeoManager* manager,
                 const CellIdToTGeoVolumeFunction& get_volume_ptr );

  //! Destructor
  ~RootNavigator();

  //! Get the point location w.r.t. a given cell
  PointLocation getPointLocation(
               const double position[3],
               const double direction[3],
               const ModuleTraits::InternalCellHandle cell_id ) const override;

  //! Get the surface normal at a point on the surface
  void getSurfaceNormal( const ModuleTraits::InternalSurfaceHandle surface_id,
                         const double position[3],
                         const double direction[3],
                         double normal[3] ) const override;

  //! Find the cell that contains a given ray
  ModuleTraits::InternalCellHandle findCellContainingRay(
                                  const double position[3],
                                  const double direction[3],
                                  CellIdSet& found_cell_cache ) const override;

  //! Find the cell that contains the ray
  ModuleTraits::InternalCellHandle findCellContainingRay(
                                    const double position[3],
                                    const double direction[3] ) const override;

  //! Check if the internal ray is set
  bool isInternalRaySet() const override;

  //! Initialize (or reset) an internal Root ray
  void setInternalRay( const double x_position,
                       const double y_position,
                       const double z_position,
                       const double x_direction,
                       const double y_direction,
                       const double z_direction ) override;
                      
                       
  //! Initialize (or reset) an internal Root ray
  void setInternalRay(
                const double x_position,
                const double y_position,
                const double z_position,
                const double x_direction,
                const double y_direction,
                const double z_direction,
                const ModuleTraits::InternalCellHandle current_cell ) override;

  //! Get the internal Root ray position
  const double* getInternalRayPosition() const override;

  //! Get the internal Root ray direction
  const double* getInternalRayDirection() const override;

  //! Get the cell containing the internal Root ray position
  ModuleTraits::InternalCellHandle getCellContainingInternalRay() const override;

  //! Get the distance from the internal Root ray pos. to the nearest boundary
  double fireInternalRay( ModuleTraits::InternalSurfaceHandle* surface_hit ) override;

  //! Advance the internal Root ray to the next boundary
  bool advanceInternalRayToCellBoundary( double* surface_normal ) override;

  //! Advance the internal Root ray a substep
  void advanceInternalRayBySubstep( const double substep_distance ) override;

  //! Change the internal ray direction (without changing its location)
  void changeInternalRayDirection( const double x_direction,
                                   const double y_direction,
                                   const double z_direction ) override;

private:

  // Deep copy an array
  static void deepCopy( double* copy_array, const double* orig_array );

  // Find the node containing the point
  TGeoNode* findNodeContainingRay( const double position[3],
                                   const double direction[3] ) const;

  // Set the internal ray set flag
  void internalRaySet();

  // The tolerance used to determine the location of points within cells
  static const double s_tol;

  // The geometry manager
  TGeoManager* d_manager;

  // The function used to convert cell id to TGeoVolume*
  CellIdToTGeoVolumeFunction d_get_volume_ptr;

  // Keeps track of whether or not the navigator rays have been set
  bool d_internal_ray_set;

  // The geometry navigators
  TGeoNavigator* d_navigator;
};

// Deep copy an array
inline void RootNavigator::deepCopy( double* copy_array,
                                     const double* orig_array )
{
  copy_array[0] = orig_array[0];
  copy_array[1] = orig_array[1];
  copy_array[2] = orig_array[2];
}
  
} // end Geometry namespace

#endif // end GEOMETRY_ROOT_NAVIGATOR_HPP

//---------------------------------------------------------------------------//
// end Geometry_RootNavigator.hpp
//---------------------------------------------------------------------------//
