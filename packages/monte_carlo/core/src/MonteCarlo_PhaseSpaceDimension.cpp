//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimension.cpp
//! \author Alex Robinson
//! \brief  Phase space dimension helper functiond definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Convert the PhaseSpaceDimension to a string
std::string convertPhaseSpaceDimensionToString(
					  const PhaseSpaceDimension dimension )
{
  switch( dimension )
  {
  case COSINE_DIMENSION:
    return PhaseSpaceDimensionTraits<COSINE_DIMENSION>::name();
  case ENERGY_DIMENSION:
    return PhaseSpaceDimensionTraits<ENERGY_DIMENSION>::name();
  case TIME_DIMENSION:
    return PhaseSpaceDimensionTraits<TIME_DIMENSION>::name();
  case COLLISION_NUMBER_DIMENSION:
    return PhaseSpaceDimensionTraits<COLLISION_NUMBER_DIMENSION>::name();
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: PhaseSpaceDimension " << dimension <<
		     " cannot be converted to a string!" );
  }
}

} // end MonteCarlo namespace

namespace Utility{

// Template specialization for Utility::HDF5TypeTraits
H5::EnumType HDF5TypeTraits<MonteCarlo::PhaseSpaceDimension>::dataType()
{
  H5::EnumType hdf5_phase_space_dimension_type( sizeof( short ) );
  for( short d = MonteCarlo::DIMENSION_start; 
       d < MonteCarlo::DIMENSION_end; 
       ++d )
  {
    // This is dangerous generally but the enum has been set up to support it
    MonteCarlo::PhaseSpaceDimension dimension = 
      static_cast<MonteCarlo::PhaseSpaceDimension>( d );

    std::string dimension_name = 
      MonteCarlo::convertPhaseSpaceDimensionToString( dimension );

    hdf5_phase_space_dimension_type.insert( dimension_name.c_str(), &d );
  }
  
  return hdf5_phase_space_dimension_type;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimension.cpp
//---------------------------------------------------------------------------//
