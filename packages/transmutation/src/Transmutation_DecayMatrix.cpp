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
#include "Data_DecayDataContainer.hpp"
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
  Data::DecayDataContainer decay_library(decay_data_path);

  std::set<unsigned> available_szaids = 
    decay_library.getNuclideIdentifiers();
  
  // Allocate the matrix
  decay_matrix->shape(zaids.length(),zaids.length());
  
  // Loop through all the isotopes in the matrix and fill with appropriate data
  for(int i = 0; i < zaids.length(); i++)
  {
    // Get decay data for the isotope if any is available
    if( available_szaids.count( zaids[i] ) )
    {
      Data::DecayNuclide decay_nuclide = 
	decay_library.getDecayNuclide( zaids[i] );          
      
      // Add the decay isotopes to the matrix
      DecayMatrix::addDecayIsotopes( decay_matrix, zaids, decay_nuclide, i );
      
      // Check if the isotope can fission spontaneously
      if( FissionableIsotopes::isSpontaneousFissionable( zaids[i] ) )
      {
	// Add the fission fragments to the matrix
	DecayMatrix::addSpontaneousFissionYields( decay_matrix, 
						  zaids, 
						  decay_nuclide, 
						  i) ;
      }
    }
  }
}

void DecayMatrix::addDecayIsotopes(Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& decay_matrix, 
                                   Teuchos::Array<int>& zaids, 
                                   Data::DecayNuclide& decay_nuclide,
                                   const int i)
{ 
  // Add the decay constants for the isotope
  (*decay_matrix)(i,i) -= decay_nuclide.getDecayConstant();
  
  // Loop through the number of decay daughters for the isotopes
  for(int j = 0; j < decay_nuclide.getNumberOfDecayBranches(); j++)
  {
    // Find the location to place the fission fragment into the matrix
    int decay_location = IsotopesForDepletion::getLocation( 
						  decay_nuclide.getDaughter(j),
						  zaids );

    // Chech if isotope was found
    if( decay_location >= 0 )
    {
      (*decay_matrix)(decay_location,i) += 
	decay_nuclide.getDecayConstant() * 
	decay_nuclide.getBranchingRatio(j);
    }
  }
}

void DecayMatrix::addSpontaneousFissionYields(
	   Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& decay_matrix,
	   Teuchos::Array<int>& zaids,
	   Data::DecayNuclide& decay_nuclide,
	   const int i )
{
  // Get the file path to the endf file with the fission fragments
  std::string endf_file_path = 
    FissionableIsotopes::getSpontaneousFissionableIsotopeFilePath( zaids[i] );

  // Open the endf file with the fission fragments
  Data::ENDFFissionYieldsFileHandler fission_yields( endf_file_path.c_str(), 
						     zaids[i] );

  // Loop through the fission fragments
  for(int j = 0; j < fission_yields.getZaidFissionProductsIndependentYields()[0].length(); j++)
  {
    // Find the location to place the fission fragment into the matrix
    int fission_fragment_location = 
      IsotopesForDepletion::getLocation( 
		fission_yields.getZaidFissionProductsIndependentYields()[0][j],
		zaids );

    // Chech if isotope was found
    if( fission_fragment_location >= 0 )
    {
      // Add the fission fragment to the matrix
      (*decay_matrix)(fission_fragment_location,i) += 
	DecayMatrix::getSpontaneousFissionBranchingRatio(decay_nuclide) *
	fission_yields.getYieldFissionProductsIndependentYields()[0][j] *
	decay_nuclide.getDecayConstant();
    } 
  }
}

double DecayMatrix::getSpontaneousFissionBranchingRatio( 
				      const Data::DecayNuclide& decay_nuclide )
{
  double branching_ratio = 0;
  
  // Loop through the number of decay daughters for the isotopes
  for(int i = 0; i < decay_nuclide.getNumberOfDecayBranches(); i++)
  {
    if( decay_nuclide.getDaughter(i) == 0 )
      branching_ratio = decay_nuclide.getBranchingRatio(i);
  }
  
  // Make sure branching ratio is greater then 0
  testPostcondition(branching_ratio >= 0);
  
  return branching_ratio;
}


} // End namespace transmutation

//---------------------------------------------------------------------------//
// end Transmutation_DecayMatrix.cpp
//---------------------------------------------------------------------------//
