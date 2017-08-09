//---------------------------------------------------------------------------//
//!
//! \file   tstUnitTraits.cpp
//! \author Alex Robinson
//! \brief  Unit traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <type_traits>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/units/systems/cgs/energy.hpp>
#include <boost/units/systems/si/energy.hpp>

// FRENSIE Includes
#include "Utility_UnitTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<cgs::energy,si::energy,ElectronVolt,KiloElectronVolt,MegaElectronVolt> TestTypes;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the unit type is defined
BOOST_AUTO_TEST_CASE( Unit_void )
{
  BOOST_CHECK( (std::is_same<Utility::UnitTraits<void>::Unit,void>::value) );
}

//---------------------------------------------------------------------------//
// Check that the unit type is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( Unit, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::Unit,T>::value) );
}

//---------------------------------------------------------------------------//
// Check that the dimension type is defined
BOOST_AUTO_TEST_CASE( Dimension_void )
{
  BOOST_CHECK( (std::is_same<Utility::UnitTraits<void>::Dimension,void>::value) );
}

//---------------------------------------------------------------------------//
// Check that the dimension type is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( Dimension, T, TestTypes )
{
  BOOST_CHECK( !(std::is_same<typename Utility::UnitTraits<T>::Dimension,void>::value) );
}

//---------------------------------------------------------------------------//
// Check that the system type is defined
BOOST_AUTO_TEST_CASE( System_void )
{
  BOOST_CHECK( (std::is_same<Utility::UnitTraits<void>::System,void>::value) );
}

//---------------------------------------------------------------------------//
// Check that the system type is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( System, T, TestTypes )
{
  BOOST_CHECK( !(std::is_same<typename Utility::UnitTraits<T>::System,void>::value) );
}

//---------------------------------------------------------------------------//
// Check that the inverse unit type is defined
BOOST_AUTO_TEST_CASE( InverseUnit_void )
{
  BOOST_CHECK( (std::is_same<Utility::UnitTraits<void>::InverseUnit,void>::value) );
}

//---------------------------------------------------------------------------//
// Check that the inverse unit type is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( InverseUnit, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::InverseUnit,decltype(T()/(T()*T()))>::value) );
}

//---------------------------------------------------------------------------//
// Check that the unit to the desired power is defined
BOOST_AUTO_TEST_CASE( GetUnitToPowerType_void )
{
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<1>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<2>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<3>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<4>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<5>::type,void>::value) );
  
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<-1>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<-2>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<-3>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<-4>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<-5>::type,void>::value) );
  
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<1,1>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<1,2>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<1,3>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<1,4>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetUnitToPowerType<1,5>::type,void>::value) );
}

//---------------------------------------------------------------------------//
// Check that the unit to the desired power is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( GetUnitToPowerType, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<1>::type,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<2>::type,decltype(T()*T())>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<3>::type,decltype(T()*T()*T())>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<4>::type,decltype(T()*T()*T()*T())>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<5>::type,decltype(T()*T()*T()*T()*T())>::value) );

  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<-1>::type,decltype(T()/(T()*T()))>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<-2>::type,decltype(T()/(T()*T()*T()))>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<-3>::type,decltype(T()/(T()*T()*T()*T()))>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<-4>::type,decltype(T()/(T()*T()*T()*T()*T()))>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<-5>::type,decltype(T()/(T()*T()*T()*T()*T()*T()))>::value) );

  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<1,1>::type,T>::value) );
  BOOST_CHECK( !(std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<1,2>::type,void>::value) );
  BOOST_CHECK( !(std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<1,3>::type,void>::value) );
  BOOST_CHECK( !(std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<1,4>::type,void>::value) );
  BOOST_CHECK( !(std::is_same<typename Utility::UnitTraits<T>::template GetUnitToPowerType<1,5>::type,void>::value) );
}

//---------------------------------------------------------------------------//
// Check that a quantity with the desired base type is defined
BOOST_AUTO_TEST_CASE( GetQuantityType_void )
{
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetQuantityType<void>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetQuantityType<int>::type,int>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetQuantityType<float>::type,float>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetQuantityType<double>::type,double>::value) );
}

//---------------------------------------------------------------------------//
// Check that a quantity with the desired base type is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( GetQuantityType, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetQuantityType<int>::type,boost::units::quantity<T,int> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetQuantityType<float>::type,boost::units::quantity<T,float> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetQuantityType<double>::type,boost::units::quantity<T,double> >::value) );
}

//---------------------------------------------------------------------------//
// Check that a unit type multiplied by another unit type is defined
BOOST_AUTO_TEST_CASE( GetMultipliedUnitType_void )
{
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetMultipliedUnitType<void>::type,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetMultipliedUnitType<int>::type,int>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetMultipliedUnitType<double>::type,double>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetMultipliedUnitType<std::string>::type,std::string>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetMultipliedUnitType<cgs::energy>::type,cgs::energy>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetMultipliedUnitType<si::energy>::type,si::energy>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<void>::template GetMultipliedUnitType<ElectronVolt>::type,ElectronVolt>::value) );
}

//---------------------------------------------------------------------------//
// Check that a unit type multiplied by another unit type is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( GetMultipliedUnitType, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetMultipliedUnitType<void>::type,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetMultipliedUnitType<T>::type,decltype(T()*T())>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::UnitTraits<T>::template GetMultipliedUnitType<decltype(T()/(T()*T()))>::type,decltype(T()/T())>::value) );
}

//---------------------------------------------------------------------------//
// Check that the name of the unit can be returned
BOOST_AUTO_TEST_CASE( name )
{
  BOOST_CHECK_EQUAL( Utility::UnitTraits<void>::name(), "void" );
  BOOST_CHECK_EQUAL( Utility::UnitTraits<cgs::energy>::name(),
                     "centimeter^2 gram second^-2" );
  BOOST_CHECK_EQUAL( Utility::UnitTraits<si::energy>::name(),
                     "meter^2 kilogram second^-2" );
  BOOST_CHECK_EQUAL( Utility::UnitTraits<ElectronVolt>::name(),
                     "electron volt" );
  BOOST_CHECK_EQUAL( Utility::UnitTraits<KiloElectronVolt>::name(),
                     "kiloelectron volt" );
  BOOST_CHECK_EQUAL( Utility::UnitTraits<MegaElectronVolt>::name(),
                     "megaelectron volt" );
}

//---------------------------------------------------------------------------//
// Check that the symbol of the unit can be returned
BOOST_AUTO_TEST_CASE( symbol )
{
  BOOST_CHECK_EQUAL( Utility::UnitTraits<void>::symbol(), "0" );
  BOOST_CHECK_EQUAL( Utility::UnitTraits<cgs::energy>::symbol(),
                     "cm^2 g s^-2" );
  BOOST_CHECK_EQUAL( Utility::UnitTraits<si::energy>::symbol(),
                     "m^2 kg s^-2" );
  BOOST_CHECK_EQUAL( Utility::UnitTraits<ElectronVolt>::symbol(), "eV" );
  BOOST_CHECK_EQUAL( Utility::UnitTraits<KiloElectronVolt>::symbol(), "keV" );
  BOOST_CHECK_EQUAL( Utility::UnitTraits<MegaElectronVolt>::symbol(), "MeV" );
}

//---------------------------------------------------------------------------//
// end tstUnitTraits.cpp
//---------------------------------------------------------------------------//
