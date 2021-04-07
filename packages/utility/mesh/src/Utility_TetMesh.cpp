//---------------------------------------------------------------------------//
//!
//! \file   Utility_TetMesh.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tetrahedral mesh class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/serialization/array_wrapper.hpp>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // This must be included first
#include "Utility_TetMesh.hpp"
#include "Utility_TetrahedronHelpers.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"
#include "FRENSIE_config.hpp"

// Moab Includes
#ifdef HAVE_FRENSIE_MOAB
#include <moab/Interface.hpp>
#include <moab/Core.hpp>
#include <moab/BoundBox.hpp>
#include <moab/AdaptiveKDTree.hpp>
#include <moab/Matrix3.hpp>
#endif // end HAVE_FRENSIE_MOAB

namespace Utility{

/*! The tet mesh implementation class
 *
 * This class is used to hide the moab api from the Utility::TetMesh
 * declaration. Note that all moab::EntityHandle objects will be stored as
 * Utility::Mesh::ElementHandle objects (uint64_t) instead. This is done to
 * ensure that every mesh archive is the same across systems.
 */
class TetMeshImpl
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
  TetMeshImpl( const std::string& input_mesh_file_name,
               const bool verbose_construction,
               const bool display_warnings );

  //! Destructor
  TetMeshImpl()
  { /* ... */ }

  //! Get the start iterator of the tet handle list
  ElementHandleIterator getStartElementHandleIterator() const;

  //! Get the end iterator of the tet handle list
  ElementHandleIterator getEndElementHandleIterator() const;

  //! Get the number of tet elements
  size_t getNumberOfElements() const;

  //! Returns the volumes of each mesh element
  void getElementVolumes( ElementHandleVolumeMap& element_volumes ) const;

  //! Returns the volume of a specific mesh element
  double getElementVolume( ElementHandle element ) const;

  //! Returns the moab interface pointer (obfuscated)
  void* getMoabInterface() const;

  //! Returns the tet meshset
  ElementHandle getTetMeshsetHandle() const;

  //! Check if a point is inside of the mesh
  bool isPointInMesh( const double point[3] ) const;

  //! Returns the tet that contains a given point
  ElementHandle whichElementIsPointIn( const double point[3] ) const;

  //! Determine the mesh elements that a line segment intersects
  void computeTrackLengths( const double start_point[3],
                            const double end_point[3],
                            ElementHandleTrackLengthArray&
                            tet_element_track_lengths ) const;

private:

#ifdef HAVE_FRENSIE_MOAB
  // Create the tet meshset
  void createTetMeshset( moab::Range& all_tet_elements,
                         const bool verbose );

  // Create the kd-tree
  void createKDTree( moab::Range& all_tet_elements,
                     const bool verbose );

#endif // end HAVE_FRENSIE_MOAB

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

#ifdef HAVE_FRENSIE_MOAB

  // The input file that stores the mesh
  std::string d_mesh_input_file;

  // Display warnings
  bool d_display_warnings;

  // The moab instance that stores all mesh data
  std::unique_ptr<moab::Interface> d_moab_interface;

  // The tet meshset
  ElementHandle d_tet_meshset;

  // The root of the kd-tree
  ElementHandle d_kd_tree_root;

  // The kd-tree for finding point in tet
  std::unique_ptr<moab::AdaptiveKDTree> d_kd_tree;

  // The map of tet ids and barycentric coordinate transform matrices
  std::unordered_map<ElementHandle,std::pair<std::array<double,9>,std::array<double,3> > >
  d_tet_barycentric_data;

  // The tet element handles
  std::vector<ElementHandle> d_tets;
#endif // end HAVE_FRENSIE_MOAB
};

// Initialize the static member data
const double TetMeshImpl::s_tol = 1e-6;

} // end Utility namespace

BOOST_CLASS_VERSION( Utility::TetMeshImpl, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TetMeshImpl, Utility );

namespace Utility{

// Default constructor
TetMesh::TetMesh()
{
#ifndef HAVE_FRENSIE_MOAB
  THROW_EXCEPTION( std::logic_error,
                   "A tetrahedral mesh cannot be created because MOAB is not "
                   "enabled!" );
#endif // end HAVE_FRENSIE_MOAB
}

// Constructor
TetMesh::TetMesh( const std::string& input_mesh_file_name,
                  const bool verbose_construction,
                  const bool display_warnings )
  : d_impl( new TetMeshImpl( input_mesh_file_name,
                             verbose_construction,
                             display_warnings ) )
{
#ifndef HAVE_FRENSIE_MOAB
  THROW_EXCEPTION( std::logic_error,
                   "A tetrahedral mesh cannot be created because MOAB is not "
                   "enabled!" );
#endif // end HAVE_FRENSIE_MOAB
}

// Destructor
TetMesh::~TetMesh()
{
  delete d_impl;
}

// Constructor
TetMeshImpl::TetMeshImpl( const std::string& input_mesh_file_name,
                          const bool verbose_construction,
                          const bool display_warnings )
#ifdef HAVE_FRENSIE_MOAB
  : d_mesh_input_file( input_mesh_file_name ),
    d_display_warnings( display_warnings ),
    d_moab_interface( new moab::Core ),
    d_tet_meshset(),
    d_kd_tree_root(),
    d_kd_tree( new moab::AdaptiveKDTree( d_moab_interface.get() ) ),
    d_tet_barycentric_data(),
    d_tets()
#endif // end HAVE_FRENSIE_MOAB
{
#ifdef HAVE_FRENSIE_MOAB
  moab::ErrorCode return_value;

  moab::Range all_tet_elements;

  this->createTetMeshset( all_tet_elements, verbose_construction );

  // Construct the extra tet data
  for( moab::Range::const_iterator tet_handle_it = all_tet_elements.begin();
       tet_handle_it != all_tet_elements.end();
       ++tet_handle_it )
  {
    // Make sure that the tet is valid
    TEST_FOR_EXCEPTION( *tet_handle_it == 0,
                        Utility::MOABException,
                        "An invalid tet element was found!" );

    moab::EntityHandle tet_handle = *tet_handle_it;

    // Add the tet handle to the cached list of element handles
    d_tets.push_back( tet_handle );

    // Extract the vertex data for the given tet
    {
      std::vector<moab::EntityHandle> vertex_handles;

      d_moab_interface->get_connectivity( &tet_handle, 1, vertex_handles );

      // Test that the vertex entity contains four points
      TEST_FOR_EXCEPTION( vertex_handles.size() != 4,
                          Utility::MOABException,
                          "A tet was found with an invalid number of vertices "
                          "(" << vertex_handles.size() << " != 4)" );

      std::array<double,3> vertices[4];

      for( size_t i = 0; i < vertex_handles.size(); ++i )
      {
        d_moab_interface->get_coords( &vertex_handles[i],
                                      1,
                                      vertices[i].data() );
      }

      // Calculate barycentric matrix
      std::pair<std::array<double,9>,std::array<double,3> >&
        tet_barycentric_data = d_tet_barycentric_data[tet_handle];
      Utility::calculateBarycentricTransformMatrix(
                                           vertices[0].data(),
                                           vertices[1].data(),
                                           vertices[2].data(),
                                           vertices[3].data(),
                                           tet_barycentric_data.first.data() );

      // Assign reference vertices (always the fourth vertex)
      tet_barycentric_data.second = vertices[3];
    }
  }

  // Create the kd-tree
  this->createKDTree( all_tet_elements, verbose_construction );
#endif // end HAVE_FRENSIE_MOAB
}

#ifdef HAVE_FRENSIE_MOAB
// Create the tet meshset
void TetMeshImpl::createTetMeshset( moab::Range& all_tet_elements,
                                    const bool verbose_construction )
{
  moab::ErrorCode return_value;

  // Create an empty MOAB meshset
  {
    moab::EntityHandle tmp_tet_meshset;

    return_value = d_moab_interface->create_meshset( moab::MESHSET_SET,
                                                     tmp_tet_meshset );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        Utility::MOABException,
                        moab::ErrorCodeStr[return_value] );

    d_tet_meshset = tmp_tet_meshset;
  }

  if( verbose_construction )
  {
    FRENSIE_LOG_PARTIAL_NOTIFICATION( "Loading tetrahedral mesh from file "
                                      << d_mesh_input_file << " ... " );
  }

  // Populate MOAB meshset with data from input file
  {
    moab::EntityHandle tmp_tet_meshset = d_tet_meshset;

    return_value = d_moab_interface->load_file( d_mesh_input_file.c_str(),
                                                &tmp_tet_meshset );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        Utility::MOABException,
                        moab::ErrorCodeStr[return_value] );
  }

  // Extract the 3D elements from the meshset
  return_value = d_moab_interface->get_entities_by_dimension(
                                          d_tet_meshset, 3, all_tet_elements );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  // Eliminate all but the 3D elements from the meshset
  {
    // Clear the meshset
    moab::EntityHandle tmp_tet_meshset = d_tet_meshset;

    return_value = d_moab_interface->clear_meshset( &tmp_tet_meshset, 1 );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        Utility::MOABException,
                        moab::ErrorCodeStr[return_value] );

    // Reconstruct the meshset using the 3D entities
    return_value = d_moab_interface->add_entities( d_tet_meshset,
                                                   all_tet_elements );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        Utility::MOABException,
                        moab::ErrorCodeStr[return_value] );
  }

  if( verbose_construction )
  {
    FRENSIE_LOG_NOTIFICATION( "done (constructed "
                              << all_tet_elements.size() <<
                              " tetrahedrons)." );
  }
}

// Create the kd-tree
void TetMeshImpl::createKDTree( moab::Range& all_tet_elements,
                                const bool verbose_construction )
{
  // Get the dimension of the input set
  int current_dimension =
    d_moab_interface->dimension_from_handle(all_tet_elements[0]);

  moab::Range surface_triangles;

  // Determine the edges from the input set
  moab::ErrorCode return_value =
    d_moab_interface->get_adjacencies( all_tet_elements,
                                       current_dimension - 1,
                                       true,
                                       surface_triangles,
                                       moab::Interface::UNION );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  all_tet_elements.merge( surface_triangles );

  const char settings[]="MESHSET_FLAGS=0x1;TAG_NAME=0";
  moab::FileOptions fileopts(settings);

  if( verbose_construction )
  {
    FRENSIE_LOG_PARTIAL_NOTIFICATION( "Constructing kd-tree ... " );
  }

  moab::EntityHandle tmp_kd_tree_root;

  d_kd_tree->build_tree( all_tet_elements, &tmp_kd_tree_root, &fileopts );

  d_kd_tree_root = tmp_kd_tree_root;

  if( verbose_construction )
  {
    FRENSIE_LOG_NOTIFICATION( "done." );
  }
}
#endif // end HAVE_FRENSIE_MOAB

// Get the mesh type name
std::string TetMesh::getMeshTypeName() const
{
  return "Tet Mesh";
}

// Get the mesh element type name
std::string TetMesh::getMeshElementTypeName() const
{
  return "Tet";
}

// Get the start iterator of the tet handle list
auto TetMesh::getStartElementHandleIterator() const -> ElementHandleIterator
{
  return d_impl->getStartElementHandleIterator();
}

// Get the start iterator of the tet handle list
auto TetMeshImpl::getStartElementHandleIterator() const -> ElementHandleIterator
{
#ifdef HAVE_FRENSIE_MOAB
  return d_tets.begin();
#else
  return ElementHandleIterator();
#endif
}

// Get the end iterator of the tet handle list
auto TetMesh::getEndElementHandleIterator() const -> ElementHandleIterator
{
  return d_impl->getEndElementHandleIterator();
}

// Get the end iterator of the tet handle list
auto TetMeshImpl::getEndElementHandleIterator() const -> ElementHandleIterator
{
#ifdef HAVE_FRENSIE_MOAB
  return d_tets.end();
#else
  return ElementHandleIterator();
#endif
}

// Get the number of tet elements
size_t TetMesh::getNumberOfElements() const
{
  return d_impl->getNumberOfElements();
}

// Get the number of tet elements
size_t TetMeshImpl::getNumberOfElements() const
{
#ifdef HAVE_FRENSIE_MOAB
  return d_tets.size();
#else
  return 0;
#endif
}

// Returns the volumes of each mesh element
void TetMesh::getElementVolumes( ElementHandleVolumeMap& element_volumes ) const
{
  return d_impl->getElementVolumes( element_volumes );
}

// Returns the volumes of each mesh element
void TetMeshImpl::getElementVolumes( ElementHandleVolumeMap& element_volumes ) const
{
#ifdef HAVE_FRENSIE_MOAB
  for( auto&& element_handle : d_tets )
  {
    element_volumes[element_handle] = this->getElementVolume(element_handle);
  }
#endif // end HAVE_FRENSIE_MOAB
}

// Returns the volume of a specific element
double TetMesh::getElementVolume( ElementHandle element ) const
{
  return d_impl->getElementVolume( element );
}

// Returns the volume of a specific element
double TetMeshImpl::getElementVolume( ElementHandle element ) const
{
#ifdef HAVE_FRENSIE_MOAB
  moab::EntityHandle tet_handle = element;

  // Extract the vertex data for the given tet
  std::vector<moab::EntityHandle> vertex_handles;
  
  d_moab_interface->get_connectivity( &tet_handle, 1, vertex_handles );

  std::array<double,3> vertices[4];

  for( unsigned i = 0; i != vertex_handles.size(); ++i )
  {
    d_moab_interface->get_coords( &vertex_handles[i],
          1,
          vertices[i].data() );
  }

  return Utility::calculateTetrahedronVolume( vertices[0].data(),
                                              vertices[1].data(),
                                              vertices[2].data(),
                                              vertices[3].data() );
#endif
}

// Returns the moab interface pointer (obfuscated)
void* TetMeshImpl::getMoabInterface() const
{
#ifdef HAVE_FRENSIE_MOAB
  return d_moab_interface.get();
#else
  return nullptr;
#endif // end HAVE_FRENSIE_MOAB
}

// Returns the tet meshset
auto TetMeshImpl::getTetMeshsetHandle() const -> ElementHandle
{
#ifdef HAVE_FRENSIE_MOAB
  return d_tet_meshset;
#else
  return 0;
#endif // end HAVE_FRENSIE_MOAB
}

// Check if a point is inside of the mesh
bool TetMesh::isPointInMesh( const double point[3] ) const
{
  return d_impl->isPointInMesh( point );
}

// Check if a point is inside of the mesh
bool TetMeshImpl::isPointInMesh( const double point[3] ) const
{
#ifdef HAVE_FRENSIE_MOAB
  // Find the leaf node that the point is in (if there is one)
  moab::AdaptiveKDTreeIter kd_tree_iteration;

  moab::ErrorCode return_value =
    d_kd_tree->point_search( point, kd_tree_iteration );

  // Check that the leaf actually contains the point (concave mesh)
  if( return_value == moab::MB_SUCCESS && kd_tree_iteration.handle() != 0 )
  {
    moab::EntityHandle leaf_node = kd_tree_iteration.handle();

    moab::Range tets_in_leaf;

    return_value = d_moab_interface->get_entities_by_dimension( leaf_node,
                                                                3,
                                                                tets_in_leaf,
                                                                false );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        Utility::MOABException,
                        moab::ErrorCodeStr[return_value] );

    // Quickly check if the point is likely in one of the tets
    for( moab::Range::const_iterator tet_handle_it = tets_in_leaf.begin();
         tet_handle_it != tets_in_leaf.end();
         ++tet_handle_it )
    {
      const std::pair<std::array<double,9>,std::array<double,3> >&
        tet_barycentric_data = d_tet_barycentric_data.find( *tet_handle_it )->second;

      if( Utility::isPointInTet( point,
                                 tet_barycentric_data.second.data(),
                                 tet_barycentric_data.first.data(),
                                 s_tol ) )
      {
        return true;
      }
    }

    // The point is not in any of the tets in the leaf node
    return false;
  }
  // The point is outside of the mesh bounding box
  else
    return false;
#else // HAVE_FRENSIE_MOAB
  return false;
#endif // end HAVE_FRENSIE_MOAB
}

// Returns the tet that contains a given point
auto TetMesh::whichElementIsPointIn( const double point[3] ) const -> ElementHandle
{
  return d_impl->whichElementIsPointIn( point );
}

// Returns the tet that contains a given point
auto TetMeshImpl::whichElementIsPointIn( const double point[3] ) const -> ElementHandle
{
  // Make sure that the point is in the mesh
  testPrecondition( this->isPointInMesh( point ) );

#ifdef HAVE_FRENSIE_MOAB
  // Find the kd-tree leaf that contains the point
  moab::AdaptiveKDTreeIter kd_tree_iterator;

  moab::ErrorCode return_value = d_kd_tree->point_search( point,
                                                          kd_tree_iterator );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  TEST_FOR_EXCEPTION( kd_tree_iterator.handle() == 0,
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );

  moab::EntityHandle leaf = kd_tree_iterator.handle();
  moab::Range tets_in_leaf;

  return_value = d_moab_interface->get_entities_by_dimension( leaf,
							      3,
							      tets_in_leaf,
							      false );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );

  // A tet must be found since a leaf was found - failure to find a tet
  // indicates a tolerance issue usually
  ElementHandle element_handle = 0;

  for( moab::Range::const_iterator tet_handle_it = tets_in_leaf.begin();
       tet_handle_it != tets_in_leaf.end();
       ++tet_handle_it )
  {
    const std::pair<std::array<double,9>,std::array<double,3> >&
      tet_barycentric_data = d_tet_barycentric_data.find( *tet_handle_it )->second;

    if( Utility::isPointInTet( point,
                               tet_barycentric_data.second.data(),
                               tet_barycentric_data.first.data(),
                               s_tol ) )
    {
      element_handle = *tet_handle_it;

      break;
    }
  }

  // Make sure that the tet has been found
  if( element_handle == 0 && d_display_warnings )
  {
    FRENSIE_LOG_TAGGED_WARNING( "TetMesh",
                                "The tetrahedron containing point {"
                                << point[0] << "," << point[1] << ","
                                << point[2] << "} could not be found ("
                                << tets_in_leaf.size() << " tets in leaf)!" );
  }

  // Make sure that the leaf is valid
  testPostcondition( tets_in_leaf.size() > 0 );

  return element_handle;
#else // HAVE_FRENSIE_MOAB
  return 0;
#endif // end HAVE_FRENSIE_MOAB
}

// Determine the mesh elements that a line segment intersects
void TetMesh::computeTrackLengths( const double start_point[3],
                                   const double end_point[3],
                                   ElementHandleTrackLengthArray&
                                   tet_element_track_lengths ) const
{
  d_impl->computeTrackLengths( start_point,
                               end_point,
                               tet_element_track_lengths );
}

// Determine the mesh elements that a line segment intersects
void TetMeshImpl::computeTrackLengths( const double start_point[3],
                                       const double end_point[3],
                                       ElementHandleTrackLengthArray&
                                       tet_element_track_lengths ) const
{
#ifdef HAVE_FRENSIE_MOAB
  // Calculate the direction and determine the track length
  double direction[3] = {end_point[0]-start_point[0],
                         end_point[1]-start_point[1],
                         end_point[2]-start_point[2]};

  double track_length =
    Utility::normalizeVectorAndReturnMagnitude( direction );

  // Determine the distances to intersections with mesh elements
  std::vector<double> ray_tet_intersections;
  std::vector<moab::EntityHandle> tet_surface_triangles;

  moab::ErrorCode return_value =
    d_kd_tree->ray_intersect_triangles( d_kd_tree_root,
                                        s_tol,
                                        direction,
                                        start_point,
                                        tet_surface_triangles,
                                        ray_tet_intersections,
                                        0,
                                        track_length );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  // Clear the tet surface triangles - not used
  tet_surface_triangles.clear();

  // Reset the tet element track lengths
  tet_element_track_lengths.clear();

  if( ray_tet_intersections.size() > 0 )
  {
    // Sort all intersections of the ray with the tets
    std::sort( ray_tet_intersections.begin(),
               ray_tet_intersections.end() );

    // Remove the first intersection if it is zero (start point on surface)
    if( ray_tet_intersections.front() == 0.0 )
      ray_tet_intersections.erase( ray_tet_intersections.begin() );

    // Calculate the tet intersection points and partial track lengths
    std::vector<moab::CartVect> array_of_hit_points;

    // Add the origin point
    {
      moab::CartVect start_point_cv( start_point[0],
                                     start_point[1],
                                     start_point[2] );

      array_of_hit_points.push_back( start_point_cv );
    }

    // Add all intermediate points
    for( size_t i = 0; i < ray_tet_intersections.size(); ++i )
    {
      moab::CartVect hit_point;

      hit_point[0] = direction[0]*ray_tet_intersections[i]
        + start_point[0];
      hit_point[1] = direction[1]*ray_tet_intersections[i]
        + start_point[1];
      hit_point[2] = direction[2]*ray_tet_intersections[i]
        + start_point[2];

      array_of_hit_points.push_back( hit_point );
    }

    // Add the end point (don't add if the end point lies on the surface)
    if( ray_tet_intersections.back() < track_length )
    {
      moab::CartVect end_point_cv(end_point[0], end_point[1], end_point[2]);

      array_of_hit_points.push_back( end_point_cv );

      ray_tet_intersections.push_back( track_length );
    }

    // Determine the tet that each line segment passes through
    for( size_t i = 0; i < ray_tet_intersections.size(); ++i )
    {
      moab::CartVect tet_centroid =
        (array_of_hit_points[i+1] + array_of_hit_points[i])/2.0;

      // Check that the centroid falls in the mesh - if the mesh is concave
      // it is possible that it falls outside
      if( this->isPointInMesh( tet_centroid.array() ) )
      {
        ElementHandle element_handle =
          this->whichElementIsPointIn( tet_centroid.array() );

        // Make sure that a tet was found (tolerance issue may prevent this)
        if( element_handle == 0 )
          continue;

        double tet_track_length;

        if( i != 0 )
        {
          tet_track_length = ray_tet_intersections[i] -
            ray_tet_intersections[i-1];
        }
        else
          tet_track_length = ray_tet_intersections[i];

        tet_element_track_lengths.push_back( std::make_tuple(
                           element_handle,
                           std::array<double,3>( {array_of_hit_points[i][0],
                                                  array_of_hit_points[i][1],
                                                  array_of_hit_points[i][2]} ),
                           tet_track_length ) );
      }
    }
  }

  // Handle the cases where there are no intersections
  else
  {
    double mid_point[3] = {(end_point[0]+start_point[0])/2,
                           (end_point[1]+start_point[1])/2,
                           (end_point[2]+start_point[2])/2};

    // case 1: line segment is entirely in one tet
    if( this->isPointInMesh( mid_point ) )
    {
      ElementHandle element_handle = this->whichElementIsPointIn( mid_point );

      if( element_handle != 0 )
      {
        tet_element_track_lengths.push_back( std::make_tuple(
                                      element_handle,
                                      std::array<double,3>( {start_point[0],
                                                             start_point[1],
                                                             start_point[2]} ),
                                      track_length ) );
      }
    }

    // case 2: track entirely misses mesh - do nothing
  }
#endif // end HAVE_FRENSIE_MOAB
}

// Export the mesh to a vtk file (type determined by suffix - e.g. mesh.vtk)
void TetMesh::exportData( const std::string& output_file_name,
                          const TagNameSet& tag_root_names,
                          const MeshElementHandleDataMap& mesh_tag_data ) const
{
#ifdef HAVE_FRENSIE_MOAB
  this->exportDataImpl( output_file_name,
                        tag_root_names,
                        mesh_tag_data,
                        d_impl->getMoabInterface(),
                        d_impl->getTetMeshsetHandle(),
                        [](const ElementHandle tet_handle){return tet_handle;} );
#endif // end HAVE_FRENSIE_MOAB
}

// Save the data to an archive
template<typename Archive>
void TetMesh::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Mesh );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_impl );
}

// Save the data to an archive
template<typename Archive>
void TetMeshImpl::save( Archive& ar, const unsigned version ) const
{
#ifdef HAVE_FRENSIE_MOAB
  ar & BOOST_SERIALIZATION_NVP( d_mesh_input_file );
  ar & BOOST_SERIALIZATION_NVP( d_display_warnings );
  ar & BOOST_SERIALIZATION_NVP( d_tet_barycentric_data );
  ar & BOOST_SERIALIZATION_NVP( d_tets );
#endif // end HAVE_FRENSIE_MOAB
}

// Load the data from an archive
template<typename Archive>
void TetMesh::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Mesh );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_impl );
}

// Load the data from an archive
template<typename Archive>
void TetMeshImpl::load( Archive& ar, const unsigned version )
{
#ifdef HAVE_FRENSIE_MOAB
  ar & BOOST_SERIALIZATION_NVP( d_mesh_input_file );
  ar & BOOST_SERIALIZATION_NVP( d_display_warnings );
  ar & BOOST_SERIALIZATION_NVP( d_tet_barycentric_data );
  ar & BOOST_SERIALIZATION_NVP( d_tets );

  // Initialize the moab interface
  d_moab_interface.reset( new moab::Core );

  // Reconstruct the tet meshset
  moab::Range all_tet_elements;

  this->createTetMeshset( all_tet_elements, false );

  // Initialize the kd-tree
  d_kd_tree.reset( new moab::AdaptiveKDTree( d_moab_interface.get() ) );

  // Reconstruct the kd-tree
  this->createKDTree( all_tet_elements, false );

  // Verify that the entity handles haven't changed
  for( auto&& cached_element_handle : d_tets )
  {
    TEST_FOR_EXCEPTION( all_tet_elements.find( cached_element_handle ) ==
                        all_tet_elements.end(),
                        std::runtime_error,
                        "The tet mesh cannot be loaded from the archive "
                        "because the moab::EntityHandles have changed!" );
  }
#endif // end HAVE_FRENSIE_MOAB
}

} // end Utility namespace

BOOST_CLASS_EXPORT_IMPLEMENT( Utility::TetMeshImpl );
BOOST_CLASS_EXPORT_IMPLEMENT( Utility::TetMesh );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::TetMesh );

//---------------------------------------------------------------------------//
// end Utility_TetMesh.cpp
//---------------------------------------------------------------------------//
