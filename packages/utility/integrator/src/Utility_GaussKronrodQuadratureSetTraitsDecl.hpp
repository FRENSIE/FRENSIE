//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodQuadratureSetTraitsDecl.hpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod quadrature set traits declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_DECL_HPP
#define UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_DECL_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

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
    static const Teuchos::Array<double> gauss_weights;
    
    //! Kronrad quadrature weights 
    static const Teuchos::Array<double> kronrod_weights;

    //! Kronrad quadrature abscissae
    static const Teuchos::Array<double> kronrod_abscissae;

    private:

    // Initialize the gauss weight array
    static inline Teuchos::Array<double> initializeGaussWeights()
    { return Teuchos::Array<double>(); }

    // Initialize the kronrod weight array
    static inline Teuchos::Array<double> initializeKronrodWeights()
    { return Teuchos::Array<double>(); }

    // Initialize the gauss weight array
    static inline Teuchos::Array<double> initializeKronrodAbscissae()
    { return Teuchos::Array<double>(); }
  };

} // end Utility namespace

#endif // end UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodQuadratureSetTraitsDecl.hpp
//---------------------------------------------------------------------------//
