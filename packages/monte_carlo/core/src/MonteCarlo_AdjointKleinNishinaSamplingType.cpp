//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointKleinNishinaSamplingType.hpp
//! \author Alex Robinson
//! \brief  Adjoint Klein-Nishina sampling helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointKleinNishinaSamplingType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Convert a MonteCarlo:: to a string
std::string ToStringTraits<MonteCarlo::AdjointKleinNishinaSamplingType>::toString( const MonteCarlo::AdjointKleinNishinaSamplingType type )
{
  switch( type )
  {
    case MonteCarlo::TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING:
      return "Two Branch Rejection Adjoint Klein-Nishina Sampling";
    case MonteCarlo::THREE_BRANCH_LIN_MIXED_ADJOINT_KN_SAMPLING:
      return "Three Branch Lin Mixed Adjoint Klein-Nishina Sampling";
    case MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING:
      return "Three Branch Log Mixed Adjoint Klein-Nishina Sampling";
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "Unknown adjoint Klein-Nishina sampling type "
                       "encountered!" );
    }
  }
}

// Place the MonteCarlo:: in a stream
void ToStringTraits<MonteCarlo::AdjointKleinNishinaSamplingType>::toStream( std::ostream& os, const MonteCarlo::AdjointKleinNishinaSamplingType type )
{
os << ToStringTraits<MonteCarlo::AdjointKleinNishinaSamplingType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointKleinNishinaSamplingType.hpp
//---------------------------------------------------------------------------//
