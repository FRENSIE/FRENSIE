//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistribution.i
//! \author Alex Robinson
//! \brief  The OneDDistribution class interface file
//!
//---------------------------------------------------------------------------//

%{
#include "Utility_OneDDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
%}

// Include the distribution helper
%include "Utility_DistributionHelper.i"

// Include typemaps support
%include <typemaps.i>

// Add a few general typemaps
%apply unsigned& INOUT { unsigned& trials };
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

// Import the OneDDistribution
%import "Utility_OneDDistribution.hpp"

// Add a few UnitAwareOneDDistribution typemaps
%typemap(in) Utility::UnitAwareOneDDistribution<void,void>::IndepQuantity {
  $1 = PyFloat_AsDouble($input);
}

%typemap(out) Utility::UnitAwareOneDDistribution<void,void>::IndepQuantity {
  $result = PyFloat_FromDouble($1);
}

%typemap(out) Utility::UnitAwareOneDDistribution<void,void>::DepQuantity {
  $result = PyFloat_FromDouble($1);
}

%typemap(out) Utility::UnitAwareOneDDistribution<void,void>::InverseIndepQuantity {
  $result = PyFloat_FromDouble($1);
}

// Instantiate a UnitAwareOneDDistribution
%template(OneDDistribution) Utility::UnitAwareOneDDistribution<void,void>;

// Import the TabularOneDDistribution
%import "Utility_TabularOneDDistribution.hpp"

// Add a few UnitAwareTabularOneDDistribution typemaps
%typemap(in) Utility::UnitAwareTabularOneDDistribution<void,void>::IndepQuantity {
  $1 = PyFloat_AsDouble($input);
}

%typemap(out) Utility::UnitAwareTabularOneDDistribution<void,void>::IndepQuantity {
  $result = PyFloat_FromDouble($1);
}

%typemap(out) Utility::UnitAwareTabularOneDDistribution<void,void>::DepQuantity {
  $result = PyFloat_FromDouble($1);
}

%typemap(out) Utility::UnitAwareTabularOneDDistribution<void,void>::InverseIndepQuantity {
  $result = PyFloat_FromDouble($1);
}

// Instantiate a UnitAwareTabularOneDDistribution
%template(TabularOneDDistribution) Utility::UnitAwareTabularOneDDistribution<void,void>;

// Add support for the UniformDistribution
%ignore Utility::UnitAwareUniformDistribution<void,void>::sample( const IndepQuantity, const IndepQuantity );
%ignore Utility::UnitAwareUniformDistribution<void,void>::sampleAndRecordTrials( const IndepQuantity, const IndepQuantity, unsigned& );
%ignore Utility::UnitAwareUniformDistribution<void,void>::sampleWithRandomNumber( const IndepQuantity, const IndepQuantity, const double );
%import "Utility_UniformDistribution.hpp"

%feature("docstring") Utility::UnitAwareUniformDistribution<void,void>::UnitAwareUniformDistribution
"The dependent value (dependent_value) can be ignored (default value = 1.0)"

%extend Utility::UnitAwareUniformDistribution<void,void>
{
  // Instantiate the desired version of the template constructor
  %template(UniformDistribution) Utility::UnitAwareUniformDistribution::UnitAwareUniformDistribution<double,double>;
};

// Allow the user to ignore the dependent value when creating the dist.
%typemap(default) const double& dependent_value {
  double default_dependent_value = 1.0;
  $1 = &default_dependent_value;
}

%tab_distribution_interface_setup( UniformDistribution )

//---------------------------------------------------------------------------//
// end Utility_OneDDistribution.i
//---------------------------------------------------------------------------//

