//---------------------------------------------------------------------------//
//!
//! \file   Utility_StructuredHexMesh.cpp
//! \author Philip Britt
//! \brief  Hexahedron mesh storage file
//! 
//---------------------------------------------------------------------------//


// FRENSIE Includes
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SearchAlgorithms.hpp"

namespace Utility{

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
  
  //assign bounding planes of the mesh
  d_bounding_planes[0] = *(d_x_planes.begin());
  d_bounding_planes[1] = *(d_x_planes.end());
  d_bounding_planes[2] = *(d_y_planes.begin());
  d_bounding_planes[3] = *(d_y_planes.end());
  d_bounding_planes[4] = *(d_z_planes.begin());
  d_bounding_planes[5] = *(d_z_planes.end());
}
  
/*!compute track lengths for a given ray and which hex they correspond to. Return
  teuchos array of pairs*/
Teuchos::Array<std::pair<unsigned,double>> StructuredHexMesh::computeTrackLengths( 
                                            const double start_point[3],
                                            const double end_point[3],
                                            const double direction[3] )
{
  //initialize a few required variables
  double current_point[3] { start_point[0], start_point[1], start_point[2] };
  
  Teuchos::Array<std::pair<unsigned,double>> contribution_array;
  
  double track_length = vectorMagnitude( end_point[0] - start_point[0],
                                         end_point[1] - start_point[1],
                                         end_point[2] - start_point[2] );
                                         
  double length_iteration = 0;
  

  /* determine if start point is in mesh. If it isn't, then go through the process
     of determining what the distance along the direction is to the mesh or if
     none of the distances intersect with the mesh at all */
  bool start_point_in_mesh = isPointInMesh( start_point );
  if(!start_point_in_mesh)
  {
  
    //find the possible interaction planes
    Teuchos::Array<std::pair<unsigned, unsigned>> interaction_planes =
      findInteractionPlanes( start_point, 
                             direction );
  
    //take care of case where there are no possible interaction planes
    if(interaction_planes.size()==0)
    {
    
      //return empty array if this is true
      return contribution_array;
  
    }
    //find the distances to each plane
    Teuchos::Array<std::pair<unsigned,double>> distance_array = 
      findDistances( start_point,
                     direction,
                     interaction_planes );
    
    //loop over each distance and determine if this point is still in the plane
    Teuchos::Array<std::pair<unsigned,double>>::size_type i;
    double push_distance;
    bool is_test_point_in_mesh = false;
    for(i = 0; i < distance_array.size(); ++i)
    {

      double distance = distanceArray[i].second;
      double test_point[3];
      
      test_point[0] = start_point[0] + direction(0) * (distance + s_tol);
      test_point[1] = start_point[1] + direction(1) * (distance + s_tol);
      test_point[2] = start_point[2] + direction(2) * (distance + s_tol);
      
      bool is_test_point_in_mesh = isPointInMesh(test_point);
      
      if(is_test_point_in_mesh)
      {
      
        push_distance = distance;
        continue;
      
      }


    }
    
    //test determine if none of them came back true. This means ray didn't intersect with mesh
    if(!is_test_point_in_mesh)
    {
      //return empty array if it never entered mesh
      return contribution_array;
    
    }
    //also take care of when the distance to the mesh is greater than the track length of particle
    else if(push_distance > track_length)
    {
    
      return contribution_array;
    
    }
    else
    {
      //otherwise, push the point to mesh
      current_point[0] = current_point[0] + push_distance*direction[0];
      current_point[1] = current_point[1] + push_distance*direction[1];
      current_point[2] = current_point[2] + push_distance*direction[2];
      length_iteration = push_distance;
      
    }
    
  }
  
  /*find the possible interaction planes for the current point. This is required
    to find the interaction planes whether the start point is in the mesh or the
    start point was outside the mesh because the interaction planes will change under
    the circumstances of the start point being outside the mesh
    note: size of the array must be 3 here for it to make any sense*/
  Teuchos::Array<std::pair<unsigned, unsigned>> interaction_planes =
    findInteractionPlanes( current_point, 
                           direction );
  
  //find the x, y, and z lower plane indices of the hex before entering loop.
  unsigned x_index = interaction_planes[0].second;
  unsigned y_index = interaction_planes[1].second;
  unsigned z_index = interaction_planes[2].second;
  
  //determine which direction to increment based on direction
  int incrementer[3];
  
  for(unsigned i = 0; i < 3; ++i)
  {
  
    if(direction[i] < 0)
    {
      incrementer[i] = -1;
    }
    else
    {
      incrementer[i] = 1;
    }
    
  }
  
  //make sure the new interaction planes are the ones you want.
  
  //start loop to iterate over track length segments
  while(length_iteration < track_length)
  {
    //find the distances to each intersection point
    Teuchos::Array<std::pair<unsigned,double>> distances = 
      findDistances(current_point,
                    direction,
                    interaction_planes);
                    
    /*pick the shortest distance which, while inside mesh, will always be the
      relevant intersection point*/
    std::pair<unsigned,double> distance = findIntersectionPoint( distances );
    
    /*if the distance is past the end point, reset the distance to the distance
      to the end point*/
    if( distance > track_length - length_iteration )
    {
      distance = track_length - length_iteration;
    }
    
    //form the hex_index for the contribution
    unsigned hex_index = findIndex( x_index,
                                    y_index,
                                    z_index );
    
    //form a contribution out of the distance found earlier and the hex_index
    std::pair<unsigned,double> contribution = std:make_pair(hex_index, distance);
    
    //push the contribution into the contribution array
    contributionArray.push_back(contribution);
    
    //determine which plane it crossed and iterate this index up
    unsigned intersection_dimension = distance.first;
    
    /*increment index by 1 or -1 depending on what dimension was intersected
      x is 1, y is 2, z is 3 */
    if(intersection_dimension == 1)
    {
      x_index += incrementer[0];
    }
    else if(intersection_dimension == 2)
    {
      y_index += incrementer[1];
    }
    else if(intersection_dimension == 3)
    {
      z_index += incrementer[2];
    }
    
    /*determine if the intersection index is on a bounding plane. If it does,
      exit loop and return the contribution array*/
    if(x_index == 0 || x_index == d_x_planes.size() + 1)
    {
      continue;
    }
    else if(y_index == 0 || y_index == d_y_planes.size() + 1 )
    {
      continue;
    }
    else if(z_index == 0 || z_index == d_z_planes.size() + 1 )
    {
      continue;
    }
  }
  

}

Teuchos::Array<std::pair<unsigned,unsigned>> StructuredHexMesh::findInteractionPlanes( 
                                                          const double point[3],
                                                          const double direction[3] )
{
  unsigned x_plane_index;
  unsigned y_plane_index;
  unsigned z_plane_index;
  Teuchos::Array,std::pair<unsigned,unsigned>> interaction_planes;
  //figure out x interaction plane
  if(point[0] < d_bounding_planes[0] && direction[0] > 0)
  {
  
    x_plane_index = 0;
    std::pair<unsigned,unsigned> x_interaction_plane = std::make_pair(1, x_plane_index);
    interaction_planes.push_back(x_interaction_plane);
    
  }
  else if(point[0] > d_bounding_planes[1] && direction[0] < 0)
  {
  
    x_plane_index = d_x_planes.size() + 1;
    std::pair<unsigned,unsigned> x_interaction_plane = std::make_pair(1, x_plane_index);
    interaction_planes.push_back(x_interaction_plane);
  
  }
  else
  {
  
    x_plane_index = findXPlaneIndex( point[0],
                                     direction[0] );
    std::pair<unsigned,unsigned> x_interaction_plane = std::make_pair(1, x_plane_index);
    interaction_planes.push_back(x_interaction_plane);
  
  }
  //figure out y interaction plane
  if(point[1] < d_bounding_planes[2] && direction[1] > 0)
  {
  
    y_plane_index = 0;
    std::pair<unsigned,unsigned> y_interaction_plane = std::make_pair(2, y_plane_index);
    interaction_planes.push_back(y_interaction_plane);
    
  }
  else if(point[1] > d_bounding_planes[3] && direction[1] < 0)
  {
  
    y_plane_index = d_y_planes.size() + 1;
    std::pair<unsigned,unsigned> y_interaction_plane = std::make_pair(2, y_plane_index);
    interaction_planes.push_back(y_interaction_plane);  
  
  }
  else
  {
  
    y_plane_index = findYPlaneIndex( point[1],
                                     direction[1]);
    std::pair<unsigned,unsigned> y_interaction_plane = std::make_pair(2, y_plane_index);
    interaction_planes.push_back(y_interaction_plane);
  
  }
  //figure out z interaction plane
  if(point[2] < d_bounding_planes[4] && direction[2] > 0)
  {
  
    z_plane_index = 0;
    std::pair<unsigned,unsigned> z_interaction_plane = std::make_pair(3, z_plane_index);
    interaction_planes.push_back(z_interaction_plane);
    
  }
  else if(point[2] > d_bounding_planes[5] && direction[2] < 0)
  {
  
    z_plane_index = d_z_planes.size() + 1;
    std::pair<unsigned,unsigned> z_interaction_plane = std::make_pair(3, z_plane_index);
    interaction_planes.push_back(z_interaction_plane);
  
  }
  else
  {
  
    z_plane_index = findZPlaneIndex( point[1],
                                     direction[1]);
    std::pair<unsigned,unsigned> z_interaction_plane = std::make_pair(3, z_plane_index);
    interaction_planes.push_back(z_interaction_plane);
      
  }    

  return interaction_planes;

}

Teuchos::Array<std::pair<unsigned,double>> StructuredHexMesh::findDistances( 
                                    const double point[3],
                                    const double direction[3],
                                    const Teuchos::Array<std::pair<unsigned,unsigned>& planeSet)
{

  Teuchos::Array<std::pair<unsigned,double>> distances;
  
  for(unsigned i = 0; i < planeSet.size(); ++i)
  {
  
    double distance = (planeSet[i] - point[i]) / direction[i];
    unsigned dimension = planeSet[i].first;
    std::pair<unsigned, double> distance_pair = std::make_pair(dimension, distance);
    distances.push_back(distance_pair);
    
  }

  return distances;

}

std::pair<unsigned,double> StructuredHexMesh::findIntersectionPoint( const Teuchos::Array<std::pair<unsigned,unsigned>>& distances )
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

  unsigned x_dimension = d_x_planes.size();
  unsigned y_dimension = d_y_planes.size();
  
  unsigned hex_index = x_index +
                       y_index * x_dimension +
                       z_index * x_dimension * y_dimension;

  return hex_index;

}

bool StructuredHexMesh::isPointInMesh( const double point[3] )
{
  bool inMesh = false;
  if(d_bounding_planes[0] < point[0] && point[0] < d_bounding_planes[1])
  {
    if(d_bounding_planes[2] < point[1] && point[1] < d_bounding_planes[3] )
    {
      if(d_bounding_planes[4] < point[2] && point[2] < d_bounding_planes[5] )
      {
      
        inMesh = true;
        
      }
    }
  }
  
  return inMesh;

}

unsigned StructuredHexMesh::findXPlaneIndex( const double x_coordinate,
                                             const double x_direction_component)
{
  
  unsigned x_interaction_index;
  unsigned x_lower_index = Search::binaryLowerBoundIndex( d_x_planes.begin(),
                                                          d_x_planes.end(),
                                                          x_coordinate );

  if(x_direction_component > 0)
  {
    x_interaction_index = x_lower_index + 1;
    
  }
  else
  {
    x_interaction_index = x_lower_index;
  }
  
  return x_interaction_index;

}

unsigned StructuredHexMesh::findYPlaneIndex( const double y_coordinate,
                                             const double y_direction_component)
{

  unsigned y_interaction_index;
  unsigned y_lower_index = Search::binaryLowerBoundIndex( d_y_planes.begin(),
                                                          d_y_planes.end(),
                                                          y_coordinate );

  if(y_direction_component > 0)
  {
    y_interaction_index = y_lower_index + 1;
    
  }
  else
  {
    y_interaction_index = y_lower_index;
  }
  
  return y_interaction_index;

}

unsigned StructuredHexMesh::findZPlaneIndex( const double z_coordinate,
                                             const double z_direction_component)
{

  unsigned z_interaction_index;
  unsigned z_lower_index = Search::binaryLowerBoundIndex( d_z_planes.begin(),
                                                          d_z_planes.end(),
                                                          z_coordinate );

  if(z_direction_component > 0)
  {
    z_interaction_index = z_lower_index + 1;
    
  }
  else
  {
    z_interaction_index = z_lower_index;
  }
  
  return z_interaction_index;

}
                          


} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_StructuredHexMesh.cpp
//---------------------------------------------------------------------------//
