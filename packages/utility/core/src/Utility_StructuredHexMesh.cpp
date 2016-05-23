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
  
bool StructuredHexMesh::isPointInMesh( const double point[3] )
{

  bool in_mesh = false;
  //check x planes
  if( d_bounding_planes[0] + s_tol < point[0] &&
     point[0] < d_bounding_planes[1] - s_tol )
  {
    //check y planes
    if( d_bounding_planes[2] + s_tol < point[1] &&
      point[1] < d_bounding_planes[3] - s_tol )
    {
      //check z planes
      if( d_bounding_planes[4] + s_tol < point[2] &&
        point[2] < d_bounding_planes[5] - s_tol )
      {  
        in_mesh = true;
      }
    }
  }

  return in_mesh;
}

/* binary search for hex containing point, return index for relevant hex and
   indices of relevant set of planes which bound that hex element*/
unsigned StructuredHexMesh::whichHexIsPointIn( const double point[3], 
                                               unsigned hex_plane_indices[6] )
{

  unsigned x_index = Search::binaryLowerBoundIndex(d_x_planes.begin(),
                                                   d_x_planes.end(),
                                                   point[0] );
                                                   
  hex_plane_indices[0] = x_index;
  hex_plane_indices[1] = x_index+1;
  
  unsigned y_index = Search::binaryLowerBoundIndex(d_y_planes.begin(),
                                                   d_y_planes.end(),
                                                   point[1] );
                                                   
  hex_plane_indices[2] = y_index;
  hex_plane_indices[3] = y_index+1;
                                                   
  unsigned z_index = Search::binaryLowerBoundIndex(d_z_planes.begin(),
                                                   d_z_planes.end(),
                                                   point[2] );
  
  hex_plane_indices[4] = y_index;
  hex_plane_indices[5] = y_index+1;

  unsigned index = returnIndex(x_index,y_index,z_index);
  return index;

}

//return index of 1-d array of hexes
unsigned StructuredHexMesh::returnIndex( const unsigned x_index,
                                         const unsigned y_index,
                                         const unsigned z_index)
{
  //find size of arrays containing x and y plane locations
  Teuchos::Array<double>::size_type x_dim = d_x_planes.size();
  Teuchos::Array<double>::size_type y_dim = d_y_planes.size();

  return x_index + y_index*x_dim + z_index*x_dim*y_dim;

}

// compute the track lengths. 
Teuchos::Array<std::pair<unsigned,double>> StructuredHexMesh::computeTrackLengths(
                                           const double start_point[3],
                                           const double end_point[3],
                                           const double direction[3] )
{
  //declare and/or initialize variables required for entire method
  Teuchos::Array<std::pair<unsigned,double>> contributionArray;
  double current_point[3];
  double overall_track_length = vectorMagnitude(end_point[0] - start_point[0],
                                                end_point[1] - start_point[1],
                                                end_point[2] - start_point[2]);
  double segment_length;
  /*check if start_point is inside mesh or outside mesh. Different functions used
    to determine distance to mesh are different from ones used inside mesh */
  bool is_start_point_in_mesh = isPointInMesh(start_point);
  if(!is_start_point_in_mesh)
  {
    //determine if special case with ray traveling away from all planes
    bool SpecialCase = RayIntersectWithBoundingPlanes(start_point, direction);
    if(SpecialCase)
    {
      //return empty array if true
      return contributionArray;
    }
    else
    {
      //find the relevant bounding planes that the ray may interact with
      unsigned bounding_plane_indices[3];
      findBoundingPlanes(  start_point,
                           direction,
                           bounding_plane_indices);
      //determine distances to relevant bounding planes
      double bounding_plane_distances[3];
      calculateDistanceToBoundingPlane( start_point,
                                        direction,
                                        bounding_plane_indices,
                                        bounding_plane_distances );
      //determine if any of these distances put particle inside mesh
      for(unsigned i = 0; i < 3; ++i)
      {
        //iterate current point over distances
        current_point[0] = start_point[0] +
          (bounding_plane_distances[i]+s_tol)*direction[0];
        current_point[1] = start_point[1] + 
          (bounding_plane_distances[i]+s_tol)*direction[1];      
        current_point[2] = start_point[2] +
          (bounding_plane_distances[i]+s_tol)*direction[2];
        
        //determine if new point is in mesh. If so, assign that distance as the distance required
        bool is_current_point_in_mesh = isPointInMesh(current_point);
        if(is_current_point_in_mesh)
        {
          distance_to_mesh = bounding_plane_distances[i];
          continue;
        }
      }
      
      //if none of the points are within the mesh, return an empty array
      if(!is_current_point_in_mesh)
      {
        return contributionArray;
      }
      
      //if distance found is greater than ray length, return an empty array
      if(distance_to_mesh >= overall_track_length)
      {
        return contributionArray;
      }
      
      /*otherwise, push current_point up to the mesh intersection
        and also start the segment length iteration at that distance, used for
        iteration over partial tracks later*/
      
      segment_length = distance_to_mesh;
      current_point[0] = start_point[0] + distance_to_mesh*direction[0];
      current_point[1] = start_point[1] + distance_to_mesh*direction[1];      
      current_point[2] = start_point[2] + distance_to_mesh*direction[2];
      
      /*also initialize a point slightly past the intersection point to determine
        which hex the particle is entering*/
      double hex_determination_point[3];
      hex_determination_point[0] = current_point[0] + s_tol*direction[0];
      hex_determination_point[1] = current_point[1] + s_tol*direction[1];
      hex_determination_point[2] = current_point[2] + s_tol*direction[2];      
    }
  }
  
  //initialize hex_determination_point as the start_point if the start_point is inside the mesh
  if(is_start_point_in_mesh)
  {
    hex_determination_point[0] = start_point[0];
    hex_determination_point[1] = start_point[1];
    hex_determination_point[2] = start_point[2];
    segment_length = 0;
  }

  //iterate over segment_length to form partial track length array
  while(segment_length < overall_track_length)
  {

    std::pair <unsigned,double> contribution;
    //initialize relevant hex element bounding plane index array
    unsigned hex_plane_indices[6];

    /*figure out what the bounding planes are needed and what index corresponds
      to that hex. */
    unsigned hex_index = 
      whichHexIsPointIn( hex_determination_point, hex_plane_indices);
      
    //figure out which interaction planes are relevant for intersection points
    unsigned plane_intersection_index_set[3];
    findInteractionPlanes( hex_determination_point,
                           direction,
                           hex_plane_indices,
                           plane_intersection_index_set );
                           
    //find distances to each plane picked along particle path
    double distances_to_planes[3]
    distances_to_planes[0] = calculateDistanceToPlane( current_point[0],
                                                       direction[0],
                                                       plane_intersection_index_set[0]);
    distances_to_planes[1] = calculateDistanceToPlane( current_point[1],
                                                       direction[1],
                                                       plane_intersection_index_set[1]);
    distances_to_planes[2] = calculateDistanceToPlane( current_point[2],
                                                       direction[2],
                                                       plane_intersection_index_set[2]);
    //determine which one is the plane that the particle will intersect first
    double distance_to_intersection = pickPlane(distances_to_planes);
    
    /*find out if distance is further than the end of the overall track length.
      Should also take care of when a particle starts and stops in single cell */
    if(distance_to_intersection + segment_length > overall_track_length)
    {
      contribution = std::make_pair(hex_index, overall_track_length - segment_length);
      contributionArray.push_back(contribution);
      return contributionArray;
    }
    //form contribution pair for track length through entire hex cell
    contribution = std::make_pair(hex_index, distance_to_intersection);
    contributionArray.push_back(contribution);
    
    //move particle to intersection point
    segment_length = segment_length + distance_to_intersection;
    current_point[0] = current_point[0] + distance_to_intersection*direction[0];
    current_point[1] = current_point[1] + distance_to_intersection*direction[1];
    current_point[2] = current_point[2] + distance_to_intersection*direction[2];
    
    //find hex_determination_point
    hex_determination_point[0] =
      hex_determination_point[0] + distance_to_intersection*direction[0];
    hex_determination_point[1] =
      hex_determination_point[1] + distance_to_intersection*direction[1];
    hex_determination_point[2] =
      hex_determination_point[2] + distance_to_intersection*direction[2];    
        
    /*determine if hex determination point is still inside mesh.
    If not, then the particle has exited mesh and final contribution
    should be made*/
    bool exited_mesh = isPointInMesh(hex_determination_point);
    if(exited_mesh)
    {
      continue;
    }
  }
  
  /*return contributionArray. This should only execute if the particle leaves
    the mesh. If it dies in the mesh, this should never execute, but should be
    taken care of above*/
  return contributionArray;
      
      

}

//returns the planes for a ray inside of a mesh that are needed to determine intersection points
void StructuredHexMesh::findInteractionPlanes( const double current_point[3],
                                               const double direction[3],
                                               unsigned hex_plane_indices[3],
                                               unsigned plane_intersection_index_set[3] )
{



}

//find distances to a relevant plane
double StructuredHexMesh::calculateDistanceToPlane(const double current_point_component,
                                                   const double direction_component,
                                                   const unsigned plane_location)
{

  double distance = (plane_location - current_point_component) / direction_component;
  return distance;

}

//used only for rays inside a mesh to pick the relevant plane that the point will interact with
double StructuredHexMesh::pickPlane(const double distances[3])
{
  double lowest_distance;
  
  lowest_distance = distances[0];
  for(unsigned i = 1; i < 3; ++i)
  {
    if(distances[i] < lowest_distance)
    {
      lowest_distance = distances[i];
    }
  }
  
  return lowest_distance;
}

//finds the centroid of a given line segment
void StructuredHexMesh::findCentroid(const double current_point[3],
                  const double distance,
                  const double direction[3],
                  double centroid_point[3])
{
  double centroid_distance = distance/2;
  
  centroid_point[0] = current_point[0] + centroid_distance * direction[0];
  centroid_point[1] = current_point[1] + centroid_distance * direction[1];
  centroid_point[2] = current_point[2] + centroid_distance * direction[2];
  
}


bool StructuredHexMesh::doesRayIntersectWithBoundingPlanes(const double start_point[3],
                                                           const double direction[3])
{
     
  
}



} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_StructuredHexMesh.cpp
//---------------------------------------------------------------------------//
