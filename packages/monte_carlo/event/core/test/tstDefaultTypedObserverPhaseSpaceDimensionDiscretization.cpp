//---------------------------------------------------------------------------//
//!
//! \file   tstDefaultTypedObserverPhaseSpaceDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Default typed observer phase space dimension disc. unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>

// FRENSIE Includes
#include "MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef std::tuple<
  std::integral_constant<MonteCarlo::ObserverPhaseSpaceDimension,MonteCarlo::OBSERVER_COSINE_DIMENSION>,
  std::integral_constant<MonteCarlo::ObserverPhaseSpaceDimension,MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION>,
  std::integral_constant<MonteCarlo::ObserverPhaseSpaceDimension,MonteCarlo::OBSERVER_ENERGY_DIMENSION>,
  std::integral_constant<MonteCarlo::ObserverPhaseSpaceDimension,MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION>,
  std::integral_constant<MonteCarlo::ObserverPhaseSpaceDimension,MonteCarlo::OBSERVER_TIME_DIMENSION>
  > OrderedContinuousPhaseSpaceDimensions;

typedef std::tuple<
  std::integral_constant<MonteCarlo::ObserverPhaseSpaceDimension,MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>
  > OrderedDiscretePhaseSpaceDimensions;

typedef std::tuple<
  std::integral_constant<MonteCarlo::ObserverPhaseSpaceDimension,MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION>
  > UnorderedPhaseSpaceDimensions;

typedef decltype(std::tuple_cat(OrderedContinuousPhaseSpaceDimensions(),OrderedDiscretePhaseSpaceDimensions(),UnorderedPhaseSpaceDimensions())) PhaseSpaceDimensions;

typedef std::tuple<
  std::tuple<boost::archive::xml_oarchive,boost::archive::xml_iarchive>,
  std::tuple<boost::archive::text_oarchive,boost::archive::text_iarchive>,
  std::tuple<boost::archive::binary_oarchive,boost::archive::binary_iarchive>,
  std::tuple<Utility::HDF5OArchive,Utility::HDF5IArchive>
  > TestArchives;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize an observer phase space dimension discretization
template<MonteCarlo::ObserverPhaseSpaceDimension dimension>
void initialize(
  std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>&
  dimension_discretization,
  const bool add_discrete_lines )
{
  typedef MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension> DiscretizationType;

  typename DiscretizationType::InputDataType discretization( 4 );

  discretization[0] = 0.0;
  discretization[1] = 1e-5;
  discretization[2] = 1e-4;
  discretization[3] = 1e-3;

  if( add_discrete_lines )
  {
    discretization.resize( 9 );
    
    discretization[4] = 1e-3;
    discretization[5] = 1e-2;
    discretization[6] = 1e-1;
    discretization[7] = 1e-1;
    discretization[8] = 1.0;
  }

  dimension_discretization.reset( new DiscretizationType( discretization ) );
}

// Initialize an observer phase space dimension discretization
template<>
void initialize<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
  std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>&
  dimension_discretization,
  const bool )
{
  typedef MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION> DiscretizationType;

  typename DiscretizationType::InputDataType discretization( 3 );

  discretization[0] = 0;
  discretization[1] = 1;
  discretization[2] = 10;

  dimension_discretization.reset( new DiscretizationType( discretization ) );
}

// Initialize an observer phase space dimension discretization
template<>
void initialize<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION>(
  std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>&
  dimension_discretization,
  const bool )
{
  typedef MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION> DiscretizationType;

  typename DiscretizationType::InputDataType discretization( 3 );

  discretization[0].insert( 0 );
  discretization[1].insert( 0 );
  discretization[1].insert( 1 );
  discretization[2].insert( 2 );

  dimension_discretization.reset( new DiscretizationType( discretization ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the discretized dimension can be returned
FRENSIE_UNIT_TEST_TEMPLATE( DefaultTypedObserverPhaseSpaceDimension,
                            getDimension,
                            PhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedObserverPhaseSpaceDimension );

  constexpr MonteCarlo::ObserverPhaseSpaceDimension dimension =
    WrappedObserverPhaseSpaceDimension::value;

  std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
    discretized_dimension;

  initialize<dimension>( discretized_dimension, false );

  FRENSIE_CHECK_EQUAL( discretized_dimension->getDimension(), dimension );
}

//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST_TEMPLATE( DefaultTypedObserverPhaseSpaceDimension,
                            getNumberOfBins,
                            PhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedObserverPhaseSpaceDimension );

  constexpr MonteCarlo::ObserverPhaseSpaceDimension dimension =
    WrappedObserverPhaseSpaceDimension::value;

  std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
    discretized_dimension;

  initialize<dimension>( discretized_dimension, false );

  FRENSIE_CHECK_EQUAL( discretized_dimension->getNumberOfBins(), 3 );
}

//---------------------------------------------------------------------------//
// Check if a value is contained in the discretization
FRENSIE_UNIT_TEST_TEMPLATE( DefaultTypedObserverPhaseSpaceDimension,
                            isValueInDiscretization_ordered_continuous,
                            OrderedContinuousPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedObserverPhaseSpaceDimension );

  constexpr MonteCarlo::ObserverPhaseSpaceDimension dimension =
    WrappedObserverPhaseSpaceDimension::value;

  std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
    discretized_dimension;

  initialize<dimension>( discretized_dimension, false );

  FRENSIE_CHECK( !discretized_dimension->isValueInDiscretization( boost::any( -1.0 ) ) );
  FRENSIE_CHECK( discretized_dimension->isValueInDiscretization( boost::any( 0.0 ) ) );
  FRENSIE_CHECK( discretized_dimension->isValueInDiscretization( boost::any( 1e-3 ) ) );
  FRENSIE_CHECK( !discretized_dimension->isValueInDiscretization( boost::any( 1e-2 ) ) );
}

//---------------------------------------------------------------------------//
// Check if a value is contained in the discretization
FRENSIE_UNIT_TEST_TEMPLATE( DefaultTypedObserverPhaseSpaceDimension,
                            isValueInDiscretization_ordered_discrete,
                            OrderedDiscretePhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedObserverPhaseSpaceDimension );

  constexpr MonteCarlo::ObserverPhaseSpaceDimension dimension =
    WrappedObserverPhaseSpaceDimension::value;

  typedef typename MonteCarlo::ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType DimensionType;

  std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
    discretized_dimension;

  initialize<dimension>( discretized_dimension, false );

  FRENSIE_CHECK( discretized_dimension->isValueInDiscretization( boost::any( (DimensionType)0 ) ) );
  FRENSIE_CHECK( discretized_dimension->isValueInDiscretization( boost::any( (DimensionType)1 ) ) );
  FRENSIE_CHECK( discretized_dimension->isValueInDiscretization( boost::any( (DimensionType)10 ) ) );
  FRENSIE_CHECK( !discretized_dimension->isValueInDiscretization( boost::any( (DimensionType)11 ) ) );
}

//---------------------------------------------------------------------------//
// Check if a value is contained in the discretization
FRENSIE_UNIT_TEST_TEMPLATE( DefaultTypedObserverPhaseSpaceDimension,
                            isValueInDiscretization_unordered,
                            UnorderedPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedObserverPhaseSpaceDimension );

  constexpr MonteCarlo::ObserverPhaseSpaceDimension dimension =
    WrappedObserverPhaseSpaceDimension::value;

  typedef typename MonteCarlo::ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType DimensionType;

  std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
    discretized_dimension;

  initialize<dimension>( discretized_dimension, false );

  FRENSIE_CHECK( discretized_dimension->isValueInDiscretization( boost::any( (DimensionType)0 ) ) );
  FRENSIE_CHECK( discretized_dimension->isValueInDiscretization( boost::any( (DimensionType)1 ) ) );
  FRENSIE_CHECK( discretized_dimension->isValueInDiscretization( boost::any( (DimensionType)2 ) ) );
  FRENSIE_CHECK( !discretized_dimension->isValueInDiscretization( boost::any( (DimensionType)3 ) ) );
}

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
FRENSIE_UNIT_TEST_TEMPLATE( DefaultTypedObserverPhaseSpaceDimension,
                            calculateBinIndex_ordered_continuous,
                            OrderedContinuousPhaseSpaceDimensions )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedObserverPhaseSpaceDimension );

  constexpr MonteCarlo::ObserverPhaseSpaceDimension dimension =
    WrappedObserverPhaseSpaceDimension::value;

  std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
    discretized_dimension;

  initialize<dimension>( discretized_dimension, true );

  MonteCarlo::ObserverPhaseSpaceDimensionDiscretization::BinIndexArray
    bin_indices;

  discretized_dimension->calculateBinIndicesOfValue( boost::any(0.0), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(5e-6), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(1e-5), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 0 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(5e-5), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(1e-4), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 1 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(5e-4), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(9.9999999999999e-4), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 2 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(1e-3), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 3 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(1.0000000000001e-3), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(5e-3), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(1e-2), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 4 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(5e-2), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 5 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(9.999999999999e-2), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 5 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(1e-1), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 6 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(1.000000000001e-1), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 7 );

  discretized_dimension->calculateBinIndicesOfValue( boost::any(0.5), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 7 );

  bin_indices.clear();

  discretized_dimension->calculateBinIndicesOfValue( boost::any(1.0), bin_indices );
  
  FRENSIE_REQUIRE_EQUAL( bin_indices.size(), 1 );
  FRENSIE_CHECK_EQUAL( bin_indices.front(), 7 );

  bin_indices.clear();
  

}

// //---------------------------------------------------------------------------//
// // Check that a bin index can be calculated
// MC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
// 				   calculateBinIndex_any,
// 				   dimension )
// {
//   std::shared_ptr<MonteCarlo::EstimatorDimensionDiscretization> discretized_dimension;

//   initialize<dimension>( discretized_dimension, true );

//   typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<dimension> OPSDT;

//   typename OPSDT::dimensionType value_1, value_2, value_3, value_4,
//     value_5, value_6, value_7, value_8, value_9, value_10, value_11,
//     value_12, value_13, value_14, value_15, value_16, value_17;

//   if( dimension != MonteCarlo::COLLISION_NUMBER_DIMENSION )
//   {
//     value_1 = 0.0;
//     value_2 = 5e-6;
//     value_3 = 1e-5;
//     value_4 = 5e-5;
//     value_5 = 1e-4;
//     value_6 = 5e-4;
//     value_7 = 9.9999999999999e-4;
//     value_8 = 1e-3;
//     value_9 = 1.0000000000001e-3;
//     value_10 = 5e-3;
//     value_11 = 1e-2;
//     value_12 = 5e-2;
//     value_13 = 9.999999999999e-2;
//     value_14 = 1e-1;
//     value_15 = 1.000000000001e-1;
//     value_16 = 5e-1;
//     value_17 = 1.0;

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_1 ) ), 0u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_2 ) ), 0u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_3 ) ), 0u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_4 ) ), 1u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_5 ) ), 1u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_6 ) ), 2u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_7 ) ), 2u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_8 ) ), 3u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_9 ) ), 4u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					      boost::any( value_10 ) ), 4u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					      boost::any( value_11 ) ), 4u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					      boost::any( value_12 ) ), 5u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					      boost::any( value_13 ) ), 5u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					      boost::any( value_14 ) ), 6u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					      boost::any( value_15 ) ), 7u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					      boost::any( value_16 ) ), 7u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					      boost::any( value_17 ) ), 7u );
//   }
//   else
//   {
//     value_1 = 0;
//     value_2 = 1;
//     value_3 = 2;
//     value_4 = -1; // max value

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_1 ) ), 0u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_2 ) ), 1u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_3 ) ), 2u );
//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					       boost::any( value_4 ) ), 2u );
//   }

//   discretized_dimension->print( std::cout );
// }

// UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
// 			 calculateBinIndex_any );

// //---------------------------------------------------------------------------//
// // Check that a bin index can be calculated
// MC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
// 				   calculateBinIndex_particle_state_wrapper,
// 				   dimension )
// {
//   std::shared_ptr<MonteCarlo::EstimatorDimensionDiscretization> discretized_dimension;

//   initialize<dimension>( discretized_dimension, true );

//   typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<dimension> OPSDT;

//   typename OPSDT::dimensionType value_1, value_2, value_3, value_4,
//     value_5, value_6, value_7, value_8, value_9, value_10, value_11,
//     value_12, value_13, value_14, value_15, value_16, value_17;

//   if( dimension != MonteCarlo::COLLISION_NUMBER_DIMENSION )
//   {
//     MonteCarlo::NeutronState particle( 0ull );
//     MonteCarlo::ObserverParticleStateWrapper particle_wrapper( particle );

//     particle.setSourceEnergy( 1e-15 );
//     particle.setEnergy( 1e-15 );
//     particle.setSourceTime( 0.0 );
//     particle.setTime( 0.0 );
//     particle_wrapper.setAngleCosine( 0.0 );

//     value_17 = 1.0;

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 0u );

//     particle.setSourceEnergy( 5e-6 );
//     particle.setEnergy( 5e-6 );
//     particle.setSourceTime( 5e-6 );
//     particle.setTime( 5e-6 );
//     particle_wrapper.setAngleCosine( 5e-6 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 0u );

//     particle.setSourceEnergy( 1e-5 );
//     particle.setEnergy( 1e-5 );
//     particle.setSourceTime( 1e-5 );
//     particle.setTime( 1e-5 );
//     particle_wrapper.setAngleCosine( 1e-5 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 0u );

//     particle.setSourceEnergy( 5e-5 );
//     particle.setEnergy( 5e-5 );
//     particle.setSourceTime( 5e-5 );
//     particle.setTime( 5e-5 );
//     particle_wrapper.setAngleCosine( 5e-5 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 1u );

//     particle.setSourceEnergy( 1e-4 );
//     particle.setEnergy( 1e-4 );
//     particle.setSourceTime( 1e-4 );
//     particle.setTime( 1e-4 );
//     particle_wrapper.setAngleCosine( 1e-4 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 1u );

//     particle.setSourceEnergy( 5e-4 );
//     particle.setEnergy( 5e-4 );
//     particle.setSourceTime( 5e-4 );
//     particle.setTime( 5e-4 );
//     particle_wrapper.setAngleCosine( 5e-4 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 2u );

//     particle.setSourceEnergy( 9.9999999999999e-4 ); 
//     particle.setEnergy( 9.9999999999999e-4 );
//     particle.setSourceTime( 9.9999999999999e-4 ); 
//     particle.setTime( 9.9999999999999e-4 );
//     particle_wrapper.setAngleCosine( 9.9999999999999e-4 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 2u );

//     particle.setSourceEnergy( 1e-3 );
//     particle.setEnergy( 1e-3 );
//     particle.setSourceTime( 1e-3 );
//     particle.setTime( 1e-3 );
//     particle_wrapper.setAngleCosine( 1e-3 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 3u );

//     particle.setSourceEnergy( 1.0000000000001e-3 );
//     particle.setEnergy( 1.0000000000001e-3 );
//     particle.setSourceTime( 1.0000000000001e-3 ); 
//     particle.setTime( 1.0000000000001e-3 );
//     particle_wrapper.setAngleCosine( 1.0000000000001e-3 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 4u );

//     particle.setSourceEnergy( 5e-3 );
//     particle.setEnergy( 5e-3 );
//     particle.setSourceTime( 5e-3 );
//     particle.setTime( 5e-3 );
//     particle_wrapper.setAngleCosine( 5e-3 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 4u );

//     particle.setSourceEnergy( 1e-2 );
//     particle.setEnergy( 1e-2 );
//     particle.setSourceTime( 1e-2 );
//     particle.setTime( 1e-2 );
//     particle_wrapper.setAngleCosine( 1e-2 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 4u );

//     particle.setSourceEnergy( 5e-2 );
//     particle.setEnergy( 5e-2 );
//     particle.setSourceTime( 5e-2 );
//     particle.setTime( 5e-2 );
//     particle_wrapper.setAngleCosine( 5e-2 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 5u );

//     particle.setSourceEnergy( 9.999999999999e-2 );
//     particle.setEnergy( 9.999999999999e-2 );
//     particle.setSourceTime( 9.999999999999e-2 );
//     particle.setTime( 9.999999999999e-2 );
//     particle_wrapper.setAngleCosine( 9.999999999999e-2 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 5u );

//     particle.setSourceEnergy( 1e-1 );
//     particle.setEnergy( 1e-1 );
//     particle.setSourceTime( 1e-1 );
//     particle.setTime( 1e-1 );
//     particle_wrapper.setAngleCosine( 1e-1 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 6u );

//     particle.setSourceEnergy( 1.000000000001e-1 );
//     particle.setEnergy( 1.000000000001e-1 );
//     particle.setSourceTime( 1.000000000001e-1 ); 
//     particle.setTime( 1.000000000001e-1 );
//     particle_wrapper.setAngleCosine( 1.000000000001e-1 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 7u );

//     particle.setSourceEnergy( 5e-1 );
//     particle.setEnergy( 5e-1 );
//     particle.setSourceTime( 5e-1 );
//     particle.setTime( 5e-1 );
//     particle_wrapper.setAngleCosine( 5e-1 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 7u );

//     particle.setSourceEnergy( 1.0 );
//     particle.setEnergy( 1.0 );
//     particle.setSourceTime( 1.0 );
//     particle.setTime( 1.0 );
//     particle_wrapper.setAngleCosine( 1.0 );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
//                                                       particle_wrapper ), 7u );
//   }
//   else
//   {
//     MonteCarlo::NeutronState particle( 0ull );
//     MonteCarlo::ObserverParticleStateWrapper particle_wrapper( particle );

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					              particle_wrapper ), 0u );

//     particle.incrementCollisionNumber();

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					              particle_wrapper ), 1u );

//     particle.incrementCollisionNumber();

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					              particle_wrapper ), 2u );

//     particle.incrementCollisionNumber();

//     TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
// 					              particle_wrapper ), 2u );
//   }

//   discretized_dimension->print( std::cout );
// }

// UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
// 			 calculateBinIndex_particle_state_wrapper );

// //---------------------------------------------------------------------------//
// // Check that the bin boundaries can be exported
// MC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
// 				   exportData,
// 				   dimension )
// {
//   // Set up the discretization
//   typedef MonteCarlo::ObserverPhaseSpaceDimensionTraits<dimension> OPSDT;

//   std::vector<typename OPSDT::dimensionType> discretization;

//   if( dimension != MonteCarlo::COLLISION_NUMBER_DIMENSION )
//   {
//     discretization.resize( 9 );

//     discretization[0] = 0.0;
//     discretization[1] = 1e-5;
//     discretization[2] = 1e-4;
//     discretization[3] = 1e-3;
//     discretization[4] = 1e-3;
//     discretization[5] = 1e-2;
//     discretization[6] = 1e-1;
//     discretization[7] = 1e-1;
//     discretization[8] = 1.0;
//   }
//   else
//   {
//     discretization.resize( 4 );

//     discretization[0] = 0u;
//     discretization[1] = 1u;
//     discretization[2] = 2u;
//     discretization[3] = std::numeric_limits<unsigned>::max();
//   }

//   std::shared_ptr<MonteCarlo::EstimatorDimensionDiscretization>
//     discretized_dimension(
//             new MonteCarlo::GeneralEstimatorDimensionDiscretization<dimension>(
// 							    discretization ) );

//   // Set up the EstimatorHDF5FileHandler
//   std::ostringstream oss;
//   oss << dimension << ".h5";

//   MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( oss.str() );

//   discretized_dimension->exportData( 0u, hdf5_file_handler );
//   discretized_dimension->exportData( 10u, hdf5_file_handler );

//   // Make sure the data was written to the correct estimators
//   std::vector<typename OPSDT::dimensionType> discretization_copy;

//   hdf5_file_handler.getEstimatorBinBoundaries<dimension>( 0u,
// 							  discretization_copy);

//   TEST_COMPARE_ARRAYS( discretization, discretization_copy );

//   hdf5_file_handler.getEstimatorBinBoundaries<dimension>( 10u,
// 							  discretization_copy);

//   TEST_COMPARE_ARRAYS( discretization, discretization_copy );

//   TEST_THROW( hdf5_file_handler.getEstimatorBinBoundaries<dimension>(
// 							 1u,
// 							 discretization_copy ),
// 	      std::runtime_error );
// }

// UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
// 			 exportData );

//---------------------------------------------------------------------------//
// end tstGeneralEstimatorDimensionDiscretization.cpp
//---------------------------------------------------------------------------//

