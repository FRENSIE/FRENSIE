//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_DecayMatrix.cpp
//! \author Alex Bennett
//! \brief  Creates a decay matrix for depletion.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Transmutation_DecayMatrix.hpp"
#include "Data_DecayFile.hpp"
#include "Data_DecayData.hpp"
#include "Data_DecayLib.hpp"
#include "DecayDataPath.hpp"

namespace Transmutation {

void DecayMatrix::getDecayMatrix(Teuchos::Array<int>& zaids,
                                 Teuchos::Array<Teuchos::Array<double> >& decay_matrix,
                                 std::string& data_file)
{
     // Set up path to cross section file
     std::string decay_data_path = DECAY_DATA_DIRECTORY;
     decay_data_path += data_file;

     // Open cross section file
     data::DecayFile decay_file(decay_data_path);
     data::DecayLib decay_library(decay_file);

     // Allocate the matrix
     decay_matrix.resize(zaids.length());

     // Set up Decay Matrix
     for(int i = 0; i < zaids.length(); i++)
     {
          decay_matrix[i].resize(zaids.length(),0.0);
     }     

     // Fill Decay Matrix
     // Loop through all the isotopes in the matrix
     for(int i = 0; i < zaids.length(); i++)
     {
          // Get decay data for the isotope
          data::DecayData decay_data = decay_library.GetDecayData(zaids[i]);          

          // Add the decay constants for the isotope
          decay_matrix[i][i] -= decay_data.GetDecayConst();

          // Loop through the number of decay daughters for the isotopes
          for(int j = 0; j < decay_data.GetNumber(); j++)
          {
               for(int k = 0; k < zaids.length(); k++)
               {
                     // Check if the daughter nuclide is also in the matrix
                     if( zaids[k] == decay_data.GetDaughter(j) )
                     {
                          // Add the decay constants for the daughter nuclide of the isotope
                          decay_matrix[k][i] += decay_data.GetDecayConst() * decay_data.GetBranchingRatio(j);
                     }
               }
          }
      }
}

} // End namespace transmutation

//---------------------------------------------------------------------------//
// end Transmutation_DecayMatrix.cpp
//---------------------------------------------------------------------------//
