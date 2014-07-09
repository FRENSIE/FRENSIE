//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_IsotopesForDepletion.cpp
//! \author Alex Bennett
//! \brief  Creates a list of istopes to be used in the depetion matrix.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Transmutation_IsotopesForDepletion.hpp"
#include "Transmutation_AllIsotopes.hpp"
#include "Utility_ContractException.hpp"

namespace Transmutation {

void IsotopesForDepletion::getIsotopes( Teuchos::Array<int>& zaids )
{
    zaids.clear();

    // Create Arrays for the zaids and meta stable zaids
    Teuchos::Array<int> meta_state_zaids;

    // Get all the zaids
    Transmutation::AllIsotopes::getAllZaids( zaids );

    // Get all the meta stable zaids
    Transmutation::AllIsotopes::getAllMetaStateZaids( meta_state_zaids );

    // Adds the meta stable zaids and the zaids into one list
    zaids.insert( zaids.end() , meta_state_zaids.begin() , meta_state_zaids.end() );

    // Sorts the array
    std::sort( zaids.begin() , zaids.end() , IsotopesForDepletion::sZaidComparison );
};

int IsotopesForDepletion::getLocation(const int input_zaid, const Teuchos::Array<int>& zaids)
{
   // Make sure the input zaid is positive
   testPrecondition( input_zaid >= 0 );

   // Search for input zaid location
   for(int i = 0; i != zaids.length(); i++)
   {
      if( input_zaid == zaids[i] )
      {
         return i;
      }
   }
   return -1;
}

bool IsotopesForDepletion::sZaidComparison(const int i, const int j)
{
    // Make sure i and j are numbers greater then 0
    testPrecondition( i > 0 and j > 0 );

    if( i < 1000000 and j > 1000000)
    {
         if( j > 2000000 )
         {
              return i <= j - 2000000;
         }
         else
         {
              return i <= j - 1000000;
         }
    }
    else if( i > 1000000 and j < 1000000)
    {
         if( i > 2000000)
         {
              return i - 2000000 < j;
         }
         else
         {
              return i - 1000000 < j;
         }
    }
    else if( i > 1000000 and j > 1000000)
    {
         if( i > 2000000 and j > 2000000)
         {
               return i < j;
         }
         else if( i > 2000000 )
         {
               return i - 1000000 < j;
         }
         else if( j > 2000000 )
         {
               return i > j - 2000000;
         }
         else
         {
               return i < j;
         }
    }
    else
    {
         return i < j;
    }
}

} // End namespace transmutation

//---------------------------------------------------------------------------//
// end Transmutation_IsotopesForDepletion.cpp
//---------------------------------------------------------------------------//
