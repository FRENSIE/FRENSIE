//---------------------------------------------------------------------------//
//!
//! \file   Utility_StructuredHexMesh.hpp
//! \author Philip Britt
//! \brief  Hexahedron mesh storage header file
//! 
//---------------------------------------------------------------------------//

#ifndef UTILITY_STRUCTURED_HEX_MESH_HPP
#define UTILITY_STRUCTURED_HEX_MESH_HPP

// Std Lib Includes
#include <utility>
#include <list>

// boost includes
#include <boost/unordered_map.hpp>

// Trillinos Includes
#include <Teuchos_Array.hpp>

namespace Utility{
/*! StructuredHexMesh stores the mesh itself and performs calculations
 *  to return important information from the mesh */
class StructuredHexMesh
{

public:

  //! HexIndex handle
  typedef unsigned long HexIndex;

  //! plane index handle
  typedef unsigned PlaneIndex;
  
  //! HexVolume handles
  typedef double HexVolume;

  //! Iterator handle over all hex elements
  typedef std::list<HexIndex>::const_iterator HexIDIterator;

  //! Constructor
  StructuredHexMesh( const Teuchos::Array<double>& x_planes,
                     const Teuchos::Array<double>& y_planes,
                     const Teuchos::Array<double>& z_planes );
  //! Destructor
  ~StructuredHexMesh()
  { /* ... */ }

  //! Returns the volumes of the hex elements for the estimator class.
  boost::unordered_map<HexIndex, HexVolume> calculateVolumes();

  //! Returns a bool that says whether or not a point is in the mesh.
  bool isPointInMesh( const double point[3] ) const;
  
  //! Returns the index of the hex that contains a given point.
  HexIndex whichHexIsPointIn( const double point[3] ) const;
  
  //! Returns an array of pairs of hex IDs and partial track lengths along a given line segment.
  Teuchos::Array<std::pair<HexIndex,double>> computeTrackLengths( 
                              const double start_point[3],
                              const double end_point[3] );
  
  //! Get the start iterator of the hex element list.
  /*! \details returns the iterator that points to the first element in the list containing
   *           all of the hex ID elements */
  HexIDIterator getStartHexIDIterator();
  
  //! Get the end iterator of the hex element list.
  /*! \details returns the iterator that points to one beyond the last element in the list containing
   *           all of the hex ID elements */
  HexIDIterator getEndHexIDIterator();
  
  //! Get the number of planes on the X axis.
  unsigned getNumberOfXPlanes();
  
  //! Get the number of planes on the Y axis.
  unsigned getNumberOfYPlanes();
  
  //! Get the number of planes on the Z axis.
  unsigned getNumberOfZPlanes();
  
  //! Get the location of a specific plane on the x axis.
  double getXPlaneLocation( PlaneIndex i);
  
  //! Get the location of a specific plane on the y axis.
  double getYPlaneLocation( PlaneIndex i);
  
  //! Get the location of a specific plane on the z axis.
  double getZPlaneLocation( PlaneIndex i);
  
  //! Deconstruct a hex index into indices of planes on each dimension.
  /*! \details This method is used primarily with moab since the moab
   *           methods used in the estimator class require the parameter space over
   *           all three dimensions to form a structured mesh */
  void getHexPlaneIndices(const HexIndex h, unsigned hex_parameter_indices[3]);
  
private:
  // enumeration type converting dimensions to integers
  enum Dimension{ x_dim = 0,
                  y_dim = 1,
                  z_dim = 2 };
  
  // set the plane indices that make up the hex element index
  void setMemberIndices( const double point[3],
                         const double direction[3],
                         const Teuchos::Array<std::pair<Dimension,PlaneIndex>>& interaction_planes );
  
  /* Deals with a special case of the particle being born in the boundary region but traveling away from the mesh
     and the particle born in the boundary region and staying in that boundary region.
     If it does, it should just return true which will result in a return of an empty contribution array */

  //! \todo this method should be deleted when the boundary region is successfully removed from the code
  bool boundaryRegionSpecialCase( const double start_point[3],
                                  const double end_point[3],
                                  const double direction[3] );
  
  // determines if the particle has exited the mesh
  bool didParticleExitMesh( Dimension intersection_dimension,
                            Teuchos::Array<std::pair<Dimension,PlaneIndex>> interaction_planes); 
  
  // returns the planes that a particle might interact with next
  Teuchos::Array<std::pair<Dimension,PlaneIndex>> findInteractionPlanes( 
                                                        const double point[3],
                                                        const double direction[3] );
                                                        
  // finds distance to each of the possible interaction planes
  Teuchos::Array<std::pair<Dimension,double>> findDistances( 
                                                        const double point[3],
                                                        const double direction[3],
                      const Teuchos::Array<std::pair<Dimension,PlaneIndex>>& planeSet );
                      
  //used to find the relevant intersection point where the particle will intersect the mesh
  std::pair<Dimension,double> findIntersectionPoint( const Teuchos::Array<std::pair<Dimension,double>>& distances);
  
  //form the index out of the x,y, and z lower hex plane bounding indices
  HexIndex findIndex( const unsigned x_index,
                      const unsigned y_index,
                      const unsigned z_index ) const;
  
  //overload function for ease
  HexIndex findIndex( const unsigned indices[3] ) const;
  
  // sets the incrementer for mesh iteration
  void setIncrementer( const double direction[3],
                       int incrementer[3] ) const;

  // pushes point along direction to new intersection point
  void pushPoint( double point[3],
                  const double direction[3],
                  const double push_distance ) const;

  // sets x dimension for hex index
  void setXIndex( const double x );

  // sets y dimension for hex index
  void setYIndex( const double y );

  // sets z dimension for hex index
  void setZIndex( const double z );
  
  // finds interaction plane for a given dimension
  void findInteractionPlaneForDimension( const Dimension dim,
                                         const double coordinate_component,
                                         const double direction_component,
                                         const Teuchos::Array<double>& plane_set,
                                         Teuchos::Array<std::pair<Dimension,PlaneIndex>>& interaction_planes ) const;

  // check boundary region special cases for each dimension
  bool boundaryRegionByDimension( const double start_point_component,
                                  const double end_point_component,
                                  const double direction_component,
                                  const Teuchos::Array<double>& plane_set ) const;
  
  // The tolerance used for geometric tests
  static const double s_tol;

  // plane location member data
  Teuchos::Array<double> d_x_planes;
  Teuchos::Array<double> d_y_planes;
  Teuchos::Array<double> d_z_planes;
  
  // all hex elements
  std::list<HexIndex> d_hex_elements;
  
  // indices of the planes that are used to form the index for the hex element a particle is in
  unsigned d_hex_plane_indices[3];  
                            
};

} // end Utility namespace


#endif // end UTILITY_STRUCTURED_HEX_MESH_HPP

//---------------------------------------------------------------------------//
// end Utility_StructuredHexMesh.hpp
//---------------------------------------------------------------------------//
