//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_DecayMatrix.cpp
//! \author Alex Bennett
//! \brief  Creates a decay matrix for depletion.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Transmutation_DecayMatrix.hpp"
#include "Transmutation_IsotopesForDepletion.hpp"
#include "Transmutation_FissionableIsotopes.hpp"
#include "Data_DecayFile.hpp"
#include "Data_DecayData.hpp"
#include "Data_DecayLib.hpp"
#include "DecayDataPath.hpp"
#include "Data_ENDFFissionYieldsFileHandler.hpp"
#include "Utility_ContractException.hpp"

namespace Transmutation {

//Initializing Static Member Data
const std::string DecayMatrix::default_data_file = "endf7.dk.xml";

void DecayMatrix::getDecayMatrix(Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& decay_matrix,
                                 const std::string& data_file)
{
     // Set up the zaids array
     Teuchos::Array<int> zaids;
     IsotopesForDepletion::getIsotopes( zaids ); 

     // Set up path to cross section file
     std::string decay_data_path = DECAY_DATA_DIRECTORY;
     decay_data_path += data_file;

     // Open cross section file
     data::DecayFile decay_file(decay_data_path);
     data::DecayLib decay_library(decay_file);

     // Allocate the matrix
     decay_matrix->shape(zaids.length(),zaids.length());

     // Fill Decay Matrix
     // Loop through all the isotopes in the matrix
     for(int i = 0; i < zaids.length(); i++)
     {
         // Get decay data for the isotope
         data::DecayData decay_data = decay_library.GetDecayData(zaids[i]);          

         // Add the decay isotopes to the matrix
         DecayMatrix::addDecayIsotopes(decay_matrix, zaids, decay_data, i);
         
         // Check if the isotope can fission spontaneously
         if( FissionableIsotopes::isSpontaneousFissionable( zaids[i] ) )
         {
             // Add the fission fragments to the matrix
             DecayMatrix::addSpontaneousFissionYields(decay_matrix, zaids, decay_data, i);
         }
     }
}

void DecayMatrix::addDecayIsotopes(Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& decay_matrix, 
                                   Teuchos::Array<int>& zaids, 
                                   data::DecayData& decay_data,
                                   const int i)
{ 
     // Add the decay constants for the isotope
     (*decay_matrix)(i,i) -= decay_data.GetDecayConst();

     // Loop through the number of decay daughters for the isotopes
     for(int j = 0; j < decay_data.GetNumber(); j++)
     {
        // Find the location to place the fission fragment into the matrix
        int decay_location = IsotopesForDepletion::getLocation( decay_data.GetDaughter(j), zaids );

         // Chech if isotope was found
         if( decay_location >= 0 )
         {
              (*decay_matrix)(decay_location,i) += decay_data.GetDecayConst() * decay_data.GetBranchingRatio(j);
         }
     }
}

void DecayMatrix::addSpontaneousFissionYields(Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& decay_matrix,
                                              Teuchos::Array<int>& zaids,
                                              data::DecayData& decay_data,
                                              const int i)
{
     // Get the file path to the endf file with the fission fragments
     std::string endf_file_path = FissionableIsotopes::getSpontaneousFissionableIsotopeFilePath( zaids[i] );

     // Open the endf file with the fission fragments
     Data::ENDFFissionYieldsFileHandler fission_yields( endf_file_path.c_str(), zaids[i] );

     // Loop through the fission fragments
     for(int j = 0; j < fission_yields.getZaidFissionProductsIndependentYields()[0].length(); j++)
     {
         // Find the location to place the fission fragment into the matrix
         int fission_fragment_location = 
             IsotopesForDepletion::getLocation( fission_yields.getZaidFissionProductsIndependentYields()[0][j], zaids );

          // Chech if isotope was found
          if( fission_fragment_location >= 0 )
          {
             // Add the fission fragment to the matrix
             (*decay_matrix)(fission_fragment_location,i) += 
                                     DecayMatrix::getSpontaneousFissionBranchingRatio(decay_data) *
                                     fission_yields.getYieldFissionProductsIndependentYields()[0][j] *
                                     decay_data.GetDecayConst();
          } 
     }
}

double DecayMatrix::getSpontaneousFissionBranchingRatio(const data::DecayData& decay_data)
{
   double branching_ratio = 0;

   // Loop through the number of decay daughters for the isotopes
   for(int i = 0; i < decay_data.GetNumber(); i++)
   {
       if(decay_data.GetDaughter(i) == 0)
       {
           branching_ratio = decay_data.GetBranchingRatio(i);
       }
   }

    // Make sure branching ratio is greater then 0
    testPostcondition(branching_ratio >= 0);

    return branching_ratio;
}


} // End namespace transmutation

//---------------------------------------------------------------------------//
// end Transmutation_DecayMatrix.cpp
//---------------------------------------------------------------------------//
