//---------------------------------------------------------------------------//
//!
//! \file   tstQuantityTraits.cpp
//! \author Alex Robinson
//! \brief  Quantity traits unit tests
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
#include <boost/mpl/insert_range.hpp>
#include <boost/units/systems/cgs/energy.hpp>
#include <boost/units/systems/si/energy.hpp>

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"

using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<float,double> TestFloatingPointTypes;

typedef boost::mpl::list<int, unsigned long, float, double> TestTypes;

template<typename Unit, typename RawTypeWrapper = void>
struct QuantityTypeList
{
  typedef boost::mpl::list<boost::units::quantity<Unit,float>, boost::units::quantity<Unit,double> > BasicFloatingPointQuantityTypes;
  
  typedef boost::mpl::list<boost::units::quantity<Unit,int>, boost::units::quantity<Unit,unsigned long>, boost::units::quantity<Unit,float>, boost::units::quantity<Unit,double> > BasicQuantityTypes;

  typedef boost::mpl::list<boost::units::quantity<Unit,std::complex<int> >, boost::units::quantity<Unit,std::complex<unsigned long> >, boost::units::quantity<Unit,std::complex<float> >, boost::units::quantity<Unit,std::complex<double> > > ComplexQuantityTypes;

  typedef typename boost::mpl::insert_range<BasicQuantityTypes, typename boost::mpl::end<BasicQuantityTypes>::type,ComplexQuantityTypes>::type type;
};

template<typename... TypeLists>
struct MergeTypeLists
{ /* ... */ };

template<typename FrontList, typename... TypeLists>
struct MergeTypeLists<FrontList,TypeLists...>
{
private:
  typedef typename MergeTypeLists<TypeLists...>::type BackMergedListType;

public:
  typedef typename boost::mpl::insert_range<FrontList,typename boost::mpl::end<FrontList>::type,BackMergedListType>::type type;
};

template<typename FrontList>
struct MergeTypeLists<FrontList>
{ 
  typedef FrontList type;
};

typedef typename MergeTypeLists<typename QuantityTypeList<cgs::energy>::BasicFloatingPointQuantityTypes, typename QuantityTypeList<si::energy>::BasicFloatingPointQuantityTypes, typename QuantityTypeList<ElectronVolt>::BasicFloatingPointQuantityTypes, typename QuantityTypeList<KiloElectronVolt>::BasicFloatingPointQuantityTypes>::type TestBasicFloatingPointQuantityTypes;

typedef typename MergeTypeLists<typename QuantityTypeList<cgs::energy>::BasicQuantityTypes, typename QuantityTypeList<si::energy>::BasicQuantityTypes, typename QuantityTypeList<ElectronVolt>::BasicQuantityTypes, typename QuantityTypeList<KiloElectronVolt>::BasicQuantityTypes>::type TestBasicQuantityTypes;

typedef typename MergeTypeLists<typename QuantityTypeList<cgs::energy>::ComplexQuantityTypes, typename QuantityTypeList<si::energy>::ComplexQuantityTypes, typename QuantityTypeList<ElectronVolt>::ComplexQuantityTypes, typename QuantityTypeList<KiloElectronVolt>::ComplexQuantityTypes>::type TestComplexQuantityTypes;

typedef typename MergeTypeLists<typename QuantityTypeList<cgs::energy>::type, typename QuantityTypeList<si::energy>::type, typename QuantityTypeList<ElectronVolt>::type, typename QuantityTypeList<KiloElectronVolt>::type>::type TestQuantityTypes;

//---------------------------------------------------------------------------//
// Check that UnitType is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( UnitType, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::UnitType,void>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::UnitType,void>::value) );
  
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::UnitType,cgs::energy>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::UnitType,si::energy>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::UnitType,ElectronVolt>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::UnitType,KiloElectronVolt>::value) );

  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::UnitType,cgs::energy>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::UnitType,si::energy>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::UnitType,ElectronVolt>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::UnitType,KiloElectronVolt>::value) );
}

//---------------------------------------------------------------------------//
// Check that RawType is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( RawType, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::RawType,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::RawType,std::complex<T> >::value) );
  
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::RawType,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::RawType,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::RawType,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::RawType,T>::value) );

  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::RawType,std::complex<T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::RawType,std::complex<T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::RawType,std::complex<T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::RawType,std::complex<T> >::value) );
}

//---------------------------------------------------------------------------//
// Check that RawFloatingPointType is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( RawFloatingPointType, T, TestTypes )
{
  if( std::is_floating_point<T>::value )
  {
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::RawFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType,std::complex<T> >::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::RawFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::RawFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::RawFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::RawFloatingPointType,T>::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::RawFloatingPointType,std::complex<T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::RawFloatingPointType,std::complex<T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::RawFloatingPointType,std::complex<T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::RawFloatingPointType,std::complex<T> >::value) );
  }
  else
  {
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::RawFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType,std::complex<double> >::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::RawFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::RawFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::RawFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::RawFloatingPointType,double>::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::RawFloatingPointType,std::complex<double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::RawFloatingPointType,std::complex<double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::RawFloatingPointType,std::complex<double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::RawFloatingPointType,std::complex<double> >::value) );
  }
}

//---------------------------------------------------------------------------//
// Check that RealRawFloatingPointType is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( RealRawFloatingPointType, T, TestTypes )
{
  if( std::is_floating_point<T>::value )
  {
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::RealRawFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::RealRawFloatingPointType,T>::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::RealRawFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::RealRawFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::RealRawFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::RealRawFloatingPointType,T>::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::RealRawFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::RealRawFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::RealRawFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::RealRawFloatingPointType,T>::value) );
  }
  else
  {
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::RealRawFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::RealRawFloatingPointType,double>::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::RealRawFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::RealRawFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::RealRawFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::RealRawFloatingPointType,double>::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::RealRawFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::RealRawFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::RealRawFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::RealRawFloatingPointType,double>::value) );
  }
}

//---------------------------------------------------------------------------//
// Check that QuantityType is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( QuantityType, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::QuantityType,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::QuantityType,std::complex<T> >::value) );

  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::QuantityType,boost::units::quantity<cgs::energy,T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::QuantityType,boost::units::quantity<si::energy,T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::QuantityType,boost::units::quantity<ElectronVolt,T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::QuantityType,boost::units::quantity<KiloElectronVolt,T> >::value) );

  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::QuantityType,boost::units::quantity<cgs::energy,std::complex<T> > >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::QuantityType,boost::units::quantity<si::energy,std::complex<T> > >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::QuantityType,boost::units::quantity<ElectronVolt,std::complex<T> > >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::QuantityType,boost::units::quantity<KiloElectronVolt,std::complex<T> > >::value) );
}

//---------------------------------------------------------------------------//
// Check that FloatingQuantityType is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( FloatingPointQuantityType, T, TestTypes )
{
  if( std::is_floating_point<T>::value )
  {
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::FloatingPointQuantityType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::FloatingPointQuantityType,std::complex<T> >::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::FloatingPointQuantityType,boost::units::quantity<cgs::energy,T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::FloatingPointQuantityType,boost::units::quantity<si::energy,T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::FloatingPointQuantityType,boost::units::quantity<ElectronVolt,T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::FloatingPointQuantityType,boost::units::quantity<KiloElectronVolt,T> >::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::FloatingPointQuantityType,boost::units::quantity<cgs::energy,std::complex<T> > >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::FloatingPointQuantityType,boost::units::quantity<si::energy,std::complex<T> > >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::FloatingPointQuantityType,boost::units::quantity<ElectronVolt,std::complex<T> > >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::FloatingPointQuantityType,boost::units::quantity<KiloElectronVolt,std::complex<T> > >::value) );
  }
  else
  {
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::FloatingPointQuantityType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::FloatingPointQuantityType,std::complex<double> >::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::FloatingPointQuantityType,boost::units::quantity<cgs::energy,double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::FloatingPointQuantityType,boost::units::quantity<si::energy,double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::FloatingPointQuantityType,boost::units::quantity<ElectronVolt,double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::FloatingPointQuantityType,boost::units::quantity<KiloElectronVolt,double> >::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::FloatingPointQuantityType,boost::units::quantity<cgs::energy,std::complex<double> > >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::FloatingPointQuantityType,boost::units::quantity<si::energy,std::complex<double> > >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::FloatingPointQuantityType,boost::units::quantity<ElectronVolt,std::complex<double> > >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::FloatingPointQuantityType,boost::units::quantity<KiloElectronVolt,std::complex<double> > >::value) );
  }
}

//---------------------------------------------------------------------------//
// Check that RealFloatingQuantityType is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( RealFloatingPointQuantityType, T, TestTypes )
{
  if( std::is_floating_point<T>::value )
  {
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::RealFloatingPointQuantityType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::RealFloatingPointQuantityType,T>::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::RealFloatingPointQuantityType,boost::units::quantity<cgs::energy,T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::RealFloatingPointQuantityType,boost::units::quantity<si::energy,T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::RealFloatingPointQuantityType,boost::units::quantity<ElectronVolt,T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::RealFloatingPointQuantityType,boost::units::quantity<KiloElectronVolt,T> >::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::RealFloatingPointQuantityType,boost::units::quantity<cgs::energy,T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::RealFloatingPointQuantityType,boost::units::quantity<si::energy,T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::RealFloatingPointQuantityType,boost::units::quantity<ElectronVolt,T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::RealFloatingPointQuantityType,boost::units::quantity<KiloElectronVolt,T> >::value) );
  }
  else
  {
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::RealFloatingPointQuantityType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::RealFloatingPointQuantityType,double>::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::RealFloatingPointQuantityType,boost::units::quantity<cgs::energy,double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::RealFloatingPointQuantityType,boost::units::quantity<si::energy,double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::RealFloatingPointQuantityType,boost::units::quantity<ElectronVolt,double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::RealFloatingPointQuantityType,boost::units::quantity<KiloElectronVolt,double> >::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::RealFloatingPointQuantityType,boost::units::quantity<cgs::energy,double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::RealFloatingPointQuantityType,boost::units::quantity<si::energy,double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::RealFloatingPointQuantityType,boost::units::quantity<ElectronVolt,double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::RealFloatingPointQuantityType,boost::units::quantity<KiloElectronVolt,double> >::value) );
  }
}

//---------------------------------------------------------------------------//
// Check that the quantity type raised to the desired rational power is
// defined
BOOST_AUTO_TEST_CASE_TEMPLATE( GetQuantityToPowerType_basic, T, TestTypes )
{
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<1>::type,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<2>::type,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<3>::type,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<1,1>::type,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<1,2>::type,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<1,3>::type,T>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<3,2>::type,T>::value) );
  
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<1>::type,std::complex<T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<2>::type,std::complex<T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<3>::type,std::complex<T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<1,1>::type,std::complex<T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<1,2>::type,std::complex<T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<1,3>::type,std::complex<T> >::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<3,2>::type,std::complex<T> >::value) );

  if( std::is_floating_point<T>::value )
  {
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<1>::AsFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<2>::AsFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<3>::AsFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<1,1>::AsFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<1,2>::AsFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<1,3>::AsFloatingPointType,T>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<3,2>::AsFloatingPointType,T>::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<1>::AsFloatingPointType,std::complex<T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<2>::AsFloatingPointType,std::complex<T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<3>::AsFloatingPointType,std::complex<T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<1,1>::AsFloatingPointType,std::complex<T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<1,2>::AsFloatingPointType,std::complex<T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<1,3>::AsFloatingPointType,std::complex<T> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<3,2>::AsFloatingPointType,std::complex<T> >::value) );
  }
  else
  {
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<1>::AsFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<2>::AsFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<3>::AsFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<1,1>::AsFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<1,2>::AsFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<1,3>::AsFloatingPointType,double>::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<T>::template GetQuantityToPowerType<3,2>::AsFloatingPointType,double>::value) );
    
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<1>::AsFloatingPointType,std::complex<double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<2>::AsFloatingPointType,std::complex<double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<3>::AsFloatingPointType,std::complex<double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<1,1>::AsFloatingPointType,std::complex<double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<1,2>::AsFloatingPointType,std::complex<double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<1,3>::AsFloatingPointType,std::complex<double> >::value) );
    BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<std::complex<T> >::template GetQuantityToPowerType<3,2>::AsFloatingPointType,std::complex<double> >::value) );
  }
}

//---------------------------------------------------------------------------//
// Check that the quantity type raised to the desired rational power is
// defined
BOOST_AUTO_TEST_CASE_TEMPLATE( GetQuantityToPowerType,
                               QuantityType,
                               TestQuantityTypes )
{
  // Power = 0
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<0>::type,typename Utility::QuantityTraits<QuantityType>::RawType>::value) );
  
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<0>::AsFloatingPointType,typename Utility::QuantityTraits<QuantityType>::RawFloatingPointType>::value) );

  // Power = 1
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1>::type,QuantityType>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,1>::type,QuantityType>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,-1>::type,QuantityType>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,2>::type,QuantityType>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,-2>::type,QuantityType>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,3>::type,QuantityType>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,-3>::type,QuantityType>::value) );

  typedef typename Utility::QuantityTraits<QuantityType>::FloatingPointQuantityType FloatingPointQuantityType;
    
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1>::AsFloatingPointType,FloatingPointQuantityType>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,1>::AsFloatingPointType,FloatingPointQuantityType>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,-1>::AsFloatingPointType,FloatingPointQuantityType>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,2>::AsFloatingPointType,FloatingPointQuantityType>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,-2>::AsFloatingPointType,FloatingPointQuantityType>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,3>::AsFloatingPointType,FloatingPointQuantityType>::value) );
  BOOST_CHECK( (std::is_same<typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,-3>::AsFloatingPointType,FloatingPointQuantityType>::value) );

  // Power = 2
  BOOST_CHECK_EQUAL( typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2>::type(),
                     QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,1>::type()),
                     QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,-1>::type()),
                     QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<4,2>::type()),
                     QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-4,-2>::type()),
                     QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<6,3>::type()),
                     QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-6,-3>::type()),
                     QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<8,4>::type()),
                     QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-8,-4>::type()),
                     QuantityType()*QuantityType() );

  BOOST_CHECK_EQUAL( typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2>::AsFloatingPointType(),
                     FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,1>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,-1>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<4,2>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-4,-2>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<6,3>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-6,-3>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<8,4>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-8,-4>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType() );

  // Power = 3
  BOOST_CHECK_EQUAL( typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3>::type(),
                     QuantityType()*QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,1>::type()),
                     QuantityType()*QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,-1>::type()),
                     QuantityType()*QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<6,2>::type()),
                     QuantityType()*QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-6,-2>::type()),
                     QuantityType()*QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<9,3>::type()),
                     QuantityType()*QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-9,-3>::type()),
                     QuantityType()*QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<12,4>::type()),
                     QuantityType()*QuantityType()*QuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-12,-4>::type()),
                     QuantityType()*QuantityType()*QuantityType() );

  BOOST_CHECK_EQUAL( typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3>::AsFloatingPointType(),
                     FloatingPointQuantityType()*FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,1>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,-1>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<6,2>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-6,-2>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<9,3>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-9,-3>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<12,4>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType()*FloatingPointQuantityType() );
  BOOST_CHECK_EQUAL( (typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-12,-4>::AsFloatingPointType()),
                     FloatingPointQuantityType()*FloatingPointQuantityType()*FloatingPointQuantityType() );

  // Power = -1
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1>::type::from_value(1),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,1>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,-1>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,2>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,-2>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1>::AsFloatingPointType::from_value(1),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,1>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,-1>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,2>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,-2>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );

  // Power = -2
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2>::type::from_value(1),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,1>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,-1>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-4,2>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<4,-2>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2>::AsFloatingPointType::from_value(1),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,1>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,-1>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-4,2>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<4,-2>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );

  // Power = -3
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3>::type::from_value(1),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,1>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,-1>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-6,2>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<6,-2>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3>::AsFloatingPointType::from_value(1),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,1>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,-1>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-6,2>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<6,-2>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );

  // Power = 1/2
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,2>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,-2>::type::from_value(1)),
                     QuantityType::from_value(1) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,4>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,-4>::type::from_value(1)),
                     QuantityType::from_value(1) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,6>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,-6>::type::from_value(1)),
                     QuantityType::from_value(1) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,2>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,-2>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,4>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,-4>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,6>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,-6>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1) );

  // Power = 1/3
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,3>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,-3>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,-3>::type::from_value(1)),
                     QuantityType::from_value(1) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,6>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,-6>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,-6>::type::from_value(1)),
                     QuantityType::from_value(1) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,9>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,-9>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,-9>::type::from_value(1)),
                     QuantityType::from_value(1) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,3>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,-3>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,-3>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,6>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,-6>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,-6>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,9>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,-9>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,-9>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1) );

  // Power = 3/2
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,2>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,-2>::type::from_value(1)),
                     QuantityType::from_value(1)*
                     QuantityType::from_value(1)*
                     QuantityType::from_value(1) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<6,4>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-6,-4>::type::from_value(1)),
                     QuantityType::from_value(1)*
                     QuantityType::from_value(1)*
                     QuantityType::from_value(1) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<9,6>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-9,-6>::type::from_value(1)),
                     QuantityType::from_value(1)*
                     QuantityType::from_value(1)*
                     QuantityType::from_value(1) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,2>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,-2>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)*
                     FloatingPointQuantityType::from_value(1)*
                     FloatingPointQuantityType::from_value(1) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<6,4>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-6,-4>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)*
                     FloatingPointQuantityType::from_value(1)*
                     FloatingPointQuantityType::from_value(1) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<9,6>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-9,-6>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)*
                     FloatingPointQuantityType::from_value(1)*
                     FloatingPointQuantityType::from_value(1) );

  // Power = -1/2
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,2>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,-2>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,4>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,-4>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,6>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,-6>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,2>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,-2>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,4>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,-4>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,6>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,-6>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );

  // Power = -1/3
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,3>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,-3>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,-3>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,6>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,-6>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,-6>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,9>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,-9>::type::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,-9>::type::from_value(1)),
                     QuantityType::from_value(1)/
                     (QuantityType::from_value(1)*
                      QuantityType::from_value(1)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-1,3>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,-3>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,-3>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-2,6>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,-6>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<2,-6>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<-3,9>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,-9>::AsFloatingPointType::from_value(1)*
                      Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<3,-9>::AsFloatingPointType::from_value(1)),
                     FloatingPointQuantityType::from_value(1)/
                     (FloatingPointQuantityType::from_value(1)*
                      FloatingPointQuantityType::from_value(1)) );
}

//---------------------------------------------------------------------------//
// Check that the QuantityTraits struct has been specialized for the type
BOOST_AUTO_TEST_CASE_TEMPLATE( is_specialized, T, TestTypes )
{
  BOOST_CHECK( Utility::QuantityTraits<T>::is_specialized::value );
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::is_specialized::value );
  
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_specialized::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_specialized::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_specialized::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::is_specialized::value) );

  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_specialized::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_specialized::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_specialized::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::is_specialized::value) );
}

//---------------------------------------------------------------------------//
// Check if the type is signed
BOOST_AUTO_TEST_CASE_TEMPLATE( is_signed, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::is_signed::value,
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::is_signed::value,
                     std::is_signed<T>::value );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_signed::value),
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_signed::value),
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_signed::value),
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::is_signed::value),
                     std::is_signed<T>::value );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_signed::value),
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_signed::value),
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_signed::value),
                     std::is_signed<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::is_signed::value),
                     std::is_signed<T>::value );
}

//---------------------------------------------------------------------------//
// Check if the type is an integer
BOOST_AUTO_TEST_CASE_TEMPLATE( is_integer, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::is_integer::value,
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::is_integer::value,
                     std::is_integral<T>::value );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_integer::value),
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_integer::value),
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_integer::value),
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::is_integer::value),
                     std::is_integral<T>::value );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_integer::value),
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_integer::value),
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_integer::value),
                     std::is_integral<T>::value );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::is_integer::value),
                     std::is_integral<T>::value );
}

//---------------------------------------------------------------------------//
// Check if the type is complex
BOOST_AUTO_TEST_CASE_TEMPLATE( is_complex, T, TestTypes )
{
  BOOST_CHECK( !Utility::QuantityTraits<T>::is_complex::value );
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::is_complex::value );

  BOOST_CHECK( !(Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_complex::value) );
  BOOST_CHECK( !(Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_complex::value) );
  BOOST_CHECK( !(Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_complex::value) );
  BOOST_CHECK( !(Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::is_complex::value) );

  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_complex::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_complex::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_complex::value) );
  BOOST_CHECK( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::is_complex::value) );
}

//---------------------------------------------------------------------------//
// Check if the type uses exact representations
BOOST_AUTO_TEST_CASE_TEMPLATE( is_exact, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::is_exact::value,
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::is_exact::value,
                     std::numeric_limits<T>::is_exact );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::is_exact::value),
                     std::numeric_limits<T>::is_exact );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::is_exact::value),
                     std::numeric_limits<T>::is_exact );
}

//---------------------------------------------------------------------------//
// Check if the type has a representation for positive infinity
BOOST_AUTO_TEST_CASE_TEMPLATE( has_infinity, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::has_infinity::value,
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::has_infinity::value,
                     std::numeric_limits<T>::has_infinity );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,T> >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<KiloElectronVolt,std::complex<T> > >::has_infinity::value),
                     std::numeric_limits<T>::has_infinity );
}

//---------------------------------------------------------------------------//
// Check if the type has a representation for quiet nan
BOOST_AUTO_TEST_CASE_TEMPLATE( has_quiet_nan, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::has_quiet_nan::value,
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::has_quiet_nan::value,
                     std::numeric_limits<T>::has_quiet_NaN );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::has_quiet_nan::value),
                     std::numeric_limits<T>::has_quiet_NaN );  
}

//---------------------------------------------------------------------------//
// Check if the type has a representation for signaling nan
BOOST_AUTO_TEST_CASE_TEMPLATE( has_signaling_nan, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::has_signaling_nan::value,
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::has_signaling_nan::value,
                     std::numeric_limits<T>::has_signaling_NaN );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::has_signaling_nan::value),
                     std::numeric_limits<T>::has_signaling_NaN );
}

//---------------------------------------------------------------------------//
// Check if the type allows denormalizing values
BOOST_AUTO_TEST_CASE_TEMPLATE( has_denorm, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::has_denorm::value,
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::has_denorm::value,
                     std::numeric_limits<T>::has_denorm );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::has_denorm::value),
                     std::numeric_limits<T>::has_denorm );
}

//---------------------------------------------------------------------------//
// Check if the type detects a loss of accuracy as a denormalization loss
// instead of an inexact result
BOOST_AUTO_TEST_CASE_TEMPLATE( has_denorm_loss, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::has_denorm_loss::value,
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::has_denorm_loss::value,
                     std::numeric_limits<T>::has_denorm_loss );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::has_denorm_loss::value),
                     std::numeric_limits<T>::has_denorm_loss );
}

//---------------------------------------------------------------------------//
// Check if the type adheres to the IEC-559/IEEE-754 standard
BOOST_AUTO_TEST_CASE_TEMPLATE( is_iec559, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::is_iec559::value,
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::is_iec559::value,
                     std::numeric_limits<T>::is_iec559 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::is_iec559::value),
                     std::numeric_limits<T>::is_iec559 );
}

//---------------------------------------------------------------------------//
// Check if the set of values that the type can represent is bounded
BOOST_AUTO_TEST_CASE_TEMPLATE( is_bounded, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::is_bounded::value,
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::is_bounded::value,
                     std::numeric_limits<T>::is_bounded );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::is_bounded::value),
                     std::numeric_limits<T>::is_bounded );
}

//---------------------------------------------------------------------------//
// Check if the type is modulo
BOOST_AUTO_TEST_CASE_TEMPLATE( is_modulo, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::is_modulo::value,
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::is_modulo::value,
                     std::numeric_limits<T>::is_modulo );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::is_modulo::value),
                     std::numeric_limits<T>::is_modulo );
}

//---------------------------------------------------------------------------//
// Check if trapping is implemented for the type
BOOST_AUTO_TEST_CASE_TEMPLATE( traps, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::traps::value,
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::traps::value,
                     std::numeric_limits<T>::traps );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::traps::value),
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::traps::value),
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::traps::value),
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::traps::value),
                     std::numeric_limits<T>::traps );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::traps::value),
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::traps::value),
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::traps::value),
                     std::numeric_limits<T>::traps );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::traps::value),
                     std::numeric_limits<T>::traps );
}

//---------------------------------------------------------------------------//
// Check if the type checks the tinyness before rounding
BOOST_AUTO_TEST_CASE_TEMPLATE( tinyness_before, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::tinyness_before::value,
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::tinyness_before::value,
                     std::numeric_limits<T>::tinyness_before );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::tinyness_before::value),
                     std::numeric_limits<T>::tinyness_before );
}

//---------------------------------------------------------------------------//
// Check if the rounding style for the type is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( round_style, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::round_style::value,
                     std::numeric_limits<T>::round_style );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::round_style::value,
                     std::numeric_limits<T>::round_style );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::round_style::value),
                     std::numeric_limits<T>::round_style );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::round_style::value),
                     std::numeric_limits<T>::round_style );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::round_style::value),
                     std::numeric_limits<T>::round_style );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::round_style::value),
                     std::numeric_limits<T>::round_style );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::round_style::value),
                     std::numeric_limits<T>::round_style );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::round_style::value),
                     std::numeric_limits<T>::round_style );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::round_style::value),
                     std::numeric_limits<T>::round_style );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::round_style::value),
                     std::numeric_limits<T>::round_style );
}

//---------------------------------------------------------------------------//
// Check if the number of non-sign bits for the type is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( digits, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::digits::value,
                     std::numeric_limits<T>::digits );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::digits::value,
                     std::numeric_limits<T>::digits );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::digits::value),
                     std::numeric_limits<T>::digits );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::digits::value),
                     std::numeric_limits<T>::digits );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::digits::value),
                     std::numeric_limits<T>::digits );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::digits::value),
                     std::numeric_limits<T>::digits );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::digits::value),
                     std::numeric_limits<T>::digits );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::digits::value),
                     std::numeric_limits<T>::digits );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::digits::value),
                     std::numeric_limits<T>::digits );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::digits::value),
                     std::numeric_limits<T>::digits );
}

//---------------------------------------------------------------------------//
// Check if the number of digits (in decimal base) that can be represented by
// the type is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( digits10, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::digits10::value,
                     std::numeric_limits<T>::digits10 );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::digits10::value,
                     std::numeric_limits<T>::digits10 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::digits10::value),
                     std::numeric_limits<T>::digits10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::digits10::value),
                     std::numeric_limits<T>::digits10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::digits10::value),
                     std::numeric_limits<T>::digits10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::digits10::value),
                     std::numeric_limits<T>::digits10 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::digits10::value),
                     std::numeric_limits<T>::digits10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::digits10::value),
                     std::numeric_limits<T>::digits10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::digits10::value),
                     std::numeric_limits<T>::digits10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::digits10::value),
                     std::numeric_limits<T>::digits10 );
}

//---------------------------------------------------------------------------//
// Check if the number of digits (in decimal base) required to ensure that
// values that differ are always differentiated by the type is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( max_digits10, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::max_digits10::value,
                     std::numeric_limits<T>::max_digits10 );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::max_digits10::value,
                     std::numeric_limits<T>::max_digits10 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::max_digits10::value),
                     std::numeric_limits<T>::max_digits10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::max_digits10::value),
                     std::numeric_limits<T>::max_digits10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::max_digits10::value),
                     std::numeric_limits<T>::max_digits10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::max_digits10::value),
                     std::numeric_limits<T>::max_digits10 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::max_digits10::value),
                     std::numeric_limits<T>::max_digits10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::max_digits10::value),
                     std::numeric_limits<T>::max_digits10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::max_digits10::value),
                     std::numeric_limits<T>::max_digits10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::max_digits10::value),
                     std::numeric_limits<T>::max_digits10 );
}

//---------------------------------------------------------------------------//
// Check that the base of the type is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( radix, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::radix::value,
                     std::numeric_limits<T>::radix );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::radix::value,
                     std::numeric_limits<T>::radix );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::radix::value),
                     std::numeric_limits<T>::radix );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::radix::value),
                     std::numeric_limits<T>::radix );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::radix::value),
                     std::numeric_limits<T>::radix );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::radix::value),
                     std::numeric_limits<T>::radix );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::radix::value),
                     std::numeric_limits<T>::radix );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::radix::value),
                     std::numeric_limits<T>::radix );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::radix::value),
                     std::numeric_limits<T>::radix );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::radix::value),
                     std::numeric_limits<T>::radix );
}

//---------------------------------------------------------------------------//
// Check that the min negative integer value such that radix raised to
// (this-1) generates a normalized floating-point quantity is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( min_exponent, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::min_exponent::value,
                     std::numeric_limits<T>::min_exponent );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::min_exponent::value,
                     std::numeric_limits<T>::min_exponent );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::min_exponent::value),
                     std::numeric_limits<T>::min_exponent );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::min_exponent::value),
                     std::numeric_limits<T>::min_exponent );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::min_exponent::value),
                     std::numeric_limits<T>::min_exponent );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::min_exponent::value),
                     std::numeric_limits<T>::min_exponent );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::min_exponent::value),
                     std::numeric_limits<T>::min_exponent );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::min_exponent::value),
                     std::numeric_limits<T>::min_exponent );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::min_exponent::value),
                     std::numeric_limits<T>::min_exponent );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::min_exponent::value),
                     std::numeric_limits<T>::min_exponent );
}

//---------------------------------------------------------------------------//
// Check that the min integer value such that 10 raised to that power generates
// a normalized floating-point quantity is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( min_exponent10, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::min_exponent10::value,
                     std::numeric_limits<T>::min_exponent10 );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::min_exponent10::value,
                     std::numeric_limits<T>::min_exponent10 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::min_exponent10::value),
                     std::numeric_limits<T>::min_exponent10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::min_exponent10::value),
                     std::numeric_limits<T>::min_exponent10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::min_exponent10::value),
                     std::numeric_limits<T>::min_exponent10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::min_exponent10::value),
                     std::numeric_limits<T>::min_exponent10 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::min_exponent10::value),
                     std::numeric_limits<T>::min_exponent10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::min_exponent10::value),
                     std::numeric_limits<T>::min_exponent10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::min_exponent10::value),
                     std::numeric_limits<T>::min_exponent10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::min_exponent10::value),
                     std::numeric_limits<T>::min_exponent10 );
}

//---------------------------------------------------------------------------//
// Check that one more than the largest integer power of the radix that is a
// valid finite floating-point value is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( max_exponent, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::max_exponent::value,
                     std::numeric_limits<T>::max_exponent );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::max_exponent::value,
                     std::numeric_limits<T>::max_exponent );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::max_exponent::value),
                     std::numeric_limits<T>::max_exponent );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::max_exponent::value),
                     std::numeric_limits<T>::max_exponent );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::max_exponent::value),
                     std::numeric_limits<T>::max_exponent );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::max_exponent::value),
                     std::numeric_limits<T>::max_exponent );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::max_exponent::value),
                     std::numeric_limits<T>::max_exponent );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::max_exponent::value),
                     std::numeric_limits<T>::max_exponent );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::max_exponent::value),
                     std::numeric_limits<T>::max_exponent );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::max_exponent::value),
                     std::numeric_limits<T>::max_exponent );
}

//---------------------------------------------------------------------------//
// Check that the max integer power of 10 that is a valid finite floating-point
// value is defined
BOOST_AUTO_TEST_CASE_TEMPLATE( max_exponent10, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::max_exponent10::value,
                     std::numeric_limits<T>::max_exponent10 );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::max_exponent10::value,
                     std::numeric_limits<T>::max_exponent10 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,T> >::max_exponent10::value),
                     std::numeric_limits<T>::max_exponent10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,T> >::max_exponent10::value),
                     std::numeric_limits<T>::max_exponent10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,T> >::max_exponent10::value),
                     std::numeric_limits<T>::max_exponent10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,T> >::max_exponent10::value),
                     std::numeric_limits<T>::max_exponent10 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<cgs::energy,std::complex<T> > >::max_exponent10::value),
                     std::numeric_limits<T>::max_exponent10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<si::energy,std::complex<T> > >::max_exponent10::value),
                     std::numeric_limits<T>::max_exponent10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<ElectronVolt,std::complex<T> > >::max_exponent10::value),
                     std::numeric_limits<T>::max_exponent10 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<boost::units::quantity<MegaElectronVolt,std::complex<T> > >::max_exponent10::value),
                     std::numeric_limits<T>::max_exponent10 );
}

//---------------------------------------------------------------------------//
// Check that the zero quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( zero_basic, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::zero(), T(0) );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::zero(), std::complex<T>( 0, 0 ) );
}

//---------------------------------------------------------------------------//
// Check that the zero quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( zero, QuantityType, TestQuantityTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::zero(),
                     QuantityType::from_value( 0 ) );
}

//---------------------------------------------------------------------------//
// Check that the one quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( one_basic, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::one(), T(1) );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::one(), std::complex<T>( 1, 0 ) );
}

//---------------------------------------------------------------------------//
// Check that the one quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( one, QuantityType, TestQuantityTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::one(),
                     QuantityType::from_value( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the min quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( min_basic, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::min(),
                     std::numeric_limits<T>::min() );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::min(),
                     std::complex<T>( std::numeric_limits<T>::min(), 0 ) );
}

//---------------------------------------------------------------------------//
// Check that the min quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( min, QuantityType, TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::min(),
                     QuantityType::from_value( std::numeric_limits<RawType>::min() ) );

  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::min(),
                     ComplexQuantityType::from_value( ComplexRawType( std::numeric_limits<RawType>::min(), 0 ) ) );
}

//---------------------------------------------------------------------------//
// Check that the denormalized min quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( denormMin_basic, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::denormMin(),
                     std::numeric_limits<T>::denorm_min() );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::denormMin(),
                     std::complex<T>( std::numeric_limits<T>::denorm_min(), 0 ) );
}

//---------------------------------------------------------------------------//
// Check that the denormalized min quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( denormMin, QuantityType, TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::denormMin(),
                     QuantityType::from_value( std::numeric_limits<RawType>::denorm_min() ) );

  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::denormMin(),
                     ComplexQuantityType::from_value( ComplexRawType( std::numeric_limits<RawType>::denorm_min(), 0 ) ) );
}

//---------------------------------------------------------------------------//
// Check that the max quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( max_basic, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::max(),
                     std::numeric_limits<T>::max() );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::max(),
                     std::complex<T>( std::numeric_limits<T>::max(), 0 ) );
}

//---------------------------------------------------------------------------//
// Check that the max quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( max, QuantityType, TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::max(),
                     QuantityType::from_value( std::numeric_limits<RawType>::max() ) );

  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::max(),
                     ComplexQuantityType::from_value( ComplexRawType( std::numeric_limits<RawType>::max(), 0 ) ) );
}

//---------------------------------------------------------------------------//
// Check that the lowest quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( lowest_basic, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::lowest(),
                     std::numeric_limits<T>::lowest() );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::lowest(),
                     std::complex<T>( std::numeric_limits<T>::lowest(), 0 ) );
}

//---------------------------------------------------------------------------//
// Check that the lowest quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( lowest, QuantityType, TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::lowest(),
                     QuantityType::from_value( std::numeric_limits<RawType>::lowest() ) );

  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::lowest(),
                     ComplexQuantityType::from_value( ComplexRawType( std::numeric_limits<RawType>::lowest(), 0 ) ) );
}

//---------------------------------------------------------------------------//
// Check that machine epsilon can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( epsilon_basic, T, TestFloatingPointTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::epsilon(),
                     std::numeric_limits<T>::epsilon() );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::epsilon(),
                     std::complex<T>( std::numeric_limits<T>::epsilon(), 0 ) );
}

//---------------------------------------------------------------------------//
// Check that machine epsilon can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( epsilon,
                               QuantityType,
                               TestBasicFloatingPointQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::epsilon(),
                     QuantityType::from_value( std::numeric_limits<RawType>::epsilon() ) );

  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::epsilon(),
                     ComplexQuantityType::from_value( ComplexRawType( std::numeric_limits<RawType>::epsilon(), 0 ) ) );
}

//---------------------------------------------------------------------------//
// Check that the max rounding error can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( roundError_basic, T, TestFloatingPointTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::roundError(),
                     std::numeric_limits<T>::round_error() );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::roundError(),
                     std::complex<T>( std::numeric_limits<T>::round_error(), 0 ) );
}

//---------------------------------------------------------------------------//
// Check that the max rounding error can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( roundError,
                               QuantityType,
                               TestBasicFloatingPointQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::roundError(),
                     QuantityType::from_value( std::numeric_limits<RawType>::round_error() ) );

  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::roundError(),
                     ComplexQuantityType::from_value( ComplexRawType( std::numeric_limits<RawType>::round_error(), 0 ) ) );
}

//---------------------------------------------------------------------------//
// Check that infinite quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( inf_basic, T, TestFloatingPointTypes )
{
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::inf(),
                     std::numeric_limits<T>::infinity() );
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::inf(),
                     std::complex<T>( std::numeric_limits<T>::infinity(), 0 ) );
}

//---------------------------------------------------------------------------//
// Check that infinite quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( inf,
                               QuantityType,
                               TestBasicFloatingPointQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::inf(),
                     QuantityType::from_value( std::numeric_limits<RawType>::infinity() ) );

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::inf(),
                     ComplexQuantityType::from_value( ComplexRawType( std::numeric_limits<RawType>::infinity(), 0 ) ) );
}

//---------------------------------------------------------------------------//
// Check that the quiet nan quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( nan_basic, T, TestFloatingPointTypes )
{
  BOOST_CHECK( Utility::QuantityTraits<T>::nan() !=
               Utility::QuantityTraits<T>::nan() );
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::nan() !=
               Utility::QuantityTraits<std::complex<T> >::nan() );
}

//---------------------------------------------------------------------------//
// Check that the quiet nan quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( _nan,
                               QuantityType,
                               TestBasicFloatingPointQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;

  BOOST_CHECK( Utility::QuantityTraits<QuantityType>::nan() !=
               Utility::QuantityTraits<QuantityType>::nan() );

  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;

  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::nan() !=
               Utility::QuantityTraits<ComplexQuantityType>::nan() );
}

//---------------------------------------------------------------------------//
// Check that the signaling nan quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( signalingNan_basic, T, TestFloatingPointTypes )
{
  BOOST_CHECK( Utility::QuantityTraits<T>::signalingNan() !=
               Utility::QuantityTraits<T>::signalingNan() );
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::signalingNan() !=
               Utility::QuantityTraits<std::complex<T> >::signalingNan() );
}

//---------------------------------------------------------------------------//
// Check that the signaling nan quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( signalingNan,
                               QuantityType,
                               TestBasicFloatingPointQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;

  BOOST_CHECK( Utility::QuantityTraits<QuantityType>::signalingNan() !=
               Utility::QuantityTraits<QuantityType>::signalingNan() );

  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<ComplexRawType>::type ComplexQuantityType;

  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::signalingNan() !=
               Utility::QuantityTraits<ComplexQuantityType>::signalingNan() );
}

//---------------------------------------------------------------------------//
// Check that the absolute value of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( abs_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::abs( T(0) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::abs( T(0) ), RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::abs( T(1) ),
                     RawFloatingPointType(1) );
  BOOST_CHECK_EQUAL( Utility::abs( T(1) ), RawFloatingPointType(1) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::abs( T(2) ),
                     RawFloatingPointType(2) );
  BOOST_CHECK_EQUAL( Utility::abs( T(2) ), RawFloatingPointType(2) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( 0, 0 ) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( 0, 0 ) ),
                     RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( 1, 0 ) ),
                     RawFloatingPointType(1) );
  BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( 1, 0 ) ),
                     RawFloatingPointType(1) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( 2, 0 ) ),
                     RawFloatingPointType(2) );
  BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( 2, 0 ) ),
                     RawFloatingPointType(2) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( 0, 1 ) ),
                     RawFloatingPointType(1) );
  BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( 0, 1 ) ),
                     RawFloatingPointType(1) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( 0, 2 ) ),
                     RawFloatingPointType(2) );
  BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( 0, 2 ) ),
                     RawFloatingPointType(2) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( 1, 1 ) ),
                     RawFloatingPointType(std::sqrt(2)) );
  BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( 1, 1 ) ),
                     RawFloatingPointType(std::sqrt(2)) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( 2, 2 ) ),
                     RawFloatingPointType(std::sqrt(8)) );
  BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( 2, 2 ) ),
                     RawFloatingPointType(std::sqrt(8)) );
  
  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::abs( T(-2) ),
                       RawFloatingPointType(2) );
    BOOST_CHECK_EQUAL( Utility::abs( T(-2) ), RawFloatingPointType(2) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::abs( T(-1) ),
                       RawFloatingPointType(1) );
    BOOST_CHECK_EQUAL( Utility::abs( T(-1) ), RawFloatingPointType(1) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( -2, 0 ) ),
                       RawFloatingPointType(2) );
    BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( -2, 0 ) ),
                       RawFloatingPointType(2) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( -1, 0 ) ),
                       RawFloatingPointType(1) );
    BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( -1, 0 ) ),
                       RawFloatingPointType(1) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( 0, -2 ) ),
                       RawFloatingPointType(2) );
    BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( 0, -2 ) ),
                       RawFloatingPointType(2) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( 0, -1 ) ),
                       RawFloatingPointType(1) );
    BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( 0, -1 ) ),
                       RawFloatingPointType(1) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( -1, 1 ) ),
                       RawFloatingPointType(std::sqrt(2)) );
    BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( -1, 1 ) ),
                       RawFloatingPointType(std::sqrt(2)) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( 1, -1 ) ),
                       RawFloatingPointType(std::sqrt(2)) );
    BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( 1, -1 ) ),
                       RawFloatingPointType(std::sqrt(2)) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::abs( std::complex<T>( -1, -1 ) ),
                       RawFloatingPointType(std::sqrt(2)) );
    BOOST_CHECK_EQUAL( Utility::abs( std::complex<T>( -1, -1 ) ),
                       RawFloatingPointType(std::sqrt(2)) );
  }
}

//---------------------------------------------------------------------------//
// Check that the absolute value of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( _abs, QuantityType, TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::RealFloatingPointQuantityType RealFloatingPointQuantityType;
  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<ComplexRawType>::type ComplexQuantityType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::abs( QuantityType::from_value( 0 ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::abs( QuantityType::from_value( 0 ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::abs( QuantityType::from_value( 1 ) ),
                     RealFloatingPointQuantityType::from_value( 1 ) );
  BOOST_CHECK_EQUAL( Utility::abs( QuantityType::from_value( 1 ) ),
                     RealFloatingPointQuantityType::from_value( 1 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::abs( QuantityType::from_value( 2 ) ),
                     RealFloatingPointQuantityType::from_value( 2 ) );
  BOOST_CHECK_EQUAL( Utility::abs( QuantityType::from_value( 2 ) ),
                     RealFloatingPointQuantityType::from_value( 2 ) );

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 1 ) );
  BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 1 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( 2, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 2 ) );
  BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( 2, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 2 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) ),
                     RealFloatingPointQuantityType::from_value( 1 ) );
  BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) ),
                     RealFloatingPointQuantityType::from_value( 1 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( 0, 2 ) ) ),
                     RealFloatingPointQuantityType::from_value( 2 ) );
  BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( 0, 2 ) ) ),
                     RealFloatingPointQuantityType::from_value( 2 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( 1, 1 ) ) ),
                     RealFloatingPointQuantityType::from_value( std::sqrt(2) ) );
  BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( 1, 1 ) ) ),
                     RealFloatingPointQuantityType::from_value( std::sqrt(2) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( 2, 2 ) ) ),
                     RealFloatingPointQuantityType::from_value( std::sqrt(8) ) );
  BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( 2, 2 ) ) ),
                     RealFloatingPointQuantityType::from_value( std::sqrt(8) ) );

  if( Utility::QuantityTraits<QuantityType>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::abs( QuantityType::from_value( -2 ) ),
                       RealFloatingPointQuantityType::from_value( 2 ) );
    BOOST_CHECK_EQUAL( Utility::abs( QuantityType::from_value( -2 ) ),
                       RealFloatingPointQuantityType::from_value( 2 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::abs( QuantityType::from_value( -1 ) ),
                       RealFloatingPointQuantityType::from_value( 1 ) );
    BOOST_CHECK_EQUAL( Utility::abs( QuantityType::from_value( -1 ) ),
                       RealFloatingPointQuantityType::from_value( 1 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( -2, 0 ) ) ),
                       RealFloatingPointQuantityType::from_value( 2 ) );
    BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( -2, 0 ) ) ),
                       RealFloatingPointQuantityType::from_value( 2 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) ),
                       RealFloatingPointQuantityType::from_value( 1 ) );
    BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) ),
                       RealFloatingPointQuantityType::from_value( 1 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( 0, -2 ) ) ),
                       RealFloatingPointQuantityType::from_value( 2 ) );
    BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( 0, -2 ) ) ),
                       RealFloatingPointQuantityType::from_value( 2 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) ),
                       RealFloatingPointQuantityType::from_value( 1 ) );
    BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) ),
                       RealFloatingPointQuantityType::from_value( 1 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( -1, 1 ) ) ),
                       RealFloatingPointQuantityType::from_value( std::sqrt(2) ) );
    BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( -1, 1 ) ) ),
                       RealFloatingPointQuantityType::from_value( std::sqrt(2) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( 1, -1 ) ) ),
                       RealFloatingPointQuantityType::from_value( std::sqrt(2) ) );
    BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( 1, -1 ) ) ),
                       RealFloatingPointQuantityType::from_value( std::sqrt(2) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::abs( ComplexQuantityType::from_value( ComplexRawType( -1, -1 ) ) ),
                       RealFloatingPointQuantityType::from_value( std::sqrt(2) ) );
    BOOST_CHECK_EQUAL( Utility::abs( ComplexQuantityType::from_value( ComplexRawType( -1, -1 ) ) ),
                       RealFloatingPointQuantityType::from_value( std::sqrt(2) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the conjugate of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( conj_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::conj( T(0) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::conj( T(0) ), RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::conj( T(1) ),
                     RawFloatingPointType(1) );
  BOOST_CHECK_EQUAL( Utility::conj( T(1) ), RawFloatingPointType(1) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::conj( T(2) ),
                     RawFloatingPointType(2) );
  BOOST_CHECK_EQUAL( Utility::conj( T(2) ), RawFloatingPointType(2) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( 0, 0 ) ),
                     ComplexRawFloatingPointType( 0, 0 ) );
  BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( 0, 0 ) ),
                     ComplexRawFloatingPointType( 0, 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( 1, 0 ) ),
                     ComplexRawFloatingPointType( 1, 0 ) );
  BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( 1, 0 ) ),
                     ComplexRawFloatingPointType( 1, 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( 2, 0 ) ),
                     ComplexRawFloatingPointType( 2, 0 ) );
  BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( 2, 0 ) ),
                     ComplexRawFloatingPointType( 2, 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( 0, 1 ) ),
                     ComplexRawFloatingPointType( 0, -1 ) );
  BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( 0, 1 ) ),
                     ComplexRawFloatingPointType( 0, -1 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( 0, 2 ) ),
                     ComplexRawFloatingPointType( 0, -2 ) );
  BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( 0, 2 ) ),
                     ComplexRawFloatingPointType( 0, -2 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( 1, 1 ) ),
                     ComplexRawFloatingPointType( 1, -1 ) );
  BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( 1, 1 ) ),
                     ComplexRawFloatingPointType( 1, -1 ) );
  
  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::conj( T(-2) ),
                       RawFloatingPointType(-2) );
    BOOST_CHECK_EQUAL( Utility::conj( T(-2) ), RawFloatingPointType(-2) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::conj( T(-1) ),
                       RawFloatingPointType(-1) );
    BOOST_CHECK_EQUAL( Utility::conj( T(-1) ), RawFloatingPointType(-1) );
  
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( -2, 0 ) ),
                       ComplexRawFloatingPointType( -2, 0 ) );
    BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( -2, 0 ) ),
                       ComplexRawFloatingPointType( -2, 0 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( -1, 0 ) ),
                       ComplexRawFloatingPointType( -1, 0 ) );
    BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( -1, 0 ) ),
                       ComplexRawFloatingPointType( -1, 0 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( 0, -2 ) ),
                       ComplexRawFloatingPointType( 0, 2 ) );
    BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( 0, -2 ) ),
                       ComplexRawFloatingPointType( 0, 2 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( 0, -1 ) ),
                       ComplexRawFloatingPointType( 0, 1 ) );
    BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( 0, -1 ) ),
                       ComplexRawFloatingPointType( 0, 1 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( 1, -1 ) ),
                       ComplexRawFloatingPointType( 1, 1 ) );
    BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( 1, -1 ) ),
                       ComplexRawFloatingPointType( 1, 1 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( -1, 1 ) ),
                       ComplexRawFloatingPointType( -1, -1 ) );
    BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( -1, 1 ) ),
                       ComplexRawFloatingPointType( -1, -1 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::conj( std::complex<T>( -1, -1 ) ),
                       ComplexRawFloatingPointType( -1, 1 ) );
    BOOST_CHECK_EQUAL( Utility::conj( std::complex<T>( -1, -1 ) ),
                       ComplexRawFloatingPointType( -1, 1 ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the conjugate of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( _conj, QuantityType, TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::FloatingPointQuantityType FloatingPointQuantityType;
  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;
  typedef typename Utility::QuantityTraits<ComplexQuantityType>::RawFloatingPointType ComplexRawFloatingPointType;
  typedef typename Utility::QuantityTraits<ComplexQuantityType>::FloatingPointQuantityType ComplexFloatingPointQuantityType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::conj( QuantityType::from_value(  0 ) ),
                     FloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::conj( QuantityType::from_value(  0 ) ),
                     FloatingPointQuantityType::from_value( 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::conj( QuantityType::from_value( 1 ) ),
                     FloatingPointQuantityType::from_value( 1 ) );
  BOOST_CHECK_EQUAL( Utility::conj( QuantityType::from_value( 1 ) ),
                     FloatingPointQuantityType::from_value( 1 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::conj( QuantityType::from_value( 2 ) ),
                     FloatingPointQuantityType::from_value( 2 ) );
  BOOST_CHECK_EQUAL( Utility::conj( QuantityType::from_value( 2 ) ),
                     FloatingPointQuantityType::from_value( 2 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) ),
                     ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 0, 0 ) ) );
  BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) ),
                     ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 0, 0 ) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) ),
                     ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 1, 0 ) ) );
  BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) ),
                     ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 1, 0 ) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( 2, 0 ) ) ),
                     ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 2, 0 ) ) );
  BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( 2, 0 ) ) ),
                     ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 2, 0 ) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) ),
                     ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 0, -1 ) ) );
  BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) ),
                     ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 0, -1 ) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( 0, 2 ) ) ),
                     ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 0, -2 ) ) );
  BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( 0, 2 ) ) ),
                     ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 0, -2 ) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( 1, 1 ) ) ),
                     ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 1, -1 ) ) );
  BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( 1, 1 ) ) ),
                     ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 1, -1 ) ) );
  
  if( Utility::QuantityTraits<QuantityType>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::conj( QuantityType::from_value( -2 ) ),
                       FloatingPointQuantityType::from_value( -2 ) );
    BOOST_CHECK_EQUAL( Utility::conj( QuantityType::from_value( -2 ) ),
                       FloatingPointQuantityType::from_value( -2 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::conj( QuantityType::from_value( -1 ) ),
                       FloatingPointQuantityType::from_value( -1 ) );
    BOOST_CHECK_EQUAL( Utility::conj( QuantityType::from_value( -1 ) ),
                       FloatingPointQuantityType::from_value( -1 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( -2, 0 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( -2, 0 ) ) );
    BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( -2, 0 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( -2, 0 ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( -1, 0 ) ) );
    BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( -1, 0 ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( 0, -2 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 0, 2 ) ) );
    BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( 0, -2 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 0, 2 ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 0, 1 ) ) );
    BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 0, 1 ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( -1, 1 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( -1, -1 ) ) );
    BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( -1, 1 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( -1, -1 ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( 1, -1 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 1, 1 ) ) );
    BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( 1, -1 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( 1, 1 ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::conj( ComplexQuantityType::from_value( ComplexRawType( -1, -1 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( -1, 1 ) ) );
    BOOST_CHECK_EQUAL( Utility::conj( ComplexQuantityType::from_value( ComplexRawType( -1, -1 ) ) ),
                       ComplexFloatingPointQuantityType::from_value( ComplexRawFloatingPointType( -1, 1 ) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the real part of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( real_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::real( T(0) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::real( T(0) ), RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::real( T(1) ),
                     RawFloatingPointType(1) );
  BOOST_CHECK_EQUAL( Utility::real( T(1) ), RawFloatingPointType(1) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::real( T(2) ),
                     RawFloatingPointType(2) );
  BOOST_CHECK_EQUAL( Utility::real( T(2) ), RawFloatingPointType(2) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::real( std::complex<T>( 0, 0 ) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::real( std::complex<T>( 0, 0 ) ),
                     RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::real( std::complex<T>( 1, 0 ) ),
                     RawFloatingPointType(1) );
  BOOST_CHECK_EQUAL( Utility::real( std::complex<T>( 1, 0 ) ),
                     RawFloatingPointType(1) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::real( std::complex<T>( 2, 0 ) ),
                     RawFloatingPointType(2) );
  BOOST_CHECK_EQUAL( Utility::real( std::complex<T>( 2, 0 ) ),
                     RawFloatingPointType(2) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::real( std::complex<T>( 0, 1 ) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::real( std::complex<T>( 0, 1 ) ),
                     RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::real( std::complex<T>( 0, 2 ) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::real( std::complex<T>( 0, 2 ) ),
                     RawFloatingPointType(0) );
  
  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::real( T(-2) ),
                       RawFloatingPointType(-2) );
    BOOST_CHECK_EQUAL( Utility::real( T(-2) ),
                       RawFloatingPointType(-2) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::real( T(-1) ),
                       RawFloatingPointType(-1) );
    BOOST_CHECK_EQUAL( Utility::real( T(-1) ),
                       RawFloatingPointType(-1) );

    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::real( std::complex<T>( -2, 0 ) ),
                       RawFloatingPointType(-2) );
    BOOST_CHECK_EQUAL( Utility::real( std::complex<T>( -2, 0 ) ),
                       RawFloatingPointType(-2) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::real( std::complex<T>( -1, 0 ) ),
                       RawFloatingPointType(-1) );
    BOOST_CHECK_EQUAL( Utility::real( std::complex<T>( -1, 0 ) ),
                       RawFloatingPointType(-1) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::real( std::complex<T>( 0, -2 ) ),
                       RawFloatingPointType(0) );
    BOOST_CHECK_EQUAL( Utility::real( std::complex<T>( 0, -2 ) ),
                       RawFloatingPointType(0) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::real( std::complex<T>( 0, -1 ) ),
                       RawFloatingPointType(0) );
    BOOST_CHECK_EQUAL( Utility::real( std::complex<T>( 0, -1 ) ),
                       RawFloatingPointType(0) );
  }
}

//---------------------------------------------------------------------------//
// Check that the real part of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( _real, QuantityType, TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::FloatingPointQuantityType RealFloatingPointQuantityType;
  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::real( QuantityType::from_value( 0 ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::real( QuantityType::from_value( 0 ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::real( QuantityType::from_value( 1 ) ),
                     RealFloatingPointQuantityType::from_value( 1 ) );
  BOOST_CHECK_EQUAL( Utility::real( QuantityType::from_value( 1 ) ),
                     RealFloatingPointQuantityType::from_value( 1 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::real( QuantityType::from_value( 2 ) ),
                     RealFloatingPointQuantityType::from_value( 2 ) );
  BOOST_CHECK_EQUAL( Utility::real( QuantityType::from_value( 2 ) ),
                     RealFloatingPointQuantityType::from_value( 2 ) );

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::real( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::real( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::real( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 1 ) );
  BOOST_CHECK_EQUAL( Utility::real( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 1 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::real( ComplexQuantityType::from_value( ComplexRawType( 2, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 2 ) );
  BOOST_CHECK_EQUAL( Utility::real( ComplexQuantityType::from_value( ComplexRawType( 2, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 2 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::real( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::real( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::real( ComplexQuantityType::from_value( ComplexRawType( 0, 2 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::real( ComplexQuantityType::from_value( ComplexRawType( 0, 2 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );

  if( Utility::QuantityTraits<QuantityType>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::real( QuantityType::from_value( -2 ) ),
                       RealFloatingPointQuantityType::from_value( -2 ) );
    BOOST_CHECK_EQUAL( Utility::real( QuantityType::from_value( -2 ) ),
                       RealFloatingPointQuantityType::from_value( -2 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::real( QuantityType::from_value( -1 ) ),
                       RealFloatingPointQuantityType::from_value( -1 ) );
    BOOST_CHECK_EQUAL( Utility::real( QuantityType::from_value( -1 ) ),
                       RealFloatingPointQuantityType::from_value( -1 ) );

    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::real( ComplexQuantityType::from_value( ComplexRawType( -2, 0 ) ) ),
                       RealFloatingPointQuantityType::from_value( -2 ) );
    BOOST_CHECK_EQUAL( Utility::real( ComplexQuantityType::from_value( ComplexRawType( -2, 0 ) ) ),
                       RealFloatingPointQuantityType::from_value( -2 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::real( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) ),
                       RealFloatingPointQuantityType::from_value( -1 ) );
    BOOST_CHECK_EQUAL( Utility::real( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) ),
                       RealFloatingPointQuantityType::from_value( -1 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::real( ComplexQuantityType::from_value( ComplexRawType( 0, -2 ) ) ),
                       RealFloatingPointQuantityType::from_value( 0 ) );
    BOOST_CHECK_EQUAL( Utility::real( ComplexQuantityType::from_value( ComplexRawType( 0, -2 ) ) ),
                       RealFloatingPointQuantityType::from_value( 0 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::real( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) ),
                       RealFloatingPointQuantityType::from_value( 0 ) );
    BOOST_CHECK_EQUAL( Utility::real( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) ),
                       RealFloatingPointQuantityType::from_value( 0 ) );    
  }
}

//---------------------------------------------------------------------------//
// Check that the imaginary part of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( imag_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::imag( T(0) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::imag( T(0) ), RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::imag( T(1) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::imag( T(1) ), RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::imag( T(2) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::imag( T(2) ), RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::imag( std::complex<T>( 0, 0 ) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::imag( std::complex<T>( 0, 0 ) ),
                     RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::imag( std::complex<T>( 1, 0 ) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::imag( std::complex<T>( 1, 0 ) ),
                     RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::imag( std::complex<T>( 2, 0 ) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::imag( std::complex<T>( 2, 0 ) ),
                     RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::imag( std::complex<T>( 0, 1 ) ),
                     RawFloatingPointType(1) );
  BOOST_CHECK_EQUAL( Utility::imag( std::complex<T>( 0, 1 ) ),
                     RawFloatingPointType(1) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::imag( std::complex<T>( 0, 2 ) ),
                     RawFloatingPointType(2) );
  BOOST_CHECK_EQUAL( Utility::imag( std::complex<T>( 0, 2 ) ),
                     RawFloatingPointType(2) );
  
  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::imag( T(-2) ),
                       RawFloatingPointType(0) );
    BOOST_CHECK_EQUAL( Utility::imag( T(-2) ), RawFloatingPointType(0) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::imag( T(-1) ),
                       RawFloatingPointType(0) );
    BOOST_CHECK_EQUAL( Utility::imag( T(-1) ), RawFloatingPointType(0) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::imag( std::complex<T>( -2, 0 ) ),
                       RawFloatingPointType(0) );
    BOOST_CHECK_EQUAL( Utility::imag( std::complex<T>( -2, 0 ) ),
                       RawFloatingPointType(0) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::imag( std::complex<T>( -1, 0 ) ),
                       RawFloatingPointType(0) );
    BOOST_CHECK_EQUAL( Utility::imag( std::complex<T>( -1, 0 ) ),
                       RawFloatingPointType(0) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::imag( std::complex<T>( 0, -2 ) ),
                       RawFloatingPointType(-2) );
    BOOST_CHECK_EQUAL( Utility::imag( std::complex<T>( 0, -2 ) ),
                       RawFloatingPointType(-2) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::imag( std::complex<T>( 0, -1 ) ),
                       RawFloatingPointType(-1) );
    BOOST_CHECK_EQUAL( Utility::imag( std::complex<T>( 0, -1 ) ),
                       RawFloatingPointType(-1) );
  }
}

//---------------------------------------------------------------------------//
// Check that the imaginary part of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( _imag, QuantityType, TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::RealFloatingPointQuantityType RealFloatingPointQuantityType;
  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::imag( QuantityType::from_value( 0 ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::imag( QuantityType::from_value( 0 ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::imag( QuantityType::from_value( 1 ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::imag( QuantityType::from_value( 1 ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::imag( QuantityType::from_value( 2 ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::imag( QuantityType::from_value( 2 ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::imag( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::imag( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::imag( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::imag( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::imag( ComplexQuantityType::from_value( ComplexRawType( 2, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  BOOST_CHECK_EQUAL( Utility::imag( ComplexQuantityType::from_value( ComplexRawType( 2, 0 ) ) ),
                     RealFloatingPointQuantityType::from_value( 0 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::imag( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) ),
                     RealFloatingPointQuantityType::from_value( 1 ) );
  BOOST_CHECK_EQUAL( Utility::imag( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) ),
                     RealFloatingPointQuantityType::from_value( 1 ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::imag( ComplexQuantityType::from_value( ComplexRawType( 0, 2 ) ) ),
                     RealFloatingPointQuantityType::from_value( 2 ) );
  BOOST_CHECK_EQUAL( Utility::imag( ComplexQuantityType::from_value( ComplexRawType( 0, 2 ) ) ),
                     RealFloatingPointQuantityType::from_value( 2 ) );

  if( Utility::QuantityTraits<QuantityType>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::imag( QuantityType::from_value( -2 ) ),
                       RealFloatingPointQuantityType::from_value( 0 ) );
    BOOST_CHECK_EQUAL( Utility::imag( QuantityType::from_value( -2 ) ),
                       RealFloatingPointQuantityType::from_value( 0 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::imag( QuantityType::from_value( -1 ) ),
                       RealFloatingPointQuantityType::from_value( 0 ) );
    BOOST_CHECK_EQUAL( Utility::imag( QuantityType::from_value( -1 ) ),
                       RealFloatingPointQuantityType::from_value( 0 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::imag( ComplexQuantityType::from_value( ComplexRawType( -2, 0 ) ) ),
                       RealFloatingPointQuantityType::from_value( 0 ) );
    BOOST_CHECK_EQUAL( Utility::imag( ComplexQuantityType::from_value( ComplexRawType( -2, 0 ) ) ),
                       RealFloatingPointQuantityType::from_value( 0 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::imag( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) ),
                       RealFloatingPointQuantityType::from_value( 0 ) );
    BOOST_CHECK_EQUAL( Utility::imag( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) ),
                       RealFloatingPointQuantityType::from_value( 0 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::imag( ComplexQuantityType::from_value( ComplexRawType( 0, -2 ) ) ),
                       RealFloatingPointQuantityType::from_value( -2 ) );
    BOOST_CHECK_EQUAL( Utility::imag( ComplexQuantityType::from_value( ComplexRawType( 0, -2 ) ) ),
                       RealFloatingPointQuantityType::from_value( -2 ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<ComplexQuantityType>::imag( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) ),
                       RealFloatingPointQuantityType::from_value( -1 ) );
    BOOST_CHECK_EQUAL( Utility::imag( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) ),
                       RealFloatingPointQuantityType::from_value( -1 ) );
    
  }
}

//---------------------------------------------------------------------------//
// Test if a quantity is nan or inf
BOOST_AUTO_TEST_CASE_TEMPLATE( isnaninf_float_basic, T, TestFloatingPointTypes )
{
  T infinity = Utility::QuantityTraits<T>::inf();
  std::complex<T> complex_infinity =
    Utility::QuantityTraits<std::complex<T> >::inf();
    
  BOOST_CHECK( Utility::QuantityTraits<T>::isnaninf( infinity ) );
  BOOST_CHECK( Utility::isnaninf( infinity ) );
  
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );

  complex_infinity = std::complex<T>( T(0), infinity );

  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );

  complex_infinity = std::complex<T>( infinity, infinity );
  
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );

  infinity *= -1;
  complex_infinity = std::complex<T>( -infinity, T(0) );

  BOOST_CHECK( Utility::QuantityTraits<T>::isnaninf( infinity ) );
  BOOST_CHECK( Utility::isnaninf( infinity ) );
  
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );
  
  complex_infinity = std::complex<T>( T(0), -infinity );
  
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );
  
  complex_infinity = std::complex<T>( infinity, -infinity );
  
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );
  
  complex_infinity = std::complex<T>( -infinity, infinity );
  
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );

  complex_infinity = std::complex<T>( -infinity, -infinity );
  
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );

  T quiet_nan = Utility::QuantityTraits<T>::nan();
  std::complex<T> complex_quiet_nan = Utility::QuantityTraits<std::complex<T> >::nan();

  BOOST_CHECK( Utility::QuantityTraits<T>::isnaninf( quiet_nan ) );
  BOOST_CHECK( Utility::isnaninf( quiet_nan ) );
  
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_quiet_nan ) );
  BOOST_CHECK( Utility::isnaninf( complex_quiet_nan ) );
  
  complex_quiet_nan = std::complex<T>( T(0), quiet_nan );
  
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_quiet_nan ) );
  BOOST_CHECK( Utility::isnaninf( complex_quiet_nan ) );
  
  complex_quiet_nan = std::complex<T>( quiet_nan, quiet_nan );
  
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_quiet_nan ) );
  BOOST_CHECK( Utility::isnaninf( complex_quiet_nan ) );
  
  T signaling_nan = Utility::QuantityTraits<T>::signalingNan();
  std::complex<T> complex_signaling_nan = Utility::QuantityTraits<std::complex<T> >::signalingNan();

  BOOST_CHECK( Utility::QuantityTraits<T>::isnaninf( signaling_nan ) );
  BOOST_CHECK( Utility::isnaninf( signaling_nan ) );
  
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_signaling_nan ) );
  BOOST_CHECK( Utility::isnaninf( complex_signaling_nan ) );
  
  complex_signaling_nan = std::complex<T>( T(0), signaling_nan );
  
  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_signaling_nan ) );
  BOOST_CHECK( Utility::isnaninf( complex_signaling_nan ) );
  
  complex_signaling_nan = std::complex<T>( signaling_nan, signaling_nan );

  BOOST_CHECK( Utility::QuantityTraits<std::complex<T> >::isnaninf( complex_signaling_nan ) );
  BOOST_CHECK( Utility::isnaninf( complex_signaling_nan ) );
}

//---------------------------------------------------------------------------//
// Test if a quantity is nan or inf
BOOST_AUTO_TEST_CASE_TEMPLATE( isnaninf_basic, T, TestTypes )
{
  BOOST_CHECK( !Utility::QuantityTraits<T>::isnaninf( Utility::QuantityTraits<T>::max() ) );
  BOOST_CHECK( !Utility::isnaninf( Utility::QuantityTraits<T>::max() ) );
  
  BOOST_CHECK( !Utility::QuantityTraits<std::complex<T> >::isnaninf( Utility::QuantityTraits<std::complex<T> >::max() ) );
  BOOST_CHECK( !Utility::isnaninf( Utility::QuantityTraits<std::complex<T> >::max() ) );

  BOOST_CHECK( !Utility::QuantityTraits<T>::isnaninf( Utility::QuantityTraits<T>::min() ) );
  BOOST_CHECK( !Utility::isnaninf( Utility::QuantityTraits<T>::min() ) );
  
  BOOST_CHECK( !Utility::QuantityTraits<std::complex<T> >::isnaninf( Utility::QuantityTraits<std::complex<T> >::min() ) );
  BOOST_CHECK( !Utility::isnaninf( Utility::QuantityTraits<std::complex<T> >::min() ) );
  
  BOOST_CHECK( !Utility::QuantityTraits<T>::isnaninf( Utility::QuantityTraits<T>::lowest() ) );
  BOOST_CHECK( !Utility::isnaninf( Utility::QuantityTraits<T>::lowest() ) );
  
  BOOST_CHECK( !Utility::QuantityTraits<std::complex<T> >::isnaninf( Utility::QuantityTraits<std::complex<T> >::lowest() ) );
  BOOST_CHECK( !Utility::isnaninf( Utility::QuantityTraits<std::complex<T> >::lowest() ) );
}

//---------------------------------------------------------------------------//
// Test if a quantity is non or inf
BOOST_AUTO_TEST_CASE_TEMPLATE( isnaninf_float,
                               QuantityType,
                               TestBasicFloatingPointQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<ComplexRawType>::type ComplexQuantityType;

  QuantityType infinity = Utility::QuantityTraits<QuantityType>::inf();
  ComplexQuantityType complex_infinity =
    Utility::QuantityTraits<ComplexQuantityType>::inf();
    
  BOOST_CHECK( Utility::QuantityTraits<QuantityType>::isnaninf( infinity ) );
  BOOST_CHECK( Utility::isnaninf( infinity ) );
  
  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );

  complex_infinity = ComplexQuantityType::from_value( ComplexRawType( Utility::QuantityTraits<RawType>::zero(), Utility::QuantityTraits<RawType>::inf() ) );

  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );
    
  complex_infinity = ComplexQuantityType::from_value( ComplexRawType( Utility::QuantityTraits<RawType>::inf(), Utility::QuantityTraits<RawType>::inf() ) );

  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );

  infinity = -Utility::QuantityTraits<QuantityType>::inf();
  complex_infinity = ComplexQuantityType::from_value( ComplexRawType( -Utility::QuantityTraits<RawType>::inf(), Utility::QuantityTraits<RawType>::zero() ) );
  
  BOOST_CHECK( Utility::QuantityTraits<QuantityType>::isnaninf( infinity ) );
  BOOST_CHECK( Utility::isnaninf( infinity ) );
  
  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );
  
  complex_infinity = ComplexQuantityType::from_value( ComplexRawType( Utility::QuantityTraits<RawType>::zero(), -Utility::QuantityTraits<RawType>::inf() ) );
  
  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );
  
  complex_infinity = ComplexQuantityType::from_value( ComplexRawType( Utility::QuantityTraits<RawType>::inf(), -Utility::QuantityTraits<RawType>::inf() ) );
  
  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );
  
  complex_infinity = ComplexQuantityType::from_value( -ComplexRawType( Utility::QuantityTraits<RawType>::inf(), Utility::QuantityTraits<RawType>::inf() ) );
  
  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );

  complex_infinity = ComplexQuantityType::from_value( -ComplexRawType( Utility::QuantityTraits<RawType>::inf(), -Utility::QuantityTraits<RawType>::inf() ) );
  
  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_infinity ) );
  BOOST_CHECK( Utility::isnaninf( complex_infinity ) );

  QuantityType quiet_nan = Utility::QuantityTraits<QuantityType>::nan();
  ComplexQuantityType complex_quiet_nan = Utility::QuantityTraits<ComplexQuantityType>::nan();

  BOOST_CHECK( Utility::QuantityTraits<QuantityType>::isnaninf( quiet_nan ) );
  BOOST_CHECK( Utility::isnaninf( quiet_nan ) );
  
  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_quiet_nan ) );
  BOOST_CHECK( Utility::isnaninf( complex_quiet_nan ) );
  
  complex_quiet_nan = ComplexQuantityType::from_value( ComplexRawType( Utility::QuantityTraits<RawType>::zero(), Utility::QuantityTraits<RawType>::nan() ) );
  
  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_quiet_nan ) );
  BOOST_CHECK( Utility::isnaninf( complex_quiet_nan ) );
  
  complex_quiet_nan = ComplexQuantityType::from_value( ComplexRawType( Utility::QuantityTraits<RawType>::nan(), Utility::QuantityTraits<RawType>::nan() ) );
  
  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_quiet_nan ) );
  BOOST_CHECK( Utility::isnaninf( complex_quiet_nan ) );
  
  QuantityType signaling_nan = Utility::QuantityTraits<QuantityType>::nan();
  ComplexQuantityType complex_signaling_nan = Utility::QuantityTraits<ComplexQuantityType>::nan();

  BOOST_CHECK( Utility::QuantityTraits<QuantityType>::isnaninf( signaling_nan ) );
  BOOST_CHECK( Utility::isnaninf( signaling_nan ) );
  
  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_signaling_nan ) );
  BOOST_CHECK( Utility::isnaninf( complex_signaling_nan ) );
  
  complex_signaling_nan = ComplexQuantityType::from_value( ComplexRawType( Utility::QuantityTraits<RawType>::zero(), Utility::QuantityTraits<RawType>::nan() ) );
  
  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_signaling_nan ) );
  BOOST_CHECK( Utility::isnaninf( complex_signaling_nan ) );
  
  complex_signaling_nan = ComplexQuantityType::from_value( ComplexRawType( Utility::QuantityTraits<RawType>::nan(), Utility::QuantityTraits<RawType>::nan() ) );
  
  BOOST_CHECK( Utility::QuantityTraits<ComplexQuantityType>::isnaninf( complex_signaling_nan ) );
  BOOST_CHECK( Utility::isnaninf( complex_signaling_nan ) );
}

//---------------------------------------------------------------------------//
// Test if a quantity is non or inf
BOOST_AUTO_TEST_CASE_TEMPLATE( isnaninf, QuantityType, TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef std::complex<RawType> ComplexRawType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<ComplexRawType>::type ComplexQuantityType;

  BOOST_CHECK( !Utility::QuantityTraits<QuantityType>::isnaninf( Utility::QuantityTraits<QuantityType>::max() ) );
  BOOST_CHECK( !Utility::isnaninf( Utility::QuantityTraits<QuantityType>::max() ) );
  
  BOOST_CHECK( !Utility::QuantityTraits<ComplexQuantityType>::isnaninf( Utility::QuantityTraits<ComplexQuantityType>::max() ) );
  BOOST_CHECK( !Utility::isnaninf( Utility::QuantityTraits<ComplexQuantityType>::max() ) );

  BOOST_CHECK( !Utility::QuantityTraits<QuantityType>::isnaninf( Utility::QuantityTraits<QuantityType>::min() ) );
  BOOST_CHECK( !Utility::isnaninf( Utility::QuantityTraits<QuantityType>::min() ) );
  
  BOOST_CHECK( !Utility::QuantityTraits<ComplexQuantityType>::isnaninf( Utility::QuantityTraits<ComplexQuantityType>::min() ) );
  BOOST_CHECK( !Utility::isnaninf( Utility::QuantityTraits<ComplexQuantityType>::min() ) );
  
  BOOST_CHECK( !Utility::QuantityTraits<QuantityType>::isnaninf( Utility::QuantityTraits<QuantityType>::lowest() ) );
  BOOST_CHECK( !Utility::isnaninf( Utility::QuantityTraits<QuantityType>::lowest() ) );
  
  BOOST_CHECK( !Utility::QuantityTraits<ComplexQuantityType>::isnaninf( Utility::QuantityTraits<ComplexQuantityType>::lowest() ) );
  BOOST_CHECK( !Utility::isnaninf( Utility::QuantityTraits<ComplexQuantityType>::lowest() ) );
}

//---------------------------------------------------------------------------//
// Check that the square root of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( sqrt_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::sqrt( T(0) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::sqrt( T(0) ), RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::sqrt( T(1) ),
                     RawFloatingPointType(1) );
  BOOST_CHECK_EQUAL( Utility::sqrt( T(1) ), RawFloatingPointType(1) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::sqrt( T(2) ),
                     RawFloatingPointType(std::sqrt(2)) );
  BOOST_CHECK_EQUAL( Utility::sqrt(T(2)), RawFloatingPointType(std::sqrt(2)) );

  // Check that the sqrt of complex types can be calculated
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(0), T(0) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(0), T(0) ) ) );
  BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(0), T(0) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(0), T(0) ) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(1), T(0) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(1), T(0) ) ) );
  BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(1), T(0) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(1), T(0) ) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(0), T(1) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(0), T(1) ) ) );
  BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(0), T(1) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(0), T(1) ) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(1), T(1) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(1), T(1) ) ) );
  BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(1), T(1) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(1), T(1) ) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(2), T(0) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(2), T(0) ) ) );
  BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(2), T(0) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(2), T(0) ) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(0), T(2) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(0), T(2) ) ) );
  BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(0), T(2) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(0), T(2) ) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(2), T(2) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(2), T(2) ) ) );
  BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(2), T(2) ) ),
                     std::sqrt( ComplexRawFloatingPointType( T(2), T(2) ) ) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK( Utility::isnaninf( Utility::QuantityTraits<T>::sqrt( T(-1) ) ) );
    BOOST_CHECK( Utility::isnaninf( Utility::sqrt( T(-1) ) ) );
    
    BOOST_CHECK( Utility::isnaninf( Utility::QuantityTraits<T>::sqrt( T(-2) ) ) );
    BOOST_CHECK( Utility::isnaninf( Utility::sqrt( T(-2) ) ) );

    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(-1), T(0) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(-1), T(0) ) ) );
    BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(-1), T(0) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(-1), T(0) ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(0), T(-1) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(0), T(-1) ) ) );
    BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(0), T(-1) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(0), T(-1) ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(-1), T(1) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(-1), T(1) ) ) );
    BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(-1), T(1) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(-1), T(1) ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(1), T(-1) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(1), T(-1) ) ) );
    BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(1), T(-1) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(1), T(-1) ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(-1), T(-1) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(-1), T(-1) ) ) );
    BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(-1), T(-1) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(-1), T(-1) ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(-2), T(0) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(-2), T(0) ) ) );
    BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(-2), T(0) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(-2), T(0) ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(0), T(-2) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(0), T(-2) ) ) );
    BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(0), T(-2) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(0), T(-2) ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(-2), T(2) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(-2), T(2) ) ) );
    BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(-2), T(2) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(-2), T(2) ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(2), T(-2) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(2), T(-2) ) ) );
    BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(2), T(-2) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(2), T(-2) ) ) );
    
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::sqrt( std::complex<T>( T(-2), T(-2) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(-2), T(-2) ) ) );
    BOOST_CHECK_EQUAL( Utility::sqrt( std::complex<T>( T(-2), T(-2) ) ),
                       std::sqrt( ComplexRawFloatingPointType( T(-2), T(-2) ) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the square root of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( _sqrt, QuantityType, TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<QuantityType>::FloatingPointQuantityType FloatingPointQuantityType;
  typedef std::complex<RawType> ComplexRawType;
  typedef std::complex<RawFloatingPointType> ComplexRawFloatingPointType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;
  typedef typename Utility::QuantityTraits<ComplexQuantityType>::FloatingPointQuantityType ComplexFloatingPointQuantityType;
  typedef std::is_same<RawFloatingPointType,float> IsRawFloatingPointTypeFloat;
  
  RawFloatingPointType tolerance = IsRawFloatingPointTypeFloat::value ? 1e-6 : 1e-12;
  
  // Check that the returned type from the sqrt method is correct
  BOOST_CHECK( (std::is_same<decltype(Utility::QuantityTraits<QuantityType>::sqrt( Utility::QuantityTraits<QuantityType>::zero() )),typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,2>::AsFloatingPointType>::value) );
  BOOST_CHECK( (std::is_same<decltype(Utility::sqrt( Utility::QuantityTraits<QuantityType>::zero() )),typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,2>::AsFloatingPointType>::value) );

  // Check that the sqrt method calculates the correct value
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::sqrt( Utility::QuantityTraits<QuantityType>::zero() )*
                     Utility::QuantityTraits<QuantityType>::sqrt( Utility::QuantityTraits<QuantityType>::zero() ),
                     Utility::QuantityTraits<FloatingPointQuantityType>::zero() );
  BOOST_CHECK_EQUAL( Utility::sqrt( Utility::QuantityTraits<QuantityType>::zero() )*
                     Utility::sqrt( Utility::QuantityTraits<QuantityType>::zero() ),
                     Utility::QuantityTraits<FloatingPointQuantityType>::zero() );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::sqrt( Utility::QuantityTraits<QuantityType>::one() )*
                     Utility::QuantityTraits<QuantityType>::sqrt( Utility::QuantityTraits<QuantityType>::one() ),
                     Utility::QuantityTraits<FloatingPointQuantityType>::one() );
  BOOST_CHECK_EQUAL( Utility::sqrt( Utility::QuantityTraits<QuantityType>::one() )*
                     Utility::sqrt( Utility::QuantityTraits<QuantityType>::one() ),
                     Utility::QuantityTraits<FloatingPointQuantityType>::one() );
  
  // We can't do floating-point comparisons with quantity types in the boost
  // test framework so we will compare raw values instead
  BOOST_CHECK_CLOSE_FRACTION( Utility::QuantityTraits<QuantityType>::sqrt( QuantityType::from_value( 2 ) ).value(),
                              std::sqrt(2),
                              tolerance );
  BOOST_CHECK_CLOSE_FRACTION( Utility::sqrt( QuantityType::from_value( 2 ) ).value(),
                              std::sqrt(2),
                              tolerance );

  // Check that the returned type from the sqrt method is correct (when using
  // complex types)
  BOOST_CHECK( (std::is_same<decltype(Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) )),typename Utility::QuantityTraits<ComplexQuantityType>::template GetQuantityToPowerType<1,2>::AsFloatingPointType>::value) );
               
  ComplexFloatingPointQuantityType complex_quantity =
    Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) );
  
  BOOST_CHECK_SMALL( Utility::real(complex_quantity).value(), tolerance );
  BOOST_CHECK_SMALL( Utility::imag(complex_quantity).value(), tolerance );

  complex_quantity =
    Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) );

  BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), 1.0, tolerance );
  BOOST_CHECK_SMALL( Utility::imag(complex_quantity).value(), tolerance );

  complex_quantity =
    Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) );

  BOOST_CHECK_SMALL( Utility::real(complex_quantity).value(), tolerance );
  BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), 1.0, tolerance );

  complex_quantity =
    Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( 1, 1 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( 1, 1 ) ) );

  BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), 1.0, tolerance );
  BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), 1.0, tolerance );

  complex_quantity =
    Utility::sqrt( ComplexQuantityType::from_value( ComplexRawType( 2, 2 ) ) )*
    Utility::sqrt( ComplexQuantityType::from_value( ComplexRawType( 2, 2 ) ) );

  BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), 2.0, tolerance );
  BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), 2.0, tolerance );
      
  if( Utility::QuantityTraits<QuantityType>::is_signed::value )
  {
    BOOST_CHECK( Utility::isnaninf( Utility::QuantityTraits<QuantityType>::sqrt( QuantityType::from_value( -1 ) ) ) );
    BOOST_CHECK( Utility::isnaninf( Utility::sqrt( QuantityType::from_value( -1 ) ) ) );
    
    BOOST_CHECK( Utility::isnaninf( Utility::QuantityTraits<QuantityType>::sqrt( QuantityType::from_value( -2 ) ) ) );
    BOOST_CHECK( Utility::isnaninf( Utility::sqrt( QuantityType::from_value( -2 ) ) ) );

    complex_quantity = 
      Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) )*
      Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) );

    BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), -1.0, tolerance );
    BOOST_CHECK_SMALL( Utility::imag(complex_quantity).value(), tolerance );

    complex_quantity =
      Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) )*
      Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) );

    BOOST_CHECK_SMALL( Utility::real(complex_quantity).value(), tolerance );
    BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), -1.0, tolerance );

    complex_quantity =
      Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( -1, -1 ) ) )*
      Utility::QuantityTraits<ComplexQuantityType>::sqrt( ComplexQuantityType::from_value( ComplexRawType( -1, -1 ) ) );

    BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), -1.0, tolerance );
    BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), -1.0, tolerance );

    complex_quantity =
      Utility::sqrt( ComplexQuantityType::from_value( ComplexRawType( -2, -2 ) ) )*
      Utility::sqrt( ComplexQuantityType::from_value( ComplexRawType( -2, -2 ) ) );

    BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), -2.0, tolerance );
    BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), -2.0, tolerance );
  }
}

//---------------------------------------------------------------------------//
// Check that the cube root of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( cbrt_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;
  typedef std::is_same<RawFloatingPointType,float> IsRawFloatingPointTypeFloat;

  typename std::conditional<IsRawFloatingPointTypeFloat::value,float,double>::type tolerance = IsRawFloatingPointTypeFloat::value ? 1e-6 : 1e-12;

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::cbrt( T(0) ),
                     RawFloatingPointType(0) );
  BOOST_CHECK_EQUAL( Utility::cbrt( T(0) ), RawFloatingPointType(0) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::cbrt( T(1) ),
                     RawFloatingPointType(1) );
  BOOST_CHECK_EQUAL( Utility::cbrt( T(1) ), RawFloatingPointType(1) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::cbrt( T(2) ),
                     RawFloatingPointType(std::cbrt(2)) );
  BOOST_CHECK_EQUAL( Utility::cbrt(T(2)), RawFloatingPointType(std::cbrt(2)) );

  // Check that the cbrt of complex types can be calculated
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(0), T(0) ) ),
                     ComplexRawFloatingPointType( T(0), T(0) ) );
  BOOST_CHECK_EQUAL( Utility::cbrt( std::complex<T>( T(0), T(0) ) ),
                     ComplexRawFloatingPointType( T(0), T(0) ) );
  
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(1), T(0) ) ),
                     ComplexRawFloatingPointType( T(1), T(0) ) );
  BOOST_CHECK_EQUAL( Utility::cbrt( std::complex<T>( T(1), T(0) ) ),
                     ComplexRawFloatingPointType( T(1), T(0) ) );

  ComplexRawFloatingPointType complex_value =
    Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(0), T(1) ) );
  
  BOOST_CHECK_CLOSE_FRACTION( complex_value.real(), std::sqrt(3.0)/2, tolerance );
  BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(), 0.5, tolerance );

  complex_value = Utility::cbrt( std::complex<T>( T(0), T(1) ) );
  
  BOOST_CHECK_CLOSE_FRACTION( complex_value.real(), std::sqrt(3.0)/2, tolerance );
  BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(), 0.5, tolerance );

  complex_value = Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(1), T(1) ) );

  BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                              (std::pow(2.0,2.0/3)/4)*(1+std::sqrt(3.0)),
                              tolerance );
  BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                              (std::pow(2.0,2.0/3)/4)*(-1+std::sqrt(3.0)),
                              tolerance );

  complex_value = Utility::cbrt( std::complex<T>( T(1), T(1) ) );

  BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                              (std::pow(2.0,2.0/3)/4)*(1+std::sqrt(3.0)),
                              tolerance );
  BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                              (std::pow(2.0,2.0/3)/4)*(-1+std::sqrt(3.0)),
                              tolerance );

  complex_value = Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(2), T(0) ) );

  BOOST_CHECK_CLOSE_FRACTION( complex_value.real(), std::cbrt(2.0), tolerance );
  BOOST_CHECK_SMALL( complex_value.imag(), tolerance );

  complex_value = Utility::cbrt( std::complex<T>( T(2), T(0) ) );

  BOOST_CHECK_CLOSE_FRACTION( complex_value.real(), std::cbrt(2.0), tolerance );
  BOOST_CHECK_SMALL( complex_value.imag(), tolerance );

  complex_value = Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(0), T(2) ) );

  BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                              std::cbrt(2.0)*std::sqrt(3.0)/2,
                              tolerance );
  BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                              std::cbrt(2.0)/2,
                              tolerance );

  complex_value = Utility::cbrt( std::complex<T>( T(0), T(2) ) );

  BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                              std::cbrt(2.0)*std::sqrt(3.0)/2,
                              tolerance );
  BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                              std::cbrt(2.0)/2,
                              tolerance );

  complex_value = Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(2), T(2) ) );

  BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                              0.5*(1+std::sqrt(3.0)),
                              tolerance );
  BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                              0.5*(-1+std::sqrt(3.0)),
                              tolerance );

  complex_value = Utility::cbrt( std::complex<T>( T(2), T(2) ) );

  BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                              0.5*(1+std::sqrt(3.0)),
                              tolerance );
  BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                              0.5*(-1+std::sqrt(3.0)),
                              tolerance );
  
  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::cbrt( T(-1) ),
                       RawFloatingPointType(-1) );
    BOOST_CHECK_EQUAL( Utility::cbrt( T(-1) ), RawFloatingPointType(-1) );
  
    BOOST_CHECK_EQUAL( Utility::QuantityTraits<T>::cbrt( T(-2) ),
                       RawFloatingPointType(std::cbrt(-2)) );
    BOOST_CHECK_EQUAL( Utility::cbrt(T(-2)), RawFloatingPointType(std::cbrt(-2)) );

    ComplexRawFloatingPointType complex_value =
      Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(-1), T(0) ) );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.real(), 0.5, tolerance );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                                std::sqrt(3.0)/2,
                                tolerance );

    complex_value = Utility::cbrt( std::complex<T>( T(-1), T(0) ) );

    BOOST_CHECK_CLOSE_FRACTION( complex_value.real(), 0.5, tolerance );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                                std::sqrt(3.0)/2,
                                tolerance );

    complex_value = Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(0), T(-1) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                                std::sqrt(3.0)/2,
                                tolerance );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(), -0.5, tolerance );

    complex_value = Utility::cbrt( std::complex<T>( T(0), T(-1) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                                std::sqrt(3.0)/2,
                                tolerance );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(), -0.5, tolerance );
    
    complex_value = Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(-1), T(-1) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                                std::pow(2.0,2.0/3)/2,
                                tolerance );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                                -std::pow(2.0,2.0/3)/2,
                                tolerance );

    complex_value = Utility::cbrt( std::complex<T>( T(-1), T(-1) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                                std::pow(2.0,2.0/3)/2,
                                tolerance );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                                -std::pow(2.0,2.0/3)/2,
                                tolerance );
    
    complex_value = Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(-2), T(0) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                                std::cbrt(2.0)/2,
                                tolerance );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                                std::cbrt(2.0)*std::sqrt(3.0)/2,
                                tolerance );

    complex_value = Utility::cbrt( std::complex<T>( T(-2), T(0) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                                std::cbrt(2.0)/2,
                                tolerance );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                                std::cbrt(2.0)*std::sqrt(3.0)/2,
                                tolerance );
    
    complex_value = Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(0), T(-2) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                                std::cbrt(2.0)*std::sqrt(3.0)/2,
                                tolerance );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                                -std::cbrt(2.0)/2,
                                tolerance );

    complex_value = Utility::cbrt( std::complex<T>( T(0), T(-2) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( complex_value.real(),
                                std::cbrt(2.0)*std::sqrt(3.0)/2,
                                tolerance );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(),
                                -std::cbrt(2.0)/2,
                                tolerance );
    
    complex_value = Utility::QuantityTraits<std::complex<T> >::cbrt( std::complex<T>( T(-2), T(-2) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( complex_value.real(), 1.0, tolerance );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(), -1.0, tolerance );

    complex_value = Utility::cbrt( std::complex<T>( T(-2), T(-2) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( complex_value.real(), 1.0, tolerance );
    BOOST_CHECK_CLOSE_FRACTION( complex_value.imag(), -1.0, tolerance );
  }
}

//---------------------------------------------------------------------------//
// Check that the cube root of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( _cbrt, QuantityType, TestBasicQuantityTypes )
{
  typedef typename Utility::QuantityTraits<QuantityType>::RawType RawType;
  typedef typename Utility::QuantityTraits<QuantityType>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<QuantityType>::FloatingPointQuantityType FloatingPointQuantityType;
  typedef std::complex<RawType> ComplexRawType;
  typedef std::complex<RawFloatingPointType> ComplexRawFloatingPointType;
  typedef typename Utility::QuantityTraits<QuantityType>::UnitType UnitType;
  typedef typename Utility::UnitTraits<UnitType>::template GetQuantityType<std::complex<RawType> >::type ComplexQuantityType;
  typedef typename Utility::QuantityTraits<ComplexQuantityType>::FloatingPointQuantityType ComplexFloatingPointQuantityType;
  typedef std::is_same<RawFloatingPointType,float> IsRawFloatingPointTypeFloat;
  
  RawFloatingPointType tolerance = IsRawFloatingPointTypeFloat::value ? 1e-6 : 1e-12;

  // Check that the returned type from the cbrt method is correct
  BOOST_CHECK( (std::is_same<decltype(Utility::QuantityTraits<QuantityType>::cbrt( Utility::QuantityTraits<QuantityType>::one() )),typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,3>::AsFloatingPointType>::value) );
  BOOST_CHECK( (std::is_same<decltype(Utility::cbrt( Utility::QuantityTraits<QuantityType>::one() ) ),typename Utility::QuantityTraits<QuantityType>::template GetQuantityToPowerType<1,3>::AsFloatingPointType>::value) );

  // Check that the cbrt method calculates the correct value (of one root)
  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::cbrt( Utility::QuantityTraits<QuantityType>::zero() )*
                     Utility::QuantityTraits<QuantityType>::cbrt( Utility::QuantityTraits<QuantityType>::zero() )*
                     Utility::QuantityTraits<QuantityType>::cbrt( Utility::QuantityTraits<QuantityType>::zero() ),
                     Utility::QuantityTraits<FloatingPointQuantityType>::zero() );
  BOOST_CHECK_EQUAL( Utility::cbrt( Utility::QuantityTraits<QuantityType>::zero() )*
                     Utility::cbrt( Utility::QuantityTraits<QuantityType>::zero() )*
                     Utility::cbrt( Utility::QuantityTraits<QuantityType>::zero() ),
                     Utility::QuantityTraits<FloatingPointQuantityType>::zero() );

  BOOST_CHECK_EQUAL( Utility::QuantityTraits<QuantityType>::cbrt( Utility::QuantityTraits<QuantityType>::one() )*
                     Utility::QuantityTraits<QuantityType>::cbrt( Utility::QuantityTraits<QuantityType>::one() )*
                     Utility::QuantityTraits<QuantityType>::cbrt( Utility::QuantityTraits<QuantityType>::one() ),
                     Utility::QuantityTraits<FloatingPointQuantityType>::one() );
  BOOST_CHECK_EQUAL( Utility::cbrt( Utility::QuantityTraits<QuantityType>::one() )*
                     Utility::cbrt( Utility::QuantityTraits<QuantityType>::one() )*
                     Utility::cbrt( Utility::QuantityTraits<QuantityType>::one() ),
                     Utility::QuantityTraits<FloatingPointQuantityType>::one() );

  // We can't do floating-point comparisons with quantity types in the boost
  // test framework so we will compare raw values instead
  BOOST_CHECK_CLOSE_FRACTION( Utility::QuantityTraits<QuantityType>::cbrt( QuantityType::from_value( 2 ) ).value(),
                              std::cbrt( 2.0 ),
                              tolerance );
  BOOST_CHECK_CLOSE_FRACTION( Utility::cbrt( QuantityType::from_value( 2 ) ).value(),
                              std::cbrt( 2.0 ),
                              tolerance );

  // Check that the returned type from the cbrt method is correct (when
  // using complex types)
  BOOST_CHECK( (std::is_same<decltype(Utility::QuantityTraits<ComplexQuantityType>::cbrt( Utility::QuantityTraits<ComplexQuantityType>::one() )),typename Utility::QuantityTraits<ComplexQuantityType>::template GetQuantityToPowerType<1,3>::AsFloatingPointType>::value) );
  BOOST_CHECK( (std::is_same<decltype(Utility::cbrt( Utility::QuantityTraits<ComplexQuantityType>::one() ) ),typename Utility::QuantityTraits<ComplexQuantityType>::template GetQuantityToPowerType<1,3>::AsFloatingPointType>::value) );

  ComplexFloatingPointQuantityType complex_quantity =
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) );

  BOOST_CHECK_SMALL( Utility::real(complex_quantity).value(), tolerance );
  BOOST_CHECK_SMALL( Utility::imag(complex_quantity).value(), tolerance );
  
  complex_quantity =
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) )*
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) )*
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, 0 ) ) );

  BOOST_CHECK_SMALL( Utility::real(complex_quantity).value(), tolerance );
  BOOST_CHECK_SMALL( Utility::imag(complex_quantity).value(), tolerance );

  complex_quantity =
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) );

  BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), 1.0, tolerance );
  BOOST_CHECK_SMALL( Utility::imag(complex_quantity).value(), tolerance );

  complex_quantity =
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) )*
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) )*
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 1, 0 ) ) );

  BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), 1.0, tolerance );
  BOOST_CHECK_SMALL( Utility::imag(complex_quantity).value(), tolerance );

  complex_quantity =
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) );

  BOOST_CHECK_SMALL( Utility::real(complex_quantity).value(), tolerance );
  BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), 1.0, tolerance );

  complex_quantity =
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) )*
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) )*
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, 1 ) ) );
  
  BOOST_CHECK_SMALL( Utility::real(complex_quantity).value(), tolerance );
  BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), 1.0, tolerance );

  complex_quantity =
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 1, 1 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 1, 1 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 1, 1 ) ) );

  BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), 1.0, tolerance );
  BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), 1.0, tolerance );

  complex_quantity =
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 1, 1 ) ) )*
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 1, 1 ) ) )*
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 1, 1 ) ) );
  
  BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), 1.0, tolerance );
  BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), 1.0, tolerance );

  complex_quantity =
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 2, 2 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 2, 2 ) ) )*
    Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 2, 2 ) ) );

  BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), 2.0, tolerance );
  BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), 2.0, tolerance );

  complex_quantity =
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 2, 2 ) ) )*
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 2, 2 ) ) )*
    Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 2, 2 ) ) );
  
  BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), 2.0, tolerance );
  BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), 2.0, tolerance );

  if( Utility::QuantityTraits<QuantityType>::is_signed::value )
  {
    BOOST_CHECK_CLOSE_FRACTION( Utility::QuantityTraits<QuantityType>::cbrt( QuantityType::from_value( -1 ) ).value(),
                                std::cbrt( -1.0 ),
                                tolerance );
    BOOST_CHECK_CLOSE_FRACTION( Utility::cbrt( QuantityType::from_value( -1 ) ).value(),
                                std::cbrt( -1.0 ),
                                tolerance );
    
    BOOST_CHECK_CLOSE_FRACTION( Utility::QuantityTraits<QuantityType>::cbrt( QuantityType::from_value( -2 ) ).value(),
                                std::cbrt( -2.0 ),
                                tolerance );
    BOOST_CHECK_CLOSE_FRACTION( Utility::cbrt( QuantityType::from_value( -2 ) ).value(),
                                std::cbrt( -2.0 ),
                                tolerance );

    complex_quantity =
      Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) )*
      Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) )*
      Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), -1.0, tolerance );
    BOOST_CHECK_SMALL( Utility::imag(complex_quantity).value(), tolerance );
    
    complex_quantity =
      Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) )*
      Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) )*
      Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( -1, 0 ) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), -1.0, tolerance );
    BOOST_CHECK_SMALL( Utility::imag(complex_quantity).value(), tolerance );
    
    complex_quantity =
      Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) )*
      Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) )*
      Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) );
    
    BOOST_CHECK_SMALL( Utility::real(complex_quantity).value(), tolerance );
    BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), -1.0, tolerance );
    
    complex_quantity =
      Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) )*
      Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) )*
      Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( 0, -1 ) ) );
    
    BOOST_CHECK_SMALL( Utility::real(complex_quantity).value(), tolerance );
    BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), -1.0, tolerance );
    
    complex_quantity =
      Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( -1, -1 ) ) )*
      Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( -1, -1 ) ) )*
      Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( -1, -1 ) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), -1.0, tolerance );
    BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), -1.0, tolerance );
    
    complex_quantity =
      Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( -1, -1 ) ) )*
      Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( -1, -1 ) ) )*
      Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( -1, -1 ) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), -1.0, tolerance );
    BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), -1.0, tolerance );
    
    complex_quantity =
      Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( -2, -2 ) ) )*
      Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( -2, -2 ) ) )*
      Utility::QuantityTraits<ComplexQuantityType>::cbrt( ComplexQuantityType::from_value( ComplexRawType( -2, -2 ) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), -2.0, tolerance );
    BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), -2.0, tolerance );
    
    complex_quantity =
      Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( -2, -2 ) ) )*
      Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( -2, -2 ) ) )*
      Utility::cbrt( ComplexQuantityType::from_value( ComplexRawType( -2, -2 ) ) );
    
    BOOST_CHECK_CLOSE_FRACTION( Utility::real(complex_quantity).value(), -2.0, tolerance );
    BOOST_CHECK_CLOSE_FRACTION( Utility::imag(complex_quantity).value(), -2.0, tolerance );
  }
}

//---------------------------------------------------------------------------//
// Check that a quantity to the zeroth power can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_0_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;

  // Special case: 0^0 -> we've defined this to be one
  BOOST_CHECK_EQUAL( Utility::rpow<0>( T(0) ), 1.0 );
  BOOST_CHECK_EQUAL( Utility::rpow<0>( std::complex<T>(0, 0) ),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,1>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-1>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,2>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-2>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,3>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-3>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,10>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,10>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-10>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-10>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( T(0) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  // Power = 0
  BOOST_CHECK_EQUAL( Utility::rpow<0>( T(1) ), 1.0 );
  BOOST_CHECK_EQUAL( Utility::rpow<0>( T(2) ), 1.0 );

  BOOST_CHECK_EQUAL( Utility::rpow<0>( std::complex<T>(1, 0) ),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<0>( std::complex<T>(0, 1) ),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<0>( std::complex<T>(1, 1) ),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<0>( std::complex<T>(2, 0) ),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<0>( std::complex<T>(0, 2) ),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<0>( std::complex<T>(2, 2) ),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,1>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,1>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,1>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-1>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-1>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-1>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,2>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,2>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,2>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-2>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-2>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-2>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,3>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,3>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,3>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-3>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-3>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-3>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,10>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,10>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,10>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,10>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,10>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,10>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,10>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,10>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-10>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-10>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-10>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-10>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-10>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-10>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-10>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-10>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( T(2) )), 1.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( std::complex<T>(2, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( std::complex<T>(0, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::rpow<0>( T(-1) ), 1.0 );
    BOOST_CHECK_EQUAL( Utility::rpow<0>( T(-2) ), 1.0 );
    
    BOOST_CHECK_EQUAL( Utility::rpow<0>( std::complex<T>(-1, 0) ),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<0>( std::complex<T>(0, -1) ),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<0>( std::complex<T>(-1, -1) ),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<0>( std::complex<T>(-2, -2) ),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,1>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,1>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-1>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-1>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-1>( std::complex<T>(0, 1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,2>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,2>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-2>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-2>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,3>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,3>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-3>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-3>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,10>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,10>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,10>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,10>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,10>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,10>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,10>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-10>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<0,-10>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-10>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-10>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-10>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<0,-10>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( T(-2) )), 1.0 );

    BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<0,-10>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
  }
}

//---------------------------------------------------------------------------//
// Check that rational power of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_1_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;
  
  BOOST_CHECK_EQUAL( Utility::rpow<1>( T(0) ), 0.0 );
  BOOST_CHECK_EQUAL( Utility::rpow<1>( T(1) ), 1.0 );
  BOOST_CHECK_EQUAL( Utility::rpow<1>( T(2) ), 2.0 );

  BOOST_CHECK_EQUAL( Utility::rpow<1>( std::complex<T>(0, 0)),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<1>( std::complex<T>(1, 0)),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<1>( std::complex<T>(0, 1)),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<1>( std::complex<T>(1, 1)),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<1>( std::complex<T>(2, 2)),
                     ComplexRawFloatingPointType(2.0, 2.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,1>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,1>( T(2) )), 2.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(2.0, 2.0) );


  BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( T(2) )), 2.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(2.0, 2.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-1>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-1>( T(2) )), 2.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(2.0, 2.0) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( T(2) )), 2.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(2.0, 2.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,2>( T(2) )), 2.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(2.0, 2.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( T(2) )), 2.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(2.0, 2.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-2>( T(2) )), 2.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(2.0, 2.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( T(2) )), 2.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(2.0, 2.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,3>( T(2) )), 2.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(2.0, 2.0) );
  
  
  BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( T(2) )), 2.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(2.0, 2.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-3>( T(2) )), 2.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(2.0, 2.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( T(2) )), 2.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(1.0, 1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(2.0, 2.0) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::rpow<1>( T(-1) ), -1.0 );
    BOOST_CHECK_EQUAL( Utility::rpow<1>( T(-2) ), -2.0 );
    
    BOOST_CHECK_EQUAL( Utility::rpow<1>( std::complex<T>(-1, 0)),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<1>( std::complex<T>(0, -1)),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<1>( std::complex<T>(-1, -1)),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<1>( std::complex<T>(-2, -2)),
                       ComplexRawFloatingPointType(-2.0, -2.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,1>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,1>( T(-2) )), -2.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-2.0, -2.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( T(-2) )), -2.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-2.0, -2.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-1>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-1>( T(-2) )), -2.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-2.0, -2.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( T(-2) )), -2.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-2.0, -2.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,2>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,2>( T(-2) )), -2.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-2.0, -2.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( T(-2) )), -2.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,2>( std::complex<T>(-2, -2) )),
                     ComplexRawFloatingPointType(-2.0, -2.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-2>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-2>( T(-2) )), -2.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-2.0, -2.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( T(-2) )), -2.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-2.0, -2.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,3>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,3>( T(-2) )), -2.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-2.0, -2.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( T(-2) )), -2.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-2.0, -2.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-3>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-3>( T(-2) )), -2.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-2.0, -2.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( T(-2) )), -2.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-1.0, -1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-2.0, -2.0) );
  }
}

//---------------------------------------------------------------------------//
// Check that rational power of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_neg1_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;
  
  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-1>( T(0) )) );
  BOOST_CHECK_EQUAL( Utility::rpow<-1>( T(1) ), 1.0 );
  BOOST_CHECK_EQUAL( Utility::rpow<-1>( T(2) ), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-1>( std::complex<T>(0, 0))) );
  BOOST_CHECK_EQUAL( Utility::rpow<-1>( std::complex<T>(1, 0)),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<-1>( std::complex<T>(0, 1)),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<-1>( std::complex<T>(1, 1)),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( Utility::rpow<-1>( std::complex<T>(2, 2)),
                     ComplexRawFloatingPointType(0.25, -0.25) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-1,1>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,1>( T(2) )), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<-1,1>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.25, -0.25) );


  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-1,1>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,1>( T(2) )), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-1,1>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.25, -0.25) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<1,-1>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,-1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,-1>( T(2) )), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<1,-1>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,-1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,-1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,-1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,-1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.25, -0.25) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<1,-1>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,-1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,-1>( T(2) )), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<1,-1>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,-1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,-1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,-1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,-1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.25, -0.25) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-2,2>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,2>( T(2) )), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<-2,2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.25, -0.25) );
  
  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-2,2>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,2>( T(2) )), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-2,2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.25, -0.25) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<2,-2>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,-2>( T(2) )), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<2,-2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.25, -0.25) );
  
  BOOST_CHECK( Utility::isnaninf(Utility::rpow<2,-2>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,-2>( T(2) )), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<2,-2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,-2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,-2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,-2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,-2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.25, -0.25) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-3,3>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,3>( T(2) )), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<-3,3>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.25, -0.25) );
  
  
  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-3,3>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,3>( T(2) )), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-3,3>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.25, -0.25) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<3,-3>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,-3>( T(2) )), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<3,-3>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.25, -0.25) );
  
  BOOST_CHECK( Utility::isnaninf(Utility::rpow<3,-3>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,-3>( T(2) )), 0.5 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<3,-3>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,-3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,-3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,-3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.5, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,-3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.25, -0.25) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::rpow<-1>( T(-1) ), -1.0 );
    BOOST_CHECK_EQUAL( Utility::rpow<-1>( T(-2) ), -0.5 );
    
    BOOST_CHECK_EQUAL( Utility::rpow<-1>( std::complex<T>(-1, 0)),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<-1>( std::complex<T>(0, -1)),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<-1>( std::complex<T>(-1, -1)),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( Utility::rpow<-1>( std::complex<T>(-2, -2)),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,1>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,1>( T(-2) )), -0.5 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,1>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,1>( T(-2) )), -0.5 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,-1>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,-1>( T(-2) )), -0.5 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,-1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,-1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,-1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,-1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<1,-1>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,-1>( T(-2) )), -0.5 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<1,-1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,-1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,-1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,-1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,2>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,2>( T(-2) )), -0.5 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,2>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,2>( T(-2) )), -0.5 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,-2>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,-2>( T(-2) )), -0.5 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<2,-2>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,-2>( T(-2) )), -0.5 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<2,-2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,-2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,-2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,-2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,3>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,3>( T(-2) )), -0.5 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,3>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,3>( T(-2) )), -0.5 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,-3>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,-3>( T(-2) )), -0.5 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<3,-3>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,-3>( T(-2) )), -0.5 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<3,-3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,-3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,-3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(-0.5, 0.5) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,-3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(-0.25, 0.25) );
  }
}

//---------------------------------------------------------------------------//
// Check that rational power of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_2_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;
  
  BOOST_CHECK_EQUAL( Utility::rpow<2>( T(0) ), 0.0 );
  BOOST_CHECK_EQUAL( Utility::rpow<2>( T(1) ), 1.0 );
  BOOST_CHECK_EQUAL( Utility::rpow<2>( T(2) ), 4.0 );

  BOOST_CHECK_EQUAL( Utility::rpow<2>( std::complex<T>(0, 0) ),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<2>( std::complex<T>(1, 0) ),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<2>( std::complex<T>(0, 1) ),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<2>( std::complex<T>(1, 1) ),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<2>( std::complex<T>(2, 2) ),
                     ComplexRawFloatingPointType(0.0, 8.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,1>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,1>( T(2) )), 4.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, 8.0) );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( T(2) )), 4.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, 8.0) );
  
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-1>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-1>( T(2) )), 4.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, 8.0) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( T(2) )), 4.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, 8.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<4,2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<4,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<4,2>( T(2) )), 4.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, 8.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( T(2) )), 4.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, 8.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-4,-2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-4,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-4,-2>( T(2) )), 4.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, 8.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( T(2) )), 4.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, 8.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,3>( T(2) )), 4.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, 8.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( T(2) )), 4.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, 8.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-3>( T(2) )), 4.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, 8.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( T(2) )), 4.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, 8.0) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::rpow<2>( T(-1) ), 1.0 );
    BOOST_CHECK_EQUAL( Utility::rpow<2>( T(-2) ), 4.0 );
    
    BOOST_CHECK_EQUAL( Utility::rpow<2>( std::complex<T>(-1, 0) ),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<2>( std::complex<T>(0, -1) ),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<2>( std::complex<T>(-1, -1) ),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<2>( std::complex<T>(-2, -2) ),
                       ComplexRawFloatingPointType(0.0, 8.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,1>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,1>( T(-2) )), 4.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,1>( std::complex<T>(0, -1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, 8.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( T(-2) )), 4.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, 8.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-1>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-1>( T(-2) )), 4.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, 8.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( T(-2) )), 4.0 );

    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, 8.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<4,2>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<4,2>( T(-2) )), 4.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, 8.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( T(-2) )), 4.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<4,2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, 8.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-4,-2>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-4,-2>( T(-2) )), 4.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, 8.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( T(-2) )), 4.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,-2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, 8.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,3>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,3>( T(-2) )), 4.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, 8.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( T(-2) )), 4.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, 8.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-3>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-3>( T(-2) )), 4.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, 8.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( T(-2) )), 4.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, 2.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, 8.0) );
  }
}

//---------------------------------------------------------------------------//
// Check that rational power of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_neg2_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;
  
  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-2>( T(0) )) );
  BOOST_CHECK_EQUAL( Utility::rpow<-2>( T(1) ), 1.0 );
  BOOST_CHECK_EQUAL( Utility::rpow<-2>( T(2) ), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( Utility::rpow<-2>( std::complex<T>(1, 0) ),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<-2>( std::complex<T>(0, 1) ),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<-2>( std::complex<T>(1, 1) ),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( Utility::rpow<-2>( std::complex<T>(2, 2) ),
                     ComplexRawFloatingPointType(0.0, -0.125) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-2,1>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,1>( T(2) )), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<-2,1>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, -0.125) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-2,1>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,1>( T(2) )), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-2,1>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, -0.125) );
  
  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<2,-1>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,-1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,-1>( T(2) )), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<2,-1>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, -0.125) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<2,-1>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,-1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,-1>( T(2) )), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<2,-1>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,-1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,-1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,-1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,-1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, -0.125) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-4,2>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-4,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-4,2>( T(2) )), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<-4,2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, -0.125) );
  
  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-4,2>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,2>( T(2) )), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-4,2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, -0.125) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<4,-2>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<4,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<4,-2>( T(2) )), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<4,-2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,-2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,-2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,-2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,-2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, -0.125) );
  
  BOOST_CHECK( Utility::isnaninf(Utility::rpow<4,-2>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,-2>( T(2) )), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<4,-2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,-2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,-2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,-2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,-2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, -0.125) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-6,3>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,3>( T(2) )), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<-6,3>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, -0.125) );
  
  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-6,3>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,3>( T(2) )), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-6,3>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, -0.125) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<6,-3>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,-3>( T(2) )), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<6,-3>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, -0.125) );
  
  BOOST_CHECK( Utility::isnaninf(Utility::rpow<6,-3>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,-3>( T(2) )), 0.25 );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<6,-3>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,-3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,-3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,-3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(0.0, -0.5) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,-3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(0.0, -0.125) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::rpow<-2>( T(-1) ), 1.0 );
    BOOST_CHECK_EQUAL( Utility::rpow<-2>( T(-2) ), 0.25 );
    
    BOOST_CHECK_EQUAL( Utility::rpow<-2>( std::complex<T>(-1, 0) ),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<-2>( std::complex<T>(0, -1) ),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<-2>( std::complex<T>(-1, -1) ),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( Utility::rpow<-2>( std::complex<T>(-2, -2) ),
                       ComplexRawFloatingPointType(0.0, -0.125) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,1>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,1>( T(-2) )), 0.25 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,1>( std::complex<T>(0, -1) )),
                     ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, -0.125) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,1>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,1>( T(-2) )), 0.25 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, -0.125) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,-1>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,-1>( T(-2) )), 0.25 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,-1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, -0.125) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<2,-1>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,-1>( T(-2) )), 0.25 );

    BOOST_CHECK_EQUAL( (Utility::rpow<2,-1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,-1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,-1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,-1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, -0.125) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-4,2>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-4,2>( T(-2) )), 0.25 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, -0.125) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,2>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,2>( T(-2) )), 0.25 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, -0.125) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<4,-2>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<4,-2>( T(-2) )), 0.25 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,-2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,-2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,-2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,-2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, -0.125) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<4,-2>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<4,-2>( T(-2) )), 0.25 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<4,-2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<4,-2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<4,-2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( (Utility::rpow<4,-2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, -0.125) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,3>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,3>( T(-2) )), 0.25 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, -0.125) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,3>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,3>( T(-2) )), 0.25 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, -0.125) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,-3>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,-3>( T(-2) )), 0.25 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, -0.125) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<6,-3>( T(-1) )), 1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,-3>( T(-2) )), 0.25 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<6,-3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,-3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,-3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(0.0, -0.5) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,-3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(0.0, -0.125) );
  }
}

//---------------------------------------------------------------------------//
// Check that rational power of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_3_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;
  
  BOOST_CHECK_EQUAL( Utility::rpow<3>( T(0) ), 0.0 );
  BOOST_CHECK_EQUAL( Utility::rpow<3>( T(1) ), 1.0 );
  BOOST_CHECK_EQUAL( Utility::rpow<3>( T(2) ), 8.0 );

  BOOST_CHECK_EQUAL( Utility::rpow<3>( std::complex<T>(0, 0) ),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<3>( std::complex<T>(1, 0) ),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<3>( std::complex<T>(0, 1) ),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<3>( std::complex<T>(1, 1) ),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( Utility::rpow<3>( std::complex<T>(2, 2) ),
                     ComplexRawFloatingPointType(-16.0, 16.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,1>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,1>( T(2) )), 8.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(-16.0, 16.0) );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( T(2) )), 8.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(-16.0, 16.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-1>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-1>( T(2) )), 8.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(-16.0, 16.0) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( T(2) )), 8.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(-16.0, 16.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,2>( T(2) )), 8.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(-16.0, 16.0) );
  
  
  BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( T(2) )), 8.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(-16.0, 16.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-2>( T(2) )), 8.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(-16.0, 16.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( T(2) )), 8.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(-16.0, 16.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<9,3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<9,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<9,3>( T(2) )), 8.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(-16.0, 16.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( T(2) )), 8.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(-16.0, 16.0) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-9,-3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-9,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-9,-3>( T(2) )), 8.0 );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(-16.0, 16.0) );
  
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( T(2) )), 8.0 );

  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( std::complex<T>(1, 0) )),
                     ComplexRawFloatingPointType(1.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( std::complex<T>(0, 1) )),
                     ComplexRawFloatingPointType(0.0, -1.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( std::complex<T>(1, 1) )),
                     ComplexRawFloatingPointType(-2.0, 2.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( std::complex<T>(2, 2) )),
                     ComplexRawFloatingPointType(-16.0, 16.0) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( Utility::rpow<3>( T(-1) ), -1.0 );
    BOOST_CHECK_EQUAL( Utility::rpow<3>( T(-2) ), -8.0 );
    
    BOOST_CHECK_EQUAL( Utility::rpow<3>( std::complex<T>(-1, 0) ),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<3>( std::complex<T>(0, -1) ),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<3>( std::complex<T>(-1, -1) ),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( Utility::rpow<3>( std::complex<T>(-2, -2) ),
                       ComplexRawFloatingPointType(16.0, -16.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,1>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,1>( T(-2) )), -8.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(16.0, -16.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( T(-2) )), -8.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(16.0, -16.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-1>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-1>( T(-2) )), -8.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(16.0, -16.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( T(-2) )), -8.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-1>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(16.0, -16.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,2>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,2>( T(-2) )), -8.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(16.0, -16.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( T(-2) )), -8.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(16.0, -16.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-2>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-2>( T(-2) )), -8.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(16.0, -16.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( T(-2) )), -8.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-2>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(16.0, -16.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<9,3>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<9,3>( T(-2) )), -8.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(16.0, -16.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( T(-2) )), -8.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<9,3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(16.0, -16.0) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-9,-3>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-9,-3>( T(-2) )), -8.0 );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(16.0, -16.0) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( T(-1) )), -1.0 );
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( T(-2) )), -8.0 );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( std::complex<T>(-1, 0) )),
                       ComplexRawFloatingPointType(-1.0, 0.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( std::complex<T>(0, -1) )),
                       ComplexRawFloatingPointType(0.0, 1.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( std::complex<T>(-1, -1) )),
                       ComplexRawFloatingPointType(2.0, -2.0) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,-3>( std::complex<T>(-2, -2) )),
                       ComplexRawFloatingPointType(16.0, -16.0) );
  }
}

//---------------------------------------------------------------------------//
// Check that rational power of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_1_over_2_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,2>( T(2) )),
                     RawFloatingPointType(std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,2>( std::complex<T>(1, 0) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,2>( std::complex<T>(0, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,2>( std::complex<T>(1, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,2>( std::complex<T>(2, 2) )),
                     std::sqrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<1,2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,2>( T(2) )),
                     RawFloatingPointType(std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<1,2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,2>( std::complex<T>(1, 0) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,2>( std::complex<T>(0, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,2>( std::complex<T>(1, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,2>( std::complex<T>(2, 2) )),
                     std::sqrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-2>( T(2) )),
                     RawFloatingPointType(std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-2>( std::complex<T>(1, 0) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-2>( std::complex<T>(0, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-2>( std::complex<T>(1, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-2>( std::complex<T>(2, 2) )),
                     std::sqrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-2>( T(2) )),
                     RawFloatingPointType(std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-2>( std::complex<T>(1, 0) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-2>( std::complex<T>(0, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-2>( std::complex<T>(1, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-2>( std::complex<T>(2, 2) )),
                     std::sqrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,4>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,4>( T(2) )),
                     RawFloatingPointType(std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,4>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,4>( std::complex<T>(1, 0) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,4>( std::complex<T>(0, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,4>( std::complex<T>(1, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,4>( std::complex<T>(2, 2) )),
                     std::sqrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,4>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,4>( T(2) )),
                     RawFloatingPointType(std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,4>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,4>( std::complex<T>(1, 0) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,4>( std::complex<T>(0, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,4>( std::complex<T>(1, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,4>( std::complex<T>(2, 2) )),
                     std::sqrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-4>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-4>( T(2) )),
                     RawFloatingPointType(std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-4>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-4>( std::complex<T>(1, 0) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-4>( std::complex<T>(0, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-4>( std::complex<T>(1, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-4>( std::complex<T>(2, 2) )),
                     std::sqrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-4>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-4>( T(2) )),
                     RawFloatingPointType(std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-4>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-4>( std::complex<T>(1, 0) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-4>( std::complex<T>(0, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-4>( std::complex<T>(1, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-4>( std::complex<T>(2, 2) )),
                     std::sqrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,6>( T(2) )),
                     RawFloatingPointType(std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,6>( std::complex<T>(1, 0) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,6>( std::complex<T>(0, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,6>( std::complex<T>(1, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,6>( std::complex<T>(2, 2) )),
                     std::sqrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,6>( T(2) )),
                     RawFloatingPointType(std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,6>( std::complex<T>(1, 0) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,6>( std::complex<T>(0, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,6>( std::complex<T>(1, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,6>( std::complex<T>(2, 2) )),
                     std::sqrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-6>( T(2) )),
                     RawFloatingPointType(std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-6>( std::complex<T>(1, 0) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-6>( std::complex<T>(0, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-6>( std::complex<T>(1, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-6>( std::complex<T>(2, 2) )),
                     std::sqrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-6>( T(2) )),
                     RawFloatingPointType(std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-6>( std::complex<T>(1, 0) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-6>( std::complex<T>(0, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-6>( std::complex<T>(1, 1) )),
                     std::sqrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-6>( std::complex<T>(2, 2) )),
                     std::sqrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<1,2>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<1,2>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,2>( std::complex<T>(-1, 0) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,2>( std::complex<T>(0, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,2>( std::complex<T>(-1, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,2>( std::complex<T>(-2, -2) )),
                       std::sqrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<1,2>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<1,2>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<1,2>( std::complex<T>(-1, 0) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,2>( std::complex<T>(0, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,2>( std::complex<T>(-1, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,2>( std::complex<T>(-2, -2) )),
                       std::sqrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-1,-2>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-1,-2>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-2>( std::complex<T>(-1, 0) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-2>( std::complex<T>(0, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-2>( std::complex<T>(-1, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-2>( std::complex<T>(-2, -2) )),
                       std::sqrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-1,-2>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-1,-2>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-2>( std::complex<T>(-1, 0) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-2>( std::complex<T>(0, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-2>( std::complex<T>(-1, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-2>( std::complex<T>(-2, -2) )),
                       std::sqrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<2,4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<2,4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,4>( std::complex<T>(-1, 0) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,4>( std::complex<T>(0, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,4>( std::complex<T>(-1, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,4>( std::complex<T>(-2, -2) )),
                       std::sqrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<2,4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<2,4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<2,4>( std::complex<T>(-1, 0) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,4>( std::complex<T>(0, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,4>( std::complex<T>(-1, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,4>( std::complex<T>(-2, -2) )),
                       std::sqrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-2,-4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-2,-4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-4>( std::complex<T>(-1, 0) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-4>( std::complex<T>(0, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-4>( std::complex<T>(-1, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-4>( std::complex<T>(-2, -2) )),
                       std::sqrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-2,-4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-2,-4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-4>( std::complex<T>(-1, 0) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-4>( std::complex<T>(0, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-4>( std::complex<T>(-1, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-4>( std::complex<T>(-2, -2) )),
                       std::sqrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<3,6>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<3,6>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,6>( std::complex<T>(-1, 0) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,6>( std::complex<T>(0, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,6>( std::complex<T>(-1, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,6>( std::complex<T>(-2, -2) )),
                       std::sqrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<3,6>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<3,6>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<3,6>( std::complex<T>(-1, 0) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,6>( std::complex<T>(0, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,6>( std::complex<T>(-1, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,6>( std::complex<T>(-2, -2) )),
                       std::sqrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-3,-6>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-3,-6>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-6>( std::complex<T>(-1, 0) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-6>( std::complex<T>(0, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-6>( std::complex<T>(-1, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-6>( std::complex<T>(-2, -2) )),
                       std::sqrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-3,-6>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-3,-6>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-6>( std::complex<T>(-1, 0) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-6>( std::complex<T>(0, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-6>( std::complex<T>(-1, -1) )),
                       std::sqrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-6>( std::complex<T>(-2, -2) )),
                       std::sqrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that rational power of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_1_over_3_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,3>( T(2) )),
                     RawFloatingPointType(Utility::cbrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,3>( std::complex<T>(1, 0) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,3>( std::complex<T>(0, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,3>( std::complex<T>(1, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,3>( std::complex<T>(2, 2) )),
                     Utility::cbrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( T(2) )),
                     RawFloatingPointType(Utility::cbrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( std::complex<T>(1, 0) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( std::complex<T>(0, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( std::complex<T>(1, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( std::complex<T>(2, 2) )),
                     Utility::cbrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-3>( T(2) )),
                     RawFloatingPointType(Utility::cbrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-3>( std::complex<T>(1, 0) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-3>( std::complex<T>(0, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-3>( std::complex<T>(1, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-3>( std::complex<T>(2, 2) )),
                     Utility::cbrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( T(2) )),
                     RawFloatingPointType(Utility::cbrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( std::complex<T>(1, 0) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( std::complex<T>(0, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( std::complex<T>(1, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( std::complex<T>(2, 2) )),
                     Utility::cbrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,6>( T(2) )),
                     RawFloatingPointType(Utility::cbrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,6>( std::complex<T>(1, 0) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,6>( std::complex<T>(0, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,6>( std::complex<T>(1, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,6>( std::complex<T>(2, 2) )),
                     Utility::cbrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( T(2) )),
                     RawFloatingPointType(Utility::cbrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( std::complex<T>(1, 0) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( std::complex<T>(0, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( std::complex<T>(1, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( std::complex<T>(2, 2) )),
                     Utility::cbrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-6>( T(2) )),
                     RawFloatingPointType(Utility::cbrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-6>( std::complex<T>(1, 0) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-6>( std::complex<T>(0, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-6>( std::complex<T>(1, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-6>( std::complex<T>(2, 2) )),
                     Utility::cbrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( T(2) )),
                     RawFloatingPointType(Utility::cbrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( std::complex<T>(1, 0) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( std::complex<T>(0, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( std::complex<T>(1, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( std::complex<T>(2, 2) )),
                     Utility::cbrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,9>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,9>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,9>( T(2) )),
                     RawFloatingPointType(Utility::cbrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,9>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,9>( std::complex<T>(1, 0) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,9>( std::complex<T>(0, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,9>( std::complex<T>(1, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,9>( std::complex<T>(2, 2) )),
                     Utility::cbrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( T(2) )),
                     RawFloatingPointType(Utility::cbrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( std::complex<T>(1, 0) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( std::complex<T>(0, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( std::complex<T>(1, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( std::complex<T>(2, 2) )),
                     Utility::cbrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-9>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-9>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-9>( T(2) )),
                     RawFloatingPointType(Utility::cbrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-9>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-9>( std::complex<T>(1, 0) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-9>( std::complex<T>(0, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-9>( std::complex<T>(1, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-9>( std::complex<T>(2, 2) )),
                     Utility::cbrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( T(2) )),
                     RawFloatingPointType(Utility::cbrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( std::complex<T>(1, 0) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 0.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( std::complex<T>(0, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(0.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( std::complex<T>(1, 1) )),
                     Utility::cbrt( ComplexRawFloatingPointType(1.0, 1.0) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( std::complex<T>(2, 2) )),
                     Utility::cbrt( ComplexRawFloatingPointType(2.0, 2.0) ) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,3>( T(-1) )),
                       RawFloatingPointType(Utility::cbrt( -1.0 )) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,3>( T(-2) )),
                       RawFloatingPointType(Utility::cbrt( -2.0 )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,3>( std::complex<T>(-1, 0) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,3>( std::complex<T>(0, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,3>( std::complex<T>(-1, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,3>( std::complex<T>(-2, -2) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( T(-1) )),
                       RawFloatingPointType(Utility::cbrt( -1.0 )) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( T(-2) )),
                       RawFloatingPointType(Utility::cbrt( -2.0 )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( std::complex<T>(-1, 0) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( std::complex<T>(0, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( std::complex<T>(-1, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,3>( std::complex<T>(-2, -2) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-3>( T(-1) )),
                       RawFloatingPointType(Utility::cbrt( -1.0 )) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-3>( T(-2) )),
                       RawFloatingPointType(Utility::cbrt( -2.0 )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-3>( std::complex<T>(-1, 0) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-3>( std::complex<T>(0, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-3>( std::complex<T>(-1, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-3>( std::complex<T>(-2, -2) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( T(-1) )),
                       RawFloatingPointType(Utility::cbrt( -1.0 )) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( T(-2) )),
                       RawFloatingPointType(Utility::cbrt( -2.0 )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( std::complex<T>(-1, 0) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( std::complex<T>(0, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( std::complex<T>(-1, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-3>( std::complex<T>(-2, -2) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,6>( T(-1) )),
                       RawFloatingPointType(Utility::cbrt( -1.0 )) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,6>( T(-2) )),
                       RawFloatingPointType(Utility::cbrt( -2.0 )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,6>( std::complex<T>(-1, 0) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,6>( std::complex<T>(0, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,6>( std::complex<T>(-1, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,6>( std::complex<T>(-2, -2) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( T(-1) )),
                       RawFloatingPointType(Utility::cbrt( -1.0 )) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( T(-2) )),
                       RawFloatingPointType(Utility::cbrt( -2.0 )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( std::complex<T>(-1, 0) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( std::complex<T>(0, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( std::complex<T>(-1, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,6>( std::complex<T>(-2, -2) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-6>( T(-1) )),
                       RawFloatingPointType(Utility::cbrt( -1.0 )) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-6>( T(-2) )),
                       RawFloatingPointType(Utility::cbrt( -2.0 )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-6>( std::complex<T>(-1, 0) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-6>( std::complex<T>(0, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-6>( std::complex<T>(-1, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-6>( std::complex<T>(-2, -2) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( T(-1) )),
                       RawFloatingPointType(Utility::cbrt( -1.0 )) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( T(-2) )),
                       RawFloatingPointType(Utility::cbrt( -2.0 )) );
        
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( std::complex<T>(-1, 0) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( std::complex<T>(0, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( std::complex<T>(-1, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-6>( std::complex<T>(-2, -2) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,9>( T(-1) )),
                       RawFloatingPointType(Utility::cbrt( -1.0 )) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,9>( T(-2) )),
                       RawFloatingPointType(Utility::cbrt( -2.0 )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,9>( std::complex<T>(-1, 0) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,9>( std::complex<T>(0, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,9>( std::complex<T>(-1, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,9>( std::complex<T>(-2, -2) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( T(-1) )),
                       RawFloatingPointType(Utility::cbrt( -1.0 )) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( T(-2) )),
                       RawFloatingPointType(Utility::cbrt( -2.0 )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( std::complex<T>(-1, 0) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( std::complex<T>(0, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( std::complex<T>(-1, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,9>( std::complex<T>(-2, -2) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-9>( T(-1) )),
                       RawFloatingPointType(Utility::cbrt( -1.0 )) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-9>( T(-2) )),
                       RawFloatingPointType(Utility::cbrt( -2.0 )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-9>( std::complex<T>(-1, 0) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-9>( std::complex<T>(0, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-9>( std::complex<T>(-1, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-9>( std::complex<T>(-2, -2) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( T(-1) )),
                       RawFloatingPointType(Utility::cbrt( -1.0 )) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( T(-2) )),
                       RawFloatingPointType(Utility::cbrt( -2.0 )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( std::complex<T>(-1, 0) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, 0.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( std::complex<T>(0, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(0.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( std::complex<T>(-1, -1) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-1.0, -1.0) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-9>( std::complex<T>(-2, -2) )),
                       Utility::cbrt( ComplexRawFloatingPointType(-2.0, -2.0) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that rational power of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_1_over_4_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,4>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,4>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.25)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,4>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,4>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,4>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,4>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,4>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.25) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<1,4>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,4>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.25)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<1,4>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,4>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,4>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,4>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,4>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.25) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-4>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-4>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.25)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-4>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-4>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-4>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-4>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-4>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.25) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-4>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-4>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.25)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-4>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-4>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-4>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-4>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-4>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.25) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,8>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,8>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,8>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.25)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,8>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,8>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,8>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,8>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,8>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.25) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,8>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,8>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,8>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.25)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,8>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,8>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,8>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,8>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,8>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.25) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-8>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-8>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-8>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.25)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-8>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-8>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-8>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-8>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-8>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.25) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-8>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-8>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-8>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.25)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-8>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-8>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-8>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-8>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-8>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.25) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,12>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,12>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,12>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.25)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,12>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,12>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,12>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,12>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,12>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.25) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,12>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,12>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,12>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.25)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,12>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,12>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,12>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,12>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,12>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.25) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-12>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-12>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-12>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.25)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-12>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-12>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-12>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-12>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-12>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.25) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-12>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-12>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-12>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.25)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-12>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-12>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-12>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-12>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.25) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-12>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.25) ) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<1,4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<1,4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,4>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,4>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,4>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,4>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.25) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<1,4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<1,4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<1,4>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,4>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,4>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,4>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.25) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-1,-4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-1,-4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-4>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-4>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-4>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-4>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.25) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-1,-4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-1,-4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-4>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-4>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-4>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-4>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.25) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<2,8>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<2,8>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,8>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,8>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,8>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,8>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.25) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<2,8>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<2,8>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<2,8>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,8>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,8>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,8>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.25) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-2,-8>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-2,-8>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-8>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-8>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-8>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-8>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.25) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-2,-8>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-2,-8>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-8>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-8>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-8>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-8>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.25) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<3,12>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<3,12>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,12>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,12>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,12>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,12>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.25) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<3,12>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<3,12>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<3,12>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,12>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,12>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,12>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.25) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-3,-12>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-3,-12>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-12>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-12>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-12>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-12>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.25) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-3,-12>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-3,-12>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-12>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-12>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-12>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.25) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-12>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.25) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that rational power of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_1_over_5_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,5>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,5>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,5>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.2)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,5>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,5>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,5>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,5>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,5>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.2) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.2)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.2) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-5>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-5>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-5>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.2)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-5>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-5>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-5>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-5>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-5>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.2) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.2)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.2) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,10>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,10>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,10>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.2)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,10>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,10>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,10>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,10>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,10>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.2) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.2)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.2) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-10>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-10>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-10>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.2)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-10>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-10>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-10>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-10>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-10>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.2) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.2)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.2) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,15>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,15>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,15>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.2)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,15>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,15>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,15>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,15>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,15>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.2) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.2)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.2) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-15>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-15>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-15>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.2)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-15>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-15>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-15>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-15>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-15>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.2) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( T(2) )),
                     RawFloatingPointType(std::pow(2.0, 0.2)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(0.2) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(0.2) ) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,5>( T(-1) )),
                       RawFloatingPointType(-std::pow(1.0, 0.2)) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<1,5>( T(-2) )),
                       RawFloatingPointType(-std::pow(2.0, 0.2)) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,5>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,5>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType( 0.0, -1.0 ), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,5>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<1,5>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.2) ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( T(-1) )),
                       RawFloatingPointType(-std::pow(1.0, 0.2)) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( T(-2) )),
                       RawFloatingPointType(-std::pow(2.0, 0.2)) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType( 0.0, -1.0 ), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<1,5>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.2) ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-5>( T(-1) )),
                       RawFloatingPointType(-std::pow(1.0, 0.2)) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-1,-5>( T(-2) )),
                       RawFloatingPointType(-std::pow(2.0, 0.2)) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-5>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-5>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType( 0.0, -1.0 ), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-5>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-1,-5>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.2) ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( T(-1) )),
                       RawFloatingPointType(-std::pow(1.0, 0.2)) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( T(-2) )),
                       RawFloatingPointType(-std::pow(2.0, 0.2)) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType( 0.0, -1.0 ), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-1,-5>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.2) ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,10>( T(-1) )),
                       RawFloatingPointType(-std::pow(1.0, 0.2)) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,10>( T(-2) )),
                       RawFloatingPointType(-std::pow(2.0, 0.2)) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,10>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,10>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType( 0.0, -1.0 ), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,10>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,10>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.2) ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( T(-1) )),
                       RawFloatingPointType(-std::pow(1.0, 0.2)) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( T(-2) )),
                       RawFloatingPointType(-std::pow(2.0, 0.2)) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType( 0.0, -1.0 ), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,10>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.2) ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-10>( T(-1) )),
                       RawFloatingPointType(-std::pow(1.0, 0.2)) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-10>( T(-2) )),
                       RawFloatingPointType(-std::pow(2.0, 0.2)) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-10>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-10>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType( 0.0, -1.0 ), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-10>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-10>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.2) ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( T(-1) )),
                       RawFloatingPointType(-std::pow(1.0, 0.2)) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( T(-2) )),
                       RawFloatingPointType(-std::pow(2.0, 0.2)) );
        
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType( 0.0, -1.0 ), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-10>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.2) ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,15>( T(-1) )),
                       RawFloatingPointType(-std::pow(1.0, 0.2)) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,15>( T(-2) )),
                       RawFloatingPointType(-std::pow(2.0, 0.2)) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,15>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,15>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType( 0.0, -1.0 ), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,15>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,15>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.2) ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( T(-1) )),
                       RawFloatingPointType(-std::pow(1.0, 0.2)) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( T(-2) )),
                       RawFloatingPointType(-std::pow(2.0, 0.2)) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType( 0.0, -1.0 ), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,15>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.2) ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-15>( T(-1) )),
                       RawFloatingPointType(-std::pow(1.0, 0.2)) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-15>( T(-2) )),
                       RawFloatingPointType(-std::pow(2.0, 0.2)) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-15>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-15>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType( 0.0, -1.0 ), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-15>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-15>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.2) ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( T(-1) )),
                       RawFloatingPointType(-std::pow(1.0, 0.2)) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( T(-2) )),
                       RawFloatingPointType(-std::pow(2.0, 0.2)) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType( 0.0, -1.0 ), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(0.2) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-15>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(0.2) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that rational power of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_3_over_2_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,2>( T(2) )),
                     RawFloatingPointType(2*std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,2>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,2>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,2>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,2>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,2>( T(2) )),
                     RawFloatingPointType(2*std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<3,2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,2>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,2>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,2>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,2>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,-2>( T(2) )),
                     RawFloatingPointType(2*std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-2>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-2>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-2>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-2>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-2>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-2>( T(2) )),
                     RawFloatingPointType(2*std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-2>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-2>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-2>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-2>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,-2>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,4>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,4>( T(2) )),
                     RawFloatingPointType(2*std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,4>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,4>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,4>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,4>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,4>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<6,4>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,4>( T(2) )),
                     RawFloatingPointType(2*std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<6,4>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,4>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,4>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,4>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,4>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-4>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-4>( T(2) )),
                     RawFloatingPointType(2*std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-4>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-4>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-4>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-4>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-4>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-4>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-4>( T(2) )),
                     RawFloatingPointType(2*std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-4>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-4>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-4>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-4>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-4>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<9,6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<9,6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<9,6>( T(2) )),
                     RawFloatingPointType(2*std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,6>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,6>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,6>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,6>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<9,6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,6>( T(2) )),
                     RawFloatingPointType(2*std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<9,6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,6>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,6>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,6>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,6>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-9,-6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-9,-6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-9,-6>( T(2) )),
                     RawFloatingPointType(2*std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-6>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-6>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-6>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-6>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-6>( T(2) )),
                     RawFloatingPointType(2*std::sqrt(2.0)) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-6>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-6>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-6>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,-6>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<3,2>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<3,2>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,2>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,2>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,2>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,2>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<3,2>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<3,2>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<3,2>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,2>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,2>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,2>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-3,-2>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-3,-2>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-2>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-2>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-2>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,-2>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-3,-2>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-3,-2>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-2>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-2>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-2>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,-2>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<6,4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<6,4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,4>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,4>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,4>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,4>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<6,4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<6,4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<6,4>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,4>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,4>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,4>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-6,-4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-6,-4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-4>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-4>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-4>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-4>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-6,-4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-6,-4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-4>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-4>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-4>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-4>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<9,6>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<9,6>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,6>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,6>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,6>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,6>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<9,6>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<9,6>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<9,6>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<9,6>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<9,6>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<9,6>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-9,-6>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-9,-6>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-6>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-6>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-6>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,-6>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-9,-6>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-9,-6>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,-6>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,-6>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,-6>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,-6>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that rational power of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_neg3_over_2_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-3,2>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-3,2>( T(2) )),
                     RawFloatingPointType(1/(2*std::sqrt(2.0))) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<-3,2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,2>( std::complex<T>(1, 0) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,2>( std::complex<T>(0, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,2>( std::complex<T>(1, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,2>( std::complex<T>(2, 2) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-3,2>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,2>( T(2) )),
                     RawFloatingPointType(1/(2*std::sqrt(2.0))) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-3,2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,2>( std::complex<T>(1, 0) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,2>( std::complex<T>(0, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,2>( std::complex<T>(1, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-3,2>( std::complex<T>(2, 2) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<3,-2>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<3,-2>( T(2) )),
                     RawFloatingPointType(1/(2*std::sqrt(2.0))) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<3,-2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-2>( std::complex<T>(1, 0) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-2>( std::complex<T>(0, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-2>( std::complex<T>(1, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-2>( std::complex<T>(2, 2) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<3,-2>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,-2>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,-2>( T(2) )),
                     RawFloatingPointType(1/(2*std::sqrt(2.0))) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<3,-2>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,-2>( std::complex<T>(1, 0) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,-2>( std::complex<T>(0, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,-2>( std::complex<T>(1, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<3,-2>( std::complex<T>(2, 2) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-6,4>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,4>( T(2) )),
                     RawFloatingPointType(1/(2*std::sqrt(2.0))) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<-6,4>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,4>( std::complex<T>(1, 0) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,4>( std::complex<T>(0, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,4>( std::complex<T>(1, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,4>( std::complex<T>(2, 2) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-6,4>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,4>( T(2) )),
                     RawFloatingPointType(1/(2*std::sqrt(2.0))) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-6,4>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,4>( std::complex<T>(1, 0) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,4>( std::complex<T>(0, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,4>( std::complex<T>(1, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,4>( std::complex<T>(2, 2) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<6,-4>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,-4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,-4>( T(2) )),
                     RawFloatingPointType(1/(2*std::sqrt(2.0))) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<6,-4>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-4>( std::complex<T>(1, 0) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-4>( std::complex<T>(0, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-4>( std::complex<T>(1, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-4>( std::complex<T>(2, 2) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<6,-4>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,-4>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,-4>( T(2) )),
                     RawFloatingPointType(1/(2*std::sqrt(2.0))) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<6,-4>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,-4>( std::complex<T>(1, 0) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,-4>( std::complex<T>(0, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,-4>( std::complex<T>(1, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,-4>( std::complex<T>(2, 2) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-9,6>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-9,6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-9,6>( T(2) )),
                     RawFloatingPointType(1/(2*std::sqrt(2.0))) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<-9,6>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,6>( std::complex<T>(1, 0) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,6>( std::complex<T>(0, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,6>( std::complex<T>(1, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,6>( std::complex<T>(2, 2) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-9,6>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,6>( T(2) )),
                     RawFloatingPointType(1/(2*std::sqrt(2.0))) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<-9,6>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,6>( std::complex<T>(1, 0) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,6>( std::complex<T>(0, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,6>( std::complex<T>(1, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-9,6>( std::complex<T>(2, 2) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<9,-6>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<9,-6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<9,-6>( T(2) )),
                     RawFloatingPointType(1/(2*std::sqrt(2.0))) );

  BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<std::complex<T> >::template rpow<9,-6>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,-6>( std::complex<T>(1, 0) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,-6>( std::complex<T>(0, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,-6>( std::complex<T>(1, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,-6>( std::complex<T>(2, 2) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<9,-6>( T(0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,-6>( T(1) )), 1.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,-6>( T(2) )),
                     RawFloatingPointType(1/(2*std::sqrt(2.0))) );

  BOOST_CHECK( Utility::isnaninf(Utility::rpow<9,-6>( std::complex<T>(0, 0) )) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,-6>( std::complex<T>(1, 0) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,-6>( std::complex<T>(0, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,-6>( std::complex<T>(1, 1) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(1.5) ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<9,-6>( std::complex<T>(2, 2) )),
                     RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(1.5) ) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-3,2>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-3,2>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,2>( std::complex<T>(-1, 0) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,2>( std::complex<T>(0, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,2>( std::complex<T>(-1, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-3,2>( std::complex<T>(-2, -2) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-3,2>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-3,2>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,2>( std::complex<T>(-1, 0) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,2>( std::complex<T>(0, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,2>( std::complex<T>(-1, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-3,2>( std::complex<T>(-2, -2) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<3,-2>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<3,-2>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-2>( std::complex<T>(-1, 0) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-2>( std::complex<T>(0, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-2>( std::complex<T>(-1, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<3,-2>( std::complex<T>(-2, -2) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<3,-2>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<3,-2>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<3,-2>( std::complex<T>(-1, 0) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,-2>( std::complex<T>(0, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,-2>( std::complex<T>(-1, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<3,-2>( std::complex<T>(-2, -2) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-6,4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-6,4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,4>( std::complex<T>(-1, 0) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,4>( std::complex<T>(0, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,4>( std::complex<T>(-1, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,4>( std::complex<T>(-2, -2) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-6,4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-6,4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,4>( std::complex<T>(-1, 0) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,4>( std::complex<T>(0, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,4>( std::complex<T>(-1, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,4>( std::complex<T>(-2, -2) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<6,-4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<6,-4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-4>( std::complex<T>(-1, 0) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-4>( std::complex<T>(0, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-4>( std::complex<T>(-1, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,-4>( std::complex<T>(-2, -2) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<6,-4>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<6,-4>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<6,-4>( std::complex<T>(-1, 0) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,-4>( std::complex<T>(0, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,-4>( std::complex<T>(-1, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,-4>( std::complex<T>(-2, -2) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-9,6>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<-9,6>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,6>( std::complex<T>(-1, 0) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,6>( std::complex<T>(0, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,6>( std::complex<T>(-1, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-9,6>( std::complex<T>(-2, -2) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-9,6>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<-9,6>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,6>( std::complex<T>(-1, 0) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,6>( std::complex<T>(0, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,6>( std::complex<T>(-1, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-9,6>( std::complex<T>(-2, -2) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );

    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<9,-6>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::QuantityTraits<T>::template rpow<9,-6>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,-6>( std::complex<T>(-1, 0) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,-6>( std::complex<T>(0, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,-6>( std::complex<T>(-1, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<9,-6>( std::complex<T>(-2, -2) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
    
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<9,-6>( T(-1) )) );
    BOOST_CHECK( Utility::isnaninf(Utility::rpow<9,-6>( T(-2) )) );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<9,-6>( std::complex<T>(-1, 0) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<9,-6>( std::complex<T>(0, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<9,-6>( std::complex<T>(-1, -1) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(1.5) ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<9,-6>( std::complex<T>(-2, -2) )),
                       RawFloatingPointType(1)/std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(1.5) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that rational power of a quantity can be computed
BOOST_AUTO_TEST_CASE_TEMPLATE( rpow_2_over_3_basic, T, TestTypes )
{
  typedef typename Utility::QuantityTraits<T>::RawFloatingPointType RawFloatingPointType;
  typedef typename Utility::QuantityTraits<std::complex<T> >::RawFloatingPointType ComplexRawFloatingPointType;

  typedef std::is_same<RawFloatingPointType,float> IsRawFloatingPointTypeFloat;
  
  RawFloatingPointType tolerance = IsRawFloatingPointTypeFloat::value ? 1e-6 : 1e-12;

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,3>( T(1) )), 1.0 );
  BOOST_CHECK_CLOSE_FRACTION( (Utility::QuantityTraits<T>::template rpow<2,3>( T(2) )),
                              RawFloatingPointType(std::pow(2.0, 2.0/3)),
                              tolerance );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,3>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,3>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,3>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,3>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(2.0)/3 ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,3>( T(1) )), 1.0 );
  BOOST_CHECK_CLOSE_FRACTION( (Utility::rpow<2,3>( T(2) )),
                              RawFloatingPointType(std::pow(2.0, 2.0/3)),
                              tolerance );

  BOOST_CHECK_EQUAL( (Utility::rpow<2,3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,3>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,3>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,3>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<2,3>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(2.0)/3 ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-3>( T(1) )), 1.0 );
  BOOST_CHECK_CLOSE_FRACTION( (Utility::QuantityTraits<T>::template rpow<-2,-3>( T(2) )),
                              RawFloatingPointType(std::pow(2.0, 2.0/3)),
                              tolerance );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-3>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-3>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-3>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-3>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(2.0)/3 ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-3>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-3>( T(1) )), 1.0 );
  BOOST_CHECK_CLOSE_FRACTION( (Utility::rpow<-2,-3>( T(2) )),
                              RawFloatingPointType(std::pow(2.0, 2.0/3)),
                              tolerance );

  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-3>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-3>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-3>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-3>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-2,-3>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(2.0)/3 ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<4,6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<4,6>( T(1) )), 1.0 );
  BOOST_CHECK_CLOSE_FRACTION( (Utility::QuantityTraits<T>::template rpow<4,6>( T(2) )),
                              RawFloatingPointType(std::pow(2.0, 2.0/3)),
                              tolerance );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,6>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,6>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,6>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,6>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(2.0)/3 ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<4,6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,6>( T(1) )), 1.0 );
  BOOST_CHECK_CLOSE_FRACTION( (Utility::rpow<4,6>( T(2) )),
                              RawFloatingPointType(std::pow(2.0, 2.0/3)),
                              tolerance );

  BOOST_CHECK_EQUAL( (Utility::rpow<4,6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,6>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,6>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,6>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<4,6>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(2.0)/3 ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-4,-6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-4,-6>( T(1) )), 1.0 );
  BOOST_CHECK_CLOSE_FRACTION( (Utility::QuantityTraits<T>::template rpow<-4,-6>( T(2) )),
                              RawFloatingPointType(std::pow(2.0, 2.0/3)),
                              tolerance );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-6>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-6>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-6>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-6>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(2.0)/3 ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-6>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-6>( T(1) )), 1.0 );
  BOOST_CHECK_CLOSE_FRACTION( (Utility::rpow<-4,-6>( T(2) )),
                              RawFloatingPointType(std::pow(2.0, 2.0/3)),
                              tolerance );

  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-6>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-6>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-6>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-6>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-4,-6>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(2.0)/3 ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,9>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,9>( T(1) )), 1.0 );
  BOOST_CHECK_CLOSE_FRACTION( (Utility::QuantityTraits<T>::template rpow<6,9>( T(2) )),
                              RawFloatingPointType(std::pow(2.0, 2.0/3)),
                              tolerance );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,9>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,9>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,9>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,9>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,9>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(2.0)/3 ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<6,9>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,9>( T(1) )), 1.0 );
  BOOST_CHECK_CLOSE_FRACTION( (Utility::rpow<6,9>( T(2) )),
                              RawFloatingPointType(std::pow(2.0, 2.0/3)),
                              tolerance );

  BOOST_CHECK_EQUAL( (Utility::rpow<6,9>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,9>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,9>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,9>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<6,9>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(2.0)/3 ) );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-9>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-9>( T(1) )), 1.0 );
  BOOST_CHECK_CLOSE_FRACTION( (Utility::QuantityTraits<T>::template rpow<-6,-9>( T(2) )),
                              RawFloatingPointType(std::pow(2.0, 2.0/3)),
                              tolerance );

  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-9>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-9>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-9>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-9>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-9>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(2.0)/3 ) );

  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-9>( T(0) )), 0.0 );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-9>( T(1) )), 1.0 );
  BOOST_CHECK_CLOSE_FRACTION( (Utility::rpow<-6,-9>( T(2) )),
                              RawFloatingPointType(std::pow(2.0, 2.0/3)),
                              tolerance );

  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-9>( std::complex<T>(0, 0) )),
                     ComplexRawFloatingPointType(0.0, 0.0) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-9>( std::complex<T>(1, 0) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-9>( std::complex<T>(0, 1) )),
                     std::pow( ComplexRawFloatingPointType(0.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-9>( std::complex<T>(1, 1) )),
                     std::pow( ComplexRawFloatingPointType(1.0, 1.0), RawFloatingPointType(2.0)/3 ) );
  BOOST_CHECK_EQUAL( (Utility::rpow<-6,-9>( std::complex<T>(2, 2) )),
                     std::pow( ComplexRawFloatingPointType(2.0, 2.0), RawFloatingPointType(2.0)/3 ) );

  if( Utility::QuantityTraits<T>::is_signed::value )
  {
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<2,3>( T(-1) )),
                       RawFloatingPointType(1.0) );
    BOOST_CHECK_CLOSE_FRACTION( (Utility::QuantityTraits<T>::template rpow<2,3>( T(-2) )),
                                RawFloatingPointType(std::pow(2.0, 2.0/3)),
                                tolerance );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,3>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,3>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,3>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<2,3>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(2.0)/3 ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<2,3>( T(-1) )),
                       RawFloatingPointType(1.0) );
    BOOST_CHECK_CLOSE_FRACTION( (Utility::rpow<2,3>( T(-2) )),
                                RawFloatingPointType(std::pow(2.0, 2.0/3)),
                                tolerance );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<2,3>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,3>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,3>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<2,3>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(2.0)/3 ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-2,-3>( T(-1) )),
                       RawFloatingPointType(1.0) );
    BOOST_CHECK_CLOSE_FRACTION( (Utility::QuantityTraits<T>::template rpow<-2,-3>( T(-2) )),
                                RawFloatingPointType(std::pow(2.0, 2.0/3)),
                                tolerance );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-3>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-3>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-3>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-2,-3>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(2.0)/3 ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-3>( T(-1) )),
                       RawFloatingPointType(1.0) );
    BOOST_CHECK_CLOSE_FRACTION( (Utility::rpow<-2,-3>( T(-2) )),
                                RawFloatingPointType(std::pow(2.0, 2.0/3)),
                                tolerance );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-3>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-3>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-3>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-2,-3>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(2.0)/3 ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<4,6>( T(-1) )),
                       RawFloatingPointType(1.0) );
    BOOST_CHECK_CLOSE_FRACTION( (Utility::QuantityTraits<T>::template rpow<4,6>( T(-2) )),
                                RawFloatingPointType(std::pow(2.0, 2.0/3)),
                                tolerance );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,6>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,6>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,6>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<4,6>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(2.0)/3 ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<4,6>( T(-1) )),
                       RawFloatingPointType(1.0) );
    BOOST_CHECK_CLOSE_FRACTION( (Utility::rpow<4,6>( T(-2) )),
                                RawFloatingPointType(std::pow(2.0, 2.0/3)),
                                tolerance );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<4,6>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<4,6>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<4,6>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<4,6>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(2.0)/3 ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-4,-6>( T(-1) )),
                       RawFloatingPointType(1.0) );
    BOOST_CHECK_CLOSE_FRACTION( (Utility::QuantityTraits<T>::template rpow<-4,-6>( T(-2) )),
                                RawFloatingPointType(std::pow(2.0, 2.0/3)),
                                tolerance );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-6>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-6>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-6>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-4,-6>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(2.0)/3 ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<-4,-6>( T(-1) )),
                       RawFloatingPointType(1.0) );
    BOOST_CHECK_CLOSE_FRACTION( (Utility::rpow<-4,-6>( T(-2) )),
                                RawFloatingPointType(std::pow(2.0, 2.0/3)),
                                tolerance );
        
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,-6>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,-6>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,-6>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-4,-6>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(2.0)/3 ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<6,9>( T(-1) )),
                       RawFloatingPointType(1.0) );
    BOOST_CHECK_CLOSE_FRACTION( (Utility::QuantityTraits<T>::template rpow<6,9>( T(-2) )),
                                RawFloatingPointType(std::pow(2.0, 2.0/3)),
                                tolerance );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,9>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,9>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,9>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<6,9>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(2.0)/3 ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<6,9>( T(-1) )),
                       RawFloatingPointType(1.0) );
    BOOST_CHECK_CLOSE_FRACTION( (Utility::rpow<6,9>( T(-2) )),
                                RawFloatingPointType(std::pow(2.0, 2.0/3)),
                                tolerance );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<6,9>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,9>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,9>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<6,9>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(2.0)/3 ) );

    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<T>::template rpow<-6,-9>( T(-1) )),
                       RawFloatingPointType(1.0) );
    BOOST_CHECK_CLOSE_FRACTION( (Utility::QuantityTraits<T>::template rpow<-6,-9>( T(-2) )),
                                RawFloatingPointType(std::pow(2.0, 2.0/3)),
                                tolerance );
    
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-9>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-9>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-9>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::QuantityTraits<std::complex<T> >::template rpow<-6,-9>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(2.0)/3 ) );

    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-9>( T(-1) )),
                       RawFloatingPointType(1.0) );
    BOOST_CHECK_CLOSE_FRACTION( (Utility::rpow<-6,-9>( T(-2) )),
                                RawFloatingPointType(std::pow(2.0, 2.0/3)),
                                tolerance );
    
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-9>( std::complex<T>(-1, 0) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, 0.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-9>( std::complex<T>(0, -1) )),
                       std::pow( ComplexRawFloatingPointType(0.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-9>( std::complex<T>(-1, -1) )),
                       std::pow( ComplexRawFloatingPointType(-1.0, -1.0), RawFloatingPointType(2.0)/3 ) );
    BOOST_CHECK_EQUAL( (Utility::rpow<-6,-9>( std::complex<T>(-2, -2) )),
                       std::pow( ComplexRawFloatingPointType(-2.0, -2.0), RawFloatingPointType(2.0)/3 ) );
  }
}

//---------------------------------------------------------------------------//
// Check that a quantity can be initialized from a raw quantity
BOOST_AUTO_TEST_CASE_TEMPLATE( initializeQuantity_basic, T, TestTypes )
{

}

//---------------------------------------------------------------------------//
// Check that a quantity can be initialized from a raw quantity
BOOST_AUTO_TEST_CASE_TEMPLATE( initializeQuantity,
                               QuantityType,
                               TestQuantityTypes )
{

}

//---------------------------------------------------------------------------//
// Check that the value of a raw quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( getRawQuantity_basic, T, TestTypes )
{

}

//---------------------------------------------------------------------------//
// Check that the value of a raw quantity can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( getRawQuantity,
                               QuantityType,
                               TestQuantityTypes )
{

}

//---------------------------------------------------------------------------//
// Check that the value of a quantity can be set
BOOST_AUTO_TEST_CASE_TEMPLATE( setQuantity_basic, T, TestTypes )
{

}

//---------------------------------------------------------------------------//
// Check that the value of a quantity can be set
BOOST_AUTO_TEST_CASE_TEMPLATE( setQuantity, QuantityType, TestQuantityTypes )
{

}

//---------------------------------------------------------------------------//
// end tstQuantityTraits.cpp
//---------------------------------------------------------------------------//
