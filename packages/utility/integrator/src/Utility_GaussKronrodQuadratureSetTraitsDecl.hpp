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

  //! Gauss-Kronrod quadrature set traits 
  template<int Points>
  struct GaussKronrodQuadratureSetTraits
  {
    //! Valid rule
    static const bool valid_rule = false;

    //! Gauss quadrature weights 
    static const std::vector<long double> gauss_weights;
    
    //! Kronrad quadrature weights 
    static const std::vector<long double> kronrod_weights;

    //! Kronrad quadrature abscissae
    static const std::vector<long double> kronrod_abscissae;

    private:

    // Initialize the gauss weight array
    static inline std::vector<long double> initializeGaussWeights()
    { return std::vector<long double>(); }

    // Initialize the kronrod weight array
    static inline std::vector<long double> initializeKronrodWeights()
    { return std::vector<long double>(); }

    // Initialize the gauss weight array
    static inline std::vector<long double> initializeKronrodAbscissae()
    { return std::vector<long double>(); }
  };

} // end Utility namespace

#endif // end UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodQuadratureSetTraitsDecl.hpp
//---------------------------------------------------------------------------//
