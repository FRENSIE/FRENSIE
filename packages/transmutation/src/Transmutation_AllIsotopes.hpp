//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_AllIsotopes.hpp
//! \author Alex Bennett
//! \brief  Includes all the isotopes for depletion.
//!
//---------------------------------------------------------------------------//


#ifndef TRANSMUTATION_ALL_ISOTOPES_HPP
#define TRANSMUTATION_ALL_ISOTOPES_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

namespace Transmutation {

class AllIsotopes {
public:
  static std::pair<int,int> getZaidLimits(const int z);
  static void getZaids(const int z, Teuchos::Array<int>& zaids);
  static void getAllZaids(Teuchos::Array<int>& zaids);
  static void getMetaStateZaids(const int z, Teuchos::Array<int>& meta_state_zaids);
  static void getAllMetaStateZaids(Teuchos::Array<int>& meta_state_zaids);
private:
  static boost::unordered_map<int, std::pair<int,int> > master_isotope_map;
  static boost::unordered_map<int, std::vector<int> > master_meta_state_isotope_map; 
};

} 

#endif // TRANSMUTATION_All_ISOTOPES_HPP

//---------------------------------------------------------------------------//
// end Transmutation_AllIsotopes.hpp
//---------------------------------------------------------------------------//
