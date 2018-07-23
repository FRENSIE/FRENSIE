//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimension.i
//! \author Luke Kersting
//! \brief  The PhaseSpaceDimension classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "MonteCarlo_PhaseSpacePoint.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_PhaseSpaceDimensionClass.hpp"
#include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraitsDecl.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution.hpp"

#include "Utility_UnivariateDistributionType.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_EquiprobableBinDistribution.hpp"
#include "Utility_EvaporationDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_MaxwellFissionDistribution.hpp"
#include "Utility_NormalDistribution.hpp"
#include "Utility_PolynomialDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TabularCDFDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_WattDistribution.hpp"

#include "Utility_BasicBivariateDistribution.hpp"
#include "Utility_TabularBasicBivariateDistribution.hpp"
#include "Utility_PartiallyTabularBasicBivariateDistribution.hpp"
#include "Utility_FullyTabularBasicBivariateDistribution.hpp"
#include "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"
#include "Utility_InterpolatedPartiallyTabularBasicBivariateDistribution.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_HistogramTabularBasicBivariateDistributionImplBase.hpp"
#include "Utility_HistogramPartiallyTabularBasicBivariateDistribution.hpp"
#include "Utility_HistogramFullyTabularBasicBivariateDistribution.hpp"

#include "Utility_SpatialCoordinateConversionPolicy.hpp"
#include "Utility_DirectionalCoordinateConversionPolicy.hpp"

#include "Utility_CartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_CartesianDirectionalCoordinateConversionPolicy.hpp"
#include "Utility_TranslationCartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_GeneralCartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_RotationCartesianCoordinateConversionPolicy.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"

#include "Utility_CylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_TranslationCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_GeneralCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_RotationCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"

#include "Utility_SphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_SphericalDirectionalCoordinateConversionPolicy.hpp"
#include "Utility_TranslationSphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_GeneralSphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_RotationSphericalCoordinateConversionPolicy.hpp"
#include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"

#include "Utility_SpatialDimensionType.hpp"
#include "Utility_DirectionalDimensionType.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"

using namespace MonteCarlo;
%}

// Include the PhaseSpaceDimension helpers
%include "MonteCarlo_PhaseSpaceDimensionHelpers.i"

// ---------------------------------------------------------------------------//
// Add PhaseSpacePoint support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_PhaseSpacePoint.hpp"

// ---------------------------------------------------------------------------//
// Add PhaseSpaceDimension support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_PhaseSpaceDimension.hpp"

// Add some useful methods to the class
%extend MonteCarlo::PhaseSpaceDimension
{
  // String representation method
  PyObject* __repr__() const
  {
    std::string repr_string = Utility::toString($self);
    return PyString_FromString( repr_string.c_str() );
  }

  // String conversion method
  PyObject* __str__() const
  {
    std::string repr_string = Utility::toString($self);
    return PyString_FromString( repr_string.c_str() );
  }
};

// ---------------------------------------------------------------------------//
// Add PhaseSpaceDimensionClass support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_PhaseSpaceDimensionClass.hpp"

// ---------------------------------------------------------------------------//
// Add PhaseSpaceDimensionTraits support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_PhaseSpaceDimensionTraitsDecl.hpp"

// // The primary spatial PhaseSpaceDimension
// %template(PhaseSpacePrimarySpatialDimensionTraits) MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>;

%include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"

// The primary spatial PhaseSpaceDimension
%template(PhaseSpacePrimarySpatialDimensionTraits) MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>;

// The secondary spatial PhaseSpaceDimension
%template(PhaseSpaceSecondarySpatialDimensionTraits) MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>;

// The tertiary spatial PhaseSpaceDimension
%template(PhaseSpaceTertiarySpatialDimensionTraits) MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>;

// The primary directional PhaseSpaceDimension
%template(PhaseSpacePrimaryDirectionalDimensionTraits) MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>;

// The secondary directional PhaseSpaceDimension
%template(PhaseSpaceSecondaryDirectionalDimensionTraits) MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>;

// The tertiary directional PhaseSpaceDimension
%template(PhaseSpaceTertiaryDirectionalDimensionTraits) MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>;

// The energy PhaseSpaceDimension
%template(PhaseSpaceEnergyDimensionTraits) MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::ENERGY_DIMENSION>;

// The time PhaseSpaceDimension
%template(PhaseSpaceTimeDimensionTraits) MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::TIME_DIMENSION>;

// The weight PhaseSpaceDimension
%template(PhaseSpaceWeightDimensionTraits) MonteCarlo::PhaseSpaceDimensionTraits<MonteCarlo::WEIGHT_DIMENSION>;

// ---------------------------------------------------------------------------//
// Add PhaseSpaceDimensionDistribution support
// ---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::PhaseSpaceDimensionDistribution );

%include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"

//---------------------------------------------------------------------------//
// Helper macro for shared pointers
//---------------------------------------------------------------------------//
%define %shared_ptr_setup_helper( DISTRIBUTION )

  %shared_ptr( MonteCarlo::DISTRIBUTION<MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
  %shared_ptr( MonteCarlo::DISTRIBUTION<MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
  %shared_ptr( MonteCarlo::DISTRIBUTION<MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
  %shared_ptr( MonteCarlo::DISTRIBUTION<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
  %shared_ptr( MonteCarlo::DISTRIBUTION<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
  %shared_ptr( MonteCarlo::DISTRIBUTION<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
  %shared_ptr( MonteCarlo::DISTRIBUTION<MonteCarlo::ENERGY_DIMENSION> );
  %shared_ptr( MonteCarlo::DISTRIBUTION<MonteCarlo::TIME_DIMENSION> );
  %shared_ptr( MonteCarlo::DISTRIBUTION<MonteCarlo::WEIGHT_DIMENSION> );

%enddef

// ---------------------------------------------------------------------------//
// Add IndependentPhaseSpaceDimensionDistribution support
// ---------------------------------------------------------------------------//

%shared_ptr_setup_helper( IndependentPhaseSpaceDimensionDistribution )

%include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"

%independent_phase_space_dimension_setup( Independent )

// ---------------------------------------------------------------------------//
// Add ImportanceSampledIndependentPhaseSpaceDimensionDistribution support
// ---------------------------------------------------------------------------//

%shared_ptr_setup_helper( ImportanceSampledIndependentPhaseSpaceDimensionDistribution )

%include "MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.hpp"

%independent_phase_space_dimension_setup( ImportanceSampledIndependent )

// ---------------------------------------------------------------------------//
// Add DependentPhaseSpaceDimensionDistribution support
// ---------------------------------------------------------------------------//

// The default constructor is protected and needs to be ignored
%ignore MonteCarlo::DependentPhaseSpaceDimensionDistribution::DependentPhaseSpaceDimensionDistribution();

%pre_dependent_phase_space_dimension_setup( Dependent )

%include "MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp"

%basic_dependent_phase_space_dimension_setup( Dependent )


// ---------------------------------------------------------------------------//
// Add ImportanceSampledDependentPhaseSpaceDimensionDistribution support
// ---------------------------------------------------------------------------//

%pre_dependent_phase_space_dimension_setup( ImportanceSampledDependent )

%include "MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution.hpp"

%extend MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution
{
  // Return the phase space dimension
  MonteCarlo::PhaseSpaceDimension getDimension() const
  {
    return $self->getDimension();
  }

  // Return the phase space dimension class
  MonteCarlo::PhaseSpaceDimensionClass getDimensionClass() const
  {
    return $self->getDimensionClass();
  }

  // Return the parent phase space dimension
  MonteCarlo::PhaseSpaceDimension getParentDimension() const
  {
    return $self->getParentDimension();
  }

  // Return the parent phase space dimension class
  MonteCarlo::PhaseSpaceDimensionClass getParentDimensionClass() const
  {
    return $self->getParentDimensionClass();
  }

  // Check if the dimension distribution is independent
  bool isIndependent() const
  {
    return $self->isIndependent();
  }

  // Check if the dimension is dependent on the dimension of interest
  bool isDependentOnDimension(
              const MonteCarlo::PhaseSpaceDimension other_dimension ) const
  {
    return $self->isDependentOnDimension(other_dimension);
  }

  // Check if the dimension distribution is continuous
  bool isContinuous() const
  {
    return $self->isContinuous();
  }

  // Check if the dimension distribution is tabular
  bool isTabular() const
  {
    return $self->isTabular();
  }

  // Check if the dimension distribution is uniform (somewhere)
  bool isUniform() const
  {
    return $self->isUniform();
  }

  // Check if the underlying distribution has the form of interest
  bool hasForm( const Utility::UnivariateDistributionType distribution_type ) const
  {
    return $self->hasForm(distribution_type);
  }

  // Get the distribution type name
  std::string getDistributionTypeName() const
  {
    return $self->getDistributionTypeName();
  }

  // Evaluate the dimension distribution without cascade to dependent dists.
  double evaluateWithoutCascade(
          const MonteCarlo::PhaseSpacePoint& phase_space_point ) const
  {
    return $self->evaluateWithoutCascade(phase_space_point);
  }

  // Set the dimension value (weight appropriately)
  void setDimensionValueAndApplyWeight(
          MonteCarlo::PhaseSpacePoint& phase_space_sample,
          const double dimension_value ) const
  {
    $self->setDimensionValueAndApplyWeight(phase_space_sample, dimension_value);
  }
};

%advanced_dependent_phase_space_dimension_setup( ImportanceSampledDependent, ImportanceSampled )

//---------------------------------------------------------------------------//
// end MonteCarlo.PhaseSpaceDimension.i
//---------------------------------------------------------------------------//
