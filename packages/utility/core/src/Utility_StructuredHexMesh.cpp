//---------------------------------------------------------------------------//
//!
//! \file   Utility_StructuredHexMesh.cpp
//! \author Philip Britt
//! \brief  Hexahedron mesh storage file
//! 
//---------------------------------------------------------------------------//

#include <iostream>

// FRENSIE Includes
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SearchAlgorithms.hpp"

namespace Utility{
// take care of when distance is very small
//initialize static member data
const double StructuredHexMesh::s_tol = 1e-6;

//!Constructor
StructuredHexMesh::StructuredHexMesh( const Teuchos::Array<double>& x_grid_points,
                                      const Teuchos::Array<double>& y_grid_points,
                                      const Teuchos::Array<double>& z_grid_points)
{
  //assign the given grid points to member data
  d_x_planes.assign(x_grid_points.begin(),x_grid_points.end());
  d_y_planes.assign(y_grid_points.begin(),y_grid_points.end());
  d_z_planes.assign(z_grid_points.begin(),z_grid_points.end());

}

//determine whether or not the point is in the mesh
bool StructuredHexMesh::isPointInMesh( const double point[3] )
{

  if( d_x_planes.front() - s_tol <= point[x] && point[x] <= d_x_planes.back() + s_tol )
  {
    if( d_y_planes.front() - s_tol <= point[y] && point[y] <= d_y_planes.back() + s_tol )
    {
      if(d_z_planes.front() - s_tol <= point[z] && point[z] <= d_z_planes.back() + s_tol )
      {
        return true;
      }
    }
  }
  
  return false;
}

//find the index of the hex that a point is in

unsigned StructuredHexMesh::whichHexIsPointIn( const double point[3] )
{

}

/*!compute track lengths for a given ray and which hex they correspond to. Return
  teuchos array of pairs*/
Teuchos::Array<std::pair<unsigned,double>> StructuredHexMesh::computeTrackLengths( 
                                            const double start_point[3],
                                            const double end_point[3],
                                            const double direction[3] )
{
  //initialize variables
  Teuchos::Array<std::pair<unsigned,double>> contribution_array;
  
  double current_point[3] { start_point[0], start_point[1], start_point[2] };
  
  Teuchos::Array<std::pair<planeDimension,plane_index>> interaction_plane_array;
  
  Teuchos::Array<std::pair<planeDimension,double>> distance_array;
  
  double track_length = vectorMagnitude( start_point[0] - end_point[0],
                                         start_point[1] - end_point[1],
                                         start_point[2] - end_point[2] );
  double iteration_length = 0;
  
  std::pair<planeDimension, double> distance_to_intersection;
  
  
  bool pointInMesh = isPointInMesh(current_point);
  //test if point starts in mesh. If not, figure out if it interacts with mesh
  if( !pointInMesh )
  {
  
    //find the planes that the point interacts with
    interaction_plane_array = findInteractionPlanes( current_point,
                                                     direction );
    
    //if it doesn't interact with any planes, return an empty array
    if( interaction_plane_array.size() == 0 )
    {
      return contribution_array;
    }
    
    //find the distances to the different planes it interacts with
    distance_array = findDistances( current_point,
                                    direction,
                                    interaction_plane_array );

    //find out if any of these intersections enter mesh
    double push_distance;
    bool does_point_hit_mesh = false;
    for(unsigned i = 0; i < distance_array.size(); ++i)
    {
      //push the intersection point a small amount along distance to find out if that point is inside the mesh
      double test_point[3];
      test_point[0] = current_point[0] + (distance_array[i] + s_tol) * direction[0];
      test_point[1] = current_point[1] + (distance_array[i] + s_tol) * direction[1];
      test_point[2] = current_point[2] + (distance_array[i] + s_tol) * direction[2];
      
      if(isPointInMesh(test_point))
      {
        push_distance = distance[i];
        does_point_hit_mesh = true;
        continue;
      }
    
    }
    
    //check if intersection distance is greater than particle track length or if particle never hits mesh
    if( !does_point_hit_mesh || push_distance >= track_length)
    {
      return contribution_array;
    }
    //otherwise, push the point up to the mesh and increase iteration_length by push_distance
    else
    {
      current_point[0] += push_distance*direction[0];
      current_point[1] += push_distance*direction[1];
      current_point[2] += push_distance*direction[2];
      iteration_length = push_distance;
    }
  
  }
  
  //check special case of a point being caught in the boundary region but traveling away from mesh. This takes care of when the point was born in boundary zone but traveling away *and* when the particle entered mesh in the boundary region but never actually entered mesh
  if(boundaryRegionSpecialCase( current_point, direction ) )
  {
    return contribution_array;
  }

  //find the planes that the particle will interact with (since point has either moved or these were never found if inside mesh) and set indices up for interaction planes and hex_index planes
  interaction_planes = findInteractionPlanes( current_point,
                                              direction );
  
  setMemberIndices( current_point,
                    direction,
                    interaction_planes );
  
  int incrementer[3];
  
  for(unsigned i = 0; i < 3; ++i)
  {
  
    if(direction[i] < 0)
    {
      incrementer[i] = -1;
    }
    else
    {
      incrementer[i] = 0;
    }
  
  }
  
  while(true)
  {
    //find the distances to each interaction plane
    distance_array = findDistances( current_point,
                                    direction,
                                    interaction_planes );
    //pick out the distance at which particle will enter a new hex element
    distance_to_intersection = findIntersectionPoint( distance_array );
    
    //check if the distance is greater than the remaining track length left
    bool isTrackLengthExhausted = false;
    if( track_length - iteration_distance - s_tol < distance_to_intersection )
    {
    
      distance_to_intersection.second = track_length - iteration_distance;
      isTrackLengthExhausted = true;
    
    }
    
    //figure out what hex cell this is in
    hex_index = find_index(d_hex_plane_indices);
    //form contribution pair and push back into array
    std::pair<unsigned,double> contribution;
    contribution.first = hex_index;
    contribution.second = distance_to_intersection.second;
    contribution_array.push_back(contribution);
    
    //check if the interaction plane was a bounding plane or if the earlier case of particle exhausting track length occurred. If so, exit loop;
    bool particleExitedMesh = didParticleExitMesh(interaction_planes);
    if(particleExitedMesh || isTrackLengthExhausted)
    {
      continue;
    }
    
    //iterate up or down interaction planes and hex index planes
    d_hex_plane_indices[ distance_to_intersection.first ] += 
      incrementer[ distance_to_intersection.first ];

    for(unsigned i = 0; i < interaction_planes.size(); ++i)
    {
  
      if(interaction_planes[i].first == distance_to_intersection.first)
      {
        interaction_planes[i].second += incrementer[distance_to_intersection.first];
      }
  
    }
  
  }

  return contribution_array;
}

//begin private functions

//set the member indices for a particle traveling through the mesh
void StructuredHexMesh::setMemberIndices( double point[3],
                                          const Teuchos::Array<std::pair<planeDimension,plane_index>>& interaction_planes )
{
  /*first try to avoid a binary search. If the direction is negative for a given interaction plane,
    just use the interaction plane index as the member index*/
  bool wasMemberPlaneSet[3] {false, false, false};
  for(unsigned i = 0; i < interaction_planes.size(); ++i)
  {
    if(interaction_planes[i].first == x && direction[x] < 0)
    {
      d_hex_plane_indices[x] = interaction_planes[i].second;
      wasMemberPlaneSet[x] = true;
    }
    else if(interaction_planes[i].first == y && direction[y] < 0)
    {
      d_hex_plane_indices[y] = interaction_planes[i].second;
      wasMemberPlaneSet[y] = true;
    }
    else if(interaction_planes[i].first == z && direction[z] < 0)
    {
      d_hex_plane_indices[z] = interaction_planes[i].second;
      wasMemberPlaneSet[z] = true;
    }
  }
  

  if(!wasMemberPlaneSet[x])
  {
    d_hex_plane_indices[x] = Search::binaryLowerBoundIndex( d_x_planes.front(),
                                                            d_x_planes.back(),
                                                            point[x] );
  }
  if(!wasMemberPlaneSet[y] )
  {
    d_hex_plane_indices[y] = Search::binaryLowerBoundIndex( d_y_planes.front(),
                                                            d_y_planes.back(),
                                                            point[y] );  
  }
  if(!wasMemberPlaneSet[z] )
  {
    d_hex_plane_indices[z] = Search::binaryLowerBoundIndex( d_z_planes.front(),
                                                            d_z_planes.back(),
                                                            point[z] );  
  }

}

/*Deals with a special case of the point being in the boundary region but traveling away from the mesh.
  If it does, it should just return true which will result in a return of an empty contribution array */
bool boundaryRegionSpecialCase( double point[3],
                                double direction[3] );
{
  bool isSpecialCase = false;
  //test boundary regions in x dimension
  if( d_x_planes.back() <= point[x] && point[x] < d_x_planes.back() + s_tol && direction[x] >= 0 )
  {
    isSpecialCase = true;
  }
  else if(d_x_planes.front() - s_tol < point[x] && point[x] <= d_x_planes.front() && direction[x] <= 0)
  {
    isSpecialCase = true;
  }
  //test boundary regions in y dimension
  if( d_y_planes.back() <= point[y] && point[y] < d_y_planes.back() + s_tol && direction[y] >= 0 )
  {
    isSpecialCase = true;
  }
  else if(d_y_planes.front() - s_tol < point[y] && point[y] <= d_y_planes.front() && direction[y] <= 0)
  {
    isSpecialCase = true;
  }
  //test boundary regions in z dimension
  if( d_z_planes.back() <= point[z] && point[z] < d_z_planes.back() + s_tol && direction[z] >= 0 )
  {
    isSpecialCase = true;
  }
  else if(d_z_planes.front() - s_tol < point[z] && point[z] <= d_z_planes.front() && direction[z] <= 0)
  {
    isSpecialCase = true;
  }

  return isSpecialCase;
}
//find the planes that a particle will interact with
Teuchos::Array<std::pair<planeDimension,plane_index>> StructuredHexMesh::findInteractionPlanes( 
                                                          const double point[3],
                                                          const double direction[3] )
{
  Teuchos::Array<std::pair<planeDimension,plane_index>> interaction_planes;
//X DIMENSION SEARCH  
  /*check if the point is above the x dimension upper bounding plane and the 
    relevant direction component is negative */
  if( point[x] >= d_x_planes.back() + s_tol && direction[x] < 0 )
  {
    std::pair<planeDimension,plane_index> x_interaction_plane = 
      std::make_pair(x, d_x_planes.size()-1);
    
    interaction_planes.push_back(x_interaction_plane);
  }
  //case of when point is in the upper boundary region. Needed for catching of real numbers pushed up to boundary plane but not quite crossing it due to finite precision
  else if( d_x_planes.back() <= point[x] && point[x] < d_x_planes.back() + s_tol)
  {
    std::pair<planeDimension,plane_index> x_interaction_plane = 
      std::make_pair(x, d_x_planes.size()-2);
    
    interaction_planes.push_back(x_interaction_plane);    
  }
  /*check if the point is below the x dimension lower bounding plane and the
    relevant direction component is positive */
  else if( point[x] <= d_x_planes.front() - s_tol && direction[x] > 0 )
  {
    std::pair<planeDimension,plane_index> x_interaction_plane = 
      std::make_pair(x, 0);
    
    interaction_planes.push_back(x_interaction_plane);
  }
  //case of when point is in the lower boundary region. Needed for catching of real numbers pushed up to boundary plane but not quite crossing it due to finite precision
  else if( d_x_planes.front() >= point[x] && point[x] > d_x_planes.front() - s_tol)
  {
    std::pair<planeDimension,plane_index> x_interaction_plane = 
      std::make_pair(x, 1);
    
    interaction_planes.push_back(x_interaction_plane);    
  }
  //otherwise, somewhere inside the mesh. Need to look for which plane it will interact with
  else
  {
    if(direction[x] > 0)
    {
      plane_index x_plane_index =
        Search::binaryUpperBoundIndex( d_x_planes.begin(),
                                       d_x_planes.end(),
                                       point[x] );
      std::pair<planeDimension,plane_index> x_interaction_plane =
        std::make_pair(x, x_plane_index);
      interaction_planes.push_back(x_interaction_plane);
      
    }
    else if( direction[x] < 0)
    {
      plane_index x_plane_index =
        Search::binaryLowerBoundIndex( d_x_planes.begin(),
                                       d_x_planes.end(),
                                       point[x] );
      std::pair<planeDimension,plane_index> x_interaction_plane =
        std::make_pair(x, x_plane_index);
      
      interaction_planes.push_back(x_interaction_plane);
    }
  }
  
//Y DIMENSION SEARCH
  /*check if the point is above the y dimension upper bounding plane and the 
    relevant direction component is negative */
  if( point[y] >= d_y_planes.back() + s_tol && direction[y] < 0 )
  {
    std::pair<planeDimension,plane_index> y_interaction_plane = 
      std::make_pair(y, d_y_planes.size()-1);
    
    interaction_planes.push_back(y_interaction_plane);
  }
  //case of when point is in the upper boundary region. Needed for catching of real numbers pushed up to boundary plane but not quite crossing it due to finite precision
  else if( d_y_planes.back() <= point[y] && point[y] < d_y_planes.back() + s_tol)
  {
    std::pair<planeDimension,plane_index> y_interaction_plane = 
      std::make_pair(y, d_y_planes.size()-2);
    
    interaction_planes.push_back(y_interaction_plane);    
  }
  /*check if the point is below the y dimension lower bounding plane and the
    relevant direction component is positive */
  else if( point[y] <= d_y_planes.front() - s_tol && direction[y] > 0 )
  {
    std::pair<planeDimension,plane_index> y_interaction_plane = 
      std::make_pair(y, 0);
    
    interaction_planes.push_back(y_interaction_plane);
  }
  //case of when point is in the lower boundary region. Needed for catching of real numbers pushed up to boundary plane but not quite crossing it due to finite precision
  else if( d_y_planes.front() >= point[y] && point[y] > d_y_planes.front() - s_tol)
  {
    std::pair<planeDimension,plane_index> y_interaction_plane = 
      std::make_pair(y, 1);
    
    interaction_planes.push_back(y_interaction_plane);    
  }
  //otherwise, somewhere inside the mesh. Need to look for which plane it will interact with
  else
  {
    if(direction[y] > 0)
    {
      plane_index y_plane_index =
        Search::binaryUpperBoundIndex( d_y_planes.begin(),
                                       d_y_planes.end(),
                                       point[y] );
      std::pair<planeDimension,plane_index> y_interaction_plane =
        std::make_pair(y, y_plane_index);
      interaction_planes.push_back(y_interaction_plane);
      
    }
    else if( direction[y] < 0)
    {
      plane_index y_plane_index =
        Search::binaryLowerBoundIndex( d_y_planes.begin(),
                                       d_y_planes.end(),
                                       point[y] );
      std::pair<planeDimension,plane_index> y_interaction_plane =
        std::make_pair(y, y_plane_index);
      
      interaction_planes.push_back(y_interaction_plane);
    }
  }

//Z DIMENSION SEARCH
  /*check if the point is above the z dimension upper bounding plane and the 
    relevant direction component is negative */
  if( point[z] >= d_z_planes.back() + s_tol && direction[z] < 0 )
  {
    std::pair<planeDimension,plane_index> z_interaction_plane = 
      std::make_pair(z, d_z_planes.size()-1);
    
    interaction_planes.push_back(z_interaction_plane);
  }
  //case of when point is in the upper boundary region. Needed for catching of real numbers pushed up to boundary plane but not quite crossing it due to finite precision
  else if( d_z_planes.back() <= point[z] && point[z] < d_z_planes.back() + s_tol)
  {
    std::pair<planeDimension,plane_index> z_interaction_plane = 
      std::make_pair(z, d_z_planes.size()-2);
    
    interaction_planes.push_back(z_interaction_plane);    
  }
  /*check if the point is below the z dimension lower bounding plane and the
    relevant direction component is positive */
  else if( point[z] <= d_z_planes.front() - s_tol && direction[z] > 0 )
  {
    std::pair<planeDimension,plane_index> z_interaction_plane = 
      std::make_pair(z, 0);
    
    interaction_planes.push_back(z_interaction_plane);
  }
  //case of when point is in the lower boundary region. Needed for catching of real numbers pushed up to boundary plane but not quite crossing it due to finite precision
  else if( d_z_planes.front() >= point[z] && point[z] > d_z_planes.front() - s_tol)
  {
    std::pair<planeDimension,plane_index> z_interaction_plane = 
      std::make_pair(z, 1);
    
    interaction_planes.push_back(z_interaction_plane);    
  }
  //otherwise, somewhere inside the mesh. Need to look for which plane it will interact with
  else
  {
    if(direction[z] > 0)
    {
      plane_index z_plane_index =
        Search::binaryUpperBoundIndex( d_z_planes.begin(),
                                       d_z_planes.end(),
                                       point[z] );
      std::pair<planeDimension,plane_index> z_interaction_plane =
        std::make_pair(z, z_plane_index);
      interaction_planes.push_back(z_interaction_plane);
      
    }
    else if( direction[z] < 0)
    {
      plane_index z_plane_index =
        Search::binaryLowerBoundIndex( d_z_planes.begin(),
                                       d_z_planes.end(),
                                       point[z] );
      std::pair<planeDimension,plane_index> z_interaction_plane =
        std::make_pair(z, z_plane_index);
      
      interaction_planes.push_back(z_interaction_plane);
    }
  }
  
  return interaction_planes;

}

//find distances to each interaction plane
Teuchos::Array<std::pair<unsigned,double>> StructuredHexMesh::findDistances( 
                                    const double point[3],
                                    const double direction[3],
                                    const Teuchos::Array<std::pair<unsigned,unsigned>>& planeSet)
{

  Teuchos::Array<std::pair<unsigned,double>> distances;
  double distance;
  
  //iterate over each pair of the interaction planes and find the distance to it
  for( unsigned i = 0; i < planeSet.size(); ++i)
  {
    if(planeSet[i].first == 0)
    {
      distance = (d_x_planes[planeSet[i].second] - point[0]) / direction[0];
    }
    else if(planeSet[i].first == 1)
    {
      distance = (d_y_planes[planeSet[i].second] - point[1]) / direction[1];
    }
    else if(planeSet[i].first == 2)
    {
      distance = (d_z_planes[planeSet[i].second] - point[2]) / direction[2];
    }
    unsigned dimension = planeSet[i].first;
    std::pair<unsigned, double> distance_pair = std::make_pair(dimension, distance);
    distances.push_back(distance_pair);  
    
  
  }

}

//pick out the shortest distance
std::pair<unsigned,double> StructuredHexMesh::findIntersectionPoint( const Teuchos::Array<std::pair<unsigned,double>>& distances )
{
  //set initialize min pair as the first pair
  std::pair<unsigned,double> min_distance_pair = distances[0];
  
  //iterate over all the pairs to find the smallest
  for(unsigned i = 1; i < distances.size(); ++i)
  {
    
    if(distances[i].second < min_distance_pair.second)
    {
      min_distance_pair = distances[i];
    } 
    
  }
  
  return min_distance_pair;


}

unsigned StructuredHexMesh::findIndex( const unsigned x_index,
                                       const unsigned y_index,
                                       const unsigned z_index )
{
  unsigned x_dimension = d_x_planes.size()-1;
  unsigned y_dimension = d_y_planes.size()-1;
  unsigned hex_index = x_index +
                       y_index * x_dimension +
                       z_index * x_dimension * y_dimension;

  return hex_index;

}

unsigned StructuredHexMesh::findIndex( const unsigned indices[3] )
{
  return StructuredHexMesh::findIndex( indices[0], indices[1], indices[2] );
}
                          


} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_StructuredHexMesh.cpp
//---------------------------------------------------------------------------//
