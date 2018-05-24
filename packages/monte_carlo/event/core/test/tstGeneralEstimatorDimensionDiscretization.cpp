//---------------------------------------------------------------------------//
//!
//! \file   tstGeneralEstimatorDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_GeneralEstimatorDimensionDiscretization.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_EstimatorParticleStateWrapper.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_EventUnitTestHarnessExtensions.hpp"
#include "Utility_Vector.hpp"
#include "Utility_UnitTestHarness.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )				\
  using namespace MonteCarlo;						\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, SOURCE_ENERGY_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ENERGY_DIMENSION )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, COSINE_DIMENSION )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, SOURCE_TIME_DIMENSION ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, TIME_DIMENSION )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, COLLISION_NUMBER_DIMENSION ) \

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize an estimator dimension discretization pointer
template<MonteCarlo::PhaseSpaceDimension dimension>
void initialize( std::shared_ptr<MonteCarlo::EstimatorDimensionDiscretization>&
		 dimension_discretization,
		 const bool add_discrete_lines )
{
  typedef MonteCarlo::PhaseSpaceDimensionTraits<dimension> EPSDT;

  std::vector<typename EPSDT::dimensionType> discretization( 4 );

  if( add_discrete_lines )
    discretization.resize( 9 );

  discretization[0] = 0.0;
  discretization[1] = 1e-5;
  discretization[2] = 1e-4;
  discretization[3] = 1e-3;

  if( add_discrete_lines )
  {
    discretization[4] = 1e-3;
    discretization[5] = 1e-2;
    discretization[6] = 1e-1;
    discretization[7] = 1e-1;
    discretization[8] = 1.0;
  }

  dimension_discretization.reset(
                new MonteCarlo::GeneralEstimatorDimensionDiscretization<dimension>(
							    discretization ) );
}

// Initialize an estimator dimension discretization point
template<>
void initialize<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
			std::shared_ptr<MonteCarlo::EstimatorDimensionDiscretization>&
			dimension_discretization,
			const bool )
{
  typedef MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::COLLISION_NUMBER_DIMENSION> EPSDT;

  std::vector<typename EPSDT::dimensionType> discretization( 3 );

  discretization[0] = 0;
  discretization[1] = 1;
  discretization[2] = std::numeric_limits<unsigned>::max();

  dimension_discretization.reset( new MonteCarlo::GeneralEstimatorDimensionDiscretization<MonteCarlo::COLLISION_NUMBER_DIMENSION>( discretization ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the discretized dimension can be returned
MC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
				   getDimension,
				   dimension )
{
  std::shared_ptr<MonteCarlo::EstimatorDimensionDiscretization> discretized_dimension;

  initialize<dimension>( discretized_dimension, false );

  TEST_EQUALITY_CONST( discretized_dimension->getDimension(),
		       dimension );
}

UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
			 getDimension );

//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
MC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
				   getNumberOfBins,
				   dimension )
{
  std::shared_ptr<MonteCarlo::EstimatorDimensionDiscretization> discretized_dimension;

  initialize<dimension>( discretized_dimension, false );

  TEST_EQUALITY_CONST( discretized_dimension->getNumberOfBins(), 3u );
}

UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
			 getNumberOfBins );

//---------------------------------------------------------------------------//
// Check if a value is contained in the discretization
MC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
				   isValueInDiscretization,
				   dimension )
{
  std::shared_ptr<MonteCarlo::EstimatorDimensionDiscretization> discretized_dimension;

  initialize<dimension>( discretized_dimension, false );

  typedef MonteCarlo::PhaseSpaceDimensionTraits<dimension> EPSDT;

  typename EPSDT::dimensionType value_1, value_2, value_3, value_4;

  if( dimension != MonteCarlo::COLLISION_NUMBER_DIMENSION )
  {
    value_1 = -1;
    value_2 = 0;
    value_3 = 1e-3;
    value_4 = 1e-2;
    TEST_ASSERT( !discretized_dimension->isValueInDiscretization(
						   boost::any( value_1 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization(
						   boost::any( value_2 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization(
						   boost::any( value_3 ) ) );
    TEST_ASSERT( !discretized_dimension->isValueInDiscretization(
						   boost::any( value_4 ) ) );
  }
  else
  {
    value_1 = 0;
    value_2 = 1;
    value_3 = 2;
    value_3 = -1; // max value
    TEST_ASSERT( discretized_dimension->isValueInDiscretization(
						   boost::any( value_1 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization(
						   boost::any( value_2 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization(
						   boost::any( value_3 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization(
						   boost::any( value_4 ) ) );
  }
 }

UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
			 isValueInDiscretization );

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
MC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
				   calculateBinIndex_any,
				   dimension )
{
  std::shared_ptr<MonteCarlo::EstimatorDimensionDiscretization> discretized_dimension;

  initialize<dimension>( discretized_dimension, true );

  typedef MonteCarlo::PhaseSpaceDimensionTraits<dimension> EPSDT;

  typename EPSDT::dimensionType value_1, value_2, value_3, value_4,
    value_5, value_6, value_7, value_8, value_9, value_10, value_11,
    value_12, value_13, value_14, value_15, value_16, value_17;

  if( dimension != MonteCarlo::COLLISION_NUMBER_DIMENSION )
  {
    value_1 = 0.0;
    value_2 = 5e-6;
    value_3 = 1e-5;
    value_4 = 5e-5;
    value_5 = 1e-4;
    value_6 = 5e-4;
    value_7 = 9.9999999999999e-4;
    value_8 = 1e-3;
    value_9 = 1.0000000000001e-3;
    value_10 = 5e-3;
    value_11 = 1e-2;
    value_12 = 5e-2;
    value_13 = 9.999999999999e-2;
    value_14 = 1e-1;
    value_15 = 1.000000000001e-1;
    value_16 = 5e-1;
    value_17 = 1.0;

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_1 ) ), 0u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_2 ) ), 0u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_3 ) ), 0u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_4 ) ), 1u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_5 ) ), 1u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_6 ) ), 2u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_7 ) ), 2u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_8 ) ), 3u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_9 ) ), 4u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					      boost::any( value_10 ) ), 4u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					      boost::any( value_11 ) ), 4u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					      boost::any( value_12 ) ), 5u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					      boost::any( value_13 ) ), 5u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					      boost::any( value_14 ) ), 6u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					      boost::any( value_15 ) ), 7u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					      boost::any( value_16 ) ), 7u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					      boost::any( value_17 ) ), 7u );
  }
  else
  {
    value_1 = 0;
    value_2 = 1;
    value_3 = 2;
    value_4 = -1; // max value

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_1 ) ), 0u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_2 ) ), 1u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_3 ) ), 2u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					       boost::any( value_4 ) ), 2u );
  }

  discretized_dimension->print( std::cout );
}

UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
			 calculateBinIndex_any );

//---------------------------------------------------------------------------//
// Check that a bin index can be calculated
MC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
				   calculateBinIndex_particle_state_wrapper,
				   dimension )
{
  std::shared_ptr<MonteCarlo::EstimatorDimensionDiscretization> discretized_dimension;

  initialize<dimension>( discretized_dimension, true );

  typedef MonteCarlo::PhaseSpaceDimensionTraits<dimension> EPSDT;

  typename EPSDT::dimensionType value_1, value_2, value_3, value_4,
    value_5, value_6, value_7, value_8, value_9, value_10, value_11,
    value_12, value_13, value_14, value_15, value_16, value_17;

  if( dimension != MonteCarlo::COLLISION_NUMBER_DIMENSION )
  {
    MonteCarlo::NeutronState particle( 0ull );
    MonteCarlo::EstimatorParticleStateWrapper particle_wrapper( particle );

    particle.setSourceEnergy( 1e-15 );
    particle.setEnergy( 1e-15 );
    particle.setSourceTime( 0.0 );
    particle.setTime( 0.0 );
    particle_wrapper.setAngleCosine( 0.0 );

    value_17 = 1.0;

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 0u );

    particle.setSourceEnergy( 5e-6 );
    particle.setEnergy( 5e-6 );
    particle.setSourceTime( 5e-6 );
    particle.setTime( 5e-6 );
    particle_wrapper.setAngleCosine( 5e-6 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 0u );

    particle.setSourceEnergy( 1e-5 );
    particle.setEnergy( 1e-5 );
    particle.setSourceTime( 1e-5 );
    particle.setTime( 1e-5 );
    particle_wrapper.setAngleCosine( 1e-5 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 0u );

    particle.setSourceEnergy( 5e-5 );
    particle.setEnergy( 5e-5 );
    particle.setSourceTime( 5e-5 );
    particle.setTime( 5e-5 );
    particle_wrapper.setAngleCosine( 5e-5 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 1u );

    particle.setSourceEnergy( 1e-4 );
    particle.setEnergy( 1e-4 );
    particle.setSourceTime( 1e-4 );
    particle.setTime( 1e-4 );
    particle_wrapper.setAngleCosine( 1e-4 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 1u );

    particle.setSourceEnergy( 5e-4 );
    particle.setEnergy( 5e-4 );
    particle.setSourceTime( 5e-4 );
    particle.setTime( 5e-4 );
    particle_wrapper.setAngleCosine( 5e-4 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 2u );

    particle.setSourceEnergy( 9.9999999999999e-4 ); 
    particle.setEnergy( 9.9999999999999e-4 );
    particle.setSourceTime( 9.9999999999999e-4 ); 
    particle.setTime( 9.9999999999999e-4 );
    particle_wrapper.setAngleCosine( 9.9999999999999e-4 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 2u );

    particle.setSourceEnergy( 1e-3 );
    particle.setEnergy( 1e-3 );
    particle.setSourceTime( 1e-3 );
    particle.setTime( 1e-3 );
    particle_wrapper.setAngleCosine( 1e-3 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 3u );

    particle.setSourceEnergy( 1.0000000000001e-3 );
    particle.setEnergy( 1.0000000000001e-3 );
    particle.setSourceTime( 1.0000000000001e-3 ); 
    particle.setTime( 1.0000000000001e-3 );
    particle_wrapper.setAngleCosine( 1.0000000000001e-3 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 4u );

    particle.setSourceEnergy( 5e-3 );
    particle.setEnergy( 5e-3 );
    particle.setSourceTime( 5e-3 );
    particle.setTime( 5e-3 );
    particle_wrapper.setAngleCosine( 5e-3 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 4u );

    particle.setSourceEnergy( 1e-2 );
    particle.setEnergy( 1e-2 );
    particle.setSourceTime( 1e-2 );
    particle.setTime( 1e-2 );
    particle_wrapper.setAngleCosine( 1e-2 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 4u );

    particle.setSourceEnergy( 5e-2 );
    particle.setEnergy( 5e-2 );
    particle.setSourceTime( 5e-2 );
    particle.setTime( 5e-2 );
    particle_wrapper.setAngleCosine( 5e-2 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 5u );

    particle.setSourceEnergy( 9.999999999999e-2 );
    particle.setEnergy( 9.999999999999e-2 );
    particle.setSourceTime( 9.999999999999e-2 );
    particle.setTime( 9.999999999999e-2 );
    particle_wrapper.setAngleCosine( 9.999999999999e-2 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 5u );

    particle.setSourceEnergy( 1e-1 );
    particle.setEnergy( 1e-1 );
    particle.setSourceTime( 1e-1 );
    particle.setTime( 1e-1 );
    particle_wrapper.setAngleCosine( 1e-1 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 6u );

    particle.setSourceEnergy( 1.000000000001e-1 );
    particle.setEnergy( 1.000000000001e-1 );
    particle.setSourceTime( 1.000000000001e-1 ); 
    particle.setTime( 1.000000000001e-1 );
    particle_wrapper.setAngleCosine( 1.000000000001e-1 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 7u );

    particle.setSourceEnergy( 5e-1 );
    particle.setEnergy( 5e-1 );
    particle.setSourceTime( 5e-1 );
    particle.setTime( 5e-1 );
    particle_wrapper.setAngleCosine( 5e-1 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 7u );

    particle.setSourceEnergy( 1.0 );
    particle.setEnergy( 1.0 );
    particle.setSourceTime( 1.0 );
    particle.setTime( 1.0 );
    particle_wrapper.setAngleCosine( 1.0 );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
                                                      particle_wrapper ), 7u );
  }
  else
  {
    MonteCarlo::NeutronState particle( 0ull );
    MonteCarlo::EstimatorParticleStateWrapper particle_wrapper( particle );

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					              particle_wrapper ), 0u );

    particle.incrementCollisionNumber();

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					              particle_wrapper ), 1u );

    particle.incrementCollisionNumber();

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					              particle_wrapper ), 2u );

    particle.incrementCollisionNumber();

    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex(
					              particle_wrapper ), 2u );
  }

  discretized_dimension->print( std::cout );
}

UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
			 calculateBinIndex_particle_state_wrapper );

//---------------------------------------------------------------------------//
// Check that the bin boundaries can be exported
MC_UNIT_TEST_EPSD_TEMPLATE_1_DECL( GeneralEstimatorDimensionDiscretization,
				   exportData,
				   dimension )
{
  // Set up the discretization
  typedef MonteCarlo::PhaseSpaceDimensionTraits<dimension> EPSDT;

  std::vector<typename EPSDT::dimensionType> discretization;

  if( dimension != MonteCarlo::COLLISION_NUMBER_DIMENSION )
  {
    discretization.resize( 9 );

    discretization[0] = 0.0;
    discretization[1] = 1e-5;
    discretization[2] = 1e-4;
    discretization[3] = 1e-3;
    discretization[4] = 1e-3;
    discretization[5] = 1e-2;
    discretization[6] = 1e-1;
    discretization[7] = 1e-1;
    discretization[8] = 1.0;
  }
  else
  {
    discretization.resize( 4 );

    discretization[0] = 0u;
    discretization[1] = 1u;
    discretization[2] = 2u;
    discretization[3] = std::numeric_limits<unsigned>::max();
  }

  std::shared_ptr<MonteCarlo::EstimatorDimensionDiscretization>
    discretized_dimension(
            new MonteCarlo::GeneralEstimatorDimensionDiscretization<dimension>(
							    discretization ) );

  // Set up the EstimatorHDF5FileHandler
  std::ostringstream oss;
  oss << dimension << ".h5";

  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( oss.str() );

  discretized_dimension->exportData( 0u, hdf5_file_handler );
  discretized_dimension->exportData( 10u, hdf5_file_handler );

  // Make sure the data was written to the correct estimators
  std::vector<typename EPSDT::dimensionType> discretization_copy;

  hdf5_file_handler.getEstimatorBinBoundaries<dimension>( 0u,
							  discretization_copy);

  TEST_COMPARE_ARRAYS( discretization, discretization_copy );

  hdf5_file_handler.getEstimatorBinBoundaries<dimension>( 10u,
							  discretization_copy);

  TEST_COMPARE_ARRAYS( discretization, discretization_copy );

  TEST_THROW( hdf5_file_handler.getEstimatorBinBoundaries<dimension>(
							 1u,
							 discretization_copy ),
	      std::runtime_error );
}

UNIT_TEST_INSTANTIATION( GeneralEstimatorDimensionDiscretization,
			 exportData );

//---------------------------------------------------------------------------//
// end tstGeneralEstimatorDimensionDiscretization.cpp
//---------------------------------------------------------------------------//

