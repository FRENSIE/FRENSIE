//---------------------------------------------------------------------------//
//!
//! \file   Utility_StructuredHexMesh.cpp
//! \author Philip Britt
//! \brief  Hexahedron mesh storage file
//! 
//---------------------------------------------------------------------------//

//std includes
#include <math.h>

// FRENSIE Includes
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SearchAlgorithms.hpp"

namespace Utility{
// take care of when distance is very small
//initialize static member data
const double StructuredHexMesh::s_tol = 1e-12;

//! Constructor
StructuredHexMesh::StructuredHexMesh( const Teuchos::Array<double>& x_planes,
                                      const Teuchos::Array<double>& y_planes,
                                      const Teuchos::Array<double>& z_planes)
{

  //Test for at least 2 planes
  testPrecondition(x_planes.size()>=2);
  testPrecondition(y_planes.size()>=2);
  testPrecondition(z_planes.size()>=2);
  
  //make sure that the planes are in increasing sequential order

  for(unsigned i = 0; i < x_planes.size()-1; ++i)
  {
    testPrecondition( x_planes[i] < x_planes[i+1] );
  }

  for(unsigned i = 0; i < y_planes.size()-1; ++i)
  {
    testPrecondition( y_planes[i] < y_planes[i+1] );
  }

  for(unsigned i = 0; i < z_planes.size()-1; ++i)
  {
    testPrecondition( z_planes[i] < z_planes[i+1] );
  }
  
  //assign the given planes to member data
  d_x_planes.assign(x_planes.begin(),x_planes.end());
  d_y_planes.assign(y_planes.begin(),y_planes.end());
  d_z_planes.assign(z_planes.begin(),z_planes.end());
  
  //form the list of hex element indices
  for( unsigned k = 0; k < d_z_planes.size()-1; ++k )
  {
    for( unsigned j = 0; j < d_y_planes.size()-1; ++j )
    {
      for( unsigned i = 0; i < d_x_planes.size()-1; ++i )
      {
      
        d_hex_elements.push_back( findIndex( i, j, k) );
      
      }
    }
  }
}

boost::unordered_map<StructuredHexMesh::HexIndex,
                     StructuredHexMesh::HexVolume>
                     StructuredHexMesh::calculateVolumes()
{

  boost::unordered_map<HexIndex, HexVolume> hex_volumes;
  for(PlaneIndex k = 0; k < d_z_planes.size() - 1; ++k)
  {
    for(PlaneIndex j = 0; j < d_y_planes.size() - 1; ++j)
    {
      for(PlaneIndex i = 0; i < d_x_planes.size() - 1; ++i)
      {
      
        hex_volumes[ findIndex(i, j, k) ] = 
          (d_x_planes[i + 1] - d_x_planes[i])*
          (d_y_planes[j + 1] - d_y_planes[j])*
          (d_z_planes[k + 1] - d_z_planes[k]);
          
      }
    }
  }
  
  return hex_volumes;

}

//determine whether or not the point is in the mesh
bool StructuredHexMesh::isPointInMesh( const double point[3] )
{

  if( d_x_planes.front() - s_tol <= point[x_dim] && point[x_dim] <= d_x_planes.back() + s_tol )
  {
    if( d_y_planes.front() - s_tol <= point[y_dim] && point[y_dim] <= d_y_planes.back() + s_tol )
    {
      if(d_z_planes.front() - s_tol <= point[z_dim] && point[z_dim] <= d_z_planes.back() + s_tol )
      {
        return true;
      }
    }
  }
  
  return false;
}

//find the index of the hex that a point is in

StructuredHexMesh::HexIndex StructuredHexMesh::whichHexIsPointIn( const double point[3] )
{

  unsigned x_index = Search::binaryLowerBoundIndex( d_x_planes.begin(),
                                                    d_x_planes.end(),
                                                    point[x_dim] );

  /*take care of when the point is exactly on the last x plane. The search
    will return the last x plane if this is true which does not correspond to
    any of the hex elements. Instead, move it back one */
  if( x_index == d_x_planes.size() - 1)
  {
    x_index = d_x_planes.size() - 2;
  }
  unsigned y_index = Search::binaryLowerBoundIndex( d_y_planes.begin(),
                                                    d_y_planes.end(),
                                                    point[y_dim] );
  if( y_index == d_y_planes.size() - 1)
  {
    y_index = d_y_planes.size() - 2;
  }
  unsigned z_index = Search::binaryLowerBoundIndex( d_z_planes.begin(),
                                                    d_z_planes.end(),
                                                    point[z_dim] );
  if( z_index == d_z_planes.size() - 1)
  {
    z_index = d_z_planes.size() - 2;
  }
  
  return findIndex( x_index,
                    y_index,
                    z_index );

}

/*!compute track lengths for a given ray and which hex they correspond to. Return
  teuchos array of pairs*/
Teuchos::Array<std::pair<StructuredHexMesh::HexIndex,double>> StructuredHexMesh::computeTrackLengths( 
                                            const double start_point[3],
                                            const double end_point[3],
                                            const double direction[3],
                                            const double track_length )
{
  //initialize variables
  Teuchos::Array<std::pair<HexIndex,double>> contribution_array;
  
  double current_point[3] { start_point[0], start_point[1], start_point[2] };
  
  Teuchos::Array<std::pair<planeDimension,PlaneIndex>> interaction_plane_array;
  
  Teuchos::Array<std::pair<planeDimension,double>> distance_array;
  
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
    double* push_distance = NULL;
    bool does_point_hit_mesh = false;
    for(unsigned i = 0; i < distance_array.size(); ++i)
    {
      //push the intersection point a small amount along distance to find out if that point is inside the mesh
      double test_point[3];
      test_point[x_dim] = current_point[x_dim] + (distance_array[i].second + s_tol) * direction[x_dim];
      test_point[y_dim] = current_point[y_dim] + (distance_array[i].second + s_tol) * direction[y_dim];
      test_point[z_dim] = current_point[z_dim] + (distance_array[i].second + s_tol) * direction[z_dim];
      
      if(isPointInMesh(test_point))
      {
        //set this boolean to true for use in determining whether the particle entered the mesh later
        does_point_hit_mesh = true;
        
        //figure out whether push_distance exists yet. If not, then set the push_distance
        // to the recently found distance to the intersection point. If it does exist
        // and is smaller than previously found push_distances, then set it equal
        // to the newly found distance
        if(!push_distance || *push_distance > distance_array[i].second)
        {
          push_distance = &distance_array[i].second;
        }

      }
    
    }
    
    //check if intersection distance is greater than particle track length or if particle never hits mesh
    if( !does_point_hit_mesh || *push_distance >= track_length)
    {
      return contribution_array;
    }
    //otherwise, push the point up to the mesh and increase iteration_length by push_distance
    else
    {
      current_point[x_dim] += (*push_distance)*direction[x_dim];
      current_point[y_dim] += (*push_distance)*direction[y_dim];
      current_point[z_dim] += (*push_distance)*direction[z_dim];
      iteration_length = *push_distance;
    }
  
  }
  
  //check special case of a point being caught in the boundary region but traveling away from mesh. This takes care of when the point was born in boundary zone but traveling away *and* when the particle entered mesh in the boundary region but never actually entered mesh
  if(boundaryRegionSpecialCase( current_point, end_point, direction ) )
  {
    return contribution_array;
  }

  //find the planes that the particle will interact with (since point has either moved or these were never found if inside mesh) and set indices up for interaction planes and HexIndex planes
  interaction_plane_array = findInteractionPlanes( current_point,
                                                   direction );

  setMemberIndices( current_point,
                    direction,
                    interaction_plane_array );

  //set the direction that the hex cells will move through
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

  while(true)
  {
    //find the distances to each interaction plane
    distance_array = findDistances( current_point,
                                    direction,
                                    interaction_plane_array );

    //pick out the distance at which particle will enter a new hex element
    distance_to_intersection = findIntersectionPoint( distance_array );

    //check if the distance is greater than the remaining track length left
    bool isTrackLengthExhausted = false;
    if( track_length - iteration_length - s_tol < distance_to_intersection.second )
    {

      distance_to_intersection.second = track_length - iteration_length;
      isTrackLengthExhausted = true;

    }


    //figure out what hex cell this is in
    unsigned hex_index = findIndex(d_hex_plane_indices);
    //form contribution pair and push back into array
    std::pair<unsigned,double> contribution;
    contribution.first = hex_index;
    contribution.second = distance_to_intersection.second;
    contribution_array.push_back(contribution);


    //check if the interaction plane was a bounding plane or if the earlier case of particle exhausting track length occurred. If so, exit loop;
    bool particleExitedMesh = didParticleExitMesh( distance_to_intersection.first,
                                                   interaction_plane_array);

    if(particleExitedMesh || isTrackLengthExhausted)
    {
      break;
    }
    
    //iterate up or down interaction planes and hex index planes
    d_hex_plane_indices[ distance_to_intersection.first ] += 
      incrementer[ distance_to_intersection.first ];

    for(unsigned i = 0; i < interaction_plane_array.size(); ++i)
    {
  
      if(interaction_plane_array[i].first == distance_to_intersection.first)
      {
        interaction_plane_array[i].second += incrementer[distance_to_intersection.first];
      }
  
    }
    // increase iteration_length by distance
    iteration_length += distance_to_intersection.second;
    //push up current point to new intersection point
    current_point[x_dim] += distance_to_intersection.second*direction[x_dim];
    current_point[y_dim] += distance_to_intersection.second*direction[y_dim];
    current_point[z_dim] += distance_to_intersection.second*direction[z_dim];
  }

  return contribution_array;
}

//get the start iterator of the hex element list
/*! \details returns the iterator that points to the first element in the list containing
 *           all of the hex ID elements */
StructuredHexMesh::HexIDIterator StructuredHexMesh::getStartHexIDIterator()
{

  return d_hex_elements.begin(); 
  
}

//get the end iterator of the hex element list
/*! \details returns the iterator that points to one beyond the last element in the list containing
 *           all of the hex ID elements */
StructuredHexMesh::HexIDIterator StructuredHexMesh::getEndHexIDIterator()
{

  return d_hex_elements.end();

}

//get the number of planes on the X axis
unsigned StructuredHexMesh::getNumberOfXPlanes()
{

  return d_x_planes.size();

}

//get the number of planes on the Y axis
unsigned StructuredHexMesh::getNumberOfYPlanes()
{

  return d_y_planes.size();

}

//get the number of planes on the Z axis
unsigned StructuredHexMesh::getNumberOfZPlanes()
{

  return d_z_planes.size();

}

//get the location of a specific plane on the x axis
double StructuredHexMesh::getXPlaneLocation( PlaneIndex i)
{
  //make sure plane index is valid
  testPrecondition( i < d_x_planes.size() && i >= 0);
  
  return d_x_planes[i];

}

//get the location of a specific plane on the y axis
double StructuredHexMesh::getYPlaneLocation( PlaneIndex i)
{
  //make sure plane index is valid
  testPrecondition( i < d_y_planes.size() && i >= 0);
  
  return d_y_planes[i];

}

//get the location of a specific plane on the y axis
double StructuredHexMesh::getZPlaneLocation( PlaneIndex i)
{
  //make sure plane index is valid
  testPrecondition( i < d_z_planes.size() && i >= 0);
  
  return d_z_planes[i];

}
//! return the individual plane indices from a hex index for moab to use
void StructuredHexMesh::moabGetHexPlaneIndices(const HexIndex h, unsigned hex_parameter_indices[3])
{

  testPrecondition( h >= 0 &&
                    h < d_hex_elements.size() );

  unsigned x_dim = (d_x_planes.size() - 1);
  unsigned y_dim = (d_y_planes.size() - 1);
  
  hex_parameter_indices[2] = h/(x_dim*y_dim);
  hex_parameter_indices[1] = (h - hex_parameter_indices[2] * x_dim * y_dim) / x_dim;
  hex_parameter_indices[0] = h - hex_parameter_indices[1] * x_dim
    - hex_parameter_indices[2] * x_dim * y_dim;

}

//begin private functions

//set the member indices for a particle traveling through the mesh
void StructuredHexMesh::setMemberIndices( const double point[3],
                                          const double direction[3],
                                          const Teuchos::Array<std::pair<planeDimension,PlaneIndex>>& interaction_planes )
{
  /*first try to avoid a binary search. If the direction is negative for a given interaction plane,
    just use the interaction plane index as the member index*/
  bool wasMemberPlaneSet[3] {false, false, false};
  for(unsigned i = 0; i < interaction_planes.size(); ++i)
  {
    if(interaction_planes[i].first == x_dim && direction[x_dim] < 0)
    {
      d_hex_plane_indices[x_dim] = interaction_planes[i].second;
      wasMemberPlaneSet[x_dim] = true;
    }
    else if(interaction_planes[i].first == y_dim && direction[y_dim] < 0)
    {
      d_hex_plane_indices[y_dim] = interaction_planes[i].second;
      wasMemberPlaneSet[y_dim] = true;
    }
    else if(interaction_planes[i].first == z_dim && direction[z_dim] < 0)
    {
      d_hex_plane_indices[z_dim] = interaction_planes[i].second;
      wasMemberPlaneSet[z_dim] = true;
    }
  }
  
  //if the hex plane isn't the same as the interaction plane, find the hex plane
  if(!wasMemberPlaneSet[x_dim])
  {
    //take care of boundary region case
    if( d_x_planes.front() - s_tol < point[x_dim] && point[x_dim] < d_x_planes.front() )
    {
      d_hex_plane_indices[x_dim] = 0;
    }
    else if( d_x_planes.back() < point[x_dim] && point[x_dim] < d_x_planes.back() + s_tol )
    {
      d_hex_plane_indices[x_dim] = d_x_planes.size() - 1;
    }
    //somewhere inside the mesh
    else
    {
      //take care of case when poitn is exactly on the upper boundary
      if(point[x_dim] == d_x_planes.back())
      {
        d_hex_plane_indices[x_dim] = d_x_planes.size() - 2;
      }
      else
      {
        d_hex_plane_indices[x_dim] = Search::binaryLowerBoundIndex( d_x_planes.begin(),
                                                                    d_x_planes.end(),
                                                                    point[x_dim] );
      }
    }
  }
  if(!wasMemberPlaneSet[y_dim] )
  {
    if( d_y_planes.front() - s_tol < point[y_dim] && point[y_dim] < d_y_planes.front() )
    {
      d_hex_plane_indices[y_dim] = 0;
    }
    else if( d_y_planes.back() < point[y_dim] && point[y_dim] < d_y_planes.back() + s_tol )
    {
      d_hex_plane_indices[y_dim] = d_y_planes.size() - 1;
    }
    else
    {
      if(point[y_dim] == d_y_planes.back())
      {
        d_hex_plane_indices[y_dim] = d_y_planes.size() - 2;
      }
      else
      {
        d_hex_plane_indices[y_dim] = Search::binaryLowerBoundIndex( d_y_planes.begin(),
                                                                    d_y_planes.end(),
                                                                    point[y_dim] );
      }
    }
  }
  if(!wasMemberPlaneSet[z_dim] )
  {
    if( d_z_planes.front() - s_tol < point[z_dim] && point[z_dim] < d_z_planes.front() )
    {
      d_hex_plane_indices[z_dim] = 0;
    }
    else if( d_z_planes.back() < point[z_dim] && point[z_dim] < d_z_planes.back() + s_tol )
    {
      d_hex_plane_indices[z_dim] = d_z_planes.size() - 1;
    }
    else
    {
      if(point[z_dim] == d_z_planes.back())
      {
        d_hex_plane_indices[z_dim] = d_z_planes.size() - 2;
      }
      else
      {
        d_hex_plane_indices[z_dim] = Search::binaryLowerBoundIndex( d_z_planes.begin(),
                                                                    d_z_planes.end(),
                                                                    point[z_dim] );
      }
    }
  }

}

/*Deals with a special case of the particle being in the boundary region but traveling away from the mesh
  and the particle born in the boundary region and staying in that boundary region.
  If it does, it should just return true which will result in a return of an empty contribution array */
bool StructuredHexMesh::boundaryRegionSpecialCase( const double start_point[3],
                                                   const double end_point[3],
                                                   const double direction[3] )
{
  bool isSpecialCase = false;
  //test boundary regions in x dimension
  if( d_x_planes.back() <= start_point[x_dim] && start_point[x_dim] < d_x_planes.back() + s_tol )
  {
    if( direction[x_dim] >= 0 )
    {
      isSpecialCase = true;
    }
    else if( d_x_planes.back() <= end_point[x_dim] && end_point[x_dim] < d_x_planes.back() + s_tol)
    {
      isSpecialCase = true;
    }
  }
  else if(d_x_planes.front() - s_tol < start_point[x_dim] && start_point[x_dim] <= d_x_planes.front() )
  {
    if( direction[x_dim] <= 0 )
    {
      isSpecialCase = true;
    }
    else if( d_x_planes.front() - s_tol < end_point[x_dim] && end_point[x_dim] <= d_x_planes.front() )
    {
      isSpecialCase = true;
    }
  }
  //test boundary regions in y dimension
  if( d_y_planes.back() <= start_point[y_dim] && start_point[y_dim] < d_y_planes.back() + s_tol )
  {
    if( direction[y_dim] >= 0 )
    {
      isSpecialCase = true;
    }
    else if( d_y_planes.back() <= end_point[y_dim] && end_point[y_dim] < d_y_planes.back() + s_tol)
    {
      isSpecialCase = true;
    }
  }
  else if(d_y_planes.front() - s_tol < start_point[y_dim] && start_point[y_dim] <= d_y_planes.front() )
  {
    if( direction[y_dim] <= 0 )
    {
      isSpecialCase = true;
    }
    else if( d_y_planes.front() - s_tol < end_point[y_dim] && end_point[y_dim] <= d_y_planes.front() )
    {
      isSpecialCase = true;
    }
  }
  //test boundary regions in z dimension
  if( d_z_planes.back() <= start_point[z_dim] && start_point[z_dim] < d_z_planes.back() + s_tol )
  {
    if( direction[z_dim] >= 0 )
    {
      isSpecialCase = true;
    }
    else if( d_z_planes.back() <= end_point[z_dim] && end_point[z_dim] < d_z_planes.back() + s_tol)
    {
      isSpecialCase = true;
    }
  }
  else if(d_z_planes.front() - s_tol < start_point[z_dim] && start_point[z_dim] <= d_z_planes.front() )
  {
    if( direction[z_dim] <= 0 )
    {
      isSpecialCase = true;
    }
    else if( d_z_planes.front() - s_tol < end_point[z_dim] && end_point[z_dim] <= d_z_planes.front() )
    {
      isSpecialCase = true;
    }
  }

  return isSpecialCase;
}

//return whether or not the particle exited the mesh
bool StructuredHexMesh::didParticleExitMesh( planeDimension intersection_dimension,
                                             Teuchos::Array<std::pair<planeDimension, PlaneIndex>> interaction_planes)
{
  bool particleExitedMesh = false;
  //check each interaction plane to see if it's the one that was intersected and also whether or not it's a bounding plane
  for(unsigned i = 0; i < interaction_planes.size(); ++i)
  {
    if(interaction_planes[i].first == intersection_dimension)
    {
      if(intersection_dimension == 0)
      {
        if(interaction_planes[i].second == d_x_planes.size() - 1 || interaction_planes[i].second == 0)
        {
          particleExitedMesh = true;
        } 
      }
      else if(intersection_dimension == 1)
      {
        if(interaction_planes[i].second == d_y_planes.size() - 1 || interaction_planes[i].second == 0)
        {
          particleExitedMesh = true;
        }       
      }
      else if(intersection_dimension == 2)
      {
        if(interaction_planes[i].second == d_z_planes.size() - 1 || interaction_planes[i].second == 0)
        {
          particleExitedMesh = true;
        }       
      }
    }
  }
  
  return particleExitedMesh;
}
//find the planes that a particle will interact with
Teuchos::Array<std::pair<StructuredHexMesh::planeDimension,StructuredHexMesh::PlaneIndex>> StructuredHexMesh::findInteractionPlanes( 
                                                          const double point[3],
                                                          const double direction[3] )
{
  Teuchos::Array<std::pair<planeDimension,PlaneIndex>> interaction_planes;
//X DIMENSION SEARCH

  if(std::fabs(direction[x_dim]) > s_tol)
  {
    /*check if the point is above the x dimension upper bounding plane and the 
      relevant direction component is negative */
    if( point[x_dim] >= d_x_planes.back() + s_tol && direction[x_dim] < 0 )
    {
      std::pair<planeDimension,PlaneIndex> x_interaction_plane = 
        std::make_pair(x_dim, d_x_planes.size()-1);
    
      interaction_planes.push_back(x_interaction_plane);
    }
    //case of when point is in the upper boundary region. Needed for catching of real numbers pushed up to boundary plane but not quite crossing it due to finite precision
    else if( d_x_planes.back() <= point[x_dim] && point[x_dim] < d_x_planes.back() + s_tol && direction[x_dim] < 0)
    {
      std::pair<planeDimension,PlaneIndex> x_interaction_plane = 
        std::make_pair(x_dim, d_x_planes.size()-2);
    
      interaction_planes.push_back(x_interaction_plane);    
    }
    /*check if the point is below the x dimension lower bounding plane and the
      relevant direction component is positive */
    else if( point[x_dim] <= d_x_planes.front() - s_tol && direction[x_dim] > 0 )
    {
      std::pair<planeDimension,PlaneIndex> x_interaction_plane = 
        std::make_pair(x_dim, 0);
    
      interaction_planes.push_back(x_interaction_plane);
    }
    //case of when point is in the lower boundary region. Needed for catching of real numbers pushed up to boundary plane but not quite crossing it due to finite precision
    else if( d_x_planes.front() >= point[x_dim] && point[x_dim] > d_x_planes.front() - s_tol && direction[x_dim] > 0)
    {
      std::pair<planeDimension,PlaneIndex> x_interaction_plane = 
        std::make_pair(x_dim, 1);
    
      interaction_planes.push_back(x_interaction_plane);    
    }
    //otherwise, somewhere inside the mesh. Need to look for which plane it will interact with
    else if( d_x_planes.front() <= point[x_dim] && point[x_dim] <= d_x_planes.back() )
    {
      if(direction[x_dim] > 0)
      {
        PlaneIndex x_plane_index =
          Search::binaryUpperBoundIndex( d_x_planes.begin(),
                                         d_x_planes.end(),
                                         point[x_dim] );
        std::pair<planeDimension,PlaneIndex> x_interaction_plane =
          std::make_pair(x_dim, x_plane_index);
        interaction_planes.push_back(x_interaction_plane);
      }
      else if( direction[x_dim] < 0)
      {
        PlaneIndex x_plane_index =
          Search::binaryLowerBoundIndex( d_x_planes.begin(),
                                         d_x_planes.end(),
                                         point[x_dim] );
        std::pair<planeDimension,PlaneIndex> x_interaction_plane =
          std::make_pair(x_dim, x_plane_index);
      
        interaction_planes.push_back(x_interaction_plane);
      }
    }
  }
  
  
//Y DIMENSION SEARCH
  if(std::fabs(direction[y_dim]) > s_tol)
  {
    /*check if the point is above the y dimension upper bounding plane and the 
      relevant direction component is negative */
    if( point[y_dim] >= d_y_planes.back() + s_tol && direction[y_dim] < 0 )
    {
      std::pair<planeDimension,PlaneIndex> y_interaction_plane = 
        std::make_pair(y_dim, d_y_planes.size()-1);
    
      interaction_planes.push_back(y_interaction_plane);
    }
    //case of when point is in the upper boundary region. Needed for catching of real numbers pushed up to boundary plane but not quite crossing it due to finite precision
    else if( d_y_planes.back() <= point[y_dim] && point[y_dim] < d_y_planes.back() + s_tol && direction[y_dim] < 0)
    {
      std::pair<planeDimension,PlaneIndex> y_interaction_plane = 
        std::make_pair(y_dim, d_y_planes.size()-2);
    
      interaction_planes.push_back(y_interaction_plane);    
    }
    /*check if the point is below the y dimension lower bounding plane and the
      relevant direction component is positive */
    else if( point[y_dim] <= d_y_planes.front() - s_tol && direction[y_dim] > 0 )
    {
      std::pair<planeDimension,PlaneIndex> y_interaction_plane = 
        std::make_pair(y_dim, 0);
      
      interaction_planes.push_back(y_interaction_plane);
    }
    //case of when point is in the lower boundary region. Needed for catching of real numbers pushed up to boundary plane but not quite crossing it due to finite precision
    else if( d_y_planes.front() >= point[y_dim] && point[y_dim] > d_y_planes.front() - s_tol && direction[y_dim] > 0)
    {
      std::pair<planeDimension,PlaneIndex> y_interaction_plane = 
        std::make_pair(y_dim, 1);
      
      interaction_planes.push_back(y_interaction_plane);    
    }
    //otherwise, somewhere inside the mesh. Need to look for which plane it will interact with
    else if( d_y_planes.front() <= point[y_dim] && point[y_dim] <= d_y_planes.back() )
    {
      if(direction[y_dim] > 0)
      {
        PlaneIndex y_plane_index =
          Search::binaryUpperBoundIndex( d_y_planes.begin(),
                                         d_y_planes.end(),
                                         point[y_dim] );
        std::pair<planeDimension,PlaneIndex> y_interaction_plane =
          std::make_pair(y_dim, y_plane_index);
        interaction_planes.push_back(y_interaction_plane);
      
      }
      else if( direction[y_dim] < 0)
      {
        PlaneIndex y_plane_index =
          Search::binaryLowerBoundIndex( d_y_planes.begin(),
                                         d_y_planes.end(),
                                         point[y_dim] );
        std::pair<planeDimension,PlaneIndex> y_interaction_plane =
          std::make_pair(y_dim, y_plane_index);
      
        interaction_planes.push_back(y_interaction_plane);
      }
    }
  }


//Z DIMENSION SEARCH
  if(std::fabs(direction[z_dim]) > s_tol )
  {
    /*check if the point is above the z dimension upper bounding plane and the 
      relevant direction component is negative */
    if( point[z_dim] >= d_z_planes.back() + s_tol && direction[z_dim] < 0 )
    {
      std::pair<planeDimension,PlaneIndex> z_interaction_plane = 
        std::make_pair(z_dim, d_z_planes.size()-1);
    
      interaction_planes.push_back(z_interaction_plane);
    }
    //case of when point is in the upper boundary region. Needed for catching of real numbers pushed up to boundary plane but not quite crossing it due to finite precision
    else if( d_z_planes.back() <= point[z_dim] && point[z_dim] < d_z_planes.back() + s_tol && direction[z_dim] < 0)
    {
      std::pair<planeDimension,PlaneIndex> z_interaction_plane = 
        std::make_pair(z_dim, d_z_planes.size()-2);
    
      interaction_planes.push_back(z_interaction_plane);    
    }
    /*check if the point is below the z dimension lower bounding plane and the
      relevant direction component is positive */
    else if( point[z_dim] <= d_z_planes.front() - s_tol && direction[z_dim] > 0 )
    {
      std::pair<planeDimension,PlaneIndex> z_interaction_plane = 
        std::make_pair(z_dim, 0);
    
      interaction_planes.push_back(z_interaction_plane);
    }
    //case of when point is in the lower boundary region. Needed for catching of real numbers pushed up to boundary plane but not quite crossing it due to finite precision
    else if( d_z_planes.front() >= point[z_dim] && point[z_dim] > d_z_planes.front() - s_tol && direction[z_dim] > 0)
    {
      std::pair<planeDimension,PlaneIndex> z_interaction_plane = 
        std::make_pair(z_dim, 1);
    
      interaction_planes.push_back(z_interaction_plane);    
    }
    //otherwise, somewhere inside the mesh. Need to look for which plane it will interact with
    else if( d_z_planes.front() <= point[z_dim] && point[z_dim] <= d_z_planes.back() )
    {
      if(direction[z_dim] > 0)
      {
        PlaneIndex z_plane_index =
          Search::binaryUpperBoundIndex( d_z_planes.begin(),
                                         d_z_planes.end(),
                                         point[z_dim] );
        std::pair<planeDimension,PlaneIndex> z_interaction_plane =
          std::make_pair(z_dim, z_plane_index);
        interaction_planes.push_back(z_interaction_plane);
      
      }
      else if( direction[z_dim] < 0)
      {
        PlaneIndex z_plane_index =
          Search::binaryLowerBoundIndex( d_z_planes.begin(),
                                         d_z_planes.end(),
                                         point[z_dim] );
        std::pair<planeDimension,PlaneIndex> z_interaction_plane =
          std::make_pair(z_dim, z_plane_index);
      
        interaction_planes.push_back(z_interaction_plane);
      }
    }
  }

  return interaction_planes;

}

//find distances to each interaction plane
Teuchos::Array<std::pair<StructuredHexMesh::planeDimension,double>> StructuredHexMesh::findDistances( 
                                    const double point[3],
                                    const double direction[3],
                                    const Teuchos::Array<std::pair<planeDimension,PlaneIndex>>& planeSet)
{

  Teuchos::Array<std::pair<planeDimension,double>> distances;
  double distance;
  
  //iterate over each pair of the interaction planes and find the distance to it
  for( unsigned i = 0; i < planeSet.size(); ++i)
  {
    if(planeSet[i].first == x_dim)
    {
      distance = (d_x_planes[planeSet[i].second] - point[x_dim]) / direction[x_dim];
    }
    else if(planeSet[i].first == y_dim)
    {
      distance = (d_y_planes[planeSet[i].second] - point[y_dim]) / direction[y_dim];
    }
    else if(planeSet[i].first == z_dim)
    {
      distance = (d_z_planes[planeSet[i].second] - point[z_dim]) / direction[z_dim];
    }
    std::pair<planeDimension, double> distance_pair = std::make_pair(planeSet[i].first, distance);
    distances.push_back(distance_pair);  
    
  }
  
  return distances;

}

//pick out the shortest distance
std::pair<StructuredHexMesh::planeDimension,double> StructuredHexMesh::findIntersectionPoint( const Teuchos::Array<std::pair<planeDimension,double>>& distances )
{
  //set initialize min pair as the first pair
  std::pair<planeDimension,double> min_distance_pair = distances[0];
  
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

StructuredHexMesh::HexIndex StructuredHexMesh::findIndex( const unsigned x_index,
                                                           const unsigned y_index,
                                                           const unsigned z_index )
{
  unsigned x_dimension = d_x_planes.size()-1;
  unsigned y_dimension = d_y_planes.size()-1;
  unsigned long hex_index = x_index +
                            y_index * x_dimension +
                            z_index * x_dimension * y_dimension;

  return hex_index;

}

StructuredHexMesh::HexIndex StructuredHexMesh::findIndex( const unsigned indices[3] )
{
  return findIndex( indices[x_dim], indices[y_dim], indices[z_dim] );
}
                          


} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_StructuredHexMesh.cpp
//---------------------------------------------------------------------------//