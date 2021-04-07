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

// std includes
#include <cmath>
#include <math.h>
#include <iostream>

namespace Utility{

// Constructor
PQLAQuadrature::PQLAQuadrature(unsigned quadrature_order)
  : d_quadrature_order(quadrature_order)
{
  testPrecondition(quadrature_order > 0);
    // Fill in later with information needed for direction source biasing.
}

// Find which triangle bin a direction vector is in
unsigned PQLAQuadrature::findTriangleBin(const std::array<double, 3>& direction) const
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
                                    std::signbit(direction_normalized_1_norm[2]))*std::pow(d_quadrature_order, 2);
}  

// Find which triangle bin a direction vector is in (takes 2-norm vector)
unsigned PQLAQuadrature::findTriangleBin( const double x_direction, const double y_direction, const double z_direction) const
{
  std::array<double, 3> direction_array {x_direction, y_direction, z_direction};

  return this->findTriangleBin(direction_array);
}

unsigned PQLAQuadrature::getQuadratureOrder() const
{
  return d_quadrature_order;
}

// Converts direction vector to 1-norm normalized vector
void PQLAQuadrature::normalizeVectorToOneNorm( const std::array<double, 3>& direction_normalized_2_norm,
                                               std::array<double, 3>& direction_normalized_1_norm ) const
{
  double normalization_constant = fabs(direction_normalized_2_norm[0]) + fabs(direction_normalized_2_norm[1]) + fabs(direction_normalized_2_norm[2]);

  direction_normalized_1_norm[0] = direction_normalized_2_norm[0]/normalization_constant;
  direction_normalized_1_norm[1] = direction_normalized_2_norm[1]/normalization_constant;
  direction_normalized_1_norm[2] = direction_normalized_2_norm[2]/normalization_constant;
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
unsigned PQLAQuadrature::calculatePositiveTriangleBinIndex(const unsigned i_x, const unsigned i_y, const unsigned i_z) const
{

  unsigned sum = 0;
  /* If not on the first row (first i_x plane), first row has 2N-1 triangles, and 2 less with every row from there.
    Calculate the sum of these elements until the relevant row is found*/
  for(unsigned i = 0; i<i_x; i++)
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
    }else if (i_x != d_quadrature_order)
    {
      sum = sum + 1;
    }
  }
  return sum;
}

// Returns the index for the octant that a direction is in
unsigned PQLAQuadrature::findSecondaryIndex(const bool x_sign, const bool y_sign, const bool z_sign) const
{
  unsigned secondary_index = 0;

  if (x_sign) secondary_index += 1;
  if (y_sign) secondary_index += 2;
  if (z_sign) secondary_index += 4;

  return secondary_index;
  
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PQLAQuadrature.cpp
//---------------------------------------------------------------------------//