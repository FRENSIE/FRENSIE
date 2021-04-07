//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringDistributionFactoryHelpers.cpp
//! \author Alex Robinson
//! \brief  Nuclear scattering distribution factory helper function defs.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistributionFactoryHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Calculate the AND/DLW block distribution array sizes
void calculateDistArraySizes(
                     const Utility::ArrayView<const double>& location_block,
		     const Utility::ArrayView<const double>& data_block,
                     std::vector<unsigned>& dist_array_sizes )
{
  unsigned first_index = 0, second_index = 1;

  dist_array_sizes.resize( location_block.size() );

  // find first/next nonzero positive location block values
  while( first_index != location_block.size() )
  {
    if( location_block[ first_index ]  > 0 )
    {
      if( first_index < location_block.size() - 1)
      {
        // find the second nonzero positive location block value
        while( second_index != location_block.size() )
        {
          if( location_block[ second_index ] > 0 )
          {
            dist_array_sizes[ first_index ] = location_block[ second_index ] - location_block[ first_index ];
            break;
          }
          else
          {
            dist_array_sizes[ second_index ] = 0;
          }
          ++second_index;
        }
        // Check if the second index is beyond the bounds of the array
        if( second_index == location_block.size() and first_index != location_block.size() - 1 )
        {
          dist_array_sizes[ first_index ] = data_block.size() + 1 - location_block[first_index];
        }
        first_index = second_index;
        ++second_index;
      }
      else
      {
        dist_array_sizes[ first_index ] = data_block.size() + 1 - location_block[first_index];
        ++first_index;
        ++second_index;
      }
    }
    else
    {
      dist_array_sizes[ first_index ] = 0;
      ++first_index;
      ++second_index;
    }
  }

  // Make sure every index in the location block has a corresponding array size
  testPostcondition( dist_array_sizes.size() ==
		     location_block.size() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringDistributionFactoryHelpers.cpp
//---------------------------------------------------------------------------//
