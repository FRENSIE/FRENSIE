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
#include "Utility_TypeTraits.hpp"

namespace Data{

/*! Subshell identifiers
 * \details The mapped integer corresponds to the ENDF subshell designator
 * and not the EADL subshell designator.
 */
enum SubshellType{
  INVALID_SUBSHELL = -1,
  UNKNOWN_SUBSHELL = 0,
  K_SUBSHELL = 1,
  L1_SUBSHELL = 2,   // 3 in EADL
  L2_SUBSHELL = 3,   // 5 in EADL
  L3_SUBSHELL = 4,   // 6 in EADL
  M1_SUBSHELL = 5,   // 8 in EADL
  M2_SUBSHELL = 6,   // 10 in EADL
  M3_SUBSHELL = 7,   // 11 in EADL
  M4_SUBSHELL = 8,   // 13 in EADL
  M5_SUBSHELL = 9,   // 14 in EADL
  N1_SUBSHELL = 10,  // 16 in EADL
  N2_SUBSHELL = 11,  // 18 in EADL
  N3_SUBSHELL = 12,  // 19 in EADL
  N4_SUBSHELL = 13,  // 21 in EADL
  N5_SUBSHELL = 14,  // 22 in EADL
  N6_SUBSHELL = 15,  // 24 in EADL
  N7_SUBSHELL = 16,  // 25 in EADL
  O1_SUBSHELL = 17,  // 27 in EADL
  O2_SUBSHELL = 18,  // 29 in EADL
  O3_SUBSHELL = 19,  // 30 in EADL
  O4_SUBSHELL = 20,  // 32 in EADL
  O5_SUBSHELL = 21,  // 33 in EADL
  O6_SUBSHELL = 22,  // 35 in EADL
  O7_SUBSHELL = 23,  // 36 in EADL
  O8_SUBSHELL = 24,  // 38 in EADL
  O9_SUBSHELL = 25,  // 39 in EADL
  P1_SUBSHELL = 26,  // 41 in EADL
  P2_SUBSHELL = 27,  // 43 in EADL
  P3_SUBSHELL = 28,  // 44 in EADL
  P4_SUBSHELL = 29,  // 46 in EADL
  P5_SUBSHELL = 30,  // 47 in EADL
  P6_SUBSHELL = 31,  // 49 in EADL
  P7_SUBSHELL = 32,  // 50 in EADL
  P8_SUBSHELL = 33,  // 52 in EADL
  P9_SUBSHELL = 34,  // 53 in EADL
  P10_SUBSHELL = 35, // 55 in EADL
  P11_SUBSHELL = 36, // 56 in EADL
  Q1_SUBSHELL = 37,  // 58 in EADL
  Q2_SUBSHELL = 38,  // 60 in EADL
  Q3_SUBSHELL = 39   // 61 in EADL
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

/*! Specialization of Utility::IsHashable for Data::SubshellType
 * \ingroup type_traits
 */
template<>
struct IsHashable<Data::SubshellType> : public std::true_type
{ /* ... */ };

} // end Utility namespace

namespace std{

//! Stream operator for printing Subshell enums
inline std::ostream& operator<<( std::ostream& os,
				 const Data::SubshellType subshell )
{
  Utility::ToStringTraits<Data::SubshellType>::toStream( os, subshell );

  return os;
}

//! Specialization of std::hash for Data::SubshellType
template<>
struct hash<Data::SubshellType> : public hash<unsigned>
{ /* ... */ };

} // end std namespace

#endif // end DATA_SUBSHELL_TYPE_HPP

//---------------------------------------------------------------------------//
// end Data_SubshellType.hpp
//---------------------------------------------------------------------------//
