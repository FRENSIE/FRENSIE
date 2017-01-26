//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimension.hpp
//! \author Alex Robinson
//! \brief  Phase space dimension enum and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP
#define MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Utility_SpatialDimensionType.hpp"
#include "Utility_DirectionalDimensionType.hpp"
#include "Utility_HDF5TypeTraits.hpp"

namespace MonteCarlo{

//! The phase space dimension type enumeration
enum PhaseSpaceDimension
{
  PHASE_SPACE_DIMENSION_start = 0,
  PRIMARY_SPATIAL_DIMENSION = DIMENSION_start,
  SECONDARY_SPATIAL_DIMENSION,
  TERTIARY_SPATIAL_DIMENSION,
  PRIMARY_DIRECTIONAL_DIMENSION,
  SECONDARY_DIRECTIONAL_DIMENSION,
  TERTIARY_DIRECTIONAL_DIMENSION,
  ENERGY_DIMENSION,
  TIME_DIMENSION,
  WEIGHT_DIMENSION,
  PHASE_SPACE_DIMENSION_end
};

//! Test if the dimension name is valid
bool isValidPhaseSpaceDimensionName( const std::string& dimension_name );

//! Convert the dimension name to a dimension type enum
PhaseSpaceDimension convertPhaseSpaceDimensionNameToEnum(
                                           const std::string& dimension_name );

//! Convert an unsigned to a PhaseSpaceDimension enum
PhaseSpaceDimension convertUnsignedToPhaseSpaceDimensionEnum(
                                                    const unsigned dimension );

//! Convert the dimension type enum to a string
std::string convertPhaseSpaceDimensionEnumToString(
                                 const PhaseSpaceDimension dimension );

//! Convert the dimension type enum to a basic string
std::string convertPhaseSpaceDimensionEnumToBasicString(
                                         const PhaseSpaceDimension dimension );

//! Convert the spatial dimension to the equivalent phase space dimension
PhaseSpaceDimension convertSpatialDimensionToPhaseSpaceDimension(
                       const Utility::SpatialDimensionType spatial_dimension );

//! Convert the directional dimension to the equivalent phase space dimension
PhaseSpaceDimension convertDirectionalDimensionToPhaseSpaceDimension(
               const Utility::DirectionalDimensionType directional_dimension );

//! Stream operator for printing dimension type enums
inline std::ostream& operator<<( std::ostream& os,
                                 const PhaseSpaceDimension dimension )
{
  os << convertPhaseSpaceDimensionEnumToString( dimension );
  return os;
}
  
} // end MonteCarlo namespace

namespace Utility{

/*! Specialization of the Utility::HDF5TypeTraits for MonteCarlo::PhaseSpaceDimension
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

    MonteCarlo::PhaseSpaceDimension dimension;
    std::string dimension_name;

    for( unsigned i = MonteCarlo::PHASE_SPACE_DIMENSION_start;
         i < MonteCarlo::PHASE_SPACE_DIMENSION_end;
         ++i )
    {
      dimension = MonteCarlo::convertUnsignedToPhaseSpaceDimensionEnum( i );

      dimension_name =
        MonteCarlo::convertPhaseSpaceDimensionToBasicString( dimension );

      hdf5_phase_space_dimension_type.insert( dimension_name.c_str(),
                                              &dimension );
    }

    return hdf5_phase_space_dimension_type;
  }

  //! Return the name of the type
  static inline std::string name()
  {
    return "PhaseSpaceDimension";
  }

  //! return the zero value for this type
  static inline MonteCarlo::PhaseSpaceDimension zero()
  {
    return MonteCarlo::PHASE_SPACE_DIMENSION_start;
  }

  //! Return the unit value for this type
  static inline MonteCarlo::PhaseSpaceDimension one()
  {
    return MonteCarlo::PHASE_SPACE_DIMENSION_start;
  }
}
  
} // end Utility namespace

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimension.hpp
//---------------------------------------------------------------------------//
