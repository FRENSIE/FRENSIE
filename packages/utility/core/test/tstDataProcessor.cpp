//---------------------------------------------------------------------------//
//!
//! \file   tstDataProcessor.cpp
//! \author Alex Robinson
//! \brief  DataProcessor class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "Utility_DataProcessor.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Data.
//---------------------------------------------------------------------------//
#define INDEP_VAR 5.11e-1
#define LOG_INDEP_VAR -6.7138568877843e-1
#define SQR_INDEP_VAR 2.61121e-1
#define DEP_VAR 3.14
#define LOG_DEP_VAR 1.1442227999202
#define SQR_DEP_VAR 9.8596
#define ZERO 0
#define SLOPE 6.1448140900196
#define CDF_NORM 64.98387
#define SHELL 5
#define SHELL_NAME "5"
#define TOL 1e-12

//---------------------------------------------------------------------------//
// Template Typedefs.
//---------------------------------------------------------------------------//
template<typename Policy>
struct TypeList
{
  typedef std::tuple<std::tuple<Policy,std::pair<double,double> >,
                     std::tuple<Policy,std::tuple<double,double> >,
                     std::tuple<Policy,std::tuple<double,double,double> >,
                     std::tuple<Policy,std::tuple<double,double,double,double> > > type;
};

typedef decltype(std::tuple_cat(typename TypeList<Utility::LogLogDataProcessing>::type(),typename TypeList<Utility::SqrSqrDataProcessing>::type())) PolicyTupleTypes;

typedef std::tuple<std::pair<double,double>,
                   std::tuple<double,double>,
                   std::tuple<double,double,double>,
                   std::tuple<double,double,double,double> > TupleTypes;

typedef std::tuple<std::tuple<std::integral_constant<size_t,2>,std::tuple<double,double,double> >,
                   std::tuple<std::integral_constant<size_t,2>,std::tuple<double,double,double,double> >,
                   std::tuple<std::integral_constant<size_t,3>,std::tuple<double,double,double,double> > > ThreePlusTupleSingleMemberTypes;

typedef std::tuple<std::tuple<std::integral_constant<size_t,1>,std::pair<double,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::pair<unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::tuple<double,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::tuple<unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::tuple<double,double,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::tuple<unsigned,double,double> >,
                   std::tuple<std::integral_constant<size_t,2>,std::tuple<double,double,double,double> >,
                   std::tuple<std::integral_constant<size_t,2>,std::tuple<unsigned,unsigned,double,double> > > TupleSingleMemberTypes;

typedef std::tuple<std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,0>,std::pair<double,unsigned>,std::tuple<double,double,unsigned> >,
                   std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,0>,std::tuple<double,unsigned>,std::tuple<double,double,unsigned> >,
                   std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,1>,std::pair<double,unsigned>,std::pair<unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,1>,std::tuple<double,unsigned>,std::tuple<unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,2>,std::tuple<double,double,unsigned>,std::tuple<unsigned,double,double> >,
                   std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,3>,std::tuple<unsigned,double,double,double>,std::tuple<double,double,double,unsigned> >,
                   std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,0>,std::pair<double,unsigned>,std::pair<unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,0>,std::tuple<double,unsigned>,std::tuple<unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,0>,std::tuple<unsigned,unsigned,double>,std::tuple<double,unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,2>,std::tuple<double,unsigned,double>,std::tuple<double,double,unsigned> >,
                   
                   std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,3>,std::tuple<unsigned,unsigned,double,double>,std::tuple<unsigned,double,double,unsigned> >,
                   std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,0>,std::tuple<double,double,unsigned>,std::tuple<unsigned,double,double> >,
                   std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,1>,std::tuple<double,unsigned,double>,std::tuple<double,double,unsigned> >,
                   std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,2>,std::tuple<double,double,double>,std::tuple<unsigned,unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,3>,std::tuple<double,double,double,double>,std::tuple<unsigned,unsigned,unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,3>,std::integral_constant<size_t,0>,std::tuple<unsigned,double,double,double>,std::tuple<double,double,double,unsigned> >,
                   std::tuple<std::integral_constant<size_t,3>,std::integral_constant<size_t,1>,std::tuple<unsigned,unsigned,double,double>,std::tuple<unsigned,double,double,unsigned> >,
                   std::tuple<std::integral_constant<size_t,3>,std::integral_constant<size_t,2>,std::tuple<double,double,double,double>,std::tuple<unsigned,unsigned,unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,3>,std::integral_constant<size_t,3>,std::tuple<double,double,double,unsigned>,std::tuple<unsigned,unsigned,unsigned,unsigned> > > TwoTupleTwoMemberTypes;

typedef std::tuple<std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,1>,std::pair<double,double> >,
                   std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,1>,std::tuple<double,double> >,
                   std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,2>,std::tuple<double,double,double> >,
                   std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,3>,std::tuple<double,double,double,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,2>,std::tuple<unsigned,double,double> >,
                   std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,3>,std::tuple<unsigned,double,unsigned,double> >,
                   std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,3>,std::tuple<double,double,unsigned,unsigned> > > TupleTwoMemberTypes;

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestDataProcessor : public Utility::DataProcessor
{
public:
  TestDataProcessor()
  { /* ... */ }

  virtual ~TestDataProcessor()
  { /* ... */ }

  void processDataFiles()
  { /* ... */ }

  // Allow public access to the DataProcessor protected member functions
  using Utility::DataProcessor::processContinuousData;
  using Utility::DataProcessor::removeElementsLessThanValue;
  using Utility::DataProcessor::removeElementsGreaterThanValue;
  using Utility::DataProcessor::coarsenConstantRegions;
  using Utility::DataProcessor::calculateSlopes;
  using Utility::DataProcessor::calculateContinuousCDF;
  using Utility::DataProcessor::calculateDiscreteCDF;
  using Utility::DataProcessor::copyTupleMemberData;
  using Utility::DataProcessor::swapTupleMemberData;
  using Utility::DataProcessor::uintToShellStr;
};

typedef Utility::LogLogDataProcessing LogLogDataProcessing;
typedef Utility::SqrSqrDataProcessing SqrSqrDataProcessing;

template<typename ProcessingPolicy>
struct ProcessingPolicyTestingTraits
{
  static const double referenceIndepValue;
  static const double referenceDepValue;
};

template<typename ProcessingPolicy>
const double ProcessingPolicyTestingTraits<ProcessingPolicy>::referenceIndepValue = 0.0;

template<typename ProcessingPolicy>
const double ProcessingPolicyTestingTraits<ProcessingPolicy>::referenceDepValue = 0.0;

template<>
struct ProcessingPolicyTestingTraits<Utility::LogLogDataProcessing>
{
  static const double referenceIndepValue;
  static const double referenceDepValue;
};

const double ProcessingPolicyTestingTraits<Utility::LogLogDataProcessing>::referenceIndepValue = LOG_INDEP_VAR;

const double ProcessingPolicyTestingTraits<Utility::LogLogDataProcessing>::referenceDepValue = LOG_DEP_VAR;

template<>
struct ProcessingPolicyTestingTraits<Utility::SqrSqrDataProcessing>
{
  static const double referenceIndepValue;
  static const double referenceDepValue;
};

const double ProcessingPolicyTestingTraits<Utility::SqrSqrDataProcessing>::referenceIndepValue = SQR_INDEP_VAR;

const double ProcessingPolicyTestingTraits<Utility::SqrSqrDataProcessing>::referenceDepValue = SQR_DEP_VAR;

//---------------------------------------------------------------------------//
// Helper functions.
//---------------------------------------------------------------------------//
template<size_t member, typename T, template<typename,typename...> class Array>
void fillArrayOneTupleMemberData( Array<T> &array )
{
  typedef typename Utility::TupleElement<member,T>::type tupleMemberType;

  if( array.size() > 0 )
  {
    for( size_t i = 1; i <= array.size(); ++i )
      Utility::get<member>( array[i-1] ) = static_cast<tupleMemberType>( i );
  }
}

template<size_t indepMember,
	 size_t depMember,
	 typename T,
	 template<typename,typename...> class Array>
void fillArrayTwoTupleMemberData( Array<T> &array )
{
  typedef typename Utility::TupleElement<indepMember,T>::type indepTupleMemberType;
  typedef typename Utility::TupleElement<depMember,T>::type depTupleMemberType;

  if( array.size() > 0 )
  {
    for( size_t i = 0; i < array.size(); ++i )
    {
      Utility::get<indepMember>( array[i] ) =
        static_cast<indepTupleMemberType>( i*INDEP_VAR );
      
      Utility::get<depMember>( array[i] ) = 
        static_cast<depTupleMemberType>( i*DEP_VAR );
    }
  }
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the DataProcessingPolicies correctly process data
FRENSIE_UNIT_TEST_TEMPLATE( DataProcessor, DataProcessingPolicy,
                            Utility::LogLogDataProcessing,
                            Utility::SqrSqrDataProcessing )
{
  FETCH_TEMPLATE_PARAM( 0, Policy );
  
  double processed_indep_var, processed_dep_var;
  processed_indep_var = Policy::processIndependentVar( INDEP_VAR );
  processed_dep_var = Policy::processDependentVar( DEP_VAR );

  double ref_indep_var, ref_dep_var;
  ref_indep_var = ProcessingPolicyTestingTraits<Policy>::referenceIndepValue;
  ref_dep_var = ProcessingPolicyTestingTraits<Policy>::referenceDepValue;

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_indep_var, ref_indep_var, TOL );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_dep_var, ref_dep_var, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can processes an array of UTILITY Tuple structs
// in the desired format
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DataProcessor,
                                   processContinuousData,
                                   PolicyTupleTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Policy );
  FETCH_TEMPLATE_PARAM( 1, Tuple );
  
  TestDataProcessor data_processor;

  // Load the array to be processed
  Tuple data_point;
  Utility::get<0>( data_point ) = INDEP_VAR;
  Utility::get<1>( data_point ) = DEP_VAR;
  std::vector<Tuple> processed_data( 10, data_point );

  // Load the reference array
  Utility::get<0>( data_point ) = ProcessingPolicyTestingTraits<Policy>::referenceIndepValue;
  Utility::get<1>( data_point ) = ProcessingPolicyTestingTraits<Policy>::referenceDepValue;
  std::vector<Tuple> ref_data( 10, data_point );

  // Process the Array
  data_processor.processContinuousData<Policy,
				       Utility::FIRST,
				       Utility::SECOND>( processed_data );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can remove elements with a tuple member less
// than a specified value
FRENSIE_UNIT_TEST_TEMPLATE( DataProcessor,
                            removeElementsLessThanValue,
                            TupleTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Tuple );
  
  TestDataProcessor data_processor;

  std::vector<Tuple> ref_data( 10 ), clipped_data( 10 );

  // Load the reference array
  fillArrayOneTupleMemberData<Utility::FIRST>( ref_data );

  // Load the clipped array
  clipped_data = ref_data;

  // Set the lower bound to the min value in the array and clip the array
  double lower_bound = Utility::get<Utility::FIRST>( ref_data.front() );
  data_processor.removeElementsLessThanValue<Utility::FIRST>( clipped_data,
							     lower_bound );

  FRENSIE_CHECK_EQUAL( clipped_data, ref_data );

  // Set the lower bound to a value less than the min value in the array and
  // clip the array
  clipped_data = ref_data;
  lower_bound = 0.0;
  data_processor.removeElementsLessThanValue<Utility::FIRST>( clipped_data,
							     lower_bound );

  FRENSIE_CHECK_EQUAL( clipped_data, ref_data );

  // Set the lower bound to a value greater than the min value but between
  // two bin boundaries and clip the array
  clipped_data = ref_data;
  lower_bound = (Utility::get<Utility::FIRST>( ref_data[2] ) +
		 Utility::get<Utility::FIRST>( ref_data[1] ) )/2.0;
  data_processor.removeElementsLessThanValue<Utility::FIRST>( clipped_data,
							     lower_bound );

  FRENSIE_CHECK_EQUAL( clipped_data | Utility::Slice(0, clipped_data.size()),
                       (ref_data | Utility::Slice(1, ref_data.size()-1)) );

  // Set the lower bound to a value greater than the min value but on
  // a bin boundary and clip the array
  clipped_data = ref_data;
  lower_bound = Utility::get<Utility::FIRST>( ref_data[2] );
  data_processor.removeElementsLessThanValue<Utility::FIRST>( clipped_data,
							     lower_bound );

  FRENSIE_CHECK_EQUAL( clipped_data | Utility::Slice(0, clipped_data.size()),
                       (ref_data | Utility::Slice(2, ref_data.size()-2)) );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can remove elements with a tuple member greater
// than a specified value
FRENSIE_UNIT_TEST_TEMPLATE( DataProcessor,
                            removeElementsGreaterThanValue,
                            TupleTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Tuple );
  
  TestDataProcessor data_processor;

  std::vector<Tuple> ref_data( 10 ), clipped_data( 10 );

  // Load the reference array
  fillArrayOneTupleMemberData<Utility::FIRST>( ref_data );

  // Load the clipped array
  clipped_data = ref_data;

  // Set the upper bound to the max value in the array and clip the array
  double upper_bound = Utility::get<Utility::FIRST>( ref_data.back() );
  data_processor.removeElementsGreaterThanValue<Utility::FIRST>( clipped_data,
								upper_bound );

  FRENSIE_CHECK_EQUAL( clipped_data, ref_data );

  // Set the upper bound to a value greater than the max value in the array and
  // clip the array
  clipped_data = ref_data;
  upper_bound = Utility::get<Utility::FIRST>( ref_data.back() ) + 1.0;
  data_processor.removeElementsGreaterThanValue<Utility::FIRST>( clipped_data,
								upper_bound );

  FRENSIE_CHECK_EQUAL( clipped_data, ref_data );

  // Set the upper bound to a value less than the max value but between
  // two bin boundaries and clip the array
  clipped_data = ref_data;
  upper_bound = (Utility::get<Utility::FIRST>( ref_data[ref_data.size()-2] ) +
		 Utility::get<Utility::FIRST>( ref_data[ref_data.size()-3]))/2.0;
  data_processor.removeElementsGreaterThanValue<Utility::FIRST>( clipped_data,
								upper_bound );
  FRENSIE_CHECK_EQUAL( clipped_data | Utility::Slice(0, clipped_data.size()),
                       (ref_data | Utility::Slice(0, ref_data.size()-1)) );

  // Set the upper bound to a value less than the max value but on
  // a bin boundary and clip the array
  clipped_data = ref_data;
  upper_bound = Utility::get<Utility::FIRST>( ref_data[ref_data.size()-3] );
  data_processor.removeElementsGreaterThanValue<Utility::FIRST>( clipped_data,
								upper_bound );
  FRENSIE_CHECK_EQUAL( clipped_data | Utility::Slice(0, clipped_data.size()),
                       (ref_data | Utility::Slice(0, ref_data.size()-2)) );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can coarsen constant regions in an array
FRENSIE_UNIT_TEST_TEMPLATE( DataProcessor, coarsenConstantRegions, TupleTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Tuple );
  
  TestDataProcessor data_processor;

  // Load the array to be processed
  Tuple data_point;
  Utility::get<0>( data_point ) = INDEP_VAR;
  Utility::get<1>( data_point ) = DEP_VAR;
  std::vector<Tuple> coarsened_data( 10, data_point );

  // Load the reference array
  Utility::get<0>( data_point ) = INDEP_VAR;
  Utility::get<1>( data_point ) = DEP_VAR;
  std::vector<Tuple> reference_data( 2, data_point );

  // Coarsen the array
  data_processor.coarsenConstantRegions<Utility::SECOND>( coarsened_data );

  FRENSIE_CHECK_FLOATING_EQUALITY( coarsened_data, reference_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate the slopes between all pairs
// of data points in an array and store in the desired tuple member
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DataProcessor,
                                   calculateSlopes,
                                   ThreePlusTupleSingleMemberTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Member );
  FETCH_TEMPLATE_PARAM( 1, Tuple );

  constexpr size_t member = Member::value;
  
  TestDataProcessor data_processor;

  // Load the array to be processed
  std::vector<Tuple> processed_data( 10 );
  fillArrayTwoTupleMemberData<Utility::FIRST,Utility::SECOND>( processed_data );

  // Load the reference array
  std::vector<Tuple> ref_data( 10 );
  fillArrayTwoTupleMemberData<Utility::FIRST,Utility::SECOND>( ref_data );

  double slope = 0.0;
  for( unsigned int i = 0; i < ref_data.size(); ++i )
  {
    if( i != ref_data.size() - 1 )
    {
      slope = (Utility::get<1>(ref_data[i+1]) - Utility::get<1>(ref_data[i]))/
	(Utility::get<0>(ref_data[i+1]) - Utility::get<0>(ref_data[i]) );
      Utility::set<member>( ref_data[i], slope );
    }
    else
      Utility::set<member>( ref_data[i], 0.0 );
  }

  // Processes the array
  data_processor.calculateSlopes<Utility::FIRST,Utility::SECOND,member>( processed_data );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a continuous cdf from an array
// of data and store in the desired tuple member
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DataProcessor,
                                   calculateContinuousCDF,
                                   ThreePlusTupleSingleMemberTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Member );
  FETCH_TEMPLATE_PARAM( 1, Tuple );

  constexpr size_t member = Member::value;
  
  TestDataProcessor data_processor;

  // Load the array to be processed
  std::vector<Tuple> processed_data( 10 );
  fillArrayTwoTupleMemberData<Utility::FIRST,Utility::SECOND>( processed_data );

  // Load the reference array
  std::vector<Tuple> ref_data( 10 );
  fillArrayTwoTupleMemberData<Utility::FIRST,Utility::SECOND>( ref_data );
  double cdf_value;

  for( unsigned int i = 0; i < ref_data.size(); ++i )
  {
    if( i != 0 )
    {
      cdf_value += 0.5*(Utility::get<0>(ref_data[i]) - Utility::get<0>(ref_data[i-1]))*
	(Utility::get<1>(ref_data[i]) + Utility::get<1>(ref_data[i-1]));
    }
    else
      cdf_value = 0.0;

    Utility::set<member>( ref_data[i], cdf_value );
  }

  double norm_value = Utility::get<member>( ref_data.back() );
  for( size_t i = 0; i < ref_data.size(); ++i )
  {
    Utility::get<1>(ref_data[i]) /= norm_value;
    Utility::set<member>( ref_data[i],
                          Utility::get<member>( ref_data[i] )/norm_value );
  }

  // Processes the array
  data_processor.calculateContinuousCDF<Utility::FIRST,Utility::SECOND,member>( processed_data );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a continuous pdf from an array
// of data and store in the desired tuple member
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DataProcessor,
                                   calculateContinuousPDF,
                                   ThreePlusTupleSingleMemberTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Member );
  FETCH_TEMPLATE_PARAM( 1, Tuple );

  constexpr size_t member = Member::value;
  
  TestDataProcessor data_processor;

  // Load the array to be processed
  std::vector<Tuple> processed_data( 10 );
  fillArrayTwoTupleMemberData<Utility::FIRST,Utility::SECOND>( processed_data );

  // Load the reference array
  std::vector<Tuple> ref_data( 10 );
  fillArrayTwoTupleMemberData<Utility::FIRST,Utility::SECOND>( ref_data );
  double pdf_value;

  for( size_t i = 0; i < ref_data.size(); ++i )
  {
    if( i != 0 )
    {
      pdf_value = (Utility::get<1>(ref_data[i]) - Utility::get<1>(ref_data[i-1]))/
	(Utility::get<0>(ref_data[i]) - Utility::get<0>(ref_data[i-1]));
    }
    else
    {
      pdf_value = (Utility::get<1>(ref_data[i+1]) - Utility::get<1>(ref_data[i]))/
	(Utility::get<0>(ref_data[i+1]) - Utility::get<0>(ref_data[i]));
    }

    Utility::set<member>( ref_data[i], pdf_value );
  }

  // Processes the array
  data_processor.calculateContinuousPDF<Utility::FIRST,member,Utility::SECOND>( processed_data );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a discrete cdf from an array
// of data in place
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DataProcessor,
                                   calculateDiscreteCDF,
                                   TupleSingleMemberTypes )
{
  FETCH_TEMPLATE_PARAM( 0, Member );
  FETCH_TEMPLATE_PARAM( 1, Tuple );

  constexpr size_t member = Member::value;
  
  TestDataProcessor data_processor;

  // Load the array to be processed
  std::vector<Tuple> processed_data( 10 );
  fillArrayOneTupleMemberData<member>( processed_data );

  // Load the reference array
  std::vector<Tuple> ref_data( 10 );
  fillArrayOneTupleMemberData<member>( ref_data );

  for( size_t i = 1; i < ref_data.size(); ++i )
  {
    Utility::set<member>( ref_data[i], Utility::get<member>( ref_data[i-1] ) +
			 Utility::get<member>( ref_data[i] ) );
  }

  for( size_t i = 0; i < ref_data.size(); ++i )
  {
    Utility::set<member>( ref_data[i], Utility::get<member>( ref_data[i] )/
			 Utility::get<member>( ref_data.back() ) );
  }

  // Processes the array
  data_processor.calculateDiscreteCDF<member,member>( processed_data );

  FRENSIE_CHECK_FLOATING_EQUALITY( processed_data, ref_data, TOL );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can swap data in one member of a tuple with
// data in another member (for all tuples in an array)
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DataProcessor,
                                   copyTupleMemberData,
                                   TwoTupleTwoMemberTypes )
{
  FETCH_TEMPLATE_PARAM( 0, MemberT1 );
  FETCH_TEMPLATE_PARAM( 1, MemberT2 );
  FETCH_TEMPLATE_PARAM( 2, Tuple1 );
  FETCH_TEMPLATE_PARAM( 3, Tuple2 );

  constexpr size_t Member1 = MemberT1::value;
  constexpr size_t Member2 = MemberT2::value;
  
  TestDataProcessor data_processor;

  // Load the array to be processed
  std::vector<Tuple1> original_data( 10 );
  fillArrayOneTupleMemberData<Member1>( original_data );

  std::vector<Tuple2> processed_data( original_data.size() );

  // Load the reference array
  std::vector<Tuple2> ref_data( 10 );
  fillArrayOneTupleMemberData<Member2>( ref_data );

  // Process the array
  data_processor.copyTupleMemberData<Member1,Member2>( original_data,
						       processed_data );

  FRENSIE_CHECK_EQUAL( processed_data, ref_data );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can swap data in one member with data in
// another member (for all tuples in an array)
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DataProcessor,
                                   swapTupleMemberData,
                                   TupleTwoMemberTypes )
{
  FETCH_TEMPLATE_PARAM( 0, MemberT1 );
  FETCH_TEMPLATE_PARAM( 1, MemberT2 );
  FETCH_TEMPLATE_PARAM( 2, Tuple );

  constexpr size_t Member1 = MemberT1::value;
  constexpr size_t Member2 = MemberT2::value;
  
  TestDataProcessor data_processor;

  // Load the array to be processed
  std::vector<Tuple> processed_data( 10 );
  fillArrayOneTupleMemberData<Member1>( processed_data );

  // Load the reference array
  std::vector<Tuple> ref_data( 10 );
  fillArrayOneTupleMemberData<Member2>( ref_data );

  // Process the array
  data_processor.swapTupleMemberData<Member1,Member2>( processed_data );

  FRENSIE_CHECK_EQUAL( processed_data, ref_data );
}

//---------------------------------------------------------------------------//
// Check that the DataProcessor can convert an unsigned int to a string
FRENSIE_UNIT_TEST( DataProcessor, uint_to_string_test )
{
  TestDataProcessor data_processor;

  std::string shell = data_processor.uintToShellStr( SHELL );
  std::string reference_shell( SHELL_NAME );

  FRENSIE_CHECK_EQUAL( shell, reference_shell );
}

//---------------------------------------------------------------------------//
// end tstDataProcessor.cpp
//---------------------------------------------------------------------------//
