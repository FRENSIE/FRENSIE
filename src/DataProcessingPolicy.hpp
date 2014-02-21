//---------------------------------------------------------------------------//
//!
//! \file   DataProcessingPolicy.hpp
//! \author Alex Robinson
//! \brief  DataProcessing policy struct declarations
//!
//---------------------------------------------------------------------------//

#ifndef DATA_PROCESSING_POLICY_HPP
#define DATA_PROCESSING_POLICY_HPP

namespace FACEMC{

/*! \brief Policy struct for processing data tables that require log-log 
 * interpolation between evaluated points.
 * 
 * This policy class implements the data processing policy interface that is
 * expected by certain protected member functions of the DataProcessor base
 * class. All data processed with this policy will be converted to log-log
 * format.
 * \ingroup policies
 */
struct LogLogDataProcessing
{
  //! Process independent variable
  template<typename T>
  static T processIndependentVar( const T indep_var );
  
  //! Process dependent variable
  template<typename T>
  static T processDependentVar( const T dep_var );  
};

/*! \brief Policy struct for processing data tables that require log-lin 
 * interpolation between evaluated points.
 * 
 * This policy class implements the data processing policy interface that is
 * expected by certain protected member functions of the DataProcessor base
 * class. All data processed with this policy will be converted to log-lin
 * format.
 * \ingroup policies
 */
struct LogLinDataProcessing
{
  //! Process independent variable
  template<typename T>
  static T processIndependentVar( const T indep_var );

  //! Process dependent variable
  template<typename T>
  static T processDependentVar( const T dep_var );
};

/*! \brief Policy struct for processing data tables that require lin-log 
 * interpolation between evaluated points.
 * 
 * This policy class implements the data processing policy interface that is
 * expected by certain protected member functions of the DataProcessor base
 * class. All data processed with this policy will be converted to lin-log
 * format.
 * \ingroup policies
 */
struct LinLogDataProcessing
{
  //! Process independent variable
  template<typename T>
  static T processIndependentVar( const T indep_var );

  //! Process dependent variable
  template<typename T>
  static T processDependentVar( const T dep_var );
};

/*! \brief Policy struct for processing data tables that require lin-lin 
 * interpolation between evaluated points.
 * 
 * This policy class implements the data processing policy interface that is
 * expected by certain protected member functions of the DataProcessor base
 * class. All data processed with this policy will be converted to lin-lin
 * format.
 * \ingroup policies
 */
struct LinLinDataProcessing
{
  //! Process independent variable
  template<typename T>
  static T processIndependentVar( const T indep_var );

  //! Process dependent variable
  template<typename T>
  static T processDependentVar( const T dep_var );
};

/*! \brief Policy struct for processing data tables that require square-square
 * interpolation between data points.
 *
 * This policy class implements the data processing policy interface that is
 * expected by certain protected member functions of the DataProcessor base
 * class. All data processed with this policy will be converted to 
 * square-square format. 
 * \ingroup policies
 */
struct SqrSqrDataProcessing
{
  //! Process independent variable
  template<typename T>
  static T processIndependentVar( const T indep_var );
  
  //! Process dependent variable
  template<typename T>
  static T processDependentVar( const T dep_var );
};
  
} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataProcessingPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_PROCESSING_POLICY_HPP

//---------------------------------------------------------------------------//
// end DataProcessingPolicy.hpp
//---------------------------------------------------------------------------//
