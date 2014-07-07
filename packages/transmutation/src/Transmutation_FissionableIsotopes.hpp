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
  static bool isSpontaneousFissionable(const int zaid);
  static std::string getFissionableIsotopeFilePath(const int zaid);
  static std::string getSpontaneousFissionableIsotopeFilePath(const int zaid);
  static boost::unordered_set<int> getAllFissionableIsotopes();
  static boost::unordered_set<int> getAllSpontaneousFissionableIsotopes();
private:
  static bool isENDFSpontaneousFissionable(const int zaid);
  static bool isUKFYSpontaneousFissionable(const int zaid);
  static boost::unordered_set<int> master_fissionable_set;
  static boost::unordered_set<int> master_spontaneous_fissionable_set;
  static boost::unordered_set<int> endf_master_spontaneous_fissionable_set;
  static boost::unordered_set<int> ukfy_master_spontaneous_fissionable_set;
};

} // TRANSMUTATION_FISSIONABLE_ISOTOPES_HPP

#endif // TRANSMUTATION_FISSIONABLE_ISOTOPES_HPP

//---------------------------------------------------------------------------//
// end Transmutation_FissionableIsotopes.hpp
//---------------------------------------------------------------------------//
