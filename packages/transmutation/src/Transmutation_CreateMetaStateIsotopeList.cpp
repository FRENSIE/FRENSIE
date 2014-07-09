//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_CreateMetaStateIsotopeList.cpp
//! \author Alex Bennett
//! \brief  Creates a list of meta stable isotopes
//!
//---------------------------------------------------------------------------//

// This subroutine is just for creating lists and is not run at execution.

// Boost Includes
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "Transmutation_CreateMetaStateIsotopeList.hpp"
#include "Transmutation_FissionableIsotopes.hpp"
#include "Transmutation_AllIsotopes.hpp"
#include "Data_ENDFFissionYieldsFileHandler.hpp"
#include "Data_DecayFile.hpp"
#include "Data_DecayData.hpp"
#include "Data_DecayLib.hpp"
#include "DecayDataPath.hpp"

namespace Transmutation {

void CreateMetaStateIsotopeList::createList()
{
// Gets all the meta stable isotopes for neutron induced fission.

      // Create a set of all the fissionable isotopes
      boost::unordered_set<int> fissionable_zaids = FissionableIsotopes::getAllFissionableIsotopes();

      // Create a set for the meta stable zaids
      boost::unordered_set<int> meta_state_zaids;

      // Loop over the fissionable isotopes
      for(boost::unordered_set<int>::iterator i = fissionable_zaids.begin();
          i != fissionable_zaids.end();
          ++i)
      {

         // Get the file path to the endf file with the fission fragments
         std::string endf_file_path = FissionableIsotopes::getFissionableIsotopeFilePath( *i );
   
         // Open the endf file with the fission fragments
         Data::ENDFFissionYieldsFileHandler fission_yields( endf_file_path.c_str(), *i );
   
         // Loop through all possible energies of fission products
         for(int j = 0 ; j < fission_yields.getEnergyIndependentYields().size(); j++)
         {
             // Get an array of all the possible fission fragments
             Teuchos::Array<int> zaids = fission_yields.getZaidFissionProductsIndependentYields()[j];
   
             // Loop through all the possible fission fragments
             for(Teuchos::Array<int>::iterator k = zaids.begin(); k!= zaids.end(); ++k)
             {
                 // Check if the fission fragment is a meta stable zaid
                 if( *k > 1000000)
                 {
                     // Add the meta stable zaid to the set
                     meta_state_zaids.insert(*k);
                 }
             }
          }
      }

// Gets all the meta stable isotopes from spontaneous fission 

      // Create a set of all the fissionable isotopes
      boost::unordered_set<int> spontaneous_fissionable_zaids = FissionableIsotopes::getAllSpontaneousFissionableIsotopes();

      // Loop over the fissionable isotopes
      for(boost::unordered_set<int>::iterator i = spontaneous_fissionable_zaids.begin();
          i != spontaneous_fissionable_zaids.end();
          ++i)
      {

         // Get the file path to the endf file with the fission fragments
         std::string endf_file_path = FissionableIsotopes::getSpontaneousFissionableIsotopeFilePath( *i );
   
         // Open the endf file with the fission fragments
         Data::ENDFFissionYieldsFileHandler spontaneous_fission_yields( endf_file_path.c_str(), *i );
   
         // Get an array of all the possible fission fragments
         Teuchos::Array<int> zaids = spontaneous_fission_yields.getZaidFissionProductsIndependentYields()[0];
   
         // Loop through all the possible fission fragments
         for(Teuchos::Array<int>::iterator j = zaids.begin(); j!= zaids.end(); ++j)
         {
             // Check if the fission fragment is a meta stable zaid
             if( *j > 1000000)
             {
                 // Add the meta stable zaid to the set
                 meta_state_zaids.insert(*j);
             }
         }

      }

// Gets all the meta stable isotopes from decay

      // Create array for zaids
      Teuchos::Array<int> zaids;

      // Fill the zaids array
      AllIsotopes::getAllZaids(zaids);

      // Set up path to cross section file
      std::string decay_data_path = DECAY_DATA_DIRECTORY;
      decay_data_path += "endf7.dk.xml";
  
      // Open cross section file
      data::DecayFile decay_file(decay_data_path);
      data::DecayLib decay_library(decay_file);
 
      // Loop over all the possible zaids 
      for(int i = 0; i != zaids.length(); i++)
      {
          // Get decay data for the isotope
          data::DecayData decay_data = decay_library.GetDecayData(zaids[i]);
  
          // Get the number of daughter nuclides
          for(int j = 0; j < decay_data.GetNumber(); j++)
          {
              // Check if the daughter nuclide is a meta stable isotope
              if(decay_data.GetDaughter(j) > 1000000)
              {
                 // Add the meta stable zaid to the set
                 meta_state_zaids.insert(decay_data.GetDaughter(j));
              }
         }
      }

// Sets up and prints out the list of meta stable isotopes

      // Loop through all the possible Z numbers
      for(int i = 1; i <= 100; i++)
      {
          // Loop through all the meta stable zaids
          for(boost::unordered_set<int>::iterator j = meta_state_zaids.begin(); j != meta_state_zaids.end(); ++j)
          {
              // Check if the current Z number matches any in the set
              if( i == (*j - 1000000)/1000 or i == (*j - 2000000)/1000)
              {
                  // Start to create the map using the Z number
                  std::cout << "(" << i << ",boost::assign::list_of";
  
                   // Loop through the set again to add all the possible meta stable zaids to the map
                   for(boost::unordered_set<int>::iterator k = meta_state_zaids.begin(); k != meta_state_zaids.end(); ++k)
                   { 
                        if( i == (*k - 1000000)/1000 or i == (*k - 2000000)/1000 )
                        {
			     std::cout << "(" << *k << ")";
                        }
                   }
                  
                   std::cout << ")" << std::endl;
  
                   break;
              }
          }
      }
};

} // End namespace transmutation

//---------------------------------------------------------------------------//
// end Transmutation_CreateMetaStateIsotopeList.cpp
//---------------------------------------------------------------------------//
