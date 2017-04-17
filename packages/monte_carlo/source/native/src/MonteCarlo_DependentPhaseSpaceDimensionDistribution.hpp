//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Dependent phase space dimension distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// Std Lib Includes
#include <type_traits>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace MonteCarlo{

/*! The dependent phase space dimension distribution class
 * \details This class will be used if parent_dimension == dimension. 
 * Compilation should fail.
 */
template<PhaseSpaceDimension parent_dimension,
         PhaseSpaceDimension dimension,
         typename Enabled = void>
class DependentPhaseSpaceDimensionDistribution
{ /* ... */ };

/*! The dependent phase space dimension distribution class
 * \details This class will be used if parent_dimension != dimension.
 */
template<PhaseSpaceDimension parent_dimension, PhaseSpaceDimension dimension>
class DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension, typename std::enable_if<parent_dimension!=dimension>::type> : public PhaseSpaceDimensionDistribution
{

public:

  //! Constructor
  DependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~DependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Return the phase space dimension
  PhaseSpaceDimension getDimension() const override;

  //! Return the phase space dimension class
  PhaseSpaceDimensionClass getDimensionClass() const override;

  //! Return the parent phase space dimension
  PhaseSpaceDimension getParentDimension() const;

  //! Return the parent phase space dimension class
  PhaseSpaceDimensionClass getParentDimensionClass() const;

  //! Check if the dimension distribution is independent
  bool isIndependent() const override;

  //! Check if the dimension is dependent on the dimension of interest
  bool isDependentOnDimension(
                    const PhaseSpaceDimension other_dimension ) const override;
};

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TIME_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TIME_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,TIME_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TIME_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,WEIGHT_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,ENERGY_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,WEIGHT_DIMENSION> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,ENERGY_DIMENSION> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TIME_DIMENSION> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
