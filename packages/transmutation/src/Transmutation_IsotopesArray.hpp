//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_IsotopesArray.hpp
//! \author Alex Bennett
//! \brief  Creates and reads from the Isotope Array. 
//!
//---------------------------------------------------------------------------//


#ifndef TRANSMUTATION_ISOTOPES_ARRAY_HPP
#define TRANSMUTATION_ISOTOPES_ARRAY_HPP

//Trilinos Includes
#include <Teuchos_Array.hpp>

namespace Transmutation {

class IsotopesArray {
public:
   static void getOrderedIsotopesArray(const boost::unordered_map<int,double>& number_densities,
                                       Teuchos::Array<double>& number_densities_array);
   static bool isIsotopeInList(int isotope);
   static void getIsotopesNumberDensityMap(boost::unordered_map<int,double>& number_densities,
                                          const Teuchos::Array<double>& number_densities_array);
   static void getNumberDensityMapFromUnorderedArray(boost::unordered_map<int,double>& number_densities,
                                                     const Teuchos::Array<std::pair<int,double> >& number_densities_array);
   static void getUnorderedArray(Teuchos::Array<std::pair<int,double> >& unordered_number_densities,
                                 const Teuchos::Array<double>& ordered_number_densities,
                                 const double lower_bound = 1e-3);
};

}
 
#endif // TRANSMUTATION_ISOTOPES_ARRAY_HPP

//---------------------------------------------------------------------------//
// end Transmutation_IsotopesArray.hpp
//---------------------------------------------------------------------------//
