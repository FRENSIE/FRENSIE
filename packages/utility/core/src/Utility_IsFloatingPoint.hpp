//---------------------------------------------------------------------------//
//!
//! \file   Utility_IsFloatingPoint.hpp
//! \author Alex Robinson
//! \brief  IsFloatingPoint helper class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_IS_FLOATING_POINT_HPP
#define UTILITY_IS_FLOATING_POINT_HPP

// Std Lib Includes
#include <type_traits>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/cmath.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

// FRENSIE Includes
#include "Utility_IsFloatingPointDecl.hpp"

namespace Utility{

/*! \brief Partial specialization of IsFloatingPoint for 
 * boost::units::quantity types.
 */
template<typename Unit, typename T>
struct IsFloatingPoint<boost::units::quantity<Unit,T>, typename std::enable_if<std::is_floating_point<T>::value>::type> : public boost::true_type {};
  
/*! \brief Partial specialization of IsFloatingPoint for 
 * boost::multiprecision::number<boost::multiprecision::cpp_dec_float<int> >
 */
template<unsigned N>
struct IsFloatingPoint<boost::multiprecision::number<boost::multiprecision::backends::cpp_dec_float<N> > > : public boost::true_type {};

} // end Utility namespace

#endif // end UTILITY_IS_FLOATING_POINT_HPP

//---------------------------------------------------------------------------//
// end Utility_IsFloatingPoint.hpp
//---------------------------------------------------------------------------//
