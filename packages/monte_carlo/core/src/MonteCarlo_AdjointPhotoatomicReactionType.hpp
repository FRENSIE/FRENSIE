//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomicReactionType.hpp
//! \author Alex Robinson
//! \brief  Adjoint photoatomic reaction type enumeration and helper function
//!         declarations.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTOATOMIC_REACTION_TYPE_HPP
#define MONTE_CARLO_ADJOINT_PHOTOATOMIC_REACTION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_SubshellType.hpp"
#include "Utility_ToStringTraits.hpp"

namespace MonteCarlo{

/*! The adjoint photoatomic reaction type enum
 *
 * When adding a new type the ToStringTraits methods and the serialization
 * method must be updated.
 */
enum AdjointPhotoatomicReactionType{
  TOTAL_ADJOINT_PHOTOATOMIC_REACTION = 1,
  TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 2,
  K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 4,
  L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 5,
  L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 6,
  L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 7,
  M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 8,
  M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 9,
  M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 10,
  M4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 11,
  M5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 12,
  N1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 13,
  N2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 14,
  N3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 15,
  N4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 16,
  N5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 17,
  N6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 18,
  N7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 19,
  O1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 20,
  O2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 21,
  O3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 22,
  O4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 23,
  O5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 24,
  O6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 25,
  O7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 26,
  O8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 27,
  O9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 28,
  P1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 29,
  P2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 30,
  P3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 31,
  P4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 32,
  P5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 33,
  P6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 34,
  P7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 35,
  P8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 36,
  P9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 37,
  P10_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 38,
  P11_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 39,
  Q1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 40,
  Q2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 41,
  Q3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION = 42,
  COHERENT_ADJOINT_PHOTOATOMIC_REACTION = 43,
  PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION = 44,
  TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION = 45
};

//! Convert a Data::SubshellType enum to a Incoherent AdjointPhotoatomicReactionType enum
AdjointPhotoatomicReactionType
convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum(
					   const Data::SubshellType subshell );

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for 
 * MonteCarlo::AdjointPhotoatomicReactionType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::AdjointPhotoatomicReactionType>
{
  //! Convert a MonteCarlo::AdjointElectroatomicReactionType to a string
  static std::string toString( const MonteCarlo::AdjointPhotoatomicReactionType type );

  //! Place the MonteCarlo::AdjointElectroatomicReactionType in a stream
  static void toStream( std::ostream& os, const MonteCarlo::AdjointPhotoatomicReactionType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing AdjointPhotoatomicReactionType enums
inline std::ostream& operator<<( std::ostream& os,
				 const AdjointPhotoatomicReactionType reaction )
{
  os << Utility::toString( reaction );
  return os;
}

} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::AdjointElectroatomicReactionType enum
template<typanem Archive>
void serialize( Archive& archive,
                MonteCarlo::AdjointElectroatomicReactionType type )
{
  if( Archive::is_saving::value )
    archive & (int)type;
  else
  {
    int raw_type;

    archive & raw_type;

    switch( raw_type )
    {
      case (int)MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::M4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::M4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
        break;
      }
      case (int)MonteCarlo::M5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::M5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::N1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::N1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::N2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::N2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::N3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::N3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::N4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::N4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::N5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::N5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::N6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::N6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::N7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::N7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::O1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::O1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::O2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::O2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::O3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::O3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::O4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::O4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::O5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::O5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::O6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::O6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::O7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::O7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::O8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::O8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::O9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::O9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::P1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::P1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::P2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::P2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::P3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::P3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::P4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::P4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::P5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::P5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::P6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::P6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::P7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::P7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::P8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::P8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::P9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::P9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::P10_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::P10_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::P11_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::P11_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::Q1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::Q1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
        break;
      }
      case (int)MonteCarlo::Q2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::Q2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::Q3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::Q3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
      case (int)MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION:
      {
        return MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION;
        break;
      }
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "Cannot convert the deserialized raw adjoint "
                       "photoatomic reaction type to the "
                       "corresponding photoatomic reaction type" );
    }
  }
}

} // end serialization namespace

} // end boost namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTOATOMIC_REACTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomicReactionType.hpp
//---------------------------------------------------------------------------//
