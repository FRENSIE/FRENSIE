//---------------------------------------------------------------------------//
//!
//! \file   tstEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard entity estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "MonteCarlo_PhotonState.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int )

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
template<typename EntityId>
class TestStandardEntityEstimator : public MonteCarlo::StandardEntityEstimator<EntityId>
{
public:
  TestStandardEntityEstimator( const unsigned long long id,
			       const double multiplier,
			       const Teuchos::Array<EntityId>& entity_ids,
			       const Teuchos::Array<double>& entity_norm_constants )
    : MonteCarlo::StandardEntityEstimator<EntityId>( id,
						 multiplier,
						 entity_ids,
						 entity_norm_constants )
  { /* ... */ }

  ~TestStandardEntityEstimator()
  { /* ... */ }

  void print( std::ostream& os ) const
  { this->printImplementation( os, "Surface" ); }

  // Allow public access to the standard entity estimator protected mem. funcs.
  using MonteCarlo::StandardEntityEstimator<EntityId>::addPartialHistoryContribution;
};

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Set the standard entity estimator bins (and response functions)
void setEstimatorBins( Teuchos::RCP<MonteCarlo::Estimator>& estimator )
{  
  // Set the energy bins
  Teuchos::Array<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1.0;

  estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(energy_bin_boundaries);

  // Set the cosine bins
  Teuchos::Array<double> cosine_bin_boundaries( 3 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = 0.0;
  cosine_bin_boundaries[2] = 1.0;

  estimator->setBinBoundaries<MonteCarlo::COSINE_DIMENSION>(cosine_bin_boundaries);

  // Set the time bins
  Teuchos::Array<double> time_bin_boundaries( 3 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;

  estimator->setBinBoundaries<MonteCarlo::TIME_DIMENSION>( time_bin_boundaries );

  // Set the collision number bins
  Teuchos::Array<unsigned> collision_number_bins( 3 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = std::numeric_limits<unsigned>::max();

  estimator->setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
						       collision_number_bins );

  // Set the response functions
  Teuchos::Array<Teuchos::RCP<MonteCarlo::ResponseFunction> > 
    response_functions( 1 );
  response_functions[0] = MonteCarlo::ResponseFunction::default_response_function;

  estimator->setResponseFunctions( response_functions );
}

// Initialize the standard entity estimator (general)
template<typename EntityId>
void initializeStandardEntityEstimator(
       Teuchos::RCP<TestStandardEntityEstimator<EntityId> >& entity_estimator )
{ /* ... */ }

// Initialize the standard entity estimator (int)
template<>
void initializeStandardEntityEstimator<int>( 
	           Teuchos::RCP<TestStandardEntityEstimator<int> >& estimator )
{
  // Set the entity ids
  Teuchos::Array<int> entity_ids( 2 );
  entity_ids[0] = 0;
  entity_ids[1] = 1;

  // Set the entity normalization constants
  Teuchos::Array<double> entity_norm_constants( 2 );
  entity_norm_constants[0] = 1.0;
  entity_norm_constants[1] = 2.0;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset(new TestStandardEntityEstimator<int>(0ull,
						       estimator_multiplier,
						       entity_ids,
						       entity_norm_constants));

  // Set the entity estimator bins (and response functions)
  Teuchos::RCP<MonteCarlo::Estimator> base_estimator = 
    Teuchos::rcp_dynamic_cast<MonteCarlo::Estimator>( estimator );

  setEstimatorBins( base_estimator );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( StandardEntityEstimator,
				   getNumberOfBins,
				   EntityId )
{
  Teuchos::RCP<TestStandardEntityEstimator<EntityId> > estimator;
  initializeStandardEntityEstimator( estimator );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 24 );
}

UNIT_TEST_INSTANTIATION( StandardEntityEstimator, getNumberOfBins );

//---------------------------------------------------------------------------//
// Check that the number of response functions can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( StandardEntityEstimator,
				   getNumberOfResponseFunctions,
				   EntityId )
{
  Teuchos::RCP<TestStandardEntityEstimator<EntityId> > estimator;
  initializeStandardEntityEstimator( estimator );

  TEST_EQUALITY_CONST( estimator->getNumberOfResponseFunctions(), 1 );
}

UNIT_TEST_INSTANTIATION( StandardEntityEstimator, 
			 getNumberOfResponseFunctions );

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( StandardEntityEstimator,
				   addPartialHistoryContribution,
				   EntityId )
{
  Teuchos::RCP<TestStandardEntityEstimator<EntityId> > estimator;
  initializeStandardEntityEstimator( estimator );
  
  MonteCarlo::PhotonState particle( 0ull );
  particle.setEnergy( 1.0 );
  particle.setTime( 1e2 );
  particle.incrementCollisionNumber();

  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );

  estimator->addPartialHistoryContribution( 0, particle, 0.0, 1.0 );

  TEST_ASSERT( estimator->hasUncommittedHistoryContribution() );

  particle.setEnergy( 1e-1 );
  particle.setTime( 1e4 );
  particle.incrementCollisionNumber();

  estimator->addPartialHistoryContribution( 1, particle, 0.0, 1.0 );

  TEST_ASSERT( estimator->hasUncommittedHistoryContribution() );

  estimator->commitHistoryContribution();

  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );

  MonteCarlo::Estimator::setNumberOfHistories( 1.0 );
  MonteCarlo::Estimator::setEndTime( 1.0 );

  std::cout << std::endl << *estimator << std::endl;
}

UNIT_TEST_INSTANTIATION( StandardEntityEstimator,
			 addPartialHistoryContribution );

//---------------------------------------------------------------------------//
// end tstStandardEntityEstimator.cpp
//---------------------------------------------------------------------------//

	      
