//---------------------------------------------------------------------------//
//!
//! \file   Utility_PQLAQuadrature.cpp
//! \author Philip Britt
//! \brief  PQLA quadrature discretization definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_PQLAQuadrature.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"

// std includes
#include <cmath>

namespace Utility{

// Constructor
PQLAQuadrature::PQLAQuadrature(unsigned quadrature_order)
{
  testPrecondition(quadrature_order > 0);
  d_quadrature_order = quadrature_order;

  // Form the triangle vertices

  // Initialize triangle vertex indices at lower left corner of positive domain octahedron face
  // This point is always either at lower left end of right-side-up triangle or upper left of up-side-down triangle
  double i_x;
  double i_y;
  double i_z;

  // Used for iteration purposes (to tell where you are in use of conditionals)
  unsigned x_index;
  unsigned y_index;
  unsigned z_index;

  size_t number_of_rows = quadrature_order;
  size_t number_of_triangles_in_row = 2*d_quadrature_order-1;
  for(size_t row = 0; row < number_of_rows; ++row)
  {
    // Initialize to bottom of row
    x_index = number_of_rows - row;
    y_index = row;
    z_index = 0;

    i_x = static_cast<double>(x_index);
    i_y = static_cast<double>(y_index);
    i_z = 0.0;

    for(size_t row_triangle = 0; row_triangle < number_of_triangles_in_row; ++row_triangle)
    {
      // Array vector (for triangle formation later)
      std::vector<std::array<double, 3>> vertex_vector;
      vertex_vector.push_back({i_x, i_y, i_z});
      if(row_triangle % 2 == 0)
      {
        // Always go counter-clockwise with vertices around triangle (start lower left vertex)
        vertex_vector.push_back({i_x-1.0, i_y+1.0, i_z    });
        vertex_vector.push_back({i_x-1.0, i_y    , i_z+1.0});

        x_index = x_index - 1;
        z_index = z_index + 1;
        // y _index doesn't change;

        i_x = vertex_vector[2][0];
        i_z = vertex_vector[2][2];

      }
      else
      {
        // Always go counter-clockwise with vertices around triangle (start upper left vertex)
        vertex_vector.push_back({i_x    , i_y+1.0, i_z-1.0});
        vertex_vector.push_back({i_x-1.0, i_y+1.0, i_z    });
        // Do nothing for next triangle if triangle is pointing down (same vertex starting point for next triangle)
      }
      // normalize vectors to 2-norm (currently in 1-norm)
      
      for(size_t i = 0; i < 3; ++i)
      {
        normalizeVector(vertex_vector[i].data());
      }


      
      // calculate cosine of length of side of spherical triangle opposite from respective vertex (for use later, not kept as member data)
      std::vector<double> opposite_cos_vector {calculateCosineOfAngleBetweenUnitVectors(vertex_vector[1].data(), vertex_vector[2].data()),
                                              calculateCosineOfAngleBetweenUnitVectors(vertex_vector[0].data(), vertex_vector[2].data()),
                                              calculateCosineOfAngleBetweenUnitVectors(vertex_vector[0].data(), vertex_vector[1].data())};

      // calculate length of side of spherical triangle opposite from respective vertex (in radians b/c unit sphere)
      std::vector<double> opposite_side_length_vector{acos(opposite_cos_vector[0]), acos(opposite_cos_vector[1]), acos(opposite_cos_vector[2])};

      std::vector<double> angle_vector{acos((opposite_cos_vector[0] - opposite_cos_vector[1]*opposite_cos_vector[2])/(sin(opposite_side_length_vector[1])*sin(opposite_side_length_vector[2]))),
                                      acos((opposite_cos_vector[1] - opposite_cos_vector[0]*opposite_cos_vector[2])/(sin(opposite_side_length_vector[0])*sin(opposite_side_length_vector[2]))),
                                      acos((opposite_cos_vector[2] - opposite_cos_vector[0]*opposite_cos_vector[1])/(sin(opposite_side_length_vector[0])*sin(opposite_side_length_vector[1])))};

      // Store triangle area
      double triangle_area = angle_vector[0]+angle_vector[1]+angle_vector[2]-M_PI;

      SphericalTriangle local_triangle;

      for(size_t i = 0; i < 3; ++i)
      {
        local_triangle.triangle_parameter_vector.push_back( std::make_tuple(vertex_vector[i], opposite_side_length_vector[i], angle_vector[i]));
      }

      local_triangle.area = triangle_area;
      // Store triangle info
      d_spherical_triangle_vector.push_back(local_triangle);
    }

    number_of_triangles_in_row -= 2;
  }

  int triangle_stride = d_quadrature_order*d_quadrature_order;
  for(int i = 1; i < 8; ++i)
  {
    // Index to figure out which octant I'm in.
    int octant = i;
    int x_multiplier = 1;
    int y_multiplier = 1;
    int z_multiplier = 1;

    if(octant >= 4)
    {
      z_multiplier = -1;
      octant -= 4;
    }
    if(octant >= 2)
    {
      y_multiplier = -1;
      octant -= 2;
    }
    if(octant >= 1)
    {
      x_multiplier = -1;
      octant -= 1;
    }

    for(int j = 0; j < triangle_stride; ++j)
    {
      SphericalTriangle local_triangle = d_spherical_triangle_vector[j];
      for(int k = 0; k < 3; ++k)
      {
        std::get<0>(local_triangle.triangle_parameter_vector[k])[0] *= x_multiplier;
        std::get<0>(local_triangle.triangle_parameter_vector[k])[1] *= y_multiplier;
        std::get<0>(local_triangle.triangle_parameter_vector[k])[2] *= z_multiplier;
      }
      d_spherical_triangle_vector.push_back(local_triangle);
    }

  }
}

// Find which triangle bin a direction vector is in
size_t PQLAQuadrature::findTriangleBin(const std::array<double, 3>& direction) const
{

  // Convert direction vector to 1-norm vector
  std::array<double, 3> direction_normalized_1_norm;
  
  normalizeVectorToOneNorm(direction,
                           direction_normalized_1_norm);

  size_t result =  this->calculatePositiveTriangleBinIndex(static_cast<int>(fabs(direction_normalized_1_norm[0])*d_quadrature_order),
                                                 static_cast<int>(fabs(direction_normalized_1_norm[1])*d_quadrature_order),
                                                 static_cast<int>(fabs(direction_normalized_1_norm[2])*d_quadrature_order))
         +this->findSecondaryIndex(std::signbit(direction_normalized_1_norm[0]), 
                                    std::signbit(direction_normalized_1_norm[1]),
                                    std::signbit(direction_normalized_1_norm[2]))*std::pow(d_quadrature_order, 2);
  return result;
}  

// Find which triangle bin a direction vector is in (takes 2-norm vector)
size_t PQLAQuadrature::findTriangleBin( const double x_direction, const double y_direction, const double z_direction) const
{
  std::array<double, 3> direction_array {x_direction, y_direction, z_direction};

  return this->findTriangleBin(direction_array);
}

// Return the order of the quadrature
unsigned PQLAQuadrature::getQuadratureOrder() const
{
  return d_quadrature_order;
}

// Return the total number of triangles
size_t PQLAQuadrature::getNumberOfTriangles() const
{
  return 8*pow(d_quadrature_order,2);
}

// Return the area of a triangle
double PQLAQuadrature::getTriangleArea(const size_t triangle_index) const
{
  testPrecondition(triangle_index >= 0 && triangle_index <= this->getNumberOfTriangles()-1);
  return d_spherical_triangle_vector[triangle_index].area;
}

// Return a random direction from within a spherical triangle
void PQLAQuadrature::sampleIsotropicallyFromTriangle(std::array<double, 3>& direction_vector,
                                                     const size_t triangle_index) const
{
  SphericalTriangle triangle;
  this->getSphericalTriangle(triangle_index,
                             triangle);

  double random_area = RandomNumberGenerator::getRandomNumber<double>()*triangle.area;

  double s = sin(random_area - std::get<2>(triangle.triangle_parameter_vector[0]));
  double t = cos(random_area - std::get<2>(triangle.triangle_parameter_vector[0]));

  double u = t - cos(std::get<2>(triangle.triangle_parameter_vector[0]));
  double v = s + sin(std::get<2>(triangle.triangle_parameter_vector[0]))*cos(std::get<1>(triangle.triangle_parameter_vector[2]));

  double q = ((v*t - u*s)*cos(std::get<2>(triangle.triangle_parameter_vector[0])) - v)/
             ((v*s + u*t)*sin(std::get<2>(triangle.triangle_parameter_vector[0])));

  std::array<double, 3> C_hat;
  std::array<double, 3> vector_operation_result;
  this->isotropicSamplingVectorOperation(std::get<0>(triangle.triangle_parameter_vector[2]),
                                         std::get<0>(triangle.triangle_parameter_vector[0]),
                                         vector_operation_result);
  for(int i = 0; i < 3; ++i)
  {
    C_hat[i] = q*std::get<0>(triangle.triangle_parameter_vector[0])[i]+sqrt(1-q*q)*vector_operation_result[i];
  }

  double z = 1-RandomNumberGenerator::getRandomNumber<double>()*(1-calculateCosineOfAngleBetweenUnitVectors(C_hat.data(), std::get<0>(triangle.triangle_parameter_vector[1]).data()));

  this->isotropicSamplingVectorOperation(C_hat,
                                         std::get<0>(triangle.triangle_parameter_vector[1]),
                                         vector_operation_result);
  for(int i = 0; i < 3; ++i)
  {
    direction_vector[i] = z*std::get<0>(triangle.triangle_parameter_vector[1])[i] + sqrt(1-z*z)*vector_operation_result[i];
  }
}

// Method for a vector operation in support of above isotropic sampling method
void PQLAQuadrature::isotropicSamplingVectorOperation(const std::array<double, 3>& vertex_1,
                                      const std::array<double, 3>& vertex_2,
                                      std::array<double, 3>& result_vector) const
{
  double dot_product_result = calculateCosineOfAngleBetweenUnitVectors( vertex_1.data(), vertex_2.data() );
  for(int i = 0; i < 3; ++i)
  {
    result_vector[i] = vertex_1[i] - dot_product_result*vertex_2[i];
  }
  normalizeVector(result_vector.data());
  testPostcondition(isUnitVector(result_vector.data()));
}

// Converts direction vector to 1-norm normalized vector
void PQLAQuadrature::normalizeVectorToOneNorm( const std::array<double, 3>& direction_normalized_2_norm,
                                               std::array<double, 3>& direction_normalized_1_norm ) const
{
  double normalization_constant = fabs(direction_normalized_2_norm[0]) + fabs(direction_normalized_2_norm[1]) + fabs(direction_normalized_2_norm[2]);

  for(int i = 0; i < 3; ++i)
  {
    direction_normalized_1_norm[i] = direction_normalized_2_norm[i]/normalization_constant;
  }

}

// Converts direction vector to 1-norm normalized vector
void PQLAQuadrature::normalizeVectorToOneNorm(  const double x_direction,
                                                const double y_direction, 
                                                const double z_direction,
                                                std::array<double, 3>& direction_normalized_1_norm) const
{
  std::array<double, 3> direction_normalized_2_norm {x_direction, y_direction, z_direction};

  this->normalizeVectorToOneNorm( direction_normalized_2_norm,
                                  direction_normalized_1_norm );
}

// Take lower bounding plane indices of direction vector to form triangle index
size_t PQLAQuadrature::calculatePositiveTriangleBinIndex(const unsigned i_x, const unsigned i_y, const unsigned i_z) const
{

  unsigned sum = 0;
  /* If not on the first row (first i_x plane), first row has 2N-1 triangles, and 2 less with every row from there.
    Calculate the sum of these elements until the relevant row is found*/
  for(unsigned i = 0; i<i_y; ++i)
  {
    sum = sum + 2*(d_quadrature_order - i) - 1;
  }
  // Add the basic equation for calculating the triangle index
  sum = sum + d_quadrature_order + i_z - i_x - i_y - 1;

  // handle edge cases, default to lower plane index on edge cases (i_z is added, i_y is subtracted, making the below logic correct)
  if( i_x + i_y + i_z == d_quadrature_order)
  {
    if( i_z > 0 )
    {
      sum = sum - 1;
    }else if (i_y != d_quadrature_order)
    {
      sum = sum + 1;
    }
  }
  return sum;
}

// Returns the index for the octant that a direction is in
size_t PQLAQuadrature::findSecondaryIndex(const bool x_sign, const bool y_sign, const bool z_sign) const
{
  size_t secondary_index = 0;

  if (x_sign) secondary_index += 1;
  if (y_sign) secondary_index += 2;
  if (z_sign) secondary_index += 4;

  return secondary_index;
  
}

// Return a spherical triangle struct
void PQLAQuadrature::getSphericalTriangle(const size_t triangle_index,
                                                             SphericalTriangle& triangle) const
{
  testPrecondition(triangle_index >= 0 && triangle_index <= this->getNumberOfTriangles()-1);
  triangle = d_spherical_triangle_vector[triangle_index];
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PQLAQuadrature.cpp
//---------------------------------------------------------------------------//