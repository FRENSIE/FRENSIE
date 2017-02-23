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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_SampleMoment.hpp"
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
// Check that the current score of the moment can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_1, getCurrentScore, T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T> moment_a;

  TEST_EQUALITY_CONST( moment_a.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::zero() );

  Utility::SampleMoment<1,T>
    moment_b( Utility::QuantityTraits<ValueType>::one() );

  TEST_EQUALITY_CONST( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_1, getCurrentScore );

//---------------------------------------------------------------------------//
// Check that the current score of the moment can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_2, getCurrentScore, T )
{
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType;

  Utility::SampleMoment<2,T> moment_a;

  TEST_EQUALITY_CONST( moment_a.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::zero() );

  Utility::SampleMoment<2,T>
    moment_b( Utility::QuantityTraits<ValueType>::one() );

  TEST_EQUALITY_CONST( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_2, getCurrentScore );

//---------------------------------------------------------------------------//
// Check that the current score of the moment can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_3, getCurrentScore, T )
{
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType;

  Utility::SampleMoment<3,T> moment_a;

  TEST_EQUALITY_CONST( moment_a.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::zero() );

  Utility::SampleMoment<3,T>
    moment_b( Utility::QuantityTraits<ValueType>::one() );

  TEST_EQUALITY_CONST( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_3, getCurrentScore );

//---------------------------------------------------------------------------//
// Check that the current score of the moment can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_4, getCurrentScore, T )
{
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType;

  Utility::SampleMoment<4,T> moment_a;

  TEST_EQUALITY_CONST( moment_a.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::zero() );

  Utility::SampleMoment<4,T>
    moment_b( Utility::QuantityTraits<ValueType>::one() );

  TEST_EQUALITY_CONST( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_4, getCurrentScore );

//---------------------------------------------------------------------------//
// Check that the calculated moment can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_1, get, T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T>
    moment( Utility::QuantityTraits<ValueType>::one() );

  TEST_EQUALITY_CONST( moment.get( 10 ),
                       Utility::QuantityTraits<ValueType>::one()/10. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_1, get );

//---------------------------------------------------------------------------//
// Check that the calculated moment can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_2, get, T )
{
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType;

  Utility::SampleMoment<2,T>
    moment( Utility::QuantityTraits<ValueType>::one() );

  TEST_EQUALITY_CONST( moment.get( 10 ),
                       Utility::QuantityTraits<ValueType>::one()/10. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_2, get );

//---------------------------------------------------------------------------//
// Check that the calculated moment can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_3, get, T )
{
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType;

  Utility::SampleMoment<3,T>
    moment( Utility::QuantityTraits<ValueType>::one() );

  TEST_EQUALITY_CONST( moment.get( 10 ),
                       Utility::QuantityTraits<ValueType>::one()/10. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_3, get );

//---------------------------------------------------------------------------//
// Check that the calculated moment can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_4, get, T )
{
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType;

  Utility::SampleMoment<4,T>
    moment( Utility::QuantityTraits<ValueType>::one() );

  TEST_EQUALITY_CONST( moment.get( 10 ),
                       Utility::QuantityTraits<ValueType>::one()/10. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_4, get );

//---------------------------------------------------------------------------//
// Check that the copy constructor can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_1, copy_constructor, T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<1,T> moment_b( moment_a );

  TEST_EQUALITY_CONST( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_1, copy_constructor );

//---------------------------------------------------------------------------//
// Check that the copy constructor can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_2, copy_constructor, T )
{
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType;

  Utility::SampleMoment<2,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<2,T> moment_b( moment_a );

  TEST_EQUALITY_CONST( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_2, copy_constructor );

//---------------------------------------------------------------------------//
// Check that the copy constructor can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_3, copy_constructor, T )
{
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType;

  Utility::SampleMoment<3,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<3,T> moment_b( moment_a );

  TEST_EQUALITY_CONST( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_3, copy_constructor );

//---------------------------------------------------------------------------//
// Check that the copy constructor can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_4, copy_constructor, T )
{
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType;

  Utility::SampleMoment<4,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<4,T> moment_b( moment_a );

  TEST_EQUALITY_CONST( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_4, copy_constructor );

//---------------------------------------------------------------------------//
// Check that the assignment operator can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_1, assignment_operator, T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<1,T> moment_b = moment_a;

  TEST_EQUALITY_CONST( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_1, assignment_operator );

//---------------------------------------------------------------------------//
// Check that the assignment operator can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_2, assignment_operator, T )
{
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType;

  Utility::SampleMoment<2,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<2,T> moment_b = moment_a;

  TEST_EQUALITY_CONST( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_2, assignment_operator );

//---------------------------------------------------------------------------//
// Check that the assignment operator can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_3, assignment_operator, T )
{
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType;

  Utility::SampleMoment<3,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<3,T> moment_b = moment_a;

  TEST_EQUALITY_CONST( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_3, assignment_operator );

//---------------------------------------------------------------------------//
// Check that the assignment operator can be used
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_4, assignment_operator, T )
{
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType;

  Utility::SampleMoment<4,T>
    moment_a( Utility::QuantityTraits<ValueType>::one()/2. );

  Utility::SampleMoment<4,T> moment_b = moment_a;

  TEST_EQUALITY_CONST( moment_b.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_4, assignment_operator );

//---------------------------------------------------------------------------//
// Check that a raw score can be added to the moment
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_1, addRawScore, T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T> moment;

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_1, addRawScore );

//---------------------------------------------------------------------------//
// Check that a raw score can be added to the moment
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_2, addRawScore, T )
{
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType;

  Utility::SampleMoment<2,T> moment;

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/4. );

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_2, addRawScore );

//---------------------------------------------------------------------------//
// Check that a raw score can be added to the moment
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_3, addRawScore, T )
{
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType;

  Utility::SampleMoment<3,T> moment;

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/8. );

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/4. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_3, addRawScore );

//---------------------------------------------------------------------------//
// Check that a raw score can be added to the moment
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_4, addRawScore, T )
{
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType;

  Utility::SampleMoment<4,T> moment;

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/16. );

  moment.addRawScore( Utility::QuantityTraits<T>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/8. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_4, addRawScore );

//---------------------------------------------------------------------------//
// Check that a processed score can be added to the moment
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_1, addProcessedScore, T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T> moment;

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_1, addProcessedScore );

//---------------------------------------------------------------------------//
// Check that a processed score can be added to the moment
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_2, addProcessedScore, T )
{
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType;

  Utility::SampleMoment<2,T> moment;

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_2, addProcessedScore );

//---------------------------------------------------------------------------//
// Check that a processed score can be added to the moment
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_3, addProcessedScore, T )
{
  typedef typename Utility::SampleMoment<3,T>::ValueType ValueType;

  Utility::SampleMoment<3,T> moment;

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_3, addProcessedScore );

//---------------------------------------------------------------------------//
// Check that a processed score can be added to the moment
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_4, addProcessedScore, T )
{
  typedef typename Utility::SampleMoment<4,T>::ValueType ValueType;

  Utility::SampleMoment<4,T> moment;

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one()/2. );

  moment.addProcessedScore( Utility::QuantityTraits<ValueType>::one()/2. );

  TEST_EQUALITY_CONST( moment.getCurrentScore(),
                       Utility::QuantityTraits<ValueType>::one() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_4, addProcessedScore );

//---------------------------------------------------------------------------//
// Check that the mean can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_Helpers, calculateMean, T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType;

  Utility::SampleMoment<1,T> moment( Utility::QuantityTraits<ValueType>::one()*10. );
  
  ValueType mean = Utility::calculateMean( moment, 100 );

  TEST_EQUALITY_CONST( mean, Utility::QuantityTraits<ValueType>::one()*0.1 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_Helpers, calculateMean );

//---------------------------------------------------------------------------//
// Check that the variance can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_Helpers, calculateVariance, T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  
  Utility::SampleMoment<1,T> first_moment( Utility::QuantityTraits<ValueType1>::one()*10. );
  Utility::SampleMoment<2,T> second_moment( Utility::QuantityTraits<ValueType2>::one()*100. );

  ValueType2 variance =
    Utility::calculateVariance( first_moment, second_moment, 100 );

  TEST_EQUALITY_CONST( variance, Utility::QuantityTraits<ValueType2>::one() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_Helpers, calculateVariance );

//---------------------------------------------------------------------------//
// Check that the std dev can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_Helpers, calculateStdDev, T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  
  Utility::SampleMoment<1,T> first_moment( Utility::QuantityTraits<ValueType1>::one()*10. );
  Utility::SampleMoment<2,T> second_moment( Utility::QuantityTraits<ValueType2>::one()*100. );

  ValueType1 std_dev =
    Utility::calculateStdDev( first_moment, second_moment, 100 );

  TEST_EQUALITY_CONST( std_dev, Utility::QuantityTraits<ValueType1>::one() );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_Helpers, calculateStdDev );

//---------------------------------------------------------------------------//
// Check that the variance of the mean can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_Helpers, calculateVarianceOfMean, T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  
  Utility::SampleMoment<1,T> first_moment( Utility::QuantityTraits<ValueType1>::one()*10. );
  Utility::SampleMoment<2,T> second_moment( Utility::QuantityTraits<ValueType2>::one()*100. );

  ValueType2 variance =
    Utility::calculateVarianceOfMean( first_moment, second_moment, 100 );

  TEST_EQUALITY_CONST( variance, Utility::QuantityTraits<ValueType2>::one()/100. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_Helpers, calculateVarianceOfMean );

//---------------------------------------------------------------------------//
// Check that the std dev of the mean can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_Helpers, calculateStdDevOfMean, T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;
  
  Utility::SampleMoment<1,T> first_moment( Utility::QuantityTraits<ValueType1>::one()*10. );
  Utility::SampleMoment<2,T> second_moment( Utility::QuantityTraits<ValueType2>::one()*100. );

  ValueType1 std_dev =
    Utility::calculateStdDevOfMean( first_moment, second_moment, 100 );

  TEST_EQUALITY_CONST( std_dev, Utility::QuantityTraits<ValueType1>::one()/10. );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_Helpers, calculateStdDevOfMean );

//---------------------------------------------------------------------------//
// Check that the relative error can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_Helpers, calculateRelativeError, T )
{
  typedef typename Utility::SampleMoment<1,T>::ValueType ValueType1;
  typedef typename Utility::SampleMoment<2,T>::ValueType ValueType2;

  Utility::SampleMoment<1,T> first_moment( Utility::QuantityTraits<ValueType1>::one()*10. );
  Utility::SampleMoment<2,T> second_moment( Utility::QuantityTraits<ValueType2>::one()*100. );

  typename Utility::QuantityTraits<T>::RawType relative_error =
    Utility::calculateRelativeError( first_moment, second_moment, 100 );

  TEST_FLOATING_EQUALITY( relative_error, 1.0, 1e-12 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_Helpers, calculateRelativeError );

//---------------------------------------------------------------------------//
// Check that the relative variance of the variance can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_Helpers, calculateRelativeVOV, T )
{
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
  
  TEST_FLOATING_EQUALITY( relative_vov, 0.97010101010101002, 1e-12 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_Helpers, calculateRelativeVOV );

//---------------------------------------------------------------------------//
// Check that the figure of merit can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SampleMoment_Helpers, calculateFOM, T )
{
  typename Utility::QuantityTraits<T>::RawType fom =
    Utility::calculateFOM( 2.0, 1e3 );

  TEST_FLOATING_EQUALITY( fom, 2.5e-4, 1e-12 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( SampleMoment_Helpers, calculateFOM );

//---------------------------------------------------------------------------//
// end tstSampleMoment.cpp
//---------------------------------------------------------------------------//
