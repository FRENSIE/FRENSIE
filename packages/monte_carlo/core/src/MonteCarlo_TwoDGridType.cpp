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

// // Convert string to TwoDGridType
// TwoDGridType
// convertStringToTwoDGridType( const std::string raw_policy )
// {
//   if( raw_policy == "Correlated" || raw_policy == "correlated" || raw_policy == "CORRELATED" )
//     return CORRELATED_GRID;
//   if( raw_policy == "Unit-base Correlated" || raw_policy == "unit-base correlated" || raw_policy == "UNIT-BASE CORRELATED" )
//     return UNIT_BASE_CORRELATED_GRID;
//   else if( raw_policy == "Direct" || raw_policy == "direct" || raw_policy == "DIRECT" )
//     return DIRECT_GRID;
//   else if( raw_policy == "Unit-base" || raw_policy == "unit-base" || raw_policy == "UNIT-BASE" )
//     return UNIT_BASE_GRID;
//   else
//   {
//     THROW_EXCEPTION( std::runtime_error,
//                      "Error: 2D grid type "
//                      << raw_policy <<
//                      " is not currently supported!" );
//   }
// }

} // end MonteCarlo namespace

namespace Utility{

// Convert a MonteCarlo::TwoDGridType to a string
std::string ToStringTraits<MonteCarlo::TwoDGridType>::toString( const MonteCarlo::TwoDGridType type )
{
  switch( type )
  {
  case MonteCarlo::CORRELATED_GRID:
    return "Correlated";
  case MonteCarlo::UNIT_BASE_CORRELATED_GRID:
    return "Unit-base Correlated";
  case MonteCarlo::DIRECT_GRID:
    return "Direct";
  case MonteCarlo::UNIT_BASE_GRID:
    return "Unit-base";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "TwoDGridType " << (unsigned)type <<
                     " cannot be converted to a string!" );
  }
}

// Place the MonteCarlo::TwoDGridType in a stream
void ToStringTraits<MonteCarlo::TwoDGridType>::toStream( std::ostream& os, const MonteCarlo::TwoDGridType type )
{
  os << ToStringTraits<MonteCarlo::TwoDGridType>::toString( type );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDGridType.cpp
//---------------------------------------------------------------------------//
