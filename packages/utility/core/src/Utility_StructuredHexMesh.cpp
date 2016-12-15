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
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"

namespace Utility{

// Initialize static member data
const double StructuredHexMesh::s_tol = 1e-12;

// Constructor
StructuredHexMesh::StructuredHexMesh( const Teuchos::Array<double>& x_planes,
                                      const Teuchos::Array<double>& y_planes,
                                      const Teuchos::Array<double>& z_planes)
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

  // Assign the given planes to member data
  d_x_planes.assign(x_planes.begin(),x_planes.end());
  d_y_planes.assign(y_planes.begin(),y_planes.end());
  d_z_planes.assign(z_planes.begin(),z_planes.end());
  
  // Form the list of hex element indices
  for( unsigned k = 0; k < d_z_planes.size()-1; ++k )
  {
    for( unsigned j = 0; j < d_y_planes.size()-1; ++j )
    {
      for( unsigned i = 0; i < d_x_planes.size()-1; ++i )
      {
        d_hex_elements.push_back( this->findIndex( i, j, k) );
      }
    }
  }
}

// Returns the volumes of the hex elements for the estimator class.
boost::unordered_map<StructuredHexMesh::HexIndex,
                     StructuredHexMesh::HexVolume> StructuredHexMesh::calculateVolumes() const
{

  boost::unordered_map<HexIndex, HexVolume> hex_volumes;
  for(PlaneIndex k = 0; k < d_z_planes.size() - 1; ++k)
  {
    for(PlaneIndex j = 0; j < d_y_planes.size() - 1; ++j)
    {
      for(PlaneIndex i = 0; i < d_x_planes.size() - 1; ++i)
      {
        hex_volumes[ this->findIndex(i, j, k) ] = 
          (d_x_planes[i + 1] - d_x_planes[i])*
          (d_y_planes[j + 1] - d_y_planes[j])*
          (d_z_planes[k + 1] - d_z_planes[k]);
      }
    }
  }
  return hex_volumes;
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
StructuredHexMesh::HexIndex StructuredHexMesh::whichHexIsPointIn( const double point[3] ) const
{
  testPrecondition( this->isPointInMesh(point) );
  unsigned x_index = Search::binaryLowerBoundIndex( d_x_planes.begin(),
                                                    d_x_planes.end(),
                                                    point[X_DIMENSION] );

  /* 
     Take care of when the point is exactly on the last x plane. The search
     will return the last x plane if this is true which does not correspond to
     any of the hex elements. Instead, move it back one 
  */
  if( x_index == d_x_planes.size() - 1)
  {
    x_index = d_x_planes.size() - 2;
  }
  unsigned y_index = Search::binaryLowerBoundIndex( d_y_planes.begin(),
                                                    d_y_planes.end(),
                                                    point[Y_DIMENSION] );
  if( y_index == d_y_planes.size() - 1)
  {
    y_index = d_y_planes.size() - 2;
  }
  unsigned z_index = Search::binaryLowerBoundIndex( d_z_planes.begin(),
                                                    d_z_planes.end(),
                                                    point[Z_DIMENSION] );
  if( z_index == d_z_planes.size() - 1)
  {
    z_index = d_z_planes.size() - 2;
  }
  return this->findIndex( x_index,
                          y_index,
                          z_index );
}

// Returns an array of pairs of hex IDs and partial track lengths along a given line segment
Teuchos::Array<std::pair<StructuredHexMesh::HexIndex,double>> StructuredHexMesh::computeTrackLengths( 
                                            const double start_point[3],
                                            const double end_point[3] )const
{
  // Make sure end point isn't the same as start point - use after bugs with end point of dying particle is fixed
  testPrecondition( start_point[0] != end_point[0] ||
                    start_point[1] != end_point[1] ||
                    start_point[2] != end_point[2] );

  // Calculate track length and direction unit vector
  double direction[3] {end_point[X_DIMENSION] - start_point[X_DIMENSION],
                       end_point[Y_DIMENSION] - start_point[Y_DIMENSION],
                       end_point[Z_DIMENSION] - start_point[Z_DIMENSION]};
                       
  double track_length = Utility::vectorMagnitude( direction[X_DIMENSION],
                                                  direction[Y_DIMENSION],
                                                  direction[Z_DIMENSION] );
                                                  
  Utility::normalizeVector( direction );
  
  // Initialize contribution array
  Teuchos::Array<std::pair<HexIndex,double>> contribution_array;

  double current_point[3] { start_point[X_DIMENSION], 
                            start_point[Y_DIMENSION], 
                            start_point[Z_DIMENSION] };

  // Test if point starts in mesh. If not, figure out if it interacts with mesh
  if( !this->isPointInMesh(current_point) )
  {
    /* 
      First member of pair is whether the mesh was intersected,
      second member of pair is the distance to the intersection
    */
    std::tuple<bool, Dimension, double> ray_intersection_tuple = 
      this->doesRayIntersectMesh( current_point,
                                  direction,
                                  track_length);
    if( std::get<0>( ray_intersection_tuple ) )
    {
      this->pushPoint( current_point, 
                       direction,
                       std::get<2>( ray_intersection_tuple ) );
      PlaneIndex hex_plane_indices[3]; 
      this->setHexPlaneIndices( std::get<1>( ray_intersection_tuple ),
                              current_point,
                              hex_plane_indices );
      contribution_array = this->traceThroughMesh( current_point,
                                                   direction,
                                                   track_length - std::get<2>( ray_intersection_tuple ),
                                                   hex_plane_indices );
    }
  }
  else
  {
    PlaneIndex hex_plane_indices[3]; 
    this->setHexPlaneIndices( current_point, hex_plane_indices );

    contribution_array = this->traceThroughMesh( current_point,
                                                 direction,
                                                 track_length,
                                                 hex_plane_indices );
  }
  return contribution_array;
}

// Get the start iterator of the hex element list.
StructuredHexMesh::HexIDIterator StructuredHexMesh::getStartHexIDIterator() const
{
  return d_hex_elements.begin(); 
}

// Get the end iterator of the hex element list.
StructuredHexMesh::HexIDIterator StructuredHexMesh::getEndHexIDIterator() const
{
  return d_hex_elements.end();
}

// Get the number of planes on the X axis.
unsigned StructuredHexMesh::getNumberOfXPlanes() const
{
  return d_x_planes.size();
}

// Get the number of planes on the Y axis.
unsigned StructuredHexMesh::getNumberOfYPlanes() const
{
  return d_y_planes.size();
}

// Get the number of planes on the Z axis.
unsigned StructuredHexMesh::getNumberOfZPlanes() const
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

// Deconstruct a hex index into indices of planes on each dimension.
void StructuredHexMesh::getHexPlaneIndices(const HexIndex h, unsigned hex_parameter_indices[3]) const
{
  testPrecondition( h >= 0 &&
                    h < d_hex_elements.size() );

  unsigned x_size = (d_x_planes.size() - 1);
  unsigned y_size = (d_y_planes.size() - 1);
  
  hex_parameter_indices[2] = h/(x_size*y_size);
  hex_parameter_indices[1] = (h - hex_parameter_indices[2] * x_size * Y_DIMENSION) / x_size;
  hex_parameter_indices[0] = h - hex_parameter_indices[1] * x_size
    - hex_parameter_indices[2] * x_size * y_size;
}

// Begin private functions

// Returns a pair where the first member is true if the ray intersects with the mesh and the second is the distance to the intersection point
std::tuple<bool, StructuredHexMesh::Dimension, double> 
  StructuredHexMesh::doesRayIntersectMesh( const double point[3],
                                           const double direction[3],
                                           const double track_length ) const
{
  // This method should only be used when the point starts outside of mesh
  testPrecondition( !(this->isPointInMesh(point)) );
  // Make sure direction vector is a unit vector
  testPrecondition( Utility::vectorMagnitude( direction[X_DIMENSION],
                                              direction[Y_DIMENSION],
                                              direction[Z_DIMENSION] ) <= 1 + s_tol &&
                    Utility::vectorMagnitude( direction[X_DIMENSION],
                                              direction[Y_DIMENSION],
                                              direction[Z_DIMENSION] ) >= 1 - s_tol);
  
  bool ray_intersect_mesh = false;
  Dimension intersection_dimension = X_DIMENSION;
  double distance = 0;
  Teuchos::Array<std::pair<Dimension, double>> bounding_plane_distance_set = 
    this->findBoundingInteractionPlaneDistances( point, direction);
  
  // Check whether there are any possible bounding planes to intersect with
  if( bounding_plane_distance_set.size() > 0 )
  {

    for(unsigned i = 0; i < bounding_plane_distance_set.size(); ++i)
    {
      // If the distance is greater than the track length, skip it
      if( bounding_plane_distance_set[i].second > track_length ) continue;
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
        ray_intersect_mesh = true;
        intersection_dimension = bounding_plane_distance_set[i].first;
        distance = bounding_plane_distance_set[i].second;
        break;
      }
    }
  } 
  return std::make_tuple(ray_intersect_mesh, intersection_dimension, distance);;
}

// Trace particle path through mesh until it dies or leaves mesh
Teuchos::Array<std::pair<StructuredHexMesh::HexIndex,double>> 
  StructuredHexMesh::traceThroughMesh( double point[3],
                                       const double direction[3],
                                       const double track_length,
                                       PlaneIndex hex_plane_indices[3] )const
{
  Teuchos::Array<std::pair<Dimension, PlaneIndex>> interaction_planes =
    this->findInteractionPlanes( point, direction, hex_plane_indices);
  Teuchos::Array<std::pair<HexIndex, double>> contribution_array;
  double iteration_distance = 0;
  unsigned incrementer[3];
  this->setIncrementer( incrementer, direction );
  bool continue_tracing = true;

  while(continue_tracing)
  {
    std::pair<Dimension, double> intersection_distance =
      this->findIntersectionDistance( point,
                                      direction,
                                      interaction_planes );
    double partial_track_length;
    
    // Check if track length is exhausted
    if( track_length <= iteration_distance + intersection_distance.second - s_tol )
    {
      partial_track_length = track_length - iteration_distance;
      continue_tracing = false;
    }
    else
    {
      partial_track_length = intersection_distance.second;
    }
    
    // Push back a new pair for the indices
    contribution_array.push_back( std::make_pair(this->findIndex( hex_plane_indices ), 
                                                 partial_track_length) );
    
    // Check if the particle left the mesh
    if( this->didParticleLeaveMesh( intersection_distance.first,
                                    interaction_planes ) )
    {
      continue_tracing = false;
    }

    // If the track length was exhausted or the particle left the mesh, leave loop and return array.
    if( continue_tracing )
    {
      // Otherwise, push point up to new location
      this->pushPoint(point, direction, partial_track_length);
      // Increase iteration_distance to new value
      iteration_distance += partial_track_length;
      // Increment indices and perform calculation again.
      hex_plane_indices[intersection_distance.first] +=
        incrementer[intersection_distance.first];
      for( unsigned i = 0; i < interaction_planes.size() ; ++i )
      {
        if(interaction_planes[i].first == intersection_distance.first)
        {
          interaction_planes[i].second += incrementer[interaction_planes[i].first];
          break;
        }
      }
    }
  }
  return contribution_array;
}

// Find the interaction planes that a particle will interact with
Teuchos::Array<std::pair<StructuredHexMesh::Dimension, StructuredHexMesh::PlaneIndex>> 
  StructuredHexMesh::findInteractionPlanes( const double point[3],
                                            const double direction[3],
                                            const PlaneIndex hex_plane_indices[3] ) const
{
  testPrecondition( this->isPointInMesh( point ) );
  
  Teuchos::Array<std::pair<Dimension, PlaneIndex>> interaction_planes;
  for( unsigned i = X_DIMENSION; i <= Z_DIMENSION; ++i)
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
  return interaction_planes;
}

// Find the intersection distance along the path of the particle with the next hex
std::pair<StructuredHexMesh::Dimension, double> 
  StructuredHexMesh::findIntersectionDistance( const double point[3],
                                               const double direction[3],
                                               const Teuchos::Array<std::pair<Dimension, PlaneIndex>>& interaction_planes) const
{
  testPrecondition( this->isPointInMesh(point) );
  testPrecondition( Utility::vectorMagnitude( direction[X_DIMENSION],
                                              direction[Y_DIMENSION],
                                              direction[Z_DIMENSION] ) <= 1 + s_tol &&
                    Utility::vectorMagnitude( direction[X_DIMENSION],
                                              direction[Y_DIMENSION],
                                              direction[Z_DIMENSION] ) >= 1 - s_tol);

  Teuchos::Array<std::pair<Dimension, double>> distance_array;
  for(unsigned i = 0; i < interaction_planes.size(); ++i)
  {
    if(interaction_planes[i].first == X_DIMENSION)
    {
      distance_array.push_back( std::make_pair( X_DIMENSION, 
                                                this->findDistanceToInteractionPlane( d_x_planes[ interaction_planes[i].second ],
                                                                                                  point[X_DIMENSION],
                                                                                                  direction[X_DIMENSION] ) ) ); 
    }
    else if(interaction_planes[i].first == Y_DIMENSION)
    {
      distance_array.push_back( std::make_pair( Y_DIMENSION, 
                                                this->findDistanceToInteractionPlane( d_y_planes[ interaction_planes[i].second ],
                                                                                                  point[Y_DIMENSION],
                                                                                                  direction[Y_DIMENSION] ) ) ); 
    }
    else if(interaction_planes[i].first == Z_DIMENSION)
    {
      distance_array.push_back( std::make_pair( Z_DIMENSION, 
                                                this->findDistanceToInteractionPlane( d_z_planes[ interaction_planes[i].second ],
                                                                                                  point[Z_DIMENSION],
                                                                                                  direction[Z_DIMENSION] ) ) );    
    }
  }
  
  return findShortestDistance( distance_array );
  
}

// Calculate distance to a plane from a ray along its direction
double StructuredHexMesh::findDistanceToInteractionPlane( const double interaction_plane_location,
                                       const double position_component,
                                       const double direction_component ) const
{
  return (interaction_plane_location - position_component)/direction_component;
}

// Find the shortest distance to the respective interaction planes along a particle path
std::pair<StructuredHexMesh::Dimension, double> 
  StructuredHexMesh::findShortestDistance( const Teuchos::Array<std::pair<Dimension, double>>& distance_array ) const
{
  unsigned j = 0;
  double shortest_distance = distance_array[0].second;
  for(unsigned i = 0; i < distance_array.size(); ++i)
  {
    if(distance_array[i].second <= shortest_distance)
    {
      j = i;
      shortest_distance = distance_array[i].second;
    }
  }
  return distance_array[j];
}

// Form the incrementer so that the particle increments over the planes in the correct direction
void StructuredHexMesh::setIncrementer( unsigned incrementer[3],
                                        const double direction[3] ) const
{
  for(unsigned i = 0; i < 3; ++i)
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
void StructuredHexMesh::setHexPlaneIndices( const double current_point[3],
                                          PlaneIndex hex_plane_indices[3] )const
{
  testPrecondition( isPointInMesh(current_point) );
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
void StructuredHexMesh::setHexPlaneIndices( const Dimension intersection_dimension,
                                          const double current_point[3],
                                          PlaneIndex hex_plane_indices[3] )const
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
StructuredHexMesh::PlaneIndex StructuredHexMesh::setHexPlaneIndex( const double position_component, 
                                        const Teuchos::Array<double>& plane_set,
                                        const Dimension plane_dimension  ) const 
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
Teuchos::Array<std::pair<StructuredHexMesh::Dimension, double>> 
  StructuredHexMesh::findBoundingInteractionPlaneDistances( const double point[3],
                                                            const double direction[3] ) const
{

  Teuchos::Array<std::pair<Dimension, double>> boundary_planes;
  
  this->checkPlaneSet( d_x_planes,
                       point[X_DIMENSION], 
                       direction[X_DIMENSION],
                       boundary_planes,
                       X_DIMENSION );
  this->checkPlaneSet( d_y_planes, 
                       point[Y_DIMENSION], 
                       direction[Y_DIMENSION],
                       boundary_planes,
                       Y_DIMENSION );
  this->checkPlaneSet( d_z_planes, 
                       point[Z_DIMENSION], 
                       direction[Z_DIMENSION],
                       boundary_planes,
                       Z_DIMENSION );

  return boundary_planes;
}

// Checks an individual set of planes for interaction plane in that dimension
void StructuredHexMesh::checkPlaneSet( const Teuchos::Array<double>& plane_set,
                                       const double position_component,
                                       const double direction_component,
                                       Teuchos::Array<std::pair<Dimension, double>>& boundary_planes,
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
bool StructuredHexMesh::isPointOnMeshSurface( const double point[3],
                                              const Dimension dimension_intersected ) const
{
  bool pointOnMesh = false;
  
  if(dimension_intersected == X_DIMENSION)
  {
    if(this->checkWithinBoundingPlane( point[Y_DIMENSION], d_y_planes ) )
    {
      if(this->checkWithinBoundingPlane( point[Z_DIMENSION], d_z_planes ) )
      {
        pointOnMesh = true;
      }
    }
  }
  else if(dimension_intersected == Y_DIMENSION)
  {
    if(this->checkWithinBoundingPlane( point[X_DIMENSION], d_x_planes ) )
    {
      if(this->checkWithinBoundingPlane( point[Z_DIMENSION], d_z_planes ) )
      {
        pointOnMesh = true;
      }
    }
  }
  else if(dimension_intersected == Z_DIMENSION)
  {
    if(this->checkWithinBoundingPlane( point[X_DIMENSION], d_x_planes ) )
    {
      if(this->checkWithinBoundingPlane( point[Y_DIMENSION], d_y_planes ) )
      {
        pointOnMesh = true;
      }
    } 
  }
  return pointOnMesh;
}

// Function for checking each individual plane to see if it is within bounds
bool StructuredHexMesh::checkWithinBoundingPlane( const double position_component,
                                                  const Teuchos::Array<double>& plane_set )const
{
  if( plane_set.front() <= position_component && position_component <= plane_set.back() )
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
bool StructuredHexMesh::didParticleLeaveMesh( Dimension intersection_dimension,
                                              Teuchos::Array<std::pair<Dimension, StructuredHexMesh::PlaneIndex>> interaction_planes ) const
{
  bool exitMesh = false;
  for(unsigned i = 0; i < interaction_planes.size(); ++i)
  {
    if( intersection_dimension == interaction_planes[i].first &&
        intersection_dimension == X_DIMENSION )
    {
      if( interaction_planes[i].second == d_x_planes.size() - 1 ||
          interaction_planes[i].second == 0 )
      {
        exitMesh = true;
      }
    }
    if( intersection_dimension == interaction_planes[i].first &&
        intersection_dimension == Y_DIMENSION )
    {
      if( interaction_planes[i].second == d_y_planes.size() - 1 ||
          interaction_planes[i].second == 0 )
      {
        exitMesh = true;
      }
    }
    if( intersection_dimension == interaction_planes[i].first &&
        intersection_dimension == Z_DIMENSION )
    {
      if( interaction_planes[i].second == d_z_planes.size() - 1 ||
          interaction_planes[i].second == 0 )
      {
        exitMesh = true;
      }
    }
  }
  return exitMesh;
}

// Calculate hex index from respective plane indices
unsigned long StructuredHexMesh::findIndex( const unsigned i,
                                            const unsigned j,
                                            const unsigned k ) const
{
  return i +
         j * (d_x_planes.size()-1) +
         k * (d_x_planes.size()-1) * (d_y_planes.size()-1);
}

// Compute hex index from plane indices
unsigned long StructuredHexMesh::findIndex( const unsigned indices[3] ) const
{
  return findIndex( indices[X_DIMENSION],
                    indices[Y_DIMENSION],
                    indices[Z_DIMENSION] );
}

} // End Utility namespace

//---------------------------------------------------------------------------//
// end Utility_StructuredHexMesh.cpp
//---------------------------------------------------------------------------//
