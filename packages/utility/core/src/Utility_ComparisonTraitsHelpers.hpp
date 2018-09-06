//---------------------------------------------------------------------------//
//!
//! \file   Utility_ComparisonTraitsHelpers.hpp
//! \author Alex Robinson
//! \brief  The comparison traits helper methods/classes declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMPARISON_TRAITS_HELPERS_HPP
#define UTILITY_COMPARISON_TRAITS_HELPERS_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "Utility_ComparisonPolicy.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

/*! Check the comparison result and add "passed" or "failed!" to the log
 * \ingroup comparison_traits
 */
void reportComparisonPassFail( const bool result, std::ostream& log );

namespace Details{

/*! Increment the right shift
 * \ingroup comparison_traits
 */
constexpr size_t incrementRightShift( const size_t right_shift )
{ return right_shift+2; }

/*! The zero helper
 * \ingroup comparison_traits
 */
template<typename T, typename Enabled = void>
struct ZeroHelper;

/*! STL compliant container zero helper implementation
 *
 * A partial specialization of ZeroHelper must be made for the container type
 * and it should inherit from this struct.
 * \ingroup comparison_traits
 */
template<typename STLCompliantContainer>
struct STLCompliantContainerZeroHelper
{
  //! Return the zero object
  static STLCompliantContainer zero( const STLCompliantContainer& mirror_obj );
};

/*! Create the zero object
 * \ingroup comparison_traits
 */
template<typename T>
T zero( const T& mirror_obj );

/*! Default implementation of the createComparisonHeader method
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T,
         typename ExtraDataType>
std::string createComparisonHeaderImpl( const T& left_value,
                                        const std::string& left_name,
                                        const bool log_left_name,
                                        const T& right_value,
                                        const std::string& right_name,
                                        const bool log_right_name,
                                        const std::string& name_suffix,
                                        const ExtraDataType& extra_data );

/*! Default implementation of the compare method
 * \ingroup comparison_traits
 */
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T,
         typename ExtraDataType,
         typename ComparisonHeaderGenerator = decltype(&Utility::Details::createComparisonHeaderImpl<ComparisonPolicy,RightShift,T,ExtraDataType>)>
bool compareImpl( const T& left_value,
                  const std::string& left_name,
                  const bool log_left_name,
                  const T& right_value,
                  const std::string& right_name,
                  const bool log_right_name,
                  const std::string& name_suffix,
                  std::ostream& log,
                  const bool log_comparison_details,
                  const ExtraDataType& extra_data,
                  const ComparisonHeaderGenerator header_generator =
                  &Utility::Details::createComparisonHeaderImpl<ComparisonPolicy,RightShift,T,ExtraDataType> );

} // end Details namespace

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_ComparisonTraitsHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_COMPARISON_TRAITS_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_ComparisonTraitsHelpers.hpp
//---------------------------------------------------------------------------//
