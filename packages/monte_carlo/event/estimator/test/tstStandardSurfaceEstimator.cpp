//---------------------------------------------------------------------------//
//!
//! \file   tstStandardSurfaceEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard surface estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_StandardSurfaceEstimator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestStandardSurfaceEstimator : public MonteCarlo::StandardSurfaceEstimator
{
public:
  TestStandardSurfaceEstimator(
                             const uint32_t id,
                             const double multiplier,
                             const std::vector<uint64_t>& entity_ids,
	                     const std::vector<double>& entity_norm_constants )
    : MonteCarlo::StandardSurfaceEstimator( id,
                                            multiplier,
                                            entity_ids,
                                            entity_norm_constants )
  { /* ... */ }

  ~TestStandardSurfaceEstimator()
  { /* ... */ }

  void updateFromParticleCrossingSurfaceEvent(
  	                      const MonteCarlo::ParticleState& particle,
                              const Geometry::Model::EntityId surface_crossing,
                              const double angle_cosine ) final override
  { /* ... */ }

  void printSummary( std::ostream& os ) const final override
  { this->printImplementation( os, "Surface" ); }
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the estimator is a surface type estimator
FRENSIE_UNIT_TEST( StandardSurfaceEstimator, check_type )
{
  std::vector<Geometry::Model::EntityId> surface_ids( 2 );
  surface_ids[0] = 0;
  surface_ids[1] = 1;

  std::vector<double> surface_norm_consts( 2 );
  surface_norm_consts[0] = 1.0;
  surface_norm_consts[1] = 2.0;

  std::shared_ptr<TestStandardSurfaceEstimator> estimator(
                     new TestStandardSurfaceEstimator( 0ull,
                                                       2.0,
                                                       surface_ids,
					               surface_norm_consts ) );

  FRENSIE_CHECK( !estimator->isCellEstimator() );
  FRENSIE_CHECK( estimator->isSurfaceEstimator() );
  FRENSIE_CHECK( !estimator->isMeshEstimator() );
}

//---------------------------------------------------------------------------//
// Check that particle types can be assigned
FRENSIE_UNIT_TEST( StandardSurfaceEstimator, setParticleType )
{
  std::vector<Geometry::Model::EntityId> surface_ids( 2 );
  surface_ids[0] = 0;
  surface_ids[1] = 1;

  std::vector<double> surface_norm_consts( 2 );
  surface_norm_consts[0] = 1.0;
  surface_norm_consts[1] = 2.0;

  std::shared_ptr<TestStandardSurfaceEstimator> estimator(
                     new TestStandardSurfaceEstimator( 0ull,
                                                       2.0,
                                                       surface_ids,
					               surface_norm_consts ) );

  std::vector<MonteCarlo::ParticleType> particle_types( 4 );
  particle_types[0] = MonteCarlo::PHOTON;
  particle_types[1] = MonteCarlo::NEUTRON;
  particle_types[2] = MonteCarlo::ADJOINT_PHOTON;
  particle_types[3] = MonteCarlo::ADJOINT_NEUTRON;

  estimator->setParticleTypes( particle_types );

  // All but the first particle should be ignored
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
// end tstStandardSurfaceEstimator.cpp
//---------------------------------------------------------------------------//
