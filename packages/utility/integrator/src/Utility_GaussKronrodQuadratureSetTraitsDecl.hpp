//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodQuadratureSetTraitsDecl.hpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod quadrature set traits declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_DECL_HPP
#define UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_DECL_HPP

// std Includes
#include <vector>

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

namespace Utility{

//typedef boost::multiprecision::cpp_dec_float_50 long_float;

//! Gauss-Kronrod quadrature set traits
template<int Points, typename FloatType, typename Enabled = void>
struct GaussKronrodQuadratureSetTraits
{
  //! Valid rule
  static const bool valid_rule = false;

  //! Gauss quadrature weights
  static const std::vector<FloatType> gauss_weights;

  //! Kronrod quadrature weights
  static const std::vector<FloatType> kronrod_weights;

  //! Kronrod quadrature abscissae
  static const std::vector<FloatType> kronrod_abscissae;

private:

  // Initialize the gauss weight array
  static inline std::vector<FloatType> initializeGaussWeights()
  { return std::vector<FloatType>(); }

  // Initialize the kronrod weight array
  static inline std::vector<FloatType> initializeKronrodWeights()
  { return std::vector<FloatType>(); }

  // Initialize the gauss weight array
  static inline std::vector<FloatType> initializeKronrodAbscissae()
  { return std::vector<FloatType>(); }
};

} // end Utility namespace

#endif // end UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodQuadratureSetTraitsDecl.hpp
//---------------------------------------------------------------------------//
