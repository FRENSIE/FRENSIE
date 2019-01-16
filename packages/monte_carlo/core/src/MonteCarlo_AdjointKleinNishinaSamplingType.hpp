//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointKleinNishinaSamplingType.hpp
//! \author Alex Robinson
//! \brief  Adjoint Klein-Nishina sampling type enum and helper function decls.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_KLEIN_NISHINA_SAMPLING_TYPE_HPP
#define MONTE_CARLO_ADJOINT_KLEIN_NISHINA_SAMPLING_TYPE_HPP

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

/*! The adjoint Klein-Nishina sampling type enum
 *
 * When adding a new type the ToStringTraits methods and the serialization
 * method must be updated
 */
enum AdjointKleinNishinaSamplingType
{
  TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING = 0,
  THREE_BRANCH_LIN_MIXED_ADJOINT_KN_SAMPLING,
  THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING
};
  
} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for
 * MonteCarlo::AdjointKleinNishinaSamplingType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::AdjointKleinNishinaSamplingType>
{
  //! Convert a MonteCarlo:: to a string
  static std::string toString( const MonteCarlo::AdjointKleinNishinaSamplingType type );

  //! Place the MonteCarlo:: in a stream
  static void toStream( std::ostream& os, const MonteCarlo::AdjointKleinNishinaSamplingType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing AdjointKleinNishinaSamplingType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::AdjointKleinNishinaSamplingType incoherent_adjoint_model )
{
  os << Utility::toString( incoherent_adjoint_model );
  return os;
}
  
} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::AdjointKleinNishinaSamplingType enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::AdjointKleinNishinaSamplingType& type,
                const unsigned version )
{
  if( Archive::is_saving::value )
    archive & (int)type;
  else
  {
    int raw_type;

    archive & raw_type;

    switch( raw_type )
    {
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::THREE_BRANCH_LIN_MIXED_ADJOINT_KN_SAMPLING, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING, int, type );
      
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw adjoint "
                         "Klein-Nishina sampling type to its corresponding "
                         "enum value!" );
      }
    }
  }
}

} // end serialization namespace

} // end boost namespace

#endif // end MONTE_CARLO_ADJOINT_KLEIN_NISHINA_SAMPLING_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointKleinNishinaSamplingType.hpp
//---------------------------------------------------------------------------//
