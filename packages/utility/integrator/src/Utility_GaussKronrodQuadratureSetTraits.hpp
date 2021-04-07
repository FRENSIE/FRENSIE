//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodQuadratureSetTraits.hpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod quadrature set traits
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_HPP
#define UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_HPP

// Boost Includes
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>

// FRENSIE Includes
#include "Utility_GaussKronrodQuadratureSetTraitsDecl.hpp"
#include "Utility_IsFloatingPoint.hpp"

namespace Utility{

// Gauss-Kronrod quadrature set traits 15 point rule
template<typename FloatType>
struct GaussKronrodQuadratureSetTraits<15,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>
{
  // Valid rule
  static const bool valid_rule = true;

  // Gauss quadrature weights
  static const std::vector<FloatType> gauss_weights;

  // Kronrod quadrature weights
  static const std::vector<FloatType> kronrod_weights;

  // Kronrod quadrature abscissae
  static const std::vector<FloatType> kronrod_abscissae;

private:

  // Initialize the gauss weight array
  static std::vector<FloatType> initializeGaussWeights();

  // Initialize the kronrod weight array
  static std::vector<FloatType> initializeKronrodWeights();

  // Initialize the gauss weight array
  static std::vector<FloatType> initializeKronrodAbscissae();
};

// Gauss-Kronrod quadrature set traits 21 point rule
template<typename FloatType>
struct GaussKronrodQuadratureSetTraits<21,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>
{
  // Valid rule
  static const bool valid_rule = true;

  // Gauss quadrature weights
  static const std::vector<FloatType> gauss_weights;

  // Kronrod quadrature weights
  static const std::vector<FloatType> kronrod_weights;

  // Kronrod quadrature abscissae
  static const std::vector<FloatType> kronrod_abscissae;

private:

  // Initialize the gauss weight array
  static std::vector<FloatType> initializeGaussWeights();

  // Initialize the kronrod weight array
  static std::vector<FloatType> initializeKronrodWeights();

  // Initialize the gauss weight array
  static std::vector<FloatType> initializeKronrodAbscissae();
};

// Gauss-Kronrod quadrature set traits 31 point rule
template<typename FloatType>
struct GaussKronrodQuadratureSetTraits<31,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>
{
  // Valid rule
  static const bool valid_rule = true;

  // Gauss quadrature weights
  static const std::vector<FloatType> gauss_weights;

  // Kronrod quadrature weights
  static const std::vector<FloatType> kronrod_weights;

  // Kronrod quadrature abscissae
  static const std::vector<FloatType> kronrod_abscissae;

private:

  // Initialize the gauss weight array
  static std::vector<FloatType> initializeGaussWeights();

  // Initialize the kronrod weight array
  static std::vector<FloatType> initializeKronrodWeights();

  // Initialize the gauss weight array
  static std::vector<FloatType> initializeKronrodAbscissae();
};

// Gauss-Kronrod quadrature set traits 41 point rule
template<typename FloatType>
struct GaussKronrodQuadratureSetTraits<41,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>
{
  // Valid rule
  static const bool valid_rule = true;

  // Gauss quadrature weights
  static const std::vector<FloatType> gauss_weights;

  // Kronrod quadrature weights
  static const std::vector<FloatType> kronrod_weights;

  // Kronrod quadrature abscissae
  static const std::vector<FloatType> kronrod_abscissae;

private:

  // Initialize the gauss weight array
  static std::vector<FloatType> initializeGaussWeights();

  // Initialize the kronrod weight array
  static std::vector<FloatType> initializeKronrodWeights();

  // Initialize the gauss weight array
  static std::vector<FloatType> initializeKronrodAbscissae();
};

// Gauss-Kronrod quadrature set traits 51 point rule
template<typename FloatType>
struct GaussKronrodQuadratureSetTraits<51,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>
{
  // Valid rule
  static const bool valid_rule = true;

  // Gauss quadrature weights
  static const std::vector<FloatType> gauss_weights;

  // Kronrod quadrature weights
  static const std::vector<FloatType> kronrod_weights;

  // Kronrod quadrature abscissae
  static const std::vector<FloatType> kronrod_abscissae;

private:

  // Initialize the gauss weight array
  static std::vector<FloatType> initializeGaussWeights();

  // Initialize the kronrod weight array
  static std::vector<FloatType> initializeKronrodWeights();

  // Initialize the gauss weight array
  static std::vector<FloatType> initializeKronrodAbscissae();
};

// Gauss-Kronrod quadrature set traits 61 point rule
template<typename FloatType>
struct GaussKronrodQuadratureSetTraits<61,FloatType,typename boost::enable_if<IsFloatingPoint<FloatType> >::type>
{
  // Valid rule
  static const bool valid_rule = true;

  // Gauss quadrature weights
  static const std::vector<FloatType> gauss_weights;

  // Kronrod quadrature weights
  static const std::vector<FloatType> kronrod_weights;

  // Kronrod quadrature abscissae
  static const std::vector<FloatType> kronrod_abscissae;

private:

  // Initialize the gauss weight array
  static std::vector<FloatType> initializeGaussWeights();

  // Initialize the kronrod weight array
  static std::vector<FloatType> initializeKronrodWeights();

  // Initialize the gauss weight array
  static std::vector<FloatType> initializeKronrodAbscissae();
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_GaussKronrodQuadratureSetTraits_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_GAUSS_KRONROD_QUADRATURE_SET_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodQuadratureSetTraits.hpp
//---------------------------------------------------------------------------//
