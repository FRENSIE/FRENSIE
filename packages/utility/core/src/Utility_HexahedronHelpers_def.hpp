//---------------------------------------------------------------------------//
//!
//! \file   Utility_TetrahedronHelpers_def.hpp
//! \author Luke Kersting, Philip Britt
//! \brief  Tetrahedron helper function template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TETRAHEDRON_HELPERS_DEF_HPP
#define UTILITY_TETRAHEDRON_HELPERS_DEF_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseSolver.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_BLAS_types.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

//vertex 1 is common vertex;
Teuchos::Array<double> crossProduct(const Teuchos::Array<double> vector_1,
                                    const Teuchos::Array<double> vector_2)
{
  

  Teuchos::Array<double> cross_product_result(3);
  cross_product_result[0] = vector_1[1] * vector_2[2] - vector_1[2] * vector_2[1];
  cross_product_result[1] = -(vector_1[0] * vector_2[2] - vector_1[2] * vector_2[0]);
  cross_product_result[2] = vector_1[0] * vector_2[1] - vector_1[1] * vector_2[0];

  return cross_product_result;
} 



// Calculate tetrahedron barycentric transform matrix
                         
template<typename Matrix>                                                      
void calculateFaceNormals( const double vertex_a[3],
			   const double vertex_b[3],
			   const double vertex_c[3],
			   const double vertex_d[3],
		           const double vertex_e[3],
			   const double vertex_f[3],
			   const double vertex_g[3],
			   const double vertex_h[3],
                           Teuchos::TwoDArray<double>& face_normals) 
{
  // Make sure the matrix is valid
  testPrecondition( face_normals.getNumRows() == 6 );
  testPrecondition( face_normals.getNumCols() == 3 );

  Teuchos::Array<double> vector_ab(3);
  Teuchos::Array<double> vector_ad(3);
  Teuchos::Array<double> vector_ae(3);
  Teuchos::Array<double> vector_gf(3);
  Teuchos::Array<double> vector_gh(3);
  Teuchos::Array<double> vector_gc(3);

  for(int i = 0; i != 3; i++) {
        vector_ab[i] = vertex_b[i] - vertex_a[i];
        vector_ad[i] = vertex_d[i] - vertex_a[i];
        vector_ae[i] = vertex_e[i] - vertex_a[i];

        vector_gf[i] = vertex_f[i] - vertex_g[i];
        vector_gh[i] = vertex_h[i] - vertex_g[i];
        vector_gc[i] = vertex_c[i] - vertex_g[i];
  }

  face_normals[0] = crossProduct(vector_ad, vector_ab);
  face_normals[1] = crossProduct(vector_gh, vector_gf);
  face_normals[2] = crossProduct(vector_gc, vector_gh);
  face_normals[3] = crossProduct(vector_gf, vector_gc);
  face_normals[4] = crossProduct(vector_ab, vector_ae);
  face_normals[5] = crossProduct(vector_ae, vector_ad);

  return face_normals;
}

// Determine if a point is in a given tet
/*! \details Make sure the matrix has dimensions 3x3!                        
 */

//note: reference_vertex1 is point a, reference_vertex2 is point g
template<typename TestPoint, typename ReferencePoint, typename Matrix>      
bool isPointInHex( const TestPoint& point, 
                   const ReferencePoint& reference_vertex_a,
                   const ReferencePoint& reference_vertex_g,   
		   const Teuchos::TwoDArray<double> face_normals )
{
  Teuchos::Array<double> testpoint_reference_vector_1(3);
  testpoint_reference_vector_1[0] = point[0] - reference_vertex_a[0];
  testpoint_reference_vector_1[1] = point[1] - reference_vertex_a[1];
  testpoint_reference_vector_1[2] = point[2] - reference_vertex_a[2];

  Teuchos::Array<double> testpoint_reference_vector_2(3);
  testpoint_reference_vector_2[0] = point[0] - reference_vertex_g[0];
  testpoint_reference_vector_2[1] = point[1] - reference_vertex_g[1];
  testpoint_reference_vector_2[2] = point[2] - reference_vertex_g[2];

  bool inside_hex = true;
  //loop through TwoDArray of normal vectors
  for(int i = 0; i != 6; i++) {

        double dot_product = 0;
        //first loop through faces that are associated with point a.
        if(i < 3) {
                for(int j = 0; j != 3; j++) {

                        dot_product += testpoint_reference_vector_1[j] * face_normals[i][j];

                }
                if(dot_product > 0) {
                                inside_hex = false;
                                return inside_hex;
                }
        }
        //then loop through faces that are associated with point g.
        else {
                for(int j = 0; j != 3; j++) {

                        dot_product += testpoint_reference_vector_2[j] * face_normals[i][j];
                        
                }
                if(dot_product > 0) {
                                inside_hex = false;
                                return inside_hex;
                }
        }


  }

  return inside_hex;

}



} // end Utility namespace

#endif // end UTILITY_TETRAHEDRON_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TetrahedronHelpers_def.hpp
//---------------------------------------------------------------------------//
