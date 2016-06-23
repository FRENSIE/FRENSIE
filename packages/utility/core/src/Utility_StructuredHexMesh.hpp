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

// boost includes
#include <boost/unordered_map.hpp>

// Trillinos Includes
#include <Teuchos_Array.hpp>

namespace Utility{

class StructuredHexMesh
{

public:
  typedef unsigned long hex_index;
  typedef double hex_volume;
  
    
  //! Constructor
  StructuredHexMesh( const Teuchos::Array<double>& x_grid_points,
                     const Teuchos::Array<double>& y_grid_points,
                     const Teuchos::Array<double>& z_grid_points );

  //! Destructor
  ~StructuredHexMesh()
  { /* ... */ }

  //returns the volumes of the hex elements for the estimator class
  boost::unordered_map<hex_index, hex_volume> calculateVolumes();

  //returns a bool that says whether or not a point is in the mesh
  bool isPointInMesh( const double point[3] );
  
  //returns the index of the hex that contains a given point
  hex_index whichHexIsPointIn( const double point[3] );
  
  //! returns partial track lengths along a given line segment
  Teuchos::Array<std::pair<hex_index,double>> computeTrackLengths( 
                              const double start_point[3],
                              const double end_point[3],
                              const double direction[3],
                              const double track_length );

  // plane location member data
  Teuchos::Array<double> d_x_planes;
  Teuchos::Array<double> d_y_planes;
  Teuchos::Array<double> d_z_planes;
  
  // indices of the planes that are used to form the index for the hex element a particle is in
  unsigned d_hex_plane_indices[3];
  

  
private:

  // The tolerance used for geometric tests
  static const double s_tol;
  
  //enumeration type converting dimensions to integers
  enum planeDimension{ x_dim = 0,
                       y_dim = 1,
                       z_dim = 2 };

  typedef unsigned plane_index;
  
  void setMemberIndices( const double point[3],
                         const double direction[3],
                         const Teuchos::Array<std::pair<planeDimension,plane_index>>& interaction_planes );
  
  bool boundaryRegionSpecialCase( const double start_point[3],
                                  const double end_point[3],
                                  const double direction[3] );

  bool didParticleExitMesh( planeDimension intersecction_dimension,
                            Teuchos::Array<std::pair<planeDimension,plane_index>> interaction_planes); 
                       
  Teuchos::Array<std::pair<planeDimension,plane_index>> findInteractionPlanes( 
                                                        const double point[3],
                                                        const double direction[3] );
                         
  Teuchos::Array<std::pair<planeDimension,double>> findDistances( 
                                                        const double point[3],
                                                        const double direction[3],
                      const Teuchos::Array<std::pair<planeDimension,plane_index>>& planeSet );
                      
  //used to find the relevant intersection point where the particle will intersect the mesh
  std::pair<planeDimension,double> findIntersectionPoint( const Teuchos::Array<std::pair<planeDimension,double>>& distances);
  
  //form the index out of the x,y, and z lower hex plane bounding indices
  hex_index findIndex( const unsigned x_index,
                      const unsigned y_index,
                      const unsigned z_index );
  
  //overload function for ease
  hex_index findIndex( const unsigned indices[3] );
                            
};


} // end Utility namespace


#endif // end UTILITY_STRUCTURED_HEX_MESH_HPP

//---------------------------------------------------------------------------//
// end Utility_StructuredHexMesh.hpp
//---------------------------------------------------------------------------//
