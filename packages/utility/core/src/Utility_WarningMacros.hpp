//---------------------------------------------------------------------------//
//!
//! \file   Utility_WarningMacros.hpp
//! \author Alex Robinson
//! \brief  Macros that can be used for displaying warning messages
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_WARNING_MACROS_HPP
#define UTILITY_WARNING_MACROS_HPP

// FRENSIE Includes
#include "Utility_WarningLevelTraits.hpp"

namespace Utility{

namespace Details {

/*! The warning stream helper class
 * \ingroup warning_level_traits
 */
template<typename T, WarningType warning, typename Enabled = void>
class WarningStreamHelper
{
  //! Add the message details to the stream (nothing is added to stream)
  template<typename T>
  static inline void addToStream( std::ostream&, const T& )
  { /* ... */ }
};

/*! The warning stream helper class
 * \ingroup warning_level_traits
 */
template<typename T, WarningType warning>
class WarningStreamHelper<T,warning,boost::enable_if<boost::mpl::has_key<T,boost::mpl::integral_c<WarningType,warning> >::type>
{
  //! Add the message details to the stream
  template<typename T>
  static inline void addToStream( std::ostream& os, const T& obj )
  { os << obj; }
};

//! Add an object to the warning stream
template<WarningLevel level, WarningType warning, typename T>
inline void addToWarningStream( std::ostream& os, const T& obj )
{
  Details::WarningStreamHelper<typename WarningLevelTraits<level>::SupportedWarningTypes,warning>::addToStream( os, obj );
}
  
} // end Details namespace
  
} // end Utility namespace

#define SET_WARNING_LEVEL( level ) \
global_warning_level = level

#define REPORT( warning_type, msg )

#endif // end UTILITY_WARNING_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_WarningMacros.hpp
//---------------------------------------------------------------------------//
