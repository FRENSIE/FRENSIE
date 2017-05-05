//---------------------------------------------------------------------------//
//!
//! \file   Geometry_InfiniteMediumNavigator.hpp
//! \author Alex Robinson
//! \brief  The infinite medium model navigator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_INFINITE_MEDIUM_NAVIGATOR_HPP
#define GEOMETRY_INFINITE_MEDIUM_NAVIGATOR_HPP

// FRENSIE Includes
#include "Geometry_Navigator.hpp"

namespace Geometry{

//! The infinite medium geometry navigator
class InfiniteMediumNavigator : public Navigator
{

public:

  //! Constructor
  InfiniteMediumNavigator(
              const ModuleTraits::InternalCellHandle infinite_medium_cell_id );

  //! Destructor
  ~InfiniteMediumNavigator();

  //! Get the location of a point w.r.t. a given cell
  PointLocation getPointLocation(
                  const double position[3],
                  const double direction[3],
                  const ModuleTraits::InternalCellHandle cell ) const override;
  
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

  //! Find the cell that contains a given ray
  ModuleTraits::InternalCellHandle findCellContainingRay(
                                    const double position[3],
                                    const double direction[3] ) const override;
  
  //! Check if an internal ray has been set
  bool isInternalRaySet() const override;

  //! Set the internal ray with unknown starting cell
  void setInternalRay( const double x_position,
                       const double y_position,
                       const double z_position,
                       const double x_direction,
                       const double y_direction,
                       const double z_direction ) override;

  //! Set the internal ray with known starting cell
  void setInternalRay(
                  const double x_position,
                  const double y_position,
                  const double z_position,
                  const double x_direction,
                  const double y_direction,
                  const double z_direction,
                  const ModuleTraits::InternalCellHandle start_cell ) override;

  //! Get the internal ray position
  const double* getInternalRayPosition() const override;

  //! Get the internal ray direction
  const double* getInternalRayDirection() const override;

  //! Get the cell that contains the internal ray
  ModuleTraits::InternalCellHandle getCellContainingInternalRay() const override;

  //! Fire the internal ray through the geometry
  double fireInternalRay(
                   ModuleTraits::InternalSurfaceHandle* surface_hit ) override;

  //! Advance the internal ray to the cell boundary
  bool advanceInternalRayToCellBoundary( double* surface_normal ) override;

  //! Advance the internal ray by a substep (less than distance to boundary)
  void advanceInternalRayBySubstep( const double step_size ) override;

  //! Change the internal ray direction
  void changeInternalRayDirection( const double x_direction,
                                   const double y_direction,
                                   const double z_direction ) override;

  //! Clone the navigator
  InfiniteMediumNavigator* clone() const override;

private:

  // The infinite medium cell id
  ModuleTraits::InternalCellHandle d_cell;
  
  // The position
  double* d_position;

  // The direction
  double* d_direction;
};
  
} // end Geometry namespace

#endif // end GEOMETRY_INFINITE_MEDIUM_NAVIGATOR_HPP

//---------------------------------------------------------------------------//
// end Geometry_InfiniteMediumNavigator.hpp
//---------------------------------------------------------------------------//
