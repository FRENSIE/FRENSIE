//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistribution.i
//! \author Alex Robinson
//! \brief  The OneDDistribution class interface file
//!
//---------------------------------------------------------------------------//

%{
// Trilinos Includes
#include <PyTrilinos_Teuchos_Util.h>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_EquiprobableBinDistribution.hpp"
#include "Utility_EvaporationDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_MaxwellFissionDistribution.hpp"
#include "Utility_NormalDistribution.hpp"
#include "Utility_PolynomialDistribution.hpp"
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

// Import the PyTrilinos utilities
%import <PyTrilinos_Teuchos_Util.h>

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
// Add support for the DeltaDistribution
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
// Ignore the extra constructors
%ignore Utility::UnitAwareDiscreteDistribution<void,void>::UnitAwareDiscreteDistribution( const Teuchos::Array<double>&, const Teuchos::Array<double>&, const bool );
%ignore Utility::UnitAwareDiscreteDistribution<void,void>::UnitAwareDiscreteDistribution( const Teuchos::Array<double>&, const Teuchos::Array<double>& );

// Import the DiscreteDistribution
%import "Utility_DiscreteDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") 
Utility::UnitAwareDiscreteDistribution<void,void>::UnitAwareDiscreteDistribution
"The independent values and dependent values should be stored in a NumPy array.
The dependent values can represent the CDF instead of the distribution (pass in
'True' as the 3rd argument)."

// Allow the user to use NumPy arrays in the constructor
%extend Utility::UnitAwareDiscreteDistribution<void,void>
{
  // Constructor
  UnitAwareDiscreteDistribution( PyObject* independent_py_array,
                                 PyObject* dependent_py_array,
                                 const bool interpret_dependent_values_as_cdf )
  {
    Teuchos::Array<double> independent_values;
    
    PyTrilinos::CopyNumPyToTeuchos( independent_py_array, independent_values );

    Teuchos::Array<double> dependent_values;

    PyTrilinos::CopyNumPyToTeuchos( dependent_py_array, dependent_values );

    return new Utility::UnitAwareDiscreteDistribution<void,void>( 
                                           independent_values, 
                                           dependent_values,
                                           interpret_dependent_values_as_cdf );
  }

  // Constructor
  UnitAwareDiscreteDistribution( PyObject* independent_py_array,
                                 PyObject* dependent_py_array )
  {
    Teuchos::Array<double> independent_values;
    
    PyTrilinos::CopyNumPyToTeuchos( independent_py_array, independent_values );

    Teuchos::Array<double> dependent_values;

    PyTrilinos::CopyNumPyToTeuchos( dependent_py_array, dependent_values );

    return new Utility::UnitAwareDiscreteDistribution<void,void>( 
                                                            independent_values,
                                                            dependent_values,
                                                            false );
  }
};

// Standard tabular distribution interface setup
%tab_distribution_interface_setup( DiscreteDistribution )

//---------------------------------------------------------------------------//
// Add support for the EquiprobableBinDistribution
//---------------------------------------------------------------------------//
// Import the Equiprobable Bin Distribution
%import "Utility_EquiprobableBinDistribution.hpp"

// Allow the user to use NumPy arrays in the constructor
%extend Utility::UnitAwareEquiprobableBinDistribution<void,void>
{
  // Constructor
  UnitAwareEquiprobableBinDistribution( PyObject* py_array_bin_boundaries )
  {
    Teuchos::Array<double> bin_boundaries;
    
    PyTrilinos::CopyNumPyToTeuchos( py_array_bin_boundaries, bin_boundaries );
    
    return new Utility::UnitAwareEquiprobableBinDistribution<void,void>( 
                                                              bin_boundaries );
  }
};

// Standard tabular distribution interface setup
%tab_distribution_interface_setup( EquiprobableBinDistribution )

//---------------------------------------------------------------------------//
// Add support for the EvaporationDistribution
//---------------------------------------------------------------------------//
// Ignore the static methods
%ignore Utility::UnitAwareEvaporationDistribution<void,void>::sample( const IndepQuantity, const IndepQuantity, const IndepQuantity );
%ignore Utility::UnitAwareEvaporationDistribution<void,void>::sampleAndRecordTrials( const IndepQuantity, const IndepQuantity, const IndepQuantity, unsigned& );

// Import the Evaporation Distribution
%import "Utility_EvaporationDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") Utility::UnitAwareEvaporationDistribution<void,void>::UnitAwareEvaporationDistribution
"All of the input parameters can be ignored. The defaults values for each 
input parameter are the following:

  incident_energy = 1.0 (MeV)
  nuclear_temperature = 1.0 (MeV)
  restruction_energy = 0.0 (MeV)
  constant_multiplier = 1.0."

// Instantiate the template constructor for double values
%extend Utility::UnitAwareEvaporationDistribution<void,void>
{
  // Instantiate the desired version of the template constructor
  %template(EvaporationDistribution) Utility::UnitAwareEvaporationDistribution::UnitAwareEvaporationDistribution<double,double,double>;
};

// Standard distribution interface setup
%distribution_interface_setup( EvaporationDistribution )

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
%extend Utility::UnitAwareExponentialDistribution<void,void>
{
  // Instantiate the desired version of the template constructor
  %template(ExponentialDistribution) Utility::UnitAwareExponentialDistribution::UnitAwareExponentialDistribution<double,double,double>;
};

// Standard distribution interface setup
%distribution_interface_setup( ExponentialDistribution )

//---------------------------------------------------------------------------//
// Add support for the HistogramDistribution
//---------------------------------------------------------------------------//
// Ignore the extra constructors
%ignore Utility::UnitAwareHistogramDistribution<void,void>::UnitAwareHistogramDistribution( const Teuchos::Array<double>&, const Teuchos::Array<double>&, const bool );
%ignore Utility::UnitAwareHistogramDistribution<void,void>::UnitAwareHistogramDistribution( const Teuchos::Array<double>&, const Teuchos::Array<double>& );

// Import the HistogramDistribution
%import "Utility_HistogramDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") 
Utility::UnitAwareHistogramDistribution<void,void>::UnitAwareHistogramDistribution
"The bin boundaries and bin values should be stored in a NumPy array.
The bin values can represent the CDF instead of the distribution (pass in
'True' as the 3rd argument)."

// Allow the user to use NumPy arrays in the constructor
%extend Utility::UnitAwareHistogramDistribution<void,void>
{
  // Constructor
  UnitAwareHistogramDistribution(PyObject* bin_boundaries_py_array,
                                 PyObject* bin_values_py_array,
                                 const bool interpret_dependent_values_as_cdf )
  {
    Teuchos::Array<double> bin_boundaries;
    
    PyTrilinos::CopyNumPyToTeuchos( bin_boundaries_py_array, 
                                    bin_boundaries );

    Teuchos::Array<double> bin_values;

    PyTrilinos::CopyNumPyToTeuchos( bin_values_py_array, bin_values );

    return new Utility::UnitAwareHistogramDistribution<void,void>( 
                                           bin_boundaries, 
                                           bin_values,
                                           interpret_dependent_values_as_cdf );
  }

  // Constructor
  UnitAwareHistogramDistribution( PyObject* bin_boundaries_py_array,
                                  PyObject* bin_values_py_array )
  {
    Teuchos::Array<double> bin_boundaries;
    
    PyTrilinos::CopyNumPyToTeuchos( bin_boundaries_py_array, 
                                    bin_boundaries );

    Teuchos::Array<double> bin_values;

    PyTrilinos::CopyNumPyToTeuchos( bin_values_py_array, 
                                    bin_values );

    return new Utility::UnitAwareHistogramDistribution<void,void>( 
                                                                bin_boundaries,
                                                                bin_values,
                                                                false );
  }
};

// Standard tabular distribution interface setup
%tab_distribution_interface_setup( HistogramDistribution )

//---------------------------------------------------------------------------//
// Add support for the Maxwell fission distribution
//---------------------------------------------------------------------------//
// Ignore the static methods
%ignore Utility::UnitAwareMaxwellFissionDistribution<void,void>::sample( const IndepQuantity, const IndepQuantity, const IndepQuantity );
%ignore Utility::UnitAwareMaxwellFissionDistribution<void,void>::sampleAndRecordTrials( const IndepQuantity, const IndepQuantity, const IndepQuantity, unsigned& );

// Import the MaxwellFission Distribution
%import "Utility_MaxwellFissionDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") Utility::UnitAwareMaxwellFissionDistribution<void,void>::UnitAwareMaxwellFissionDistribution
"All of the input parameters can be ignored. The defaults values for each 
input parameter are the following:

  incident_energy = 1.0 (MeV)
  nuclear_temperature = 1.0 (MeV)
  restruction_energy = 0.0 (MeV)
  constant_multiplier = 1.0."

// Instantiate the template constructor for double values
%extend Utility::UnitAwareMaxwellFissionDistribution<void,void>
{
  // Instantiate the desired version of the template constructor
  %template(MaxwellFissionDistribution) Utility::UnitAwareMaxwellFissionDistribution::UnitAwareMaxwellFissionDistribution<double,double,double>;
};

// Standard distribution interface setup
%distribution_interface_setup( MaxwellFissionDistribution )

//---------------------------------------------------------------------------//
// Add support for the Normal distribution
//---------------------------------------------------------------------------//
// Ignore the static methods
%ignore Utility::UnitAwareNormalDistribution<void,void>::sample( const IndepQuantity, const IndepQuantity, const IndepQuantity, const IndepQuantity );
%ignore Utility::UnitAwareNormalDistribution<void,void>::sampleAndRecordTrials(  unsigned&, const IndepQuantity, const IndepQuantity, const IndepQuantity, const IndepQuantity );

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
%extend Utility::UnitAwareNormalDistribution<void,void>
{
  // Instantiate the desired version of the template constructor
  %template(NormalDistribution) Utility::UnitAwareNormalDistribution::UnitAwareNormalDistribution<double,double,double,double>;
};

// Standard distribution interface setup
%distribution_interface_setup( NormalDistribution )

//---------------------------------------------------------------------------//
// Add support for the PolynomialDistribution
//---------------------------------------------------------------------------//
// Import the Polynomial Distribution
%import "Utility_PolynomialDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring") 
Utility::UnitAwarePolynomialDistribution<void,void>::UnitAwarePolynomialDistribution
"The coefficients should be stored in a NumPy array."

// Allow the user to use NumPy arrays in the constructor
%extend Utility::UnitAwarePolynomialDistribution<void,void>
{
  // Constructor
  UnitAwarePolynomialDistribution( PyObject* py_array_coefficients,
                                   const double min_indep_limit,
                                   const double max_indep_limit )
  {
    Teuchos::Array<double> coefficients;
    
    PyTrilinos::CopyNumPyToTeuchos( py_array_coefficients, coefficients );
    
    return new Utility::UnitAwarePolynomialDistribution<void,void>( 
                                                             coefficients,
                                                             min_indep_limit,
                                                             max_indep_limit );
  }
};

// Standard distribution interface setup
%distribution_interface_setup( PolynomialDistribution )

//---------------------------------------------------------------------------//
// Add support for the UniformDistribution
//---------------------------------------------------------------------------//
// Ignore the static methods
%ignore Utility::UnitAwareUniformDistribution<void,void>::sample( const IndepQuantity, const IndepQuantity );
%ignore Utility::UnitAwareUniformDistribution<void,void>::sampleAndRecordTrials( const IndepQuantity, const IndepQuantity, unsigned& );
%ignore Utility::UnitAwareUniformDistribution<void,void>::sampleWithRandomNumber( const IndepQuantity, const IndepQuantity, const double );

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

