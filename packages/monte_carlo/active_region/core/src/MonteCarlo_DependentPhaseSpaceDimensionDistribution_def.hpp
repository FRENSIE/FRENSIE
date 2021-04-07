//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DependentPhaseSpaceDimensionDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Dependent phase space dimension distribution class template def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
template<PhaseSpaceDimension parent_dimension, PhaseSpaceDimension dimension>
DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::DependentPhaseSpaceDimensionDistribution(
              const std::shared_ptr<const Utility::BasicBivariateDistribution>&
              dimension_distribution )
  : d_dimension_distribution( dimension_distribution )
{
  // Make sure that the dimension distribution is valid
  testPrecondition( dimension_distribution.get() );
}

// Return the phase space dimension
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
PhaseSpaceDimension DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::getDimension() const
{
  return dimension;
}

// Return the phase space dimension class
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
PhaseSpaceDimensionClass DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::getDimensionClass() const
{
  return PhaseSpaceDimensionTraits<dimension>::getClass();
}

// Return the independent phase space dimension
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
PhaseSpaceDimension DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::getParentDimension() const
{
  return parent_dimension;
}

// Return the independent phase space dimension class
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
PhaseSpaceDimensionClass DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::getParentDimensionClass() const
{
  return PhaseSpaceDimensionTraits<parent_dimension>::getClass();
}

// Check if the dimension distribution is independent
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
bool DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::isIndependent() const
{
  return false;
}

// Check if the dimension is dependent on the dimension of interest
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
bool DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::isDependentOnDimension(
                              const PhaseSpaceDimension other_dimension ) const
{
  return parent_dimension == other_dimension;
}

// Check if the dimension distribution is continuous
/*! \details This method only checks if the distribution is continuous w.r.t.
 * the independent dimension. More information is needed to check if the
 * distribution is continuous w.r.t. the dependent dimension.
 */
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>

bool DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::isContinuous() const
{
  return d_dimension_distribution->isPrimaryDimensionContinuous();
}

// Check if the dimension distribution is tabular
/*! \details This method only checks if the distribution is tabular w.r.t.
 * the independent dimension. More information is needed to check if the
 * distribution is tabular w.r.t. the dependent dimension.
 */
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
bool DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::isTabular() const
{
  return d_dimension_distribution->isPrimaryDimensionTabular();
}

// Check if the dimension distribution is uniform (somewhere)
/*! \details This method will always return false since we cannot test
 * if the two-d distribution is constant everywhere that it is defined.
 */
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
bool DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::isUniform() const
{
  return false;
}

// Check if the underlying distribution has the form of interest
/*! \details This method will always return false since we cannot test
 * if the two-d distribution has the form of interest everywhere that it is
 * defined.
 */
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
bool DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::hasForm(
                              const Utility::UnivariateDistributionType ) const
{
  return false;
}

// Get the distribution type name
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
std::string DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::getDistributionTypeName() const
{
  return "BasicBivariateDistribution";
}

// Evaluate the dimension distribution without cascade to dependent dists.
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
double DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::evaluateWithoutCascade(
                               const PhaseSpacePoint& phase_space_point ) const
{
  return d_dimension_distribution->evaluate(
              MonteCarlo::getCoordinate<parent_dimension>( phase_space_point ),
              MonteCarlo::getCoordinate<dimension>( phase_space_point ) );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
void DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::sampleWithoutCascade(
                                    PhaseSpacePoint& phase_space_sample ) const
{
  const double sample =
    d_dimension_distribution->sampleSecondaryConditional(
           MonteCarlo::getCoordinate<parent_dimension>( phase_space_sample ) );

  MonteCarlo::setCoordinate<dimension>( phase_space_sample, sample );
  MonteCarlo::setCoordinateWeight<dimension>( phase_space_sample, 1.0 );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
void DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::sampleAndRecordTrialsWithoutCascade(
                                  PhaseSpacePoint& phase_space_sample,
                                  Counter& trials ) const
{
  const double sample =
    d_dimension_distribution->sampleSecondaryConditionalAndRecordTrials(
             MonteCarlo::getCoordinate<parent_dimension>( phase_space_sample ),
             trials );

  MonteCarlo::setCoordinate<dimension>( phase_space_sample, sample );
  MonteCarlo::setCoordinateWeight<dimension>( phase_space_sample, 1.0 );
}

// Set the dimension value (weight appropriately)
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
void DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::setDimensionValueAndApplyWeight(
                                           PhaseSpacePoint& phase_space_sample,
                                           const double dimension_value ) const
{
  const double weight = this->evaluatePDFWithoutCascade(
             MonteCarlo::getCoordinate<parent_dimension>( phase_space_sample ),
             dimension_value );

  // Make sure that the weight is valid
  TEST_FOR_EXCEPTION( weight <= 0.0,
                      std::logic_error,
                      "An invalid weight (" << weight << ") has been "
                      "calculated for dimension " << dimension << "!" );

  MonteCarlo::setCoordinate<dimension>( phase_space_sample, dimension_value );
  MonteCarlo::setCoordinateWeight<dimension>( phase_space_sample, weight );
}

// Evaluate the PDF of this dimension distribution
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
double DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::evaluatePDFWithoutCascade(
                                          const double parent_dimension_value,
                                          const double dimension_value ) const
{
  return d_dimension_distribution->evaluateSecondaryConditionalPDF(
                                     parent_dimension_value, dimension_value );
}

// Save the data to an archive
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
template<typename Archive>
void DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class member data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( PhaseSpaceDimensionDistribution );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_dimension_distribution );
}

// Load the data from an archive
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
template<typename Archive>
void DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension>::load( Archive& ar, const unsigned version )
{
  // Load the base class member data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( PhaseSpaceDimensionDistribution );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_dimension_distribution );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// DependentPrimarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondarySpatialDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiarySpatialDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimaryDirectionalDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondaryDirectionalDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiaryDirectionalDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( EnergyDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TimeDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightDependentPrimarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentSecondarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimarySpatialDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiarySpatialDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimaryDirectionalDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondaryDirectionalDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiaryDirectionalDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( EnergyDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TimeDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightDependentSecondarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTertiarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimarySpatialDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondarySpatialDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimaryDirectionalDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondaryDirectionalDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiaryDirectionalDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( EnergyDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TimeDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightDependentTertiarySpatialDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentPrimaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimarySpatialDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondarySpatialDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiarySpatialDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondaryDirectionalDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiaryDirectionalDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( EnergyDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TimeDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightDependentPrimaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentSecondaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimarySpatialDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondarySpatialDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiarySpatialDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimaryDirectionalDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiaryDirectionalDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( EnergyDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TimeDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightDependentSecondaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTertiaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimarySpatialDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondarySpatialDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiarySpatialDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimaryDirectionalDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondaryDirectionalDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( EnergyDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TimeDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightDependentTertiaryDirectionalDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentEnergyDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimarySpatialDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondarySpatialDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiarySpatialDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimaryDirectionalDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondaryDirectionalDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiaryDirectionalDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TimeDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightDependentEnergyDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTimeDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimarySpatialDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondarySpatialDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiarySpatialDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimaryDirectionalDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondaryDirectionalDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiaryDirectionalDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( EnergyDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightDependentTimeDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TIME_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentWeightDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimarySpatialDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondarySpatialDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiarySpatialDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PrimaryDirectionalDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SecondaryDirectionalDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TertiaryDirectionalDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( EnergyDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TimeDependentWeightDimensionDistribution, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

#endif // end MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DependentPhaseSpaceDimensionDistribution_def.hpp
//---------------------------------------------------------------------------//
