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
#include <tuple>

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
  boost::unordered_map<HexIndex, HexVolume> calculateVolumes() const;

  //! Returns a bool that says whether or not a point is in the mesh.
  bool isPointInMesh( const double point[3] ) const;
  
  //! Returns the index of the hex that contains a given point.
  HexIndex whichHexIsPointIn( const double point[3] ) const;

  //! Returns an array of pairs of hex IDs and partial track lengths along a given line segment.
  Teuchos::Array<std::pair<HexIndex,double>> computeTrackLengths( 
                              const double start_point[3],
                              const double end_point[3] )const;
  
  //! Get the start iterator of the hex element list.
  /*! \details returns the iterator that points to the first element in the list containing
   *           all of the hex ID elements */
  HexIDIterator getStartHexIDIterator() const;
  
  //! Get the end iterator of the hex element list.
  /*! \details returns the iterator that points to one beyond the last element in the list containing
   *           all of the hex ID elements */
  HexIDIterator getEndHexIDIterator() const;
  
  //! Get the number of planes on the X axis.
  unsigned getNumberOfXPlanes() const;
  
  //! Get the number of planes on the Y axis.
  unsigned getNumberOfYPlanes() const;
  
  //! Get the number of planes on the Z axis.
  unsigned getNumberOfZPlanes() const;
  
  //! Get the location of a specific plane on the x axis.
  double getXPlaneLocation( PlaneIndex i) const;
  
  //! Get the location of a specific plane on the y axis.
  double getYPlaneLocation( PlaneIndex i) const;
  
  //! Get the location of a specific plane on the z axis.
  double getZPlaneLocation( PlaneIndex i) const;
  
  //! Deconstruct a hex index into indices of planes on each dimension.
  /*! \details This method is used primarily with moab since the moab
   *           methods used in the estimator class require the parameter space over
   *           all three dimensions to form a structured mesh */
  void getHexPlaneIndices(const HexIndex h, unsigned hex_parameter_indices[3]) const;
  
private:
  // enumeration type converting dimensions to integers
  enum Dimension: unsigned{ X_DIMENSION = 0,
                            Y_DIMENSION = 1,
                            Z_DIMENSION = 2 };

  // Returns a pair where the first member is true if the ray intersects with the mesh and the second is the distance to the intersection point
  std::tuple<bool, Dimension, double> doesRayIntersectMesh( const double point[3],
                                                            const double direction[3],
                                                            const double track_length) const;

  // Trace particle path through mesh until it dies or leaves mesh
  Teuchos::Array<std::pair<HexIndex,double>> traceThroughMesh( double point[3],
                                                               const double direction[3],
                                                               const double track_length,
                                                               PlaneIndex hex_plane_indices[3] ) const;

  // Find the interaction planes that a particle will interact with
  Teuchos::Array<std::pair<Dimension, PlaneIndex>> findInteractionPlanes( const double point[3],
                                                                          const double direction[3],
                                                                          const PlaneIndex hex_plane_indices[3] ) const;

  // Find the intersection distance along the path of the particle with the next hex
  std::pair<Dimension, double> findIntersectionDistance( const double point[3],
                                                         const double direction[3],
                                                         const Teuchos::Array<std::pair<Dimension, PlaneIndex>>& interaction_planes) const;

  // Calculate distance to a plane from a ray along its direction
  double findDistanceToInteractionPlane( const double interaction_plane_location,
                                         const double position_component,
                                         const double direction_component ) const;

  // Find the shortest distance to the respective interaction planes along a particle path
  std::pair<Dimension, double> findShortestDistance( const Teuchos::Array<std::pair<Dimension, double>>& distance_array ) const;

  // Form the incrementer so that the particle increments over the planes in the correct direction
  void setIncrementer( unsigned incrementer[3],
                       const double direction[3] ) const;

  // set the plane indices that make up the hex element index
  void setHexPlaneIndices( const double current_point[3],
                         PlaneIndex hex_plane_indices[3] )const;
  
  // overloaded function for setting member indices
  void setHexPlaneIndices( const Dimension intersection_dimension,
                         const double current_point[3],
                         PlaneIndex hex_plane_indices[3] )const;

  // Set individual hex plane indicies for particle.
  StructuredHexMesh::PlaneIndex setHexPlaneIndex( const double position_component, 
                       const Teuchos::Array<double>& plane_set,
                       const Dimension plane_dimension  ) const;
                       
  // Returns a set of distances to up to 3 planes that bound the mesh which the particle may interact with
  Teuchos::Array<std::pair<Dimension, double>> findBoundingInteractionPlaneDistances( const double point[3],
                                                                                      const double direction[3] ) const;

  // Checks an individual set of planes for interaction plane in that dimension
  void checkPlaneSet( const Teuchos::Array<double>& plane_set,
                      const double position_component,
                      const double direction_component,
                      Teuchos::Array<std::pair<Dimension, double>>& boundary_planes,
                      const Dimension plane_dimension ) const;

  // Returns whether or not a particle actually hit the mesh surface
  bool isPointOnMeshSurface( const double point[3],
                             const Dimension dimension_intersected ) const;

  // function for checking each individual plane to see if it is within bounds
  bool checkWithinBoundingPlane( const double position_component,
                                 const Teuchos::Array<double>& plane_set )const;
  
  // determines if the particle has exited the mesh
  bool didParticleLeaveMesh( const Dimension intersection_dimension,
                             const Teuchos::Array<std::pair<Dimension,PlaneIndex>> interaction_planes) const; 
                                                        
  // finds distance to each of the possible interaction planes
  Teuchos::Array<std::pair<Dimension,double>> findDistances( 
                                                        const double point[3],
                                                        const double direction[3],
                      const Teuchos::Array<std::pair<Dimension,PlaneIndex>>& planeSet ) const;
                      
  //used to find the relevant intersection point where the particle will intersect the mesh
  std::pair<Dimension,double> findIntersectionPoint( const Teuchos::Array<std::pair<Dimension,double>>& distances) const;
  
  // sets the incrementer for mesh iteration
  void setIncrementer( const double direction[3],
                       int incrementer[3] ) const;

  // pushes point along direction to new intersection point
  void pushPoint( double point[3],
                  const double direction[3],
                  const double push_distance ) const;
  
  // finds interaction plane for a given dimension
  void findInteractionPlaneForDimension( const Dimension dim,
                                         const double coordinate_component,
                                         const double direction_component,
                                         const Teuchos::Array<double>& plane_set,
                                         const Teuchos::Array<std::pair<Dimension,PlaneIndex>>& interaction_planes ) const;
  // Compute hex index from plane indices
  unsigned long findIndex( const unsigned i,
                           const unsigned j,
                           const unsigned k ) const;

  // Compute hex index from plane indices
  unsigned long findIndex( const unsigned indices[3] ) const;

  // The tolerance used for geometric tests
  static const double s_tol;

  // plane location member data
  Teuchos::Array<double> d_x_planes;
  Teuchos::Array<double> d_y_planes;
  Teuchos::Array<double> d_z_planes;
  
  // all hex elements
  std::list<HexIndex> d_hex_elements;
                            
};

} // end Utility namespace


#endif // end UTILITY_STRUCTURED_HEX_MESH_HPP

//---------------------------------------------------------------------------//
// end Utility_StructuredHexMesh.hpp
//---------------------------------------------------------------------------//
