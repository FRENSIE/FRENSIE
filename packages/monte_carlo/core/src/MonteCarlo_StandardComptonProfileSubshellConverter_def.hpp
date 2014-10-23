//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardComptonProfileSubshellConverter_def.hpp
//! \author Alex Robinson
//! \brief  Standard Compton profile subshell-to_index converter def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDERD_COMPTON_PROFILE_SUBSHELL_CONVERTER_DEF_HPP
#define MONTE_CARLO_STANDERD_COMPTON_PROFILE_SUBSHELL_CONVERTER_DEF_HPP

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Convert a subshell enum to an compton profile subshell index
template<unsigned Z>
unsigned StandardComptonProfileSubshellConverter<Z>::convertSubshellToIndex( 
                                            const SubshellType subshell ) const
{
  return ComptonProfileTraits<Z>::convertToIndex( subshell );
}

//! Compton profile traits struct for Z=1
template<>
struct ComptonProfileTraits<1u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=2
template<>
struct ComptonProfileTraits<2u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<1u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=3
struct ComptonProfileTraits<3u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
}

//! Compton profile traits struct for Z=4
template<>
struct ComptonProfileTraits<4u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<3u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=5
struct ComptonProfileTraits<5u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 2u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
}

//! Compton profile traits struct for Z=6
template<>
struct ComptonProfileTraits<6u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<5u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=7
template<>
struct ComptonProfileTraits<7u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<5u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=8
template<>
struct ComptonProfileTraits<8u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<5u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=9
template<>
struct ComptonProfileTraits<9u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<5u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=10
template<>
struct ComptonProfileTraits<10u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<5u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=11
struct ComptonProfileTraits<11u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 2u;
    case M1_SUBSHELL: return 3u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
}

//! Compton profile traits struct for Z=12
template<>
struct ComptonProfileTraits<12u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<11u>::convertToIndex( subshell ); }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDERD_COMPTON_PROFILE_SUBSHELL_CONVERTER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardComptonProfileSubshellConverter_def.hpp
//---------------------------------------------------------------------------//
