//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_FissionableIsotopes.cpp
//! \author Alex Bennett
//! \brief  Checks if an isotope is fissionable.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/unordered_set.hpp>
#include <boost/assign/list_of.hpp>

// FRENSIE Includes
#include "Transmutation_FissionableIsotopes.hpp"
#include "FissionProductDataPath.hpp"
#include "Utility_ContractException.hpp"

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

// Initializing static member data.
boost::unordered_set<int> FissionableIsotopes::endf_master_spontaneous_fissionable_set = boost::assign::list_of
     (92238)
     (96244)
     (96246)
     (96248)
     (98250)
     (98252)
     (99253)
     (100254)
     (100256);

boost::unordered_set<int> FissionableIsotopes::ukfy_master_spontaneous_fissionable_set = boost::assign::list_of
     (90230)
     (90232)
     (91231)
     (91238)
     (92232)
     (92234)
     (92235)
     (92236)
     (92238)
     (93228)
     (94236)
     (94238)
     (94239)
     (94240)
     (94242)
     (94244)
     (95232)
     (95234)
     (95241)
     (95243)
     (96234)
     (96242)
     (96244)
     (96246)
     (96248)
     (96250)
     (97238)
     (97240)
     (97242)
     (97249)
     (98237)
     (98238)
     (98240)
     (98242)
     (98249)
     (98250)
     (98252)
     (1095242)
     (2095242);
 
boost::unordered_set<int> FissionableIsotopes::master_spontaneous_fissionable_set = boost::assign::list_of
     (90230)
     (90232)
     (91231)
     (91238)
     (92232)
     (92234)
     (92235)
     (92236)
     (92238)
     (93228)
     (94236)
     (94238)
     (94239)
     (94240)
     (94242)
     (94244)
     (95232)
     (95234)
     (95241)
     (95243)
     (96234)
     (96242)
     (96244)
     (96246)
     (96248)
     (96250)
     (97238)
     (97240)
     (97242)
     (97249)
     (98237)
     (98238)
     (98240)
     (98242)
     (98249)
     (98250)
     (98252)
     (99253)
     (100254)
     (100256)
     (1095242)
     (2095242);
 
// Check if the isotope is in the list of fissionable isotopes.
bool FissionableIsotopes::isFissionable(const int zaid)
{
   // Make sure zaid is a number greater then 0
   testPrecondition( zaid > 0 );

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

// Check if the isotope is in the list of spontaneous fissionable isotopes.
bool FissionableIsotopes::isSpontaneousFissionable(const int zaid)
{
   // Make sure zaid is a number greater then 0
   testPrecondition( zaid > 0 );

   if( FissionableIsotopes::master_spontaneous_fissionable_set.find(zaid) ==
       FissionableIsotopes::master_spontaneous_fissionable_set.end())
   {
       return false;
   }
   else
   {
       return true;
   }
} 

// Check if the isotope is in the list of endf spontaneous fissionable isotopes.
bool FissionableIsotopes::isENDFSpontaneousFissionable(const int zaid)
{
   // Make sure zaid is a number greater then 0
   testPrecondition( zaid > 0 );

   if( FissionableIsotopes::endf_master_spontaneous_fissionable_set.find(zaid) ==
       FissionableIsotopes::endf_master_spontaneous_fissionable_set.end())
   {
       return false;
   }
   else
   {
       return true;
   }
}
 
// Check if the isotope is in the list of ukfy spontaneous fissionable isotopes.
bool FissionableIsotopes::isUKFYSpontaneousFissionable(const int zaid)
{
   // Make sure zaid is a number greater then 0
   testPrecondition( zaid > 0 );

   if( FissionableIsotopes::ukfy_master_spontaneous_fissionable_set.find(zaid) ==
       FissionableIsotopes::ukfy_master_spontaneous_fissionable_set.end())
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

    std::string zaid_file_path = ENDF_NEUTRON_INDUCED_FISSION_PRODUCT_DIRECTORY;
    zaid_file_path += oss.str();
    zaid_file_path += ".txt";

    return zaid_file_path;
}

std::string FissionableIsotopes::getSpontaneousFissionableIsotopeFilePath(const int zaid)
{
    // Make sure isotope is spontaneous fissionable
    testPrecondition(isSpontaneousFissionable(zaid));

    std::ostringstream oss;
    oss << zaid;

    std::string zaid_file_path;

    if( isENDFSpontaneousFissionable(zaid) )
    {
       zaid_file_path = ENDF_SPONTANEOUS_FISSION_PRODUCT_DIRECTORY;
    }
    else if( isUKFYSpontaneousFissionable(zaid) )
    {
       zaid_file_path = UKFY_SPONTANEOUS_FISSION_PRODUCT_DIRECTORY;
    }
    else
    {
       zaid_file_path = " ";
       std::cerr << "Error: Spontaneous fissionable isotope : " << zaid 
                 << " data path not found " << std::endl;
    }
   
    zaid_file_path += oss.str();
    zaid_file_path += ".txt";

    return zaid_file_path;
}

boost::unordered_set<int> FissionableIsotopes::getAllFissionableIsotopes()
{
    return FissionableIsotopes::master_fissionable_set;
}

boost::unordered_set<int> FissionableIsotopes::getAllSpontaneousFissionableIsotopes()
{
    return FissionableIsotopes::master_spontaneous_fissionable_set;
}

} // End namespace transmutation

//---------------------------------------------------------------------------//
// end Transmutation_FissionableIsotopes.cpp
//---------------------------------------------------------------------------//
