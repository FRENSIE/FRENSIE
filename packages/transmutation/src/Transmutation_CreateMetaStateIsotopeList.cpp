//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_CreateMetaStateIsotopeList.cpp
//! \author Alex Bennett
//! \brief  Creates a list of meta stable isotopes
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "Transmutation_CreateMetaStateIsotopeList.hpp"
#include "Transmutation_FissionableIsotopes.hpp"
#include "Data_ENDFFissionYieldsFileHandler.hpp"

namespace Transmutation {

void CreateMetaStateIsotopeList::createList()
{
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
   
         // Get an array of all the possible fission fragments
         Teuchos::Array<int> zaids = fission_yields.getZaidFissionProductsIndependentYields()[0];
   
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

      std::cout << std::endl;

      // Loop through all the possible Z numbers
      for(int i = 1; i <= 100; i++)
      {
          // Loop through all the meta stable zaids
          for(boost::unordered_set<int>::iterator j = meta_state_zaids.begin(); j != meta_state_zaids.end(); ++j)
          {
              // Check if the current Z number matches any in the set
              if( i == (*j - 1000000)/1000)
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
