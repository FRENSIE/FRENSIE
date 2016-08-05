//---------------------------------------------------------------------------//
//!
//! \file   Utility_IsFloatingPoint.hpp
//! \author Alex Robinson
//! \brief  IsFloatingPoint helper class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_IS_FLOATING_POINT_HPP
#define UTILITY_IS_FLOATING_POINT_HPP

// Boost Includes
#include <boost/multiprecision/cpp_dec_float.hpp>

// FRENSIE Includes
#include "Utility_IsFloatingPointDecl.hpp"

namespace Utility{
  
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
