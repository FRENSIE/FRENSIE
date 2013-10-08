//---------------------------------------------------------------------------//
//!
//! \file   CellFactory.hpp
//! \author Alex Robinson
//! \brief  Cell factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CELL_FACTORY_HPP
#define CELL_FACTORY_HPP

// Std Lib Includes
#include <string>
#include <map>

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "Cell.hpp"
#include "Surface.hpp"
#include "Polygon.hpp"
#include "Tuple.hpp"

namespace FACEMC{

/*! \brief Eighth space enumeration
 * 
 * Assigning the booleans in this order assures that the octants
 * are iterated through in counter-clockwise order w.r.t. the x-y plane.
 */
enum Octant{
  START_OCTANT = 0,
  POS_POS_POS_OCTANT = START_OCTANT,
  POS_NEG_POS_OCTANT,
  POS_NEG_NEG_OCTANT,
  POS_POS_NEG_OCTANT,
  NEG_NEG_POS_OCTANT,
  NEG_NEG_NEG_OCTANT,
  NEG_POS_NEG_OCTANT,
  NEG_POS_POS_OCTANT,
  END_OCTANT = NEG_POS_POS_OCTANT
};

/*! \brief Enumeration to specify whether function must find a point
 *
 * This enumeration is used by the findNextPolygonCorner member function when
 * design-by-contract is enabled. 
 */
enum PointFindNecessity{
  POINT_MUST_BE_FOUND,
  POINT_MAY_NOT_BE_FOUND
};

/*! \brief Enumeration to specify the cell attribute(s) to calc. numerically
 */
enum NumericalCellIntegrationType{
  CELL_VOLUME,
  CELL_SURFACE_AREAS,
  CELL_VOLUME_AND_SURFACE_AREAS
};  

/*! \brief Enumeration to specify the orientation of a polygon
 */
enum PolygonOrientation{
  LEFT_HANDED,
  RIGHT_HANDED,
  INVALID_ORIENTATION
};

template<typename Cell, typename SurfaceMap = typename Cell::SurfaceMap>
class CellFactory 
{
public:

  //@{
  //! Typedefs
  //! Typedef for cell pointer
  typedef typename Teuchos::RCP<Cell> CellPtr;
  //! Typedef for bounding box
  typedef Quad<Pair<typename Cell::ordinalType, NumericalCellIntegrationType>,
	       Pair<typename Cell::scalarType,typename Cell::scalarType>,
	       Pair<typename Cell::scalarType,typename Cell::scalarType>,
	       Pair<typename Cell::scalarType,typename Cell::scalarType> >
	       BoudingBox;
  //@}

private:
  
  //! Typedef for cell ordinal type
  typedef typename Cell::ordinalType cellOrdinalType;
  //! Typedef for surface ordinal type
  typedef typename Cell::surfaceOrdinalType surfaceOrdinalType;
  //! Typedef for scalar type
  typedef typename Cell::scalarType scalarType;
  //! Typedef for suface-sense pairs iterator
  typedef typename Cell::SurfaceSensePairsIterator SurfaceSensePairsIterator;
  //! Typedef for Boolean array
  typedef typename Cell::BooleanArray BooleanArray;
  //! Typedef for scalar traits
  typedef Teuchos::ScalarTraits<scalarType> ST;
  //! Typedef for cell ordinal traits
  typedef Teuchos::OrdinalTraits<cellOrdinalType> CellOT;
  //! Typedef for surface ordinal traits
  typedef Teuchos::OrdinalTraits<surfaceOrdinalType> SurfaceOT;
  //! Typedef for three space traits and policy struct
  typedef ThreeSpaceTraitsAndPolicy<scalarType> ThreeSpace;
  //! Typedef for linear algebra policy
  typedef LinearAlgebraPolicy<scalarType> LAP;
  //! Typedef for vector
  typedef typename ThreeSpace::Vector Vector;
  //! Typedef for matrix
  typedef typename ThreeSpace::Matrix Matrix;
  //! Typedef for intersection point
  typedef Pair<Trip<scalarType,scalarType,scalarType>,
	       Trip<surfaceOrdinalType,surfaceOrdinalType,surfaceOrdinalType> >
  IntersectionPoint;
  //!Typedef for polygon
  typedef Polygon<surfaceOrdinalType,scalarType> Polygon;
  //! Typedef for polygon corner
  typedef typename Polygon::Point PolygonCorner;

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

  //! Get the cells needing Monte Carlo integration
  Teuchos::Array<typename Cell::ordinalType> 
  getCellsNeedingMonteCarloIntegration() const;

protected:

  //! Calculate the volume and area of a polyhedral cell
  void calculatePolyhedralCellVolumeAndArea( CellPtr &cell );

  //! Create the polygons bounding the cell
  static void createBoundingPolygons( 
				  const Teuchos::Array<Polygon> &cell_polygons,
				  CellPtr &cell );

  //! Determine if a cell can have its volume calculated
  static void isAnalyticallyIntegrable( CellPtr &cell );

  //! Calculate the volume of a polyhedral cell using bounding polygons
  static scalarType calculatePolyhedralCellVolumeFromPolygons( 
				const Teuchos::Array<Polygon> &cell_polygons );

  //! Create a bounding box for a polyhedral cell from bounding polygons
  static void createBoundingBoxFromPolygons( 
				BoundingBox &cell_bounding_box,
				const Teuchos::Array<Polygon> &cell_polygons );

  //! Calculate the intersection points of planes with a plane of interest
  static void calculateIntersectionPoints(
			    std::list<IntersectionPoint> &intersection_points,
			    const SurfaceSensePairsIterator &plane_of_polygon,
			    const CellPtr &cell ) const;

  //! Calculate the intersection point created by three planes
  static IntersectionPoint calculateIntersectionPoint(
		     const SurfaceSensePairsIterator &primary_surface,
		     const SurfaceSensePairsIterator &secondary_surface,
		     const SurfaceSensePairsIterator &tertiary_surface ) const;

  //! Return if the intersection point is real
  static bool isRealIntersectionPoint( const IntersectionPoint &point,
				       const CellPtr &cell ) const;

  //! Initialize boolean variables for the point test
  static void initializeBooleansForPointTest( 
			      const Octant octant,
			      bool &primary_surface_boolean_parameter,
			      bool &secondary_surface_boolean_parameter,
			      bool &tertiary_surface_boolean_parameter ) const;

  //! Get the point test function multiplier
  static unsigned getPointTestFunctionMultiplier( const Octant octant ) const;
  
  //! Create a polygon from intersection points
  static Polygon createPolygonFromIntersectionPoints(
			     std::list<IntersectionPoint> &intersection_points,
			     const CellPtr &cell ) const;

  //! Find the first three points on the boundary of the polygon
  static typename std::list<Pair<scalarType,scalarType> >::const_iterator 
  initializePolygonCorners( std::list<PolygonCorner> &oriented_polygon_corners,
			    std::list<IntersectionPoint> &intersection_points,
			    const CellPtr &cell,
			    surfaceOrdinalType &current_surface_id ) const;

  //! Find the lexicographically largest point
  static typename std::list<IntersectionPoint>::const_iterator
  getLexicographicallyLargestPoint(
	       const std::list<IntersectionPoint> &intersection_points ) const;

  //! Find the next point on the boundary of the polygon
  /*! \details If the point may not be found by this function 
   * (POINT_MAY_NOT_BE_FOUND), this function may return an iterator to the
   * end of the list. It is therefore important to test the iterator returned.
   */
  static typename std::list<IntersectionPoint>::const_iterator
  getNextPolygonCorner( 
       const surfaceOrdinalType desired_surface_id,
       const typename std::list<PolygonCorner>::const_iterator &current_corner,
       const std::list<IntersectionPoint> &intersection_points,
       PointFindNecessity point_find_necessity = POINT_MUST_BE_FOUND ) const;

  //! Get the next surface id (edge) of the polygon
  static scalarType getNextSurfaceId( 
		    const surfaceOrdinalType current_surface_id,   
		    const typename std::list<IntersectionPoint>::const_iterator
		    &intersection_point ) const;

  //! Rotate the polygon to the x-y plane
  static void transformPolygon( std::list<PolygonCorner> &polygon,
			 const SurfaceSensePairsIterator &plane_of_polygon,
			 Matrix &rotation_matrix,
			 Vector &translation_vector ) const;

  //! Calculate the volume contribution from a surface bounding this cell
  static scalarType calculatePolygonVolumeContribution( 
			   const std::list<PolygonCorner> &polygon,
			   const ScalarType polygon_area,
			   const Vector plane_of_polygon_normal,
			   const Vector reference_plane_normal,
			   const scalarType reference_plane_const_term ) const;

  //! Calculate the volume and area of a rotationally symmetric cell
  void calculateRotationallySymmetricCellVolumeAndArea( CellPtr &cell );

  //! Initialize the polygon
  // \brief Returns an iterator to the start point of the new polygon
  // \param current_surface_id holds the surface id that should be searched
  //        for in the next intersection point
  std::list<Quad<double,double,unsigned,unsigned> >::const_iterator
  initializePolygon( 
		    std::list<Quad<double,double,unsigned,unsigned> > 
		    &polygon,
		    std::list<Quad<double,double,unsigned,unsigned> > 
		    &intersection_points,
		    const Teuchos::Array<Pair<Surface,Surface::Sense> > 
                    &surfaces,
		    unsigned &current_surface_id ) const;  

  //! Calculate the rotationally symmetric cell volume and surface areas
  // \brief If the cell is indeed rotationally symmetric, true will be returned
  bool calculateRotationallySymmetricCellVolumeAndSurfaceAreas();

  //! Calculate a bounding box for the cell
  Cell calculateBoundingBox() const;

private:

  // Stored copy of the global surface map (weak pointer)
  Teuchos::RCP<const SurfaceMap> d_global_surface_map;

  // Bounding boxes of cells needing MC integration to determine vol (and area)
  Teuchos::Array<BoundingBox> d_bounding_boxes;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include CellFactory_def.hpp

//---------------------------------------------------------------------------//

#endif // end CELL_FACTORY_HPP

//---------------------------------------------------------------------------//
// end CellFactory.hpp
//---------------------------------------------------------------------------//


