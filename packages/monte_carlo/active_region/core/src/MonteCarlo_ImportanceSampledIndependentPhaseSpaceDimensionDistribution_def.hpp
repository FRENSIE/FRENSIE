//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Importance sampled independent phase space dimension distribution
//!         template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
template<PhaseSpaceDimension dimension>
ImportanceSampledIndependentPhaseSpaceDimensionDistribution<dimension>::ImportanceSampledIndependentPhaseSpaceDimensionDistribution(
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  dimension_distribution,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  importance_distribution )
  : BaseType( dimension_distribution ),
    d_dimension_importance_distribution( importance_distribution )
{
  // Make sure that the importance distribution is valid
  testPrecondition( importance_distribution.get() );
  testPrecondition( importance_distribution->hasSameBounds( *dimension_distribution ) );
}

// Sample a dimension value without a cascade to the dependent dists.
/*! \details A phase space dimension value will be sampled from the importance
 * distribution. The weight of the dimension will be the ratio of the
 * dimension distribution PDF and the importance distribution PDF at the 
 * sampled dimension value. This preserves the expected value of the phase
 * space dimension distribution.
 */
template<PhaseSpaceDimension dimension>
void ImportanceSampledIndependentPhaseSpaceDimensionDistribution<dimension>::sampleWithoutCascade(
                                    PhaseSpacePoint& phase_space_sample ) const
{
  const double sample = d_dimension_importance_distribution->sample();

  const double weight = this->calculateSampleWeight( sample );

  MonteCarlo::setCoordinate<dimension>( phase_space_sample, sample );
  MonteCarlo::setCoordinateWeight<dimension>( phase_space_sample, weight );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension dimension>
void ImportanceSampledIndependentPhaseSpaceDimensionDistribution<dimension>::sampleAndRecordTrialsWithoutCascade(
                                           PhaseSpacePoint& phase_space_sample,
                                           Counter& trials ) const
{
  const double sample =
    d_dimension_importance_distribution->sampleAndRecordTrials( trials );

  const double weight = this->calculateSampleWeight( sample );

  MonteCarlo::setCoordinate<dimension>( phase_space_sample, sample );
  MonteCarlo::setCoordinateWeight<dimension>( phase_space_sample, weight );
}

// Calculate the weight of a sample
template<PhaseSpaceDimension dimension>
double ImportanceSampledIndependentPhaseSpaceDimensionDistribution<dimension>::calculateSampleWeight(
                                          const double dimension_sample ) const
{
  const double weight_numerator =
    this->evaluatePDFWithoutCascade( dimension_sample );

  const double weight_denominator =
    d_dimension_importance_distribution->evaluatePDF( dimension_sample );

  double weight = 1.0;

  if( weight_denominator > 0.0 )
  {
    weight = weight_numerator/weight_denominator;

    if( weight == 0.0 )
    {
      FRENSIE_LOG_WARNING( "Distribution evaluated to 0.0 for sample "
                           << dimension_sample << " resulting in a 0.0 "
                           "sample weight. Check that the distributions for "
                           "dimension " << dimension << " have been set up "
                           "correctly!" );
    }
  }
  
  // If we enter this block there is likely a problem with our distributions
  else
  {
    TEST_FOR_EXCEPTION( weight_numerator > 0.0,
                        std::runtime_error,
                        "Importance distribution evaluated to 0.0 for "
                        "sample " << dimension_sample << " resulting in an "
                        "infinite sample weight. Check that the "
                        "importance distribution for dimension "
                        << dimension << " has been set up correctly!" );
    
    // If both evaluate to 0, a weight of 1 is desired but nan will result
    FRENSIE_LOG_WARNING( "Both the distribution and the importance "
                         "distribution evaluated to 0.0 for sample "
                         << dimension_sample << ". The weight will be set "
                         "to 1.0. Check that the distributions for "
                         "dimension " << dimension << " have been set up "
                         "correctly!" );
    weight = 1.0;
  }

  // Make sure that the weight is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf( weight ) );
  testPostcondition( weight > 0.0 );

  return weight;
}

// Save the data to an archive
template<PhaseSpaceDimension dimension>
template<typename Archive>
void ImportanceSampledIndependentPhaseSpaceDimensionDistribution<dimension>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class member data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_dimension_importance_distribution );
}

// Load the data from an archive
template<PhaseSpaceDimension dimension>
template<typename Archive>
void ImportanceSampledIndependentPhaseSpaceDimensionDistribution<dimension>::load( Archive& ar, const unsigned version )
{
  // Load the base class member data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_dimension_importance_distribution );
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledIndependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledIndependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledIndependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledIndependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledIndependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledIndependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledIndependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledIndependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ImportanceSampledIndependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ImportanceSampledIndependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION> );

#endif // end MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution_def.hpp
//---------------------------------------------------------------------------//
