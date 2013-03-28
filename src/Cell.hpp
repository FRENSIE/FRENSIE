//---------------------------------------------------------------------------//
// \file   Cell.hpp
// \author Alex Robinson
// \brief  Cell class declaration
//---------------------------------------------------------------------------//

#ifndef CELL_HPP
#define CELL_HPP

// Std Lib Includes
#include <string>
#include <map>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "BooleanCellFunctor.hpp"
#include "Surface.hpp"
#include "Tuple.hpp"
#include "ContractException.hpp"

namespace FACEMC{

class Cell
{

public:

  //@{
  //! Typedefs
  typedef Teuchos::Tuple<double,3> Vector;
  //@}
  
  //! Constructor
  // \brief The cell volume will be calculated if requested
  Cell( unsigned id,
	std::string &cell_definition,
	std::map<unsigned,Teuchos::RCP<Surface> > &global_surface_map,
	bool calculate_geometric_data );

  //! Destructor
  ~Cell()
  { /* ... */ }

  //! Return if the point is in the cell
  bool isIn( const Vector &point ) const;

  //! Return if the point is on the cell
  bool isOn( const Vector &point ) const;

  //! Return the volume of the cell
  double getVolume() const;

  //! Return the area of a surface bounding the cell
  double getSurfaceArea( unsigned surface_id ) const;

protected:

  //! Default Constructor
  Cell() : d_cell_definition_evaluator( "0n1" ), 
	   d_geometric_data_calculated(true)
  { /* ... */ }

  //! Simply Constructor
  Cell( std::string &cell_definition ) 
    : d_cell_definition_evaluator( cell_definition ), 
      d_geometric_data_calculated(true)
  { /* ... */ }

  //! Strip the cell definition of set operation characters
  void simplifyCellDefinitionString( std::string &cell_definition );

  //! Assign surfaces to the cell
  void assignSurfaces( std::string &cell_definition, 
		       std::map<unsigned,Teuchos::RCP<Surface> > &global_surface_map );

  //! Calculate the cell volume and surface area of the bounding surfaces
  void calculateVolumeAndSurfaceAreas();

  //! Calculate the polyhedron volume and surface areas
  void calculatePolyhedralCellVolumeAndSurfaceAreas();

  //! Calculate the intersection points of planes with the z-axis
  void calculatePolygonIntersectionPoints( 
			    const Teuchos::Array<Pair<Surface,Surface::Sense> > 
			    &surfaces,
			    std::list<Quad<double,double,unsigned,unsigned> > 
			    &intersection_points ) const;
  
  //! Test if an intersection point is real
  bool testIntersectionPoint( 
			    const Teuchos::Array<Pair<Surface,Surface::Sense> > 
			    &surfaces,
			    const Quad<double,double,unsigned,unsigned>
			    &intersection_point ) const;

  //! Create a polygon from intersection points
  void createPolygon( std::list<Quad<double,double,unsigned,unsigned> > 
		      &intersection_points,
		      const Teuchos::Array<Pair<Surface,Surface::Sense> > 
                      &surfaces ) const;

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

  //! Calculate the area of a surface bounding the polyhedral cell
  // \brief Adds the area of the surface relative to this cell to the 
  // d_surface_areas map
  void calculatePolygonArea( 
	       const unsigned surface_id,
	       const std::list<Quad<double,double,unsigned,unsigned> > &polygon,
	       std::list<double> &polygon_areas );

  //! Calculate the volume contribution from a surface bounding this cell
  void calculatePolygonVolumeContribution( 
	       const Surface &reference_surface,
	       const std::list<Quad<double,double,unsigned,unsigned> > &polygon,
	       const std::list<double> &polygon_areas );
  
  //! Calculate the rotationally symmetric cell volume and surface areas
  // \brief If the cell is indeed rotationally symmetric, true will be returned
  bool calculateRotationallySymmetricCellVolumeAndSurfaceAreas();

  //! Calculate the cell volume and surface areas using monte carlo integration
  void calculateVolumeAndSurfaceAreasUsingMonteCarlo();

  //! Calculate a bounding box for the cell
  Cell calculateBoundingBox() const;
  
  //! Get the surface array
  Teuchos::Array<Pair<Teuchos::RCP<Surface>,Surface::Sense> >
  getSurfaceArray() const;

private:

  // Cell Id
  unsigned d_id;

  // Functor used to evaluate the cell definition
  BooleanCellFunctor d_cell_definition_evaluator;

  // Surfaces and Senses that define the cell
  Teuchos::Array<Pair<Teuchos::RCP<Surface>,Surface::Sense> > d_surfaces;
  
  // Surface information particular to this cell
  std::map<unsigned,double> d_surface_areas;

  // Cell volume
  double d_volume;

  // Bool that records if the cell volume and surface areas were calculated
  bool d_geometric_data_calculated;

};

} // end FACEMC namespace

#endif // end CELL_HPP

//---------------------------------------------------------------------------//
// end Cell.hpp
//---------------------------------------------------------------------------//
