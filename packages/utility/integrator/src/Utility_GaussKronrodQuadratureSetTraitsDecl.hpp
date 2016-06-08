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

// Boost Includes
#include <boost/multiprecision/cpp_dec_float.hpp>

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

namespace Utility{

typedef boost::multiprecision::cpp_dec_float_50 long_float;

  //! Gauss-Kronrod quadrature set traits 
  template<int Points>
  struct GaussKronrodQuadratureSetTraits
  {
    //! Valid rule
    static const bool valid_rule = false;

    //! Gauss quadrature weights 
    static const std::vector<long_float> gauss_weights;
    
    //! Kronrad quadrature weights 
    static const std::vector<long_float> kronrod_weights;

    //! Kronrad quadrature abscissae
    static const std::vector<long_float> kronrod_abscissae;

    private:

    // Initialize the gauss weight array
    static inline std::vector<long_float> initializeGaussWeights()
    { return std::vector<long_float>(); }

    // Initialize the kronrod weight array
    static inline std::vector<long_float> initializeKronrodWeights()
    { return std::vector<long_float>(); }

    // Initialize the gauss weight array
    static inline std::vector<long_float> initializeKronrodAbscissae()
    { return std::vector<long_float>(); }
  };

} // end Utility namespace

#endif // end UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodQuadratureSetTraitsDecl.hpp
//---------------------------------------------------------------------------//
