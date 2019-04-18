//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Importance sampled dependent phase space dimension distribution
//!         class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
ImportanceSampledDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::ImportanceSampledDependentPhaseSpaceDimensionDistribution(
              const std::shared_ptr<const Utility::BasicBivariateDistribution>&
              dimension_distribution,
              const std::shared_ptr<const Utility::BasicBivariateDistribution>&
              importance_distribution )
  : BaseType( dimension_distribution ),
    d_dimension_importance_distribution( importance_distribution )
{
  // Make sure that the dimension distribution is valid
  testPrecondition( importance_distribution.get() );
  testPrecondition( importance_distribution->hasSamePrimaryBounds( *dimension_distribution ) );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
void ImportanceSampledDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::sampleWithoutCascade(
                                    PhaseSpacePoint& phase_space_sample ) const
{
  const double sample =
    d_dimension_importance_distribution->sampleSecondaryConditional(
           MonteCarlo::getCoordinate<parent_dimension>( phase_space_sample ) );

  const double weight =
    this->calculateSampleWeight(
             MonteCarlo::getCoordinate<parent_dimension>( phase_space_sample ),
             sample );

  MonteCarlo::setCoordinate<dimension>( phase_space_sample, sample );
  MonteCarlo::setCoordinateWeight<dimension>( phase_space_sample, weight );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
void ImportanceSampledDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::sampleAndRecordTrialsWithoutCascade(
                                           PhaseSpacePoint& phase_space_sample,
                                           Counter& trials ) const
{
  const double sample =
    d_dimension_importance_distribution->sampleSecondaryConditionalAndRecordTrials(
             MonteCarlo::getCoordinate<parent_dimension>( phase_space_sample ),
             trials );
  
  const double weight =
    this->calculateSampleWeight(
             MonteCarlo::getCoordinate<parent_dimension>( phase_space_sample ),
             sample );
  
  MonteCarlo::setCoordinate<dimension>( phase_space_sample, sample );
  MonteCarlo::setCoordinateWeight<dimension>( phase_space_sample, weight );
}

// Calculate the weight of a sample
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
double ImportanceSampledDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::calculateSampleWeight(
                                      const double parent_dimension_value,
                                      const double dimension_sample ) const
{
  const double weight_numerator =
    this->evaluatePDFWithoutCascade(
                                    parent_dimension_value, dimension_sample );

  const double weight_denominator =
    d_dimension_importance_distribution->evaluateSecondaryConditionalPDF(
                                    parent_dimension_value, dimension_sample );

  double weight = 1.0;

  if( weight_denominator > 0.0 )
  {
    weight = weight_numerator/weight_denominator;

    if( weight == 0.0 )
    {
      FRENSIE_LOG_WARNING( "Distribution evaluated to 0.0 for sample "
                           << dimension_sample << " resulting in a 0.0 "
                           "sample weight. Check that the distributions for "
                           "dependent dimension " << dimension <<
                           " have been set up correctly!" );
    }
  }

  // If we enter this block there is likely a problem with our distributions
  else
  {
    TEST_FOR_EXCEPTION( weight_numerator > 0.0,
                        std::runtime_error,
                        "Importance distribution evaluated to 0.0 for "
                        "sample " << dimension_sample << " resulting "
                        "in an infinite sample weight. Check that the "
                        "importance distribution for dependent dimension "
                        << dimension << " has been set up correctly!" );

    // If both evaluate to 0, a weight of 1 is desired but nan will result
    FRENSIE_LOG_WARNING( "Both the distribution and the importance "
                         "distribution evaluated to 0.0 for sample "
                         << dimension_sample << ". The weight will be "
                         "set to 1.0. Check that the distributions for "
                         "dependent dimension " << dimension << " have "
                         "been set up correctly!" );
    weight = 1.0;
  }

  // Make sure that the weight is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf( weight ) );
  testPostcondition( weight > 0.0 );

  return weight;
}

// Save the data to an archive
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
template<typename Archive>
void ImportanceSampledDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class member data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_dimension_importance_distribution );
}

// Load the data from an archive
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
template<typename Archive>
void ImportanceSampledDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::load( Archive& ar, const unsigned version )
{
  // Load the base class member data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_dimension_importance_distribution );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// DependentPrimarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondarySpatialDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiarySpatialDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimaryDirectionalDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondaryDirectionalDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiaryDirectionalDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledEnergyDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTimeDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledWeightDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentSecondarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimarySpatialDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiarySpatialDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimaryDirectionalDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondaryDirectionalDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiaryDirectionalDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledEnergyDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTimeDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledWeightDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTertiarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimarySpatialDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondarySpatialDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimaryDirectionalDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondaryDirectionalDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiaryDirectionalDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledEnergyDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTimeDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledWeightDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentPrimaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimarySpatialDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondarySpatialDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiarySpatialDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondaryDirectionalDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiaryDirectionalDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledEnergyDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTimeDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledWeightDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentSecondaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimarySpatialDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondarySpatialDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiarySpatialDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimaryDirectionalDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiaryDirectionalDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledEnergyDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTimeDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledWeightDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTertiaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimarySpatialDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondarySpatialDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiarySpatialDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimaryDirectionalDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondaryDirectionalDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledEnergyDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTimeDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledWeightDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentEnergyDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimarySpatialDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondarySpatialDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiarySpatialDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimaryDirectionalDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondaryDirectionalDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiaryDirectionalDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTimeDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledWeightDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTimeDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimarySpatialDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondarySpatialDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiarySpatialDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimaryDirectionalDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondaryDirectionalDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiaryDirectionalDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledEnergyDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledWeightDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TIME_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentWeightDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimarySpatialDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondarySpatialDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiarySpatialDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledPrimaryDirectionalDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledSecondaryDirectionalDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTertiaryDirectionalDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledEnergyDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledTimeDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

#endif // end MONTE_CARLO_IMPORTANCE_SAMPLED_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution_def.hpp
//---------------------------------------------------------------------------//
