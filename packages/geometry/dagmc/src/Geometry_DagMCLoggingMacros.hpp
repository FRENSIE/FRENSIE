//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCLoggingMacros.hpp
//! \author Alex Robinson
//! \brief  DagMC logging macros
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_LOGGING_MACROS_HPP
#define GEOMETRY_DAGMC_LOGGING_MACROS_HPP

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"

/*! Log a DagMC error
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_DAGMC_ERROR( msg )           \
  FRENSIE_LOG_TAGGED_ERROR( "DagMC", msg )

/*! Log a DagMC warning
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_DAGMC_WARNING( msg )         \
  FRENSIE_LOG_TAGGED_WARNING( "DagMC", msg )

/*! Log a DagMC notification
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_DAGMC_NOTIFICATION( msg )    \
  FRENSIE_LOG_TAGGED_NOTIFICATION( "DagMC", msg )

/*! Log DagMC details
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_DAGMC_DETAILS( msg )         \
  FRENSIE_LOG_TAGGED_DETAILS( "DagMC", msg )

/*! Log DagMC pedantic details
 * \ingroup logging_macros
 */
#define FRENSIE_LOG_DAGMC_PEDANTIC_DETAILS( msg )        \
  FRENSIE_LOG_TAGGED_PEDANTIC_DETAILS( "DagMC", msg )

#endif // end GEOMETRY_DAGMC_LOGGING_MACROS_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCLoggingMacros.hpp
//---------------------------------------------------------------------------//
