//---------------------------------------------------------------------------//
//!
//! \file   Utility.UnivariateDistribution.i
//! \author Alex Robinson, Luke Kersting
//! \brief  The UnivariateDistribution class interface file
//!
//---------------------------------------------------------------------------//

%define %utility_univariate_dist_docstring
"
PyFrensie.Utility.UnivariateDistribution is the python interface to
the Univariate distributions in the FRENSIE utility/distribution subpackage.

The purpose of UnivariateDistribution is to provide a variety of 1-D
distributions that can be used for both evaluation and sampling. This sub-module
will only be accessed under the Utility.Distribution sub-module.
"
%enddef

%module(package   = "PyFrensie.Utility",
        autodoc   = "1",
        docstring = %utility_univariate_dist_docstring) UnivariateDistribution

// Standard exception handling
%include "exception.i"

// Global swig features
%feature("autodoc", "1");

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
  catch( Utility::BadUnivariateDistributionParameter& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

%{
#define NO_IMPORT_ARRAY
#include "numpy_include.h"

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Utility_UnivariateDistributionType.hpp"
#include "Utility_DistributionTraits.hpp"
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
//#include "Utility_CoupledElasticDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"

// Add the Utility namespace to the global lookup scope
using namespace Utility;
%}

// Include typemaps support
%include <typemaps.i>

// General std library handling
%include <std_string.i>
%include <std_vector.i>
%include <std_shared_ptr.i>

// Include macros to find initialized numpy
%include "numpy.i"

// Import the base distribution interface
%import "Utility.Distribution.i"

// Import the distribution traits class
%import "Utility_DistributionTraits.hpp"

// Include the univariate distribution helpers
%include "Utility_UnivariateDistributionHelpers.i"

// Add a few general templates
%template(DoubleVector) std::vector<double>;
%template(VectorPtrTabUni) std::vector<std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<void,void> > >;

// Add a few general typemaps
typedef unsigned int size_t;
%apply Utility::DistributionTraits::Counter& INOUT { Utility::DistributionTraits::Counter& trials };
%apply unsigned& OUTPUT { unsigned& sampled_bin_index };

// General ignore directives
%ignore *::IndepUnit;
%ignore *::DepUnit;
%ignore *::ThisType;
%ignore *::IndepQuantity;
%ignore *::InverseIndepQuantity;
%ignore *::DepQuantity;
%ignore *::getDistributionType;
%ignore *::operator=;
%ignore *::toStream;
%ignore *::fromStream;
%ignore *::fromUnitlessDistribution;

//---------------------------------------------------------------------------//
// Add support for the UnivariateDistributionType
//---------------------------------------------------------------------------//

%include "Utility_UnivariateDistributionType.hpp"

//---------------------------------------------------------------------------//
// Add support for the UnivariateDistribution
//---------------------------------------------------------------------------//
// Import the UnivariateDistribution
%import "Utility_UnivariateDistribution.hpp"

// Basic distribution interface setup
%basic_distribution_interface_setup( UnivariateDistribution )

// // Add functionality to Upcast to the UnivariateDistribution from derived classes
// %inline %{
// std::shared_ptr<const Utility::UnitAwareUnivariateDistribution<void,void> > upcastToUnivariateDistribution(
//   std::shared_ptr<const Utility::UnitAwareUnivariateDistribution<void,void> >& dist )
// {
//   return dist;
// }
// %}

//---------------------------------------------------------------------------//
// Add support for the TabularUnivariateDistribution
//---------------------------------------------------------------------------//
// Import the TabularUnivariateDistribution
%import "Utility_TabularUnivariateDistribution.hpp"

// Basic tabular distribution interface setup
%basic_tab_distribution_interface_setup( TabularUnivariateDistribution )

// // Add functionality to Upcast to the TabularUnivariateDistribution from derived classes
// %inline %{
// std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<void,void> > upcastToTabularUnivariateDistribution(
//   std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<void,void> >& tab_dist )
// {
//   return tab_dist;
// }
// %}

//---------------------------------------------------------------------------//
// Add support for the DeltaDistribution
//---------------------------------------------------------------------------//
// Import the DeltaDistribution
%import "Utility_DeltaDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareDeltaDistribution<void,void>::UnitAwareDeltaDistribution
"The dependent value (multiplier) can be ignored (default value = 1.0)"

// Instantiate the template constructor for double values
%extend Utility::UnitAwareDeltaDistribution
{
  %template(DeltaDistribution) Utility::UnitAwareDeltaDistribution::UnitAwareDeltaDistribution<double,double>;
};


// Allow the user to ignore the multiplier in the constructor
%typemap(default) const double multiplier {
  $1 = 1.0;
}

// Standard tabular distribution interface setup
%standard_tab_distribution_interface_setup( DeltaDistribution )

//---------------------------------------------------------------------------//
// Add support for the DiscreteDistribution
//---------------------------------------------------------------------------//
// Import the DiscreteDistribution
%import "Utility_DiscreteDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareDiscreteDistribution<void,void>::UnitAwareDiscreteDistribution
"The independent values and dependent values should be stored in a NumPy array.
The dependent values can represent the CDF instead of the distribution (pass in
'True' as the 3rd argument)."

// Standard tabular distribution interface setup
%standard_tab_distribution_interface_setup( DiscreteDistribution )

//---------------------------------------------------------------------------//
// Add support for the EquiprobableBinDistribution
//---------------------------------------------------------------------------//
// Import the Equiprobable Bin Distribution
%import "Utility_EquiprobableBinDistribution.hpp"

// Standard tabular distribution interface setup
%standard_tab_distribution_interface_setup( EquiprobableBinDistribution )

//---------------------------------------------------------------------------//
// Add support for the EvaporationDistribution
//---------------------------------------------------------------------------//
// Ignore the static methods
%ignore Utility::UnitAwareEvaporationDistribution<void,void>::sample( const IndepQuantity, const IndepQuantity, const IndepQuantity );
%ignore Utility::UnitAwareEvaporationDistribution<void,void>::sampleAndRecordTrials( const IndepQuantity, const IndepQuantity, const IndepQuantity, DistributionTraits::Counter& );

// Import the Evaporation Distribution
%import "Utility_EvaporationDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") Utility::UnitAwareEvaporationDistribution<void,void>::UnitAwareEvaporationDistribution
"All of the input parameters can be ignored. The defaults values for each
input parameter are the following:

  incident_energy = 1.0 (MeV)
  nuclear_temperature = 1.0 (MeV)
  restriction_energy = 0.0 (MeV)
  constant_multiplier = 1.0."

// Instantiate the template constructor for double values
%extend Utility::UnitAwareEvaporationDistribution
{
  // Instantiate the desired version of the template constructor
  %template(EvaporationDistribution) Utility::UnitAwareEvaporationDistribution::UnitAwareEvaporationDistribution<double,double,double>;
};

// Standard distribution interface setup
%standard_distribution_interface_setup( EvaporationDistribution )

//---------------------------------------------------------------------------//
// Add support for the ExponentialDistribution
//---------------------------------------------------------------------------//
// Ignore the static methods
%ignore Utility::UnitAwareExponentialDistribution<void,void>::sample( const InverseIndepQuantity );
%ignore Utility::UnitAwareExponentialDistribution<void,void>::sample( const InverseIndepQuantity, const IndepQuantity, const IndepQuantity );

// Import the Exponential Distribution
%import "Utility_ExponentialDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") Utility::UnitAwareExponentialDistribution<void,void>::UnitAwareExponentialDistribution
"The lower limit and/or the upper limit can be ignored (default values are 0.0
and inf)"

// Instantiate the template constructor for double values
%extend Utility::UnitAwareExponentialDistribution
{
  // Instantiate the desired version of the template constructor
  %template(ExponentialDistribution) Utility::UnitAwareExponentialDistribution::UnitAwareExponentialDistribution<double,double,double>;
};

// Standard distribution interface setup
%standard_distribution_interface_setup( ExponentialDistribution )

//---------------------------------------------------------------------------//
// Add support for the HistogramDistribution
//---------------------------------------------------------------------------//
// Import the HistogramDistribution
%import "Utility_HistogramDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareHistogramDistribution<void,void>::UnitAwareHistogramDistribution
"The bin boundaries and bin values should be stored in a NumPy array.
The bin values can represent the CDF instead of the distribution (pass in
'True' as the 3rd argument)."

// Standard tabular distribution interface setup
%standard_tab_distribution_interface_setup( HistogramDistribution )

//---------------------------------------------------------------------------//
// Add support for the Maxwell fission distribution
//---------------------------------------------------------------------------//
// Ignore the static methods
%ignore Utility::UnitAwareMaxwellFissionDistribution<void,void>::sample( const IndepQuantity, const IndepQuantity, const IndepQuantity );
%ignore Utility::UnitAwareMaxwellFissionDistribution<void,void>::sampleAndRecordTrials( const IndepQuantity, const IndepQuantity, const IndepQuantity, DistributionTraits::Counter& );

// Import the MaxwellFission Distribution
%import "Utility_MaxwellFissionDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") Utility::UnitAwareMaxwellFissionDistribution<void,void>::UnitAwareMaxwellFissionDistribution
"All of the input parameters can be ignored. The defaults values for each
input parameter are the following:

  incident_energy = 1.0 (MeV)
  nuclear_temperature = 1.0 (MeV)
  restriction_energy = 0.0 (MeV)
  constant_multiplier = 1.0."

// Instantiate the template constructor for double values
%extend Utility::UnitAwareMaxwellFissionDistribution
{
  // Instantiate the desired version of the template constructor
  %template(MaxwellFissionDistribution) Utility::UnitAwareMaxwellFissionDistribution::UnitAwareMaxwellFissionDistribution<double,double,double>;
};

// Standard distribution interface setup
%standard_distribution_interface_setup( MaxwellFissionDistribution )

//---------------------------------------------------------------------------//
// Add support for the Normal distribution
//---------------------------------------------------------------------------//
// Ignore the static methods
%ignore Utility::UnitAwareNormalDistribution<void,void>::sample( const IndepQuantity, const IndepQuantity, const IndepQuantity, const IndepQuantity );
%ignore Utility::UnitAwareNormalDistribution<void,void>::sampleAndRecordTrials(  DistributionTraits::Counter&, const IndepQuantity, const IndepQuantity, const IndepQuantity, const IndepQuantity );

// Import the Normal Distribution
%import "Utility_NormalDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") Utility::UnitAwareNormalDistribution<void,void>::UnitAwareNormalDistribution
"All of the input parameters can be ignored. The defaults values for each
input parameter are the following:

  mean = 0.0,
  standard_deviation = 1.0,
  constant_multiplier = 1.0,
  min_independent_value = -inf,
  max_independent_value = inf."

// Instantiate the template constructor for double values
%extend Utility::UnitAwareNormalDistribution
{
  // Instantiate the desired version of the template constructor
  %template(NormalDistribution) Utility::UnitAwareNormalDistribution::UnitAwareNormalDistribution<double,double,double,double>;
};

// Standard distribution interface setup
%standard_distribution_interface_setup( NormalDistribution )

//---------------------------------------------------------------------------//
// Add support for the PolynomialDistribution
//---------------------------------------------------------------------------//
// Import the Polynomial Distribution
%import "Utility_PolynomialDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwarePolynomialDistribution<void,void>::UnitAwarePolynomialDistribution
"The coefficients should be stored in a NumPy array."

// Instantiate the template constructor for double values
%extend Utility::UnitAwarePolynomialDistribution
{
  // Instantiate the desired version of the template constructor
  %template(PolynomialDistribution) Utility::UnitAwarePolynomialDistribution::UnitAwarePolynomialDistribution<double>;
};

// Standard distribution interface setup
%standard_distribution_interface_setup( PolynomialDistribution )

//---------------------------------------------------------------------------//
// Add support for the PowerDistribution
//---------------------------------------------------------------------------//
// Import the Power Distribution
%import "Utility_PowerDistribution.hpp"

// There are many power distributions - use this macro to set up each
%define %power_distribution_interface_setup( POWER )
// Ignore the static methods
%ignore Utility::UnitAwarePowerDistribution<POWER,void,void>::sample( const IndepQuantity, const IndepQuantity );

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwarePowerDistribution<POWER,void,void>::UnitAwarePowerDistribution
"The constant multiplier can be ignored (default value = 1.0)"

// Allow the user to ignore the constant multiplier in the constructor
%extend Utility::UnitAwarePowerDistribution<POWER,void,void>
{
  // Constructor
  UnitAwarePowerDistribution()
  {
    return new Utility::UnitAwarePowerDistribution<POWER,void,void>(
                                                               1.0, 0.0, 1.0 );
  }

  // Constructor
  UnitAwarePowerDistribution( const double min_indep_limit,
                              const double max_indep_limit )
  {
    return new Utility::UnitAwarePowerDistribution<POWER,void,void>(
                                                             1.0,
                                                             min_indep_limit,
                                                             max_indep_limit );
  }

  // Constructor (mimics the constructor in Utility_PowerDistribution.hpp -
  // see comment below)
  UnitAwarePowerDistribution( const double constant_multiplier,
                              const double min_indep_limit,
                              const double max_indep_limit )
  {
    return new Utility::UnitAwarePowerDistribution<POWER,void,void>(
                                                           constant_multiplier,
                                                           min_indep_limit,
                                                           max_indep_limit );
  }

  // Unfortunately, we cannot instantiate the constructor because swig will
  // not create the constructors correctly (currently)
  //%template(PowerDistribution_ ## POWER) Utility::UnitAwarePowerDistribution::UnitAwarePowerDistribution<double>;
};

// Standard distribution interface setup
%advanced_distribution_interface_setup( PowerDistribution_ ## POWER , PowerDistribution, POWER )

%enddef

%power_distribution_interface_setup( 1 )
%power_distribution_interface_setup( 2 )

//---------------------------------------------------------------------------//
// Add support for the TabularDistribution
//---------------------------------------------------------------------------//

// Import the Tabular Distribution
%import "Utility_TabularDistribution.hpp"

// There are many tabular distributions - use this macro to set up each
%define %tabular_distribution_interface_setup( INTERP )

// Ignore the static methods
%ignore Utility::UnitAwareTabularDistribution<Utility::INTERP,void,void>::typeName( const bool verbose_name, const bool use_template_params = false, const std::string& delim = std::string() );

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareTabularDistribution<Utility::INTERP,void,void>::UnitAwareTabularDistribution
"The independent values and dependent values should be stored in a NumPy array.
"

%advanced_tab_distribution_interface_setup( TabularDistribution_ ## INTERP, TabularDistribution, Utility::INTERP )

%enddef

%tabular_distribution_interface_setup( LinLin )
%tabular_distribution_interface_setup( LinLog )
%tabular_distribution_interface_setup( LogLin )
%tabular_distribution_interface_setup( LogLog )

//---------------------------------------------------------------------------//
// Add support for the TabularCDFDistribution
//---------------------------------------------------------------------------//
// Import the Tabular CDF Distribution
%import "Utility_TabularCDFDistribution.hpp"

// There are many tabular cdf distributions - use this macro to set up each
%define %tabular_cdf_distribution_interface_setup( INTERP )

// Ignore the static methods
%ignore Utility::UnitAwareTabularCDFDistribution<Utility::INTERP,void,void>::typeName( const bool verbose_name, const bool use_template_params = false, const std::string& delim = std::string() );

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareTabularCDFDistribution<Utility::INTERP,void,void>::UnitAwareTabularCDFDistribution
"The independent values and dependent values should be stored in a NumPy array.
"

%advanced_tab_distribution_interface_setup( TabularCDFDistribution_ ## INTERP, TabularCDFDistribution, Utility::INTERP )

%enddef

%tabular_cdf_distribution_interface_setup( LinLin )
%tabular_cdf_distribution_interface_setup( LinLog )
%tabular_cdf_distribution_interface_setup( LogLin )
%tabular_cdf_distribution_interface_setup( LogLog )

//---------------------------------------------------------------------------//
// Add support for the UniformDistribution
//---------------------------------------------------------------------------//
// Ignore the static methods
%ignore Utility::UnitAwareUniformDistribution<void,void>::sample( const IndepQuantity, const IndepQuantity );
%ignore Utility::UnitAwareUniformDistribution<void,void>::sampleAndRecordTrials( const IndepQuantity, const IndepQuantity, DistributionTraits::Counter& );
%ignore Utility::UnitAwareUniformDistribution<void,void>::sampleWithRandomNumber( const IndepQuantity, const IndepQuantity, const double );

// Import the Uniform Distribution
%import "Utility_UniformDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") Utility::UnitAwareUniformDistribution<void,void>::UnitAwareUniformDistribution
"The dependent value (dependent_value) can be ignored (default value = 1.0)"

// Instantiate the template constructor for double values
%extend Utility::UnitAwareUniformDistribution
{
  // Instantiate the desired version of the template constructor
  %template(UniformDistribution) Utility::UnitAwareUniformDistribution::UnitAwareUniformDistribution<double,double>;
};

// Allow the user to ignore the dependent value in the constructor
%typemap(default) const double& dependent_value (double default_dependent_value){
  default_dependent_value = 1.0;
  $1 = &default_dependent_value;
}

// Standard tabular distribution interface setup
%standard_tab_distribution_interface_setup( UniformDistribution )

//---------------------------------------------------------------------------//
// Add support for the WattDistribution
//---------------------------------------------------------------------------//
// Ignore the static methods
%ignore Utility::UnitAwareWattDistribution<void,void>::sample( const IndepQuantity, const IndepQuantity, const InverseIndepQuantity, const IndepQuantity );
%ignore Utility::UnitAwareWattDistribution<void,void>::sampleAndRecordTrials( const IndepQuantity, const IndepQuantity, const InverseIndepQuantity, const IndepQuantity, DistributionTraits::Counter& );

// Import the Watt Distribution
%import "Utility_WattDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") Utility::UnitAwareWattDistribution<void,void>::UnitAwareWattDistribution
"All of the input parameters can be ignored. The defaults values for each
input parameter are the following:

  incident_energy = 1.0 (MeV)
  a_parameter = 1.0 (MeV)
  b_parameter = 1.0 (MeV^-1)
  restriction_energy = 0.0 (MeV)
  constant_multiplier = 1.0."

// Instantiate the template constructor for double values
%extend Utility::UnitAwareWattDistribution
{
  // Instantiate the desired version of the template constructor
  %template(WattDistribution) Utility::UnitAwareWattDistribution::UnitAwareWattDistribution<double,double,double,double>;
};

// Standard distribution interface setup
%standard_distribution_interface_setup( WattDistribution )

//---------------------------------------------------------------------------//
// Add support for the CoupledElasticDistribution
//---------------------------------------------------------------------------//
// Import the Coupled Elastic UnivariateDistribution
// %import "Utility_CoupledElasticDistribution.hpp"

// // There are many Coupled Elastic One D distributions - use this macro to set up each
// %define %coupled_elastic_distribution_interface_setup( INTERP )

// // Add a more detailed docstring for the constructor
// %feature("docstring")
// Utility::UnitAwareCoupledElasticDistribution<Utility::INTERP,void,void>::UnitAwareCoupledElasticDistribution
// "The independent values and dependent values should be stored in a NumPy array.
// "

// %advanced_tab_distribution_interface_setup( CoupledElasticDistribution_ ## INTERP, CoupledElasticDistribution, Utility::INTERP )

// %enddef

// %coupled_elastic_distribution_interface_setup( LinLin )
// %coupled_elastic_distribution_interface_setup( LinLog )

//---------------------------------------------------------------------------//
// end Utility.UnivariateDistribution.i
//---------------------------------------------------------------------------//
