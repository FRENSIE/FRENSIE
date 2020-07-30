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

};

} // end Utility namespace

#endif // end UTILITY_PQLA_QUADRATURE

//---------------------------------------------------------------------------//
// end Utility_PQLADiscetization.hpp
//---------------------------------------------------------------------------//