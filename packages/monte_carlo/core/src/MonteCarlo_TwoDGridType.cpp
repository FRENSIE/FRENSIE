//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDGridType.cpp
//! \author Luke Kersting
//! \brief  TwoDGrid type helper definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"
#include "MonteCarlo_TwoDGridType.hpp"

namespace MonteCarlo{

// Convert the TwoDGridType to a string
std::string convertTwoDGridTypeToString( const TwoDGridType type )
{
  switch( type )
  {
  case CORRELATED_GRID:
    return "Correlated";
  case UNIT_BASE_CORRELATED_GRID:
    return "Unit-base Correlated";
  case DIRECT_GRID:
    return "Direct";
  case UNIT_BASE_GRID:
    return "Unit-base";
  case CUMULATIVE_POINTS_GRID:
    return "Cumulative Points";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: TwoDGridType " << (unsigned)type <<
                     " cannot be converted to a string!" );
  }
}

// Convert string to TwoDGridType
TwoDGridType
convertStringToTwoDGridType( const std::string raw_policy )
{
  if( raw_policy == "Correlated" || raw_policy == "correlated" || raw_policy == "CORRELATED" )
    return CORRELATED_GRID;
  if( raw_policy == "Unit-base Correlated" || raw_policy == "unit-base correlated" || raw_policy == "UNIT-BASE CORRELATED" )
    return UNIT_BASE_CORRELATED_GRID;
  else if( raw_policy == "Direct" || raw_policy == "direct" || raw_policy == "DIRECT" )
    return DIRECT_GRID;
  else if( raw_policy == "Unit-base" || raw_policy == "unit-base" || raw_policy == "UNIT-BASE" )
    return UNIT_BASE_GRID;
  else if( raw_policy == "Cumulative Points" || raw_policy == "cumulative points" || raw_policy == "CUMULATIVE POINTS" )
    return CUMULATIVE_POINTS_GRID;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: 2D grid type "
                     << raw_policy <<
                     " is not currently supported!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDGridType.cpp
//---------------------------------------------------------------------------//
