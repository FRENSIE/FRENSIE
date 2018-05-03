//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionType.hpp
//! \author Luke Kersting
//! \brief  Electroatomic reaction type enumeration and helper function decls.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOMIC_REACTION_TYPE_HPP
#define MONTE_CARLO_ELECTROATOMIC_REACTION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_SubshellType.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_TypeTraits.hpp"

namespace MonteCarlo{

/*! The electroatomic reaction type enum.
 *
 * When adding a new type the ToStringTraits methods and the serialization
 * method must be updated.
 */
enum ElectroatomicReactionType{
  TOTAL_ELECTROATOMIC_REACTION = 1,
  TOTAL_ABSORPTION_ELECTROATOMIC_REACTION = 2,
  BREMSSTRAHLUNG_ELECTROATOMIC_REACTION = 3,
  POSITRON_ANNIHILATION_ELECTROATOMIC_REACTION = 4,
  COUPLED_ELASTIC_ELECTROATOMIC_REACTION = 5,
  HYBRID_ELASTIC_ELECTROATOMIC_REACTION = 6,
  DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION = 7,
  CUTOFF_ELASTIC_ELECTROATOMIC_REACTION = 8,
  SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION = 9,
  MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION = 10,
  ATOMIC_EXCITATION_ELECTROATOMIC_REACTION = 11,
  TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 12,
  K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 13,
  L1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 14,
  L2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 15,
  L3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 16,
  M1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 17,
  M2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 18,
  M3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 19,
  M4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 20,
  M5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 21,
  N1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 22,
  N2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 23,
  N3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 24,
  N4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 25,
  N5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 26,
  N6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 27,
  N7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 28,
  O1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 29,
  O2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 30,
  O3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 31,
  O4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 32,
  O5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 33,
  O6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 34,
  O7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 35,
  O8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 36,
  O9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 37,
  P1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 38,
  P2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 39,
  P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 40,
  P4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 41,
  P5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 42,
  P6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 43,
  P7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 44,
  P8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 45,
  P9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 46,
  P10_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 47,
  P11_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 48,
  Q1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 49,
  Q2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 50,
  Q3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION = 51
};

//! Convert a Data::SubshellType enum to a ElectroatomicReactionType enum
ElectroatomicReactionType convertSubshellEnumToElectroionizationElectroatomicReactionEnum(
                                    const Data::SubshellType subshell );

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for
 * MonteCarlo::ElectroatomicReactionType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::ElectroatomicReactionType>
{
  //! Convert a MonteCarlo::ElectroatomicReactionType to a string
  static std::string toString( const MonteCarlo::ElectroatomicReactionType type );

  //! Place the MonteCarlo::ElectroatomicReactionType in a stream
  static void toStream( std::ostream& os, const MonteCarlo::ElectroatomicReactionType type );
};

/*! Specialization of Utility::IsHashable for MonteCarlo::ElectroatomicReactionType
 * \ingroup type_traits
 */
template<>
struct IsHashable<MonteCarlo::ElectroatomicReactionType> : public std::true_type
{ /* ... */ };

} // end Utility namespace

namespace std{

//! Stream operator for printing ElectroatomicReactionType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::ElectroatomicReactionType reaction )
{
  os << Utility::toString( reaction );
  return os;
}

//! Specialization of std::hash for MonteCarlo::ElectroatomicReactionType
template<>
struct hash<MonteCarlo::ElectroatomicReactionType> : public hash<unsigned>
{ /* ... */ };

} // end std namespace

#endif // end MONTE_CARLO_ELECTROATOMIC_REACTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionType.hpp
//---------------------------------------------------------------------------//


