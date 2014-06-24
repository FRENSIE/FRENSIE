//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_FissionableIsotopes.hpp
//! \author Alex Bennett
//! \brief  Checks if an isotope is fissionable.
//!
//---------------------------------------------------------------------------//


#ifndef TRANSMUTATION_FISSIONABLE_ISOTOPES_HPP
#define TRANSMUTATION_FISSIONABLE_ISOTOPES_HPP

#include <boost/unordered_set.hpp>

namespace Transmutation {

class FissionableIsotopes {
public:
  static bool isFissionable(const int zaid);
  static std::string getFissionableIsotopeFilePath(const int zaid);
  static boost::unordered_set<int> getAllFissionableIsotopes();
private:
  static boost::unordered_set<int> master_fissionable_set;
};

} // TRANSMUTATION_FISSIONABLE_ISOTOPES_HPP

#endif // TRANSMUTATION_FISSIONABLE_ISOTOPES_HPP

//---------------------------------------------------------------------------//
// end Transmutation_FissionableIsotopes.hpp
//---------------------------------------------------------------------------//
