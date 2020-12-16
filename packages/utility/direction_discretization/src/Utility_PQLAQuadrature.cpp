//---------------------------------------------------------------------------//
//!
//! \file   Utility_PQLAQuadrature.cpp
//! \author Philip Britt
//! \brief  PQLA quadrature discretization definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_PQLAQuadrature.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"

// std includes
#include <cmath>

namespace Utility{

// Constructor
PQLAQuadrature::PQLAQuadrature(unsigned quadrature_order)
{
  testPrecondition(quadrature_order > 0);
  d_quadrature_order = quadrature_order;

  //MORE COMMENTS
  // CLEAN UP get<> statements

  // Form the triangle vertices

  // Initialize triangle vertex indices at lower left corner of positive domain octahedron face
  // This point is always either at lower left end of right-side-up triangle or upper left of up-side-down triangle
  double i_x;
  double i_y;
  double i_z;
  
  size_t number_of_triangles_in_row = 2*d_quadrature_order-1;
  for(size_t row = 0; row < d_quadrature_order; ++row)
  {
    // Initialize to bottom of row
    i_x = static_cast<double>(d_quadrature_order - row);
    i_y = static_cast<double>(row);
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
      // normalize vectors to 2-norm (currently indices of planes)
      
      for(size_t i = 0; i < 3; ++i)
      {
        normalizeVector(vertex_vector[i].data());
      }

      SphericalTriangle local_triangle;
      local_triangle.computeAndStoreTriangleParameters(vertex_vector);

      // Store triangle info
      d_spherical_triangle_vector.push_back(local_triangle);
    }

    number_of_triangles_in_row -= 2;
  }

  int triangle_stride = d_quadrature_order*d_quadrature_order;
  for(int octant = 1; octant < 8; ++octant)
  {

    int x_multiplier = 1;
    int y_multiplier = 1;
    int z_multiplier = 1;

    // Bitwise operations to tell which octant this is
    if(octant & 1) x_multiplier = -1;
    if(octant & 2) y_multiplier = -1;
    if(octant & 4) z_multiplier = -1;

    for(int tri = 0; tri < triangle_stride; ++tri)
    {
      SphericalTriangle local_triangle = d_spherical_triangle_vector[tri];
      for(int vert = 0; vert < 3; ++vert)
      {
        std::array<double, 3>& vertex_vector = std::get<0>(local_triangle.triangle_parameter_vector[vert]);

        vertex_vector[0] *= x_multiplier;
        vertex_vector[1] *= y_multiplier;
        vertex_vector[2] *= z_multiplier;
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

  return this->calculatePositiveTriangleBinIndex(static_cast<int>(fabs(direction_normalized_1_norm[0])*d_quadrature_order),
                                                 static_cast<int>(fabs(direction_normalized_1_norm[1])*d_quadrature_order),
                                                 static_cast<int>(fabs(direction_normalized_1_norm[2])*d_quadrature_order))
         +this->findSecondaryIndex(std::signbit(direction_normalized_1_norm[0]), 
                                    std::signbit(direction_normalized_1_norm[1]),
                                    std::signbit(direction_normalized_1_norm[2]))*d_quadrature_order*d_quadrature_order;
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
  return 8*d_quadrature_order*d_quadrature_order;
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
  testPrecondition(triangle_index >= 0 && triangle_index <= this->getNumberOfTriangles()-1);
  SphericalTriangle triangle = d_spherical_triangle_vector[triangle_index];

  std::array<double, 3>& vertex_A_vector = std::get<0>(triangle.triangle_parameter_vector[0]);
  std::array<double, 3>& vertex_B_vector = std::get<0>(triangle.triangle_parameter_vector[1]);
  std::array<double, 3>& vertex_C_vector = std::get<0>(triangle.triangle_parameter_vector[2]);

  double& opposite_side_length_A = std::get<2>(triangle.triangle_parameter_vector[0]);

  double& vertex_angle_B = std::get<1>(triangle.triangle_parameter_vector[2]);

  double random_area = RandomNumberGenerator::getRandomNumber<double>()*triangle.area;

  double s = sin(random_area - opposite_side_length_A);
  double t = cos(random_area - opposite_side_length_A);

  double u = t - cos(opposite_side_length_A);
  double v = s + sin(opposite_side_length_A)*cos(vertex_angle_B);

  double q = ((v*t - u*s)*cos(opposite_side_length_A) - v)/
             ((v*s + u*t)*sin(opposite_side_length_A));

  std::array<double, 3> C_hat;
  std::array<double, 3> vector_operation_result;
  this->isotropicSamplingVectorOperation(vertex_C_vector,
                                         vertex_A_vector,
                                         vector_operation_result);


  for(int dim = 0; dim < 3; ++dim)
  {
    C_hat[dim] = q*vertex_A_vector[dim]+sqrt(1-q*q)*vector_operation_result[dim];
  }

  double z = 1-RandomNumberGenerator::getRandomNumber<double>()*(1-calculateCosineOfAngleBetweenUnitVectors(C_hat.data(), vertex_B_vector.data()));

  this->isotropicSamplingVectorOperation(C_hat,
                                         vertex_B_vector,
                                         vector_operation_result);
  for(int dim = 0; dim < 3; ++dim)
  {
    direction_vector[dim] = z*vertex_B_vector[dim] + sqrt(1-z*z)*vector_operation_result[dim];
  }
}

// Method for a vector operation in support of above isotropic sampling method
void PQLAQuadrature::isotropicSamplingVectorOperation(const std::array<double, 3>& vertex_1,
                                      const std::array<double, 3>& vertex_2,
                                      std::array<double, 3>& result_vector) const
{
  double dot_product_result = calculateCosineOfAngleBetweenUnitVectors( vertex_1.data(), vertex_2.data() );
  for(int dim = 0; dim < 3; ++dim)
  {
    result_vector[dim] = vertex_1[dim] - dot_product_result*vertex_2[dim];
  }
  normalizeVector(result_vector.data());
  testPostcondition(isUnitVector(result_vector.data()));
}

// Converts direction vector to 1-norm normalized vector
void PQLAQuadrature::normalizeVectorToOneNorm( const std::array<double, 3>& direction_normalized_2_norm,
                                               std::array<double, 3>& direction_normalized_1_norm ) const
{
  double normalization_constant = fabs(direction_normalized_2_norm[0]) + fabs(direction_normalized_2_norm[1]) + fabs(direction_normalized_2_norm[2]);

  if(normalization_constant > 0)
  {
    for(int dim = 0; dim < 3; ++dim)
    {
      direction_normalized_1_norm[dim] = direction_normalized_2_norm[dim]/normalization_constant;
    }
  } else
  {
    THROW_EXCEPTION(std::runtime_error, " Normalization constant <= 0 ")
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

const std::vector<SphericalTriangle>& PQLAQuadrature::getSphericalTriangleVector() const
{
  return d_spherical_triangle_vector;
}

void SphericalTriangle::computeAndStoreTriangleParameters(std::vector<std::array<double, 3>>& vertex_vector)
{
  // Put methods in struct to simplify this part.
  
  // calculate cosine of length of side of spherical triangle opposite from respective vertex (for use later, not kept as member data)
  std::vector<double> opposite_cos_vector {calculateCosineOfAngleBetweenUnitVectors(vertex_vector[1].data(), vertex_vector[2].data()),
                                            calculateCosineOfAngleBetweenUnitVectors(vertex_vector[0].data(), vertex_vector[2].data()),
                                            calculateCosineOfAngleBetweenUnitVectors(vertex_vector[0].data(), vertex_vector[1].data())};

  // calculate length of side of spherical triangle opposite from respective vertex (in radians b/c unit sphere)
  std::vector<double> opposite_side_length_vector{acos(opposite_cos_vector[0]), acos(opposite_cos_vector[1]), acos(opposite_cos_vector[2])};

  std::vector<double> angle_vector{acos((opposite_cos_vector[0] - opposite_cos_vector[1]*opposite_cos_vector[2])/(sin(opposite_side_length_vector[1])*sin(opposite_side_length_vector[2]))),
                                  acos((opposite_cos_vector[1] - opposite_cos_vector[0]*opposite_cos_vector[2])/(sin(opposite_side_length_vector[0])*sin(opposite_side_length_vector[2]))),
                                  acos((opposite_cos_vector[2] - opposite_cos_vector[0]*opposite_cos_vector[1])/(sin(opposite_side_length_vector[0])*sin(opposite_side_length_vector[1])))};

  for(size_t vert = 0; vert < 3; ++vert)
  {
    triangle_parameter_vector.push_back( std::make_tuple(vertex_vector[vert], opposite_side_length_vector[vert], angle_vector[vert]));
  }

  // Store triangle area
  area = angle_vector[0]+angle_vector[1]+angle_vector[2]-M_PI;
}

EXPLICIT_CLASS_SERIALIZE_INST( PQLAQuadrature );
} // end Utility namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( PQLAQuadrature, Utility );

//---------------------------------------------------------------------------//
// end Utility_PQLAQuadrature.cpp
//---------------------------------------------------------------------------//