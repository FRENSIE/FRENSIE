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

namespace Transmutation {

class DecayMatrix {
public:
   static void getDecayMatrix(Teuchos::Array<int>& zaids,
                              Teuchos::SerialDenseMatrix<int,double>& decay_matrix,
                              std::string& data_file);
};

}
 
#endif // TRANSMUTATION_DECAY_MATRIX_HPP

//---------------------------------------------------------------------------//
// end Transmutation_DecayMatrix.hpp
//---------------------------------------------------------------------------//
