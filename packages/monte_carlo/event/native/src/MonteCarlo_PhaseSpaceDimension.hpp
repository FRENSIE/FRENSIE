//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimension.hpp
//! \author Alex Robinson
//! \brief  Phase space dimension enumeration and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP
#define MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP

// Std Lib Includes
#include <iostream>
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// HDF5 Includes
#include <H5Cpp.h>

// FRENSIE Includes
#include "Utility_HDF5TypeTraits.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

/*! The phase space dimension enumeration
 *
 * Make sure that the DIMENSION_end value equals the last dimension name if
 * more dimension names are added. The start and end enum names are used for
 * iterating through the list of dimensions.
 */
enum PhaseSpaceDimension{
  DIMENSION_start = 0,
  COSINE_DIMENSION = DIMENSION_start,
  ENERGY_DIMENSION,
  TIME_DIMENSION,
  COLLISION_NUMBER_DIMENSION,
  DIMENSION_end
};

//! Convert the PhaseSpaceDimension to a string
std::string convertPhaseSpaceDimensionToString( 
				         const PhaseSpaceDimension dimension );

//! Convert the PhaseSpaceDimension to a string (basic)
std::string convertPhaseSpaceDimensionToStringBasic(
                                         const PhaseSpaceDimension dimension );

//! Convert an unsigned to a PhaseSpaceDimension
PhaseSpaceDimension convertUnsignedToPhaseSpaceDimensionEnum(
                                                    const unsigned dimension );

//! Stream operator for printing PhaseSpaceDimension enums
inline std::ostream& operator<<( std::ostream& os,
				 const PhaseSpaceDimension dimension )
{
  os << convertPhaseSpaceDimensionToString( dimension );

  return os;
}

} // end MonteCarlo namespace

namespace Utility{

/*! The specialization of the Utility::HDF5TypeTraits for the
 * MonteCarlo::PhaseSpaceDimension enum
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<MonteCarlo::PhaseSpaceDimension>
{
  //! Return the HDF5 data type
  static inline H5::EnumType dataType()
  {
    H5::EnumType hdf5_phase_space_dimension_type( 
				   sizeof( MonteCarlo::PhaseSpaceDimension ) );

    MonteCarlo::PhaseSpaceDimension value;
    std::string value_name;
    
    for( unsigned i = MonteCarlo::DIMENSION_start; 
         i < MonteCarlo::DIMENSION_end; 
         ++i )
    {
      value = MonteCarlo::convertUnsignedToPhaseSpaceDimensionEnum( i );

      value_name = 
        MonteCarlo::convertPhaseSpaceDimensionToStringBasic( value );

      hdf5_phase_space_dimension_type.insert( value_name.c_str(), &value );
    }
    
    return hdf5_phase_space_dimension_type;
  }

  //! Return the name of the type
  static inline std::string name()
  {
    return "PhaseSpaceDimension";
  }
  
  //! Returns the zero value for this type
  static inline MonteCarlo::PhaseSpaceDimension zero()
  {
    return MonteCarlo::COSINE_DIMENSION;
  }

  //! Returns the unity value for this type
  static inline MonteCarlo::PhaseSpaceDimension one()
  {
    return MonteCarlo::ENERGY_DIMENSION;
  }
};

} // end Utility namespace

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimension.hpp
//---------------------------------------------------------------------------//
