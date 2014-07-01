//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_IsotopesArray.cpp
//! \author Alex Bennett
//! \brief  Creates and read the Isotopes Array
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "Transmutation_IsotopesArray.hpp"

namespace Transmutation {

void IsotopesArray::setIsotopesArray()
{
     boost::unordered_map<int,double> concentrations; 

     concentrations.insert( std::pair<int,double>(1001,5.0) );
     concentrations.insert( std::pair<int,double>(2004,10.0) );

     for(boost::unordered_map<int,double>::iterator i = concentrations.begin(); i != concentrations.end(); ++i)
     {
          std::cout << i->first << " " << i->second << std::endl;
     }
}

} // End namespace transmutation

//---------------------------------------------------------------------------//
// end Transmutation_IsotopesArray.cpp
//---------------------------------------------------------------------------//
