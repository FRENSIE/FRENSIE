//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootLoggingMacros.hpp
//! \author Alex Robinson
//! \brief  Root logging macros
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ROOT_LOGGING_MACROS_HPP
#define GEOMETRY_ROOT_LOGGING_MACROS_HPP

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"

/*! Log a Root error
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_ROOT_ERROR( msg )           \
  FRENSIE_LOG_TAGGED_ERROR( "Root", msg )

/*! Log a Root warning
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_ROOT_WARNING( msg )         \
  FRENSIE_LOG_TAGGED_WARNING( "Root", msg )

/*! Log a Root notification
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_ROOT_NOTIFICATION( msg )    \
  FRENSIE_LOG_TAGGED_NOTIFICATION( "Root", msg )

/*! Log Root details
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_ROOT_DETAILS( msg )         \
  FRENSIE_LOG_TAGGED_DETAILS( "Root", msg )

/*! Log Root pedantic details
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_ROOT_PEDANTIC_DETAILS( msg )        \
  FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( "Root", msg )

#endif // end GEOMETRY_ROOT_LOGGING_MACROS_HPP

//---------------------------------------------------------------------------//
// end Geometry_RootLoggingMacros.hpp
//---------------------------------------------------------------------------//
