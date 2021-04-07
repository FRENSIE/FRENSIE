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
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace Geometry{

//! The infinite medium geometry navigator
class InfiniteMediumNavigator : public Navigator
{

public:

  //! Constructor
  InfiniteMediumNavigator(
          const EntityId infinite_medium_cell_id,
          const Navigator::AdvanceCompleteCallback& advance_complete_callback =
          Navigator::AdvanceCompleteCallback() );

  //! Destructor
  ~InfiniteMediumNavigator();

  //! Get the location of a point w.r.t. a given cell
  PointLocation getPointLocation(
                                const Length position[3],
                                const double direction[3],
                                const EntityId cell ) const override;

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

  //! Find the cell that contains a given ray
  EntityId findCellContainingRay(
                                    const Length position[3],
                                    const double direction[3] ) const override;

  //! Check if an internal ray has been set
  bool isStateSet() const override;

  //! Set the internal ray with unknown starting cell
  void setState( const Length x_position,
                 const Length y_position,
                 const Length z_position,
                 const double x_direction,
                 const double y_direction,
                 const double z_direction ) override;

  //! Set the internal ray with known starting cell
  void setState( const Length x_position,
                 const Length y_position,
                 const Length z_position,
                 const double x_direction,
                 const double y_direction,
                 const double z_direction,
                 const EntityId start_cell ) override;

  //! Set the internal ray state (base class overloads)
  using Navigator::setState;

  //! Get the internal ray position
  const Length* getPosition() const override;

  //! Get the internal ray direction
  const double* getDirection() const override;

  //! Get the cell that contains the internal ray
  EntityId getCurrentCell() const override;

  //! Get the distance from the internal ray pos. to the nearest boundary in all directions
  Length getDistanceToClosestBoundary() override;

  //! Fire the internal ray through the geometry
  Length fireRay( EntityId* surface_hit ) override;

  //! Change the internal ray direction
  void changeDirection( const double x_direction,
                        const double y_direction,
                        const double z_direction ) override;

  //! Clone the navigator
  InfiniteMediumNavigator* clone( const AdvanceCompleteCallback& advance_complete_callback ) const override;

  //! Clone the navigator
  InfiniteMediumNavigator* clone() const override;

protected:

  //! Copy constructor
  InfiniteMediumNavigator( const InfiniteMediumNavigator& other );

  //! Advance the internal ray to the cell boundary
  bool advanceToCellBoundaryImpl( double* surface_normal,
                                  Length& distance_traveled ) override;

  //! Advance the internal ray by a substep (less than distance to boundary)
  void advanceBySubstepImpl( const Length step_size ) override;

private:

  // Default constructor
  InfiniteMediumNavigator();

  // The infinite medium cell id
  EntityId d_cell;

  // The position
  Length* d_position;

  // The direction
  double* d_direction;
};

} // end Geometry namespace

#endif // end GEOMETRY_INFINITE_MEDIUM_NAVIGATOR_HPP

//---------------------------------------------------------------------------//
// end Geometry_InfiniteMediumNavigator.hpp
//---------------------------------------------------------------------------//
