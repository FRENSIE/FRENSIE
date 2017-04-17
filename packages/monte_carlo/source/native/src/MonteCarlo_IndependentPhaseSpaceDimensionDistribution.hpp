//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Independent phase space dimension distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

//! The independent phase space dimension distribution class
template<PhaseSpaceDimension dimension>
class IndependentPhaseSpaceDimensionDistribution : public PhaseSpaceDimensionDistribution
{

public:

  //! Constructor
  IndependentPhaseSpaceDimensionDistribution(
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        dimension_distribution );

  //! Destructor
  virtual ~IndependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Return the phase space dimension
  PhaseSpaceDimension getDimension() const override;

  //! Return the phase space dimension class
  PhaseSpaceDimensionClass getDimensionClass() const override;

  //! Get the distribution type name
  std::string getDistributionTypeName() const override;

  //! Check if the dimension distribution is independent
  bool isIndependent() const override;

  //! Check if the dimension is dependent on the dimension of interest
  bool isDependentOnDimension(
                    const PhaseSpaceDimension other_dimension ) const override;

  //! Check if the dimension distribution is continuous
  bool isContinuous() const override;

  //! Check if the dimension distribution is tabular
  bool isTabular() const override;

  //! Check if the dimension distribution is uniform (somewhere)
  bool isUniform() const;

  //! Check if the underlying distribution has the form of interest
  bool hasForm( const Utility::OneDDistributionType distribution_type ) const override;

  //! Evaluate the dimension distribution without cascade to dependent dists.
  double evaluateWithoutCascade(
                     const PhaseSpacePoint& phase_space_point ) const override;

  //! Sample a dimension value without a cascade to the dependent dists.
  virtual void sampleWithoutCascade(
                          PhaseSpacePoint& phase_space_sample ) const override;

  //! Sample a dimension value without a cascade to the dependent dists.
  virtual void sampleAndRecordTrialsWithoutCascade(
                        PhaseSpacePoint& phase_space_sample,
                        ModuleTraits::InternalCounter& trials ) const override;

  //! Set the dimension value (weight appropriately)
  void setDimensionValueAndApplyWeight(
                                 PhaseSpacePoint& phase_space_sample,
                                 const double dimension_value ) const override;
  
protected:

  //! Evaluate the PDF of this dimension distribution
  double evaluatePDFWithoutCascade( const double dimension_value ) const;

private:

  // The dimension distribution
  std::shared_ptr<const Utility::OneDDistribution> d_dimension_distribution;
};

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<TIME_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION> );
  
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_INDEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
