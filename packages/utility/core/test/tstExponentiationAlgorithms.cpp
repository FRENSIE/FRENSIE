//---------------------------------------------------------------------------//
//!
//! \file   tstExponentiationAlgorithms.cpp
//! \author Alex Robinson
//! \brief  Exponentiation algorithm unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/si/length.hpp>

// FRENSIE Includes
#include "Utility_ExponentiationAlgorithms.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Test the recursive exponentiation algorithm
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( Exponentiation, recursive,
				   std::tuple<int,int>,
                                   std::tuple<double,long>,
                                   std::tuple<double,unsigned long long> )
{
  FETCH_TEMPLATE_PARAM( 0, BaseScalarType );
  FETCH_TEMPLATE_PARAM( 1, ExponentOrdinalType );
  
  // Compute 2^30
  BaseScalarType value =
    Utility::Exponentiation::recursive<BaseScalarType,ExponentOrdinalType>(2,
									   30);
  FRENSIE_CHECK_EQUAL( value, 1073741824 );
}

//---------------------------------------------------------------------------//
// Test the static recursive exponentiation algorithm
FRENSIE_UNIT_TEST_TEMPLATE( Exponentiation, recursive_static,
                            double,
                            boost::units::quantity<boost::units::cgs::length>,
                            boost::units::quantity<boost::units::si::length> )
{
  FETCH_TEMPLATE_PARAM( 0, BaseScalarType );
  
  typedef typename Utility::QuantityTraits<BaseScalarType>::template GetQuantityToPowerType<30>::type ReturnType30;
  
  // Compute 2^30
  ReturnType30 value_30 = Utility::Exponentiation::recursive<30>( 2.*Utility::QuantityTraits<BaseScalarType>::one() );

  FRENSIE_CHECK_EQUAL( value_30, Utility::QuantityTraits<ReturnType30>::one()*1073741824. );

  // Compute 2^29
  typedef typename Utility::QuantityTraits<BaseScalarType>::template GetQuantityToPowerType<29>::type ReturnType29;

  ReturnType29 value_29 = Utility::Exponentiation::recursive<29>( 2.*Utility::QuantityTraits<BaseScalarType>::one() );

  FRENSIE_CHECK_EQUAL( value_29, Utility::QuantityTraits<ReturnType29>::one()*536870912. );
}

//---------------------------------------------------------------------------//
// Test the recursive modular exponentiation algorithm
FRENSIE_UNIT_TEST_TEMPLATE( Exponentiation, recursiveMod,
                            unsigned,
                            unsigned long,
                            unsigned long long )
{
  FETCH_TEMPLATE_PARAM( 0, OrdinalType );
  
  // Compute (2^30)mod(3)
  OrdinalType value =
    Utility::Exponentiation::recursiveMod<OrdinalType>(2,30,3);

  FRENSIE_CHECK_EQUAL( value, 1 );

  OrdinalType value2 =
    Utility::Exponentiation::recursiveMod<OrdinalType>(2,15,3);

  FRENSIE_CHECK_EQUAL( value2, 2 );
}

//---------------------------------------------------------------------------//
// end tstExponentiationAlgorithms.cpp
//---------------------------------------------------------------------------//
