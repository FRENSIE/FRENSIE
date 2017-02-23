//---------------------------------------------------------------------------//
//!
//! \file   Utility_SampleMoment.cpp
//! \author Alex Robinson
//! \brief  The sample moment class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SampleMoment.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_TEMPLATE_CLASS_INST( SampleMoment<1,double> );
EXPLICIT_TEMPLATE_CLASS_INST( SampleMoment<2,double> );
EXPLICIT_TEMPLATE_CLASS_INST( SampleMoment<3,double> );
EXPLICIT_TEMPLATE_CLASS_INST( SampleMoment<4,double> );

EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateMean( const SampleMoment<1,double>&, const size_t ) );
EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateVariance( const SampleMoment<1,double>&, const SampleMoment<2,double>&, const size_t ) );
EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateStdDev( const SampleMoment<1,double>&, const SampleMoment<2,double>&, const size_t ) );
EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateVarianceOfMean( const SampleMoment<1,double>&, const SampleMoment<2,double>&, const size_t ) );
EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateStdDevOfMean( const SampleMoment<1,double>&, const SampleMoment<2,double>&, const size_t ) );
EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateRelativeError( const SampleMoment<1,double>&, const SampleMoment<2,double>&, const size_t ) );
EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateRelativeVOV( const SampleMoment<1,double>&, const SampleMoment<2,double>&, const SampleMoment<3,double>&, const SampleMoment<4,double>&, const size_t ) );
EXPLICIT_TEMPLATE_FUNCTION_INST( double calculateFOM( const double, const double ) );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_SampleMoment.cpp
//---------------------------------------------------------------------------//
