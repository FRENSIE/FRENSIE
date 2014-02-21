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

// FACEMC Includes
#include "DataProcessor.hpp"
#include "TupleMemberTraits.hpp"
#include "Tuple.hpp"
#include "FACEMC_UnitTestHarnessExtensions.hpp"

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
  typedef FACEMC::Pair<double,double> pair_d_d;			\
  typedef FACEMC::Pair<unsigned,double> pair_u_d;			\
  typedef FACEMC::Pair<double,unsigned> pair_d_u;			\
  typedef FACEMC::Trip<double,double,double> trip_d_d_d;		\
  typedef FACEMC::Trip<unsigned,double,double> trip_u_d_d;		\
  typedef FACEMC::Trip<unsigned,double,unsigned> trip_u_d_u;		\
  typedef FACEMC::Trip<double,double,unsigned> trip_d_d_u;		\
  typedef FACEMC::Trip<unsigned,unsigned,double> trip_u_u_d;		\
  typedef FACEMC::Trip<double,unsigned,double> trip_d_u_d;		\
  typedef FACEMC::Quad<double,double,double,double> quad_d_d_d_d;	\
  typedef FACEMC::Quad<unsigned,unsigned,double,double> quad_u_u_d_d;	\
  typedef FACEMC::Quad<unsigned,double,double,unsigned> quad_u_d_d_u;	\
  typedef FACEMC::Quad<unsigned,double,double,double> quad_u_d_d_d;	\
  typedef FACEMC::Quad<double,double,double,unsigned> quad_d_d_d_u;	\
  typedef FACEMC::Quad<double,double,unsigned,unsigned> quad_d_d_u_u;	\
  typedef FACEMC::Quad<double,unsigned,unsigned,double> quad_d_u_u_d;	\
  typedef FACEMC::Quad<unsigned,double,unsigned,double> quad_u_d_u_d;	\
  typedef FACEMC::Quad<unsigned,unsigned,unsigned,double> quad_u_u_u_d; \
  typedef FACEMC::Quad<unsigned,unsigned,unsigned,unsigned> quad_u_u_u_u; \
  
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
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type, \
							    name, \
							    THIRD, \
							    trip_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type, \
							    name, \
							    THIRD, \
							    quad_d_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type, \
							    name, \
							    FOURTH, \
							    quad_d_d_d_d, \
							    array )	\

#define UNIT_TEST_INSTANTIATION_MEMBER_TUPLE( type, name )		\
  TUPLE_TYPEDEFS()							\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type,		\
						      name,		\
						      SECOND,		\
						      pair_d_d )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type,		\
						      name,		\
						      SECOND,		\
						      pair_u_d )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type,		\
						      name,		\
						      SECOND,		\
						      trip_d_d_d )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type,		\
						      name,		\
						      SECOND,		\
						      trip_u_d_d )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type,		\
						      name,		\
						      THIRD,		\
						      quad_d_d_d_d )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT( type,		\
						      name,		\
						      THIRD,		\
						      quad_u_u_d_d )	\

#define UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_2_ARRAY( type, name, array ) \
  TUPLE_TYPEDEFS()							\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    FIRST,	\
							    pair_d_u,	\
							    trip_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    SECOND,	\
							    pair_d_u,	\
							    pair_u_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    THIRD,	\
							    trip_d_d_u, \
							    trip_u_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    FOURTH,	\
							    quad_u_d_d_d, \
							    quad_d_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    FIRST,	\
							    pair_d_u,	\
							    pair_u_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    SECOND,	\
							    trip_u_u_d, \
							    trip_d_u_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    THIRD,	\
							    trip_d_u_d, \
							    trip_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    FOURTH,	\
							    quad_u_u_d_d, \
							    quad_u_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    FIRST,	\
							    trip_d_d_u, \
							    trip_u_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    SECOND,	\
							    trip_d_u_d, \
							    trip_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    THIRD,	\
							    trip_d_d_d, \
							    trip_u_u_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    FOURTH,	\
							    quad_d_d_d_d, \
							    quad_u_u_u_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    FIRST,	\
							    quad_u_d_d_d, \
							    quad_d_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    SECOND,	\
							    quad_u_u_d_d, \
							    quad_u_d_d_u, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    THIRD,	\
							    quad_d_d_d_d, \
							    quad_u_u_u_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_INSTANT( type, \
							    name, \
							    FOURTH, \
							    FOURTH, \
							    quad_d_d_d_u, \
							    quad_u_u_u_u, \
							    array )	\

#define UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_1_ARRAY( type, name, array ) \
  TUPLE_TYPEDEFS()							\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    SECOND,	\
							    pair_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    THIRD,	\
							    trip_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    FOURTH,	\
							    quad_d_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    THIRD,	\
							    trip_u_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    FOURTH,	\
							    quad_u_d_u_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    FOURTH,	\
							    quad_d_d_u_u, \
							    array )	\
  
//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//

class TestDataProcessor : public FACEMC::DataProcessor
{
public:
  TestDataProcessor()
  { /* ... */ }

  virtual ~TestDataProcessor()
  { /* ... */ }
  
  void processDataFiles()
  { /* ... */ }

  // Allow public access to the DataProcessor protected member functions
  using FACEMC::DataProcessor::processContinuousData;
  using FACEMC::DataProcessor::removeElementsLessThanValue;
  using FACEMC::DataProcessor::removeElementsGreaterThanValue;
  using FACEMC::DataProcessor::coarsenConstantRegions;
  using FACEMC::DataProcessor::calculateSlopes;
  using FACEMC::DataProcessor::calculateContinuousCDF;
  using FACEMC::DataProcessor::calculateDiscreteCDF;
  using FACEMC::DataProcessor::copyTupleMemberData;
  using FACEMC::DataProcessor::swapTupleMemberData;
  using FACEMC::DataProcessor::uintToShellStr;
};

typedef FACEMC::LogLogDataProcessing LogLogDataProcessing;
typedef FACEMC::SqrSqrDataProcessing SqrSqrDataProcessing;

template<typename ProcessingPolicy>
struct ProcessingPolicyTestingTraits
{
  static const double referenceIndepValue = 0.0;
  static const double referenceDepValue = 0.0;
};

template<>
struct ProcessingPolicyTestingTraits<FACEMC::LogLogDataProcessing>
{
  static const double referenceIndepValue = LOG_INDEP_VAR;
  static const double referenceDepValue = LOG_DEP_VAR;
};

template<>
struct ProcessingPolicyTestingTraits<FACEMC::SqrSqrDataProcessing>
{
  static const double referenceIndepValue = SQR_INDEP_VAR;
  static const double referenceDepValue = SQR_DEP_VAR;
};

//---------------------------------------------------------------------------//
// Helper functions.
//---------------------------------------------------------------------------//
template<FACEMC::TupleMember member, typename T, template<typename> class Array>
void fillArrayOneTupleMemberData( Array<T> &array )
{
  typedef typename FACEMC::Traits::TupleMemberTraits<T,member>::tupleMemberType
    tupleMemberType;
  
  typename Array<T>::size_type size = FACEMC::getArraySize( array );

  if( size > 0 )
  {
    for( unsigned int i = 1; i <= size; ++i )
    {
      FACEMC::set<member>( array[i-1], static_cast<tupleMemberType>( i ) );
    }
  }
}

template<FACEMC::TupleMember indepMember,
	 FACEMC::TupleMember depMember,
	 typename T,
	 template<typename> class Array>
void fillArrayTwoTupleMemberData( Array<T> &array )
{
  typedef typename FACEMC::Traits::TupleMemberTraits<T,indepMember>::tupleMemberType indepTupleMemberType;
  typedef typename FACEMC::Traits::TupleMemberTraits<T,depMember>::tupleMemberType depTupleMemberType;
  
  typename Array<T>::size_type size = FACEMC::getArraySize( array );

  if( size > 0 )
  {
    for( unsigned int i = 0; i < size; ++i )
    {
      FACEMC::set<indepMember>( array[i],
		            static_cast<indepTupleMemberType>( i*INDEP_VAR ) );
      FACEMC::set<depMember>( array[i],
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
// Check that the DataProcessor can processes an array of FACEMC Tuple structs
// in the desired format
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( DataProcessor, 
				   processContinuousData,
				   Policy,
				   Tuple )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  Tuple data_point;
  data_point.first = INDEP_VAR;
  data_point.second = DEP_VAR;
  Teuchos::Array<Tuple> processed_data( 10, data_point );

  // Load the reference array
  data_point.first = ProcessingPolicyTestingTraits<Policy>::referenceIndepValue;
  data_point.second = ProcessingPolicyTestingTraits<Policy>::referenceDepValue;
  Teuchos::Array<Tuple> ref_data( 10, data_point );

  // Process the Array
  data_processor.processContinuousData<Policy,
				       FACEMC::FIRST,
				       FACEMC::SECOND>( processed_data );

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( processed_data, ref_data, TOL );
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
  fillArrayOneTupleMemberData<FACEMC::FIRST>( ref_data );

  // Load the clipped array
  clipped_data = ref_data;
  
  // Set the lower bound to the min value in the array and clip the array
  double lower_bound = FACEMC::get<FACEMC::FIRST>( ref_data.front() );
  data_processor.removeElementsLessThanValue<FACEMC::FIRST>( clipped_data,
							     lower_bound );
  
  FACEMC_TEST_COMPARE_ARRAYS( clipped_data, ref_data );

  // Set the lower bound to a value less than the min value in the array and
  // clip the array
  clipped_data = ref_data;
  lower_bound = 0.0;
  data_processor.removeElementsLessThanValue<FACEMC::FIRST>( clipped_data,
							     lower_bound );

  FACEMC_TEST_COMPARE_ARRAYS( clipped_data, ref_data );

  // Set the lower bound to a value greater than the min value but between
  // two bin boundaries and clip the array
  clipped_data = ref_data;
  lower_bound = (FACEMC::get<FACEMC::FIRST>( ref_data[2] ) + 
		 FACEMC::get<FACEMC::FIRST>( ref_data[1] ) )/2.0;
  data_processor.removeElementsLessThanValue<FACEMC::FIRST>( clipped_data,
							     lower_bound );

  FACEMC_TEST_COMPARE_ARRAYS( clipped_data, ref_data( 1, ref_data.size()-1 ) );

  // Set the lower bound to a value greater than the min value but on
  // a bin boundary and clip the array
  clipped_data = ref_data;
  lower_bound = FACEMC::get<FACEMC::FIRST>( ref_data[2] );
  data_processor.removeElementsLessThanValue<FACEMC::FIRST>( clipped_data,
							     lower_bound );
  
  FACEMC_TEST_COMPARE_ARRAYS( clipped_data, ref_data( 2, ref_data.size()-2 ) );
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
  fillArrayOneTupleMemberData<FACEMC::FIRST>( ref_data );

  // Load the clipped array
  clipped_data = ref_data;
  
  // Set the upper bound to the max value in the array and clip the array
  double upper_bound = FACEMC::get<FACEMC::FIRST>( ref_data.back() );
  data_processor.removeElementsGreaterThanValue<FACEMC::FIRST>( clipped_data,
								upper_bound );
  
  FACEMC_TEST_COMPARE_ARRAYS( clipped_data, ref_data );

  // Set the upper bound to a value greater than the max value in the array and
  // clip the array
  clipped_data = ref_data;
  upper_bound = FACEMC::get<FACEMC::FIRST>( ref_data.back() ) + 1.0;
  data_processor.removeElementsGreaterThanValue<FACEMC::FIRST>( clipped_data,
								upper_bound );

  FACEMC_TEST_COMPARE_ARRAYS( clipped_data, ref_data );

  // Set the upper bound to a value less than the max value but between
  // two bin boundaries and clip the array
  clipped_data = ref_data;
  upper_bound = (FACEMC::get<FACEMC::FIRST>( ref_data[ref_data.size()-2] ) + 
		 FACEMC::get<FACEMC::FIRST>( ref_data[ref_data.size()-3]))/2.0;
  data_processor.removeElementsGreaterThanValue<FACEMC::FIRST>( clipped_data,
								upper_bound );
  FACEMC_TEST_COMPARE_ARRAYS( clipped_data, ref_data( 0, ref_data.size()-1 ) );

  // Set the upper bound to a value less than the max value but on
  // a bin boundary and clip the array
  clipped_data = ref_data;
  upper_bound = FACEMC::get<FACEMC::FIRST>( ref_data[ref_data.size()-3] );
  data_processor.removeElementsGreaterThanValue<FACEMC::FIRST>( clipped_data,
								upper_bound );
  FACEMC_TEST_COMPARE_ARRAYS( clipped_data, ref_data( 0, ref_data.size()-2 ) );
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
  data_point.first = INDEP_VAR;
  data_point.second = DEP_VAR;
  Teuchos::Array<Tuple> coarsened_data( 10, data_point );

  // Load the reference array
  data_point.first = INDEP_VAR;
  data_point.second = DEP_VAR;
  Teuchos::Array<Tuple> reference_data( 2, data_point );

  // Coarsen the array
  data_processor.coarsenConstantRegions<FACEMC::SECOND>( coarsened_data );

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( coarsened_data, reference_data, TOL );
}

UNIT_TEST_INSTANTIATION_TUPLE( DataProcessor, coarsenConstantRegions );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate the slopes between all pairs
// of data points in an array and store in the desired tuple member
FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL( DataProcessor,
						       calculateSlopes,
						       member,
						       Tuple,
						       array )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  Teuchos::Array<Tuple> raw_data( 10 );
  fillArrayTwoTupleMemberData<FACEMC::FIRST,FACEMC::SECOND>( raw_data );
  array<Tuple> processed_data;
  FACEMC::copyArrayView( processed_data, raw_data() );

  // Load the reference array
  Teuchos::Array<Tuple> ref_data( 10 );
  fillArrayTwoTupleMemberData<FACEMC::FIRST,FACEMC::SECOND>( ref_data );
  
  double slope = 0.0;
  for( unsigned int i = 0; i < ref_data.size(); ++i )
  {
    if( i != ref_data.size() - 1 )
    {
      slope = (ref_data[i+1].second - ref_data[i].second)/
	(ref_data[i+1].first - ref_data[i].first);
      FACEMC::set<member>( ref_data[i], slope );
    }
    else
      FACEMC::set<member>( ref_data[i], 0.0 );
  }

  // Processes the array
  data_processor.calculateSlopes<FACEMC::FIRST,
				 FACEMC::SECOND,
				 member>( processed_data );

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( processed_data, ref_data, TOL );
}

UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_1_ARRAY( DataProcessor, calculateSlopes, Array );
UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_1_ARRAY( DataProcessor, calculateSlopes, ArrayView );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a continuous cdf from an array
// of data and store in the desired tuple member
FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL( DataProcessor,
						       calculateContinuousCDF,
						       member,
						       Tuple,
						       array )
{
  TestDataProcessor data_processor;

  // Load the array to be processed
  Teuchos::Array<Tuple> raw_data( 10 );
  fillArrayTwoTupleMemberData<FACEMC::FIRST,FACEMC::SECOND>( raw_data );
  array<Tuple> processed_data;
  FACEMC::copyArrayView( processed_data, raw_data() );

  // Load the reference array
  Teuchos::Array<Tuple> ref_data( 10 );
  fillArrayTwoTupleMemberData<FACEMC::FIRST,FACEMC::SECOND>( ref_data );
  double cdf_value;
  
  for( unsigned int i = 0; i < ref_data.size(); ++i )
  {    
    if( i != 0 )
    {
      cdf_value += 0.5*(ref_data[i].first - ref_data[i-1].first)*
	(ref_data[i].second + ref_data[i-1].second);
    }
    else
      cdf_value = 0.0;
      
    FACEMC::set<member>( ref_data[i], cdf_value );
  }
  
  double norm_value = FACEMC::get<member>( ref_data.back() );
  for( unsigned int i = 0; i < ref_data.size(); ++i )
  {
    ref_data[i].second /= norm_value;
    FACEMC::set<member>( ref_data[i], 
			 FACEMC::get<member>( ref_data[i] )/norm_value );
  }
  
  // Processes the array
  data_processor.calculateContinuousCDF<FACEMC::FIRST,
					FACEMC::SECOND,
					member>( processed_data );

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( processed_data, ref_data, TOL );
}

UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_1_ARRAY( DataProcessor, calculateContinuousCDF, Array );
UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_1_ARRAY( DataProcessor, calculateContinuousCDF, ArrayView );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can calculate a discrete cdf from an array
// of data in place
FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_DECL( DataProcessor,
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
    FACEMC::set<member>( ref_data[i], FACEMC::get<member>( ref_data[i-1] ) +
			 FACEMC::get<member>( ref_data[i] ) );
  }
  
  for( unsigned int i = 0; i < ref_data.size(); ++i )
  {
    FACEMC::set<member>( ref_data[i], FACEMC::get<member>( ref_data[i] )/
			 FACEMC::get<member>( ref_data.back() ) );
  }
  
  // Processes the array
  data_processor.calculateDiscreteCDF<member,
  				      member>( processed_data );
  
  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( processed_data, ref_data, TOL );
}

UNIT_TEST_INSTANTIATION_MEMBER_TUPLE( DataProcessor, calculateDiscreteCDF );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can swap data in one member of a tuple with
// data in another member (for all tuples in an array)
FACEMC_UNIT_TEST_MEMBER_2_TUPLE_2_ARRAY_TEMPLATE_DECL( DataProcessor,
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
  FACEMC::copyArrayView( original_data, raw_original_data() );
 
  Teuchos::Array<Tuple2> raw_processed_data( raw_original_data.size() );
  array<Tuple2> processed_data;
  FACEMC::copyArrayView( processed_data, raw_processed_data() );
  
  // Load the reference array
  Teuchos::Array<Tuple2> ref_data( 10 );
  fillArrayOneTupleMemberData<Member2>( ref_data );
  
  // Process the array
  data_processor.copyTupleMemberData<Member1,Member2>( original_data,
						       processed_data );
  
  FACEMC_TEST_COMPARE_ARRAYS( processed_data, ref_data );
}
    
UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_2_ARRAY( DataProcessor, copyTupleMemberData, Array );
UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_2_ARRAY( DataProcessor, copyTupleMemberData, ArrayView );

//---------------------------------------------------------------------------//
// Check that the DataProcessor can swap data in one member with data in 
// another member (for all tuples in an array)
FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_DECL( DataProcessor,
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
  FACEMC::copyArrayView( processed_data, raw_data() );

  // Load the reference array
  Teuchos::Array<Tuple> ref_data( 10 );
  fillArrayOneTupleMemberData<Member2>( ref_data );
  
  // Process the array
  data_processor.swapTupleMemberData<Member1,Member2>( processed_data );
  
  FACEMC_TEST_COMPARE_ARRAYS( processed_data, ref_data );
}

UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_1_ARRAY( DataProcessor, swapTupleMemberData, Array );
UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_1_ARRAY( DataProcessor, swapTupleMemberData, ArrayView );

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
