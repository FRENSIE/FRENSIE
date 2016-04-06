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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_GeneralEstimatorDimensionDiscretization.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_EstimatorParticleStateWrapper.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )				\
  using namespace MonteCarlo;						\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ENERGY_DIMENSION )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, COSINE_DIMENSION )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, TIME_DIMENSION )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, COLLISION_NUMBER_DIMENSION ) \

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize an estimator dimension discretization pointer
template<MonteCarlo::PhaseSpaceDimension dimension>
void initialize( Teuchos::RCP<MonteCarlo::EstimatorDimensionDiscretization>&
		 dimension_discretization,
		 const bool add_discrete_lines )
{
  typedef MonteCarlo::PhaseSpaceDimensionTraits<dimension> EPSDT;

  Teuchos::Array<typename EPSDT::dimensionType> discretization( 4 );

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
			Teuchos::RCP<MonteCarlo::EstimatorDimensionDiscretization>&
			dimension_discretization,
			const bool )
{
  typedef MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::COLLISION_NUMBER_DIMENSION> EPSDT;

  Teuchos::Array<typename EPSDT::dimensionType> discretization( 3 );

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
  Teuchos::RCP<MonteCarlo::EstimatorDimensionDiscretization> discretized_dimension;

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
  Teuchos::RCP<MonteCarlo::EstimatorDimensionDiscretization> discretized_dimension;

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
  Teuchos::RCP<MonteCarlo::EstimatorDimensionDiscretization> discretized_dimension;

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
						   Teuchos::any( value_1 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_2 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_3 ) ) );
    TEST_ASSERT( !discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_4 ) ) );
  }
  else
  {
    value_1 = 0;
    value_2 = 1;
    value_3 = 2;
    value_3 = -1; // max value
    TEST_ASSERT( discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_1 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_2 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_3 ) ) );
    TEST_ASSERT( discretized_dimension->isValueInDiscretization( 
						   Teuchos::any( value_4 ) ) );
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
  Teuchos::RCP<MonteCarlo::EstimatorDimensionDiscretization> discretized_dimension;

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
					       Teuchos::any( value_1 ) ), 0u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_2 ) ), 0u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_3 ) ), 0u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_4 ) ), 1u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_5 ) ), 1u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_6 ) ), 2u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_7 ) ), 2u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_8 ) ), 3u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_9 ) ), 4u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_10 ) ), 4u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_11 ) ), 4u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_12 ) ), 5u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_13 ) ), 5u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_14 ) ), 6u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_15 ) ), 7u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_16 ) ), 7u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					      Teuchos::any( value_17 ) ), 7u );
  }
  else
  {
    value_1 = 0;
    value_2 = 1;
    value_3 = 2;
    value_4 = -1; // max value
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_1 ) ), 0u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_2 ) ), 1u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_3 ) ), 2u );
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
					       Teuchos::any( value_4 ) ), 2u );
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
  Teuchos::RCP<MonteCarlo::EstimatorDimensionDiscretization> discretized_dimension;

  initialize<dimension>( discretized_dimension, true );

  typedef MonteCarlo::PhaseSpaceDimensionTraits<dimension> EPSDT;

  typename EPSDT::dimensionType value_1, value_2, value_3, value_4,
    value_5, value_6, value_7, value_8, value_9, value_10, value_11,
    value_12, value_13, value_14, value_15, value_16, value_17;

  if( dimension != MonteCarlo::COLLISION_NUMBER_DIMENSION )
  {
    MonteCarlo::NeutronState particle( 0ull );
    MonteCarlo::EstimatorParticleStateWrapper particle_wrapper( particle );

    particle.setEnergy( 1e-15 );
    particle.setTime( 0.0 );
    particle_wrapper.setAngleCosine( 0.0 );
    
    value_17 = 1.0;
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 0u );

    particle.setEnergy( 5e-6 );
    particle.setTime( 5e-6 );
    particle_wrapper.setAngleCosine( 5e-6 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 0u );

    particle.setEnergy( 1e-5 );
    particle.setTime( 1e-5 );
    particle_wrapper.setAngleCosine( 1e-5 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 0u );

    particle.setEnergy( 5e-5 );
    particle.setTime( 5e-5 );
    particle_wrapper.setAngleCosine( 5e-5 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 1u );

    particle.setEnergy( 1e-4 );
    particle.setTime( 1e-4 );
    particle_wrapper.setAngleCosine( 1e-4 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 1u );

    particle.setEnergy( 5e-4 );
    particle.setTime( 5e-4 );
    particle_wrapper.setAngleCosine( 5e-4 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 2u );

    particle.setEnergy( 9.9999999999999e-4 );
    particle.setTime( 9.9999999999999e-4 );
    particle_wrapper.setAngleCosine( 9.9999999999999e-4 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 2u );

    particle.setEnergy( 1e-3 );
    particle.setTime( 1e-3 );
    particle_wrapper.setAngleCosine( 1e-3 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 3u );

    particle.setEnergy( 1.0000000000001e-3 );
    particle.setTime( 1.0000000000001e-3 );
    particle_wrapper.setAngleCosine( 1.0000000000001e-3 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 4u );

    particle.setEnergy( 5e-3 );
    particle.setTime( 5e-3 );
    particle_wrapper.setAngleCosine( 5e-3 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 4u );

    particle.setEnergy( 1e-2 );
    particle.setTime( 1e-2 );
    particle_wrapper.setAngleCosine( 1e-2 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 4u );

    particle.setEnergy( 5e-2 );
    particle.setTime( 5e-2 );
    particle_wrapper.setAngleCosine( 5e-2 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 5u );

    particle.setEnergy( 9.999999999999e-2 );
    particle.setTime( 9.999999999999e-2 );
    particle_wrapper.setAngleCosine( 9.999999999999e-2 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 5u );
    
    particle.setEnergy( 1e-1 );
    particle.setTime( 1e-1 );
    particle_wrapper.setAngleCosine( 1e-1 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 6u );

    particle.setEnergy( 1.000000000001e-1 );
    particle.setTime( 1.000000000001e-1 );
    particle_wrapper.setAngleCosine( 1.000000000001e-1 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 7u );
    
    particle.setEnergy( 5e-1 );
    particle.setTime( 5e-1 );
    particle_wrapper.setAngleCosine( 5e-1 );
    
    TEST_EQUALITY_CONST( discretized_dimension->calculateBinIndex( 
                                                      particle_wrapper ), 7u );

    particle.setEnergy( 1.0 );
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

  Teuchos::Array<typename EPSDT::dimensionType> discretization;
  
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

  Teuchos::RCP<MonteCarlo::EstimatorDimensionDiscretization> 
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
  Teuchos::Array<typename EPSDT::dimensionType> discretization_copy;

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

