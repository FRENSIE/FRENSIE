//---------------------------------------------------------------------------//
//!
//! \file   Utility_WarningLevelTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Warning level traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_WARNING_LEVEL_TRAITS_DECL_HPP
#define UTILITY_WARNING_LEVEL_TRAITS_DECL_HPP

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/mpl/set_c.hpp>

// FRENSIE Includes
#include "Utility_WarningLevel.hpp"
#include "Utility_WarningType.hpp"

/*! \defgroup warning_level_traits Warning Level Traits
 * \ingroup traits
 */

namespace Utility{
  
/*! This structure defines the properties of a warning level
 * \ingroup warning_level_traits
 */
template<WarningLevel level>
struct WarningLevelTraits
{
  //! The warning types supported at this warning level
  typedef boost::mpl::set_c<WarningType> SupportedWarningTypes;
};
  
} // end Utility namespace

#endif // end UTILITY_WARNING_LEVEL_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_WarningLevelTraitsDecl.hpp
//---------------------------------------------------------------------------//
