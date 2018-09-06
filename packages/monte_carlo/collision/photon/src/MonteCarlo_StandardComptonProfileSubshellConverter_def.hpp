//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardComptonProfileSubshellConverter_def.hpp
//! \author Alex Robinson
//! \brief  Standard Compton profile subshell-to_index converter def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_COMPTON_PROFILE_SUBSHELL_CONVERTER_DEF_HPP
#define MONTE_CARLO_STANDARD_COMPTON_PROFILE_SUBSHELL_CONVERTER_DEF_HPP

namespace MonteCarlo{

// Convert a subshell enum to an compton profile subshell index
template<unsigned Z>
unsigned StandardComptonProfileSubshellConverter<Z>::convertSubshellToIndex(
                                            const Data::SubshellType subshell ) const
{
  return ComptonProfileTraits<Z>::convertToIndex( subshell );
}

//! Compton profile traits struct for Z=1
template<>
struct ComptonProfileTraits<1u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=2
template<>
struct ComptonProfileTraits<2u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<1u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=3
template<>
struct ComptonProfileTraits<3u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=4
template<>
struct ComptonProfileTraits<4u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<3u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=5
template<>
struct ComptonProfileTraits<5u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 2u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=6
template<>
struct ComptonProfileTraits<6u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<5u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=7
template<>
struct ComptonProfileTraits<7u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<5u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=8
template<>
struct ComptonProfileTraits<8u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<5u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=9
template<>
struct ComptonProfileTraits<9u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<5u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=10
template<>
struct ComptonProfileTraits<10u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<5u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=11
template<>
struct ComptonProfileTraits<11u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 2u;
    case Data::M1_SUBSHELL: return 3u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=12
template<>
struct ComptonProfileTraits<12u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<11u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=13
template<>
struct ComptonProfileTraits<13u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 2u;
    case Data::M1_SUBSHELL: return 3u;
    case Data::M2_SUBSHELL: return 4u;
    case Data::M3_SUBSHELL: return 4u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=14
template<>
struct ComptonProfileTraits<14u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<13u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=15
template<>
struct ComptonProfileTraits<15u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<13u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=16
template<>
struct ComptonProfileTraits<16u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<13u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=17
template<>
struct ComptonProfileTraits<17u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<13u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=18
template<>
struct ComptonProfileTraits<18u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<13u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=19
template<>
struct ComptonProfileTraits<19u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 2u;
    case Data::M1_SUBSHELL: return 3u;
    case Data::M2_SUBSHELL: return 4u;
    case Data::M3_SUBSHELL: return 4u;
    case Data::N1_SUBSHELL: return 5u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=20
template<>
struct ComptonProfileTraits<20u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<19u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=21
template<>
struct ComptonProfileTraits<21u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 2u;
    case Data::M1_SUBSHELL: return 3u;
    case Data::M2_SUBSHELL: return 4u;
    case Data::M3_SUBSHELL: return 4u;
    case Data::M4_SUBSHELL: return 5u;
    case Data::M5_SUBSHELL: return 5u;
    case Data::N1_SUBSHELL: return 6u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=22
template<>
struct ComptonProfileTraits<22u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=23
template<>
struct ComptonProfileTraits<23u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=24
template<>
struct ComptonProfileTraits<24u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=25
template<>
struct ComptonProfileTraits<25u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=26
template<>
struct ComptonProfileTraits<26u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=27
template<>
struct ComptonProfileTraits<27u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=28
template<>
struct ComptonProfileTraits<28u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=29
template<>
struct ComptonProfileTraits<29u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=30
template<>
struct ComptonProfileTraits<30u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<21u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=31
template<>
struct ComptonProfileTraits<31u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 2u;
    case Data::M1_SUBSHELL: return 3u;
    case Data::M2_SUBSHELL: return 4u;
    case Data::M3_SUBSHELL: return 4u;
    case Data::M4_SUBSHELL: return 5u;
    case Data::M5_SUBSHELL: return 5u;
    case Data::N1_SUBSHELL: return 6u;
    case Data::N2_SUBSHELL: return 7u;
    case Data::N3_SUBSHELL: return 7u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=32
template<>
struct ComptonProfileTraits<32u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<31u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=33
template<>
struct ComptonProfileTraits<33u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<31u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=34
template<>
struct ComptonProfileTraits<34u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<31u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=35
template<>
struct ComptonProfileTraits<35u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<31u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=36
template<>
struct ComptonProfileTraits<36u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=37
template<>
struct ComptonProfileTraits<37u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::O1_SUBSHELL: return 12u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=38
template<>
struct ComptonProfileTraits<38u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<37u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=39
template<>
struct ComptonProfileTraits<39u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 12u;
    case Data::O1_SUBSHELL: return 13u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=40
template<>
struct ComptonProfileTraits<40u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<39u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=41
template<>
struct ComptonProfileTraits<41u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<39u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=42
template<>
struct ComptonProfileTraits<42u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::O1_SUBSHELL: return 14u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=43
template<>
struct ComptonProfileTraits<43u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<42u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=44
template<>
struct ComptonProfileTraits<44u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<42u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=45
template<>
struct ComptonProfileTraits<45u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<42u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=46
template<>
struct ComptonProfileTraits<46u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=47
template<>
struct ComptonProfileTraits<47u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<42u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=48
template<>
struct ComptonProfileTraits<48u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<42u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=49
template<>
struct ComptonProfileTraits<49u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::O1_SUBSHELL: return 14u;
    case Data::O2_SUBSHELL: return 15u;
    case Data::O3_SUBSHELL: return 15u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=50
template<>
struct ComptonProfileTraits<50u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<49u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=51
template<>
struct ComptonProfileTraits<51u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::O1_SUBSHELL: return 14u;
    case Data::O2_SUBSHELL: return 15u;
    case Data::O3_SUBSHELL: return 16u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=52
template<>
struct ComptonProfileTraits<52u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<51u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=53
template<>
struct ComptonProfileTraits<53u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<51u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=54
template<>
struct ComptonProfileTraits<54u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<51u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=55
template<>
struct ComptonProfileTraits<55u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::O1_SUBSHELL: return 14u;
    case Data::O2_SUBSHELL: return 15u;
    case Data::O3_SUBSHELL: return 16u;
    case Data::P1_SUBSHELL: return 17u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=56
template<>
struct ComptonProfileTraits<56u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<55u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=57
template<>
struct ComptonProfileTraits<57u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::O1_SUBSHELL: return 14u;
    case Data::O2_SUBSHELL: return 15u;
    case Data::O3_SUBSHELL: return 16u;
    case Data::O4_SUBSHELL: return 17u;
    case Data::O5_SUBSHELL: return 17u;
    case Data::P1_SUBSHELL: return 18u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
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
template<>
struct ComptonProfileTraits<58u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 14u;
    case Data::O1_SUBSHELL: return 15u;
    case Data::O2_SUBSHELL: return 16u;
    case Data::O3_SUBSHELL: return 17u;
    case Data::P1_SUBSHELL: return 19u; // 18 (5d-) is skipped
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=59
template<>
struct ComptonProfileTraits<59u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 14u;
    case Data::O1_SUBSHELL: return 15u;
    case Data::O2_SUBSHELL: return 16u;
    case Data::O3_SUBSHELL: return 17u;
    case Data::P1_SUBSHELL: return 18u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=60
template<>
struct ComptonProfileTraits<60u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<59u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=61
template<>
struct ComptonProfileTraits<61u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<59u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=62
template<>
struct ComptonProfileTraits<62u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<59u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=63
template<>
struct ComptonProfileTraits<63u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::P1_SUBSHELL: return 19u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=64
template<>
struct ComptonProfileTraits<64u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 19u;
    case Data::P1_SUBSHELL: return 20u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=65
template<>
struct ComptonProfileTraits<65u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<63u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=66
template<>
struct ComptonProfileTraits<66u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<63u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=67
template<>
struct ComptonProfileTraits<67u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<63u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=68
template<>
struct ComptonProfileTraits<68u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<63u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=69
template<>
struct ComptonProfileTraits<69u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<63u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=70
template<>
struct ComptonProfileTraits<70u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<63u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=71
template<>
struct ComptonProfileTraits<71u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<64u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=72
template<>
struct ComptonProfileTraits<72u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<64u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=73
template<>
struct ComptonProfileTraits<73u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<64u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=74
template<>
struct ComptonProfileTraits<74u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<64u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=75
template<>
struct ComptonProfileTraits<75u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 20u;
    case Data::P1_SUBSHELL: return 21u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=76
template<>
struct ComptonProfileTraits<76u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<75u>::convertToIndex( subshell ); }
};

/*! Compton profile traits struct for Z=77
 * \details There is a Compton profile for the P1 subshell but the
 * ENDF/EADL libraries do not have a P1 subshell. The Compton profile for
 * the P1 subshell will be ignored.
 */
template<>
struct ComptonProfileTraits<77u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 20u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=78
template<>
struct ComptonProfileTraits<78u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<75u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=79
template<>
struct ComptonProfileTraits<79u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<75u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=80
template<>
struct ComptonProfileTraits<80u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<75u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=81
template<>
struct ComptonProfileTraits<81u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 20u;
    case Data::P1_SUBSHELL: return 21u;
    case Data::P2_SUBSHELL: return 22u;
    case Data::P3_SUBSHELL: return 22u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=82
template<>
struct ComptonProfileTraits<82u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<81u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=83
template<>
struct ComptonProfileTraits<83u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 20u;
    case Data::P1_SUBSHELL: return 21u;
    case Data::P2_SUBSHELL: return 22u;
    case Data::P3_SUBSHELL: return 23u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=84
template<>
struct ComptonProfileTraits<84u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<83u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=85
template<>
struct ComptonProfileTraits<85u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<83u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=86
template<>
struct ComptonProfileTraits<86u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<83u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=87
template<>
struct ComptonProfileTraits<87u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 20u;
    case Data::P1_SUBSHELL: return 21u;
    case Data::P2_SUBSHELL: return 22u;
    case Data::P3_SUBSHELL: return 23u;
    case Data::Q1_SUBSHELL: return 24u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=88
template<>
struct ComptonProfileTraits<88u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<87u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=89
template<>
struct ComptonProfileTraits<89u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 20u;
    case Data::P1_SUBSHELL: return 21u;
    case Data::P2_SUBSHELL: return 22u;
    case Data::P3_SUBSHELL: return 23u;
    case Data::P4_SUBSHELL: return 24u;
    case Data::P5_SUBSHELL: return 24u;
    case Data::Q1_SUBSHELL: return 25u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=90
template<>
struct ComptonProfileTraits<90u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<89u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=91
template<>
struct ComptonProfileTraits<91u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 20u;
    case Data::O6_SUBSHELL: return 21u;
    case Data::O7_SUBSHELL: return 21u;
    case Data::P1_SUBSHELL: return 22u;
    case Data::P2_SUBSHELL: return 23u;
    case Data::P3_SUBSHELL: return 24u;
    case Data::P4_SUBSHELL: return 25u;
    case Data::P5_SUBSHELL: return 25u;
    case Data::Q1_SUBSHELL: return 26u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=92
template<>
struct ComptonProfileTraits<92u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<91u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=93
template<>
struct ComptonProfileTraits<93u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<91u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=94
template<>
struct ComptonProfileTraits<94u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 20u;
    case Data::O6_SUBSHELL: return 21u;
    case Data::O7_SUBSHELL: return 21u;
    case Data::P1_SUBSHELL: return 22u;
    case Data::P2_SUBSHELL: return 23u;
    case Data::P3_SUBSHELL: return 24u;
    case Data::Q1_SUBSHELL: return 25u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=95
template<>
struct ComptonProfileTraits<95u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 20u;
    case Data::O6_SUBSHELL: return 21u;
    case Data::O7_SUBSHELL: return 22u;
    case Data::P1_SUBSHELL: return 23u;
    case Data::P2_SUBSHELL: return 24u;
    case Data::P3_SUBSHELL: return 25u;
    case Data::Q1_SUBSHELL: return 26u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=96
template<>
struct ComptonProfileTraits<96u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 20u;
    case Data::O6_SUBSHELL: return 21u;
    case Data::O7_SUBSHELL: return 22u;
    case Data::P1_SUBSHELL: return 23u;
    case Data::P2_SUBSHELL: return 24u;
    case Data::P3_SUBSHELL: return 25u;
    case Data::P4_SUBSHELL: return 26u;
    case Data::P5_SUBSHELL: return 26u;
    case Data::Q1_SUBSHELL: return 27u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

/*! Compton profile traits struct for Z=97
 * \details There is not a Compton profile for the P4 or P5 subshells, which
 * contain electrons according to the ENDF/EADL libraries. The P4 subshell
 * will be assigned to the O6 subshell Compton profile and the P5 subshell
 * will be assigned to the O7 subshell Compton profile.
 */
template<>
struct ComptonProfileTraits<97u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 20u;
    case Data::O6_SUBSHELL: return 21u;
    case Data::O7_SUBSHELL: return 22u;
    case Data::P1_SUBSHELL: return 23u;
    case Data::P2_SUBSHELL: return 24u;
    case Data::P3_SUBSHELL: return 25u;
    case Data::P4_SUBSHELL: return 21u; // Assigned to O6 due to lack of Compton prof
    case Data::P5_SUBSHELL: return 22u; // Assigned to O7 due to lack of Compton prof
    case Data::Q1_SUBSHELL: return 26u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=98
template<>
struct ComptonProfileTraits<98u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  {
    switch( subshell )
    {
    case Data::K_SUBSHELL: return 0u;
    case Data::L1_SUBSHELL: return 1u;
    case Data::L2_SUBSHELL: return 2u;
    case Data::L3_SUBSHELL: return 3u;
    case Data::M1_SUBSHELL: return 4u;
    case Data::M2_SUBSHELL: return 5u;
    case Data::M3_SUBSHELL: return 6u;
    case Data::M4_SUBSHELL: return 7u;
    case Data::M5_SUBSHELL: return 8u;
    case Data::N1_SUBSHELL: return 9u;
    case Data::N2_SUBSHELL: return 10u;
    case Data::N3_SUBSHELL: return 11u;
    case Data::N4_SUBSHELL: return 12u;
    case Data::N5_SUBSHELL: return 13u;
    case Data::N6_SUBSHELL: return 14u;
    case Data::N7_SUBSHELL: return 15u;
    case Data::O1_SUBSHELL: return 16u;
    case Data::O2_SUBSHELL: return 17u;
    case Data::O3_SUBSHELL: return 18u;
    case Data::O4_SUBSHELL: return 19u;
    case Data::O5_SUBSHELL: return 20u;
    case Data::O6_SUBSHELL: return 21u;
    case Data::O7_SUBSHELL: return 22u;
    case Data::P1_SUBSHELL: return 23u;
    case Data::P2_SUBSHELL: return 24u;
    case Data::P3_SUBSHELL: return 25u;
    case Data::Q1_SUBSHELL: return 26u;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Subshell " << subshell << " is not valid!" );
    }
  }
};

//! Compton profile traits struct for Z=99
template<>
struct ComptonProfileTraits<99u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<98u>::convertToIndex( subshell ); }
};

//! Compton profile traits struct for Z=100
template<>
struct ComptonProfileTraits<100u>
{
  //! Convert a subshell enum to a compton profile index
  static inline unsigned convertToIndex( const Data::SubshellType subshell )
  { return ComptonProfileTraits<98u>::convertToIndex( subshell ); }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_COMPTON_PROFILE_SUBSHELL_CONVERTER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardComptonProfileSubshellConverter_def.hpp
//---------------------------------------------------------------------------//
