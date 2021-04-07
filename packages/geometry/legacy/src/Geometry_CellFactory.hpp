//---------------------------------------------------------------------------//
//!
//! \file   Geometry_CellFactory.hpp
//! \author Alex Robinson
//! \brief  Cell factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_CELL_FACTORY_HPP
#define GEOMETRY_CELL_FACTORY_HPP

// Std Lib Includes
#include <string>
#include <map>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_Cell.hpp"
#include "Geometry_Surface.hpp"
#include "Geometry_Polygon.hpp"
#include "Geometry_IntersectionPoint.hpp"
#include "Utility_Tuple.hpp"

namespace Geometry{

/*! \brief Enumeration to specify the cell attribute(s) to calc. numerically
 */
enum NumericalCellIntegrationType{
  CELL_VOLUME,
  CELL_SURFACE_AREAS,
  CELL_VOLUME_AND_SURFACE_AREAS
};

/*! A factory class for creating smart pointers to cell objects and possibly
 * calculating the volume and surface areas.
 */
template<typename Cell, typename SurfaceMap>
class CellFactory
{
public:

  //@{
  //! Typedefs
  //! Typedef for cell pointer
  typedef typename Teuchos::RCP<Cell> CellPtr;
  //! Typedef for bounding box
  typedef Utility::Quad<
    Utility::Pair<typename Cell::ordinalType, NumericalCellIntegrationType>,
    Utility::Pair<typename Cell::scalarType,typename Cell::scalarType>,
    Utility::Pair<typename Cell::scalarType,typename Cell::scalarType>,
    Utility::Pair<typename Cell::scalarType,typename Cell::scalarType> >
  BoudingBox;
  //@}

private:

  //! Typedef for cell ordinal type
  typedef typename Cell::ordinalType cellOrdinalType;
  //! Typedef for surface ordinal type
  typedef typename Cell::surfaceOrdinalType surfaceOrdinalType;
  //! Typedef for scalar type
  typedef typename Cell::scalarType scalarType;
  //! Typedef for scalar traits
  typedef Teuchos::ScalarTraits<scalarType> ST;
  //! Typedef for cell ordinal traits
  typedef Teuchos::OrdinalTraits<cellOrdinalType> CellOT;
  //! Typedef for surface ordinal traits
  typedef Teuchos::OrdinalTraits<surfaceOrdinalType> SurfaceOT;
  //! Typedef for intersection point
  typedef IntersectionPoint<surfaceOrdinalType,scalarType> Point;
  //! Typedef for polygon
  typedef Polygon<surfaceOrdinalType,scalarType> CellPolygon;

public:

  //! Constructor
  CellFactory( const SurfaceMap &global_surface_map );

  //! Destructor
  ~CellFactory()
  { /* ... */ }

  //! Create the desired cell
  CellPtr create( const typename Cell::ordinalType id,
		  std::string &cell_definition,
		  const bool calculate_volume_and_area = false ) const;

protected:

  //! Calculate the volume and area of a polyhedral cell
  void calculatePolyhedralCellVolumeAndArea( CellPtr &cell ) const;

  //! Create the polygons bounding the cell
  static void createBoundingPolygons(
				    Teuchos::Array<CellPolygon> &cell_polygons,
				    CellPtr &cell );

  //! Calculate the volume of a polyhedral cell using bounding polygons
  static scalarType calculatePolyhedralCellVolumeFromPolygons(
				const Teuchos::Array<CellPolygon>
				&cell_polygons );

  //! Create a bounding box for a polyhedral cell from bounding polygons
  // static void createBoundingBoxFromPolygons(
  // 				BoundingBox &cell_bounding_box,
  // 				const Teuchos::Array<CellPolygon> &cell_polygons );

  //! Calculate the intersection points of planes with a plane of interest
  static void calculateIntersectionPointsOnPlane(
			    std::list<Point> &intersection_points,
			    const typename Cell::SurfaceSensePairsIterator
			    &plane_of_polygon,
			    const CellPtr &cell );

  //! Calculate the volume and area of a rotationally symmetric cell
  // void calculateRotationallySymmetricCellVolumeAndArea( CellPtr &cell );

private:

  // Stored copy of the global surface map (weak pointer)
  Teuchos::RCP<const SurfaceMap> d_global_surface_map;
};

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_CellFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_CELL_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Geometry_CellFactory.hpp
//---------------------------------------------------------------------------//


