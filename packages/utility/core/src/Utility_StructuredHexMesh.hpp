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

// Trillinos Includes
#include <Teuchos_Array.hpp>

namespace Utility{

class StructuredHexMesh
{

public:
  
  //! Constructor
  StructuredHexMesh( const Teuchos::Array<double>& x_grid_points,
                     const Teuchos::Array<double>& y_grid_points,
                     const Teuchos::Array<double>& z_grid_points );

  //! Destructor
  ~StructuredHexMesh()
  { /* ... */ }
  
  //! Tells whether or not a point is inside the mesh
  bool isPointInMesh( const double point[3] );
  
  //! Returns index for which hex element the point is contained in
  unsigned whichHexIsPointIn( const double point[3], unsigned hex_plane_indices[6] );
  
  //! returns 1-d array index of hex assuming x index is iterated over first
  unsigned returnIndex( const unsigned x_index,
                        const unsigned y_index,
                        const unsigned z_index );
  
  //! returns partial track lengths along a given line segment
  Teuchos::Array<std::pair<unsigned,double>> computeTrackLengths( 
                              const double start_point[3],
                              const double end_point[3],
                              const double direction[3] );
  // plane location member data
  Teuchos::Array<double>& d_x_planes;
  Teuchos::Array<double>& d_y_planes;
  Teuchos::Array<double>& d_z_planes;
  
  // bounding plane member data (x1,x2,y1,y2,z1,z2)
  double d_bounding_planes[6];
  
                               
private:

  // The tolerance used for geometric tests
  static const double s_tol;       

  //!find set of possible planes that track length can intersect with
  void findInteractionPlanes( const double current_point[3],
                              const double direction[3],
                              unsigned hex_plane_indices[3],
                              unsigned plane_set[3] );
  
  //!Find distance to chosen plane
  double calculateDistanceToPlane( const double current_point_component,
                                   const double direction_component,
                                   const unsigned plane_location ); 
  
  //!pick the smallest distance to planes to return distance to said plane                                  
  double pickPlane(const double distances[3]);
  
  void findCentroid(const double current_point[3],
                  const double distance[3],
                  const double direction[3],
                  double centroid_point[3]);
                  
  bool rayIntersectsWithBoundingPlanes(const double start_point[3],
                                       const double direction[3]);

}


} // end Utility namespace


#endif // end UTILITY_STRUCTURED_HEX_MESH_HPP

//---------------------------------------------------------------------------//
// end Utility_StructuredHexMesh.hpp
//---------------------------------------------------------------------------//
