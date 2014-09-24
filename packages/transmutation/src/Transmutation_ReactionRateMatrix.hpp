//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_ReactionRateMatrix.hpp
//! \author Alex Bennett
//! \brief  Creates a reaction rate matrix for depletion. 
//!
//---------------------------------------------------------------------------//


#ifndef TRANSMUTATION_REACTION_RATE_MATRIX_HPP
#define TRANSMUTATION_REACTION_RATE_MATRIX_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearReactionType.hpp"

namespace Transmutation {

class ReactionRateMatrix {
public:
   static void addFissionFragments(Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& reaction_rate_matrix,
                                   const int fission_zaid, 
                                   const double& fission_reaction_rate,
                                   const Teuchos::Array<std::pair<int,double> >& fission_fragments);
   static void addReactionRates(Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& reaction_rate_matrix,
                                Teuchos::Array<std::pair<int,double> >& reaction_rates,
                                const MonteCarlo::NuclearReactionType& reaction);
private:
   static int getLocation(const int input_zaid, const Teuchos::Array<int>& zaids);
   static bool isIsotopeInList(const int input_zaid, const Teuchos::Array<int>& zaids);
   static int reactionProduct(const int input_zaid, const MonteCarlo::NuclearReactionType& reaction); 
};

}
 
#endif // TRANSMUTATION_REACTION_RATE_MATRIX_HPP

//---------------------------------------------------------------------------//
// end Transmutation_ReactionRateMatrix.hpp
//---------------------------------------------------------------------------//
