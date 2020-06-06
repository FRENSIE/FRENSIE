//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellPulseHeightEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_PhysicalConstants.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<typename ContributionMultiplierPolicy>
CellPulseHeightEstimator<ContributionMultiplierPolicy>::CellPulseHeightEstimator()
{ /* ... */ }

// Constructor
template<typename ContributionMultiplierPolicy>
CellPulseHeightEstimator<ContributionMultiplierPolicy>::CellPulseHeightEstimator(
          const Id id,
          const double multiplier,
          const std::vector<CellIdType>& entity_ids )
  : EntityEstimator( id, multiplier, entity_ids ),
    ParticleEnteringCellEventObserver(),
    ParticleLeavingCellEventObserver(),
    d_update_tracker( 1 ),
    d_dimension_values( 1 )
{
  // Set the particle types to photon, electron, positron
  Estimator::assignParticleType( PHOTON );
  Estimator::assignParticleType( ELECTRON );
  Estimator::assignParticleType( POSITRON );
}

// Check if the estimator is a cell estimator
template<typename ContributionMultiplierPolicy>
bool CellPulseHeightEstimator<ContributionMultiplierPolicy>::isCellEstimator() const
{
  return true;
}

// Check if the estimator is a surface estimator
template<typename ContributionMultiplierPolicy>
bool CellPulseHeightEstimator<ContributionMultiplierPolicy>::isSurfaceEstimator() const
{
  return false;
}

// Check if the estimator is a mesh estimator
template<typename ContributionMultiplierPolicy>
bool CellPulseHeightEstimator<ContributionMultiplierPolicy>::isMeshEstimator() const
{
  return false;
}

// Check and correct a positron contribution
template<typename ContributionMultiplierPolicy>
inline void CellPulseHeightEstimator<ContributionMultiplierPolicy>::checkAndCorrectPositronEnergyContribution(
                                                 const ParticleState& particle,
                                                 double& energy_contribution )
{
  // A special energy accounting must be done with positrons since they come
  // about from pair production, which converts some of the photon's energy
  // to mass energy. The positron will account for both the electron's and the
  // positron's mass since it is easier to identify. Unfortunately, this can
  // lead to an incorrect energy accounting if the positron leaves the cell
  // and the electron does not (or vice versa). Given the very small mfp of
  // electrons and positrons, this will usually not be a problem (be careful in
  // very thin films)
  if( particle.getParticleType() == POSITRON )
  {
    // Ingore source positrons (we only want progeny positrons)
    if( particle.getGenerationNumber() > 0 )
    {
      energy_contribution +=
        2*Utility::PhysicalConstants::electron_rest_mass_energy;
    }
  }
}

// Add current history estimator contribution
/*! \details It is unsafe to call this function directly! This function will
 * be called by the appropriate dispatcher when an event of interest occurs.
 * If calling this function directly, make sure that the cell of interest is
 * actually assigned to this estimator (otherwise segfaults are likely!).
 */
template<typename ContributionMultiplierPolicy>
inline void CellPulseHeightEstimator<ContributionMultiplierPolicy>::updateFromParticleEnteringCellEvent(
                                               const ParticleState& particle,
                                               const CellIdType cell_entering )
{
  // Make sure that the particle type is assigned
  testPrecondition( this->isParticleTypeAssigned( particle.getParticleType() ) );

  unsigned thread_id = Utility::OpenMPProperties::getThreadId();

  double energy_contribution = particle.getWeight()*particle.getEnergy();

  this->checkAndCorrectPositronEnergyContribution( particle, energy_contribution );

  double charge_contribution = particle.getWeight()*particle.getCharge();

  this->addInfoToUpdateTracker( thread_id,
                                cell_entering,
                                particle.getSourceWeight(),
                                energy_contribution,
                                charge_contribution );

  // Indicate that there is an uncommitted history contribution
  this->setHasUncommittedHistoryContribution( thread_id );
}

// Add current history estimator contribution
/*! \details It is unsafe to call this function directly! This function will
 * be called by the appropriate dispatcher when an event of interest occurs.
 * If calling this function directly, make sure that the cell of interest is
 * actually assigned to this estimator (otherwise segfaults are likely! ).
 */
template<typename ContributionMultiplierPolicy>
inline void CellPulseHeightEstimator<ContributionMultiplierPolicy>::updateFromParticleLeavingCellEvent(
                                                const ParticleState& particle,
                                                const CellIdType cell_leaving )
{
  // Make sure that the particle type is assigned
  testPrecondition( this->isParticleTypeAssigned( particle.getParticleType() ) );
  unsigned thread_id = Utility::OpenMPProperties::getThreadId();

  double energy_contribution = particle.getWeight()*particle.getEnergy();

  this->checkAndCorrectPositronEnergyContribution( particle, energy_contribution );

  energy_contribution *= -1.0;

  double charge_contribution = -particle.getWeight()*particle.getCharge();

  this->addInfoToUpdateTracker( thread_id,
                                cell_leaving,
                                particle.getSourceWeight(),
                                energy_contribution,
                                charge_contribution );

  // Indicate that there is an uncommitted history contribution
  this->setHasUncommittedHistoryContribution( thread_id );
}

// Add estimator contribution from a portion of the current history
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::commitHistoryContribution()
{
  unsigned thread_id = Utility::OpenMPProperties::getThreadId();

  typename Utility::TupleElement<1,SerialUpdateTracker>::type::const_iterator
    cell_data, end_cell_data;

  this->getCellIteratorFromUpdateTracker( thread_id, cell_data, end_cell_data );

  double energy_deposition_in_all_cells = 0.0;
  double charge_deposition_in_all_cells = 0.0;
  double source_weight = d_update_tracker[thread_id].first;

  size_t bin_index;
  double bin_contribution;

  Estimator::DimensionValueMap& thread_dimension_values =
    d_dimension_values[thread_id];

  while( cell_data != end_cell_data )
  {
    // The energy deposited in the cell by this history must be multiplied by
    // the source weight
    thread_dimension_values[OBSERVER_ENERGY_DIMENSION] =
      boost::any( Utility::get<0>(cell_data->second)*source_weight );

    if( this->isPointInObserverPhaseSpace( thread_dimension_values ) )
    {
      ObserverPhaseSpaceDimensionDiscretization::BinIndexArray bin_indices;

      this->calculateBinIndicesOfPoint( thread_dimension_values,
                                        0u,
                                        bin_indices );

      bin_contribution = this->calculateHistoryContribution(
                                            Utility::get<0>(cell_data->second),
                                            Utility::get<1>(cell_data->second),
                                            source_weight,
                                            ContributionMultiplierPolicy() );

      for( size_t i = 0; i < bin_indices.size(); ++i )
      {
        this->commitHistoryContributionToBinOfEntity( cell_data->first,
                                                      bin_indices[i],
                                                      bin_contribution );
      }

      // Add the energy deposition in this cell to the total energy deposition
      energy_deposition_in_all_cells += Utility::get<0>(cell_data->second);
      charge_deposition_in_all_cells += Utility::get<1>(cell_data->second);
    }

    ++cell_data;
  }

  // Store the total energy deposition in the dimension values map
  // The total energy deposited in all cells by this history must be multiplied
  // by the source weight
  thread_dimension_values[OBSERVER_ENERGY_DIMENSION] =
    boost::any( energy_deposition_in_all_cells*source_weight );

  // Determine the pulse bin for the combination of all cells
  if( this->isPointInObserverPhaseSpace( thread_dimension_values ) )
  {
    ObserverPhaseSpaceDimensionDiscretization::BinIndexArray bin_indices;

    this->calculateBinIndicesOfPoint( thread_dimension_values,
                                      0u,
                                      bin_indices );

    bin_contribution = this->calculateHistoryContribution(
                                            energy_deposition_in_all_cells,
                                            charge_deposition_in_all_cells,
                                            source_weight,
                                            ContributionMultiplierPolicy() );

    for( size_t i = 0; i < bin_indices.size(); ++i )
    {
      this->commitHistoryContributionToBinOfTotal( bin_indices[i],
                                                   bin_contribution );
    }
  }

  // Reset the update tracker
  this->resetUpdateTracker( thread_id );

  // Reset the has uncommitted history contribution boolean
  this->unsetHasUncommittedHistoryContribution( thread_id );
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::printSummary(
                                                       std::ostream& os ) const
{
  os << "Cell Pulse Height Estimator: " << this->getId() << "\n";

  this->printImplementation( os, "Cell" );
}

// Enable support for multiple threads
template<typename ContributionMultiplierPolicy>
void
CellPulseHeightEstimator<ContributionMultiplierPolicy>::enableThreadSupport(
                                                   const unsigned num_threads )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  EntityEstimator::enableThreadSupport( num_threads );

  // Add thread support to update tracker
  d_update_tracker.resize( num_threads );

  // Add thread support to the dimension values
  d_dimension_values.resize( num_threads );
}

// Reset the estimator data
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::resetData()
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  EntityEstimator::resetData();

  // Reset the update tracker
  for( size_t i = 0; i < d_update_tracker.size(); ++i )
  {
    d_update_tracker[i].first = 0.0;
    d_update_tracker[i].second.clear();

    this->unsetHasUncommittedHistoryContribution( i );
  }
}

// Assign bin boundaries to an estimator dimension
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::assignDiscretization(
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
  const bool range_dimension )
{
  if( bins->getDimension() == OBSERVER_ENERGY_DIMENSION )
    EntityEstimator::assignDiscretization( bins, false );
  else
  {
    FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                bins->getDimensionName() <<
                                " bins cannot be set for pulse height "
                                "estimators. The bins requested for pulse "
                                "height estimator " << this->getId() <<
                                " will be ignored." );
  }
}

// Set the response functions
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::assignResponseFunction(
             const std::shared_ptr<const ParticleResponse>& response_function )
{
  FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                              "response functions cannot be set for pulse "
                              "height estimators. The response function "
                              "requested for pulse height estimator "
                              << this->getId() << " will be ignored." );
}

// Set the particle types that can contribute to the estimator
/*! \details Only photons and electrons can contribute to this estimator
 */
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::assignParticleType( const ParticleType particle_type )
{
  FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                              "the particle types assigned to a cell pulse "
                              "height estimator are always PHOTON, ELECTRON "
                              "and POSITRON. Pulse height estimator "
                              << this->getId() <<
                              " will ignore this request." );

}

// Calculate the estimator contribution from the entire history
/*! \details The multiplier policy cannot be used directly since it only
 * operates on a particle state. The policy classes will instead be used as
 * tags for tag dispatching. This function simply returns 1.0.
 */
template<typename ContributionMultiplierPolicy>
inline double CellPulseHeightEstimator<ContributionMultiplierPolicy>::calculateHistoryContribution(
                                                    const double,
                                                    const double,
                                                    const double source_weight,
                                                    WeightMultiplier )
{
  return source_weight;
}

// Calculate the estimator contribution from the entire history
/*! \details The multiplier policy cannot be used directly since it only
 * operates on a particle state. The policy classes will instead be used as
 * tags for tag dispatching. This function returns the energy that has been
 * deposited in the cell(s) of interest for the entire history.
 */
template<typename ContributionMultiplierPolicy>
inline double CellPulseHeightEstimator<ContributionMultiplierPolicy>::calculateHistoryContribution(
                                                const double energy_deposition,
                                                const double,
                                                const double source_weight,
                                                WeightAndEnergyMultiplier )
{
  return energy_deposition*source_weight;
}

// Calculate the estimator contribution from the entire history
/*! \details The multiplier policy cannot be used directly since it only
 * operates on a particle state. The policy classes will instead be used as
 * tags for tag dispatching. This function returns the energy that has been
 * deposited in the cell(s) of interest for the entire history.
 */
template<typename ContributionMultiplierPolicy>
inline double CellPulseHeightEstimator<ContributionMultiplierPolicy>::calculateHistoryContribution(
                                                const double,
                                                const double charge_deposition,
                                                const double source_weight,
                                                WeightAndChargeMultiplier )
{
  // We simply check if the net charge is positive or negative (or zero)
  if( charge_deposition > 0.0 )
    return source_weight;
  else if( charge_deposition < 0.0 )
    return -source_weight;
  else
    return 0.0;
}

// Add info to update tracker
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::addInfoToUpdateTracker(
                                             const unsigned thread_id,
                                             const CellIdType cell_id,
                                             const double source_weight,
                                             const double energy_contribution,
                                             const double charge_contribution )
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );

  SerialUpdateTracker& thread_update_tracker = d_update_tracker[thread_id];

  auto cell_it = thread_update_tracker.second.find( cell_id );

  if( thread_update_tracker.first == 0.0 )
    thread_update_tracker.first = source_weight;

  if( cell_it != thread_update_tracker.second.end() )
  {
    Utility::get<0>( cell_it->second ) += energy_contribution;
    Utility::get<1>( cell_it->second ) += charge_contribution;
  }
  else
  {
    thread_update_tracker.second[cell_id] =
      std::make_pair( energy_contribution, charge_contribution );
  }
}

// Get the entity iterators from the update tracker
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::getCellIteratorFromUpdateTracker(
                 const unsigned thread_id,
                 typename Utility::TupleElement<1,SerialUpdateTracker>::type::const_iterator& start_cell,
                typename Utility::TupleElement<1,SerialUpdateTracker>::type::const_iterator& end_cell ) const
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );

  start_cell = d_update_tracker[thread_id].second.begin();
  end_cell = d_update_tracker[thread_id].second.end();
}

// Reset the update tracker
template<typename ContributionMultiplierPolicy>
void
CellPulseHeightEstimator<ContributionMultiplierPolicy>::resetUpdateTracker(
                                                     const unsigned thread_id )
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );

  d_update_tracker[thread_id].first = 0.0;
  d_update_tracker[thread_id].second.clear();
}

// Save the data to an archive
// Note: The update tracker will not be saved. Any uncommited data should be
// committed before the save.
template<typename ContributionMultiplierPolicy>
template<typename Archive>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( EntityEstimator );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleEnteringCellEventObserver );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleLeavingCellEventObserver );
}

// Load the data from an archive
template<typename ContributionMultiplierPolicy>
template<typename Archive>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( EntityEstimator );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleEnteringCellEventObserver );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleLeavingCellEventObserver );

  // Initialize the thread data
  d_update_tracker.resize( 1 );
  d_dimension_values.resize( 1 );
}

} // end MonteCarlo namespace

// Explicit instantiation (extern declaration)
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightMultipliedCellPulseHeightEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndEnergyMultipliedCellPulseHeightEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndChargeMultipliedCellPulseHeightEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndChargeMultiplier> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, CellPulseHeightEstimator<MonteCarlo::WeightAndChargeMultiplier> );

#endif // end MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellPulseHeightEstimator_def.hpp
//---------------------------------------------------------------------------//
