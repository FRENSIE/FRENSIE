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
#include "Tuple.hpp"

namespace FACEMC{

//! Eighth space enumeration
/*! \details Assigning the booleans in this order assures that the octants
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

template<typename Cell, typename SurfaceMap = typename Cell::SurfaceMap>
class CellFactory 
{
public:

  //@{
  //! Typedefs
  //! Typedef for cell pointer
  typedef typename Teuchos::RCP<Cell> CellPtr;
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
  void calculatePolyhedralCellVolumeAndArea( CellPtr &cell ) const;

  //! Calculate the intersection points of planes with a plane of interest
  void calculateIntersectionPoints(
			    const SurfaceSensePairsIterator &plane_of_polygon,
			    const CellPtr &cell,
			    std::list<IntersectionPoints>
			    &intersection_points ) const;

  //! Calculate the intersection point created by three planes
  IntersectionPoint calculateIntersectionPoint(
		     const SurfaceSensePairsIterator &primary_surface,
		     const SurfaceSensePairsIterator &secondary_surface,
		     const SurfaceSensePairsIterator &tertiary_surface ) const;

  //! Return if the intersection point is real
  bool isRealIntersectionPoint( const IntersectionPoint &point,
				const CellPtr &cell ) const;

  //! Initialize boolean variables for the point test
  void initializeBooleansForPointTest( 
			      const Octant octant,
			      bool &primary_surface_boolean_parameter,
			      bool &secondary_surface_boolean_parameter,
			      bool &tertiary_surface_boolean_parameter ) const;

  //! Get the point test function multiplier
  unsigned getPointTestFunctionMultiplier( const Octant octant ) const;

  //! Rotate the intersection points to the x-y plane
  void transformIntersectionPoints( 
			    const SurfaceSensePairsIterator &plane_of_polygon,
			    std::list<IntersectionPoints> &intersection_points,
			    Matrix &rotation_matrix,
			    Vector &translation_vector ) const;
  
  //! Create a polygon from intersection points
  void createPolygon( const std::list<IntersectionPoints> &intersection_points,
		      const CellPtr &Cell,
		      std::list<Pair<scalarType,scalarType> > &polygon ) const;

  //! Calculate the area of a polygon
  scalarType calculatePolygonArea( 
		const std::list<Pair<scalarType,scalarType> > &polygon ) const;

  //! Calculate the volume contribution from a surface bounding this cell
  scalarType calculatePolygonVolumeContribution( 
			const std::list<Pair<scalarType,scalarType> > &polygon,
			const Surface &reference_surface,
			SurfaceSense polygon_sense,
			SurfaceSense reference_sense ) const;

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

  //! Assign the correct sign to the polygon areas
  // \brief If the largest polygon area is negative, this feature lies
  // inside of the cell. To calculate the correct volume contribution
  // the largest polygon area must always be positive. If the largest
  // polygon area is negative, multiply all polygon areas by -1.
  void assignPolygonAreaSign( std::list<double> &polygon_areas );
  
  //! Calculate the rotationally symmetric cell volume and surface areas
  // \brief If the cell is indeed rotationally symmetric, true will be returned
  bool calculateRotationallySymmetricCellVolumeAndSurfaceAreas();

  //! Calculate a bounding box for the cell
  Cell calculateBoundingBox() const;

private:

  // Stored copy of the global surface map (weak pointer)
  Teuchos::RCP<const SurfaceMap> d_global_surface_map;

  // Cells needing Monte Carlo integration to determine volume and area
  Teuchos::ArrayView<typename Cell::ordinalType> 
  d_cells_needing_mc_integration;
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


