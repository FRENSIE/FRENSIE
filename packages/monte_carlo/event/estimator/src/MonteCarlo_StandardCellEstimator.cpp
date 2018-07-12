//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCellEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard cell estimator class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_StandardCellEstimator.hpp"
#include "Utility_LoggingMacros.hpp"

namespace MonteCarlo{

// Default constructor
StandardCellEstimator::StandardCellEstimator()
{ /* ... */ }
  
// Constructor
StandardCellEstimator::StandardCellEstimator(
                                      const uint32_t id,
                                      const double multiplier,
                                      const std::vector<CellIdType>& cell_ids,
                                      const std::vector<double>& cell_volumes )
  : StandardEntityEstimator( id, multiplier, cell_ids, cell_volumes )
{ /* ... */ }
  
// Assign discretization to an estimator dimension
/*! \details The MonteCarlo::OBSERVER_COSINE_DIMENSION cannot be discretized in
 * standard cell estimators.
 */
void StandardCellEstimator::assignDiscretization(
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
  const bool range_dimension )
{
  if( bins->getDimension() == OBSERVER_COSINE_DIMENSION )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                bins->getDimensionName() <<
                                " bins cannot be set for standard cell "
                                "estimators. The bins requested for standard "
                                "cell estimator " << this->getId() <<
                                " will be ignored!" );
  }
  else
    StandardEntityEstimator::assignDiscretization( bins, range_dimension );
}

// Assign the particle type to the estimator
/*! \details Photons, electrons and neutrons (or their adjoint
 * couterparts) can contribute to the estimator. Combinations are not
 * allowed.
 */
void StandardCellEstimator::assignParticleType(
                                            const ParticleType& particle_type )
{
  if( this->getNumberOfAssignedParticleTypes() != 0 )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                "Standard cell estimators can only have one "
                                "particle type contribute. Since estimator "
                                << this->getId() << " already has a particle "
                                "type assigned the requested particle type of "
                                << particle_type << " will be ignored!" );
  }
  else
    Estimator::assignParticleType( particle_type );
}

} // end MonteCarlo namespace

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::StandardCellEstimator );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCellEstimator.cpp
//---------------------------------------------------------------------------//
