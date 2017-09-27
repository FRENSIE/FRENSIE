//---------------------------------------------------------------------------//
//!
//! \file   tstSampleMoment.cpp
//! \author Alex Robinson
//! \brief  The sample moment unit tests
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/si/length.hpp>

// FRENSIE Includes
#include "Utility_SampleMoment.hpp"
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
// Check that the current score of the moment can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_1, getCurrentScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T> moment_a;

  FRENSIE_CHECK_EQUAL( moment_a.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::zero() );

  Utility::SampleMoment<1,T>
    moment_b( Utility::QuantityTraits<ValueType>::one() );

  FRENSIE_CHECK_EQUAL( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

//---------------------------------------------------------------------------//
// Check that the current score of the moment can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_2, getCurrentScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType;

  Utility::SampleMoment<2,T> moment_a;

  FRENSIE_CHECK_EQUAL( moment_a.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::zero() );

  Utility::SampleMoment<2,T>
    moment_b( Utility::QuantityTraits<ValueType>::one() );

  FRENSIE_CHECK_EQUAL( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

//---------------------------------------------------------------------------//
// Check that the current score of the moment can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_3, getCurrentScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType;

  Utility::SampleMoment<3,T> moment_a;

  FRENSIE_CHECK_EQUAL( moment_a.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::zero() );

  Utility::SampleMoment<3,T>
    moment_b( Utility::QuantityTraits<ValueType>::one() );

  FRENSIE_CHECK_EQUAL( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

//---------------------------------------------------------------------------//
// Check that the current score of the moment can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_4, getCurrentScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType;

  Utility::SampleMoment<4,T> moment_a;

  FRENSIE_CHECK_EQUAL( moment_a.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::zero() );

  Utility::SampleMoment<4,T>
    moment_b( Utility::QuantityTraits<ValueType>::one() );

  FRENSIE_CHECK_EQUAL( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

//---------------------------------------------------------------------------//
// Check that the calculated moment can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_1, get, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T>
    moment( Utility::QuantityTraits<ValueType>::one() );

  FRENSIE_CHECK_EQUAL( moment.get( 10 ),
                       Utility::QuantityTraits<ValueType>::one()/10. );
}

//---------------------------------------------------------------------------//
// Check that the calculated moment can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_2, get, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType;

  Utility::SampleMoment<2,T>
    moment( Utility::QuantityTraits<ValueType>::one() );

  FRENSIE_CHECK_EQUAL( moment.get( 10 ),
                       Utility::QuantityTraits<ValueType>::one()/10. );
}

//---------------------------------------------------------------------------//
// Check that the calculated moment can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_3, get, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType;

  Utility::SampleMoment<3,T>
    moment( Utility::QuantityTraits<ValueType>::one() );

  FRENSIE_CHECK_EQUAL( moment.get( 10 ),
                       Utility::QuantityTraits<ValueType>::one()/10. );
}

//---------------------------------------------------------------------------//
// Check that the calculated moment can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_4, get, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType;

  Utility::SampleMoment<4,T>
    moment( Utility::QuantityTraits<ValueType>::one() );

  FRENSIE_CHECK_EQUAL( moment.get( 10 ),
                       Utility::QuantityTraits<ValueType>::one()/10. );
}

//---------------------------------------------------------------------------//
// Check that the copy constructor can be used
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_1, copy_constructor, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<1,T> moment_b( moment_a );

  FRENSIE_CHECK_EQUAL( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

//---------------------------------------------------------------------------//
// Check that the copy constructor can be used
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_2, copy_constructor, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType;

  Utility::SampleMoment<2,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<2,T> moment_b( moment_a );

  FRENSIE_CHECK_EQUAL( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

//---------------------------------------------------------------------------//
// Check that the copy constructor can be used
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_3, copy_constructor, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType;

  Utility::SampleMoment<3,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<3,T> moment_b( moment_a );

  FRENSIE_CHECK_EQUAL( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

//---------------------------------------------------------------------------//
// Check that the copy constructor can be used
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_4, copy_constructor, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType;

  Utility::SampleMoment<4,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<4,T> moment_b( moment_a );

  FRENSIE_CHECK_EQUAL( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

//---------------------------------------------------------------------------//
// Check that the assignment operator can be used
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_1, assignment_operator, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<1,T> moment_b = moment_a;

  FRENSIE_CHECK_EQUAL( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

//---------------------------------------------------------------------------//
// Check that the assignment operator can be used
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_2, assignment_operator, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType;

  Utility::SampleMoment<2,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<2,T> moment_b = moment_a;

  FRENSIE_CHECK_EQUAL( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

//---------------------------------------------------------------------------//
// Check that the assignment operator can be used
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_3, assignment_operator, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType;

  Utility::SampleMoment<3,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<3,T> moment_b = moment_a;

  FRENSIE_CHECK_EQUAL( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

//---------------------------------------------------------------------------//
// Check that the assignment operator can be used
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_4, assignment_operator, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType;

  Utility::SampleMoment<4,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<4,T> moment_b = moment_a;

  FRENSIE_CHECK_EQUAL( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

//---------------------------------------------------------------------------//
// Check that a raw score can be added to the moment
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_1, addRawScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T> moment;

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

//---------------------------------------------------------------------------//
// Check that a raw score can be added to the moment
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_2, addRawScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType;

  Utility::SampleMoment<2,T> moment;

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/4. );

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

//---------------------------------------------------------------------------//
// Check that a raw score can be added to the moment
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_3, addRawScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType;

  Utility::SampleMoment<3,T> moment;

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/8. );

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/4. );
}

//---------------------------------------------------------------------------//
// Check that a raw score can be added to the moment
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_4, addRawScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType;

  Utility::SampleMoment<4,T> moment;

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/16. );

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/8. );
}

//---------------------------------------------------------------------------//
// Check that a processed score can be added to the moment
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_1, addProcessedScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T> moment;

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

//---------------------------------------------------------------------------//
// Check that a processed score can be added to the moment
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_2, addProcessedScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType;

  Utility::SampleMoment<2,T> moment;

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

//---------------------------------------------------------------------------//
// Check that a processed score can be added to the moment
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_3, addProcessedScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType;

  Utility::SampleMoment<3,T> moment;

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

//---------------------------------------------------------------------------//
// Check that a processed score can be added to the moment
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_4, addProcessedScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType;

  Utility::SampleMoment<4,T> moment;

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  FRENSIE_CHECK_EQUAL( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

//---------------------------------------------------------------------------//
// Check that the mean can be calculated
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_Helpers, calculateMean, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T> moment( Utility::QuantityTraits<ValueType>::one()*10. );
  
  ValueType mean = Utility::calculateMean( moment, 100 );

  FRENSIE_CHECK_EQUAL( mean, Utility::QuantityTraits<ValueType>::one()*0.1 );
}

//---------------------------------------------------------------------------//
// Check that the variance can be calculated
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_Helpers, calculateVariance, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  
  Utility::SampleMoment<1,T> first_moment( Utility::QuantityTraits<ValueType1>::one()*10. );
  Utility::SampleMoment<2,T> second_moment( Utility::QuantityTraits<ValueType2>::one()*100. );

  ValueType2 variance =
    Utility::calculateVariance( first_moment, second_moment, 100 );

  FRENSIE_CHECK_EQUAL( variance, Utility::QuantityTraits<ValueType2>::one() );
}

//---------------------------------------------------------------------------//
// Check that the std dev can be calculated
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_Helpers, calculateStdDev, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  
  Utility::SampleMoment<1,T> first_moment( Utility::QuantityTraits<ValueType1>::one()*10. );
  Utility::SampleMoment<2,T> second_moment( Utility::QuantityTraits<ValueType2>::one()*100. );

  ValueType1 std_dev =
    Utility::calculateStdDev( first_moment, second_moment, 100 );

  FRENSIE_CHECK_EQUAL( std_dev, Utility::QuantityTraits<ValueType1>::one() );
}

//---------------------------------------------------------------------------//
// Check that the variance of the mean can be calculated
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_Helpers, calculateVarianceOfMean, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  
  Utility::SampleMoment<1,T> first_moment( Utility::QuantityTraits<ValueType1>::one()*10. );
  Utility::SampleMoment<2,T> second_moment( Utility::QuantityTraits<ValueType2>::one()*100. );

  ValueType2 variance =
    Utility::calculateVarianceOfMean( first_moment, second_moment, 100 );

  FRENSIE_CHECK_EQUAL( variance, Utility::QuantityTraits<ValueType2>::one()/100. );
}

//---------------------------------------------------------------------------//
// Check that the std dev of the mean can be calculated
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_Helpers, calculateStdDevOfMean, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  
  Utility::SampleMoment<1,T> first_moment( Utility::QuantityTraits<ValueType1>::one()*10. );
  Utility::SampleMoment<2,T> second_moment( Utility::QuantityTraits<ValueType2>::one()*100. );

  ValueType1 std_dev =
    Utility::calculateStdDevOfMean( first_moment, second_moment, 100 );

  FRENSIE_CHECK_EQUAL( std_dev, Utility::QuantityTraits<ValueType1>::one()/10. );
}

//---------------------------------------------------------------------------//
// Check that the relative error can be calculated
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_Helpers, calculateRelativeError, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;

  Utility::SampleMoment<1,T> first_moment( Utility::QuantityTraits<ValueType1>::one()*10. );
  Utility::SampleMoment<2,T> second_moment( Utility::QuantityTraits<ValueType2>::one()*100. );

  typename Utility::QuantityTraits<T>::RawType relative_error =
    Utility::calculateRelativeError( first_moment, second_moment, 100 );

  FRENSIE_CHECK_FLOATING_EQUALITY( relative_error, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the relative variance of the variance can be calculated
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_Helpers, calculateRelativeVOV, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType3;
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType4;

  Utility::SampleMoment<1,T> first_moment( Utility::QuantityTraits<ValueType1>::one()*10. );
  Utility::SampleMoment<2,T> second_moment( Utility::QuantityTraits<ValueType2>::one()*100. );
  Utility::SampleMoment<3,T> third_moment( Utility::QuantityTraits<ValueType3>::one()*1000. );
  Utility::SampleMoment<4,T> fourth_moment( Utility::QuantityTraits<ValueType4>::one()*10000. );

  typename Utility::QuantityTraits<T>::RawType relative_vov =
    Utility::calculateRelativeVOV( first_moment,
                                   second_moment,
                                   third_moment,
                                   fourth_moment,
                                   100 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( relative_vov, 0.97010101010101002, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the figure of merit can be calculated
FRENSIE_UNIT_TEST_TEMPLATE( SampleMoment_Helpers, calculateFOM, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  typename Utility::QuantityTraits<T>::RawType fom =
    Utility::calculateFOM( 2.0, 1e3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( fom, 2.5e-4, 1e-12 );
}

//---------------------------------------------------------------------------//
// end tstSampleMoment.cpp
//---------------------------------------------------------------------------//
