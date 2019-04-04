//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MeshTrackLengthFluxEstimator_def.hpp
//! \author Alex Robinson
//! \brief  The mesh track-length flux estimator class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<typename ContributionMultiplierPolicy>
MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::MeshTrackLengthFluxEstimator()
{ /* ... */ }

// Constructor
template<typename ContributionMultiplierPolicy>
MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::MeshTrackLengthFluxEstimator(
                             const Id id,
                             const double multiplier,
                             const std::shared_ptr<const Utility::Mesh>& mesh )
  : StandardEntityEstimator( id, multiplier ),
    d_mesh( mesh ),
    d_no_time_bins_update_method( true ),
    d_update_method()
{
  // Make sure that the mesh pointer is valid
  testPrecondition( mesh.get() );

  // Get the mesh entity volumes an assign
  EntityNormConstMap entity_volumes;

  d_mesh->getElementVolumes( entity_volumes );

  this->assignEntities( entity_volumes );

  this->assignUpdateMethod();
}

// Check if the estimator is a cell estimator
template<typename ContributionMultiplierPolicy>
bool MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::isCellEstimator() const
{
  return false;
}

// Check if the estimator is a surface estimator
template<typename ContributionMultiplierPolicy>
bool MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::isSurfaceEstimator() const
{
  return false;
}

// Check if the estimator is a mesh estimator
template<typename ContributionMultiplierPolicy>
bool MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::isMeshEstimator() const
{
  return true;
}

// Add current history estimator contribution
template<typename ContributionMultiplierPolicy>
void MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromGlobalParticleSubtrackEndingEvent(
                                                 const ParticleState& particle,
                                                 const double start_point[3],
                                                 const double end_point[3] )
{
  // Make sure that the particle type is assigned
  testPrecondition( this->isParticleTypeAssigned( particle.getParticleType() ) );

  d_update_method( particle, start_point, end_point );
}

// Add current history estimator contribution
template<typename ContributionMultiplierPolicy>
void MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromGlobalParticleSubtrackEndingEventNoTimeBinsImpl(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  Utility::Mesh::ElementHandleTrackLengthArray contribution_array;

  d_mesh->computeTrackLengths( start_point, end_point, contribution_array );

  if( contribution_array.size() > 0 )
  {
    ObserverParticleStateWrapper particle_state_wrapper( particle );

    for( size_t i = 0; i < contribution_array.size(); ++i )
    {
      double weighted_contribution = Utility::get<2>( contribution_array[i] )*
        ContributionMultiplierPolicy::multiplier( particle );

      this->addPartialHistoryPointContribution(
                                      Utility::get<0>( contribution_array[i] ),
                                      particle_state_wrapper,
                                      weighted_contribution );
    }
  }
}

// Add current history estimator contribution
template<typename ContributionMultiplierPolicy>
void MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromGlobalParticleSubtrackEndingEventTimeBinsImpl(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  Utility::Mesh::ElementHandleTrackLengthArray contribution_array;

  d_mesh->computeTrackLengths( start_point, end_point, contribution_array );

  if( contribution_array.size() > 0 )
  {
    ObserverParticleStateWrapper particle_state_wrapper( particle );

    const double total_track_length =
      std::sqrt( (end_point[0]-start_point[0])*(end_point[0]-start_point[0]) +
                 (end_point[1]-start_point[1])*(end_point[1]-start_point[1]) +
                 (end_point[2]-start_point[2])*(end_point[2]-start_point[2]) );


    particle_state_wrapper.calculateStateTimesUsingParticleTimeAsEndTime( total_track_length );

    const double start_time = particle_state_wrapper.getStartTime();

    for( size_t i = 0; i < contribution_array.size(); ++i )
    {
      double weighted_contribution = Utility::get<2>( contribution_array[i] )*
        ContributionMultiplierPolicy::multiplier( particle );

      const auto& element_intersection_point =
        Utility::get<1>( contribution_array[i] );

      const double distance_to_element_intersection =
        std::sqrt( (element_intersection_point[0]-start_point[0])*(element_intersection_point[0]-start_point[0]) +
                   (element_intersection_point[1]-start_point[1])*(element_intersection_point[1]-start_point[1]) +
                   (element_intersection_point[2]-start_point[2])*(element_intersection_point[2]-start_point[2]) );

      const double track_start_time =
        start_time + distance_to_element_intersection/particle.getSpeed();

      const double track_end_time =
        track_start_time + Utility::get<2>( contribution_array[i] )/particle.getSpeed();

      particle_state_wrapper.setStartTime( track_start_time );
      particle_state_wrapper.setEndTime( track_end_time );

      this->addPartialHistoryRangeContribution(
                                      Utility::get<0>( contribution_array[i] ),
                                      particle_state_wrapper,
                                      weighted_contribution );
    }
  }
}

// Print the estimator data summary
/*! \details The estimator data will also be exported to a vtk file (e.g.
 * estimator_x.vtk -> x == estimator id).
 */
template<typename ContributionMultiplierPolicy>
void MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::printSummary(
                                                       std::ostream& os ) const
{
  // Collect some basic statistics regarding the mesh elements
  std::vector<unsigned long long> num_zero_elements(
                                  this->getNumberOfResponseFunctions(), 0ull );
  std::vector<unsigned long long> num_elements_lte_1pc_re(
                                  this->getNumberOfResponseFunctions(), 0ull );
  std::vector<unsigned long long> num_elements_lte_5pc_re(
                                  this->getNumberOfResponseFunctions(), 0ull );
  std::vector<unsigned long long> num_elements_lte_10pc_re(
                                  this->getNumberOfResponseFunctions(), 0ull );

  Utility::Mesh::ElementHandleIterator element_it =
    d_mesh->getStartElementHandleIterator();

  Utility::Mesh::ElementHandleIterator end_element_it =
    d_mesh->getEndElementHandleIterator();

  while( element_it != end_element_it )
  {
    const double element_volume = this->getEntityNormConstant( *element_it );

    std::vector<double> mean, relative_error, variance_of_variance,
      figure_of_merit;

    this->getEntityTotalProcessedData( *element_it,
                                       mean,
                                       relative_error,
                                       variance_of_variance,
                                       figure_of_merit );

    for( size_t i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    {
      if( mean[i] == 0.0 && relative_error[i] == 0.0 )
        ++num_zero_elements[i];
      else
      {
        if( relative_error[i] <= 0.10 )
          ++num_elements_lte_10pc_re[i];
        if( relative_error[i] <= 0.05 )
          ++num_elements_lte_5pc_re[i];
        if( relative_error[i] <= 0.01 )
          ++num_elements_lte_1pc_re[i];
      }
    }

    ++element_it;
  }

  size_t num_mesh_elements = d_mesh->getNumberOfElements();

  os << d_mesh->getMeshTypeName() << " track-length flux estimator "
     << this->getId() << ":\n"
     << "  " << d_mesh->getMeshElementTypeName() << "s: "
     << num_mesh_elements << "\n";

  // Print the percentage of elements with no hits
  os << "  % of " << d_mesh->getMeshElementTypeName()
     << " with no hits (per response func.): ";

  for( size_t i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    os << (double)num_zero_elements[i]/num_mesh_elements*100 << " ";

  os << "\n";

  // Print the percentage of elements with <= 10% relative error
  os << "  % of " << d_mesh->getMeshElementTypeName()
     << " with <= 10% RE (per response func.): ";

  for( size_t i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    os << (double)num_elements_lte_10pc_re[i]/num_mesh_elements*100 << " ";

  os << "\n";

  // Print the percentage of elements with <= 5% relative error
  os << "  % of " << d_mesh->getMeshElementTypeName()
     << " with <= 5% RE (per response func.): ";

  for( size_t i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    os << (double)num_elements_lte_5pc_re[i]/num_mesh_elements*100 << " ";

  os << "\n";

  // Print the percentage of elements with <= 1% relative error
  os << "  % of " << d_mesh->getMeshElementTypeName()
     << " with <= 1% RE (per response func.): ";

  for( size_t i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    os << (double)num_elements_lte_1pc_re[i]/num_mesh_elements*100 << " ";

  os << std::endl;

  this->exportAsVtk();
}

// Export the estimator data and mesh as a vtk file
template<typename ContributionMultiplierPolicy>
void MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::exportAsVtk() const
{
  Utility::Mesh::TagNameSet bin_tag_name_set( {"mean: ", "relative_error: ", "fom: "} );

  Utility::Mesh::TagNameSet total_tag_name_set( {"total_mean: ", "total_relative_error: ", "total_vov: ", "total_fom: "} );

  Utility::Mesh::MeshElementHandleDataMap element_data_map;

  Utility::Mesh::ElementHandleIterator element_it =
    d_mesh->getStartElementHandleIterator();

  Utility::Mesh::ElementHandleIterator end_element_it =
    d_mesh->getEndElementHandleIterator();

  while( element_it != end_element_it )
  {
    // Assign the bin data
    std::vector<double> mean, relative_error, variance_of_variance,
      figure_of_merit;

    this->getEntityBinProcessedData( *element_it,
                                     mean,
                                     relative_error,
                                     variance_of_variance,
                                     figure_of_merit );

    auto& entity_bin_mean_data = element_data_map[*element_it]["mean: "];
    entity_bin_mean_data.resize( mean.size() );

    auto& entity_bin_re_data = element_data_map[*element_it]["relative_error: "];
    entity_bin_re_data.resize( relative_error.size() );

    auto& entity_bin_fom_data = element_data_map[*element_it]["fom: "];
    entity_bin_fom_data.resize( figure_of_merit.size() );

    for( size_t i = 0; i < mean.size(); ++i )
    {
      const std::string bin_name = this->getBinName( i );

      entity_bin_mean_data[i] = std::make_pair( bin_name, mean[i] );
      entity_bin_re_data[i] = std::make_pair( bin_name, relative_error[i] );
      entity_bin_fom_data[i] = std::make_pair( bin_name, figure_of_merit[i] );
    }

    // Assign the total data
    std::vector<double> total_mean, total_relative_error,
      total_variance_of_variance, total_figure_of_merit;

    this->getEntityTotalProcessedData( *element_it,
                                       total_mean,
                                       total_relative_error,
                                       total_variance_of_variance,
                                       total_figure_of_merit );

    auto& entity_total_mean_data = element_data_map[*element_it]["total_mean: "];
    entity_total_mean_data.resize( total_mean.size() );

    auto& entity_total_re_data = element_data_map[*element_it]["total_relative_error: "];
    entity_total_re_data.resize( total_relative_error.size() );

    auto& entity_total_vov_data = element_data_map[*element_it]["total_vov: "];
    entity_total_vov_data.resize( total_variance_of_variance.size() );

    auto& entity_total_fom_data = element_data_map[*element_it]["total_fom: "];
    entity_total_fom_data.resize( total_figure_of_merit.size() );

    for( size_t i = 0; i < total_mean.size(); ++i )
    {
      const std::string& response_function_name =
        this->getResponseFunctionName( i );

      entity_total_mean_data[i] =
        std::make_pair( response_function_name, total_mean[i] );
      entity_total_re_data[i] =
        std::make_pair( response_function_name, total_relative_error[i] );
      entity_total_vov_data[i] =
        std::make_pair( response_function_name, total_variance_of_variance[i] );
      entity_total_fom_data[i] =
        std::make_pair( response_function_name,  total_figure_of_merit[i] );
    }

    ++element_it;
  }

  std::string output_name( "estimator_" );
  output_name += Utility::toString( this->getId() );
  output_name += ".vtk";

  Utility::Mesh::TagNameSet tag_name_set( bin_tag_name_set );
  tag_name_set.insert( total_tag_name_set.begin(),
                       total_tag_name_set.end() );

  d_mesh->exportData( output_name,
                      tag_name_set,
                      element_data_map );
}

// Assign discretization to an estimator dimension
template<typename ContributionMultiplierPolicy>
void MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::assignDiscretization(
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
  else if( bins->getDimension() == OBSERVER_TIME_DIMENSION )
  {
    StandardEntityEstimator::assignDiscretization( bins, true );

    d_no_time_bins_update_method = false;

    this->assignUpdateMethod();
  }
  else
    StandardEntityEstimator::assignDiscretization( bins, false );
}

// Assign the particle type to the estimator
template<typename ContributionMultiplierPolicy>
void MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::assignParticleType( const ParticleType particle_type )
{
  if( this->getNumberOfAssignedParticleTypes() != 0 )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                "Mesh track-length flux estimators can only "
                                "have one particle type contribute. Since "
                                "estimator " << this->getId() << " already "
                                "has a particle type assigned the requested "
                                "particle type of " << particle_type <<
                                " will be ignored!" );
  }
  else
    Estimator::assignParticleType( particle_type );
}

// Assign response function to the estimator
template<typename ContributionMultiplierPolicy>
void MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::assignResponseFunction(
             const std::shared_ptr<const ParticleResponse>& response_function )
{
  if( !response_function->isSpatiallyUniform() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                "only spatially uniform response functions "
                                "can be assigned to mesh track-length "
                                "estimators. Estimator " << this->getId() <<
                                " will ignore response function "
                                << response_function->getName() << "!" );
  }
  else
    Estimator::assignResponseFunction( response_function );
}

// Save the data to an archive
template<typename ContributionMultiplierPolicy>
template<typename Archive>
void MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( StandardEntityEstimator );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSubtrackEndingGlobalEventObserver );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_mesh );
  ar & BOOST_SERIALIZATION_NVP( d_no_time_bins_update_method );
}

// Load the data from an archive
template<typename ContributionMultiplierPolicy>
template<typename Archive>
void MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( StandardEntityEstimator );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSubtrackEndingGlobalEventObserver );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_mesh );
  ar & BOOST_SERIALIZATION_NVP( d_no_time_bins_update_method );

  this->assignUpdateMethod();
}

// Assign the update method
template<typename ContributionMultiplierPolicy>
void MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::assignUpdateMethod()
{
  if( d_no_time_bins_update_method )
  {
    d_update_method = std::bind<void>( &MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromGlobalParticleSubtrackEndingEventNoTimeBinsImpl,
                                       std::ref( *this ),
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3 );
  }
  else
  {
    d_update_method = std::bind<void>( &MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromGlobalParticleSubtrackEndingEventTimeBinsImpl,
                                       std::ref( *this ),
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3 );
  }
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightMultipliedMeshTrackLengthFluxEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndEnergyMultipliedMeshTrackLengthFluxEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndChargeMultipliedMeshTrackLengthFluxEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );

#endif // end MONTE_CARLO_MESH_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MeshTrackLengthFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
