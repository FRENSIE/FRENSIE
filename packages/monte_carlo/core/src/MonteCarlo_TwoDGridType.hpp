//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDGridType.hpp
//! \author Luke Kersting
//! \brief  TwoDGrid type enumeration and helper declarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTECARLO_TWO_D_GRID_TYPE_HPP
#define MONTECARLO_TWO_D_GRID_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

namespace MonteCarlo{

//! The two d grid types
enum TwoDGridType{
  CORRELATED_GRID = 1,
  UNIT_BASE_CORRELATED_GRID = 2,
  DIRECT_GRID = 3,
  UNIT_BASE_GRID = 4,
  CUMULATIVE_POINTS_GRID = 5
};

//! Convert the TwoDGridType to a string
std::string convertTwoDGridTypeToString( const TwoDGridType type );

//! Convert string to TwoDGridType
TwoDGridType convertStringToTwoDGridType( const std::string raw_policy );

//! Stream operator for printing TwoDGridType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const TwoDGridType type )
{
  os << convertTwoDGridTypeToString( type );

  return os;
}
} // end MonteCarlo namespace

#endif // end MONTECARLO_TWO_D_GRID_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDGridType.hpp
//---------------------------------------------------------------------------//
