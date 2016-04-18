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
#include "Utility_DeltaDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
%}

// Include std::string support
%include <std_string.i>

// Include typemaps support
%include <typemaps.i>

// Include Teuchos::Array support
#define TEUCHOSCORE_LIB_DLL_EXPORT
%include <Teuchos_Array.i>
#undef TEUCHOSCORE_LIB_DLL_EXPORT

// Add typemaps from Teuchos::Array to Teuchos::ArrayView
// %define %teuchos_array_to_arrayview_maps(TYPE)

// %typemap(in) Teuchos::Array<const TYPE>& (Teuchos::ArrayView<const Type> tmp_view )
// {
//   tmp_view = $
// }  
// %enddef 

// Include the distribution helper
%include "Utility_DistributionHelper.i"

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

//---------------------------------------------------------------------------//
// Add support for the OneDDistribution
//---------------------------------------------------------------------------//
// Import the OneDDistribution
%import "Utility_OneDDistribution.hpp"

// Basic distribution interface setup
%basic_distribution_interface_setup( OneDDistribution )

//---------------------------------------------------------------------------//
// Add support for the TabularOneDDistribution
//---------------------------------------------------------------------------//
// Import the TabularOneDDistribution
%import "Utility_TabularOneDDistribution.hpp"

// Basic tabular distribution interface setup
%basic_tab_distribution_interface_setup( TabularOneDDistribution )

//---------------------------------------------------------------------------//
// Add support for the DiscreteDistribution
//---------------------------------------------------------------------------//
// Import the DeltaDistribution
%import "Utility_DeltaDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") 
Utility::UnitAwareDeltaDistribution<void,void>::UnitAwareDeltaDistribution
"The dependent value (multiplier) can be ignored (default value = 1.0)"

// Instantiate the template constructor for double values
%extend Utility::UnitAwareDeltaDistribution<void,void>
{
  %template(DeltaDistribution) Utility::UnitAwareDeltaDistribution::UnitAwareDeltaDistribution<double,double>;
};

// Allow the user to ignore the multiplier in the constructor
%typemap(default) const double multiplier {
  $1 = 1.0;
}

// Standard tabular distribution interface setup
%tab_distribution_interface_setup( DeltaDistribution )

//---------------------------------------------------------------------------//
// Add support for the DiscreteDistribution
//---------------------------------------------------------------------------//
// Import the DiscreteDistribution
%import "Utility_DiscreteDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") 
Utility::UnitAwareDiscreteDistribution<void,void>::UnitAwareDiscreteDistribution
"If the dependent values can also represent the CDF. By default the 
dependent values will not be treated as a CDF. Pass in 'True' as the
3rd argument to force the distribution to treat the dependent values as CDF
values."

// Standard tabular distribution interface setup
%tab_distribution_interface_setup( DiscreteDistribution )

//---------------------------------------------------------------------------//
// Add support for the UniformDistribution
//---------------------------------------------------------------------------//
// Ignore the static methods
%ignore Utility::UnitAwareUniformDistribution<void,void>::sample( const IndepQuantity, const IndepQuantity );
%ignore Utility::UnitAwareUniformDistribution<void,void>::sampleAndRecordTrials( const IndepQuantity, const IndepQuantity, unsigned& );
%ignore Utility::UnitAwareUniformDistribution<void,void>::sampleWithRandomNumber( const IndepQuantity, const IndepQuantity, const double );

// Ignore the copy constructor
%ignore Utility::UnitAwareUniformDistribution<void,void>::UnitAwareUniformDistribution( const Utility::UnitAwareUniformDistribution<void,void>& );

// Import the Uniform Distribution
%import "Utility_UniformDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") Utility::UnitAwareUniformDistribution<void,void>::UnitAwareUniformDistribution
"The dependent value (dependent_value) can be ignored (default value = 1.0)"

// Instantiate the template constructor for double values
%extend Utility::UnitAwareUniformDistribution<void,void>
{
  // Instantiate the desired version of the template constructor
  %template(UniformDistribution) Utility::UnitAwareUniformDistribution::UnitAwareUniformDistribution<double,double>;
};

// Allow the user to ignore the dependent value in the constructor
%typemap(default) const double& dependent_value {
  double default_dependent_value = 1.0;
  $1 = &default_dependent_value;
}

// Standard tabular distribution interface setup
%tab_distribution_interface_setup( UniformDistribution )

//---------------------------------------------------------------------------//
// end Utility_OneDDistribution.i
//---------------------------------------------------------------------------//

