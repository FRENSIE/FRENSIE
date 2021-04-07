//---------------------------------------------------------------------------//
//!
//! \file   Utility_IsFloatingPointDecl.hpp
//! \author Alex Robinson
//! \brief  IsFloatingPoint helper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_IS_FLOATING_POINT_DECL_HPP
#define UTILITY_IS_FLOATING_POINT_DECL_HPP

// Boost Includes
#include <boost/type_traits/is_floating_point.hpp>

namespace Utility{

/*! The IsFloatingPoint class
 * \details This class will mimic and extend the boost::is_floating_point
 * class. Specializations can be made for special (e.g. extended precision)
 * floating point types.
 */
template<typename T, typename Enabled = void>
struct IsFloatingPoint : public boost::is_floating_point<T> {};

} // end Utility namespace

#endif // end UTILITY_IS_FLOATING_POINT_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_IsFloatingPointDecl.hpp
//---------------------------------------------------------------------------//
