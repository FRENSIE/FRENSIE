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
<<<<<<< 0a60885e4e26f934d634d5bb9609256a900f824c
#include <list>

// boost includes
#include <boost/unordered_map.hpp>
=======
>>>>>>> finished computeTrackLengths. Next will work on methods that are used in computeTrackLengths

// Trillinos Includes
#include <Teuchos_Array.hpp>

namespace Utility{

class StructuredHexMesh
{

public:
<<<<<<< 0a60885e4e26f934d634d5bb9609256a900f824c
  //! HexIndex handle
  typedef unsigned long HexIndex;

  //! plane index handle
  typedef unsigned PlaneIndex;
  
  //! HexVolume handles
  typedef double HexVolume;

  //! iterator handle over all hex elements
  typedef std::list<HexIndex>::const_iterator HexIDIterator;

  //! Constructor
  StructuredHexMesh( const Teuchos::Array<double>& x_planes,
                     const Teuchos::Array<double>& y_planes,
                     const Teuchos::Array<double>& z_planes );
=======
  
  //! Constructor
  StructuredHexMesh( const Teuchos::Array<double>& x_grid_points,
                     const Teuchos::Array<double>& y_grid_points,
                     const Teuchos::Array<double>& z_grid_points );
>>>>>>> finished computeTrackLengths. Next will work on methods that are used in computeTrackLengths

  //! Destructor
  ~StructuredHexMesh()
  { /* ... */ }
<<<<<<< 0a60885e4e26f934d634d5bb9609256a900f824c

  //! returns the volumes of the hex elements for the estimator class
  boost::unordered_map<HexIndex, HexVolume> calculateVolumes();

  //! returns a bool that says whether or not a point is in the mesh
  bool isPointInMesh( const double point[3] );
  
  //! returns the index of the hex that contains a given point
  HexIndex whichHexIsPointIn( const double point[3] );
  
  //! returns partial track lengths along a given line segment
  Teuchos::Array<std::pair<HexIndex,double>> computeTrackLengths( 
                              const double start_point[3],
                              const double end_point[3],
                              const double direction[3],
                              const double track_length );
  
  //! get the start iterator of the hex element list
  HexIDIterator getStartHexIDIterator();
  
  //! get the end iterator of the hex element list
  HexIDIterator getEndHexIDIterator();
  
  //! get the number of planes on the X axis
  unsigned getNumberOfXPlanes();
  
  //! get the number of planes on the Y axis
  unsigned getNumberOfYPlanes();
  
  //! get the number of planes on the Z axis
  unsigned getNumberOfZPlanes();
  
  //! get the location of a specific plane on the x axis
  double getXPlaneLocation( PlaneIndex i);
  
  //! get the location of a specific plane on the y axis
  double getYPlaneLocation( PlaneIndex i);
  
  //! get the location of a specific plane on the z axis
  double getZPlaneLocation( PlaneIndex i);
  
  //! deconstruct a hex index into indices of planes on each dimension
  void moabGetHexPlaneIndices(const HexIndex h, unsigned hex_parameter_indices[3]);
  
private:
  //enumeration type converting dimensions to integers
  enum planeDimension{ x_dim = 0,
                       y_dim = 1,
                       z_dim = 2 };
  
  void setMemberIndices( const double point[3],
                         const double direction[3],
                         const Teuchos::Array<std::pair<planeDimension,PlaneIndex>>& interaction_planes );
  
  bool boundaryRegionSpecialCase( const double start_point[3],
                                  const double end_point[3],
                                  const double direction[3] );

  bool didParticleExitMesh( planeDimension intersection_dimension,
                            Teuchos::Array<std::pair<planeDimension,PlaneIndex>> interaction_planes); 
                       
  Teuchos::Array<std::pair<planeDimension,PlaneIndex>> findInteractionPlanes( 
                                                        const double point[3],
                                                        const double direction[3] );
                         
  Teuchos::Array<std::pair<planeDimension,double>> findDistances( 
                                                        const double point[3],
                                                        const double direction[3],
                      const Teuchos::Array<std::pair<planeDimension,PlaneIndex>>& planeSet );
                      
  //used to find the relevant intersection point where the particle will intersect the mesh
  std::pair<planeDimension,double> findIntersectionPoint( const Teuchos::Array<std::pair<planeDimension,double>>& distances);
  
  //form the index out of the x,y, and z lower hex plane bounding indices
  HexIndex findIndex( const unsigned x_index,
                      const unsigned y_index,
                      const unsigned z_index );
  
  //overload function for ease
  HexIndex findIndex( const unsigned indices[3] );
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
=======
  
  //! Tells whether or not a point is inside the mesh
  bool isPointInMesh( const double point[3] );
  
  //! Returns index for which hex element the point is contained in
  unsigned whichHexIsPointIn( const double point[3], unsigned hex_plane_indices[6] );
  
  //! returns 1-d array index of hex assuming x index is iterated over first
  unsigned returnIndex( const unsigned x_index,
                        const unsigned y_index,
                        const unsigned z_index );
  
  //! returns partial track lengths along a given line segment
  Teuchos::Array<std::pair<unsigned,double>> computeTrackLengths( 
                              const double start_point[3],
                              const double end_point[3],
                              const double direction[3] );
  // plane location member data
  Teuchos::Array<double>& d_x_planes;
  Teuchos::Array<double>& d_y_planes;
  Teuchos::Array<double>& d_z_planes;
  
  // bounding plane member data (x1,x2,y1,y2,z1,z2)
  double d_bounding_planes[6];
  
                               
private:

  // The tolerance used for geometric tests
  static const double s_tol;       

  //!find set of possible planes that track length can intersect with
  void findInteractionPlanes( const double current_point[3],
                              const double direction[3],
                              unsigned hex_plane_indices[3],
                              unsigned plane_set[3] );
  
  //!Find distance to chosen plane
  double calculateDistanceToPlane( const double current_point_component,
                                   const double direction_component,
                                   const unsigned plane_location ); 
  
  //!pick the smallest distance to planes to return distance to said plane                                  
  double pickPlane(const double distances[3]);
  
  void findCentroid(const double current_point[3],
                  const double distance[3],
                  const double direction[3],
                  double centroid_point[3]);
                  
  bool rayIntersectsWithBoundingPlanes(const double start_point[3],
                                       const double direction[3]);

}

>>>>>>> finished computeTrackLengths. Next will work on methods that are used in computeTrackLengths

} // end Utility namespace


#endif // end UTILITY_STRUCTURED_HEX_MESH_HPP

//---------------------------------------------------------------------------//
// end Utility_StructuredHexMesh.hpp
//---------------------------------------------------------------------------//
