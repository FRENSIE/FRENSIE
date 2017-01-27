//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDimension.hpp
//! \author Alex Robinson
//! \brief  Observer phase space dimension enum and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_HPP
#define MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_HPP

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

/*! The observer phase space dimension enumeration
 *
 * Make sure that the OBSERVER_PHASE_SPACE_DIMENSION_end value is always the
 * last value if more dimension names are added. The start and end enum names 
 * are used for iterating through the list of dimensions.
 */
enum ObserverPhaseSpaceDimension{
  OBSERVER_PHASE_SPACE_DIMENSION_start = 0,
  OBSERVER_COSINE_DIMENSION = DIMENSION_start,
  OBSERVER_SOURCE_ENERGY_DIMENSION,
  OBSERVER_ENERGY_DIMENSION,
  OBSERVER_SOURCE_TIME_DIMENSION,
  OBSERVER_TIME_DIMENSION,
  OBSERVER_COLLISION_NUMBER_DIMENSION,
  OBSERVER_SOURCE_ID_DIMENSION,
  OBSERVER_PHASE_SPACE_DIMENSION_end
};

//! Convert the ObserverPhaseSpaceDimension to a string
std::string convertObserverPhaseSpaceDimensionToString(
                                 const ObserverPhaseSpaceDimension dimension );

//! Convert the ObserverPhaseSpaceDimension to a string (basic)
std::string convertObserverPhaseSpaceDimensionToStringBasic(
                                 const ObserverPhaseSpaceDimension dimension );

//! Convert an unsigned to an ObserverPhaseSpaceDimension
PhaseSpaceDimension convertUnsignedToPhaseSpaceDimensionEnum(
                                                    const unsigned dimension );

//! Stream operator for printing ObserverPhaseSpaceDimension enums
inline std::ostream& operator<<( std::ostream& os,
				 const ObserverPhaseSpaceDimension dimension )
{
  os << convertObserverPhaseSpaceDimensionToString( dimension );

  return os;
}

} // end MonteCarlo namespace

namespace Utility{

/*! The specialization of the Utility::HDF5TypeTraits for the
 * MonteCarlo::ObserverPhaseSpaceDimension enum
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<MonteCarlo::ObserverPhaseSpaceDimension>
{
  //! Return the HDF5 data type
  static inline H5::EnumType dataType()
  {
    H5::EnumType hdf5_phase_space_dimension_type(
			   sizeof( MonteCarlo::ObserverPhaseSpaceDimension ) );

    MonteCarlo::ObserverPhaseSpaceDimension value;
    std::string value_name;

    for( unsigned i = MonteCarlo::OBSERVER_PHASE_SPACE_DIMENSION_start;
         i < MonteCarlo::OBSERVER_PHASE_SPACE_DIMENSION_end;
         ++i )
    {
      value =
        MonteCarlo::convertUnsignedToObserverPhaseSpaceDimensionEnum( i );

      value_name =
        MonteCarlo::convertObserverPhaseSpaceDimensionToStringBasic( value );

      hdf5_phase_space_dimension_type.insert( value_name.c_str(), &value );
    }

    return hdf5_phase_space_dimension_type;
  }

  //! Return the name of the type
  static inline std::string name()
  {
    return "ObserverPhaseSpaceDimension";
  }

  //! Returns the zero value for this type
  static inline MonteCarlo::ObserverPhaseSpaceDimension zero()
  {
    return MonteCarlo::OBSERVER_PHASE_SPACE_DIMENSION_start;
  }

  //! Returns the unity value for this type
  static inline MonteCarlo::ObserverPhaseSpaceDimension one()
  {
    return MonteCarlo::OBSERVER_PHASE_SPACE_DIMENSION_start;
  }
};

} // end Utility namespace

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimension.hpp
//---------------------------------------------------------------------------//
