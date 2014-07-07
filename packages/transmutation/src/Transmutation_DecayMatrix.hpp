//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_DecayMatrix.hpp
//! \author Alex Bennett
//! \brief  Creates a decay matrix for depletion. 
//!
//---------------------------------------------------------------------------//


#ifndef TRANSMUTATION_DECAY_MATRIX_HPP
#define TRANSMUTATION_DECAY_MATRIX_HPP

//Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FRENSIE Includes
#include "Data_DecayData.hpp"

namespace Transmutation {

class DecayMatrix {
public:
   static void getDecayMatrix(Teuchos::SerialDenseMatrix<int,double>& decay_matrix,
                              const std::string& data_file = DecayMatrix::default_data_file);
private: 
   static void addDecayIsotopes(Teuchos::SerialDenseMatrix<int,double>& decay_matrix, 
                                             Teuchos::Array<int>& zaids, 
                                             data::DecayData& decay_data,
                                             const int i); 
   static void addSpontaneousFissionYields(Teuchos::SerialDenseMatrix<int,double>& decay_matrix, 
                                                        Teuchos::Array<int>& zaids_array,
                                                        data::DecayData& decay_data,
                                                        const int i);
   static double getSpontaneousFissionBranchingRatio(const data::DecayData& decay_data);
   static const std::string default_data_file;
};

}
 
#endif // TRANSMUTATION_DECAY_MATRIX_HPP

//---------------------------------------------------------------------------//
// end Transmutation_DecayMatrix.hpp
//---------------------------------------------------------------------------//
