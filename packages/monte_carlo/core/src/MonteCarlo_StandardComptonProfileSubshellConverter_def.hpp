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
template<>
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
};

//! Compton profile traits struct for Z=4
template<>
struct ComptonProfileTraits<4u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<3u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=5
template<>
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
};

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
template<>
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
};

//! Compton profile traits struct for Z=12
template<>
struct ComptonProfileTraits<12u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<11u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=13
template<>
struct ComptonProfileTraits<13u>
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
    case M2_SUBSHELL: return 4u;
    case M3_SUBSHELL: return 4u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=14
template<>
struct ComptonProfileTraits<14u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<13u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=15
template<>
struct ComptonProfileTraits<15u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<13u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=16
template<>
struct ComptonProfileTraits<16u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<13u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=17
template<>
struct ComptonProfileTraits<17u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<13u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=18
template<>
struct ComptonProfileTraits<18u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<13u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=19
template<>
struct ComptonProfileTraits<19u>
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
    case M2_SUBSHELL: return 4u;
    case M3_SUBSHELL: return 4u;
    case N1_SUBSHELL: return 5u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=20
template<>
struct ComptonProfileTraits<20u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<19u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=21
struct ComptonProfileTraits<21u>
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
    case M2_SUBSHELL: return 4u;
    case M3_SUBSHELL: return 4u;
    case M4_SUBSHELL: return 5u;
    case M5_SUBSHELL: return 5u;
    case N1_SUBSHELL: return 6u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=22
template<>
struct ComptonProfileTraits<22u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=23
template<>
struct ComptonProfileTraits<23u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=24
template<>
struct ComptonProfileTraits<24u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=25
template<>
struct ComptonProfileTraits<25u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=26
template<>
struct ComptonProfileTraits<26u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=27
template<>
struct ComptonProfileTraits<27u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=28
template<>
struct ComptonProfileTraits<28u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=29
template<>
struct ComptonProfileTraits<29u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=30
template<>
struct ComptonProfileTraits<30u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=31
struct ComptonProfileTraits<31u>
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
    case M2_SUBSHELL: return 4u;
    case M3_SUBSHELL: return 4u;
    case M4_SUBSHELL: return 5u;
    case M5_SUBSHELL: return 5u;
    case N1_SUBSHELL: return 6u;
    case N2_SUBSHELL: return 7u;
    case N3_SUBSHELL: return 7u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=32
template<>
struct ComptonProfileTraits<32u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<31u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=33
template<>
struct ComptonProfileTraits<33u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<31u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=34
template<>
struct ComptonProfileTraits<34u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<31u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=35
template<>
struct ComptonProfileTraits<35u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<31u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=36
struct ComptonProfileTraits<36u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 3u;
    case M1_SUBSHELL: return 4u;
    case M2_SUBSHELL: return 5u;
    case M3_SUBSHELL: return 6u;
    case M4_SUBSHELL: return 7u;
    case M5_SUBSHELL: return 8u;
    case N1_SUBSHELL: return 9u;
    case N2_SUBSHELL: return 10u;
    case N3_SUBSHELL: return 11u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=37
struct ComptonProfileTraits<37u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 3u;
    case M1_SUBSHELL: return 4u;
    case M2_SUBSHELL: return 5u;
    case M3_SUBSHELL: return 6u;
    case M4_SUBSHELL: return 7u;
    case M5_SUBSHELL: return 8u;
    case N1_SUBSHELL: return 9u;
    case N2_SUBSHELL: return 10u;
    case N3_SUBSHELL: return 11u;
    case O1_SUBSHELL: return 12u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=38
template<>
struct ComptonProfileTraits<38u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<37u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=39
struct ComptonProfileTraits<39u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 3u;
    case M1_SUBSHELL: return 4u;
    case M2_SUBSHELL: return 5u;
    case M3_SUBSHELL: return 6u;
    case M4_SUBSHELL: return 7u;
    case M5_SUBSHELL: return 8u;
    case N1_SUBSHELL: return 9u;
    case N2_SUBSHELL: return 10u;
    case N3_SUBSHELL: return 11u;
    case N4_SUBSHELL: return 12u;
    case N5_SUBSHELL: return 12u;
    case O1_SUBSHELL: return 13u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=40
template<>
struct ComptonProfileTraits<40u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<39u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=41
template<>
struct ComptonProfileTraits<41u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<39u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=42
struct ComptonProfileTraits<42u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 3u;
    case M1_SUBSHELL: return 4u;
    case M2_SUBSHELL: return 5u;
    case M3_SUBSHELL: return 6u;
    case M4_SUBSHELL: return 7u;
    case M5_SUBSHELL: return 8u;
    case N1_SUBSHELL: return 9u;
    case N2_SUBSHELL: return 10u;
    case N3_SUBSHELL: return 11u;
    case N4_SUBSHELL: return 12u;
    case N5_SUBSHELL: return 13u;
    case O1_SUBSHELL: return 14u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=43
template<>
struct ComptonProfileTraits<43u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<42u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=44
template<>
struct ComptonProfileTraits<44u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<42u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=45
template<>
struct ComptonProfileTraits<45u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<42u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=46
struct ComptonProfileTraits<46u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 3u;
    case M1_SUBSHELL: return 4u;
    case M2_SUBSHELL: return 5u;
    case M3_SUBSHELL: return 6u;
    case M4_SUBSHELL: return 7u;
    case M5_SUBSHELL: return 8u;
    case N1_SUBSHELL: return 9u;
    case N2_SUBSHELL: return 10u;
    case N3_SUBSHELL: return 11u;
    case N4_SUBSHELL: return 12u;
    case N5_SUBSHELL: return 13u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=47
template<>
struct ComptonProfileTraits<47u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<42u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=48
template<>
struct ComptonProfileTraits<48u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<42u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=49
struct ComptonProfileTraits<49u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 3u;
    case M1_SUBSHELL: return 4u;
    case M2_SUBSHELL: return 5u;
    case M3_SUBSHELL: return 6u;
    case M4_SUBSHELL: return 7u;
    case M5_SUBSHELL: return 8u;
    case N1_SUBSHELL: return 9u;
    case N2_SUBSHELL: return 10u;
    case N3_SUBSHELL: return 11u;
    case N4_SUBSHELL: return 12u;
    case N5_SUBSHELL: return 13u;
    case O1_SUBSHELL: return 14u;
    case O2_SUBSHELL: return 15u;
    case O3_SUBSHELL: return 15u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=50
template<>
struct ComptonProfileTraits<50u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<49u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=51
struct ComptonProfileTraits<51u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 3u;
    case M1_SUBSHELL: return 4u;
    case M2_SUBSHELL: return 5u;
    case M3_SUBSHELL: return 6u;
    case M4_SUBSHELL: return 7u;
    case M5_SUBSHELL: return 8u;
    case N1_SUBSHELL: return 9u;
    case N2_SUBSHELL: return 10u;
    case N3_SUBSHELL: return 11u;
    case N4_SUBSHELL: return 12u;
    case N5_SUBSHELL: return 13u;
    case O1_SUBSHELL: return 14u;
    case O2_SUBSHELL: return 15u;
    case O3_SUBSHELL: return 16u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=52
template<>
struct ComptonProfileTraits<52u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<51u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=53
template<>
struct ComptonProfileTraits<53u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<51u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=54
template<>
struct ComptonProfileTraits<54u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<51u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=55
struct ComptonProfileTraits<55u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 3u;
    case M1_SUBSHELL: return 4u;
    case M2_SUBSHELL: return 5u;
    case M3_SUBSHELL: return 6u;
    case M4_SUBSHELL: return 7u;
    case M5_SUBSHELL: return 8u;
    case N1_SUBSHELL: return 9u;
    case N2_SUBSHELL: return 10u;
    case N3_SUBSHELL: return 11u;
    case N4_SUBSHELL: return 12u;
    case N5_SUBSHELL: return 13u;
    case O1_SUBSHELL: return 14u;
    case O2_SUBSHELL: return 15u;
    case O3_SUBSHELL: return 16u;
    case P1_SUBSHELL: return 17u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=56
template<>
struct ComptonProfileTraits<56u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  { return ComptonProfileTraits<55u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=57
struct ComptonProfileTraits<57u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 3u;
    case M1_SUBSHELL: return 4u;
    case M2_SUBSHELL: return 5u;
    case M3_SUBSHELL: return 6u;
    case M4_SUBSHELL: return 7u;
    case M5_SUBSHELL: return 8u;
    case N1_SUBSHELL: return 9u;
    case N2_SUBSHELL: return 10u;
    case N3_SUBSHELL: return 11u;
    case N4_SUBSHELL: return 12u;
    case N5_SUBSHELL: return 13u;
    case O1_SUBSHELL: return 14u;
    case O2_SUBSHELL: return 15u;
    case O3_SUBSHELL: return 16u;
    case O4_SUBSHELL: return 17u;
    case O5_SUBSHELL: return 17u;
    case P1_SUBSHELL: return 18u;
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

/*! Compton profile traits struct for Z=58
 * \details There is a significant discrepancy between the compton profile
 * shell filling and the ENDF/EADL shell filling. The compton profiles
 * fill the 4f- shell and the 5d- shell while the ENDF/EADL libraries
 * fill the 4f(5/2) and the 4f(7/2) shells without filling the 5d(3/2) shells.
 * The 5d- compton profile is simply ignored.
 */
struct ComptonProfileTraits<58u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 3u;
    case M1_SUBSHELL: return 4u;
    case M2_SUBSHELL: return 5u;
    case M3_SUBSHELL: return 6u;
    case M4_SUBSHELL: return 7u;
    case M5_SUBSHELL: return 8u;
    case N1_SUBSHELL: return 9u;
    case N2_SUBSHELL: return 10u;
    case N3_SUBSHELL: return 11u;
    case N4_SUBSHELL: return 12u;
    case N5_SUBSHELL: return 13u;
    case N6_SUBSHELL: return 14u;
    case N7_SUBSHELL: return 14u;
    case O1_SUBSHELL: return 15u;
    case O2_SUBSHELL: return 16u;
    case O3_SUBSHELL: return 17u;
    case P1_SUBSHELL: return 19u; // 18 (5d-) is skipped
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=59
struct ComptonProfileTraits<59u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const SubshellType subshell )
  {
    switch( subshell )
    {
    case K_SUBSHELL: return 0u;
    case L1_SUBSHELL: return 1u;
    case L2_SUBSHELL: return 2u;
    case L3_SUBSHELL: return 3u;
    case M1_SUBSHELL: return 4u;
    case M2_SUBSHELL: return 5u;
    case M3_SUBSHELL: return 6u;
    case M4_SUBSHELL: return 7u;
    case M5_SUBSHELL: return 8u;
    case N1_SUBSHELL: return 9u;
    case N2_SUBSHELL: return 10u;
    case N3_SUBSHELL: return 11u;
    case N4_SUBSHELL: return 12u;
    case N5_SUBSHELL: return 13u;
    case N6_SUBSHELL: return 14u;
    case N7_SUBSHELL: return 14u;
    case O1_SUBSHELL: return 15u;
    case O2_SUBSHELL: return 16u;
    case O3_SUBSHELL: return 17u;
    case P1_SUBSHELL: return 18u; 
    default:
      THROW_EXCEPTION( std::logic_error, 
		       "Error: Subshell " << subshell << " is not valid!" );
    }
  }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDERD_COMPTON_PROFILE_SUBSHELL_CONVERTER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardComptonProfileSubshellConverter_def.hpp
//---------------------------------------------------------------------------//
