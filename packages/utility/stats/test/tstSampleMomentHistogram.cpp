//---------------------------------------------------------------------------//
//!
//! \file   tstSampleMomentHistogram.cpp
//! \author Alex Robinson
//! \brief  Sample moment histogram unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

// FRENSIE Includes
#include "Utility_SampleMomentHistogram.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Template Typedefs
//---------------------------------------------------------------------------//
typedef std::tuple<double,
                   boost::units::quantity<boost::units::cgs::length>,
                   boost::units::quantity<boost::units::si::length> > TestingTypes;

//---------------------------------------------------------------------------//
// Check that the size of a histogram can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentHistogram, size, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  
  Utility::SampleMomentHistogram<T> default_histogram;

  FRENSIE_CHECK_EQUAL( default_histogram.size(), 1 );

  Utility::SampleMomentHistogram<T> histogram( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*2.0}) ) );

  FRENSIE_CHECK_EQUAL( histogram.size(), 2 );
}

//---------------------------------------------------------------------------//
// Check that the bin boundaries can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentHistogram,
                            getBinBoundaries,
                            TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::SampleMomentHistogram<T> default_histogram;

  {
    const std::vector<T>& bin_boundaries =
      default_histogram.getBinBoundaries();
    
    FRENSIE_REQUIRE_EQUAL( bin_boundaries.size(), 2 );
    FRENSIE_CHECK_EQUAL( bin_boundaries.front(),
                         Utility::QuantityTraits<T>::lowest() );
    FRENSIE_CHECK_EQUAL( bin_boundaries.back(),
                         Utility::QuantityTraits<T>::max() );
  }

  Utility::SampleMomentHistogram<T> histogram( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*2.0}) ) );

  {
    const std::vector<T>& bin_boundaries =
      histogram.getBinBoundaries();

    FRENSIE_REQUIRE_EQUAL( bin_boundaries.size(), 3 );
    FRENSIE_CHECK_EQUAL( bin_boundaries[0],
                         Utility::QuantityTraits<T>::zero() );
    FRENSIE_CHECK_EQUAL( bin_boundaries[1],
                         Utility::QuantityTraits<T>::one() );
    FRENSIE_CHECK_EQUAL( bin_boundaries[2],
                         Utility::QuantityTraits<T>::one()*2.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that raw scores can be added to the histogram
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentHistogram, addRawScore, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  typedef typename Utility::QuantityTraits<T>::RawType RawType;

  Utility::SampleMomentHistogram<T> default_histogram;
  
  Utility::SampleMomentHistogram<T> histogram( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*2.0}) ) );

  default_histogram.addRawScore( -Utility::QuantityTraits<T>::one() );
  histogram.addRawScore( -Utility::QuantityTraits<T>::one() );

  FRENSIE_CHECK_EQUAL( default_histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );

  default_histogram.addRawScore( Utility::QuantityTraits<T>::zero() );
  histogram.addRawScore( Utility::QuantityTraits<T>::zero() );

  FRENSIE_CHECK_EQUAL( default_histogram.getNumberOfScores(), 2 );
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );

  default_histogram.addRawScore( Utility::QuantityTraits<T>::one() );
  histogram.addRawScore( Utility::QuantityTraits<T>::one() );

  FRENSIE_CHECK_EQUAL( default_histogram.getNumberOfScores(), 3 );
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );

  default_histogram.addRawScore( Utility::QuantityTraits<T>::one()*2.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*2.0 );

  FRENSIE_CHECK_EQUAL( default_histogram.getNumberOfScores(), 4 );
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 3 );

  default_histogram.addRawScore( Utility::QuantityTraits<T>::one()*3.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*3.0 );

  FRENSIE_CHECK_EQUAL( default_histogram.getNumberOfScores(), 5 );
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 3 );

  {
    const std::vector<RawType>& histogram_values =
      default_histogram.getHistogramValues();

    FRENSIE_REQUIRE_EQUAL( histogram_values.size(), 1 );
    FRENSIE_CHECK_EQUAL( histogram_values[0], 5.0 );
  }

  {
    const std::vector<RawType>& histogram_values =
      histogram.getHistogramValues();

    FRENSIE_REQUIRE_EQUAL( histogram_values.size(), 2 );
    FRENSIE_CHECK_EQUAL( histogram_values[0], 1.0 );
    FRENSIE_CHECK_EQUAL( histogram_values[1], 2.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a histogram can be cleared
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentHistogram, clear, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::SampleMomentHistogram<T> histogram( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*2.0}) ) );

  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.5 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.5 );

  FRENSIE_CHECK_EQUAL( histogram.size(), 2 );
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );

  histogram.clear();

  FRENSIE_CHECK_EQUAL( histogram.size(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries()[0],
                       Utility::QuantityTraits<T>::lowest() );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries()[1],
                       Utility::QuantityTraits<T>::max() );
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
}

//---------------------------------------------------------------------------//
// Check that a histogram can be reset
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentHistogram, reset, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::SampleMomentHistogram<T> histogram( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*2.0}) ) );

  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.5 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.5 );

  FRENSIE_CHECK_EQUAL( histogram.size(), 2 );
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );

  histogram.reset();

  FRENSIE_CHECK_EQUAL( histogram.size(), 2 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries()[0],
                       Utility::QuantityTraits<T>::zero() );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries()[1],
                       Utility::QuantityTraits<T>::one() );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries()[2],
                       Utility::QuantityTraits<T>::one()*2.0 );
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the bin boundaries of a histogram can be set
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentHistogram,
                            setBinBoundaries,
                            TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::SampleMomentHistogram<T> histogram;

  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.5 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.5 );

  FRENSIE_CHECK_EQUAL( histogram.size(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );

  histogram.setBinBoundaries( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*2.0}) ) );

  histogram.reset();

  FRENSIE_CHECK_EQUAL( histogram.size(), 2 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries()[0],
                       Utility::QuantityTraits<T>::zero() );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries()[1],
                       Utility::QuantityTraits<T>::one() );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries()[2],
                       Utility::QuantityTraits<T>::one()*2.0 );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the normalized histogram values can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentHistogram,
                            getNormalizedHistogramValues,
                            TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  typedef typename Utility::QuantityTraits<T>::RawType RawType;

  Utility::SampleMomentHistogram<T> histogram( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*2.0}) ) );

  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*2.0 );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 11 );

  std::vector<RawType> normalized_values;

  histogram.getNormalizedHistogramValues( normalized_values );

  FRENSIE_REQUIRE_EQUAL( normalized_values.size(), 2 );
  FRENSIE_CHECK_EQUAL( normalized_values[0], 5.0/11 );
  FRENSIE_CHECK_EQUAL( normalized_values[1], 6.0/11 );
}

//---------------------------------------------------------------------------//
// Check that the density values can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentHistogram,
                            getDensityValues,
                            TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  typedef typename Utility::SampleMomentHistogram<T>::DensityValueType DensityValueType;

  Utility::SampleMomentHistogram<T> histogram( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one()*0.5, Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*1.5, Utility::QuantityTraits<T>::one()*2.0}) ) );

  histogram.addRawScore( -Utility::QuantityTraits<T>::one() );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*2.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*3.0 );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 11 );

  std::vector<DensityValueType> density_values;

  histogram.getDensityValues( density_values );

  FRENSIE_REQUIRE_EQUAL( density_values.size(), 4 );
  FRENSIE_CHECK_EQUAL( density_values[0],
                       (3.0/(11*0.5)/Utility::QuantityTraits<T>::one()) );
  FRENSIE_CHECK_EQUAL( density_values[1],
                       (2.0/(11*0.5))/Utility::QuantityTraits<T>::one() );
  FRENSIE_CHECK_EQUAL( density_values[2],
                       (3.0/(11*0.5))/Utility::QuantityTraits<T>::one() );
  FRENSIE_CHECK_EQUAL( density_values[3],
                       (3.0/(11*0.5))/Utility::QuantityTraits<T>::one() );

  histogram.setBinBoundaries( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::lowest(), Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one()*0.5, Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*1.5, Utility::QuantityTraits<T>::one()*2.0, Utility::QuantityTraits<T>::max()}) ) );

  histogram.addRawScore( -Utility::QuantityTraits<T>::one() );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*2.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*3.0 );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 13 );

  histogram.getDensityValues( density_values );

  FRENSIE_REQUIRE_EQUAL( density_values.size(), 6 );
  FRENSIE_CHECK_EQUAL( density_values[0],
                       Utility::QuantityTraits<DensityValueType>::zero() );
  FRENSIE_CHECK_EQUAL( density_values[1],
                       (3.0/(13*0.5)/Utility::QuantityTraits<T>::one()) );
  FRENSIE_CHECK_EQUAL( density_values[2],
                       (2.0/(13*0.5))/Utility::QuantityTraits<T>::one() );
  FRENSIE_CHECK_EQUAL( density_values[3],
                       (3.0/(13*0.5))/Utility::QuantityTraits<T>::one() );
  FRENSIE_CHECK_EQUAL( density_values[4],
                       (2.0/(13*0.5))/Utility::QuantityTraits<T>::one() );
  FRENSIE_CHECK_EQUAL( density_values[5],
                       Utility::QuantityTraits<DensityValueType>::zero() );
}

//---------------------------------------------------------------------------//
// Check that a histogram can be copied
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentHistogram,
                            copy_constructor,
                            TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::SampleMomentHistogram<T> histogram( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one()*0.5, Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*1.5, Utility::QuantityTraits<T>::one()*2.0}) ) );

  histogram.addRawScore( -Utility::QuantityTraits<T>::one() );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*2.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*3.0 );

  Utility::SampleMomentHistogram<T> histogram_copy( histogram );

  FRENSIE_CHECK_EQUAL( histogram_copy.size(), histogram.size() );
  FRENSIE_CHECK_EQUAL( histogram_copy.getBinBoundaries(),
                       histogram.getBinBoundaries() );
  FRENSIE_CHECK_EQUAL( histogram_copy.getHistogramValues(),
                       histogram.getHistogramValues() );
  FRENSIE_CHECK_EQUAL( histogram_copy.getNumberOfScores(),
                       histogram.getNumberOfScores() );
}

//---------------------------------------------------------------------------//
// Check that a histogram can be copied
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentHistogram,
                            assignment_operator,
                            TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::SampleMomentHistogram<T> histogram( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one()*0.5, Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*1.5, Utility::QuantityTraits<T>::one()*2.0}) ) );

  histogram.addRawScore( -Utility::QuantityTraits<T>::one() );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*2.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*3.0 );

  Utility::SampleMomentHistogram<T> histogram_copy = histogram;

  FRENSIE_CHECK_EQUAL( histogram_copy.size(), histogram.size() );
  FRENSIE_CHECK_EQUAL( histogram_copy.getBinBoundaries(),
                       histogram.getBinBoundaries() );
  FRENSIE_CHECK_EQUAL( histogram_copy.getHistogramValues(),
                       histogram.getHistogramValues() );
  FRENSIE_CHECK_EQUAL( histogram_copy.getNumberOfScores(),
                       histogram.getNumberOfScores() );
}

//---------------------------------------------------------------------------//
// Check that two histograms can be merged
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentHistogram,
                            mergeHistograms,
                            TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );
  typedef typename Utility::SampleMomentHistogram<T>::HistogramValueType HistogramValueType;

  Utility::SampleMomentHistogram<T> histogram( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::lowest(), Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one()*0.5, Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*1.5, Utility::QuantityTraits<T>::one()*2.0, Utility::QuantityTraits<T>::max()}) ) );

  histogram.addRawScore( -Utility::QuantityTraits<T>::one() );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*2.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*3.0 );

  {
    Utility::SampleMomentHistogram<T> other_histogram( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::lowest(), Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one()*0.5, Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*1.5, Utility::QuantityTraits<T>::one()*2.0, Utility::QuantityTraits<T>::max()}) ) );

    histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.6 );
    histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.8 );
    histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.0 );
    histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.2 );
    histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.4 );
    histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.6 );
    
    histogram.mergeHistograms( other_histogram );
  }

  FRENSIE_CHECK_EQUAL( histogram.size(), 6 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       std::vector<T>({Utility::QuantityTraits<T>::lowest(), Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one()*0.5, Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*1.5, Utility::QuantityTraits<T>::one()*2.0, Utility::QuantityTraits<T>::max()}) );
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 19 );

  const std::vector<HistogramValueType>& histogram_values =
    histogram.getHistogramValues();

  FRENSIE_REQUIRE_EQUAL( histogram_values.size(), 6 );
  FRENSIE_CHECK_EQUAL( histogram_values[0],
                       Utility::QuantityTraits<HistogramValueType>::one() );
  FRENSIE_CHECK_EQUAL( histogram_values[1],
                       3.0*Utility::QuantityTraits<HistogramValueType>::one() );
  FRENSIE_CHECK_EQUAL( histogram_values[2],
                       4.0*Utility::QuantityTraits<HistogramValueType>::one() );
  FRENSIE_CHECK_EQUAL( histogram_values[3],
                       6.0*Utility::QuantityTraits<HistogramValueType>::one() );
  FRENSIE_CHECK_EQUAL( histogram_values[4],
                       3.0*Utility::QuantityTraits<HistogramValueType>::one() );
  FRENSIE_CHECK_EQUAL( histogram_values[5],
                       2.0*Utility::QuantityTraits<HistogramValueType>::one() );
}

//---------------------------------------------------------------------------//
// Check that a histogram can be archived
FRENSIE_UNIT_TEST_TEMPLATE( SampleMomentHistogram, archive, TestingTypes )
{
  FETCH_TEMPLATE_PARAM( 0, T );

  Utility::SampleMomentHistogram<T> histogram( std::make_shared<std::vector<T> >( std::vector<T>({Utility::QuantityTraits<T>::lowest(), Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::one()*0.5, Utility::QuantityTraits<T>::one(), Utility::QuantityTraits<T>::one()*1.5, Utility::QuantityTraits<T>::one()*2.0, Utility::QuantityTraits<T>::max()}) ) );

  histogram.addRawScore( -Utility::QuantityTraits<T>::one() );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*0.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.2 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.4 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.6 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*1.8 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*2.0 );
  histogram.addRawScore( Utility::QuantityTraits<T>::one()*3.0 );

  std::ostringstream archive_ostream;

  {
    boost::archive::xml_oarchive archive( archive_ostream );

    FRENSIE_REQUIRE_NO_THROW( archive << BOOST_SERIALIZATION_NVP( histogram ) );
  }

  Utility::SampleMomentHistogram<T> extracted_histogram;

  {
    std::istringstream iss( archive_ostream.str() );
    
    boost::archive::xml_iarchive archive( iss );

    FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "histogram", extracted_histogram ) );
  }

  FRENSIE_CHECK_EQUAL( extracted_histogram.size(), histogram.size() );
  FRENSIE_CHECK_EQUAL( extracted_histogram.getBinBoundaries(),
                       histogram.getBinBoundaries() );
  FRENSIE_CHECK_EQUAL( extracted_histogram.getHistogramValues(),
                       histogram.getHistogramValues() );
  FRENSIE_CHECK_EQUAL( extracted_histogram.getNumberOfScores(),
                       histogram.getNumberOfScores() );
}

//---------------------------------------------------------------------------//
// end tstSampleMomentHistogram.cpp
//---------------------------------------------------------------------------//
