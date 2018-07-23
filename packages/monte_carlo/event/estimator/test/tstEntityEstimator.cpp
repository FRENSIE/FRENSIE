//---------------------------------------------------------------------------//
//!
//! \file   tstEntityEstimator.cpp
//! \author Alex Robinson
//! \brief  Entity estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_EntityEstimator.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestEntityEstimator : public MonteCarlo::EntityEstimator
{
public:
  TestEntityEstimator( const uint32_t id,
		       const double multiplier,
		       const std::vector<uint64_t>& entity_ids,
		       const std::vector<double>& entity_norm_constants )
    : MonteCarlo::EntityEstimator( id,
                                   multiplier,
                                   entity_ids,
                                   entity_norm_constants )
  { /* ... */ }

  TestEntityEstimator( const uint32_t id,
		       const double multiplier,
		       const std::vector<uint64_t>& entity_ids )
    : MonteCarlo::EntityEstimator( id, multiplier, entity_ids )
  { /* ... */ }

  ~TestEntityEstimator()
  { /* ... */ }

  void printSummary( std::ostream& os ) const final override
  { this->printImplementation( os, "Surface" ); }

  void commitHistoryContribution() final override
  { /* ... */ }

  // Allow public access to the entity estimator protected member functions
  using MonteCarlo::EntityEstimator::commitHistoryContributionToBinOfEntity;
  using MonteCarlo::EntityEstimator::commitHistoryContributionToBinOfTotal;
};

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Set the entity estimator bins (and response functions)
void setEntityEstimatorBins( MonteCarlo::Estimator& estimator )
{
  // Set the energy bins
  std::vector<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
						       energy_bin_boundaries );

  // Set the cosine bins
  std::vector<double> cosine_bin_boundaries( 3 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = 0.0;
  cosine_bin_boundaries[2] = 1.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(
						       cosine_bin_boundaries );

  // Set the time bins
  std::vector<double> time_bin_boundaries( 3 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;

  estimator.setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(
							 time_bin_boundaries );

  // Set the collision number bins
  std::vector<unsigned> collision_number_bins( 3 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = std::numeric_limits<unsigned>::max();

  estimator.setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

  // Set the response functions
  std::vector<std::shared_ptr<const MonteCarlo::ParticleResponse> >
    response_functions( 1 );
  response_functions[0] = MonteCarlo::ParticleResponse::getDefault();

  estimator.setResponseFunctions( response_functions );
}

// Initialize the entity estimator
void initializeEntityEstimator(
                        std::shared_ptr<TestEntityEstimator>& entity_estimator,
                        const bool assign_entity_norm_consts )
{
  // Set the entity ids
  std::vector<uint64_t>
    entity_ids( 5 );
  entity_ids[0] = 0;
  entity_ids[1] = 1;
  entity_ids[2] = 2;
  entity_ids[3] = 3;
  entity_ids[4] = 4;

  // Set the entity normalization constants
  std::vector<double> entity_norm_constants( 5 );
  entity_norm_constants[0] = 1.0;
  entity_norm_constants[1] = 2.0;
  entity_norm_constants[2] = 3.0;
  entity_norm_constants[3] = 4.0;
  entity_norm_constants[4] = 5.0;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  if( assign_entity_norm_consts )
  {
    entity_estimator.reset( new TestEntityEstimator( 0ul,
						     estimator_multiplier,
						     entity_ids,
						     entity_norm_constants ) );
  }
  else
  {
    entity_estimator.reset( new TestEntityEstimator( 0ull,
                                                     estimator_multiplier,
                                                     entity_ids ) );
  }

  // Set the entity estimator bins (and response functions)
  setEntityEstimatorBins( *entity_estimator );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST( EntityEstimator, getNumberOfBins )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  FRENSIE_CHECK_EQUAL( entity_estimator->getNumberOfBins(), 24 );

  entity_estimator.reset();
  
  initializeEntityEstimator( entity_estimator, false );

  FRENSIE_CHECK_EQUAL( entity_estimator->getNumberOfBins(), 24 );
}

//---------------------------------------------------------------------------//
// Check that the number of response functions can be returned
FRENSIE_UNIT_TEST( EntityEstimator, getNumberOfResponseFunctions )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  FRENSIE_CHECK_EQUAL( entity_estimator->getNumberOfResponseFunctions(), 1 );

  entity_estimator.reset();

  initializeEntityEstimator( entity_estimator, false );

  FRENSIE_CHECK_EQUAL( entity_estimator->getNumberOfResponseFunctions(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the entity ids associated with the estimator can be returned
FRENSIE_UNIT_TEST( EntityEstimator, getEntityIds )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  std::set<uint64_t> entity_ids;
  entity_estimator->getEntityIds( entity_ids );

  FRENSIE_CHECK_EQUAL( entity_ids.size(), 5 );
}

//---------------------------------------------------------------------------//
// Check if an entity is assigned to the estimator
FRENSIE_UNIT_TEST( EntityEstimator, isEntityAssigned )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  FRENSIE_CHECK( entity_estimator->isEntityAssigned( 0 ) );
  FRENSIE_CHECK( entity_estimator->isEntityAssigned( 1 ) );
  FRENSIE_CHECK( entity_estimator->isEntityAssigned( 2 ) );
  FRENSIE_CHECK( entity_estimator->isEntityAssigned( 3 ) );
  FRENSIE_CHECK( entity_estimator->isEntityAssigned( 4 ) );
  FRENSIE_CHECK( !entity_estimator->isEntityAssigned( 5 ) );
}

//---------------------------------------------------------------------------//
// Check if the entity norm constant can be returned
FRENSIE_UNIT_TEST( EntityEstimator, getEntityNormConstant )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  FRENSIE_CHECK_EQUAL( entity_estimator->getEntityNormConstant( 0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( entity_estimator->getEntityNormConstant( 1 ), 2.0 );
  FRENSIE_CHECK_EQUAL( entity_estimator->getEntityNormConstant( 2 ), 3.0 );
  FRENSIE_CHECK_EQUAL( entity_estimator->getEntityNormConstant( 3 ), 4.0 );
  FRENSIE_CHECK_EQUAL( entity_estimator->getEntityNormConstant( 4 ), 5.0 );

  entity_estimator.reset();

  initializeEntityEstimator( entity_estimator, false );

  FRENSIE_CHECK_EQUAL( entity_estimator->getEntityNormConstant( 0 ), 1.0 );
  FRENSIE_CHECK_EQUAL( entity_estimator->getEntityNormConstant( 1 ), 1.0 );
  FRENSIE_CHECK_EQUAL( entity_estimator->getEntityNormConstant( 2 ), 1.0 );
  FRENSIE_CHECK_EQUAL( entity_estimator->getEntityNormConstant( 3 ), 1.0 );
  FRENSIE_CHECK_EQUAL( entity_estimator->getEntityNormConstant( 4 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check if the total norm constant can be returned
FRENSIE_UNIT_TEST( EntityEstimator, getTotalNormConstant )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  FRENSIE_CHECK_EQUAL( entity_estimator->getTotalNormConstant(), 15.0 );

  entity_estimator.reset();
  
  initializeEntityEstimator( entity_estimator, false );

  FRENSIE_CHECK_EQUAL( entity_estimator->getTotalNormConstant(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin
FRENSIE_UNIT_TEST( EntityEstimator, commitHistoryContributionToBinOfEntity )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  std::set<uint64_t> entity_ids;

  entity_estimator->getEntityIds( entity_ids );

  // Commit one contribution to every bin of the estimator
  for( auto&& entity_id : entity_ids )
  {
    for( size_t i = 0; i < num_estimator_bins; ++i )
    {
      entity_estimator->commitHistoryContributionToBinOfEntity( entity_id,
								i,
								0.5 );
    }
  }

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 1 );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.0 );

  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 1 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 2 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 3 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 4 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );

  // Check the entity bin data mean, re, and fom
  std::vector<double> entity_mean, entity_relative_error, entity_figure_of_merit;

  entity_estimator->getEntityBinProcessedData( 0, entity_mean, entity_relative_error, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 5.0 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );

  entity_estimator->getEntityBinProcessedData( 1, entity_mean, entity_relative_error, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 2.5 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );

  entity_estimator->getEntityBinProcessedData( 2, entity_mean, entity_relative_error, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 5.0/3 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );

  entity_estimator->getEntityBinProcessedData( 3, entity_mean, entity_relative_error, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 5.0/4 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );

  entity_estimator->getEntityBinProcessedData( 4, entity_mean, entity_relative_error, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin
FRENSIE_UNIT_TEST( EntityEstimator,
                   commitHistoryContributionToBinOfEntity_thread_safe )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  std::set<uint64_t> entity_ids;

  entity_estimator->getEntityIds( entity_ids );

  // Commit one contribution to every bin of the estimator
  for( auto&& entity_id : entity_ids )
  {
    for( size_t i = 0u; i < num_estimator_bins; ++i )
    {
      #pragma omp parallel num_threads( Utility::OpenMPProperties::getRequestedNumberOfThreads() )
      {
	entity_estimator->commitHistoryContributionToBinOfEntity(
			     entity_id,
			     i,
			     Utility::OpenMPProperties::getThreadId()+1.0 );
      }
    }
  }

  unsigned histories =
    Utility::OpenMPProperties::getRequestedNumberOfThreads();
  
  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( histories );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.0 );

  double moment_1 = histories*(histories+1.0)/2.0;
  double moment_2 = histories*(histories+1.0)*(2*histories+1.0)/6.0;

  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 1 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 2 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 3 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 4 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );

  double unnorm_mean = moment_1*10.0/histories;
  
  double rel_err = moment_2/(moment_1*moment_1) - 1.0/histories;
  
  if( histories > 1 )
    rel_err *= histories/(histories-1);

  rel_err = std::sqrt( rel_err );
  
  double fom = 0.0;

  if( rel_err > 0.0 )
    fom = 1.0/(rel_err*rel_err);

  // Check the entity bin data mean, re, and fom
  std::vector<double> entity_mean, entity_relative_error, entity_figure_of_merit;

  double mean = unnorm_mean;
  entity_estimator->getEntityBinProcessedData( 0, entity_mean, entity_relative_error, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  mean = unnorm_mean/2.0;
  entity_estimator->getEntityBinProcessedData( 1, entity_mean, entity_relative_error, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  mean = unnorm_mean/3.0;
  entity_estimator->getEntityBinProcessedData( 2, entity_mean, entity_relative_error, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  mean = unnorm_mean/4.0;
  entity_estimator->getEntityBinProcessedData( 3, entity_mean, entity_relative_error, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  mean = unnorm_mean/5.0;
  entity_estimator->getEntityBinProcessedData( 4, entity_mean, entity_relative_error, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin of the total
FRENSIE_UNIT_TEST( EntityEstimator, commitHistoryContributionToBinOfTotal )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  // Commit one contribution to every bin of the estimator
  for( size_t i = 0u; i < num_estimator_bins; ++i )
  {
    entity_estimator->commitHistoryContributionToBinOfTotal( i, 0.5 );
  }

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 2 );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.5 );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    entity_estimator->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    entity_estimator->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );

  // Check the total mean, relative error, and fom
  std::vector<double> mean, relative_error, fom;

  entity_estimator->getTotalBinProcessedData( mean, relative_error, fom );

  FRENSIE_CHECK_EQUAL( mean, std::vector<double>( 24, 5.0/30.0 ) );
  FRENSIE_CHECK_EQUAL( relative_error, std::vector<double>( 24, 1.0 ) );
  FRENSIE_CHECK_EQUAL( fom, std::vector<double>( 24, 1.0/1.5 ) );
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin of the total
FRENSIE_UNIT_TEST( EntityEstimator,
                   commitHistoryContributionToBinOfTotal_thread_safe )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  // Commit one contribution to every bin of the estimator
  for( size_t i = 0u; i < num_estimator_bins; ++i )
  {
    #pragma omp parallel num_threads( Utility::OpenMPProperties::getRequestedNumberOfThreads() )
    {
      entity_estimator->commitHistoryContributionToBinOfTotal(
		        i, Utility::OpenMPProperties::getThreadId() + 1.0 );
    }
  }

  unsigned histories =
    Utility::OpenMPProperties::getRequestedNumberOfThreads();

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( histories );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.5 );

  double moment_1 = histories*(histories+1.0)/2.0;
  double moment_2 = histories*(histories+1.0)*(2*histories+1.0)/6.0;

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    entity_estimator->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    entity_estimator->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );

  // Check the total mean, relative error, and fom
  std::vector<double> mean, relative_error, fom;

  entity_estimator->getTotalBinProcessedData( mean, relative_error, fom );

  double expected_mean = moment_1*10.0/(histories*15.0);
  double expected_rel_err = moment_2/(moment_1*moment_1) - 1.0/histories;

  if( histories > 1 )
    expected_rel_err *= histories/(histories-1);

  expected_rel_err = std::sqrt( expected_rel_err );
  
  double expected_fom = 0.0;

  if( expected_rel_err > 0.0 )
    expected_fom = 1.0/(expected_rel_err*expected_rel_err*1.5);

  FRENSIE_CHECK_EQUAL( mean, std::vector<double>( 24, expected_mean ) );
  FRENSIE_CHECK_EQUAL( relative_error, std::vector<double>( 24, expected_rel_err ) );
  FRENSIE_CHECK_EQUAL( fom, std::vector<double>( 24, expected_fom ) );
}

//---------------------------------------------------------------------------//
// Check that the total data can be returned
FRENSIE_UNIT_TEST( EntityEstimator, isTotalDataAvailable )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  FRENSIE_CHECK( !entity_estimator->isTotalDataAvailable() );

  Utility::ArrayView<const double> first_moments =
    entity_estimator->getEntityTotalDataFirstMoments( 0 );

  Utility::ArrayView<const double> second_moments =
    entity_estimator->getEntityTotalDataSecondMoments( 0 );

  Utility::ArrayView<const double> third_moments =
    entity_estimator->getEntityTotalDataThirdMoments( 0 );

  Utility::ArrayView<const double> fourth_moments =
    entity_estimator->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  first_moments = entity_estimator->getEntityTotalDataFirstMoments( 1 );
  second_moments = entity_estimator->getEntityTotalDataSecondMoments( 1 );
  third_moments = entity_estimator->getEntityTotalDataThirdMoments( 1 );
  fourth_moments = entity_estimator->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  first_moments = entity_estimator->getEntityTotalDataFirstMoments( 2 );
  second_moments = entity_estimator->getEntityTotalDataSecondMoments( 2 );
  third_moments = entity_estimator->getEntityTotalDataThirdMoments( 2 );
  fourth_moments = entity_estimator->getEntityTotalDataFourthMoments( 2 );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  first_moments = entity_estimator->getEntityTotalDataFirstMoments( 3 );
  second_moments = entity_estimator->getEntityTotalDataSecondMoments( 3 );
  third_moments = entity_estimator->getEntityTotalDataThirdMoments( 3 );
  fourth_moments = entity_estimator->getEntityTotalDataFourthMoments( 3 );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  first_moments = entity_estimator->getEntityTotalDataFirstMoments( 4 );
  second_moments = entity_estimator->getEntityTotalDataSecondMoments( 4 );
  third_moments = entity_estimator->getEntityTotalDataThirdMoments( 4 );
  fourth_moments = entity_estimator->getEntityTotalDataFourthMoments( 4 );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  first_moments = entity_estimator->getTotalDataFirstMoments();
  second_moments = entity_estimator->getTotalDataSecondMoments();
  third_moments = entity_estimator->getTotalDataThirdMoments();
  fourth_moments = entity_estimator->getTotalDataFourthMoments();

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin of the total
FRENSIE_UNIT_TEST( EntityEstimator, resetData )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  // Commit one contribution to every bin of the estimator
  for( size_t i = 0u; i < num_estimator_bins; ++i )
  {
    entity_estimator->commitHistoryContributionToBinOfTotal( i, 0.5 );
  }

  // Reset the estimator data
  entity_estimator->resetData();

  // Make sure the bins have not been changed
  FRENSIE_CHECK_EQUAL( entity_estimator->getNumberOfBins(), 24 );

  // Make sure the response functions have not changed
  FRENSIE_CHECK_EQUAL( entity_estimator->getNumberOfResponseFunctions(), 1 );

  Utility::ArrayView<const double> entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.0 ) );

  Utility::ArrayView<const double> total_bin_first_moments =
    entity_estimator->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    entity_estimator->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 24, 0.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the estimator data can be reduced
FRENSIE_UNIT_TEST( EntityEstimator, reduceData )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  for( size_t i = 0; i < num_estimator_bins; ++i )
  {
    entity_estimator->commitHistoryContributionToBinOfEntity( 0, i, 1.0 );
    entity_estimator->commitHistoryContributionToBinOfEntity( 2, i, 1.0 );
    entity_estimator->commitHistoryContributionToBinOfEntity( 4, i, 1.0 );

    entity_estimator->commitHistoryContributionToBinOfTotal( i, 2.0 );
  }

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  comm->barrier();

  entity_estimator->reduceData( *comm, 0 );

  unsigned procs = comm->size();

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( procs );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.0 );

  if( comm->rank() == 0 )
  {
    // Check the total bin data moments
    Utility::ArrayView<const double> first_moments =
      entity_estimator->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> second_moments =
      entity_estimator->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 2*procs ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 4*procs ) );

    // Check the entity bin data moments
    first_moments = entity_estimator->getEntityBinDataFirstMoments( 0 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, procs ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, procs ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 1 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 2 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, procs ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, procs ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 3 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 4 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, procs ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, procs ) );
  }
  // Make sure that estimators on other processes were reset
  else
  {
    // Check the total bin data moments
    Utility::ArrayView<const double> first_moments =
      entity_estimator->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> second_moments =
      entity_estimator->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );

    // Check the entity bin data moments
    first_moments = entity_estimator->getEntityBinDataFirstMoments( 0 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 1 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 2 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 3 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 4 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

int threads;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "threads",
                                        threads, 1,
                                        "Number of threads to use" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Set up the global OpenMP session
  if( Utility::OpenMPProperties::isOpenMPUsed() )
    Utility::OpenMPProperties::setNumberOfThreads( threads );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// tstEntityEstimator.cpp
//---------------------------------------------------------------------------//
