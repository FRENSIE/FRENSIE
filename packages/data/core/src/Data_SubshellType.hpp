//---------------------------------------------------------------------------//
//!
//! \file   Data_SubshellType.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Electron subshell enumeration and helper function decls.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SUBSHELL_TYPE_HPP
#define DATA_SUBSHELL_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

namespace Data{

/*! Subshell identifiers
 * \details The mapped integer corresponds to the ENDF subshell designator
 * and not the EADL subshell designator.
 */
enum SubshellType{
  INVALID_SUBSHELL = -1,
  UNKNOWN_SUBSHELL = 0,
  K_SUBSHELL = 1,
  L1_SUBSHELL = 2,
  L2_SUBSHELL = 3,
  L3_SUBSHELL = 4,
  M1_SUBSHELL = 5,
  M2_SUBSHELL = 6,
  M3_SUBSHELL = 7,
  M4_SUBSHELL = 8,
  M5_SUBSHELL = 9,
  N1_SUBSHELL = 10,
  N2_SUBSHELL = 11,
  N3_SUBSHELL = 12,
  N4_SUBSHELL = 13,
  N5_SUBSHELL = 14,
  N6_SUBSHELL = 15,
  N7_SUBSHELL = 16,
  O1_SUBSHELL = 17,
  O2_SUBSHELL = 18,
  O3_SUBSHELL = 19,
  O4_SUBSHELL = 20,
  O5_SUBSHELL = 21,
  O6_SUBSHELL = 22,
  O7_SUBSHELL = 23,
  O8_SUBSHELL = 24,
  O9_SUBSHELL = 25,
  P1_SUBSHELL = 26,
  P2_SUBSHELL = 27,
  P3_SUBSHELL = 28,
  P4_SUBSHELL = 29,
  P5_SUBSHELL = 30,
  P6_SUBSHELL = 31,
  P7_SUBSHELL = 32,
  P8_SUBSHELL = 33,
  P9_SUBSHELL = 34,
  P10_SUBSHELL = 35,
  P11_SUBSHELL = 36,
  Q1_SUBSHELL = 37,
  Q2_SUBSHELL = 38,
  Q3_SUBSHELL = 39
};

//! Convert an ENDF designator to a Subshell enumeration
SubshellType convertENDFDesignatorToSubshellEnum(
					      const unsigned endf_designator );

//! Convert an EADL designator to a Subshell enumeration
SubshellType convertEADLDesignatorToSubshellEnum(
					      const unsigned eadl_designator );

//! Convert an EADL designator to an ENDF designator
unsigned convertEADLDesignatorToENDFDesignator(
					      const unsigned eadl_designator );

} // end Data namespace
  
namespace Utility{

/*! Specialization of Utility::ToStringTraits for Data::SubshellType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Data::SubshellType>
{
  //! Convert a Data::SubshellType to a string
  static std::string toString( const Data::SubshellType obj );

  //! Place the Data::SubshellType in a stream
  static void toStream( std::ostream& os, const Data::SubshellType obj );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing Subshell enums
inline std::ostream& operator<<( std::ostream& os,
				 const Data::SubshellType subshell )
{
  Utility::ToStringTraits<Data::SubshellType>::toStream( os, subshell );
  
  return os;
}

} // end std namespace

#endif // end DATA_SUBSHELL_TYPE_HPP

//---------------------------------------------------------------------------//
// end Data_SubshellType.hpp
//---------------------------------------------------------------------------//
