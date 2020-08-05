//---------------------------------------------------------------------------//
//!
//! \file   tstStandardCellEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard cell estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_StandardCellEstimator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestStandardCellEstimator : public MonteCarlo::StandardCellEstimator
{
public:
  TestStandardCellEstimator( const unsigned long long id,
                             const double multiplier,
                             const std::vector<uint64_t>& entity_ids,
	                     const std::vector<double>& entity_norm_constants )
    : MonteCarlo::StandardCellEstimator( id,
                                         multiplier,
                                         entity_ids,
                                         entity_norm_constants )
  { /* ... */ }

  ~TestStandardCellEstimator()
  { /* ... */ }

  void printSummary( std::ostream& os ) const final override
  { this->printImplementation( os, "Cell" ); }
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the estimator is a cell type estimator
FRENSIE_UNIT_TEST( StandardCellEstimator, check_type )
{
  std::vector<uint64_t> cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;

  std::vector<double> cell_norm_consts( 2 );
  cell_norm_consts[0] = 1.0;
  cell_norm_consts[1] = 2.0;

  std::shared_ptr<MonteCarlo::Estimator> estimator(
			   new TestStandardCellEstimator( 0ull,
							  2.0,
							  cell_ids,
							  cell_norm_consts ) );

  FRENSIE_CHECK( estimator->isCellEstimator() );
  FRENSIE_CHECK( !estimator->isSurfaceEstimator() );
  FRENSIE_CHECK( !estimator->isMeshEstimator() );
}

//---------------------------------------------------------------------------//
// Check that estimator bins can be set
FRENSIE_UNIT_TEST( StandardCellEstimator, setDiscretization )
{
  std::vector<uint64_t> cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;

  std::vector<double> cell_norm_consts( 2 );
  cell_norm_consts[0] = 1.0;
  cell_norm_consts[1] = 2.0;

  std::shared_ptr<MonteCarlo::Estimator> estimator(
			   new TestStandardCellEstimator( 0ull,
							  2.0,
							  cell_ids,
							  cell_norm_consts ) );

  std::vector<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 0.1;
  energy_bin_boundaries[2] = 1.0;

  estimator->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
						       energy_bin_boundaries );

  FRENSIE_CHECK_EQUAL(estimator->getNumberOfBins(MonteCarlo::OBSERVER_ENERGY_DIMENSION),
		      2 );
  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 2 );

  std::vector<double> time_bin_boundaries( 3 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1.0;
  time_bin_boundaries[2] = 2.0;

  estimator->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(
							 time_bin_boundaries );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(MonteCarlo::OBSERVER_TIME_DIMENSION),
		       2 );
  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 4 );

  std::vector<unsigned> collision_number_bins( 2 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 10u;

  estimator->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

  FRENSIE_CHECK_EQUAL(
     estimator->getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 2 );
  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 8 );

  // Make sure cosine bins cannot be set
  std::vector<double> cosine_bin_boundaries( 3 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = 0.0;
  cosine_bin_boundaries[2] = 1.0;

  estimator->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(
						       cosine_bin_boundaries );

  FRENSIE_CHECK_EQUAL(estimator->getNumberOfBins(MonteCarlo::OBSERVER_COSINE_DIMENSION),
		      1 );
  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 8 );


  estimator->setDirectionDiscretization( MonteCarlo::ObserverDirectionDimensionDiscretization::ObserverDirectionDiscretizationType::PQLA,
                                        2,
                                        true );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_DIRECTION_DIMENSION ),
                       8*4 );
  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 8*8*4 );
}

//---------------------------------------------------------------------------//
// Check that particle types can be assigned
FRENSIE_UNIT_TEST( StandardCellEstimator, setParticleType )
{
  std::vector<uint64_t> cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;

  std::vector<double> cell_norm_consts( 2 );
  cell_norm_consts[0] = 1.0;
  cell_norm_consts[1] = 2.0;

  std::shared_ptr<MonteCarlo::Estimator> estimator(
                           new TestStandardCellEstimator( 0ull,
                                                          2.0,
                                                          cell_ids,
					                  cell_norm_consts ) );

  std::vector<MonteCarlo::ParticleType> particle_types( 4 );
  particle_types[0] = MonteCarlo::PHOTON;
  particle_types[1] = MonteCarlo::NEUTRON;
  particle_types[2] = MonteCarlo::ADJOINT_PHOTON;
  particle_types[3] = MonteCarlo::ADJOINT_NEUTRON;

  // All but the first particle type should be ignored
  estimator->setParticleTypes( particle_types );

  FRENSIE_CHECK( estimator->isParticleTypeAssigned( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_NEUTRON ) );

  particle_types[0] = MonteCarlo::NEUTRON;
  particle_types[1] = MonteCarlo::PHOTON;

  // All particle types should be ignored
  estimator->setParticleTypes( particle_types );

  FRENSIE_CHECK( estimator->isParticleTypeAssigned( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_NEUTRON ) );
}

//---------------------------------------------------------------------------//
// end tstStandardCellEstimator.cpp
//---------------------------------------------------------------------------//

