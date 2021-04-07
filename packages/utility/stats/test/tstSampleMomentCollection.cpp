//---------------------------------------------------------------------------//
//!
//! \file   tstSampleMomentCollection.cpp
//! \author Alex Robinson
//! \brief  The sample moment collection unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

// FRENSIE Includes
#include "Utility_SampleMomentCollection.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Template Typedefs
//---------------------------------------------------------------------------//
typedef std::tuple<double,
                   boost::units::quantity<boost::units::cgs::length>,
                   boost::units::quantity<boost::units::si::length> > TestingTypes;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the size of a collection can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollection, size, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SampleMomentCollection<T,1,2,3,4> empty_moment_collection;

  FRENSIE_CHECK_EQUAL( empty_moment_collection.size(), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( empty_moment_collection ).size()), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( empty_moment_collection ).size()), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( empty_moment_collection ).size()), 0 );

  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 10 );

  FRENSIE_CHECK_EQUAL( moment_collection.size(), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( moment_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( moment_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( moment_collection ).size()), 10 );
}

//---------------------------------------------------------------------------//
// Check that the a collection can be cleared
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollection, clear, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 10 );

  moment_collection.clear();

  FRENSIE_CHECK_EQUAL( moment_collection.size(), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( moment_collection ).size()), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( moment_collection ).size()), 0 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( moment_collection ).size()), 0 );
}

//---------------------------------------------------------------------------//
// Check that a moment can be returned using the standalone helper function
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollection, getMoment, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;

  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 10 );
  
  // Get the first moment
  Utility::SampleMoment<1,T> first_moment =
    Utility::getMoment<1>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(), 
                       Utility::QuantityTraits<ValueType1>::zero() );

  first_moment = Utility::getMoment<1>( moment_collection, 1 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::zero() );

  first_moment = Utility::getMoment<1>( moment_collection, 2 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::zero() );

  // Get the second moment
  Utility::SampleMoment<2,T> second_moment =
    Utility::getMoment<2>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::zero() );

  second_moment = Utility::getMoment<2>( moment_collection, 1 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::zero() );

  second_moment = Utility::getMoment<2>( moment_collection, 2 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::zero() );

  // Get the third moment
  Utility::SampleMoment<3,T> third_moment =
    Utility::getMoment<3>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::zero() );

  third_moment = Utility::getMoment<3>( moment_collection, 1 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::zero() );

  third_moment = Utility::getMoment<3>( moment_collection, 2 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::zero() );

  // Get the fourth moment
  Utility::SampleMoment<4,T> fourth_moment =
    Utility::getMoment<4>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::zero() );

  fourth_moment = Utility::getMoment<4>( moment_collection, 1 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::zero() );

  fourth_moment = Utility::getMoment<4>( moment_collection, 2 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::zero() );
}

//---------------------------------------------------------------------------//
// Check that the initialization constructor can be used
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollection, init_constructor, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection(
                           10,
                           Utility::QuantityTraits<ValueType1>::one()*10.,
                           Utility::QuantityTraits<ValueType2>::one()*100.,
                           Utility::QuantityTraits<ValueType3>::one()*1000.,
                           Utility::QuantityTraits<ValueType4>::one()*10000. );

  FRENSIE_CHECK_EQUAL( moment_collection.size(), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( moment_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( moment_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( moment_collection ).size()), 10 );

  // Get the first moment
  Utility::SampleMoment<1,T> first_moment =
    Utility::getMoment<1>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  first_moment = Utility::getMoment<1>( moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  // Get the second moment
  Utility::SampleMoment<2,T> second_moment =
    Utility::getMoment<2>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  second_moment = Utility::getMoment<2>( moment_collection, 9 );   

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  // Get the third moment
  Utility::SampleMoment<3,T> third_moment =
    Utility::getMoment<3>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  third_moment = Utility::getMoment<3>( moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  // Get the fourth moment
  Utility::SampleMoment<4,T> fourth_moment =
    Utility::getMoment<4>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  fourth_moment = Utility::getMoment<4>( moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );
}

//---------------------------------------------------------------------------//
// Check that the copy constructor can be used
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollection, copy_constructor, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection(
                           10,
                           Utility::QuantityTraits<ValueType1>::one()*10.,
                           Utility::QuantityTraits<ValueType2>::one()*100.,
                           Utility::QuantityTraits<ValueType3>::one()*1000.,
                           Utility::QuantityTraits<ValueType4>::one()*10000. );

  Utility::SampleMomentCollection<T,1,2,3,4>
    copy_moment_collection( moment_collection );

  FRENSIE_CHECK_EQUAL( copy_moment_collection.size(), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( copy_moment_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( copy_moment_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( copy_moment_collection ).size()), 10 );

  // Get the first moment
  Utility::SampleMoment<1,T> first_moment =
    Utility::getMoment<1>( copy_moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  first_moment = Utility::getMoment<1>( copy_moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  // Get the second moment
  Utility::SampleMoment<2,T> second_moment =
    Utility::getMoment<2>( copy_moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  second_moment = Utility::getMoment<2>( copy_moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  // Get the third moment
  Utility::SampleMoment<3,T> third_moment =
    Utility::getMoment<3>( copy_moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  third_moment = Utility::getMoment<3>( copy_moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  // Get the fourth moment
  Utility::SampleMoment<4,T> fourth_moment =
    Utility::getMoment<4>( copy_moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  fourth_moment = Utility::getMoment<4>( copy_moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );
}

//---------------------------------------------------------------------------//
// Check that the assignment operator can be used
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollection, assignment_operator, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection(
                           10,
                           Utility::QuantityTraits<ValueType1>::one()*10.,
                           Utility::QuantityTraits<ValueType2>::one()*100.,
                           Utility::QuantityTraits<ValueType3>::one()*1000.,
                           Utility::QuantityTraits<ValueType4>::one()*10000. );

  Utility::SampleMomentCollection<T,1,2,3,4>
    copy_moment_collection = moment_collection;

  FRENSIE_CHECK_EQUAL( copy_moment_collection.size(), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( copy_moment_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( copy_moment_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( copy_moment_collection ).size()), 10 );

  // Get the first moment
  Utility::SampleMoment<1,T> first_moment =
    Utility::getMoment<1>( copy_moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  first_moment = Utility::getMoment<1>( copy_moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  // Get the second moment
  Utility::SampleMoment<2,T> second_moment =
    Utility::getMoment<2>( copy_moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  second_moment = Utility::getMoment<2>( copy_moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  // Get the third moment
  Utility::SampleMoment<3,T> third_moment =
    Utility::getMoment<3>( copy_moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  third_moment = Utility::getMoment<3>( copy_moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  // Get the fourth moment
  Utility::SampleMoment<4,T> fourth_moment =
    Utility::getMoment<4>( copy_moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  fourth_moment = Utility::getMoment<4>( copy_moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );
}

//---------------------------------------------------------------------------//
// Check that a collection can be resized
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollection, resize, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection;

  moment_collection.resize( 10 );

  FRENSIE_CHECK_EQUAL( moment_collection.size(), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( moment_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( moment_collection ).size()), 10 );
  FRENSIE_CHECK_EQUAL( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( moment_collection ).size()), 10 );

  // Get the first moment
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  
  Utility::SampleMoment<1,T> first_moment =
    Utility::getMoment<1>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::zero() );

  first_moment = Utility::getMoment<1>( moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::zero() );

  // Get the second moment
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;

  Utility::SampleMoment<2,T> second_moment =
    Utility::getMoment<2>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::zero() );

  second_moment = Utility::getMoment<2>( moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::zero() );

  // Get the third moment
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;

  Utility::SampleMoment<3,T> third_moment =
    Utility::getMoment<3>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::zero() );

  third_moment = Utility::getMoment<3>( moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::zero() );

  // Get the fourth moment
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;

  Utility::SampleMoment<4,T> fourth_moment =
    Utility::getMoment<4>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::zero() );

  fourth_moment = Utility::getMoment<4>( moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::zero() );

  moment_collection.clear();

  // Resize with default values
  moment_collection.resize( 10,
                            Utility::QuantityTraits<ValueType1>::one()*10.,
                            Utility::QuantityTraits<ValueType2>::one()*100.,
                            Utility::QuantityTraits<ValueType3>::one()*1000.,
                            Utility::QuantityTraits<ValueType4>::one()*10000.);

  // Get the first moment
  first_moment = Utility::getMoment<1>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  first_moment = Utility::getMoment<1>( moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  // Get the second moment
  second_moment = Utility::getMoment<2>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  second_moment = Utility::getMoment<2>( moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  // Get the third moment
  third_moment = Utility::getMoment<3>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  third_moment = Utility::getMoment<3>( moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  // Get the fourth moment
  fourth_moment = Utility::getMoment<4>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  fourth_moment = Utility::getMoment<4>( moment_collection, 9 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );
}

//---------------------------------------------------------------------------//
// Check that a raw score can be added to the collection
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollection, addRawScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 3 );

  // Add a raw score to the first element moments
  moment_collection.addRawScore( 0, Utility::QuantityTraits<T>::one()*10. );

  // Add a raw score to all elements
  moment_collection.addRawScore( Utility::QuantityTraits<T>::one()*10. );

  // Get the first moment
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  
  Utility::SampleMoment<1,T> first_moment =
    Utility::getMoment<1>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*20. );

  first_moment = Utility::getMoment<1>( moment_collection, 1 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  first_moment = Utility::getMoment<1>( moment_collection, 2 );

  FRENSIE_CHECK_EQUAL( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  // Get the second moment
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;

  Utility::SampleMoment<2,T> second_moment =
    Utility::getMoment<2>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*200. );

  second_moment = Utility::getMoment<2>( moment_collection, 1 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  second_moment = Utility::getMoment<2>( moment_collection, 2 );

  FRENSIE_CHECK_EQUAL( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  // Get the third moment
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;

  Utility::SampleMoment<3,T> third_moment =
    Utility::getMoment<3>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*2000. );

  third_moment = Utility::getMoment<3>( moment_collection, 1 );

  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  third_moment = Utility::getMoment<3>( moment_collection, 2 );
  
  FRENSIE_CHECK_EQUAL( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  // Get the fourth moment
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;

  Utility::SampleMoment<4,T> fourth_moment =
    Utility::getMoment<4>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*20000. );

  fourth_moment = Utility::getMoment<4>( moment_collection, 1 );
  
  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  fourth_moment = Utility::getMoment<4>( moment_collection, 2 );

  FRENSIE_CHECK_EQUAL( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );
}

//---------------------------------------------------------------------------//
// Check that the current score can be returned using the standalone helper
// function
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollection, getCurrentScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 3 );

  // Add a raw score to the first element moments
  moment_collection.addRawScore( 0, Utility::QuantityTraits<T>::one()*10. );

  // Add a raw score to all elements
  moment_collection.addRawScore( Utility::QuantityTraits<T>::one()*10. );

  // Get the first moment
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  
  ValueType1 first_current_score = 
    Utility::getCurrentScore<1>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( first_current_score,
                       Utility::QuantityTraits<ValueType1>::one()*20. );

  first_current_score = Utility::getCurrentScore<1>( moment_collection, 1 );

  FRENSIE_CHECK_EQUAL( first_current_score,
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  first_current_score = Utility::getCurrentScore<1>( moment_collection, 2 );

  FRENSIE_CHECK_EQUAL( first_current_score,
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  // Reset the first moment
  Utility::getCurrentScore<1>( moment_collection, 0 ) =
    Utility::QuantityTraits<ValueType1>::zero();

  FRENSIE_CHECK_EQUAL( Utility::getCurrentScore<1>( moment_collection, 0 ),
                       Utility::QuantityTraits<ValueType1>::zero() );

  Utility::getCurrentScore<1>( moment_collection, 1 ) =
    Utility::QuantityTraits<ValueType1>::zero();

  FRENSIE_CHECK_EQUAL( Utility::getCurrentScore<1>( moment_collection, 1 ),
                       Utility::QuantityTraits<ValueType1>::zero() );

  Utility::getCurrentScore<1>( moment_collection, 2 ) =
    Utility::QuantityTraits<ValueType1>::zero();

  FRENSIE_CHECK_EQUAL( Utility::getCurrentScore<1>( moment_collection, 2 ),
                       Utility::QuantityTraits<ValueType1>::zero() );

  // Get the second moment
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;

  ValueType2 second_current_score = 
    Utility::getCurrentScore<2>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( second_current_score,
                       Utility::QuantityTraits<ValueType2>::one()*200. );

  second_current_score = Utility::getCurrentScore<2>( moment_collection, 1 );

  FRENSIE_CHECK_EQUAL( second_current_score,
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  second_current_score = Utility::getCurrentScore<2>( moment_collection, 2 );

  FRENSIE_CHECK_EQUAL( second_current_score,
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  // Reset the second moment
  Utility::getCurrentScore<2>( moment_collection, 0 ) =
    Utility::QuantityTraits<ValueType2>::zero();

  FRENSIE_CHECK_EQUAL( Utility::getCurrentScore<2>( moment_collection, 0 ),
                       Utility::QuantityTraits<ValueType2>::zero() );

  Utility::getCurrentScore<2>( moment_collection, 1 ) =
    Utility::QuantityTraits<ValueType2>::zero();

  FRENSIE_CHECK_EQUAL( Utility::getCurrentScore<2>( moment_collection, 1 ),
                       Utility::QuantityTraits<ValueType2>::zero() );

  Utility::getCurrentScore<2>( moment_collection, 2 ) =
    Utility::QuantityTraits<ValueType2>::zero();

  FRENSIE_CHECK_EQUAL( Utility::getCurrentScore<2>( moment_collection, 2 ),
                       Utility::QuantityTraits<ValueType2>::zero() );

  // Get the third moment
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;

  ValueType3 third_current_score = 
    Utility::getCurrentScore<3>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( third_current_score,
                       Utility::QuantityTraits<ValueType3>::one()*2000. );

  third_current_score = Utility::getCurrentScore<3>( moment_collection, 1 );

  FRENSIE_CHECK_EQUAL( third_current_score,
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  third_current_score = Utility::getCurrentScore<3>( moment_collection, 2 );
  
  FRENSIE_CHECK_EQUAL( third_current_score,
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  // Reset the third moment
  Utility::getCurrentScore<3>( moment_collection, 0 ) =
    Utility::QuantityTraits<ValueType3>::zero();

  FRENSIE_CHECK_EQUAL( Utility::getCurrentScore<3>( moment_collection, 0 ),
                       Utility::QuantityTraits<ValueType3>::zero() );

  Utility::getCurrentScore<3>( moment_collection, 1 ) =
    Utility::QuantityTraits<ValueType3>::zero();

  FRENSIE_CHECK_EQUAL( Utility::getCurrentScore<3>( moment_collection, 1 ),
                       Utility::QuantityTraits<ValueType3>::zero() );

  Utility::getCurrentScore<3>( moment_collection, 2 ) =
    Utility::QuantityTraits<ValueType3>::zero();

  FRENSIE_CHECK_EQUAL( Utility::getCurrentScore<3>( moment_collection, 2 ),
                       Utility::QuantityTraits<ValueType3>::zero() );

  // Get the fourth moment
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;

  ValueType4 fourth_current_score =
    Utility::getCurrentScore<4>( moment_collection, 0 );

  FRENSIE_CHECK_EQUAL( fourth_current_score,
                       Utility::QuantityTraits<ValueType4>::one()*20000. );

  fourth_current_score = Utility::getCurrentScore<4>( moment_collection, 1 );
  
  FRENSIE_CHECK_EQUAL( fourth_current_score,
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  fourth_current_score = Utility::getCurrentScore<4>( moment_collection, 2 );

  FRENSIE_CHECK_EQUAL( fourth_current_score,
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  // Reset the fourth moment
  Utility::getCurrentScore<4>( moment_collection, 0 ) =
    Utility::QuantityTraits<ValueType4>::zero();

  FRENSIE_CHECK_EQUAL( Utility::getCurrentScore<4>( moment_collection, 0 ),
                       Utility::QuantityTraits<ValueType4>::zero() );

  Utility::getCurrentScore<4>( moment_collection, 1 ) =
    Utility::QuantityTraits<ValueType4>::zero();

  FRENSIE_CHECK_EQUAL( Utility::getCurrentScore<4>( moment_collection, 1 ),
                       Utility::QuantityTraits<ValueType4>::zero() );

  Utility::getCurrentScore<4>( moment_collection, 2 ) =
    Utility::QuantityTraits<ValueType4>::zero();

  FRENSIE_CHECK_EQUAL( Utility::getCurrentScore<4>( moment_collection, 2 ),
                       Utility::QuantityTraits<ValueType4>::zero() );
}

//---------------------------------------------------------------------------//
// Check that the raw scores can be returned using the standalone helper func.
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollection, getCurrentScores, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 10 );

  // Get the raw score data for the first moments
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;

  ValueType1* first_raw_scores =
    Utility::getCurrentScores<1>( moment_collection );

  FRENSIE_CHECK_EQUAL( *first_raw_scores,
                       Utility::QuantityTraits<ValueType1>::zero() );
  FRENSIE_CHECK_EQUAL( *(first_raw_scores+9),
                       Utility::QuantityTraits<ValueType1>::zero() );

  // Get the raw score data for the second moments
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;

  ValueType2* second_raw_scores =
    Utility::getCurrentScores<2>( moment_collection ); 

  FRENSIE_CHECK_EQUAL( *second_raw_scores,
                       Utility::QuantityTraits<ValueType2>::zero() );
  FRENSIE_CHECK_EQUAL( *(second_raw_scores+9),
                       Utility::QuantityTraits<ValueType2>::zero() );

  // Get the raw score data for the third moments
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;

  ValueType3* third_raw_scores =
    Utility::getCurrentScores<3>( moment_collection );

  FRENSIE_CHECK_EQUAL( *third_raw_scores,
                       Utility::QuantityTraits<ValueType3>::zero() );
  FRENSIE_CHECK_EQUAL( *(third_raw_scores+9),
                       Utility::QuantityTraits<ValueType3>::zero() );

  // Get the raw score data for the fourth moments
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;

  ValueType4* fourth_raw_scores =
    Utility::getCurrentScores<4>( moment_collection );

  FRENSIE_CHECK_EQUAL( *fourth_raw_scores,
                       Utility::QuantityTraits<ValueType4>::zero() );
  FRENSIE_CHECK_EQUAL( *(fourth_raw_scores+9),
                       Utility::QuantityTraits<ValueType4>::zero() );
}

//---------------------------------------------------------------------------//
// Check that a moment collection can be archived
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentCollection, archive, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 3 );

  // Add a raw score to the first element moments
  moment_collection.addRawScore( 0, Utility::QuantityTraits<T>::one()*10. );

  // Add a raw score to all elements
  moment_collection.addRawScore( Utility::QuantityTraits<T>::one()*10. );

  std::ostringstream archive_ostream;

  {
    boost::archive::xml_oarchive archive( archive_ostream );

    FRENSIE_REQUIRE_NO_THROW( archive << boost::serialization::make_nvp( "collection", moment_collection ) );
  }

  Utility::SampleMomentCollection<T,1,2,3,4> extracted_moment_collection;

  {
    std::istringstream iss( archive_ostream.str() );

    boost::archive::xml_iarchive archive( iss );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "collection", extracted_moment_collection ) );
  }

  // Check that the first moments were archived successfully
  Utility::ArrayView<const typename Utility::SampleMoment<1,T>::ValueType> first_moments( Utility::getCurrentScores<1>( moment_collection ), moment_collection.size() );
  Utility::ArrayView<const typename Utility::SampleMoment<1,T>::ValueType> extracted_first_moments( Utility::getCurrentScores<1>( extracted_moment_collection ), extracted_moment_collection.size() );
  
  FRENSIE_CHECK_EQUAL( extracted_first_moments, first_moments );

  // Check that the second moments were archived successfully
  Utility::ArrayView<const typename Utility::SampleMoment<2,T>::ValueType> second_moments( Utility::getCurrentScores<2>( moment_collection ), moment_collection.size() );
  Utility::ArrayView<const typename Utility::SampleMoment<2,T>::ValueType> extracted_second_moments( Utility::getCurrentScores<2>( extracted_moment_collection ), extracted_moment_collection.size() );
  
  FRENSIE_CHECK_EQUAL( extracted_second_moments, second_moments );

  // Check that the third moments were archived successfully
  Utility::ArrayView<const typename Utility::SampleMoment<3,T>::ValueType> third_moments( Utility::getCurrentScores<3>( moment_collection ), moment_collection.size() );
  Utility::ArrayView<const typename Utility::SampleMoment<3,T>::ValueType> extracted_third_moments( Utility::getCurrentScores<3>( extracted_moment_collection ), extracted_moment_collection.size() );
  
  FRENSIE_CHECK_EQUAL( extracted_third_moments, third_moments );

  // Check that the fourth moments were archived successfully
  Utility::ArrayView<const typename Utility::SampleMoment<4,T>::ValueType> fourth_moments( Utility::getCurrentScores<4>( moment_collection ), moment_collection.size() );
  Utility::ArrayView<const typename Utility::SampleMoment<4,T>::ValueType> extracted_fourth_moments( Utility::getCurrentScores<4>( extracted_moment_collection ), extracted_moment_collection.size() );
  
  FRENSIE_CHECK_EQUAL( extracted_fourth_moments, fourth_moments );
}

//---------------------------------------------------------------------------//
// end tstSampleMomentCollection.cpp
//---------------------------------------------------------------------------//
