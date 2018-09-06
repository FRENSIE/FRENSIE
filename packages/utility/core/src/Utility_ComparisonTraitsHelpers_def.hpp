//---------------------------------------------------------------------------//
//!
//! \file   Utility_ComparisonTraitsHelpers_def.hpp
//! \author Alex Robinson
//! \brief  The comparison traits helper methods/classes definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMPARISON_TRAITS_HELPERS_DEF_HPP
#define UTILITY_COMPARISON_TRAITS_HELPERS_DEF_HPP

namespace Utility{

namespace Details{

/*! Partial specialization of the zero helper for arithmetic types
 * \ingroup comparison_traits
 */
template<typename T>
struct ZeroHelper<T,typename std::enable_if<std::is_arithmetic<T>::value>::type>
{
  //! Return the zero object
  static inline T zero( const T )
  { return Utility::QuantityTraits<T>::zero(); }
};

/*! Partial specialization of the zero helper for quantity types
 * \ingroup comparison_traits
 */
template<typename Unit, typename T>
struct ZeroHelper<boost::units::quantity<Unit,T> >
{
  //! Return the zero object
  static inline boost::units::quantity<Unit,T> zero( const boost::units::quantity<Unit,T> )
  { return Utility::QuantityTraits<boost::units::quantity<Unit,T> >::zero(); }
};

/*! Specialization of the zero helper for std::string
 * \ingroup comparison_traits
 */
template<>
struct ZeroHelper<std::string>
{
  //! Return the zero object
  static inline std::string zero( const std::string& )
  { return std::string(); }
};

/*! Specialization of the zero helper for std::wstring
 * \ingroup comparison_traits
 */
template<>
struct ZeroHelper<std::wstring>
{
  //! Return the zero object
  static inline std::wstring zero( const std::wstring& )
  { return std::wstring(); }
};

// Create the zero object
template<typename T>
inline T zero( const T& mirror_obj )
{
  return Utility::Details::ZeroHelper<T>::zero( mirror_obj );
}

// Return the zero object
template<typename STLCompliantContainer>
inline STLCompliantContainer STLCompliantContainerZeroHelper<STLCompliantContainer>::zero( const STLCompliantContainer& mirror_obj )
{
  STLCompliantContainer zero_obj( mirror_obj );

  typename STLCompliantContainer::iterator it, end_it;
  it = zero_obj.begin();
  end_it = zero_obj.end();
  
  while( it != end_it )
  {
    *it = Utility::Details::ZeroHelper<typename STLCompliantContainer::value_type>::zero( *it );
    
    ++it;
  }
  
  return zero_obj;
}

// Default implementation of the createComparisonHeader method
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T,
         typename ExtraDataType>
inline std::string createComparisonHeaderImpl(
                                              const T& left_value,
                                              const std::string& left_name,
                                              const bool log_left_name,
                                              const T& right_value,
                                              const std::string& right_name,
                                              const bool log_right_name,
                                              const std::string& name_suffix,
                                              const ExtraDataType& extra_data )
{
  std::string comparison_header( RightShift, ' ' );

  comparison_header += ComparisonPolicy::createComparisonDetails(
                                       left_name, log_left_name, left_value,
                                       right_name, log_right_name, right_value,
                                       name_suffix, extra_data );
  comparison_header += ": ";

  return comparison_header;
}
  
// Default implementation of the compare method
template<typename ComparisonPolicy,
         size_t RightShift,
         typename T,
         typename ExtraDataType,
         typename ComparisonHeaderGenerator>
inline bool compareImpl( const T& left_value,
                         const std::string& left_name,
                         const bool log_left_name,
                         const T& right_value,
                         const std::string& right_name,
                         const bool log_right_name,
                         const std::string& name_suffix,
                         std::ostream& log,
                         const bool log_comparison_details,
                         const ExtraDataType& extra_data,
                         const ComparisonHeaderGenerator header_generator )
{
  if( log_comparison_details )
  {
    log << header_generator( left_value, left_name, log_left_name,
                             right_value, right_name, log_right_name,
                             name_suffix, extra_data );
  }

  // Conduct the comparison
  const bool success =
    ComparisonPolicy::compare( left_value, right_value, extra_data );

  if( log_comparison_details )
    Utility::reportComparisonPassFail( success, log );

  return success;
}
  
} // end Details namespace
  
} // end Utility namespace

#endif // end UTILITY_COMPARISON_TRAITS_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_ComparisonTraitsHelpers_def.hpp
//---------------------------------------------------------------------------//
