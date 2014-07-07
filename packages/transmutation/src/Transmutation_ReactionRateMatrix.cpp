//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_ReactionRateMatrix.cpp
//! \author Alex Bennett
//! \brief  Creates a reaction rate matrix for depletion.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FRENSIE Includes
#include "Transmutation_ReactionRateMatrix.hpp"
#include "Transmutation_IsotopesForDepletion.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Facemc_NuclearReactionType.hpp"

namespace Transmutation {

void ReactionRateMatrix::addFissionFragments(Teuchos::SerialDenseMatrix<int,double>& reaction_rate_matrix,
                                             const int fission_zaid, 
                                             const double& fission_reaction_rate,
                                             const Teuchos::Array<std::pair<int,double> >& fission_fragments)
{
   // Initialize Zaid Array
   Teuchos::Array<int> zaids;
  
   // Fill zaid array
   IsotopesForDepletion::getIsotopes( zaids );

   // Get location of the fission zaid
   int fission_location = IsotopesForDepletion::getLocation( fission_zaid, zaids );

   // Make sure zaid location is not negeative
   testPrecondition( fission_location >= 0 );

   // Add the fission reaction rate to the matrix
   reaction_rate_matrix(fission_location,fission_location) -= fission_reaction_rate;

   // Loop through all the fission fragments
   for(int i = 0; i != fission_fragments.length(); i++)
   {
      // Get the location of the fission fragment
      int fission_fragment_location = IsotopesForDepletion::getLocation( fission_fragments[i].first, zaids );

      // Make sure zaid location is not negeative
      testPrecondition( fission_fragment_location >= 0 );

      // Add the fission fragment rection rate to the matrix
      reaction_rate_matrix(fission_fragment_location,fission_location) += fission_fragments[i].second;
   }
}
   
void ReactionRateMatrix::addReactionRates(Teuchos::SerialDenseMatrix<int,double>& reaction_rate_matrix,
                                          Teuchos::Array<std::pair<int,double> >& reaction_rates,
                                          const Facemc::NuclearReactionType& reaction)
{
   // Initialize zaids array
   Teuchos::Array<int> zaids;

   // Fill zaids array
   IsotopesForDepletion::getIsotopes( zaids );

   // Loop through all the reaction rates of a certain reaction
   for(int i = 0; i != reaction_rates.length(); i++)
   {
      // Get the location of the isotope undergoing the reaction
      int reaction_loc = ReactionRateMatrix::getLocation(reaction_rates[i].first, zaids);

      // Add the reaction rate into the matrix
      reaction_rate_matrix(reaction_loc,reaction_loc) -= reaction_rates[i].second;

      // Get the daughter nuclide
      int daughter_zaid = ReactionRateMatrix::reactionProduct(reaction_rates[i].first, reaction);

      // Get the location of the daughter nuclide
      int daughter_loc = ReactionRateMatrix::getLocation(daughter_zaid, zaids);

      // Add the daughter nuclide reaction rate to the matrix
      reaction_rate_matrix(daughter_loc,reaction_loc) += reaction_rates[i].second;
   }
}

int ReactionRateMatrix::getLocation(const int input_zaid, const Teuchos::Array<int>& zaids)
{
   // Make sure the input zaid is greater then 1000
   testPrecondition( input_zaid > 1000 );

   // Make sure the input zaid is in the zaid list
   testPrecondition( ReactionRateMatrix::isIsotopeInList( input_zaid , zaids ) );

   // Search for input zaid location
   for(int i = 0; i != zaids.length(); i++)
   {
      if( input_zaid == zaids[i] )
      {
         return i;
      }
   }
   std::cerr << std::endl;
   std::cerr << "Error: ZAID number " << input_zaid << 
                " for the reaction rate matrix was not found in the list of isotopes for depletion." << std::endl;
   return -1;
}

bool ReactionRateMatrix::isIsotopeInList(const int input_zaid, const Teuchos::Array<int>& zaids)
{
   // Serach for input zaid location
   for(int i = 0; i != zaids.length(); i++)
   {
      if( input_zaid == zaids[i] )
      {
         return true;
      }
   }
   return false; 
}

int ReactionRateMatrix::reactionProduct(const int input_zaid, 
                                         const Facemc::NuclearReactionType& reaction) 
{
   switch ( reaction )
   {
      case Facemc::N__2N_REACTION:
         return input_zaid + 1 - 2;
      case Facemc::N__GAMMA_REACTION:
         return input_zaid + 1 - 0;
      case Facemc::N__P_REACTION:
         return input_zaid + 1 - 1000;
      case Facemc::N__D_REACTION:
         return input_zaid + 1 - 1002;
      case Facemc::N__T_REACTION:
         return input_zaid + 1 - 1003;
      case Facemc::N__ALPHA_REACTION:
         return input_zaid + 1 - 2004;
      case Facemc::N__HE3_REACTION:
         return input_zaid + 1 - 2003;
      default:
         // Error is reaction type is not found
         TEST_FOR_EXCEPTION(true,std::logic_error,"Unsupported Reaction Type"); 
   }
}
 
} // End namespace transmutation

//---------------------------------------------------------------------------//
// end Transmutation_ReactionRateMatrix.cpp
//---------------------------------------------------------------------------//
