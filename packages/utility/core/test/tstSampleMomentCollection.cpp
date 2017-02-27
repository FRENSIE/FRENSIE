//---------------------------------------------------------------------------//
//!
//! \file   tstSampleMomentCollection.cpp
//! \author Alex Robinson
//! \brief  The sample moment collection unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/si/length.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_SampleMomentCollection.hpp"
#include "Utility_QuantityTraits.hpp"

typedef boost::units::quantity<boost::units::cgs::length> q_cm_double;
typedef boost::units::quantity<boost::units::si::length> q_m_double;

//---------------------------------------------------------------------------//
// Template Instantiation Macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_TEMPLATE_1_INSTANT( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, q_cm_double ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, q_m_double )

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the size of a collection can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMomentCollection, size, T )
{
  Utility::SampleMomentCollection<T,1,2,3,4> empty_moment_collection;

  TEST_EQUALITY_CONST( empty_moment_collection.size(), 0 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( empty_moment_collection ).size()), 0 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( empty_moment_collection ).size()), 0 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( empty_moment_collection ).size()), 0 );

  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 10 );

  TEST_EQUALITY_CONST( moment_collection.size(), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( moment_collection ).size()), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( moment_collection ).size()), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( moment_collection ).size()), 10 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMomentCollection, size );

//---------------------------------------------------------------------------//
// Check that the a collection can be cleared
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMomentCollection, clear, T )
{
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 10 );

  moment_collection.clear();

  TEST_EQUALITY_CONST( moment_collection.size(), 0 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( moment_collection ).size()), 0 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( moment_collection ).size()), 0 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( moment_collection ).size()), 0 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMomentCollection, clear );

//---------------------------------------------------------------------------//
// Check that a moment can be returned using the standalone helper function
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMomentCollection,
                                   getMoment,
                                   T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;

  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 10 );
  
  // Get the first moment
  Utility::SampleMoment<1,T> first_moment =
    Utility::getMoment<1>( moment_collection, 0 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(), 
                       Utility::QuantityTraits<ValueType1>::zero() );

  first_moment = Utility::getMoment<1>( moment_collection, 1 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::zero() );

  first_moment = Utility::getMoment<1>( moment_collection, 2 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::zero() );

  // Get the second moment
  Utility::SampleMoment<2,T> second_moment =
    Utility::getMoment<2>( moment_collection, 0 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::zero() );

  second_moment = Utility::getMoment<2>( moment_collection, 1 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::zero() );

  second_moment = Utility::getMoment<2>( moment_collection, 2 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::zero() );

  // Get the third moment
  Utility::SampleMoment<3,T> third_moment =
    Utility::getMoment<3>( moment_collection, 0 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::zero() );

  third_moment = Utility::getMoment<3>( moment_collection, 1 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::zero() );

  third_moment = Utility::getMoment<3>( moment_collection, 2 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::zero() );

  // Get the fourth moment
  Utility::SampleMoment<4,T> fourth_moment =
    Utility::getMoment<4>( moment_collection, 0 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::zero() );

  fourth_moment = Utility::getMoment<4>( moment_collection, 1 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::zero() );

  fourth_moment = Utility::getMoment<4>( moment_collection, 2 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::zero() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMomentCollection, getMoment );

//---------------------------------------------------------------------------//
// Check that the initialization constructor can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMomentCollection, init_constructor, T )
{
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

  TEST_EQUALITY_CONST( moment_collection.size(), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( moment_collection ).size()), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( moment_collection ).size()), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( moment_collection ).size()), 10 );

  // Get the first moment
  Utility::SampleMoment<1,T> first_moment =
    Utility::getMoment<1>( moment_collection, 0 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  first_moment = Utility::getMoment<1>( moment_collection, 9 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  // Get the second moment
  Utility::SampleMoment<2,T> second_moment =
    Utility::getMoment<2>( moment_collection, 0 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  second_moment = Utility::getMoment<2>( moment_collection, 9 );   

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  // Get the third moment
  Utility::SampleMoment<3,T> third_moment =
    Utility::getMoment<3>( moment_collection, 0 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  third_moment = Utility::getMoment<3>( moment_collection, 9 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  // Get the fourth moment
  Utility::SampleMoment<4,T> fourth_moment =
    Utility::getMoment<4>( moment_collection, 0 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  fourth_moment = Utility::getMoment<4>( moment_collection, 9 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMomentCollection, init_constructor );

//---------------------------------------------------------------------------//
// Check that the copy constructor can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMomentCollection, copy_constructor, T )
{
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

  TEST_EQUALITY_CONST( copy_moment_collection.size(), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( copy_moment_collection ).size()), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( copy_moment_collection ).size()), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( copy_moment_collection ).size()), 10 );

  // Get the first moment
  Utility::SampleMoment<1,T> first_moment =
    Utility::getMoment<1>( copy_moment_collection, 0 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  first_moment = Utility::getMoment<1>( copy_moment_collection, 9 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  // Get the second moment
  Utility::SampleMoment<2,T> second_moment =
    Utility::getMoment<2>( copy_moment_collection, 0 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  second_moment = Utility::getMoment<2>( copy_moment_collection, 9 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  // Get the third moment
  Utility::SampleMoment<3,T> third_moment =
    Utility::getMoment<3>( copy_moment_collection, 0 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  third_moment = Utility::getMoment<3>( copy_moment_collection, 9 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  // Get the fourth moment
  Utility::SampleMoment<4,T> fourth_moment =
    Utility::getMoment<4>( copy_moment_collection, 0 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  fourth_moment = Utility::getMoment<4>( copy_moment_collection, 9 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMomentCollection, copy_constructor );

//---------------------------------------------------------------------------//
// Check that the assignment operator can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMomentCollection, assignment_operator, T )
{
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

  TEST_EQUALITY_CONST( copy_moment_collection.size(), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( copy_moment_collection ).size()), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( copy_moment_collection ).size()), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( copy_moment_collection ).size()), 10 );

  // Get the first moment
  Utility::SampleMoment<1,T> first_moment =
    Utility::getMoment<1>( copy_moment_collection, 0 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  first_moment = Utility::getMoment<1>( copy_moment_collection, 9 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  // Get the second moment
  Utility::SampleMoment<2,T> second_moment =
    Utility::getMoment<2>( copy_moment_collection, 0 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  second_moment = Utility::getMoment<2>( copy_moment_collection, 9 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  // Get the third moment
  Utility::SampleMoment<3,T> third_moment =
    Utility::getMoment<3>( copy_moment_collection, 0 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  third_moment = Utility::getMoment<3>( copy_moment_collection, 9 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  // Get the fourth moment
  Utility::SampleMoment<4,T> fourth_moment =
    Utility::getMoment<4>( copy_moment_collection, 0 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  fourth_moment = Utility::getMoment<4>( copy_moment_collection, 9 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMomentCollection, assignment_operator );

//---------------------------------------------------------------------------//
// Check that a collection can be resized
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMomentCollection, resize, T )
{
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection;

  moment_collection.resize( 10 );

  TEST_EQUALITY_CONST( moment_collection.size(), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,2,3,4>&>( moment_collection ).size()), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,3,4>&>( moment_collection ).size()), 10 );
  TEST_EQUALITY_CONST( (dynamic_cast<Utility::SampleMomentCollection<T,4>&>( moment_collection ).size()), 10 );

  // Get the first moment
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  
  Utility::SampleMoment<1,T> first_moment =
    Utility::getMoment<1>( moment_collection, 0 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::zero() );

  first_moment = Utility::getMoment<1>( moment_collection, 9 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::zero() );

  // Get the second moment
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;

  Utility::SampleMoment<2,T> second_moment =
    Utility::getMoment<2>( moment_collection, 0 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::zero() );

  second_moment = Utility::getMoment<2>( moment_collection, 9 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::zero() );

  // Get the third moment
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;

  Utility::SampleMoment<3,T> third_moment =
    Utility::getMoment<3>( moment_collection, 0 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::zero() );

  third_moment = Utility::getMoment<3>( moment_collection, 9 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::zero() );

  // Get the fourth moment
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;

  Utility::SampleMoment<4,T> fourth_moment =
    Utility::getMoment<4>( moment_collection, 0 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::zero() );

  fourth_moment = Utility::getMoment<4>( moment_collection, 9 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
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

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  first_moment = Utility::getMoment<1>( moment_collection, 9 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  // Get the second moment
  second_moment = Utility::getMoment<2>( moment_collection, 0 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  second_moment = Utility::getMoment<2>( moment_collection, 9 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  // Get the third moment
  third_moment = Utility::getMoment<3>( moment_collection, 0 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  third_moment = Utility::getMoment<3>( moment_collection, 9 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  // Get the fourth moment
  fourth_moment = Utility::getMoment<4>( moment_collection, 0 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  fourth_moment = Utility::getMoment<4>( moment_collection, 9 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMomentCollection, resize );

//---------------------------------------------------------------------------//
// Check that a raw score can be added to the collection
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMomentCollection, addRawScore, T )
{
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 3 );

  // Add a raw score to the first element moments
  moment_collection.addRawScore( 0, Utility::QuantityTraits<T>::one()*10. );

  // Add a raw score to all elements
  moment_collection.addRawScore( Utility::QuantityTraits<T>::one()*10. );

  // Get the first moment
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  
  Utility::SampleMoment<1,T> first_moment =
    Utility::getMoment<1>( moment_collection, 0 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*20. );

  first_moment = Utility::getMoment<1>( moment_collection, 1 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  first_moment = Utility::getMoment<1>( moment_collection, 2 );

  TEST_EQUALITY_CONST( first_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  // Get the second moment
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;

  Utility::SampleMoment<2,T> second_moment =
    Utility::getMoment<2>( moment_collection, 0 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*200. );

  second_moment = Utility::getMoment<2>( moment_collection, 1 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  second_moment = Utility::getMoment<2>( moment_collection, 2 );

  TEST_EQUALITY_CONST( second_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  // Get the third moment
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;

  Utility::SampleMoment<3,T> third_moment =
    Utility::getMoment<3>( moment_collection, 0 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*2000. );

  third_moment = Utility::getMoment<3>( moment_collection, 1 );

  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  third_moment = Utility::getMoment<3>( moment_collection, 2 );
  
  TEST_EQUALITY_CONST( third_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  // Get the fourth moment
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;

  Utility::SampleMoment<4,T> fourth_moment =
    Utility::getMoment<4>( moment_collection, 0 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*20000. );

  fourth_moment = Utility::getMoment<4>( moment_collection, 1 );
  
  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  fourth_moment = Utility::getMoment<4>( moment_collection, 2 );

  TEST_EQUALITY_CONST( fourth_moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType4>::one()*10000. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMomentCollection, addRawScore );

//---------------------------------------------------------------------------//
// Check that the current score can be returned using the stanalone helper func
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMomentCollection,
                                   getCurrentScore,
                                   T )
{
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 3 );

  // Add a raw score to the first element moments
  moment_collection.addRawScore( 0, Utility::QuantityTraits<T>::one()*10. );

  // Add a raw score to all elements
  moment_collection.addRawScore( Utility::QuantityTraits<T>::one()*10. );

  // Get the first moment
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  
  ValueType1 first_current_score = 
    Utility::getCurrentScore<1>( moment_collection, 0 );

  TEST_EQUALITY_CONST( first_current_score,
                       Utility::QuantityTraits<ValueType1>::one()*20. );

  first_current_score = Utility::getCurrentScore<1>( moment_collection, 1 );

  TEST_EQUALITY_CONST( first_current_score,
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  first_current_score = Utility::getCurrentScore<1>( moment_collection, 2 );

  TEST_EQUALITY_CONST( first_current_score,
                       Utility::QuantityTraits<ValueType1>::one()*10. );

  // Reset the first moment
  Utility::getCurrentScore<1>( moment_collection, 0 ) =
    Utility::QuantityTraits<ValueType1>::zero();

  TEST_EQUALITY_CONST( Utility::getCurrentScore<1>( moment_collection, 0 ),
                       Utility::QuantityTraits<ValueType1>::zero() );

  Utility::getCurrentScore<1>( moment_collection, 1 ) =
    Utility::QuantityTraits<ValueType1>::zero();

  TEST_EQUALITY_CONST( Utility::getCurrentScore<1>( moment_collection, 1 ),
                       Utility::QuantityTraits<ValueType1>::zero() );

  Utility::getCurrentScore<1>( moment_collection, 2 ) =
    Utility::QuantityTraits<ValueType1>::zero();

  TEST_EQUALITY_CONST( Utility::getCurrentScore<1>( moment_collection, 2 ),
                       Utility::QuantityTraits<ValueType1>::zero() );

  // Get the second moment
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;

  ValueType2 second_current_score = 
    Utility::getCurrentScore<2>( moment_collection, 0 );

  TEST_EQUALITY_CONST( second_current_score,
                       Utility::QuantityTraits<ValueType2>::one()*200. );

  second_current_score = Utility::getCurrentScore<2>( moment_collection, 1 );

  TEST_EQUALITY_CONST( second_current_score,
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  second_current_score = Utility::getCurrentScore<2>( moment_collection, 2 );

  TEST_EQUALITY_CONST( second_current_score,
                       Utility::QuantityTraits<ValueType2>::one()*100. );

  // Reset the second moment
  Utility::getCurrentScore<2>( moment_collection, 0 ) =
    Utility::QuantityTraits<ValueType2>::zero();

  TEST_EQUALITY_CONST( Utility::getCurrentScore<2>( moment_collection, 0 ),
                       Utility::QuantityTraits<ValueType2>::zero() );

  Utility::getCurrentScore<2>( moment_collection, 1 ) =
    Utility::QuantityTraits<ValueType2>::zero();

  TEST_EQUALITY_CONST( Utility::getCurrentScore<2>( moment_collection, 1 ),
                       Utility::QuantityTraits<ValueType2>::zero() );

  Utility::getCurrentScore<2>( moment_collection, 2 ) =
    Utility::QuantityTraits<ValueType2>::zero();

  TEST_EQUALITY_CONST( Utility::getCurrentScore<2>( moment_collection, 2 ),
                       Utility::QuantityTraits<ValueType2>::zero() );

  // Get the third moment
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;

  ValueType3 third_current_score = 
    Utility::getCurrentScore<3>( moment_collection, 0 );

  TEST_EQUALITY_CONST( third_current_score,
                       Utility::QuantityTraits<ValueType3>::one()*2000. );

  third_current_score = Utility::getCurrentScore<3>( moment_collection, 1 );

  TEST_EQUALITY_CONST( third_current_score,
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  third_current_score = Utility::getCurrentScore<3>( moment_collection, 2 );
  
  TEST_EQUALITY_CONST( third_current_score,
                       Utility::QuantityTraits<ValueType3>::one()*1000. );

  // Reset the third moment
  Utility::getCurrentScore<3>( moment_collection, 0 ) =
    Utility::QuantityTraits<ValueType3>::zero();

  TEST_EQUALITY_CONST( Utility::getCurrentScore<3>( moment_collection, 0 ),
                       Utility::QuantityTraits<ValueType3>::zero() );

  Utility::getCurrentScore<3>( moment_collection, 1 ) =
    Utility::QuantityTraits<ValueType3>::zero();

  TEST_EQUALITY_CONST( Utility::getCurrentScore<3>( moment_collection, 1 ),
                       Utility::QuantityTraits<ValueType3>::zero() );

  Utility::getCurrentScore<3>( moment_collection, 2 ) =
    Utility::QuantityTraits<ValueType3>::zero();

  TEST_EQUALITY_CONST( Utility::getCurrentScore<3>( moment_collection, 2 ),
                       Utility::QuantityTraits<ValueType3>::zero() );

  // Get the fourth moment
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;

  ValueType4 fourth_current_score =
    Utility::getCurrentScore<4>( moment_collection, 0 );

  TEST_EQUALITY_CONST( fourth_current_score,
                       Utility::QuantityTraits<ValueType4>::one()*20000. );

  fourth_current_score = Utility::getCurrentScore<4>( moment_collection, 1 );
  
  TEST_EQUALITY_CONST( fourth_current_score,
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  fourth_current_score = Utility::getCurrentScore<4>( moment_collection, 2 );

  TEST_EQUALITY_CONST( fourth_current_score,
                       Utility::QuantityTraits<ValueType4>::one()*10000. );

  // Reset the fourth moment
  Utility::getCurrentScore<4>( moment_collection, 0 ) =
    Utility::QuantityTraits<ValueType4>::zero();

  TEST_EQUALITY_CONST( Utility::getCurrentScore<4>( moment_collection, 0 ),
                       Utility::QuantityTraits<ValueType4>::zero() );

  Utility::getCurrentScore<4>( moment_collection, 1 ) =
    Utility::QuantityTraits<ValueType4>::zero();

  TEST_EQUALITY_CONST( Utility::getCurrentScore<4>( moment_collection, 1 ),
                       Utility::QuantityTraits<ValueType4>::zero() );

  Utility::getCurrentScore<4>( moment_collection, 2 ) =
    Utility::QuantityTraits<ValueType4>::zero();

  TEST_EQUALITY_CONST( Utility::getCurrentScore<4>( moment_collection, 2 ),
                       Utility::QuantityTraits<ValueType4>::zero() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMomentCollection, getCurrentScore );

//---------------------------------------------------------------------------//
// Check that the raw scores can be returned using the standalone helper func.
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMomentCollection,
                                   getCurrentScores,
                                   T )
{
  Utility::SampleMomentCollection<T,1,2,3,4> moment_collection( 10 );

  // Get the raw score data for the first moments
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;

  ValueType1* first_raw_scores =
    Utility::getCurrentScores<1>( moment_collection );

  TEST_EQUALITY_CONST( *first_raw_scores,
                       Utility::QuantityTraits<ValueType1>::zero() );
  TEST_EQUALITY_CONST( *(first_raw_scores+9),
                       Utility::QuantityTraits<ValueType1>::zero() );

  // Get the raw score data for the second moments
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;

  ValueType2* second_raw_scores =
    Utility::getCurrentScores<2>( moment_collection ); 

  TEST_EQUALITY_CONST( *second_raw_scores,
                       Utility::QuantityTraits<ValueType2>::zero() );
  TEST_EQUALITY_CONST( *(second_raw_scores+9),
                       Utility::QuantityTraits<ValueType2>::zero() );

  // Get the raw score data for the third moments
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;

  ValueType3* third_raw_scores =
    Utility::getCurrentScores<3>( moment_collection );

  TEST_EQUALITY_CONST( *third_raw_scores,
                       Utility::QuantityTraits<ValueType3>::zero() );
  TEST_EQUALITY_CONST( *(third_raw_scores+9),
                       Utility::QuantityTraits<ValueType3>::zero() );

  // Get the raw score data for the fourth moments
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;

  ValueType4* fourth_raw_scores =
    Utility::getCurrentScores<4>( moment_collection );

  TEST_EQUALITY_CONST( *fourth_raw_scores,
                       Utility::QuantityTraits<ValueType4>::zero() );
  TEST_EQUALITY_CONST( *(fourth_raw_scores+9),
                       Utility::QuantityTraits<ValueType4>::zero() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMomentCollection, getCurrentScores );

//---------------------------------------------------------------------------//
// end tstSampleMomentCollection.cpp
//---------------------------------------------------------------------------//
