//---------------------------------------------------------------------------//
//!
//! \file   Utility_PQLAQuadrature.cpp
//! \author Philip Britt
//! \brief  PQLA quadrature discretization definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_PQLAQuadrature.hpp"

// std includes
#include <cmath>

namespace MonteCarlo{

  // Constructor
  PQLAQuadrature::PQLAQuadrature(unsigned quadrature_order)
  :d_quadrature_order(quadrature_order)
  {
    // Fill in later with information needed for direction source biasing.
  }

  // Find which triangle bin a direction vector is in
  unsigned PQLAQuadrature::findTriangleBin(const double[3]& direction) const
  {
    return this->findTriangleBin(direction[0], direction[1], direction[2];
  }  

  // Find which triangle bin a direction vector is in
  unsigned PQLAQuadrature::findTriangleBin( const double x_direction, const double y_direction, const double z_direction) const
  {
     return this->calculateTriangleIndex((unsigned)x_direction*(d_quadrature_order-1),
                                          (unsigned)y_direction*(d_quadrature_order-1),
                                          (unsigned)z_direction*(d_quadrature_order-1))
            + this->findSecondaryIndex(std::signbit(x_direction), 
                                       std::signbit(y_direction),
                                       std::signbit(z_direction))*d_quadrature_order^2;
  }

  // Take lower bounding plane indices of direction vector to form triangle index
  unsigned PQLAQuadrature::calculateTriangleIndex(const unsigned i_x, const unsigned i_y, const unsigned i_z) const
  {
    if i_x == 0
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
    if(x_sign && y_sign && z_sign)
    { 

      return 0;

    }else if(!x_sign && y_sign && z_sign)
    {

      return 1;

    }else if(x_sign && !y_sign && z_sign)
    {

      return 2;

    }else if(x_sign && y_sign && !z_sign)
    {

      return 3;

    }else if(!x_sign && !y_sign && z_sign)
    {

      return 4;

    }else if(!x_sign && y_sign && !z_sign)
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
      /* something went wrong */
    }
    
  }

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PQLAQuadrature.cpp
//---------------------------------------------------------------------------//