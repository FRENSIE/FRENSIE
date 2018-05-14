//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IndependentPhaseSpaceDimensionDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Independent phase space dimension distribution class template def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<PhaseSpaceDimension dimension>
IndependentPhaseSpaceDimensionDistribution<dimension>::IndependentPhaseSpaceDimensionDistribution(
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        dimension_distribution )
  : d_dimension_distribution( dimension_distribution )
{
  // Make sure that the dimension distribution is valid
  testPrecondition( dimension_distribution.get() );
}

// Return the phase space dimension
template<PhaseSpaceDimension dimension>
PhaseSpaceDimension
IndependentPhaseSpaceDimensionDistribution<dimension>::getDimension() const
{
  return dimension;
}

// Return the phase space dimension class
template<PhaseSpaceDimension dimension>
PhaseSpaceDimensionClass
IndependentPhaseSpaceDimensionDistribution<dimension>::getDimensionClass() const
{
  return PhaseSpaceDimensionTraits<dimension>::getClass();
}

// Get the distribution type name
template<PhaseSpaceDimension dimension>
std::string
IndependentPhaseSpaceDimensionDistribution<dimension>::getDistributionTypeName() const
{
  return Utility::convertOneDDistributionTypeToString(
                             d_dimension_distribution->getDistributionType() );
}

// Check if the dimension distribution is independent
template<PhaseSpaceDimension dimension>
bool IndependentPhaseSpaceDimensionDistribution<dimension>::isIndependent() const
{
  return true;
}

// Check if the dimension is dependent on the dimension of interest
template<PhaseSpaceDimension dimension>
bool IndependentPhaseSpaceDimensionDistribution<dimension>::isDependentOnDimension(
                              const PhaseSpaceDimension other_dimension ) const
{
  return false;
}

// Check if the dimension distribution is continuous
template<PhaseSpaceDimension dimension>
bool IndependentPhaseSpaceDimensionDistribution<dimension>::isContinuous() const
{
  return d_dimension_distribution->isContinuous();
}

// Check if the dimension distribution is tabular
template<PhaseSpaceDimension dimension>
bool IndependentPhaseSpaceDimensionDistribution<dimension>::isTabular() const
{
  return d_dimension_distribution->isTabular();
}

// Check if the dimension distribution is uniform (somewhere)
template<PhaseSpaceDimension dimension>
bool IndependentPhaseSpaceDimensionDistribution<dimension>::isUniform() const
{
  return this->hasForm( Utility::UNIFORM_DISTRIBUTION );
}

// Check if the underlying distribution has the form of interest
template<PhaseSpaceDimension dimension>
bool IndependentPhaseSpaceDimensionDistribution<dimension>::hasForm(
                  const Utility::OneDDistributionType distribution_type ) const
{
  return d_dimension_distribution->getDistributionType() ==
    distribution_type;
}

// Evaluate the dimension distribution without cascade to dependent dists.
template<PhaseSpaceDimension dimension>
double IndependentPhaseSpaceDimensionDistribution<dimension>::evaluateWithoutCascade(
                               const PhaseSpacePoint& phase_space_point ) const
{
  return d_dimension_distribution->evaluate(
                               getCoordinate<dimension>( phase_space_point ) );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension dimension>
void IndependentPhaseSpaceDimensionDistribution<dimension>::sampleWithoutCascade(
                                    PhaseSpacePoint& phase_space_sample ) const
{
  const double sample = d_dimension_distribution->sample();
  
  setCoordinate<dimension>( phase_space_sample, sample );
  setCoordinateWeight<dimension>( phase_space_sample, 1.0 );
}

// Sample a dimension value without a cascade to the dependent dists.
template<PhaseSpaceDimension dimension>
void IndependentPhaseSpaceDimensionDistribution<dimension>::sampleAndRecordTrialsWithoutCascade(
                                  PhaseSpacePoint& phase_space_sample,
                                  ModuleTraits::InternalCounter& trials ) const
{
  const double sample =
    d_dimension_distribution->sampleAndRecordTrials( trials );

  setCoordinate<dimension>( phase_space_sample, sample );
  setCoordinateWeight<dimension>( phase_space_sample, 1.0 );
}

// Set the dimension value (weight appropriately)
/*! \details The weight associated with the dimension will be the value of
 * the PDF at the specified dimension value.
 */
template<PhaseSpaceDimension dimension>
void IndependentPhaseSpaceDimensionDistribution<dimension>::setDimensionValueAndApplyWeight(
                                           PhaseSpacePoint& phase_space_sample,
                                           const double dimension_value ) const
{
  double weight = this->evaluatePDFWithoutCascade( dimension_value );

  // Make sure that the weight is valid
  TEST_FOR_EXCEPTION( weight <= 0.0,
                      std::logic_error,
                      "An invalid weight (" << weight << ") has been "
                      "calculated for dimension " << dimension << "!" );

  setCoordinate<dimension>( phase_space_sample, dimension_value );
  setCoordinateWeight<dimension>( phase_space_sample, weight );
}

// Evaluate the PDF of this dimension distribution
template<PhaseSpaceDimension dimension>
double IndependentPhaseSpaceDimensionDistribution<dimension>::evaluatePDFWithoutCascade(
                                           const double dimension_value ) const
{
  return d_dimension_distribution->evaluatePDF( dimension_value );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IndependentPhaseSpaceDimensionDistribution_def.hpp
//---------------------------------------------------------------------------//
