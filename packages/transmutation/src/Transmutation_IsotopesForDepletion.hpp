//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_IstopesForDepletion.hpp
//! \author Alex Bennett
//! \brief  Creates a list of istopes to be used in the depetion matrix.
//!
//---------------------------------------------------------------------------//


#ifndef TRANSMUTATION_ISOTOPES_FOR_DEPLETION_HPP
#define TRANSMUTATION_ISOTOPES_FOR_DEPLETION_HPP

//Trilinos Includes
#include <Teuchos_Array.hpp>

namespace Transmutation {

class IsotopesForDepletion {
public:
  static void getIsotopes();
private:
  static bool sZaidComparison(int i, int j);
};

} // TRANSMUTATION_ISOTOPES_FOR_DEPLETION_HPP

#endif // TRANSMUTATION_ISOTOPES_FOR_DEPLETION_HPP

//---------------------------------------------------------------------------//
// end Transmutation_IsotopesForDepletion.hpp
//---------------------------------------------------------------------------//
