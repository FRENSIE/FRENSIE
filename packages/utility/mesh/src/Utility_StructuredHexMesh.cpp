//---------------------------------------------------------------------------//
//!
//! \file   Utility_StructuredHexMesh.cpp
//! \author Philip Britt
//! \brief  Hexahedron mesh storage class
//!
//---------------------------------------------------------------------------//

//std includes
#include <math.h>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // This must be included first
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "FRENSIE_config.hpp"

// Moab Includes
#ifdef HAVE_FRENSIE_MOAB
#include <moab/Core.hpp>
#include <moab/ScdInterface.hpp>
#endif // end HAVE_FRENSIE_MOAB

namespace Utility{

// Initialize static member data
const double StructuredHexMesh::s_tol = 1e-12;

// Default constructor
StructuredHexMesh::StructuredHexMesh()
{ /* ... */ }

// Constructor
StructuredHexMesh::StructuredHexMesh( const std::vector<double>& x_planes,
                                      const std::vector<double>& y_planes,
                                      const std::vector<double>& z_planes)
  : d_x_planes( x_planes ),
    d_y_planes( y_planes ),
    d_z_planes( z_planes ),
    d_hex_elements( (x_planes.size()-1)*(y_planes.size()-1)*(z_planes.size()-1) )
{
  // Test for at least 2 planes
  testPrecondition(x_planes.size()>=2);
  testPrecondition(y_planes.size()>=2);
  testPrecondition(z_planes.size()>=2);
  // Make sure that the planes are in increasing sequential order
  testPrecondition( Sort::isSortedAscending( x_planes.begin(),
                                             x_planes.end() ) );
  testPrecondition( Sort::isSortedAscending( y_planes.begin(),
                                             y_planes.end() ) );
  testPrecondition( Sort::isSortedAscending( z_planes.begin(),
                                             z_planes.end() ) );
  // Form the list of hex element indices
  for( size_t k = 0; k < d_z_planes.size()-1; ++k )
  {
    for( size_t j = 0; j < d_y_planes.size()-1; ++j )
    {
      for( size_t i = 0; i < d_x_planes.size()-1; ++i )
      {
        size_t index = this->findIndex( i, j, k);

        d_hex_elements[index] = index;
      }
    }
  }

#ifndef HAVE_FRENSIE_MOAB
  FRENSIE_LOG_TAGGED_WARNING( "StructuredHexMesh",
                              "Cannot export mesh data to vtk because moab "
                              "has not been enabled!" );
#endif // end HAVE_FRENSIE_MOAB
}

// Get the mesh type name
std::string StructuredHexMesh::getMeshTypeName() const
{
  return "Structured Hex Mesh";
}

// Get the mesh element type name
std::string StructuredHexMesh::getMeshElementTypeName() const
{
  return "Hex";
}

// Deconstruct a hex index into indices of planes on each dimension.
/*! \details This method is used primarily with moab since the moab
 * methods used in the estimator class require the parameter space over
 * all three dimensions to form a structured mesh .
 */
void StructuredHexMesh::getHexPlaneIndices(
                                       const ElementHandle h,
                                       size_t hex_parameter_indices[3] ) const
{
  // Make sure that the hex index is valid
  testPrecondition( h >= 0 && h < d_hex_elements.size() );

  size_t x_size = (d_x_planes.size() - 1);
  size_t y_size = (d_y_planes.size() - 1);

  hex_parameter_indices[2] = h/(x_size*y_size);
  hex_parameter_indices[1] = (h - hex_parameter_indices[2] * x_size * y_size) / x_size;
  hex_parameter_indices[0] = h - hex_parameter_indices[1] * x_size - hex_parameter_indices[2] * x_size * y_size;
}

// Returns the volumes of the hex elements for the estimator class.
void StructuredHexMesh::getElementVolumes(
                                    ElementHandleVolumeMap& element_volumes ) const
{
  element_volumes.clear();

  for( PlaneIndex k = 0; k < d_z_planes.size() - 1; ++k)
  {
    for( PlaneIndex j = 0; j < d_y_planes.size() - 1; ++j)
    {
      for( PlaneIndex i = 0; i < d_x_planes.size() - 1; ++i)
      {
        element_volumes[ this->findIndex(i, j, k) ] =
          (d_x_planes[i + 1] - d_x_planes[i])*
          (d_y_planes[j + 1] - d_y_planes[j])*
          (d_z_planes[k + 1] - d_z_planes[k]);
      }
    }
  }
}

// Returns the volume of a specific mesh element
double StructuredHexMesh::getElementVolume( ElementHandle element ) const
{
  size_t plane_indices [3];
  this->getHexPlaneIndices(element, plane_indices);

  return (d_x_planes[plane_indices[0]+1] - d_x_planes[plane_indices[0]]) *
         (d_y_planes[plane_indices[1]+1] - d_y_planes[plane_indices[1]]) *
         (d_z_planes[plane_indices[2]+1] - d_z_planes[plane_indices[2]]);
}

// Returns a bool that says whether or not a point is in the mesh.
bool StructuredHexMesh::isPointInMesh( const double point[3] ) const
{

  if( d_x_planes.front() <= point[X_DIMENSION] && point[X_DIMENSION] <= d_x_planes.back() )
  {
    if( d_y_planes.front() <= point[Y_DIMENSION] && point[Y_DIMENSION] <= d_y_planes.back() )
    {
      if(d_z_planes.front() <= point[Z_DIMENSION] && point[Z_DIMENSION] <= d_z_planes.back() )
      {
        return true;
      }
    }
  }

  return false;
}

// Returns the index of the hex that contains a given point.
auto StructuredHexMesh::whichElementIsPointIn( const double point[3] ) const -> ElementHandle
{
  // Make sure that the point is in the mesh
  testPrecondition( this->isPointInMesh(point) );

  size_t x_index = Search::binaryLowerBoundIndex( d_x_planes.begin(),
                                                  d_x_planes.end(),
                                                  point[X_DIMENSION] );

  // Take care of when the point is exactly on the last x plane. The search
  // will return the last x plane if this is true which does not correspond to
  // any of the hex elements. Instead, move it back one
  if( x_index == d_x_planes.size() - 1)
  {
    x_index = d_x_planes.size() - 2;
  }

  size_t y_index = Search::binaryLowerBoundIndex( d_y_planes.begin(),
                                                  d_y_planes.end(),
                                                  point[Y_DIMENSION] );
  if( y_index == d_y_planes.size() - 1)
  {
    y_index = d_y_planes.size() - 2;
  }

  size_t z_index = Search::binaryLowerBoundIndex( d_z_planes.begin(),
                                                  d_z_planes.end(),
                                                  point[Z_DIMENSION] );
  if( z_index == d_z_planes.size() - 1)
  {
    z_index = d_z_planes.size() - 2;
  }

  return this->findIndex( x_index, y_index, z_index );
}

// Returns an array of pairs of hex IDs and partial track lengths along a given line segment
void StructuredHexMesh::computeTrackLengths(
               const double start_point[3],
               const double end_point[3],
               ElementHandleTrackLengthArray& hex_element_track_lengths ) const
{
  hex_element_track_lengths.clear();

  if( !(start_point[X_DIMENSION] == end_point[X_DIMENSION] &&
        start_point[Y_DIMENSION] == end_point[Y_DIMENSION] &&
        start_point[Z_DIMENSION] == end_point[Z_DIMENSION]) )
  {
    // Calculate track length and direction unit vector
    double direction[3] {end_point[X_DIMENSION] - start_point[X_DIMENSION],
                         end_point[Y_DIMENSION] - start_point[Y_DIMENSION],
                         end_point[Z_DIMENSION] - start_point[Z_DIMENSION]};

    double track_length =
      Utility::normalizeVectorAndReturnMagnitude( direction );

    double current_point[3] { start_point[X_DIMENSION],
                              start_point[Y_DIMENSION],
                              start_point[Z_DIMENSION] };

    // Test if point starts in mesh. If not, figure out if it interacts with mesh
    if( !this->isPointInMesh(current_point) )
    {
      // First member of pair is whether the mesh was intersected,
      // second member of pair is the distance to the intersection
      std::tuple<bool,Dimension,double> ray_intersection_tuple;

      this->doesRayIntersectMesh( current_point,
                                  direction,
                                  track_length,
                                  ray_intersection_tuple );

      if( std::get<0>( ray_intersection_tuple ) )
      {
        this->pushPoint( current_point,
                         direction,
                         std::get<2>( ray_intersection_tuple ) );

        PlaneIndex hex_plane_indices[3];
        this->setHexPlaneIndices( std::get<1>( ray_intersection_tuple ),
                                  current_point,
                                  hex_plane_indices );

        this->traceThroughMesh( current_point,
                                direction,
                                track_length - std::get<2>( ray_intersection_tuple ),
                                hex_plane_indices,
                                hex_element_track_lengths );
      }
    }
    else
    {
      PlaneIndex hex_plane_indices[3];
      this->setHexPlaneIndices( current_point, hex_plane_indices );

      this->traceThroughMesh( current_point,
                              direction,
                              track_length,
                              hex_plane_indices,
                              hex_element_track_lengths );
    }
  }
}

// Get the start iterator of the hex element list.
/*! \details returns the iterator that points to the first element in the list
 * containing all of the hex ID elements.
 */
auto StructuredHexMesh::getStartElementHandleIterator() const -> ElementHandleIterator
{
  return d_hex_elements.begin();
}

// Get the end iterator of the hex element list.
/*! \details returns the iterator that points to one beyond the last element in
 * the list containing all of the hex ID elements.
 */
auto StructuredHexMesh::getEndElementHandleIterator() const -> ElementHandleIterator
{
  return d_hex_elements.end();
}

// Get the number of mesh elements
size_t StructuredHexMesh::getNumberOfElements() const
{
  return d_hex_elements.size();
}

// Get the number of planes on the X axis.
size_t StructuredHexMesh::getNumberOfXPlanes() const
{
  return d_x_planes.size();
}

// Get the number of planes on the Y axis.
size_t StructuredHexMesh::getNumberOfYPlanes() const
{
  return d_y_planes.size();
}

// Get the number of planes on the Z axis.
size_t StructuredHexMesh::getNumberOfZPlanes() const
{
  return d_z_planes.size();
}

// Get the location of a specific plane on the x axis.
double StructuredHexMesh::getXPlaneLocation( PlaneIndex i ) const
{
  //Make sure plane index is valid
  testPrecondition( i < d_x_planes.size() && i >= 0);

  return d_x_planes[i];
}

// Get the location of a specific plane on the y axis.
double StructuredHexMesh::getYPlaneLocation( PlaneIndex i ) const
{
  // Make sure plane index is valid
  testPrecondition( i < d_y_planes.size() && i >= 0);

  return d_y_planes[i];
}

// Get the location of a specific plane on the z axis.
double StructuredHexMesh::getZPlaneLocation( PlaneIndex i)const
{
  // Make sure plane index is valid
  testPrecondition( i < d_z_planes.size() && i >= 0);

  return d_z_planes[i];
}

// Begin private functions

// Returns a pair where the first member is true if the ray intersects with the mesh and the second is the distance to the intersection point
void
StructuredHexMesh::doesRayIntersectMesh(
                   const double point[3],
                   const double direction[3],
                   const double track_length,
                   std::tuple<bool,Dimension,double>& intersection_data ) const
{
  // This method should only be used when the point starts outside of mesh
  testPrecondition( !(this->isPointInMesh(point)) );
  // Make sure direction vector is a unit vector
  testPrecondition( Utility::isUnitVector( direction ) );

  // Initialize the intersection data
  Utility::get<0>( intersection_data ) = false;
  Utility::get<1>( intersection_data ) = X_DIMENSION;
  Utility::get<2>( intersection_data ) = 0.0;

  std::vector<std::pair<Dimension,double> > bounding_plane_distance_set;

  this->findBoundingInteractionPlaneDistances( point,
                                               direction,
                                               bounding_plane_distance_set );

  // Check whether there are any possible bounding planes to intersect with
  if( bounding_plane_distance_set.size() > 0 )
  {
    for( size_t i = 0; i < bounding_plane_distance_set.size(); ++i )
    {
      // If the distance is greater than the track length, skip it
      if( bounding_plane_distance_set[i].second >= track_length )
        continue;

      double new_point[3] { point[X_DIMENSION],
                            point[Y_DIMENSION],
                            point[Z_DIMENSION] };

      // Push point up to plane intersection point
      this->pushPoint( new_point,
                       direction,
                       bounding_plane_distance_set[i].second );

      // Check if the point is on the mesh surface
      if( this->isPointOnMeshSurface( new_point, bounding_plane_distance_set[i].first ) )
      {
        Utility::get<0>( intersection_data ) = true;

        Utility::get<1>( intersection_data ) =
          bounding_plane_distance_set[i].first;

        Utility::get<2>( intersection_data ) =
          bounding_plane_distance_set[i].second;

        break;
      }
    }
  }
}

// Trace particle path through mesh until it dies or leaves mesh
void StructuredHexMesh::traceThroughMesh(
               double point[3],
               const double direction[3],
               const double track_length,
               PlaneIndex hex_plane_indices[3],
               ElementHandleTrackLengthArray& hex_element_track_lengths ) const
{
  std::vector<std::pair<Dimension,PlaneIndex> > interaction_planes;
  this->findInteractionPlanes( point,
                               direction,
                               hex_plane_indices,
                               interaction_planes );

  double iteration_distance = 0;

  size_t incrementer[3];
  this->setIncrementer( incrementer, direction );

  bool continue_tracing = true;

  while(continue_tracing)
  {
    std::pair<Dimension, double> intersection_distance;
    this->findIntersectionDistance( point,
                                    direction,
                                    interaction_planes,
                                    intersection_distance );
    double partial_track_length;

    // Check if track length is exhausted
    if( track_length <= iteration_distance + intersection_distance.second )
    {
      partial_track_length = track_length - iteration_distance;
      continue_tracing = false;
    }
    else
    {
      partial_track_length = intersection_distance.second;
    }

    // Push back a new pair for the indices
    hex_element_track_lengths.push_back(
       std::make_tuple( this->findIndex( hex_plane_indices ),
                        std::array<double,3>( {point[0], point[1], point[2]} ),
                        partial_track_length ) );

    // Check if the particle left the mesh
    if( this->didParticleLeaveMesh( intersection_distance.first,
                                    interaction_planes ) )
    {
      continue_tracing = false;
    }

    // If the track length was exhausted or the particle left the mesh, leave
    // loop and return array.
    if( continue_tracing )
    {
      // Otherwise, push point up to new location
      this->pushPoint(point, direction, partial_track_length);

      // Increase iteration_distance to new value
      iteration_distance += partial_track_length;

      // Increment indices and perform calculation again.
      hex_plane_indices[intersection_distance.first] +=
        incrementer[intersection_distance.first];

      for( size_t i = 0; i < interaction_planes.size() ; ++i )
      {
        if(interaction_planes[i].first == intersection_distance.first)
        {
          interaction_planes[i].second +=
            incrementer[interaction_planes[i].first];

          break;
        }
      }
    }
  }
}

// Find the interaction planes that a particle will interact with
void StructuredHexMesh::findInteractionPlanes(
      const double point[3],
      const double direction[3],
      const PlaneIndex hex_plane_indices[3],
      std::vector<std::pair<Dimension,PlaneIndex> >& interaction_planes ) const
{
  // Make sure that the point is in the mesh
  testPrecondition( this->isPointInMesh( point ) );

  for( size_t i = X_DIMENSION; i <= Z_DIMENSION; ++i)
  {
    if( direction[i] < 0 )
    {
      interaction_planes.push_back( std::make_pair( static_cast<Dimension>(i), hex_plane_indices[i] ) );
    }
    else if( direction[i] > 0)
    {
      interaction_planes.push_back( std::make_pair( static_cast<Dimension>(i), hex_plane_indices[i] + 1) );
    }
  }
}

// Find the intersection distance along the path of the particle with the next hex
void StructuredHexMesh::findIntersectionDistance(
                           const double point[3],
                           const double direction[3],
                           const std::vector<std::pair<Dimension,PlaneIndex> >&
                           interaction_planes,
                           std::pair<Dimension,double>&
                           intersection_distance ) const
{
  // Make sure that the point is in the mesh
  testPrecondition( this->isPointInMesh(point) );
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( direction ) );

  intersection_distance.second = std::numeric_limits<double>::infinity();

  double possible_distance;

  for( size_t i = 0; i < interaction_planes.size(); ++i )
  {
    if(interaction_planes[i].first == X_DIMENSION)
    {
      possible_distance = this->findDistanceToInteractionPlane(
                                    d_x_planes[ interaction_planes[i].second ],
                                    point[X_DIMENSION],
                                    direction[X_DIMENSION] );

      if( possible_distance < intersection_distance.second )
      {
        intersection_distance.first = X_DIMENSION;
        intersection_distance.second = possible_distance;
      }
    }
    else if(interaction_planes[i].first == Y_DIMENSION)
    {
      possible_distance = this->findDistanceToInteractionPlane(
                                    d_y_planes[ interaction_planes[i].second ],
                                    point[Y_DIMENSION],
                                    direction[Y_DIMENSION] );

      if( possible_distance < intersection_distance.second )
      {
        intersection_distance.first = Y_DIMENSION;
        intersection_distance.second = possible_distance;
      }
    }
    else if(interaction_planes[i].first == Z_DIMENSION)
    {
      possible_distance = this->findDistanceToInteractionPlane(
                                    d_z_planes[ interaction_planes[i].second ],
                                    point[Z_DIMENSION],
                                    direction[Z_DIMENSION] );

      if( possible_distance < intersection_distance.second )
      {
        intersection_distance.first = Z_DIMENSION;
        intersection_distance.second = possible_distance;
      }
    }
  }
}

// Calculate distance to a plane from a ray along its direction
double StructuredHexMesh::findDistanceToInteractionPlane(
                                       const double interaction_plane_location,
                                       const double position_component,
                                       const double direction_component ) const
{
  return (interaction_plane_location - position_component)/direction_component;
}

// Form the incrementer so that the particle increments over the planes in the correct direction
void StructuredHexMesh::setIncrementer( size_t incrementer[3],
                                        const double direction[3] ) const
{
  for(size_t i = 0; i < 3; ++i)
  {
    if(direction[i] >= 0)
    {
      incrementer[i] = 1;
    }
    else
    {
      incrementer[i] = -1;
    }
  }
}

// Overloaded method to set the hex plane indices of a given particle
void StructuredHexMesh::setHexPlaneIndices(
                                        const double current_point[3],
                                        PlaneIndex hex_plane_indices[3] ) const
{
  // Make sure that the point is in the mesh
  testPrecondition( this->isPointInMesh(current_point) );

  hex_plane_indices[X_DIMENSION] =
    this->setHexPlaneIndex( current_point[X_DIMENSION], d_x_planes, X_DIMENSION );
  hex_plane_indices[Y_DIMENSION] =
    this->setHexPlaneIndex( current_point[Y_DIMENSION], d_y_planes, Y_DIMENSION );
  hex_plane_indices[Z_DIMENSION] =
    this->setHexPlaneIndex( current_point[Z_DIMENSION], d_z_planes, Z_DIMENSION );

  testPostcondition( hex_plane_indices[X_DIMENSION] >= 0 && hex_plane_indices[X_DIMENSION] <= d_x_planes.size()-2);
  testPostcondition( hex_plane_indices[Y_DIMENSION] >= 0 && hex_plane_indices[Y_DIMENSION] <= d_y_planes.size()-2);
  testPostcondition( hex_plane_indices[Z_DIMENSION] >= 0 && hex_plane_indices[Z_DIMENSION] <= d_z_planes.size()-2);
}

// Set hex plane indices for a particle at its intersection point
void StructuredHexMesh::setHexPlaneIndices(
                                        const Dimension intersection_dimension,
                                        const double current_point[3],
                                        PlaneIndex hex_plane_indices[3] ) const
{
  // Check which dimension was intersected
  if( intersection_dimension == X_DIMENSION )
  {
    /*
      Check which bounding plane of that intersection was intersected. If not the
      first plane, then it must have been the other.
    */

    if( current_point[X_DIMENSION] <= d_x_planes.front() + s_tol &&
        current_point[X_DIMENSION] >= d_x_planes.front() - s_tol )
    {
      hex_plane_indices[X_DIMENSION] = 0;
    }
    else
    {
      hex_plane_indices[X_DIMENSION] = d_x_planes.size() - 2;
    }
    hex_plane_indices[Y_DIMENSION] =
      this->setHexPlaneIndex( current_point[Y_DIMENSION], d_y_planes, Y_DIMENSION);
    hex_plane_indices[Z_DIMENSION] =
      this->setHexPlaneIndex( current_point[Z_DIMENSION], d_z_planes, Z_DIMENSION);
  }
  else if( intersection_dimension == Y_DIMENSION )
  {
    if( current_point[Y_DIMENSION] <= d_y_planes.front() + s_tol &&
        current_point[Y_DIMENSION] >= d_y_planes.front() - s_tol )
    {
      hex_plane_indices[Y_DIMENSION] = 0;
    }
    else
    {
      hex_plane_indices[Y_DIMENSION] = d_y_planes.size() - 2;
    }
    hex_plane_indices[X_DIMENSION] =
      this->setHexPlaneIndex( current_point[X_DIMENSION], d_x_planes, X_DIMENSION);
    hex_plane_indices[Z_DIMENSION] =
      this->setHexPlaneIndex( current_point[Z_DIMENSION], d_z_planes, Z_DIMENSION);

  }
  else if( intersection_dimension == Z_DIMENSION )
  {
    if( current_point[Z_DIMENSION] <= d_z_planes.front() + s_tol &&
        current_point[Z_DIMENSION] >= d_z_planes.front() - s_tol )
    {
      hex_plane_indices[Z_DIMENSION] = 0;
    }
    else
    {
      hex_plane_indices[Z_DIMENSION] = d_z_planes.size() - 2;
    }
    hex_plane_indices[X_DIMENSION] =
      this->setHexPlaneIndex( current_point[X_DIMENSION], d_x_planes, X_DIMENSION);
    hex_plane_indices[Y_DIMENSION] =
      this->setHexPlaneIndex( current_point[Y_DIMENSION], d_y_planes, Y_DIMENSION);
  }

  testPostcondition( hex_plane_indices[X_DIMENSION] >= 0 && hex_plane_indices[X_DIMENSION] <= d_x_planes.size()-2);
  testPostcondition( hex_plane_indices[Y_DIMENSION] >= 0 && hex_plane_indices[Y_DIMENSION] <= d_y_planes.size()-2);
  testPostcondition( hex_plane_indices[Z_DIMENSION] >= 0 && hex_plane_indices[Z_DIMENSION] <= d_z_planes.size()-2);
}

// Set individual hex plane indices for particle.
auto StructuredHexMesh::setHexPlaneIndex(
                         const double position_component,
                         const std::vector<double>& plane_set,
                         const Dimension plane_dimension  ) const -> PlaneIndex
{
  PlaneIndex hex_plane_index;

  if( position_component == plane_set.back() )
  {
    hex_plane_index = plane_set.size() - 2;
  }
  else
  {
    hex_plane_index = Search::binaryLowerBoundIndex( plane_set.begin(),
                                                     plane_set.end(),
                                                     position_component );
  }

  return hex_plane_index;
}

// Returns a set of distances to up to 3 planes that bound the mesh which the particle may interact with
void StructuredHexMesh::findBoundingInteractionPlaneDistances(
  const double point[3],
  const double direction[3],
  std::vector<std::pair<Dimension,double> >& bounding_intersection_data ) const
{
  this->checkPlaneSet( d_x_planes,
                       point[X_DIMENSION],
                       direction[X_DIMENSION],
                       bounding_intersection_data,
                       X_DIMENSION );

  this->checkPlaneSet( d_y_planes,
                       point[Y_DIMENSION],
                       direction[Y_DIMENSION],
                       bounding_intersection_data,
                       Y_DIMENSION );

  this->checkPlaneSet( d_z_planes,
                       point[Z_DIMENSION],
                       direction[Z_DIMENSION],
                       bounding_intersection_data,
                       Z_DIMENSION );
}

// Checks an individual set of planes for interaction plane in that dimension
void StructuredHexMesh::checkPlaneSet(
                   const std::vector<double>& plane_set,
                   const double position_component,
                   const double direction_component,
                   std::vector<std::pair<Dimension, double> >& boundary_planes,
                   const Dimension plane_dimension ) const
{
  if( position_component < plane_set.front() && direction_component > 0 )
  {
    boundary_planes.push_back( std::make_pair(plane_dimension,
                                              (plane_set.front() - position_component)/direction_component) );
  }
  else if( position_component > plane_set.back() && direction_component < 0 )
  {
    boundary_planes.push_back( std::make_pair( plane_dimension,
                                               (plane_set.back() - position_component)/direction_component ) );
  }
}

// Returns whether or not a particle actually hit the mesh surface
bool StructuredHexMesh::isPointOnMeshSurface(
                                  const double point[3],
                                  const Dimension dimension_intersected ) const
{
  bool point_on_mesh = false;

  if(dimension_intersected == X_DIMENSION)
  {
    if(this->checkWithinBoundingPlane( point[Y_DIMENSION], d_y_planes ) )
    {
      if(this->checkWithinBoundingPlane( point[Z_DIMENSION], d_z_planes ) )
      {
        point_on_mesh = true;
      }
    }
  }
  else if(dimension_intersected == Y_DIMENSION)
  {
    if(this->checkWithinBoundingPlane( point[X_DIMENSION], d_x_planes ) )
    {
      if(this->checkWithinBoundingPlane( point[Z_DIMENSION], d_z_planes ) )
      {
        point_on_mesh = true;
      }
    }
  }
  else if(dimension_intersected == Z_DIMENSION)
  {
    if(this->checkWithinBoundingPlane( point[X_DIMENSION], d_x_planes ) )
    {
      if(this->checkWithinBoundingPlane( point[Y_DIMENSION], d_y_planes ) )
      {
        point_on_mesh = true;
      }
    }
  }
  return point_on_mesh;
}

// Function for checking each individual plane to see if it is within bounds
bool StructuredHexMesh::checkWithinBoundingPlane(
                                   const double position_component,
                                   const std::vector<double>& plane_set ) const
{
  if( plane_set.front() <= position_component &&
      position_component <= plane_set.back() )
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Pushes point along direction to new intersection point
void StructuredHexMesh::pushPoint( double point[3],
                                   const double direction[3],
                                   const double push_distance ) const
{
  point[X_DIMENSION] += direction[X_DIMENSION]*push_distance;
  point[Y_DIMENSION] += direction[Y_DIMENSION]*push_distance;
  point[Z_DIMENSION] += direction[Z_DIMENSION]*push_distance;
}

// Return whether or not a particle has exited the mesh
bool StructuredHexMesh::didParticleLeaveMesh(
                           Dimension intersection_dimension,
                           const std::vector<std::pair<Dimension,PlaneIndex> >&
                           interaction_planes ) const
{
  bool exit_mesh = false;

  for( size_t i = 0; i < interaction_planes.size(); ++i )
  {
    if( intersection_dimension == interaction_planes[i].first &&
        intersection_dimension == X_DIMENSION )
    {
      if( interaction_planes[i].second == d_x_planes.size() - 1 ||
          interaction_planes[i].second == 0 )
      {
        exit_mesh = true;
      }
    }
    if( intersection_dimension == interaction_planes[i].first &&
        intersection_dimension == Y_DIMENSION )
    {
      if( interaction_planes[i].second == d_y_planes.size() - 1 ||
          interaction_planes[i].second == 0 )
      {
        exit_mesh = true;
      }
    }
    if( intersection_dimension == interaction_planes[i].first &&
        intersection_dimension == Z_DIMENSION )
    {
      if( interaction_planes[i].second == d_z_planes.size() - 1 ||
          interaction_planes[i].second == 0 )
      {
        exit_mesh = true;
      }
    }
  }

  return exit_mesh;
}

// Calculate hex index from respective plane indices
size_t StructuredHexMesh::findIndex( const size_t i,
                                     const size_t j,
                                     const size_t k ) const
{
  return i +
         j * (d_x_planes.size()-1) +
         k * (d_x_planes.size()-1) * (d_y_planes.size()-1);
}

// Compute hex index from plane indices
size_t StructuredHexMesh::findIndex( const size_t indices[3] ) const
{
  return this->findIndex( indices[X_DIMENSION],
                          indices[Y_DIMENSION],
                          indices[Z_DIMENSION] );
}

// Export the mesh to a file (type determined by suffix)
void StructuredHexMesh::exportData( const std::string& output_file_name,
                                    const TagNameSet& tag_root_names,
                                    const MeshElementHandleDataMap& mesh_tag_data ) const
{
#ifdef HAVE_FRENSIE_MOAB
  // Preset this value to be used with all the functions that MOAB uses
  moab::ErrorCode rval;

  // Create pointer that points to a new instance of the moab_interface
  moab::Interface *moab_interface = new moab::Core();

  // Create pointer that points to a new instance of the structured mesh
  // interface
  moab::ScdInterface *scdiface = new moab::ScdInterface(moab_interface);

  // Transform planes of mesh into moab useable interleaved coordinates;
  size_t x_coordinates_size = this->getNumberOfXPlanes();
  size_t y_coordinates_size = this->getNumberOfYPlanes();
  size_t z_coordinates_size = this->getNumberOfZPlanes();

  // Make an array called coordinates that MOAB can use to construct a
  // structured hex mesh
  size_t size_of_coordinates =
    x_coordinates_size * y_coordinates_size * z_coordinates_size;

  // This array can get very large, so allocate on the heap instead of the
  // stack.
  double* coordinates = new double[size_of_coordinates*3];

  // Construct array for moab.
  /*
     An array of interleaved (XYZXYZ) coordinate vectors formed from the plane
     intersection points must be constructed in order for MOAB to correctly
     construct the mesh. Note the order of the indices being looped over; the
     indices must be in exactly this order in order for moab to correctly
     construct the mesh. Otherwise, it will connect the points with the edges
     of the mesh in an incorrect order making a lopsided mesh. Note that MOAB
     also requires every single point of the mesh to be constructed, which means
     that plane locations must be repeated in the sequence.
  */

  size_t l = 0;
  for( size_t k = 0; k < z_coordinates_size; ++k)
  {
    for( size_t j = 0; j < y_coordinates_size; ++j)
    {
      for( size_t i = 0; i < x_coordinates_size; ++i)
      {
        coordinates[l] = this->getXPlaneLocation(i);
        coordinates[l + 1] = this->getYPlaneLocation(j);
        coordinates[l + 2] = this->getZPlaneLocation(k);
        l += 3;
      }
    }
  }

  moab::ScdBox* box;
  {
    // Create the box filled with the coordinates
    rval = scdiface->construct_box( moab::HomCoord( 0, 0, 0),
                                    moab::HomCoord( x_coordinates_size - 1,
                                                    y_coordinates_size - 1,
                                                    z_coordinates_size - 1 ),
                                    coordinates,
                                    size_of_coordinates*3,
                                    box );

    TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                        Utility::MOABException,
                        moab::ErrorCodeStr[rval] );

  }
  delete[] coordinates;

  // Create the meshset
  moab::EntityHandle meshset = box->box_set();

  size_t hex_parameter_indices[3];

  this->exportDataImpl( output_file_name,
                        tag_root_names,
                        mesh_tag_data,
                        moab_interface,
                        meshset,
                        [&box,&hex_parameter_indices,this](const ElementHandle hex_id) -> ElementHandle
                        {
                          this->getHexPlaneIndices( hex_id, hex_parameter_indices );
                          return box->get_element( hex_parameter_indices[0],
                                                   hex_parameter_indices[1],
                                                   hex_parameter_indices[2] );
                        } );

  // Tidy up
  delete box;
  delete scdiface;
  delete moab_interface;
#else
  THROW_EXCEPTION( std::logic_error,
                   "The exporting of structured hex mesh data can only be "
                   "done if MOAB has been enabled!" );
#endif // end HAVE_FRENSIE_MOAB
}

} // end Utility namespace

BOOST_CLASS_EXPORT_IMPLEMENT( Utility::StructuredHexMesh )
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::StructuredHexMesh );

//---------------------------------------------------------------------------//
// end Utility_StructuredHexMesh.cpp
//---------------------------------------------------------------------------//
