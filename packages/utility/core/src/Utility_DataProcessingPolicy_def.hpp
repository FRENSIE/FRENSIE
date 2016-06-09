//---------------------------------------------------------------------------//
//!
//! \file   Utility_DataProcessingPolicy_def.hpp
//! \author Alex Robinson
//! \brief  DataProcessing policy struct definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DATA_PROCESSING_POLICY_DEF_HPP
#define UTILITY_DATA_PROCESSING_POLICY_DEF_HPP

// Std Lib Includes
#include <cmath>

namespace Utility{

/*! \tparam T Any integer or floating point type.
 * \param[in] indep_var The independent variable that will be processed.
 * \return The processed independent variable.
 */
template<typename T>
inline T LogLogDataProcessing::processIndependentVar( const T indep_var )
{
  if( indep_var >= 0 )
    return static_cast<T>( log( static_cast<double>(indep_var) ) );
  else
    return 0;
}

/*! \tparam T Any integer or floating point type.
 * \param[in] dep_var The dependent variable that will be processed.
 * \return The processed dependent variable.
 */
template<typename T>
inline T LogLogDataProcessing::processDependentVar( const T dep_var )
{
  if( dep_var >= 0 )
    return static_cast<T>( log( static_cast<double>(dep_var) ) );
  else
    return 0;
}

/*! \tparam T Any integer or floating point type.
 * \param[in] indep_var The independent variable that will be processed.
 * \return The processed independent variable.
 */
template<typename T>
inline T LogLinDataProcessing::processIndependentVar( const T indep_var )
{
  return indep_var;
}

/*! \tparam T Any integer or floating point type.
 * \param[in] dep_var The dependent variable that will be processed.
 * \return The processed dependent variable.
 */
template<typename T>
inline T LogLinDataProcessing::processDependentVar( const T dep_var )
{
  if( dep_var >= 0 )
    return static_cast<T>( log( static_cast<double>( dep_var) ) );
  else
    return 0;
}

/*! \tparam T Any integer or floating point type.
 * \param[in] indep_var The independent variable that will be processed.
 * \return The processed independent variable.
 */
template<typename T>
inline T LinLogDataProcessing::processIndependentVar( const T indep_var )
{
  if( indep_var >= 0 )
    return static_cast<T>( log( static_cast<double>(indep_var) ) );
  else
    return 0;
}

/*! \tparam T Any integer or floating point type.
 * \param[in] dep_var The dependent variable that will be processed.
 * \return The processed dependent variable.
 */
template<typename T>
inline T LinLogDataProcessing::processDependentVar( const T dep_var )
{
  return dep_var;
}

/*! \tparam T Any integer or floating point type.
 * \param[in] indep_var The independent variable that will be processed.
 * \return The processed independent variable.
 */
template<typename T>
inline T LinLinDataProcessing::processIndependentVar( const T indep_var )
{
  return indep_var;
}

/*! \tparam T Any integer or floating point type.
 * \param[in] dep_var The dependent variable that will be processed.
 * \return The processed dependent variable.
 */
template<typename T>
inline T LinLinDataProcessing::processDependentVar( const T dep_var )
{
  return dep_var;
}

/*! \tparam T Any integer or floating point type.
 * \param[in] indep_var The independent variable that will be processed.
 * \return The processed independent variable.
 */
template<typename T>
inline T SqrSqrDataProcessing::processIndependentVar( const T indep_var )
{
  return indep_var*indep_var;
}

/*! \tparam T Any integer or floating point type.
 * \param[in] dep_var The dependent variable that will be processed.
 * \return The processed dependent variable.
 */
template<typename T>
inline T SqrSqrDataProcessing::processDependentVar( const T dep_var )
{
  return dep_var*dep_var;
}

} // end Utility namespace

#endif // end UTILITY_DATA_PROCESSING_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_DataProcessingPolicy_def.hpp
//---------------------------------------------------------------------------//
