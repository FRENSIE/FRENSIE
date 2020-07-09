//---------------------------------------------------------------------------//
//!
//! \file   Utility_PQLAQuadrature.cpp
//! \author Philip Britt
//! \brief  PQLA quadrature discretization definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_PQLAQuadrature.hpp"
#include "Utility_ExceptionTestMacros.hpp"

// std includes
#include <cmath>
#include <math.h>

namespace Utility{

// Constructor
PQLAQuadrature::PQLAQuadrature(unsigned quadrature_order)
  : d_quadrature_order(quadrature_order)
{
    // Fill in later with information needed for direction source biasing.
}

// Find which triangle bin a direction vector is in
unsigned PQLAQuadrature::findTriangleBin(const std::array<double, 3>& direction)
{

  // Convert direction vector to 1-norm vector
  std::array<double, 3> direction_normalized_1_norm = normalizeVectorToOneNorm(direction);

  return this->calculatePositiveTriangleBinIndex((unsigned)direction_normalized_1_norm[0]*(d_quadrature_order-1),
                                                 (unsigned)direction_normalized_1_norm[1]-(d_quadrature_order-1),
                                                 (unsigned)direction_normalized_1_norm[2]*(d_quadrature_order-1))
        + this->findSecondaryIndex(std::signbit(direction_normalized_1_norm[0]), 
                                    std::signbit(direction_normalized_1_norm[1]),
                                    std::signbit(direction_normalized_1_norm[2]))*d_quadrature_order^2;
}  

// Find which triangle bin a direction vector is in (takes 2-norm vector)
unsigned PQLAQuadrature::findTriangleBin( const double x_direction, const double y_direction, const double z_direction)
{
  std::array<double, 3> direction_array {x_direction, y_direction, z_direction};

  return this->findTriangleBin(direction_array);
}

unsigned PQLAQuadrature::getQuadratureOrder() const
{
  return d_quadrature_order;
}

// Converts direction vector to 1-norm normalized vector
std::array<double, 3> PQLAQuadrature::normalizeVectorToOneNorm( std::array<double, 3> direction_normalized_2_norm)
{
  double normalization_constant = fabs(direction_normalized_2_norm[0]) + fabs(direction_normalized_2_norm[1]) + fabs(direction_normalized_2_norm[2]);

  std::array<double, 3> direction_normalized_1_norm {direction_normalized_2_norm[0]/normalization_constant,
                                                     direction_normalized_2_norm[1]/normalization_constant,
                                                     direction_normalized_2_norm[2]/normalization_constant};

  return direction_normalized_1_norm;
}

// Converts direction vector to 1-norm normalized vector
std::array<double, 3> PQLAQuadrature::normalizeVectorToOneNorm(double x_direction, double y_direction, double z_direction)
{
  std::array<double, 3> direction_normalized_2_norm {x_direction, y_direction, z_direction};

  return this->normalizeVectorToOneNorm(direction_normalized_2_norm);
}

// Take lower bounding plane indices of direction vector to form triangle index
unsigned PQLAQuadrature::calculatePositiveTriangleBinIndex(const unsigned i_x, const unsigned i_y, const unsigned i_z) const
{
  if( i_x == 0 )
  {
    return d_quadrature_order + i_z - i_y - 1;
  }else
  {
    unsigned sum = 0;
    for(int i = 0; i<i_x-1; i++)
    {
      sum = sum + 2*(d_quadrature_order - i) - 1;
    }
    return sum + d_quadrature_order + i_z - i_x - i_y - 1;
  }
}

unsigned PQLAQuadrature::findSecondaryIndex(const bool x_sign, const bool y_sign, const bool z_sign) const
{
  if( x_sign && y_sign && z_sign )
  { 

    return 0;

  }else if( !x_sign && y_sign && z_sign )
  {

    return 1;

  }else if( x_sign && !y_sign && z_sign )
  {

    return 2;

  }else if( x_sign && y_sign && !z_sign )
  {

    return 3;

  }else if( !x_sign && !y_sign && z_sign )
  {

    return 4;

  }else if( !x_sign && y_sign && !z_sign )
  {

    return 5;

  }else if( x_sign && !y_sign && !z_sign)
  {

    return 6;

  }else if( !x_sign && !y_sign && !z_sign)
  {

    return 7;

  }else
  {
      THROW_EXCEPTION( std::logic_error,
                       "Sign paradox detected in PQLA direction secondary indexing" );
  }
  
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PQLAQuadrature.cpp
//---------------------------------------------------------------------------//