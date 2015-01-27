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
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var ) );
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLog::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLog::isDepVarInValidRange( dep_var_1 ) );

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
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						     processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						       processed_indep_var ) );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						       processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_slope ) );
  
  return exp( processed_dep_var_0 + 
	      processed_slope*(processed_indep_var - processed_indep_var_0) );
}

// Interpolate between two points and return the processed value
template<typename T>
inline T LogLog::interpolateAndProcess( const T indep_var_0,
					const T indep_var_1,
					const T indep_var,
					const T dep_var_0,
					const T dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var ) );
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLog::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLog::isDepVarInValidRange( dep_var_1 ) );

  return log( dep_var_0 ) + log ( dep_var_1/dep_var_0 )*
    log( indep_var/indep_var_0 )/log( indep_var_1/indep_var_0 );
}

// Interpolate between two processed points and return the processed value
template<typename T>
inline T LogLog::interpolateAndProcess( const T processed_indep_var_0,
					const T processed_indep_var,
					const T processed_dep_var_0,
					const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						     processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						       processed_indep_var ) );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						       processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_slope ) );
  
  return processed_dep_var_0 + 
    processed_slope*(processed_indep_var - processed_indep_var_0);
}

// Process the independent value
template<typename T>
inline T LogLog::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLog::isIndepVarInValidRange( indep_var ) );
  
  return log( indep_var );
}

// Process the dependent value
template<typename T>
inline T LogLog::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLog::isIndepVarInValidRange( dep_var ) );

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

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogLog::isIndepVarInValidRange( const T indep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var ) );
    
  return indep_var > 0.0;
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogLog::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var ) );
    
  return dep_var > 0.0;
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
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var ) );
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLin::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLin::isDepVarInValidRange( dep_var_1 ) );

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
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						     processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						       processed_indep_var ) );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						       processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_slope ) );
  
  return exp( processed_dep_var_0 + 
	      processed_slope*(processed_indep_var - processed_indep_var_0) );
}

// Interpolate between two points and return the processed value
template<typename T>
inline T LogLin::interpolateAndProcess( const T indep_var_0,
					const T indep_var_1,
					const T indep_var,
					const T dep_var_0,
					const T dep_var_1 )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var ) );
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var_1 ) );
  testPrecondition( LogLin::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LogLin::isDepVarInValidRange( dep_var_1 ) );

  return log( dep_var_0 ) + log( dep_var_1/dep_var_0 )*
    (indep_var-indep_var_0)/(indep_var_1-indep_var_0);
}

// Interpolate between two processed points and return the processed value
template<typename T>
inline T LogLin::interpolateAndProcess( const T processed_indep_var_0,
					const T processed_indep_var,
					const T processed_dep_var_0,
					const T processed_slope )
{
  // T must be a floating point type
  testStaticPrecondition( (boost::is_floating_point<T>::value) );
  // Make sure the processed independent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						     processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						       processed_indep_var ) );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						       processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_slope ) );
  
  return processed_dep_var_0 + 
    processed_slope*(processed_indep_var - processed_indep_var_0);
}

// Process the independent value
template<typename T>
inline T LogLin::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLin::isIndepVarInValidRange( indep_var ) );
  
  return indep_var;
}

// Process the dependent value
template<typename T>
inline T LogLin::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LogLin::isDepVarInValidRange( dep_var ) );

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

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogLin::isIndepVarInValidRange( const T indep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var ) );
    
  return true;
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LogLin::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var ) );
    
  return dep_var > 0.0;
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
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var ) );
  testPrecondition( LinLog::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LinLog::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LinLog::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var_1 ) );
  testPrecondition( LinLog::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LinLog::isDepVarInValidRange( dep_var_1 ) );

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
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						     processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						       processed_indep_var ) );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						       processed_dep_var_0 ) );
  // Make sure that the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( processed_slope ) );
  
  return processed_dep_var_0 + 
    processed_slope*(processed_indep_var - processed_indep_var_0 );
}

// Interpolate between two points and return the processed value
template<typename T>
inline T LinLog::interpolateAndProcess( const T indep_var_0,
					const T indep_var_1,
					const T indep_var,
					const T dep_var_0,
					const T dep_var_1 )
{
  return interpolate( indep_var_0, 
		      indep_var_1, 
		      indep_var, 
		      dep_var_0, 
		      dep_var_1 );
}

// Interpolate between two processed points and return the processed value
template<typename T>
inline T LinLog::interpolateAndProcess( const T processed_indep_var_0,
					const T processed_indep_var,
					const T processed_dep_var_0,
					const T processed_slope )
{  
  return interpolate( processed_indep_var_0,
		      processed_indep_var,
		      processed_dep_var_0,
		      processed_slope );
}

// Process the independent value
template<typename T>
inline T LinLog::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLog::isIndepVarInValidRange( indep_var ) );
  
  return log( indep_var );
}

// Process the dependent value
template<typename T>
inline T LinLog::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLog::isDepVarInValidRange( dep_var ) );

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

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LinLog::isIndepVarInValidRange( const T indep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var ) );
    
  return indep_var > 0.0;
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LinLog::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var ) );
    
  return true;
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
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var_1 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var ) );
  testPrecondition( LinLin::isIndepVarInValidRange( indep_var_0 ) );
  testPrecondition( LinLin::isIndepVarInValidRange( indep_var_1 ) );
  testPrecondition( LinLin::isIndepVarInValidRange( indep_var ) );
  testPrecondition( indep_var_0 < indep_var_1 );
  testPrecondition( indep_var >= indep_var_0 );
  testPrecondition( indep_var <= indep_var_1 );
  // Make sure the dependent variables are valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var_1 ) );
  testPrecondition( LinLin::isDepVarInValidRange( dep_var_0 ) );
  testPrecondition( LinLin::isDepVarInValidRange( dep_var_1 ) );

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
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						     processed_indep_var_0 ) );
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						       processed_indep_var ) );
  testPrecondition( processed_indep_var_0 <= processed_indep_var );
  // Make sure the processed dependent variable is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(
						       processed_dep_var_0 ) );
  // Make sure the slope is valid
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf(processed_slope));
  
  return processed_dep_var_0 + 
    processed_slope*(processed_indep_var - processed_indep_var_0 );
}

// Interpolate between two points and return the processed value
template<typename T>
inline T LinLin::interpolateAndProcess( const T indep_var_0,
					const T indep_var_1,
					const T indep_var,
					const T dep_var_0,
					const T dep_var_1 )
{
  return interpolate( indep_var_0,
		      indep_var_1,
		      indep_var,
		      dep_var_0,
		      dep_var_1 );
}

// Interpolate between two processed points and return the processed value
template<typename T>
inline T LinLin::interpolateAndProcess( const T processed_indep_var_0,
					const T processed_indep_var,
					const T processed_dep_var_0,
					const T processed_slope )
{
  return interpolate( processed_indep_var_0,
		      processed_indep_var,
		      processed_dep_var_0,
		      processed_slope );
}

// Process the independent value
template<typename T>
inline T LinLin::processIndepVar( const T indep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLin::isIndepVarInValidRange( indep_var  ) );
  
  return indep_var;
}

// Process the dependent value
template<typename T>
inline T LinLin::processDepVar( const T dep_var )
{
  // Make sure the indep var value is valid
  testPrecondition( LinLin::isIndepVarInValidRange( dep_var ) );

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

// Test if the independent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LinLin::isIndepVarInValidRange( const T indep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( indep_var ) );
    
  return true;
}

// Test if the dependent value is in a valid range (doesn't check nan/inf)
template<typename T>
inline bool LinLin::isDepVarInValidRange( const T dep_var )
{
  // Make sure the indep var is not inf or nan
  testPrecondition( !Teuchos::ScalarTraits<T>::isnaninf( dep_var ) );
    
  return true;
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
