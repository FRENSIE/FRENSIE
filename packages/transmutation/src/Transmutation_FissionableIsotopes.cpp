//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_FissionableIsotopes.cpp
//! \author Alex Bennett
//! \brief  Checks if an isotope is fissionable.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/unordered_set.hpp>
#include <boost/assign/list_of.hpp>

// FRENSIE Includes
#include "Transmutation_FissionableIsotopes.hpp"
#include "Utility_ContractException.hpp"
#include "ENDFFissionProductDataPath.hpp"

namespace Transmutation {

// Initializing static member data.
boost::unordered_set<int> FissionableIsotopes::master_fissionable_set = boost::assign::list_of
     (90227) 
     (90229)
     (90232)
     (91231)
     (92232)
     (92233)
     (92234)
     (92235)
     (92236)
     (92237)
     (92238)
     (93237)
     (93238)
     (94238)
     (94239)
     (94240)
     (94241)
     (94242)
     (95241)
     (95243)
     (96242)
     (96243)
     (96244)
     (96245)
     (96246)
     (96248)
     (98249)
     (98250)
     (98251)
     (98252)
     (99253)
     (99254)
     (100254)
     (100255)
     (100256)
     (1095242);

// Check if the isotope is in the list of fissionable isotopes.
bool FissionableIsotopes::isFissionable(const int zaid)
{
   if( FissionableIsotopes::master_fissionable_set.find(zaid) ==
       FissionableIsotopes::master_fissionable_set.end())
   {
       return false;
   }
   else
   {
       return true;
   }
} 

std::string FissionableIsotopes::getFissionableIsotopeFilePath(const int zaid)
{
    // Make sure isotope is fissionable
    testPrecondition(isFissionable(zaid));

    std::ostringstream oss;
    oss << zaid;

    std::string zaid_file_path = ENDF_FISSION_PRODUCT_DIRECTORY;
    zaid_file_path += oss.str();
    zaid_file_path += ".txt";

    return zaid_file_path;
}

boost::unordered_set<int> FissionableIsotopes::getAllFissionableIsotopes()
{
    return FissionableIsotopes::master_fissionable_set;
}

} // End namespace transmutation

//---------------------------------------------------------------------------//
// end Transmutation_FissionableIsotopes.cpp
//---------------------------------------------------------------------------//
