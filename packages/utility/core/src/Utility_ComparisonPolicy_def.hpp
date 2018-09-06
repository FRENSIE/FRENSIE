//---------------------------------------------------------------------------//
//!
//! \file   Utility_ComparisonPolicy_def.hpp
//! \author Alex Robinson
//! \brief  Comparison policy class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMPARISON_POLICY_DEF_HPP
#define UTILITY_COMPARISON_POLICY_DEF_HPP

// Std Lib Includes
#include <cmath>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

namespace Utility{

namespace Details{

template<typename T, typename Enabled = void>
struct AbsoluteValueHelper
{
  //! Calculate the absolute value
  static inline T abs( const T& value )
  { return value; }
};

template<typename T>
struct AbsoluteValueHelper<T, typename std::enable_if<std::is_integral<T>::value>::type>
{
  //! Calculate the absolute value
  static inline T abs( const T& value )
  { return std::abs( value ); }
};

template<typename T>
struct AbsoluteValueHelper<T,typename std::enable_if<std::is_floating_point<T>::value>::type>
{
  static inline T abs( const T& value )
  { return std::fabs( value ); }
};

template<typename Unit, typename T>
struct AbsoluteValueHelper<boost::units::quantity<Unit,T> >
{
  static inline boost::units::quantity<Unit,T> abs( const boost::units::quantity<Unit,T>& value )
  {
    return boost::units::quantity<Unit,T>::from_value(
                       Details::AbsoluteValueHelper<T>::abs( value.value() ) );
  }
};
  
} // end Details namespace

// The comparison operator
template<typename DerivedType>
template<typename T>
bool ComparisonPolicy<DerivedType>::operator()(
                  const T& left_value,
                  const T& right_value,
                  const typename QuantityTraits<T>::RawType& extra_data ) const
{
  return DerivedType::compare( left_value, right_value, extra_data );
}

// Create the comparison details (default implementation)
template<typename DerivedType>
template<typename T>
std::string ComparisonPolicy<DerivedType>::createComparisonDetailsDefaultImpl(
                                   const std::string& left_name,
                                   const bool report_left_name,
                                   const T& left_value,
                                   const std::string& right_name,
                                   const bool report_right_name,
                                   const T& right_value,
                                   const std::string& name_suffix,
                                   const typename QuantityTraits<T>::RawType& )
{
  std::ostringstream oss;

  if( report_left_name )
  {
    oss << left_name;

    if( !name_suffix.empty() )
      oss << name_suffix;

    oss << " = ";
  }

  oss << Utility::toString( left_value ) << " "
      << DerivedType::template getOperatorName<T>() << " ";

  if( report_right_name )
  {
    oss << right_name;

    if( !name_suffix.empty() )
      oss << name_suffix;

    oss << " = ";
  }

  oss << Utility::toString( right_value );

  return oss.str();
}

// Get the comparison operator name
template<typename T>
inline std::string EqualityComparisonPolicy::getOperatorName()
{
  return "==";
}

// Create the comparison details
template<typename T>
inline std::string EqualityComparisonPolicy::createComparisonDetails(
                                   const std::string& left_name,
                                   const bool report_left_name,
                                   const T& left_value,
                                   const std::string& right_name,
                                   const bool report_right_name,
                                   const T& right_value,
                                   const std::string& name_suffix,
                                   const typename QuantityTraits<T>::RawType& )
{
  return BaseComparisonPolicy::createComparisonDetailsDefaultImpl(
                                                             left_name,
                                                             report_left_name,
                                                             left_value,
                                                             right_name,
                                                             report_right_name,
                                                             right_value,
                                                             name_suffix );
}

// Compare two values
template<typename T>
inline bool EqualityComparisonPolicy::compare(
                                   const T& left_value,
                                   const T& right_value,
                                   const typename QuantityTraits<T>::RawType& )
{
  return left_value == right_value;
}

// Get the comparison operator name
template<typename T>
inline std::string InequalityComparisonPolicy::getOperatorName()
{
  return "!=";
}

// Create the comparison details
template<typename T>
inline std::string InequalityComparisonPolicy::createComparisonDetails(
                                   const std::string& left_name,
                                   const bool report_left_name,
                                   const T& left_value,
                                   const std::string& right_name,
                                   const bool report_right_name,
                                   const T& right_value,
                                   const std::string& name_suffix,
                                   const typename QuantityTraits<T>::RawType& )
{
  return BaseComparisonPolicy::createComparisonDetailsDefaultImpl(
                                                             left_name,
                                                             report_left_name,
                                                             left_value,
                                                             right_name,
                                                             report_right_name,
                                                             right_value,
                                                             name_suffix );
}

// Compare two values
template<typename T>
inline bool InequalityComparisonPolicy::compare(
                                   const T& left_value,
                                   const T& right_value,
                                   const typename QuantityTraits<T>::RawType& )
{
  return left_value != right_value;
}

// Get the comparison operator name
template<typename T>
inline std::string GreaterThanComparisonPolicy::getOperatorName()
{
  return ">";
}

// Create the comparison details
template<typename T>
inline std::string GreaterThanComparisonPolicy::createComparisonDetails(
                                   const std::string& left_name,
                                   const bool report_left_name,
                                   const T& left_value,
                                   const std::string& right_name,
                                   const bool report_right_name,
                                   const T& right_value,
                                   const std::string& name_suffix,
                                   const typename QuantityTraits<T>::RawType& )
{
  return BaseComparisonPolicy::createComparisonDetailsDefaultImpl(
                                                             left_name,
                                                             report_left_name,
                                                             left_value,
                                                             right_name,
                                                             report_right_name,
                                                             right_value,
                                                             name_suffix );
}

// Compare two values
template<typename T>
inline bool GreaterThanComparisonPolicy::compare(
                                   const T& left_value,
                                   const T& right_value,
                                   const typename QuantityTraits<T>::RawType& )
{
  return left_value > right_value;
}

// Get the comparison operator name
template<typename T>
inline std::string GreaterThanOrEqualToComparisonPolicy::getOperatorName()
{
  return ">=";
}

// Create the comparison details
template<typename T>
inline std::string GreaterThanOrEqualToComparisonPolicy::createComparisonDetails(
                                   const std::string& left_name,
                                   const bool report_left_name,
                                   const T& left_value,
                                   const std::string& right_name,
                                   const bool report_right_name,
                                   const T& right_value,
                                   const std::string& name_suffix,
                                   const typename QuantityTraits<T>::RawType& )
{
  return BaseComparisonPolicy::createComparisonDetailsDefaultImpl(
                                                             left_name,
                                                             report_left_name,
                                                             left_value,
                                                             right_name,
                                                             report_right_name,
                                                             right_value,
                                                             name_suffix );
}

// Compare two values
template<typename T>
inline bool GreaterThanOrEqualToComparisonPolicy::compare(
                                   const T& left_value,
                                   const T& right_value,
                                   const typename QuantityTraits<T>::RawType& )
{
  return left_value >= right_value;
}

// Get the comparison operator name
template<typename T>
inline std::string LessThanComparisonPolicy::getOperatorName()
{
  return "<";
}

// Create the comparison details
template<typename T>
inline std::string LessThanComparisonPolicy::createComparisonDetails(
                                   const std::string& left_name,
                                   const bool report_left_name,
                                   const T& left_value,
                                   const std::string& right_name,
                                   const bool report_right_name,
                                   const T& right_value,
                                   const std::string& name_suffix,
                                   const typename QuantityTraits<T>::RawType& )
{
  return BaseComparisonPolicy::createComparisonDetailsDefaultImpl(
                                                             left_name,
                                                             report_left_name,
                                                             left_value,
                                                             right_name,
                                                             report_right_name,
                                                             right_value,
                                                             name_suffix );
}

// Compare two values
template<typename T>
inline bool LessThanComparisonPolicy::compare(
                                   const T& left_value,
                                   const T& right_value,
                                   const typename QuantityTraits<T>::RawType& )
{
  return left_value < right_value;
}

// Get the comparison operator name
template<typename T>
inline std::string LessThanOrEqualToComparisonPolicy::getOperatorName()
{
  return "<=";
}

// Create the comparison details
template<typename T>
inline std::string LessThanOrEqualToComparisonPolicy::createComparisonDetails(
                                   const std::string& left_name,
                                   const bool report_left_name,
                                   const T& left_value,
                                   const std::string& right_name,
                                   const bool report_right_name,
                                   const T& right_value,
                                   const std::string& name_suffix,
                                   const typename QuantityTraits<T>::RawType& )
{
  return BaseComparisonPolicy::createComparisonDetailsDefaultImpl(
                                                             left_name,
                                                             report_left_name,
                                                             left_value,
                                                             right_name,
                                                             report_right_name,
                                                             right_value,
                                                             name_suffix );
}

// Compare two values
template<typename T>
inline bool LessThanOrEqualToComparisonPolicy::compare(
                                   const T& left_value,
                                   const T& right_value,
                                   const typename QuantityTraits<T>::RawType& )
{
  return left_value <= right_value;
}

namespace Details{

//! Close comparison policy helper for floating point types
template<typename T, typename Enabled = void>
class CloseComparisonPolicyHelper
{
  // Typedef for this type
  typedef CloseComparisonPolicyHelper<T,Enabled> ThisType;

public:

  //! Get the comparison operator name
  static inline std::string getOperatorName()
  { return "~"; }

  //! Create the comparison details
  static std::string createComparisonDetails(
          const std::string& left_name,
          const bool report_left_name,
          const T& left_value,
          const std::string& right_name,
          const bool report_right_name,
          const T& right_value,
          const std::string& name_suffix,
          const typename QuantityTraits<T>::RawType& distance_tolerance )
  {
    std::ostringstream oss;

    if( report_left_name || report_right_name )
    {
      oss << "distance(";
      
      if( report_left_name )
      {
        oss << left_name;
        
        if( !name_suffix.empty() )
          oss << name_suffix;
      }
      else
        oss << Utility::toString( left_value );

      oss << ",";
      
      if( report_right_name )
      {
        oss << right_name;
        
        if( !name_suffix.empty() )
          oss << name_suffix;
      }
      else
        oss << Utility::toString( right_value );

      oss << ") = ";
    }

    oss << "distance(" << Utility::toString( left_value )
        << "," << Utility::toString( right_value ) << ") = "
        << Utility::toString(Utility::QuantityTraits<T>::initializeQuantity(ThisType::calculateDistance( left_value, right_value )))
        << " <= " << Utility::toString( Utility::QuantityTraits<T>::initializeQuantity( distance_tolerance ) );
    
    return oss.str();
  }

  //! Compare two values
  static inline bool compare(
          const T& left_value,
          const T& right_value,
          const typename QuantityTraits<T>::RawType& distance_tolerance )
  {
    return ThisType::calculateDistance( left_value, right_value ) <=
      distance_tolerance;
  }

  //! Calculate the absolute distance between the two values
  static inline typename QuantityTraits<T>::RawType calculateDistance(
                                                         const T& left_value,
                                                         const T& right_value )
  {
    return Utility::getRawQuantity( Details::AbsoluteValueHelper<T>::abs( left_value - right_value ) );
  }
};

//! Close comparison policy helper for all types except floating point types
template<typename T>
class CloseComparisonPolicyHelper<T,typename std::enable_if<!std::is_floating_point<typename QuantityTraits<T>::RawType>::value>::type>
{
public:

  //! Get the comparison operator name
  static inline std::string getOperatorName()
  { return Utility::EqualityComparisonPolicy::getOperatorName<T>(); }
  
  //! Create the comparison details
  static inline std::string createComparisonDetails(
                                   const std::string& left_name,
                                   const bool report_left_name,
                                   const T& left_value,
                                   const std::string& right_name,
                                   const bool report_right_name,
                                   const T& right_value,
                                   const std::string& name_suffix,
                                   const typename QuantityTraits<T>::RawType& )
  {
    return Utility::EqualityComparisonPolicy::createComparisonDetails(
                                                             left_name,
                                                             report_left_name,
                                                             left_value,
                                                             right_name,
                                                             report_right_name,
                                                             right_value,
                                                             name_suffix );
  }

  //! Compare two values
  static inline bool compare( const T& left_value,
                              const T& right_value,
                              const typename QuantityTraits<T>::RawType& )
  {
    return Utility::EqualityComparisonPolicy::compare( left_value, right_value );
  }
};
  
} // end Details namespace

// Get the comparison operator name
template<typename T>
inline std::string CloseComparisonPolicy::getOperatorName()
{
  return Details::CloseComparisonPolicyHelper<T>::getOperatorName();
}

// Create the comparison details
template<typename T>
inline std::string CloseComparisonPolicy::createComparisonDetails(
                const std::string& left_name,
                const bool report_left_name,
                const T& left_value,
                const std::string& right_name,
                const bool report_right_name,
                const T& right_value,
                const std::string& name_suffix,
                const typename QuantityTraits<T>::RawType& distance_tolerance )
{
  return Details::CloseComparisonPolicyHelper<T>::createComparisonDetails(
                                                          left_name,
                                                          report_left_name,
                                                          left_value,
                                                          right_name,
                                                          report_right_name,
                                                          right_value,
                                                          name_suffix,
                                                          distance_tolerance );
}

// Compare two values
template<typename T>
inline bool CloseComparisonPolicy::compare(
                const T& left_value,
                const T& right_value,
                const typename QuantityTraits<T>::RawType& distance_tolerance )
{
  return Details::CloseComparisonPolicyHelper<T>::compare( left_value,
                                                           right_value,
                                                           distance_tolerance );
}

// Calculate the absolute distance between the two values
/*! \details This method will only compile for floating point types.
 */
template<typename T>
inline typename QuantityTraits<T>::RawType
CloseComparisonPolicy::calculateDistance( const T& left_value,
                                          const T& right_value )
{
  return Details::CloseComparisonPolicyHelper<T>::calculateDistance( left_value, right_value );
}

namespace Details{

//! Relative error comparison policy helper for floating point types
template<typename T, typename Enabled = void>
class RelativeErrorComparisonPolicyHelper
{
  // Typedef for this type
  typedef RelativeErrorComparisonPolicyHelper<T,Enabled> ThisType;

public:

  //! Get the operator name
  static inline std::string getOperatorName()
  { return "~="; }

  //! Create the comparison details
  static std::string createComparisonDetails(
          const std::string& left_name,
          const bool report_left_name,
          const T& left_value,
          const std::string& right_name,
          const bool report_right_name,
          const T& right_value,
          const std::string& name_suffix,
          const typename QuantityTraits<T>::RawType& relative_error_tolerance )
  {
    std::ostringstream oss;

    if( report_left_name || report_right_name )
    {
      oss << "relErr(";
      
      if( report_left_name )
      {
        oss << left_name;
        
        if( !name_suffix.empty() )
          oss << name_suffix;
      }
      else
        oss << Utility::toString( left_value );

      oss << ",";
      
      if( report_right_name )
      {
        oss << right_name;
        
        if( !name_suffix.empty() )
          oss << name_suffix;
      }
      else
        oss << Utility::toString( right_value );
      
      oss << ") = ";
    }

    oss << "relErr(" << Utility::toString( left_value )
        << "," << Utility::toString( right_value ) 
        << ") = " << Utility::toString( ThisType::calculateRelativeError( left_value, right_value ) )
        << " <= " << Utility::toString( relative_error_tolerance );

    return oss.str();
  }

  //! Compare two values
  static inline bool compare(
          const T& left_value,
          const T& right_value,
          const typename QuantityTraits<T>::RawType& relative_error_tolerance )
  {
    return ThisType::calculateRelativeError( left_value, right_value ) <=
      relative_error_tolerance;
  }

  //! Compute the relative error
  static inline typename QuantityTraits<T>::RawType calculateRelativeError(
                                                         const T& left_value,
                                                         const T& right_value )
  {
    if( left_value != QuantityTraits<T>::zero() ||
        right_value != QuantityTraits<T>::zero() )
    {
      return Details::AbsoluteValueHelper<T>::abs( left_value - right_value )/
        std::max( Details::AbsoluteValueHelper<T>::abs( left_value ),
                  Details::AbsoluteValueHelper<T>::abs( right_value ) );
    }
    else
      return QuantityTraits<typename QuantityTraits<T>::RawType>::zero();
  }
};

//! Relative error comparison policy helper for all types except floating point types
template<typename T>
class RelativeErrorComparisonPolicyHelper<T,typename std::enable_if<!std::is_floating_point<typename QuantityTraits<T>::RawType>::value>::type>
{
public:

  //! Get the operator name
  static inline std::string getOperatorName()
  { return Utility::EqualityComparisonPolicy::getOperatorName<T>(); }
  
  //! Create the comparison details
  static inline std::string createComparisonDetails(
                                   const std::string& left_name,
                                   const bool report_left_name,
                                   const T& left_value,
                                   const std::string& right_name,
                                   const bool report_right_name,
                                   const T& right_value,
                                   const std::string& name_suffix,
                                   const typename QuantityTraits<T>::RawType& )
  {
    return Utility::EqualityComparisonPolicy::createComparisonDetails(
                                                             left_name,
                                                             report_left_name,
                                                             left_value,
                                                             right_name,
                                                             report_right_name,
                                                             right_value,
                                                             name_suffix );
  }

  //! Compare two values
  static inline bool compare( const T& left_value,
                              const T& right_value,
                              const typename QuantityTraits<T>::RawType& )
  {
    return Utility::EqualityComparisonPolicy::compare( left_value, right_value );
  }
};
  
} // end Details namespace

// Get the comparison operator name
template<typename T>
inline std::string RelativeErrorComparisonPolicy::getOperatorName()
{
  return Details::RelativeErrorComparisonPolicyHelper<T>::getOperatorName();
}

// Create the comparison details
/*! \details For all types except for floating point types the comparison 
 * details will be equivalent to the equality comparison details.
 */
template<typename T>
inline std::string RelativeErrorComparisonPolicy::createComparisonDetails(
          const std::string& left_name,
          const bool report_left_name,
          const T& left_value,
          const std::string& right_name,
          const bool report_right_name,
          const T& right_value,
          const std::string& name_suffix,
          const typename QuantityTraits<T>::RawType& relative_error_tolerance )
{
  return Details::RelativeErrorComparisonPolicyHelper<T>::createComparisonDetails(
                                                    left_name,
                                                    report_left_name,
                                                    left_value,
                                                    right_name,
                                                    report_right_name,
                                                    right_value,
                                                    name_suffix,
                                                    relative_error_tolerance );
}

// Compare two values
/*! \details For all types except for floating point types this comparison will
 * behave like an equality comparison.
 */
template<typename T>
inline bool RelativeErrorComparisonPolicy::compare(
          const T& left_value,
          const T& right_value,
          const typename QuantityTraits<T>::RawType& relative_error_tolerance )
{
  return Details::RelativeErrorComparisonPolicyHelper<T>::compare(
                                                    left_value,
                                                    right_value,
                                                    relative_error_tolerance );
}

// Calculate the relative error
/*! \details This method will only compile for floating point types.
 */
template<typename T>
inline typename QuantityTraits<T>::RawType RelativeErrorComparisonPolicy::calculateRelativeError(
                                                         const T& left_value,
                                                         const T& right_value )
{
  return Details::RelativeErrorComparisonPolicyHelper<T>::calculateRelativeError( left_value, right_value );
}
  
} // end Utility namespace

#endif // end UTILITY_COMPARISON_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_ComparisonPolicy_def.hpp
//---------------------------------------------------------------------------//
