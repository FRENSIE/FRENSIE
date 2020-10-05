//---------------------------------------------------------------------------//
//!
//! \file   Utility_StructuredHexMesh.hpp
//! \author Philip Britt
//! \brief  Hexahedral mesh class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STRUCTURED_HEX_MESH_HPP
#define UTILITY_STRUCTURED_HEX_MESH_HPP

// Std Lib Includes
#include <utility>

// Boost Includes
#include <boost/serialization/vector.hpp>

// FRENSIE Includes
#include "Utility_Mesh.hpp"
#include "Utility_List.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"

namespace Utility{

/*! The structured hexahedral mesh class
 * \details This class stores the mesh itself and can be used to acquire
 * important information from the mesh (e.g. intersections of a line segment
 * with mesh elements).
 */
class StructuredHexMesh : public Mesh
{

public:

  //! The mesh element handle
  typedef Mesh::ElementHandle ElementHandle;

  //! The plane index
  typedef size_t PlaneIndex;

  //! Iterator over all mesh elements
  typedef Mesh::ElementHandleIterator ElementHandleIterator;

  //! The mesh element handle, primary intersection point, track length tuple array
  typedef Mesh::ElementHandleTrackLengthArray ElementHandleTrackLengthArray;

  //! The mesh element handle, volume map
  typedef Mesh::ElementHandleVolumeMap ElementHandleVolumeMap;

  //! The mesh data tag name set
  typedef Mesh::TagNameSet TagNameSet;

  //! The mesh element handle, data map
  typedef Mesh::MeshElementHandleDataMap MeshElementHandleDataMap;

  //! Constructor
  StructuredHexMesh( const std::vector<double>& x_planes,
                     const std::vector<double>& y_planes,
                     const std::vector<double>& z_planes );
  //! Destructor
  ~StructuredHexMesh()
  { /* ... */ }

  //! Get the mesh type name
  std::string getMeshTypeName() const final override;

  //! Get the mesh element type name
  std::string getMeshElementTypeName() const final override;

  //! Get the start iterator of the hex element list.
  ElementHandleIterator getStartElementHandleIterator() const final override;

  //! Get the end iterator of the hex element list.
  ElementHandleIterator getEndElementHandleIterator() const final override;

  //! Get the number of mesh elements
  size_t getNumberOfElements() const final override;

  //! Get the number of planes on the X axis.
  size_t getNumberOfXPlanes() const;

  //! Get the number of planes on the Y axis.
  size_t getNumberOfYPlanes() const;

  //! Get the number of planes on the Z axis.
  size_t getNumberOfZPlanes() const;

  //! Get the location of a specific plane on the x axis.
  double getXPlaneLocation( PlaneIndex i ) const;

  //! Get the location of a specific plane on the y axis.
  double getYPlaneLocation( PlaneIndex i ) const;

  //! Get the location of a specific plane on the z axis.
  double getZPlaneLocation( PlaneIndex i ) const;

  //! Deconstruct a hex index into indices of planes on each dimension.
  void getHexPlaneIndices( const ElementHandle h,
                           size_t hex_parameter_indices[3] ) const;

  //! Returns the volumes of the hex elements for the estimator class.
  void getElementVolumes( ElementHandleVolumeMap& element_volumes ) const final override;

  //! Returns the volume of a specific mesh element
  double getElementVolume( ElementHandle element ) const final override;

  //! Returns a bool that says whether or not a point is in the mesh.
  bool isPointInMesh( const double point[3] ) const final override;

  // Compute hex index from plane indices
  size_t findIndex( const size_t i, const size_t j, const size_t k ) const;

  // Compute hex index from plane indices
  size_t findIndex( const size_t indices[3] ) const;

  //! Returns the index of the hex that contains a given point.
  ElementHandle whichElementIsPointIn( const double point[3] ) const final override;

  //! Returns an array of pairs of hex IDs and partial track lengths along a given line segment.
  void computeTrackLengths( const double start_point[3],
                            const double end_point[3],
                            ElementHandleTrackLengthArray&
                            hex_element_track_lengths ) const final override;

  //! Export the mesh to a file (type determined by suffix - e.g. mesh.vtk)
  void exportData( const std::string& output_file_name,
                   const TagNameSet& tag_root_names,
                   const MeshElementHandleDataMap& mesh_tag_data ) const final override;

  //! Export the mesh to a file
  using Mesh::exportData;

private:

  // Default constructor
  StructuredHexMesh();

  // Enumeration type converting dimensions to integers
  enum Dimension: size_t{ X_DIMENSION = 0,
                          Y_DIMENSION = 1,
                          Z_DIMENSION = 2 };

  // Returns a pair where the first member is true if the ray intersects with the mesh and the second is the distance to the intersection point
  void doesRayIntersectMesh(
                  const double point[3],
                  const double direction[3],
                  const double track_length,
                  std::tuple<bool,Dimension,double>& intersection_data ) const;

  // Trace particle path through mesh until it dies or leaves mesh
  void traceThroughMesh(
              double point[3],
              const double direction[3],
              const double track_length,
              PlaneIndex hex_plane_indices[3],
              ElementHandleTrackLengthArray& hex_element_track_lengths ) const;

  // Find the interaction planes that a particle will interact with
  void findInteractionPlanes( const double point[3],
                              const double direction[3],
                              const PlaneIndex hex_plane_indices[3],
                              std::vector<std::pair<Dimension,PlaneIndex> >&
                              interaction_planes ) const;

  // Find the intersection distance along the path of the particle with the next hex
  void findIntersectionDistance(
                    const double point[3],
                    const double direction[3],
                    const std::vector<std::pair<Dimension,PlaneIndex> >&
                    interaction_planes,
                    std::pair<Dimension,double>& intersection_distance ) const;

  // Calculate distance to a plane from a ray along its direction
  double findDistanceToInteractionPlane(
                                      const double interaction_plane_location,
                                      const double position_component,
                                      const double direction_component ) const;

  // Form the incrementer so that the particle increments over the planes in the correct direction
  void setIncrementer( size_t incrementer[3],
                       const double direction[3] ) const;

  // set the plane indices that make up the hex element index
  void setHexPlaneIndices( const double current_point[3],
                           PlaneIndex hex_plane_indices[3] )const;

  // overloaded function for setting member indices
  void setHexPlaneIndices( const Dimension intersection_dimension,
                           const double current_point[3],
                           PlaneIndex hex_plane_indices[3] )const;

  // Set individual hex plane indicies for particle.
  PlaneIndex setHexPlaneIndex( const double position_component,
                               const std::vector<double>& plane_set,
                               const Dimension plane_dimension  ) const;

  // Returns a set of distances to up to 3 planes that bound the mesh which the particle may interact with
  void findBoundingInteractionPlaneDistances(
                                    const double point[3],
                                    const double direction[3],
                                    std::vector<std::pair<Dimension, double> >&
                                    bounding_intersection_data  ) const;

  // Checks an individual set of planes for interaction plane in that dimension
  void checkPlaneSet( const std::vector<double>& plane_set,
                      const double position_component,
                      const double direction_component,
                      std::vector<std::pair<Dimension, double> >& boundary_planes,
                      const Dimension plane_dimension ) const;

  // Returns whether or not a particle actually hit the mesh surface
  bool isPointOnMeshSurface( const double point[3],
                             const Dimension dimension_intersected ) const;

  // function for checking each individual plane to see if it is within bounds
  bool checkWithinBoundingPlane( const double position_component,
                                 const std::vector<double>& plane_set )const;

  // determines if the particle has exited the mesh
  bool didParticleLeaveMesh(
                           const Dimension intersection_dimension,
                           const std::vector<std::pair<Dimension,PlaneIndex> >&
                           interaction_planes ) const;

  // sets the incrementer for mesh iteration
  void setIncrementer( const double direction[3],
                       int incrementer[3] ) const;

  // pushes point along direction to new intersection point
  void pushPoint( double point[3],
                  const double direction[3],
                  const double push_distance ) const;

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The tolerance used for geometric tests
  static const double s_tol;

  // The plane location member data
  std::vector<double> d_x_planes;
  std::vector<double> d_y_planes;
  std::vector<double> d_z_planes;

  // The hex elements (ids)
  std::vector<ElementHandle> d_hex_elements;
};

// Save the data to an archive
template<typename Archive>
void StructuredHexMesh::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Mesh );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_x_planes );
  ar & BOOST_SERIALIZATION_NVP( d_y_planes );
  ar & BOOST_SERIALIZATION_NVP( d_z_planes );
  ar & BOOST_SERIALIZATION_NVP( d_hex_elements );
}

// Load the data from an archive
template<typename Archive>
void StructuredHexMesh::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Mesh );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_x_planes );
  ar & BOOST_SERIALIZATION_NVP( d_y_planes );
  ar & BOOST_SERIALIZATION_NVP( d_z_planes );
  ar & BOOST_SERIALIZATION_NVP( d_hex_elements );
}

} // end Utility namespace

BOOST_SERIALIZATION_CLASS_VERSION( StructuredHexMesh, Utility, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( StructuredHexMesh, Utility );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, StructuredHexMesh );

#endif // end UTILITY_STRUCTURED_HEX_MESH_HPP

//---------------------------------------------------------------------------//
// end Utility_StructuredHexMesh.hpp
//---------------------------------------------------------------------------//
