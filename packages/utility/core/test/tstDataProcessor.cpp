//---------------------------------------------------------------------------//
//!
//! \file   tstDataProcessor.cpp
//! \author Alex Robinson
//! \brief  DataProcessor class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "Utility_DataProcessor.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

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
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define TUPLE_TYPEDEFS()					\
  typedef Utility::Pair<double,double> pair_d_d;			\
  typedef Utility::Pair<unsigned,double> pair_u_d;			\
  typedef Utility::Pair<double,unsigned> pair_d_u;			\
  typedef Utility::Trip<double,double,double> trip_d_d_d;		\
  typedef Utility::Trip<unsigned,double,double> trip_u_d_d;		\
  typedef Utility::Trip<unsigned,double,unsigned> trip_u_d_u;		\
  typedef Utility::Trip<double,double,unsigned> trip_d_d_u;		\
  typedef Utility::Trip<unsigned,unsigned,double> trip_u_u_d;		\
  typedef Utility::Trip<double,unsigned,double> trip_d_u_d;		\
  typedef Utility::Quad<double,double,double,double> quad_d_d_d_d;	\
  typedef Utility::Quad<unsigned,unsigned,double,double> quad_u_u_d_d;	\
  typedef Utility::Quad<unsigned,double,double,unsigned> quad_u_d_d_u;	\
  typedef Utility::Quad<unsigned,double,double,double> quad_u_d_d_d;	\
  typedef Utility::Quad<double,double,double,unsigned> quad_d_d_d_u;	\
  typedef Utility::Quad<double,double,unsigned,unsigned> quad_d_d_u_u;	\
  typedef Utility::Quad<double,unsigned,unsigned,double> quad_d_u_u_d;	\
  typedef Utility::Quad<unsigned,double,unsigned,double> quad_u_d_u_d;	\
  typedef Utility::Quad<unsigned,unsigned,unsigned,double> quad_u_u_u_d; \
  typedef Utility::Quad<unsigned,unsigned,unsigned,unsigned> quad_u_u_u_u; \

#define UNIT_TEST_INSTANTIATION_POLICY( type, name )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type,				\
					name,				\
					LogLogDataProcessing )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type,				\
					name,				\
					SqrSqrDataProcessing ) \

#define UNIT_TEST_INSTANTIATION_POLICY_TUPLE( type, name )		\
  TUPLE_TYPEDEFS()							\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type,				\
					name,				\
					LogLogDataProcessing,	\
					pair_d_d )			\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type,				\
					name,				\
					LogLogDataProcessing,	\
					trip_d_d_d )			\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type,				\
					name,				\
					LogLogDataProcessing,	\
					quad_d_d_d_d )			\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type,				\
					name,				\
					SqrSqrDataProcessing, \
					pair_d_d )			\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type,				\
					name,				\
					SqrSqrDataProcessing, \
					trip_d_d_d )			\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type,				\
					name,				\
					SqrSqrDataProcessing, \
					quad_d_d_d_d )			\

#define UNIT_TEST_INSTANTIATION_TUPLE( type, name )			\
  TUPLE_TYPEDEFS()							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_d_d )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_d_d_d )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_d_d_d_d )	\

#define UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_1_ARRAY( type, name, array ) \
  TUPLE_TYPEDEFS()							\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type, \
							    name, \
							    THIRD, \
							    trip_d_d_d, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type, \
							    name, \
							    THIRD, \
							    quad_d_d_d_d, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type, \
							    name, \
							    FOURTH, \
							    quad_d_d_d_d, \
							    array )	\

#define UNIT_TEST_INSTANTIATION_MEMBER_TUPLE( type, name )		\
  TUPLE_TYPEDEFS()							\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type,		\
						      name,		\
						      SECOND,		\
						      pair_d_d )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type,		\
						      name,		\
						      SECOND,		\
						      pair_u_d )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type,		\
						      name,		\
						      SECOND,		\
						      trip_d_d_d )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type,		\
						      name,		\
						      SECOND,		\
						      trip_u_d_d )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type,		\
						      name,		\
						      THIRD,		\
						      quad_d_d_d_d )	\
  UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type,		\
						      name,		\
						      THIRD,		\
						      quad_u_u_d_d )	\

#define UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_2_ARRAY( type, name, array ) \
  TUPLE_TYPEDEFS()							\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    FIRST,	\
							    pair_d_u,	\
							    trip_d_d_u, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    SECOND,	\
							    pair_d_u,	\
							    pair_u_d,	\
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    THIRD,	\
							    trip_d_d_u, \
							    trip_u_d_d, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    FOURTH,	\
							    quad_u_d_d_d, \
							    quad_d_d_d_u, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    FIRST,	\
							    pair_d_u,	\
							    pair_u_d,	\
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    SECOND,	\
							    trip_u_u_d, \
							    trip_d_u_d, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    THIRD,	\
							    trip_d_u_d, \
							    trip_d_d_u, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    FOURTH,	\
							    quad_u_u_d_d, \
							    quad_u_d_d_u, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    FIRST,	\
							    trip_d_d_u, \
							    trip_u_d_d, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    SECOND,	\
							    trip_d_u_d, \
							    trip_d_d_u, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    THIRD,	\
							    trip_d_d_d, \
							    trip_u_u_d, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    FOURTH,	\
							    quad_d_d_d_d, \
							    quad_u_u_u_d, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    FIRST,	\
							    quad_u_d_d_d, \
							    quad_d_d_d_u, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    SECOND,	\
							    quad_u_u_d_d, \
							    quad_u_d_d_u, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    THIRD,	\
							    quad_d_d_d_d, \
							    quad_u_u_u_d, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type, \
							    name, \
							    FOURTH, \
							    FOURTH, \
							    quad_d_d_d_u, \
							    quad_u_u_u_u, \
							    array )	\

#define UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_1_ARRAY( type, name, array ) \
  TUPLE_TYPEDEFS()							\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    SECOND,	\
							    pair_d_d,	\
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    THIRD,	\
							    trip_d_d_d, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    FOURTH,	\
							    quad_d_d_d_d, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    THIRD,	\
							    trip_u_d_d, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    FOURTH,	\
							    quad_u_d_u_d, \
							    array )	\
  UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    FOURTH,	\
							    quad_d_d_u_u, \
							    array )	\

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
template<Utility::TupleMember member, typename T, template<typename> class Array>
void fillArrayOneTupleMemberData( Array<T> &array )
{
  typedef typename Utility::TupleElement<member,T>::type tupleMemberType;

  typename Array<T>::size_type size = Utility::getArraySize( array );

  if( size > 0 )
  {
    for( unsigned int i = 1; i <= size; ++i )
    {
      Utility::set<member>( array[i-1], static_cast<tupleMemberType>( i ) );
    }
  }
}

template<Utility::TupleMember indepMember,
	 Utility::TupleMember depMember,
	 typename T,
	 template<typename> class Array>
void fillArrayTwoTupleMemberData( Array<T> &array )
{
  typedef typename Utility::TupleElement<indepMember,T>::type indepTupleMemberType;
  typedef typename Utility::TupleElement<depMember,T>::type depTupleMemberType;

  typename Array<T>::size_type size = Utility::getArraySize( array );

  if( size > 0 )
  {
    for( unsigned int i = 0; i < size; ++i )
    {
      Utility::set<indepMember>( array[i],
		            static_cast<indepTupleMemberType>( i*INDEP_VAR ) );
      Utility::set<depMember>( array[i],
		                static_cast<depTupleMemberType>( i*DEP_VAR ) );
    }
  }
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the DataProcessingPolicies correctly process data
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( DataProcessor,
				   DataProcessingPolicy,
				   Policy )
{
  double processed_indep_var, processed_dep_var;
  processed_indep_var = Policy::processIndependentVar( INDEP_VAR );
  processed_dep_var = Policy::processDependentVar( DEP_VAR );

  double ref_indep_var, ref_dep_var;
  ref_indep_var = ProcessingPolicyTestingTraits<Policy>::referenceIndepValue;
  ref_dep_var = ProcessingPolicyTestingTraits<Policy>::referenceDepValue;

  TEST_FLOATING_EQUALITY( processed_indep_var, ref_indep_var, TOL );
  TEST_FLOATING_EQUALITY( processed_dep_var, ref_dep_var, TOL );
}

UNIT_TEST_INSTANTIATION_POLICY( DataProcessor, DataProcessingPolicy );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can processes an array of UTILITY Tuple structs
// in the desired format
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( DataProcessor,
				   processContinuousData,
				   Policy,
				   Tuple )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  Tuple data_point;
  Utility::get<0>( data_point ) = INDEP_VAR;
  Utility::get<1>( data_point ) = DEP_VAR;
  Teuchos::Array<Tuple> processed_data( 10, data_point );

  // Load the reference array
  Utility::get<0>( data_point ) = ProcessingPolicyTestingTraits<Policy>::referenceIndepValue;
  Utility::get<1>( data_point ) = ProcessingPolicyTestingTraits<Policy>::referenceDepValue;
  Teuchos::Array<Tuple> ref_data( 10, data_point );

  // Process the Array
  data_processor.processContinuousData<Policy,
				       Utility::FIRST,
				       Utility::SECOND>( processed_data );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_data, ref_data, TOL );
}

UNIT_TEST_INSTANTIATION_POLICY_TUPLE( DataProcessor, processContinuousData );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can remove elements with a tuple member less
// than a specified value
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( DataProcessor,
				   removeElementsLessThanValue,
				   Tuple )
{
  TestDataProcessor data_processor;

  Teuchos::Array<Tuple> ref_data( 10 ), clipped_data( 10 );

  // Load the reference array
  fillArrayOneTupleMemberData<Utility::FIRST>( ref_data );

  // Load the clipped array
  clipped_data = ref_data;

  // Set the lower bound to the min value in the array and clip the array
  double lower_bound = Utility::get<Utility::FIRST>( ref_data.front() );
  data_processor.removeElementsLessThanValue<Utility::FIRST>( clipped_data,
							     lower_bound );

  UTILITY_TEST_COMPARE_ARRAYS( clipped_data, ref_data );

  // Set the lower bound to a value less than the min value in the array and
  // clip the array
  clipped_data = ref_data;
  lower_bound = 0.0;
  data_processor.removeElementsLessThanValue<Utility::FIRST>( clipped_data,
							     lower_bound );

  UTILITY_TEST_COMPARE_ARRAYS( clipped_data, ref_data );

  // Set the lower bound to a value greater than the min value but between
  // two bin boundaries and clip the array
  clipped_data = ref_data;
  lower_bound = (Utility::get<Utility::FIRST>( ref_data[2] ) +
		 Utility::get<Utility::FIRST>( ref_data[1] ) )/2.0;
  data_processor.removeElementsLessThanValue<Utility::FIRST>( clipped_data,
							     lower_bound );

  UTILITY_TEST_COMPARE_ARRAYS( clipped_data, ref_data( 1, ref_data.size()-1 ) );

  // Set the lower bound to a value greater than the min value but on
  // a bin boundary and clip the array
  clipped_data = ref_data;
  lower_bound = Utility::get<Utility::FIRST>( ref_data[2] );
  data_processor.removeElementsLessThanValue<Utility::FIRST>( clipped_data,
							     lower_bound );

  UTILITY_TEST_COMPARE_ARRAYS( clipped_data, ref_data( 2, ref_data.size()-2 ) );
}

UNIT_TEST_INSTANTIATION_TUPLE( DataProcessor, removeElementsLessThanValue );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can remove elements with a tuple member greater
// than a specified value
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( DataProcessor,
				   removeElementsGreaterThanValue,
				   Tuple )
{
  TestDataProcessor data_processor;

  Teuchos::Array<Tuple> ref_data( 10 ), clipped_data( 10 );

  // Load the reference array
  fillArrayOneTupleMemberData<Utility::FIRST>( ref_data );

  // Load the clipped array
  clipped_data = ref_data;

  // Set the upper bound to the max value in the array and clip the array
  double upper_bound = Utility::get<Utility::FIRST>( ref_data.back() );
  data_processor.removeElementsGreaterThanValue<Utility::FIRST>( clipped_data,
								upper_bound );

  UTILITY_TEST_COMPARE_ARRAYS( clipped_data, ref_data );

  // Set the upper bound to a value greater than the max value in the array and
  // clip the array
  clipped_data = ref_data;
  upper_bound = Utility::get<Utility::FIRST>( ref_data.back() ) + 1.0;
  data_processor.removeElementsGreaterThanValue<Utility::FIRST>( clipped_data,
								upper_bound );

  UTILITY_TEST_COMPARE_ARRAYS( clipped_data, ref_data );

  // Set the upper bound to a value less than the max value but between
  // two bin boundaries and clip the array
  clipped_data = ref_data;
  upper_bound = (Utility::get<Utility::FIRST>( ref_data[ref_data.size()-2] ) +
		 Utility::get<Utility::FIRST>( ref_data[ref_data.size()-3]))/2.0;
  data_processor.removeElementsGreaterThanValue<Utility::FIRST>( clipped_data,
								upper_bound );
  UTILITY_TEST_COMPARE_ARRAYS( clipped_data, ref_data( 0, ref_data.size()-1 ) );

  // Set the upper bound to a value less than the max value but on
  // a bin boundary and clip the array
  clipped_data = ref_data;
  upper_bound = Utility::get<Utility::FIRST>( ref_data[ref_data.size()-3] );
  data_processor.removeElementsGreaterThanValue<Utility::FIRST>( clipped_data,
								upper_bound );
  UTILITY_TEST_COMPARE_ARRAYS( clipped_data, ref_data( 0, ref_data.size()-2 ) );
}

UNIT_TEST_INSTANTIATION_TUPLE( DataProcessor, removeElementsGreaterThanValue );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can coarsen constant regions in an array
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( DataProcessor,
				   coarsenConstantRegions,
				   Tuple )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  Tuple data_point;
  Utility::get<0>( data_point ) = INDEP_VAR;
  Utility::get<1>( data_point ) = DEP_VAR;
  Teuchos::Array<Tuple> coarsened_data( 10, data_point );

  // Load the reference array
  Utility::get<0>( data_point ) = INDEP_VAR;
  Utility::get<1>( data_point ) = DEP_VAR;
  Teuchos::Array<Tuple> reference_data( 2, data_point );

  // Coarsen the array
  data_processor.coarsenConstantRegions<Utility::SECOND>( coarsened_data );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( coarsened_data, reference_data, TOL );
}

UNIT_TEST_INSTANTIATION_TUPLE( DataProcessor, coarsenConstantRegions );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate the slopes between all pairs
// of data points in an array and store in the desired tuple member
UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL( DataProcessor,
						       calculateSlopes,
						       member,
						       Tuple,
						       array )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  Teuchos::Array<Tuple> raw_data( 10 );
  fillArrayTwoTupleMemberData<Utility::FIRST,Utility::SECOND>( raw_data );
  array<Tuple> processed_data;
  Utility::copyArrayView( processed_data, raw_data() );

  // Load the reference array
  Teuchos::Array<Tuple> ref_data( 10 );
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
  data_processor.calculateSlopes<Utility::FIRST,
				 Utility::SECOND,
				 member>( processed_data );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_data, ref_data, TOL );
}

UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_1_ARRAY( DataProcessor, calculateSlopes, Array );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a continuous cdf from an array
// of data and store in the desired tuple member
UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL( DataProcessor,
						       calculateContinuousCDF,
						       member,
						       Tuple,
						       array )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  Teuchos::Array<Tuple> raw_data( 10 );
  fillArrayTwoTupleMemberData<Utility::FIRST,Utility::SECOND>( raw_data );
  array<Tuple> processed_data;
  Utility::copyArrayView( processed_data, raw_data() );

  // Load the reference array
  Teuchos::Array<Tuple> ref_data( 10 );
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
  for( unsigned int i = 0; i < ref_data.size(); ++i )
  {
    Utility::get<1>(ref_data[i]) /= norm_value;
    Utility::set<member>( ref_data[i],
                          Utility::get<member>( ref_data[i] )/norm_value );
  }

  // Processes the array
  data_processor.calculateContinuousCDF<Utility::FIRST,
					Utility::SECOND,
					member>( processed_data );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_data, ref_data, TOL );
}

UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_1_ARRAY( DataProcessor, calculateContinuousCDF, Array );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a continuous pdf from an array
// of data and store in the desired tuple member
UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL( DataProcessor,
							calculateContinuousPDF,
							member,
							Tuple,
							array )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  Teuchos::Array<Tuple> raw_data( 10 );
  fillArrayTwoTupleMemberData<Utility::FIRST,Utility::SECOND>( raw_data );
  array<Tuple> processed_data;
  Utility::copyArrayView( processed_data, raw_data() );

  // Load the reference array
  Teuchos::Array<Tuple> ref_data( 10 );
  fillArrayTwoTupleMemberData<Utility::FIRST,Utility::SECOND>( ref_data );
  double pdf_value;

  for( unsigned int i = 0; i < ref_data.size(); ++i )
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
  data_processor.calculateContinuousPDF<Utility::FIRST,
					member,
					Utility::SECOND>( processed_data );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_data, ref_data, TOL );
}

UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_1_ARRAY( DataProcessor, calculateContinuousPDF, Array );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a discrete cdf from an array
// of data in place
UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_DECL( DataProcessor,
						 calculateDiscreteCDF,
						 member,
						 Tuple )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  Teuchos::Array<Tuple> processed_data( 10 );
  fillArrayOneTupleMemberData<member>( processed_data );

  // Load the reference array
  Teuchos::Array<Tuple> ref_data( 10 );
  fillArrayOneTupleMemberData<member>( ref_data );

  for( unsigned int i = 1; i < ref_data.size(); ++i )
  {
    Utility::set<member>( ref_data[i], Utility::get<member>( ref_data[i-1] ) +
			 Utility::get<member>( ref_data[i] ) );
  }

  for( unsigned int i = 0; i < ref_data.size(); ++i )
  {
    Utility::set<member>( ref_data[i], Utility::get<member>( ref_data[i] )/
			 Utility::get<member>( ref_data.back() ) );
  }

  // Processes the array
  data_processor.calculateDiscreteCDF<member,
  				      member>( processed_data );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_data, ref_data, TOL );
}

UNIT_TEST_INSTANTIATION_MEMBER_TUPLE( DataProcessor, calculateDiscreteCDF );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can swap data in one member of a tuple with
// data in another member (for all tuples in an array)
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_DECL( DataProcessor,
						       copyTupleMemberData,
						       Member1,
						       Member2,
						       Tuple1,
						       Tuple2,
						       array )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  Teuchos::Array<Tuple1> raw_original_data( 10 );
  fillArrayOneTupleMemberData<Member1>( raw_original_data );
  array<Tuple1>  original_data;
  Utility::copyArrayView( original_data, raw_original_data() );

  Teuchos::Array<Tuple2> raw_processed_data( raw_original_data.size() );
  array<Tuple2> processed_data;
  Utility::copyArrayView( processed_data, raw_processed_data() );

  // Load the reference array
  Teuchos::Array<Tuple2> ref_data( 10 );
  fillArrayOneTupleMemberData<Member2>( ref_data );

  // Process the array
  data_processor.copyTupleMemberData<Member1,Member2>( original_data,
						       processed_data );

  UTILITY_TEST_COMPARE_ARRAYS( processed_data, ref_data );
}

UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_2_ARRAY( DataProcessor, copyTupleMemberData, Array );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can swap data in one member with data in
// another member (for all tuples in an array)
UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_DECL( DataProcessor,
						       swapTupleMemberData,
						       Member1,
						       Member2,
						       Tuple,
						       array )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  Teuchos::Array<Tuple> raw_data( 10 );
  fillArrayOneTupleMemberData<Member1>( raw_data );
  array<Tuple>  processed_data;
  Utility::copyArrayView( processed_data, raw_data() );

  // Load the reference array
  Teuchos::Array<Tuple> ref_data( 10 );
  fillArrayOneTupleMemberData<Member2>( ref_data );

  // Process the array
  data_processor.swapTupleMemberData<Member1,Member2>( processed_data );

  UTILITY_TEST_COMPARE_ARRAYS( processed_data, ref_data );
}

UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_1_ARRAY( DataProcessor, swapTupleMemberData, Array );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can convert an unsigned int to a string
TEUCHOS_UNIT_TEST( DataProcessor, uint_to_string_test )
{
  TestDataProcessor data_processor;

  std::string shell = data_processor.uintToShellStr( SHELL );
  std::string reference_shell( SHELL_NAME );

  TEST_EQUALITY( shell, reference_shell );
}

//---------------------------------------------------------------------------//
// end tstDataProcessor.cpp
//---------------------------------------------------------------------------//
