//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolationPolicy_def.hpp
//! \author Alex Robinson
//! \brief  Intrepolation policy struct definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATION_POLICY_DEF_HPP
#define UTILITY_INTERPOLATION_POLICY_DEF_HPP

// Std Lib Includes
#include <cmath>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

// Interpolate between two points
template<typename T>
inline T LogLog::interpolate( const T indep_var_0,
			      const T indep_var_1,
			      const T indep_var,
			      const T dep_var_0,
			      const T dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the independent variables are valid
  testPrecondition( indep_var_0 == indep_var_0 );
  testPrecondition( indep_var_1 == indep_var_1 );
  testPrecondition( indep_var == indep_var );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var_0 > 0.0 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( dep_var_0 == dep_var_0 );
  testPrecondition( dep_var_1 == dep_var_1 );
  testPrecondition( dep_var_0 > 0.0 );
  testPrecondition( dep_var_1 > 0.0 );

  return dep_var_0*
    pow((dep_var_1/dep_var_0),
	log(indep_var/indep_var_0)/log(indep_var_1/indep_var_0));
}

// Interpolate between two processed point
template<typename T>
inline T LogLog::interpolate( const T processed_indep_var_0,
			      const T processed_indep_var,
			      const T processed_dep_var_0,
			      const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( processed_indep_var_0 == processed_indep_var_0 );
  testPrecondition( processed_indep_var == processed_indep_var );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( processed_dep_var_0 == processed_dep_var_0 );
  // Make sure that the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf(processed_slope));
  
  return exp( processed_dep_var_0 + 
	      processed_slope*(processed_indep_var - processed_indep_var_0) );
}

// Process the independent value
template<typename T>
inline T LogLog::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( indep_var > 0.0 );
  
  return log( indep_var );
}

// Process the dependent value
template<typename T>
inline T LogLog::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( dep_var > 0.0 );

  return log( dep_var );
}

// Recover the processed independent value
template<typename T>
inline T LogLog::recoverProcessedIndepVar( const T processed_indep_var )
{
  return exp( processed_indep_var );
}
  
// Recover the processed dependent value
template<typename T>
inline T LogLog::recoverProcessedDepVar( const T processed_dep_var )
{
  return exp( processed_dep_var );
}

// The name of the policy
inline const std::string LogLog::name()
{
  return "LogLog";
}

// Interpolate between two points
template<typename T>
inline T LogLin::interpolate( const T indep_var_0,
			      const T indep_var_1,
			      const T indep_var,
			      const T dep_var_0,
			      const T dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( indep_var_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( dep_var_0 == dep_var_0 );
  testPrecondition( dep_var_1 == dep_var_1 );
  testPrecondition( dep_var_0 > 0.0 );
  testPrecondition( dep_var_1 > 0.0 );

  return dep_var_0*pow((dep_var_1/dep_var_0), (indep_var-indep_var_0)/(indep_var_1-indep_var_0));
}

// Interpolate between two processed points
template<typename T>
inline T LogLin::interpolate( const T processed_indep_var_0,
			      const T processed_indep_var,
			      const T processed_dep_var_0,
			      const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( 
						     processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( 
						       processed_indep_var ) );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( processed_dep_var_0 == processed_dep_var_0 );
  
  return exp( processed_dep_var_0 + 
	      processed_slope*(processed_indep_var - processed_indep_var_0) );
}

// Process the independent value
template<typename T>
inline T LogLin::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( indep_var > 0.0 );
  
  return indep_var;
}

// Process the dependent value
template<typename T>
inline T LogLin::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( dep_var > 0.0 );

  return log( dep_var );
}

// Recover the processed independent value
template<typename T>
inline T LogLin::recoverProcessedIndepVar( const T processed_indep_var )
{
  return processed_indep_var;
}
  
// Recover the processed dependent value
template<typename T>
inline T LogLin::recoverProcessedDepVar( const T processed_dep_var )
{
  return exp( processed_dep_var );
}

// The name of the policy
inline const std::string LogLin::name()
{
  return "LogLin";
}

// Interpolate between two points
template<typename T>
inline T LinLog::interpolate( const T indep_var_0,
			      const T indep_var_1,
			      const T indep_var,
			      const T dep_var_0,
			      const T dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the independent variables are valid
  testPrecondition( indep_var_0 == indep_var_0 );
  testPrecondition( indep_var_1 == indep_var_1 );
  testPrecondition( indep_var == indep_var );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var_0 > 0.0 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( dep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( dep_var_1 ) );

  return dep_var_0 + (dep_var_1 - dep_var_0)*log(indep_var/indep_var_0)/
    log(indep_var_1/indep_var_0);
}

// Interpolate between two processed point
template<typename T>
inline T LinLog::interpolate( const T processed_indep_var_0,
			      const T processed_indep_var,
			      const T processed_dep_var_0,
			      const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( processed_indep_var_0 == processed_indep_var_0 );
  testPrecondition( processed_indep_var == processed_indep_var );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( processed_dep_var_0 == processed_dep_var_0 );
  // Make sure the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf(processed_slope));
  
  return processed_dep_var_0 + 
    processed_slope*(processed_indep_var - processed_indep_var_0 );
}

// Process the independent value
template<typename T>
inline T LinLog::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( indep_var > 0.0 );
  
  return log( indep_var );
}

// Process the dependent value
template<typename T>
inline T LinLog::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( dep_var > 0.0 );

  return dep_var;
}

// Recover the processed independent value
template<typename T>
inline T LinLog::recoverProcessedIndepVar( const T processed_indep_var )
{
  return exp( processed_indep_var );
}
  
// Recover the processed dependent value
template<typename T>
inline T LinLog::recoverProcessedDepVar( const T processed_dep_var )
{
  return processed_dep_var;
}

// The name of the policy
inline const std::string LinLog::name()
{
  return "LinLog";
}

// Interpolate between two points
template<typename T>
inline T LinLin::interpolate( const T indep_var_0,
			      const T indep_var_1,
			      const T indep_var,
			      const T dep_var_0,
			      const T dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( indep_var_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( dep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( dep_var_1 ) );

  return dep_var_0 + (dep_var_1 - dep_var_0)/(indep_var_1 - indep_var_0)*
    (indep_var - indep_var_0);
}

// Interpolate between two processed point
template<typename T>
inline T LinLin::interpolate( const T processed_indep_var_0,
			      const T processed_indep_var,
			      const T processed_dep_var_0,
			      const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf(
						     processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf(
						       processed_indep_var ) );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf(
						       processed_dep_var_0 ) );
  // Make sure the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf(processed_slope));
  
  return processed_dep_var_0 + 
    processed_slope*(processed_indep_var - processed_indep_var_0 );
}

// Process the independent value
template<typename T>
inline T LinLin::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( indep_var > 0.0 );
  
  return indep_var;
}

// Process the dependent value
template<typename T>
inline T LinLin::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( dep_var > 0.0 );

  return dep_var;
}

// Recover the processed independent value
template<typename T>
inline T LinLin::recoverProcessedIndepVar( const T processed_indep_var )
{
  return processed_indep_var;
}
  
// Recover the processed dependent value
template<typename T>
inline T LinLin::recoverProcessedDepVar( const T processed_dep_var )
{
  return processed_dep_var;
}

// The name of the policy
inline const std::string LinLin::name()
{
  return "LinLin";
}

} // end Utility namespace

#endif // end UTILITY_INTERPOLATION_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolationPolicy_def.hpp
//---------------------------------------------------------------------------//
