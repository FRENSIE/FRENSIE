//---------------------------------------------------------------------------//
//!
//! \file   tstEstimator.cpp
//! \author Alex Robinson
//! \brief  Entity estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_EntityEstimator.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
typedef Geometry::ModuleTraits::InternalCellHandle CellId;

#define UNIT_TEST_INSTANTIATION( type, name )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, CellId ) \

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
template<typename EntityId>
class TestEntityEstimator : public MonteCarlo::EntityEstimator<EntityId>
{  
public:
  TestEntityEstimator( const unsigned long long id,
		       const double multiplier,
		       const Teuchos::Array<EntityId>& entity_ids,
		       const Teuchos::Array<double>& entity_norm_constants )
    : MonteCarlo::EntityEstimator<EntityId>( id, 
					 multiplier, 
					 entity_ids, 
					 entity_norm_constants )
  { /* ... */ }

  TestEntityEstimator( const unsigned long long id,
		       const double multiplier,
		       const Teuchos::Array<EntityId>& entity_ids )
    : MonteCarlo::EntityEstimator<EntityId>( id, multiplier, entity_ids )
  { /* ... */ }

  ~TestEntityEstimator()
  { /* ... */ }
  
  void print( std::ostream& os ) const
  { this->printImplementation( os, "Surface" ); }

  void enableThreadSupport( const unsigned num_threads )
  { /* ... */ }

  void commitHistoryContribution()
  { /* ... */ }

  // Allow public access to the entity estimator protected member functions
  using MonteCarlo::EntityEstimator<EntityId>::getEntityNormConstant;
  using MonteCarlo::EntityEstimator<EntityId>::getTotalNormConstant;
  using MonteCarlo::EntityEstimator<EntityId>::commitHistoryContributionToBinOfEntity;
};

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Set the entity estimator bins (and response functions)
template<typename EntityId>
void setEntityEstimatorBins( 
	       Teuchos::RCP<TestEntityEstimator<EntityId> >& entity_estimator )
{
  // Use a base class pointer to test the virtual functions
  Teuchos::RCP<MonteCarlo::Estimator> base_estimator =
    Teuchos::rcp_dynamic_cast<MonteCarlo::Estimator>( entity_estimator );
  
  // Set the energy bins
  Teuchos::Array<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1.0;

  base_estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( 
						       energy_bin_boundaries );

  // Set the cosine bins
  Teuchos::Array<double> cosine_bin_boundaries( 3 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = 0.0;
  cosine_bin_boundaries[2] = 1.0;

  base_estimator->setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( 
						       cosine_bin_boundaries );

  // Set the time bins
  Teuchos::Array<double> time_bin_boundaries( 3 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;

  base_estimator->setBinBoundaries<MonteCarlo::TIME_DIMENSION>( 
							 time_bin_boundaries );

  // Set the collision number bins
  Teuchos::Array<unsigned> collision_number_bins( 3 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = std::numeric_limits<unsigned>::max();

  base_estimator->setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
						       collision_number_bins );

  // Set the response functions
  Teuchos::Array<Teuchos::RCP<MonteCarlo::ResponseFunction> > 
    response_functions( 1 );
  response_functions[0] = MonteCarlo::ResponseFunction::default_response_function;

  base_estimator->setResponseFunctions( response_functions );
}

// Initialize the entity estimator (general)
template<typename EntityId>
void initializeEntityEstimator( 
		Teuchos::RCP<TestEntityEstimator<EntityId> >& entity_estimator,
		const bool assign_entity_norm_consts )
{ /* ... */ }

// Initialize the entity estimator (int)
template<>
void 
initializeEntityEstimator<Geometry::ModuleTraits::InternalCellHandle>( 
                     Teuchos::RCP<TestEntityEstimator<Geometry::ModuleTraits::InternalCellHandle> >& entity_estimator,
		     const bool assign_entity_norm_consts )
{  
  // Set the entity ids
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> 
    entity_ids( 5 );
  entity_ids[0] = 0;
  entity_ids[1] = 1;
  entity_ids[2] = 2;
  entity_ids[3] = 3;
  entity_ids[4] = 4;
  
  // Set the entity normalization constants
  Teuchos::Array<double> entity_norm_constants( 5 );
  entity_norm_constants[0] = 1.0;
  entity_norm_constants[1] = 2.0;
  entity_norm_constants[2] = 3.0;
  entity_norm_constants[3] = 4.0;
  entity_norm_constants[4] = 5.0;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  if( assign_entity_norm_consts )
  {
    entity_estimator.reset( 
     new TestEntityEstimator<Geometry::ModuleTraits::InternalCellHandle>(
						     0ull,
						     estimator_multiplier,
						     entity_ids,
						     entity_norm_constants ) );
  }
  else
  {
    entity_estimator.reset( 
     new TestEntityEstimator<Geometry::ModuleTraits::InternalCellHandle>(
							  0ull,
							  estimator_multiplier,
							  entity_ids ) );
  }

  // Set the entity estimator bins (and response functions)
  setEntityEstimatorBins<Geometry::ModuleTraits::InternalCellHandle>( 
							    entity_estimator );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   getNumberOfBins,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  TEST_EQUALITY_CONST( entity_estimator->getNumberOfBins(), 24 );
  
  initializeEntityEstimator( entity_estimator, false );

  TEST_EQUALITY_CONST( entity_estimator->getNumberOfBins(), 24 );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, getNumberOfBins );

//---------------------------------------------------------------------------//
// Check that the number of response functions can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   getNumberOfResponseFunctions,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;
  
  initializeEntityEstimator( entity_estimator, true );

  TEST_EQUALITY_CONST( entity_estimator->getNumberOfResponseFunctions(), 1 );

  initializeEntityEstimator( entity_estimator, false );

  TEST_EQUALITY_CONST( entity_estimator->getNumberOfResponseFunctions(), 1 );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, getNumberOfResponseFunctions );

//---------------------------------------------------------------------------//
// Check that the entity ids associated with the estimator can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   getEntityIds,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;
  typename MonteCarlo::EntityEstimator<EntityId>::EntityIdSet entity_ids;

  initializeEntityEstimator( entity_estimator, true );

  entity_estimator->getEntityIds( entity_ids );

  TEST_EQUALITY_CONST( entity_ids.size(), 5 );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, getEntityIds );

//---------------------------------------------------------------------------//
// Check if an entity is assigned to the estimator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   isEntityAssigned,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  initializeEntityEstimator( entity_estimator, true );

  TEST_ASSERT( entity_estimator->isEntityAssigned( 0 ) );
  TEST_ASSERT( entity_estimator->isEntityAssigned( 1 ) );
  TEST_ASSERT( entity_estimator->isEntityAssigned( 2 ) );
  TEST_ASSERT( entity_estimator->isEntityAssigned( 3 ) );
  TEST_ASSERT( entity_estimator->isEntityAssigned( 4 ) );
  TEST_ASSERT( !entity_estimator->isEntityAssigned( 5 ) );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, isEntityAssigned );

//---------------------------------------------------------------------------//
// Check if the entity norm constant can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   getEntityNormConstant,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  initializeEntityEstimator( entity_estimator, true );

  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 0 ), 1.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 1 ), 2.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 2 ), 3.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 3 ), 4.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 4 ), 5.0 );

  initializeEntityEstimator( entity_estimator, false );

  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 0 ), 1.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 1 ), 1.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 2 ), 1.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 3 ), 1.0 );
  TEST_EQUALITY_CONST( entity_estimator->getEntityNormConstant( 4 ), 1.0 );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, getEntityNormConstant );

//---------------------------------------------------------------------------//
// Check if the total norm constant can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   getTotalNormConstant,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  initializeEntityEstimator( entity_estimator, true );

  TEST_EQUALITY_CONST( entity_estimator->getTotalNormConstant(), 15.0 );
  
  initializeEntityEstimator( entity_estimator, false );

  TEST_EQUALITY_CONST( entity_estimator->getTotalNormConstant(), 1.0 );
}

UNIT_TEST_INSTANTIATION( EntityEstimator, getTotalNormConstant );

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( EntityEstimator,
				   commitHistoryContributionToBinOfEntity,
				   EntityId )
{
  Teuchos::RCP<TestEntityEstimator<EntityId> > entity_estimator;

  initializeEntityEstimator( entity_estimator, false );

  unsigned num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  typename MonteCarlo::EntityEstimator<EntityId>::EntityIdSet entity_ids;
  
  entity_estimator->getEntityIds( entity_ids );

  typename MonteCarlo::EntityEstimator<EntityId>::EntityIdSet::const_iterator
    entity_id, end_entity_id;
  entity_id = entity_ids.begin();
  end_entity_id = entity_ids.end();
  
  // Commit one contribution to every bin of the estimator - if there is an
  // error with the estimator bins, an exception (or segfault) will occur
  while( entity_id != end_entity_id )
  {
    for( unsigned i = 0u; i < num_estimator_bins; ++i )
    {
      entity_estimator->commitHistoryContributionToBinOfEntity( *entity_id,
								i,
								1.0 );
    }

    ++entity_id;
  }

  MonteCarlo::Estimator::setNumberOfHistories( 1.0 );
  MonteCarlo::Estimator::setEndTime( 1.0 );

  std::cout << std::endl << *entity_estimator << std::endl;
}

UNIT_TEST_INSTANTIATION( EntityEstimator, 
			 commitHistoryContributionToBinOfEntity );


//---------------------------------------------------------------------------//
// tstEntityEstimator.cpp
//---------------------------------------------------------------------------//
