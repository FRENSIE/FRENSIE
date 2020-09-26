//---------------------------------------------------------------------------//
//!
//! \file   Utility_PQLAQuadrature.hpp
//! \author Philip Britt
//! \brief  PQLA Direction Quadrature handler declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PQLA_QUADRATURE
#define UTILITY_PQLA_QUADRATURE

// FRENSIE includes
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Array.hpp"

namespace Utility{

struct SphericalTriangle
{
  /*! Vector that contains a tuple representing spherical triangle parameters.
   * \details First element of the tuple is an array that contains the
   * 2-norm direction representing a vertex of the triangle. 
   * Second is the length of the spherical triangle side opposite from that vertex
   * (or angle that the 2 other vertices of the triangle make with each other).
   * Third is the angle made from the sides of the spherical triangle from that vertex.
   * Note their order does NOT matter so long as they are consistent with the above definition
   */
  std::vector<std::tuple<std::array<double, 3>, double, double>> triangle_parameter_vector;

  //! Area of the triangle
  double area;
};

class PQLAQuadrature
{

  public:

  //! Constructor
  PQLAQuadrature(unsigned quadrature_order);

  //! Destructor
  ~PQLAQuadrature()
  { /* ... */ }

  //! Find which triangle bin a direction vector is in
  unsigned findTriangleBin( const std::array<double, 3>& direction) const;

  //! Find which triangle bin a direction vector is in
  unsigned findTriangleBin( const double x_direction, const double y_direction, const double z_direction) const;

  //! Return the order of the quadrature
  unsigned getQuadratureOrder() const;

  size_t getNumberOfTriangles() const;

  double getTriangleArea(size_t triangle_index) const;

  void sampleIsotropicallyFromTriangle(std::array<double, 3>& direction_vector);

  private:

  //! Converts direction vector to 1-norm normalized vector
  void normalizeVectorToOneNorm( const std::array<double, 3>& direction_2_norm,
                                 std::array<double, 3>& direction_1_norm) const;
  
  //! Converts direction vector to 1-norm normalized vector
  void normalizeVectorToOneNorm(  const double x_direction, 
                                  const double y_direction, 
                                  const double z_direction,
                                  std::array<double, 3>& direction_1_norm) const;

  //! Take lower bounding plane indices of direction vector to form triangle index
  unsigned calculatePositiveTriangleBinIndex(const unsigned i_x, const unsigned i_y, const unsigned i_z) const;

  //! Take direction signs to calculate secondary index
  unsigned findSecondaryIndex(const bool x_sign, const bool y_sign, const bool z_sign) const;

  //! Quadrature order
  unsigned d_quadrature_order;

  // Vector that stores POSITIVE DOMAIN spherical triangles
  std::vector<SphericalTriangle> d_spherical_triangle_vector;

};

} // end Utility namespace

#endif // end UTILITY_PQLA_QUADRATURE

//---------------------------------------------------------------------------//
// end Utility_PQLADiscetization.hpp
//---------------------------------------------------------------------------//