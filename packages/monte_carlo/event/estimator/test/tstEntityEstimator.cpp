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

  //! Check if the estimator is a cell estimator
  bool isCellEstimator() const final override
  { return false; }

  //! Check if the estimator is a surface estimator
  bool isSurfaceEstimator() const final override
  { return false; }

  //! Check if the estimator is a mesh estimator
  bool isMeshEstimator() const final override
  { return false; }

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
// Check if snapshots can be enabled on entity bins
FRENSIE_UNIT_TEST( EntityEstimator, enableSnapshotsOnEntityBins )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  FRENSIE_CHECK( !entity_estimator->areSnapshotsOnEntityBinsEnabled() );

  entity_estimator->enableSnapshotsOnEntityBins();

  FRENSIE_CHECK( entity_estimator->areSnapshotsOnEntityBinsEnabled() );
}

//---------------------------------------------------------------------------//
// Check if histograms can be enabled on entity bins
FRENSIE_UNIT_TEST( EntityEstimator, enableSampleMomentHistogramsOnEntityBins )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  FRENSIE_CHECK( !entity_estimator->areSampleMomentHistogramsOnEntityBinsEnabled() );

  entity_estimator->enableSampleMomentHistogramsOnEntityBins();

  FRENSIE_CHECK( entity_estimator->areSampleMomentHistogramsOnEntityBinsEnabled() );
}

//---------------------------------------------------------------------------//
// Check that the sample moment histogram bins can be set
FRENSIE_UNIT_TEST( EntityEstimator, setSampleMomentHistogramBins )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  entity_estimator->enableSampleMomentHistogramsOnEntityBins();

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  std::set<uint64_t> entity_ids;

  entity_estimator->getEntityIds( entity_ids );

  // Check the entity bin histograms (default)
  Utility::SampleMomentHistogram<double> histogram;

  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
  
  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                           expected_histogram_bins );
    }
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
  }

  std::shared_ptr<const std::vector<double> > custom_histogram_bins =
    std::make_shared<std::vector<double> >( Utility::fromString<std::vector<double> >( "{0.0, 1.0, 2.0, 3.0, 4.0, 5.0}" ) );

  entity_estimator->setSampleMomentHistogramBins( custom_histogram_bins );

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                           *custom_histogram_bins );
    }
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         *custom_histogram_bins );
  }
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin
FRENSIE_UNIT_TEST( EntityEstimator,
                   commitHistoryContributionToBinOfEntity_no_histogram )
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

  Utility::ArrayView<const double> entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, 0.125 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, 0.0625 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 1 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 1 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 1 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, 0.125 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, 0.0625 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 2 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 2 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 2 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, 0.125 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, 0.0625 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 3 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 3 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 3 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, 0.125 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, 0.0625 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 4 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 4 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 4 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, 0.125 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, 0.0625 ) );

  // Check the entity bin data mean, re, and fom
  std::vector<double> entity_mean, entity_relative_error,
    entity_variance_of_variance, entity_figure_of_merit;
  std::map<std::string,std::vector<double> > processed_data;

  entity_estimator->getEntityBinProcessedData( 0, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );
  entity_estimator->getEntityBinProcessedData( 0, processed_data );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 5.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 24, 5.0 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 24, 0.0 ) );

  entity_estimator->getEntityBinProcessedData( 1, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );
  entity_estimator->getEntityBinProcessedData( 1, processed_data );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 2.5 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 24, 2.5 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 24, 0.0 ) );

  entity_estimator->getEntityBinProcessedData( 2, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );
  entity_estimator->getEntityBinProcessedData( 2, processed_data );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 5.0/3 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 24, 5.0/3 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 24, 0.0 ) );

  entity_estimator->getEntityBinProcessedData( 3, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );
  entity_estimator->getEntityBinProcessedData( 3, processed_data );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 5.0/4 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 24, 5.0/4 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 24, 0.0 ) );

  entity_estimator->getEntityBinProcessedData( 4, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );
  entity_estimator->getEntityBinProcessedData( 4, processed_data );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 1.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 24, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 24, 0.0 ) );

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin
FRENSIE_UNIT_TEST( EntityEstimator,
                   commitHistoryContributionToBinOfEntity_with_histogram )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  entity_estimator->enableSampleMomentHistogramsOnEntityBins();

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

  Utility::ArrayView<const double> entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, 0.125 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, 0.0625 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 1 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 1 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 1 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, 0.125 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, 0.0625 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 2 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 2 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 2 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, 0.125 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, 0.0625 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 3 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 3 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 3 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, 0.125 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, 0.0625 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 4 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 4 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 4 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, 0.125 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, 0.0625 ) );

  // Check the entity bin data mean, re, and fom
  std::vector<double> entity_mean, entity_relative_error,
    entity_variance_of_variance, entity_figure_of_merit;
  std::map<std::string,std::vector<double> > processed_data;

  entity_estimator->getEntityBinProcessedData( 0, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );
  entity_estimator->getEntityBinProcessedData( 0, processed_data );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 5.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 24, 5.0 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 24, 0.0 ) );

  entity_estimator->getEntityBinProcessedData( 1, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );
  entity_estimator->getEntityBinProcessedData( 1, processed_data );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 2.5 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 24, 2.5 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 24, 0.0 ) );

  entity_estimator->getEntityBinProcessedData( 2, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );
  entity_estimator->getEntityBinProcessedData( 2, processed_data );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 5.0/3 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 24, 5.0/3 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 24, 0.0 ) );

  entity_estimator->getEntityBinProcessedData( 3, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );
  entity_estimator->getEntityBinProcessedData( 3, processed_data );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 5.0/4 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 24, 5.0/4 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 24, 0.0 ) );

  entity_estimator->getEntityBinProcessedData( 4, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );
  entity_estimator->getEntityBinProcessedData( 4, processed_data );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, 1.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 24, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 24, 0.0 ) );

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
  std::vector<double> expected_bin_histogram_values =
    Utility::fromString<std::vector<double> >( "{0.0r298, 1.0, 0.0r304}" );
  
  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
      FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                           expected_histogram_bins );
      FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                           expected_bin_histogram_values );
    }
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin
FRENSIE_UNIT_TEST( EntityEstimator,
                   commitHistoryContributionToBinOfEntity_thread_safe_no_histogram )
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
  double moment_3 = (histories+1)*(histories+1)*histories*histories/4.0;
  double moment_4 = (histories+1)*histories/2.0 +
    7.0*(histories+1)*histories*(histories-1)/3.0 +
    3.0*(histories+1)*histories*(histories-1)*(histories-2)/2.0 +
    (histories+1)*histories*(histories-1)*(histories-2)*(histories-3)/5.0;

  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 0 );

  Utility::ArrayView<const double> entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, moment_3 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, moment_4 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 1 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 1 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 1 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, moment_3 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, moment_4 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 2 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 2 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 2 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, moment_3 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, moment_4 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 3 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 3 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 3 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, moment_3 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, moment_4 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 4 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 4 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 4 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, moment_3 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, moment_4 ) );

  double unnorm_mean = moment_1*10.0/histories;
  
  double rel_err = moment_2/(moment_1*moment_1) - 1.0/histories;
  
  if( histories > 1 )
    rel_err *= histories/(histories-1.0);

  rel_err = std::sqrt( rel_err );

  double vov = 0.0;

  {
    const double moment_1_sqr = moment_1*moment_1;
    const double histories_sqr = histories*histories;
    const double denom_arg = moment_2 - moment_1_sqr/histories;

    if( denom_arg != 0.0 )
    {
      vov = (moment_4 -
             4.0*moment_1*moment_3/histories +
             8.0*moment_2*moment_1_sqr/histories_sqr - 
             4.0*moment_1_sqr*moment_1_sqr/(histories_sqr*histories) -
             moment_2*moment_2/histories)/
        (denom_arg*denom_arg);
    }
    else
      vov = 0.0;
  }
  
  double fom = 0.0;

  if( rel_err > 0.0 )
    fom = 1.0/(rel_err*rel_err);

  // Check the entity bin data mean, re, and fom
  std::vector<double> entity_mean, entity_relative_error,
    entity_variance_of_variance, entity_figure_of_merit;

  double mean = unnorm_mean;
  entity_estimator->getEntityBinProcessedData( 0, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, vov ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  mean = unnorm_mean/2.0;
  entity_estimator->getEntityBinProcessedData( 1, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, vov ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  mean = unnorm_mean/3.0;
  entity_estimator->getEntityBinProcessedData( 2, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_mean, std::vector<double>( 24, mean ), 1e-15 );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, vov ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  mean = unnorm_mean/4.0;
  entity_estimator->getEntityBinProcessedData( 3, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, vov ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  mean = unnorm_mean/5.0;
  entity_estimator->getEntityBinProcessedData( 4, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, vov ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin
FRENSIE_UNIT_TEST( EntityEstimator,
                   commitHistoryContributionToBinOfEntity_thread_safe_with_histogram )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  entity_estimator->enableSampleMomentHistogramsOnEntityBins();

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
  double moment_3 = (histories+1)*(histories+1)*histories*histories/4.0;
  double moment_4 = (histories+1)*histories/2.0 +
    7.0*(histories+1)*histories*(histories-1)/3.0 +
    3.0*(histories+1)*histories*(histories-1)*(histories-2)/2.0 +
    (histories+1)*histories*(histories-1)*(histories-2)*(histories-3)/5.0;

  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 0 );

  Utility::ArrayView<const double> entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, moment_3 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, moment_4 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 1 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 1 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 1 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, moment_3 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, moment_4 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 2 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 2 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 2 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, moment_3 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, moment_4 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 3 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 3 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 3 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, moment_3 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, moment_4 ) );

  entity_bin_first_moments =
    entity_estimator->getEntityBinDataFirstMoments( 4 );
  
  entity_bin_second_moments =
    entity_estimator->getEntityBinDataSecondMoments( 4 );

  entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 4 );

  entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, moment_3 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, moment_4 ) );

  double unnorm_mean = moment_1*10.0/histories;
  
  double rel_err = moment_2/(moment_1*moment_1) - 1.0/histories;
  
  if( histories > 1 )
    rel_err *= histories/(histories-1.0);

  rel_err = std::sqrt( rel_err );

  double vov = 0.0;

  {
    const double moment_1_sqr = moment_1*moment_1;
    const double histories_sqr = histories*histories;
    const double denom_arg = moment_2 - moment_1_sqr/histories;

    if( denom_arg != 0.0 )
    {
      vov = (moment_4 -
             4.0*moment_1*moment_3/histories +
             8.0*moment_2*moment_1_sqr/histories_sqr - 
             4.0*moment_1_sqr*moment_1_sqr/(histories_sqr*histories) -
             moment_2*moment_2/histories)/
        (denom_arg*denom_arg);
    }
    else
      vov = 0.0;
  }
  
  double fom = 0.0;

  if( rel_err > 0.0 )
    fom = 1.0/(rel_err*rel_err);

  // Check the entity bin data mean, re, and fom
  std::vector<double> entity_mean, entity_relative_error,
    entity_variance_of_variance, entity_figure_of_merit;

  double mean = unnorm_mean;
  entity_estimator->getEntityBinProcessedData( 0, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, vov ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  mean = unnorm_mean/2.0;
  entity_estimator->getEntityBinProcessedData( 1, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, vov ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  mean = unnorm_mean/3.0;
  entity_estimator->getEntityBinProcessedData( 2, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_mean, std::vector<double>( 24, mean ), 1e-15 );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, vov ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  mean = unnorm_mean/4.0;
  entity_estimator->getEntityBinProcessedData( 3, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, vov ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  mean = unnorm_mean/5.0;
  entity_estimator->getEntityBinProcessedData( 4, entity_mean, entity_relative_error, entity_variance_of_variance, entity_figure_of_merit );

  FRENSIE_CHECK_EQUAL( entity_mean, std::vector<double>( 24, mean ) );
  FRENSIE_CHECK_EQUAL( entity_relative_error, std::vector<double>( 24, rel_err ) );
  FRENSIE_CHECK_EQUAL( entity_variance_of_variance, std::vector<double>( 24, vov ) );
  FRENSIE_CHECK_EQUAL( entity_figure_of_merit, std::vector<double>( 24, fom ) );

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );

  std::vector<double> expected_bin_histogram_values;

  if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 1 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0r300}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 2 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 0.0r297}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 3 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0r296}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 4 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0r294}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 5 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 2.0, 0.0r294}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 6 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 2.0, 1.0, 0.0r293}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 7 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 0.0r292}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 8 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 0.0r291}" );
  }
  
  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(),
                           Utility::OpenMPProperties::getRequestedNumberOfThreads() );
      FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                           expected_histogram_bins );
      FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                           expected_bin_histogram_values );
    }
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin of the total
FRENSIE_UNIT_TEST( EntityEstimator,
                   commitHistoryContributionToBinOfTotal_no_histogram )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  std::set<uint64_t> entity_ids;

  entity_estimator->getEntityIds( entity_ids );

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

  Utility::ArrayView<const double> total_bin_third_moments =
    entity_estimator->getTotalBinDataThirdMoments();

  Utility::ArrayView<const double> total_bin_fourth_moments =
    entity_estimator->getTotalBinDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );
  FRENSIE_CHECK_EQUAL( total_bin_third_moments,
                       std::vector<double>( 24, 0.125 ) );
  FRENSIE_CHECK_EQUAL( total_bin_fourth_moments,
                       std::vector<double>( 24, 0.0625 ) );

  // Check the total mean, relative error, and fom
  std::vector<double> mean, relative_error, vov, fom;

  entity_estimator->getTotalBinProcessedData( mean, relative_error, vov, fom );

  FRENSIE_CHECK_EQUAL( mean, std::vector<double>( 24, 5.0/30.0 ) );
  FRENSIE_CHECK_EQUAL( relative_error, std::vector<double>( 24, 1.0 ) );
  FRENSIE_CHECK_EQUAL( vov, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( fom, std::vector<double>( 24, 1.0/1.5 ) );

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin of the total
FRENSIE_UNIT_TEST( EntityEstimator,
                   commitHistoryContributionToBinOfTotal_with_histogram )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  entity_estimator->enableSampleMomentHistogramsOnEntityBins();

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  std::set<uint64_t> entity_ids;

  entity_estimator->getEntityIds( entity_ids );

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

  Utility::ArrayView<const double> total_bin_third_moments =
    entity_estimator->getTotalBinDataThirdMoments();

  Utility::ArrayView<const double> total_bin_fourth_moments =
    entity_estimator->getTotalBinDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 24, 0.5 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 24, 0.25 ) );
  FRENSIE_CHECK_EQUAL( total_bin_third_moments,
                       std::vector<double>( 24, 0.125 ) );
  FRENSIE_CHECK_EQUAL( total_bin_fourth_moments,
                       std::vector<double>( 24, 0.0625 ) );

  // Check the total mean, relative error, and fom
  std::vector<double> mean, relative_error, vov, fom;

  entity_estimator->getTotalBinProcessedData( mean, relative_error, vov, fom );

  FRENSIE_CHECK_EQUAL( mean, std::vector<double>( 24, 5.0/30.0 ) );
  FRENSIE_CHECK_EQUAL( relative_error, std::vector<double>( 24, 1.0 ) );
  FRENSIE_CHECK_EQUAL( vov, std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( fom, std::vector<double>( 24, 1.0/1.5 ) );

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
  }

  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
  std::vector<double> expected_bin_histogram_values =
    Utility::fromString<std::vector<double> >( "{0.0r298, 1.0, 0.0r304}" );
  
  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_bin_histogram_values );
  }
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin of the total
FRENSIE_UNIT_TEST( EntityEstimator,
                   commitHistoryContributionToBinOfTotal_thread_safe_no_histogram )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  std::set<uint64_t> entity_ids;

  entity_estimator->getEntityIds( entity_ids );

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
  double moment_3 = (histories+1)*(histories+1)*histories*histories/4.0;
  double moment_4 = (histories+1)*histories/2.0 +
    7.0*(histories+1)*histories*(histories-1)/3.0 +
    3.0*(histories+1)*histories*(histories-1)*(histories-2)/2.0 +
    (histories+1)*histories*(histories-1)*(histories-2)*(histories-3)/5.0;

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    entity_estimator->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    entity_estimator->getTotalBinDataSecondMoments();

  Utility::ArrayView<const double> total_bin_third_moments =
    entity_estimator->getTotalBinDataThirdMoments();

  Utility::ArrayView<const double> total_bin_fourth_moments =
    entity_estimator->getTotalBinDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );
  FRENSIE_CHECK_EQUAL( total_bin_third_moments,
                       std::vector<double>( 24, moment_3 ) );
  FRENSIE_CHECK_EQUAL( total_bin_fourth_moments,
                       std::vector<double>( 24, moment_4 ) );

  // Check the total mean, relative error, and fom
  std::vector<double> mean, relative_error, vov, fom;
  std::map<std::string,std::vector<double> > processed_data;

  entity_estimator->getTotalBinProcessedData( mean, relative_error, vov, fom );
  entity_estimator->getTotalBinProcessedData( processed_data );

  double expected_mean = moment_1*10.0/(histories*15.0);
  double expected_rel_err = moment_2/(moment_1*moment_1) - 1.0/histories;

  if( histories > 1 )
    expected_rel_err *= histories/(histories-1.0);

  expected_rel_err = std::sqrt( expected_rel_err );

  double expected_vov = 0.0;

  {
    const double moment_1_sqr = moment_1*moment_1;
    const double histories_sqr = histories*histories;
    const double denom_arg = moment_2 - moment_1_sqr/histories;

    if( denom_arg != 0.0 )
    {
      expected_vov = (moment_4 -
                      4.0*moment_1*moment_3/histories +
                      8.0*moment_2*moment_1_sqr/histories_sqr - 
                      4.0*moment_1_sqr*moment_1_sqr/(histories_sqr*histories) -
                      moment_2*moment_2/histories)/
        (denom_arg*denom_arg);
    }
    else
      expected_vov = 0.0;
  }
  
  double expected_fom = 0.0;

  if( expected_rel_err > 0.0 )
    expected_fom = 1.0/(expected_rel_err*expected_rel_err*1.5);

  FRENSIE_CHECK_FLOATING_EQUALITY( mean, std::vector<double>( 24, expected_mean ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_data["mean"], std::vector<double>( 24, expected_mean ), 1e-15 );
  FRENSIE_CHECK_EQUAL( relative_error, std::vector<double>( 24, expected_rel_err ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 24, expected_rel_err ) );
  FRENSIE_CHECK_EQUAL( vov, std::vector<double>( 24, expected_vov ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 24, expected_vov ) );
  FRENSIE_CHECK_EQUAL( fom, std::vector<double>( 24, expected_fom ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 24, expected_fom ) );

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a history contribution can be committed to a bin of the total
FRENSIE_UNIT_TEST( EntityEstimator,
                   commitHistoryContributionToBinOfTotal_thread_safe_with_histogram )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  entity_estimator->enableSampleMomentHistogramsOnEntityBins();

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  std::set<uint64_t> entity_ids;

  entity_estimator->getEntityIds( entity_ids );

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
  double moment_3 = (histories+1)*(histories+1)*histories*histories/4.0;
  double moment_4 = (histories+1)*histories/2.0 +
    7.0*(histories+1)*histories*(histories-1)/3.0 +
    3.0*(histories+1)*histories*(histories-1)*(histories-2)/2.0 +
    (histories+1)*histories*(histories-1)*(histories-2)*(histories-3)/5.0;

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    entity_estimator->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    entity_estimator->getTotalBinDataSecondMoments();

  Utility::ArrayView<const double> total_bin_third_moments =
    entity_estimator->getTotalBinDataThirdMoments();

  Utility::ArrayView<const double> total_bin_fourth_moments =
    entity_estimator->getTotalBinDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 24, moment_1 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 24, moment_2 ) );
  FRENSIE_CHECK_EQUAL( total_bin_third_moments,
                       std::vector<double>( 24, moment_3 ) );
  FRENSIE_CHECK_EQUAL( total_bin_fourth_moments,
                       std::vector<double>( 24, moment_4 ) );

  // Check the total mean, relative error, and fom
  std::vector<double> mean, relative_error, vov, fom;
  std::map<std::string,std::vector<double> > processed_data;

  entity_estimator->getTotalBinProcessedData( mean, relative_error, vov, fom );
  entity_estimator->getTotalBinProcessedData( processed_data );

  double expected_mean = moment_1*10.0/(histories*15.0);
  double expected_rel_err = moment_2/(moment_1*moment_1) - 1.0/histories;

  if( histories > 1 )
    expected_rel_err *= histories/(histories-1.0);

  expected_rel_err = std::sqrt( expected_rel_err );

  double expected_vov = 0.0;

  {
    const double moment_1_sqr = moment_1*moment_1;
    const double histories_sqr = histories*histories;
    const double denom_arg = moment_2 - moment_1_sqr/histories;

    if( denom_arg != 0.0 )
    {
      expected_vov = (moment_4 -
                      4.0*moment_1*moment_3/histories +
                      8.0*moment_2*moment_1_sqr/histories_sqr - 
                      4.0*moment_1_sqr*moment_1_sqr/(histories_sqr*histories) -
                      moment_2*moment_2/histories)/
        (denom_arg*denom_arg);
    }
    else
      expected_vov = 0.0;
  }
  
  double expected_fom = 0.0;

  if( expected_rel_err > 0.0 )
    expected_fom = 1.0/(expected_rel_err*expected_rel_err*1.5);

  FRENSIE_CHECK_FLOATING_EQUALITY( mean, std::vector<double>( 24, expected_mean ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_data["mean"], std::vector<double>( 24, expected_mean ), 1e-15 );
  FRENSIE_CHECK_EQUAL( relative_error, std::vector<double>( 24, expected_rel_err ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 24, expected_rel_err ) );
  FRENSIE_CHECK_EQUAL( vov, std::vector<double>( 24, expected_vov ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 24, expected_vov ) );
  FRENSIE_CHECK_EQUAL( fom, std::vector<double>( 24, expected_fom ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 24, expected_fom ) );

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;
  
  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
  }

  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );

  std::vector<double> expected_bin_histogram_values;

  if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 1 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0r300}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 2 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 0.0r297}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 3 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0r296}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 4 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0r294}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 5 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 2.0, 0.0r294}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 6 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 2.0, 1.0, 0.0r293}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 7 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 0.0r292}" );
  }
  else if( Utility::OpenMPProperties::getRequestedNumberOfThreads() == 8 )
  {
    expected_bin_histogram_values =
      Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 0.0r291}" );
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(),
                         Utility::OpenMPProperties::getRequestedNumberOfThreads() );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_bin_histogram_values );
  }
}

//---------------------------------------------------------------------------//
// Check that a snapshot of the estimator state can be made
FRENSIE_UNIT_TEST( EntityEstimator, takeSnapshot_no_bin_snapshots )
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
      entity_estimator->commitHistoryContributionToBinOfTotal( i, 0.5 );
    }
  }

  entity_estimator->takeSnapshot( 5, 1.0 );

  for( auto&& entity_id : entity_ids )
  {
    for( size_t i = 0; i < num_estimator_bins; ++i )
    {
      entity_estimator->commitHistoryContributionToBinOfEntity( entity_id,
								i,
								1.0 );
      entity_estimator->commitHistoryContributionToBinOfTotal( i, 1.0 );
    }
  }

  entity_estimator->takeSnapshot( 5, 4.0 );

  // Check the entity bin moment snapshots
  std::vector<uint64_t> history_values;
  std::vector<double> sampling_times;

  std::vector<double> first_moments, second_moments, third_moments,
    fourth_moments;

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    entity_estimator->getEntityBinMomentSnapshotHistoryValues( i, history_values );

    entity_estimator->getEntityBinMomentSnapshotSamplingTimes( i, sampling_times );

    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinFirstMomentSnapshots( i, j, first_moments );
      entity_estimator->getEntityBinSecondMomentSnapshots( i, j, second_moments );
      entity_estimator->getEntityBinThirdMomentSnapshots( i, j, third_moments );
      entity_estimator->getEntityBinFourthMomentSnapshots( i, j, fourth_moments );

      FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    }
  }

  // Check the total bin moment snapshots
  entity_estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
  entity_estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {  
    entity_estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
    entity_estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
    entity_estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
    entity_estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }

  // Check the entity total moment snapshots
  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    entity_estimator->getEntityTotalMomentSnapshotHistoryValues( i, history_values );

    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );

    entity_estimator->getEntityTotalMomentSnapshotSamplingTimes( i, sampling_times );

    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

    entity_estimator->getEntityTotalFirstMomentSnapshots( i, 0, first_moments );
    entity_estimator->getEntityTotalSecondMomentSnapshots( i, 0, second_moments );
    entity_estimator->getEntityTotalThirdMomentSnapshots( i, 0, third_moments );
    entity_estimator->getEntityTotalFourthMomentSnapshots( i, 0, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }

  // Check the total moment snapshots
  entity_estimator->getTotalMomentSnapshotHistoryValues( history_values );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );

  entity_estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  entity_estimator->getTotalFirstMomentSnapshots( 0, first_moments );
  entity_estimator->getTotalSecondMomentSnapshots( 0, second_moments );
  entity_estimator->getTotalThirdMomentSnapshots( 0, third_moments );
  entity_estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a snapshot of the estimator state can be made
FRENSIE_UNIT_TEST( EntityEstimator, takeSnapshot_with_bin_snapshots )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  entity_estimator->enableSnapshotsOnEntityBins();

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
      entity_estimator->commitHistoryContributionToBinOfTotal( i, 0.5 );
    }
  }

  entity_estimator->takeSnapshot( 5, 1.0 );

  for( auto&& entity_id : entity_ids )
  {
    for( size_t i = 0; i < num_estimator_bins; ++i )
    {
      entity_estimator->commitHistoryContributionToBinOfEntity( entity_id,
								i,
								1.0 );
      entity_estimator->commitHistoryContributionToBinOfTotal( i, 1.0 );
    }
  }

  entity_estimator->takeSnapshot( 5, 4.0 );

  // Check the entity bin moment snapshots
  std::vector<uint64_t> history_values;
  std::vector<double> sampling_times;

  std::vector<double> first_moments, second_moments, third_moments,
    fourth_moments;

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    entity_estimator->getEntityBinMomentSnapshotHistoryValues( i, history_values );

    entity_estimator->getEntityBinMomentSnapshotSamplingTimes( i, sampling_times );

    FRENSIE_CHECK_EQUAL( history_values, std::vector<uint64_t>( {5, 10} ) );
    FRENSIE_CHECK_EQUAL( sampling_times, std::vector<double>( {1.0, 5.0} ) );
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinFirstMomentSnapshots( i, j, first_moments );
      entity_estimator->getEntityBinSecondMomentSnapshots( i, j, second_moments );
      entity_estimator->getEntityBinThirdMomentSnapshots( i, j, third_moments );
      entity_estimator->getEntityBinFourthMomentSnapshots( i, j, fourth_moments );

      FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.5, 1.5} ) );
      FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.25, 1.25} ) );
      FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {0.125, 1.125} ) );
      FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {0.0625, 1.0625} ) );
    }
  }

  // Check the entity bin processed snapshots
  std::vector<double> mean_snapshots, re_snapshots,
    vov_snapshots, fom_snapshots;

  std::map<std::string,std::vector<double> > processed_snapshots;

  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getEntityBinProcessedSnapshots( 0, j, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
    entity_estimator->getEntityBinProcessedSnapshots( 0, j, processed_snapshots );

    FRENSIE_CHECK_EQUAL( mean_snapshots, std::vector<double>( {1.0, 1.5} ) );
    FRENSIE_CHECK_EQUAL( processed_snapshots["mean"], std::vector<double>( {1.0, 1.5} ) );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 0.7114582486036499} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 0.7114582486036499} ), 1e-15 );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.41499107674003566} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.41499107674003566} ), 1e-15 );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {1.0, 0.3951219512195121} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {1.0, 0.3951219512195121} ), 1e-15 );
  }

  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getEntityBinProcessedSnapshots( 1, j, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
    entity_estimator->getEntityBinProcessedSnapshots( 1, j, processed_snapshots );

    FRENSIE_CHECK_EQUAL( mean_snapshots, std::vector<double>( {0.5, 0.75} ) );
    FRENSIE_CHECK_EQUAL( processed_snapshots["mean"], std::vector<double>( {0.5, 0.75} ) );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 0.7114582486036499} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 0.7114582486036499} ), 1e-15 );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.41499107674003566} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.41499107674003566} ), 1e-15 );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {1.0, 0.3951219512195121} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {1.0, 0.3951219512195121} ), 1e-15 );
  }

  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getEntityBinProcessedSnapshots( 2, j, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
    entity_estimator->getEntityBinProcessedSnapshots( 2, j, processed_snapshots );

    FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {1.0/3, 1.5/3} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {1.0/3, 1.5/3} ), 1e-15 );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 0.7114582486036499} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 0.7114582486036499} ), 1e-15 );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.41499107674003566} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.41499107674003566} ), 1e-15 );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {1.0, 0.3951219512195121} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {1.0, 0.3951219512195121} ), 1e-15 );
  }

  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getEntityBinProcessedSnapshots( 3, j, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
    entity_estimator->getEntityBinProcessedSnapshots( 3, j, processed_snapshots );

    FRENSIE_CHECK_EQUAL( mean_snapshots, std::vector<double>( {0.25, 1.5/4} ) );
    FRENSIE_CHECK_EQUAL( processed_snapshots["mean"], std::vector<double>( {0.25, 1.5/4} ) );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 0.7114582486036499} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 0.7114582486036499} ), 1e-15 );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.41499107674003566} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.41499107674003566} ), 1e-15 );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {1.0, 0.3951219512195121} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {1.0, 0.3951219512195121} ), 1e-15 );
  }

  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getEntityBinProcessedSnapshots( 4, j, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
    entity_estimator->getEntityBinProcessedSnapshots( 4, j, processed_snapshots );

    FRENSIE_CHECK_EQUAL( mean_snapshots, std::vector<double>( {0.2, 0.3} ) );
    FRENSIE_CHECK_EQUAL( processed_snapshots["mean"], std::vector<double>( {0.2, 0.3} ) );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 0.7114582486036499} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 0.7114582486036499} ), 1e-15 );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.41499107674003566} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.41499107674003566} ), 1e-15 );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {1.0, 0.3951219512195121} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {1.0, 0.3951219512195121} ), 1e-15 );
  }

  // Check the total bin moment snapshots
  entity_estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
  entity_estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( history_values, std::vector<uint64_t>( {5, 10} ) );
  FRENSIE_CHECK_EQUAL( sampling_times, std::vector<double>( {1.0, 5.0} ) );
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {  
    entity_estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
    entity_estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
    entity_estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
    entity_estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {2.5, 7.5} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.25, 6.25} ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {0.625, 5.625} ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {0.3125, 5.3125} ) );
  }

  // Check the total bin processed snapshots
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinProcessedSnapshots( j, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
    entity_estimator->getTotalBinProcessedSnapshots( j, processed_snapshots );

    FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {1.0/3, 0.5} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {1.0/3, 0.5} ), 1e-15 );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {0.0, 0.11111111111111105} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {0.0, 0.11111111111111105} ), 1e-15 );
    
    FRENSIE_CHECK_EQUAL( vov_snapshots, std::vector<double>( {0.0, 0.0} ) );
    FRENSIE_CHECK_EQUAL( processed_snapshots["vov"], std::vector<double>( {0.0, 0.0} ) );
    
    FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.0, 16.20000000000002} ), 1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.0, 16.20000000000002} ), 1e-15 );
  }

  history_values.clear();
  sampling_times.clear();
  first_moments.clear();
  second_moments.clear();
  third_moments.clear();
  fourth_moments.clear();

  // Check the entity total moment snapshots
  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    entity_estimator->getEntityTotalMomentSnapshotHistoryValues( i, history_values );

    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );

    entity_estimator->getEntityTotalMomentSnapshotSamplingTimes( i, sampling_times );

    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

    entity_estimator->getEntityTotalFirstMomentSnapshots( i, 0, first_moments );
    entity_estimator->getEntityTotalSecondMomentSnapshots( i, 0, second_moments );
    entity_estimator->getEntityTotalThirdMomentSnapshots( i, 0, third_moments );
    entity_estimator->getEntityTotalFourthMomentSnapshots( i, 0, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }

  // Check the total moment snapshots
  entity_estimator->getTotalMomentSnapshotHistoryValues( history_values );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );

  entity_estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  entity_estimator->getTotalFirstMomentSnapshots( 0, first_moments );
  entity_estimator->getTotalSecondMomentSnapshots( 0, second_moments );
  entity_estimator->getTotalThirdMomentSnapshots( 0, third_moments );
  entity_estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );
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

  entity_estimator->enableSnapshotsOnEntityBins();
  entity_estimator->enableSampleMomentHistogramsOnEntityBins();

  std::set<uint64_t> entity_ids;

  entity_estimator->getEntityIds( entity_ids );

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  // Commit one contribution to every bin of the estimator
  for( auto&& entity_id : entity_ids )
  {
    for( size_t i = 0; i < num_estimator_bins; ++i )
    {
      entity_estimator->commitHistoryContributionToBinOfEntity( entity_id,
								i,
								0.5 );
      entity_estimator->commitHistoryContributionToBinOfTotal( i, 0.5 );
    }
  }

  entity_estimator->takeSnapshot( 5, 1.0 );

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

  Utility::ArrayView<const double> entity_bin_third_moments =
    entity_estimator->getEntityBinDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_bin_fourth_moments =
    entity_estimator->getEntityBinDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                       std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                       std::vector<double>( 24, 0.0 ) );

  Utility::ArrayView<const double> total_bin_first_moments =
    entity_estimator->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    entity_estimator->getTotalBinDataSecondMoments();

  Utility::ArrayView<const double> total_bin_third_moments =
    entity_estimator->getTotalBinDataThirdMoments();

  Utility::ArrayView<const double> total_bin_fourth_moments =
    entity_estimator->getTotalBinDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_third_moments,
                       std::vector<double>( 24, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_fourth_moments,
                       std::vector<double>( 24, 0.0 ) );

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
  std::vector<double> expected_bin_histogram_values( 603, 0.0 );

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
      FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                           expected_histogram_bins );
      FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                           expected_bin_histogram_values );
    }
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_bin_histogram_values );
  }

  // Check the entity bin moment snapshots
  std::vector<uint64_t> history_values;
  std::vector<double> sampling_times;

  std::vector<double> first_moments, second_moments, third_moments,
    fourth_moments;

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    entity_estimator->getEntityBinMomentSnapshotHistoryValues( i, history_values );

    entity_estimator->getEntityBinMomentSnapshotSamplingTimes( i, sampling_times );

    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getEntityBinFirstMomentSnapshots( i, j, first_moments );
      entity_estimator->getEntityBinSecondMomentSnapshots( i, j, second_moments );
      entity_estimator->getEntityBinThirdMomentSnapshots( i, j, third_moments );
      entity_estimator->getEntityBinFourthMomentSnapshots( i, j, fourth_moments );

      FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    }
  }

  // Check the total bin moment snapshots
  entity_estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
  entity_estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {  
    entity_estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
    entity_estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
    entity_estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
    entity_estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }

  // Check the entity total moment snapshots
  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    entity_estimator->getEntityTotalMomentSnapshotHistoryValues( i, history_values );

    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );

    entity_estimator->getEntityTotalMomentSnapshotSamplingTimes( i, sampling_times );

    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

    entity_estimator->getEntityTotalFirstMomentSnapshots( i, 0, first_moments );
    entity_estimator->getEntityTotalSecondMomentSnapshots( i, 0, second_moments );
    entity_estimator->getEntityTotalThirdMomentSnapshots( i, 0, third_moments );
    entity_estimator->getEntityTotalFourthMomentSnapshots( i, 0, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }

  // Check the total moment snapshots
  entity_estimator->getTotalMomentSnapshotHistoryValues( history_values );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );

  entity_estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  entity_estimator->getTotalFirstMomentSnapshots( 0, first_moments );
  entity_estimator->getTotalSecondMomentSnapshots( 0, second_moments );
  entity_estimator->getTotalThirdMomentSnapshots( 0, third_moments );
  entity_estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );
}

//---------------------------------------------------------------------------//
// Check that the estimator data can be reduced
FRENSIE_UNIT_TEST( EntityEstimator, reduceData )
{
  std::shared_ptr<TestEntityEstimator> entity_estimator;
  initializeEntityEstimator( entity_estimator, true );

  entity_estimator->enableSampleMomentHistogramsOnEntityBins();
  entity_estimator->enableSnapshotsOnEntityBins();

  std::set<uint64_t> entity_ids;

  entity_estimator->getEntityIds( entity_ids );

  size_t num_estimator_bins = entity_estimator->getNumberOfBins()*
    entity_estimator->getNumberOfResponseFunctions();

  for( size_t i = 0; i < num_estimator_bins; ++i )
  {
    entity_estimator->commitHistoryContributionToBinOfEntity( 0, i, 1.0 );
    entity_estimator->commitHistoryContributionToBinOfEntity( 2, i, 1.0 );
    entity_estimator->commitHistoryContributionToBinOfEntity( 4, i, 1.0 );

    entity_estimator->commitHistoryContributionToBinOfTotal( i, 2.0 );
  }

  entity_estimator->takeSnapshot( 1, 1.0 );

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

    Utility::ArrayView<const double> third_moments =
      entity_estimator->getTotalBinDataThirdMoments();

    Utility::ArrayView<const double> fourth_moments =
      entity_estimator->getTotalBinDataFourthMoments();

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 2*procs ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 4*procs ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( 24, 8*procs ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( 24, 16*procs ) );

    // Check the entity bin data moments
    first_moments = entity_estimator->getEntityBinDataFirstMoments( 0 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 0 );
    third_moments = entity_estimator->getEntityBinDataThirdMoments( 0 );
    fourth_moments = entity_estimator->getEntityBinDataFourthMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, procs ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, procs ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( 24, procs ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( 24, procs ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 1 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 1 );
    third_moments = entity_estimator->getEntityBinDataThirdMoments( 1 );
    fourth_moments = entity_estimator->getEntityBinDataFourthMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( 24, 0.0 ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 2 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 2 );
    third_moments = entity_estimator->getEntityBinDataThirdMoments( 2 );
    fourth_moments = entity_estimator->getEntityBinDataFourthMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, procs ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, procs ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( 24, procs ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( 24, procs ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 3 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 3 );
    third_moments = entity_estimator->getEntityBinDataThirdMoments( 3 );
    fourth_moments = entity_estimator->getEntityBinDataFourthMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( 24, 0.0 ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 4 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 4 );
    third_moments = entity_estimator->getEntityBinDataThirdMoments( 4 );
    fourth_moments = entity_estimator->getEntityBinDataFourthMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, procs ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, procs ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( 24, procs ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( 24, procs ) );

    // Check the entity bin histograms
    Utility::SampleMomentHistogram<double> histogram;

    std::vector<double> expected_histogram_bins =
      Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
    std::vector<double> expected_bin_histogram_values;

    {
      std::string histogram_value_string = "{0.0r302, ";
      histogram_value_string += Utility::toString( procs );
      histogram_value_string += ", 0.0r300}";

      expected_bin_histogram_values =
        Utility::fromString<std::vector<double> >( histogram_value_string );
    }
    
    for( size_t i = 0; i < entity_ids.size(); ++i )
    {
      for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );
        
        FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                             expected_histogram_bins );

        if( i == 0 || i == 2 || i == 4 )
        {
          FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), procs );
          FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                               expected_bin_histogram_values );
        }
        else
        {
          FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
          FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                               std::vector<double>( 603, 0.0 ) );
        }
      }
    }

    // Check the total bin histograms
    {
      std::string histogram_value_string = "{0.0r305, ";
      histogram_value_string += Utility::toString( procs );
      histogram_value_string += ", 0.0r297}";

      expected_bin_histogram_values =
        Utility::fromString<std::vector<double> >( histogram_value_string );
    }

    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );
      
      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), procs );
      FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                           expected_histogram_bins );
      FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                           expected_bin_histogram_values );
    }

    // Check the entity bin moment snapshots
    std::vector<uint64_t> history_values;
    std::vector<double> sampling_times;

    std::vector<double> first_moment_snapshots, second_moment_snapshots, third_moment_snapshots, fourth_moment_snapshots;

    for( size_t i = 0; i < entity_ids.size(); ++i )
    {
      entity_estimator->getEntityBinMomentSnapshotHistoryValues( i, history_values );

      entity_estimator->getEntityBinMomentSnapshotSamplingTimes( i, sampling_times );
      std::vector<uint64_t> expected_history_values( procs );
      std::vector<double> expected_sampling_times( procs );
      std::vector<double> expected_moments( procs );
      
      for( size_t i = 0; i < procs; ++i )
      {
        expected_history_values[i] = i+1;
        expected_sampling_times[i] = i+1;
        expected_moments[i] = i+1;
      }
      
      FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
      FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
    
      for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        entity_estimator->getEntityBinFirstMomentSnapshots( i, j, first_moment_snapshots );
        entity_estimator->getEntityBinSecondMomentSnapshots( i, j, second_moment_snapshots );
        entity_estimator->getEntityBinThirdMomentSnapshots( i, j, third_moment_snapshots );
        entity_estimator->getEntityBinFourthMomentSnapshots( i, j, fourth_moment_snapshots );

        if( i == 0 || i == 2 || i == 4 )
        {
          FRENSIE_CHECK_EQUAL( first_moment_snapshots, expected_moments );
          FRENSIE_CHECK_EQUAL( second_moment_snapshots, expected_moments );
          FRENSIE_CHECK_EQUAL( third_moment_snapshots, expected_moments );
          FRENSIE_CHECK_EQUAL( fourth_moment_snapshots, expected_moments );
        }
        else
        {
          FRENSIE_CHECK_EQUAL( first_moment_snapshots, std::vector<double>( procs, 0.0 ) );
          FRENSIE_CHECK_EQUAL( second_moment_snapshots, std::vector<double>( procs, 0.0 ) );
          FRENSIE_CHECK_EQUAL( third_moment_snapshots, std::vector<double>( procs, 0.0 ) );
          FRENSIE_CHECK_EQUAL( fourth_moment_snapshots, std::vector<double>( procs, 0.0 ) );
        }
      }
    }

    // Check the total bin moment snapshots
    entity_estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
    entity_estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );

    std::vector<uint64_t> expected_history_values( procs );
    std::vector<double> expected_sampling_times( procs );
    std::vector<double> expected_first_moments( procs );
    std::vector<double> expected_second_moments( procs );
    std::vector<double> expected_third_moments( procs );
    std::vector<double> expected_fourth_moments( procs );
    
    for( size_t i = 0; i < procs; ++i )
    {
      expected_history_values[i] = i+1;
      expected_sampling_times[i] = i+1;
      expected_first_moments[i] = (i+1)*2.0;
      expected_second_moments[i] = (i+1)*4.0;
      expected_third_moments[i] = (i+1)*8.0;
      expected_fourth_moments[i] = (i+1)*16.0;
    }

    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {  
      entity_estimator->getTotalBinFirstMomentSnapshots( j, first_moment_snapshots );
      entity_estimator->getTotalBinSecondMomentSnapshots( j, second_moment_snapshots );
      entity_estimator->getTotalBinThirdMomentSnapshots( j, third_moment_snapshots );
      entity_estimator->getTotalBinFourthMomentSnapshots( j, fourth_moment_snapshots );

      FRENSIE_CHECK_EQUAL( first_moment_snapshots, expected_first_moments );
      FRENSIE_CHECK_EQUAL( second_moment_snapshots, expected_second_moments );
      FRENSIE_CHECK_EQUAL( third_moment_snapshots, expected_third_moments );
      FRENSIE_CHECK_EQUAL( fourth_moment_snapshots, expected_fourth_moments );
    }
  }
  // Make sure that estimators on other processes were reset
  else
  {
    // Check the total bin data moments
    Utility::ArrayView<const double> first_moments =
      entity_estimator->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> second_moments =
      entity_estimator->getTotalBinDataSecondMoments();

    Utility::ArrayView<const double> third_moments =
      entity_estimator->getTotalBinDataThirdMoments();

    Utility::ArrayView<const double> fourth_moments =
      entity_estimator->getTotalBinDataFourthMoments();

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( 24, 0.0 ) );

    // Check the entity bin data moments
    first_moments = entity_estimator->getEntityBinDataFirstMoments( 0 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 0 );
    third_moments = entity_estimator->getEntityBinDataThirdMoments( 0 );
    fourth_moments = entity_estimator->getEntityBinDataFourthMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( 24, 0.0 ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 1 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 1 );
    third_moments = entity_estimator->getEntityBinDataThirdMoments( 1 );
    fourth_moments = entity_estimator->getEntityBinDataFourthMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( 24, 0.0 ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 2 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 2 );
    third_moments = entity_estimator->getEntityBinDataThirdMoments( 2 );
    fourth_moments = entity_estimator->getEntityBinDataFourthMoments( 2 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( 24, 0.0 ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 3 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 3 );
    third_moments = entity_estimator->getEntityBinDataThirdMoments( 3 );
    fourth_moments = entity_estimator->getEntityBinDataFourthMoments( 3 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( 24, 0.0 ) );

    first_moments = entity_estimator->getEntityBinDataFirstMoments( 4 );
    second_moments = entity_estimator->getEntityBinDataSecondMoments( 4 );
    third_moments = entity_estimator->getEntityBinDataThirdMoments( 4 );
    fourth_moments = entity_estimator->getEntityBinDataFourthMoments( 4 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( 24, 0.0 ) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( 24, 0.0 ) );

    // Check the entity bin histograms
    Utility::SampleMomentHistogram<double> histogram;

    std::vector<double> expected_histogram_bins =
      Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
    std::vector<double> expected_bin_histogram_values( 603, 0.0 );

    for( size_t i = 0; i < entity_ids.size(); ++i )
    {
      for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        entity_estimator->getEntityBinSampleMomentHistogram( i, j, histogram );
        
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
        FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                             expected_histogram_bins );
        FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                             expected_bin_histogram_values );
      }
    }

    // Check the total bin histograms
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      entity_estimator->getTotalBinSampleMomentHistogram( j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
      FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                           expected_histogram_bins );
      FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                           expected_bin_histogram_values );
    }

    // Check the entity bin moment snapshots
    std::vector<uint64_t> history_values;
    std::vector<double> sampling_times;

    std::vector<double> first_moment_snapshots, second_moment_snapshots, third_moment_snapshots,
      fourth_moment_snapshots;

    for( size_t i = 0; i < entity_ids.size(); ++i )
    {
      entity_estimator->getEntityBinMomentSnapshotHistoryValues( i, history_values );

      entity_estimator->getEntityBinMomentSnapshotSamplingTimes( i, sampling_times );
      
      FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
      FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

      for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        entity_estimator->getEntityBinFirstMomentSnapshots( i, j, first_moment_snapshots );
        entity_estimator->getEntityBinSecondMomentSnapshots( i, j, second_moment_snapshots );
        entity_estimator->getEntityBinThirdMomentSnapshots( i, j, third_moment_snapshots );
        entity_estimator->getEntityBinFourthMomentSnapshots( i, j, fourth_moment_snapshots );

        FRENSIE_CHECK_EQUAL( first_moment_snapshots.size(), 0 );
        FRENSIE_CHECK_EQUAL( second_moment_snapshots.size(), 0 );
        FRENSIE_CHECK_EQUAL( third_moment_snapshots.size(), 0 );
        FRENSIE_CHECK_EQUAL( fourth_moment_snapshots.size(), 0 );
      }
    }

    // Check the total bin moment snapshots
    entity_estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
    entity_estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );

    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {  
      entity_estimator->getTotalBinFirstMomentSnapshots( j, first_moment_snapshots );
      entity_estimator->getTotalBinSecondMomentSnapshots( j, second_moment_snapshots );
      entity_estimator->getTotalBinThirdMomentSnapshots( j, third_moment_snapshots );
      entity_estimator->getTotalBinFourthMomentSnapshots( j, fourth_moment_snapshots );

      FRENSIE_CHECK_EQUAL( first_moment_snapshots.size(), 0 );
      FRENSIE_CHECK_EQUAL( second_moment_snapshots.size(), 0 );
      FRENSIE_CHECK_EQUAL( third_moment_snapshots.size(), 0 );
      FRENSIE_CHECK_EQUAL( fourth_moment_snapshots.size(), 0 );
    }
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
