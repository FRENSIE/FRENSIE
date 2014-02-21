//---------------------------------------------------------------------------//
//!
//! \file   DataProcessingPolicy_def.hpp
//! \author Alex Robinson
//! \brief  DataProcessing policy struct definitions
//!
//---------------------------------------------------------------------------//

#ifndef DATA_PROCESSING_POLICY_DEF_HPP
#define DATA_PROCESSING_POLICY_DEF_HPP

// Std Lib Includes
#include <cmath>

namespace FACEMC{

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

} // end FACEMC namespace

#endif // end DATA_PROCESSING_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end DataProcessingPolicy_def.hpp
//---------------------------------------------------------------------------//
