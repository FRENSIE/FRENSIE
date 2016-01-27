//---------------------------------------------------------------------------//
//!
//! \file   Utility_HexahedronHelpers.hpp
//! \author Luke Kersting, Philip Britt
//! \brief  Hexahedron helper functions
//! 
//---------------------------------------------------------------------------//

#ifndef UTILITY_HEXAHEDRON_HELPERS_HPP
#define UTILITY_HEXAHEDRON_HELPERS_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseMatrix.hpp>
#include <Teuchos_TwoDArray.hpp>
#include <Teuchos_Array.hpp>


// Moab Includes
#include <moab/CartVect.hpp>
#include <moab/Matrix3.hpp>

namespace Utility{

Teuchos::Array<double> crossProduct(const double vertex_1[3],
                                    const double vertex_2[3],
                                    const double vertex_3[3]);

//! Calculate the volume of a hexahedron
double calculateHexahedronVolume(  const double vertex_a[3],
				   const double vertex_b[3],
				   const double vertex_c[3],
				   const double vertex_d[3],
				   const double vertex_e[3],
				   const double vertex_f[3],
				   const double vertex_g[3],
				   const double vertex_h[3]);

//! Calculate the volume of a hexahedron
double calculateHexahedronVolume( const moab::CartVect& vertex_a,
				  const moab::CartVect& vertex_b,
				  const moab::CartVect& vertex_c,
				  const moab::CartVect& vertex_d,
				  const moab::CartVect& vertex_e,
				  const moab::CartVect& vertex_f,
				  const moab::CartVect& vertex_g,
				  const moab::CartVect& vertex_h);

//! Calculate hexahedron facenormal vectors
void calculateFaceNormals( const double vertex_a[3],
			   const double vertex_b[3],
		           const double vertex_c[3],
			   const double vertex_d[3],
			   const double vertex_e[3],
			   const double vertex_f[3],
		           const double vertex_g[3],
		           const double vertex_h[3],
                           Teuchos::TwoDArray<double>& face_normals);

//! Calculate hexahedron facenormal vectors
void calculateFaceNormals( const moab::CartVect& vertex_a,
		           const moab::CartVect& vertex_b,
			   const moab::CartVect& vertex_c,
			   const moab::CartVect& vertex_d,
			   const moab::CartVect& vertex_e,
			   const moab::CartVect& vertex_f,
			   const moab::CartVect& vertex_g,
			   const moab::CartVect& vertex_h,
			   Teuchos::TwoDArray<double>& face_normals );


//! Return if a point is in a hex 
template<typename TestPoint, typename ReferencePoint, typename Matrix>
bool isPointInHex( const TestPoint& point,
                   const ReferencePoint& reference_vertex,
                   const Matrix& matrix,
		   const double tol = 1e-6 );
//edited version
template<typename TestPoint>
bool isPointInHex( const TestPoint& point,
                   const Teuchos::TwoDArray<double>& face_normals,
		   const double tol = 1e-6 );
                   
//! Return if a point is in a hex - should be deleted since both calculations above output same type of array
template<typename TestPoint, typename ReferencePoint>
bool isPointInHex( const TestPoint& point,
                   const ReferencePoint& reference_vertex,
		   const double barycentric_array[9] );
               
// Calculate the volume of a hexahedron
inline double calculateHexahedronVolume( const moab::CartVect& vertex_a,
				         const moab::CartVect& vertex_b,
				         const moab::CartVect& vertex_c,
				         const moab::CartVect& vertex_d,
				         const moab::CartVect& vertex_e,
				         const moab::CartVect& vertex_f,
				         const moab::CartVect& vertex_g,
				         const moab::CartVect& vertex_h)
{
  return calculateHexahedronVolume( vertex_a.array(),
				    vertex_b.array(),
				    vertex_c.array(),
				    vertex_d.array(),
				    vertex_e.array(),
				    vertex_f.array(),
				    vertex_g.array(),
				    vertex_h.array() );
}

// Calculate hexahedron face normal vectors
inline void calculateFaceNormals( const moab::CartVect& vertex_a,
				  const moab::CartVect& vertex_b,
				  const moab::CartVect& vertex_c,
				  const moab::CartVect& vertex_d,
				  const moab::CartVect& vertex_e,
				  const moab::CartVect& vertex_f,
				  const moab::CartVect& vertex_g,
				  const moab::CartVect& vertex_h,
			          Teuchos::TwoDArray<double>& face_normals)
{
  calculateFaceNormals( vertex_a.array(),
		        vertex_b.array(),
			vertex_c.array(),
			vertex_d.array(),
		        vertex_e.array(),
			vertex_f.array(),
			vertex_g.array(),
			vertex_h.array(),
                        face_normals );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_HexahedronHelpers_def.hpp"

//---------------------------------------------------------------------------//


#endif // end UTILITY_HEXAHEDRON_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_HexahedronHelpers.hpp
//---------------------------------------------------------------------------//
