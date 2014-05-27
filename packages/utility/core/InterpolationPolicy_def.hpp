//---------------------------------------------------------------------------//
//!
//! \file   InterpolationPolicy_def.hpp
//! \author Alex Robinson
//! \brief  Intrepolation policy struct definitions
//!
//---------------------------------------------------------------------------//

#ifndef INTERPOLATION_POLICY_DEF_HPP
#define INTERPOLATION_POLICY_DEF_HPP

// Std Lib Includes
#include <cmath>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

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

} // end FACEMC namespace

#endif // end INTERPOLATION_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end InterpolationPolicy_def.hpp
//---------------------------------------------------------------------------//
