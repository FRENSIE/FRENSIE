//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo.PhaseSpaceDimension.i
//! \author Luke Kersting
//! \brief  The MonteCarlo.PhaseSpaceDimension sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %monte_carlo_phase_space_docstring
"
PyFrensie.MonteCarlo.PhaseSpaceDimension is the python interface to the FRENSIE
PhaseSpaceDimension definitions in the monte_carlo/active_region subpackage.
"
%enddef

%module(package   = "PyFrensie.MonteCarlo",
        autodoc   = "1",
        docstring = %monte_carlo_phase_space_docstring) PhaseSpaceDimension

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

#include "MonteCarlo_ExplicitTemplateInstantiationMacros.hpp"

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
#include "Utility_CoupledElasticDistribution.hpp"

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
#include "Utility_ContractException.hpp"

using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>
%include <std_string.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Include the serialization helpers for handling macros
%include "Utility_SerializationHelpers.hpp"

// Include the explicit template instantiation helpers
%include "MonteCarlo_ExplicitTemplateInstantiationMacros.hpp"

// Import the UnivariateDistribution handling
%import "Utility.UnivariateDistribution.i"

// Import the BivariateDistribution handling
%import "Utility.BivariateDistribution.i"

// Import the Coordinate handling
%import "Utility.Coordinate.i"

// Include the PhaseSpaceDimension helpers
%include "MonteCarlo_PhaseSpaceDimensionHelpers.i"

// Standard exception handling
%include "exception.i"

// General exception handling
%exception
{
  try{
    $action;
    if( PyErr_Occurred() )
      SWIG_fail;
  }
  catch( Utility::ContractException& e )
  {
    SWIG_exception( SWIG_ValueError, e.what() );
  }
  catch( std::runtime_error& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

// Global swig features
%feature("autodoc", "1");

// ---------------------------------------------------------------------------//
// Add PhaseSpacePoint support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_PhaseSpacePoint.hpp"

// ---------------------------------------------------------------------------//
// Add PhaseSpaceDimension support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_PhaseSpaceDimension.hpp"

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

%include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"

%shared_ptr( MonteCarlo::PhaseSpaceDimensionDistribution );

// ---------------------------------------------------------------------------//
// Add IndependentPhaseSpaceDimensionDistribution support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"

%independent_phase_space_dimension_setup( Independent )

// ---------------------------------------------------------------------------//
// Add ImportanceSampledIndependentPhaseSpaceDimensionDistribution support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.hpp"

%independent_phase_space_dimension_setup( ImportanceSampledIndependent )

// // ---------------------------------------------------------------------------//
// // Add DependentPhaseSpaceDimensionDistribution support
// // ---------------------------------------------------------------------------//

// // The default constructor is protected and needs to be ignored
// %ignore MonteCarlo::DependentPhaseSpaceDimensionDistribution::DependentPhaseSpaceDimensionDistribution();

// %pre_dependent_phase_space_dimension_setup( Dependent )

// %include "MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp"

// // %extend MonteCarlo::DependentPhaseSpaceDimensionDistribution
// // {
// //   DependentPhaseSpaceDimensionDistribution()
// //   { /* ... */ }
// // };

// %basic_dependent_phase_space_dimension_setup( Dependent )


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

// // Add typemaps for converting MaterialIdSet to and from Python set
// %typemap(in) MonteCarlo::PhaseSpacePoint& ( std::set<size_t> temp ){
//   temp = PyFrensie::convertFromPython<std::set<size_t> >( $input );
//   $1 = &temp;
// }

// %typemap(argout) MonteCarlo::PhaseSpacePoint& {
//   %append_output(PyFrensie::convertToPython<std::set<size_t> >( *$1 ) );
// }

// %typemap(out) MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet {
//   return PyFrensie::convertToPython<std::set<size_t> >( $1 );
// }

// %typemap(typecheck, precedence=SWIG_TYPECHECK_SET) (MonteCarlo::MaterialDefinitionDatabase::MaterialIdSet&) {
//   $1 = (PySet_Check($input)) ? 1 : 0;
// }

%advanced_dependent_phase_space_dimension_setup( ImportanceSampledDependent, ImportanceSampled )

//---------------------------------------------------------------------------//
// end MonteCarlo.PhaseSpaceDimension.i
//---------------------------------------------------------------------------//
