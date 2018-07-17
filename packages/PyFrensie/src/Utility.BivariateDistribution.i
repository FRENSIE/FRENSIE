//---------------------------------------------------------------------------//
//!
//! \file   Utility.BivariateDistribution.i
//! \author Luke Kersting
//! \brief  The BivariateDistribution class interface file
//!
//---------------------------------------------------------------------------//

%define %utility_bivariate_dist_docstring
"
PyFrensie.Utility.BivariateDistribution is the python interface to
the Bivariate distributions in the FRENSIE utility/distribution subpackage.

The purpose of BivariateDistribution is to provide a variety of 1-D
distributions that can be used for both evaluation and sampling. This sub-module
will only be accessed under the Utility.Distribution sub-module.
"
%enddef

%module(package   = "PyFrensie.Utility",
        autodoc   = "1",
        docstring = %utility_bivariate_dist_docstring) BivariateDistribution

%{
#define NO_IMPORT_ARRAY
#include "numpy_include.h"

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
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

#include "Utility_InterpolationPolicy.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_TwoDGridPolicy.hpp"

// Add the Utility namespace to the global lookup scope
using namespace Utility;
%}

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

// Include std::string support
%include <std_string.i>

// Include typemaps support
%include <typemaps.i>

// Include vector support
%include <std_vector.i>

// Include shared pointer support
%include <std_shared_ptr.i>

// Include macros to find initialized numpy
%include "numpy.i"

// Import the distribution traits class
%import "Utility_DistributionTraits.hpp"

// Import the base distribution interface
%import "Utility.Distribution.i"
%import "Utility.UnivariateDistribution.i"

// Include the bivariate distribution helpers
%include "Utility_BivariateDistributionHelpers.i"

// Add a few general typemaps
typedef unsigned int size_t;
%apply unsigned& OUTPUT { unsigned& primary_bin_index };
%apply unsigned& OUTPUT { unsigned& secondary_bin_index };

%template(VectorVectorDouble) std::vector<std::vector<double> >;

// General ignore directives
%ignore *::IndepUnit;
%ignore *::DepUnit;
%ignore *::ThisType;
%ignore *::IndepQuantity;
%ignore *::InverseIndepQuantity;
// %ignore *::DepQuantity;
%ignore *::getDistributionType;
%ignore *::operator=;
%ignore *::toStream;
%ignore *::fromStream;
%ignore *::fromUnitlessDistribution;

//---------------------------------------------------------------------------//
// Add support for the BasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the BasicBivariateDistribution
%import "Utility_BasicBivariateDistribution.hpp"

// Basic distribution interface setup
%basic_bivariate_distribution_interface_setup( BasicBivariateDistribution )

//---------------------------------------------------------------------------//
// Add support for the TabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the TabularBasicBivariateDistribution
%import "Utility_TabularBasicBivariateDistribution.hpp"

%feature("docstring") Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void, Utility::UnitAwareTabularUnivariateDistribution>
"The RENAMED_DISTRIBUTION proxy class. This class can be evaluated and sampled.
Before sampling, make sure to initialize the Frensie Pseudo-Random Number
Generator (PyFrensie.Utility.initFrensiePrng())"

// Basic distribution interface setup
%basic_tab_bivariate_distribution_interface_setup( TabularBasicBivariateDistribution, TabularBasicBivariateDistribution, Utility::UnitAwareTabularUnivariateDistribution )
%basic_tab_bivariate_distribution_interface_setup( TabularBasicBivariateDistribution_Partially, TabularBasicBivariateDistribution, Utility::UnitAwareUnivariateDistribution )


//---------------------------------------------------------------------------//
// Add support for the PartiallyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the PartiallyTabularBasicBivariateDistribution
%import "Utility_PartiallyTabularBasicBivariateDistribution.hpp"

// Standard tabular distribution interface setup
%standard_tab_bivariate_distribution_interface_setup( PartiallyTabularBasicBivariateDistribution )


//---------------------------------------------------------------------------//
// Add support for the FullyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the FullyTabularBasicBivariateDistribution
%import "Utility_FullyTabularBasicBivariateDistribution.hpp"

// Standard tabular distribution interface setup
%standard_tab_bivariate_distribution_interface_setup( FullyTabularBasicBivariateDistribution )


//---------------------------------------------------------------------------//
// Add support for the InterpolatedTabularBasicBivariateDistributionImplBase
//---------------------------------------------------------------------------//
// The Impl Base class is abstract so a constructor is not needed for SWIG
%ignore Utility::UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase::UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase;

// Import the InterpolatedTabularBasicBivariateDistributionImplBase
%import "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"

// There are many interpolated tabular distributions - use this macro to set up each
%define %tabular_bivariate_distribution_base_interface_setup( GRID, INTERP, BASE )

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase< Utility::GRID< Utility::INTERP >,Utility::BASE ## <void,void,void> >
"The InterpolatedTabularBasicBivariateDistributionImplBase class should never be directly instantiated but always used with the InterpolatedFullyTabularBasicBivariateDistribution or the InterpolatedPartiallyTabularBasicBivariateDistribution classes."

%advanced_bivariate_distribution_interface_setup( Interpolated ## BASE ##TabularBasicBivariateDistributionImplBase_ ## INTERP ## _ ## GRID, InterpolatedTabularBasicBivariateDistributionImplBase, Utility::INTERP, Utility::GRID, Utility::UnitAware ## BASE ## TabularBasicBivariateDistribution )

%enddef

// Add LinLinLin grid policies
%tabular_bivariate_distribution_base_interface_setup( Direct, LinLinLin, Fully )
%tabular_bivariate_distribution_base_interface_setup( UnitBase, LinLinLin, Fully )
%tabular_bivariate_distribution_base_interface_setup( Correlated, LinLinLin, Fully )
%tabular_bivariate_distribution_base_interface_setup( UnitBaseCorrelated, LinLinLin, Fully )
%tabular_bivariate_distribution_base_interface_setup( Direct, LinLinLin, Partially )
%tabular_bivariate_distribution_base_interface_setup( UnitBase, LinLinLin, Partially )

// Add LogLogLog grid policies
%tabular_bivariate_distribution_base_interface_setup( Direct, LogLogLog, Fully )
%tabular_bivariate_distribution_base_interface_setup( UnitBase, LogLogLog, Fully )
%tabular_bivariate_distribution_base_interface_setup( Correlated, LogLogLog, Fully )
%tabular_bivariate_distribution_base_interface_setup( UnitBaseCorrelated, LogLogLog, Fully )
%tabular_bivariate_distribution_base_interface_setup( Direct, LogLogLog, Partially )
%tabular_bivariate_distribution_base_interface_setup( UnitBase, LogLogLog, Partially )

// // Add LinLinLog grid policies
// %tabular_bivariate_distribution_base_interface_setup( Direct, LinLinLog, Fully )
// %tabular_bivariate_distribution_base_interface_setup( UnitBase, LinLinLog, Fully )
// %tabular_bivariate_distribution_base_interface_setup( Correlated, LinLinLog, Fully )
// %tabular_bivariate_distribution_base_interface_setup( UnitBaseCorrelated, LinLinLog, Fully )
// %tabular_bivariate_distribution_base_interface_setup( Direct, LinLinLog, Partially )
// %tabular_bivariate_distribution_base_interface_setup( UnitBase, LinLinLog, Partially )

//---------------------------------------------------------------------------//
// Add support for the InterpolatedFullyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//

// Import the InterpolatedFullyTabularBasicBivariateDistribution
%import "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

// There are many interpolated tabular distributions - use this macro to set up each
%define %tabular_bivariate_distribution_interface_setup( GRID, INTERP )

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::GRID<Utility::INTERP>,void,void,void>
"The primary independent values can be stored as a python list or a NumPy array. The secondary independent values and dependent values can be stored as a python list of NumPy array or of a python list. Alternatively, a list of univariate distributions can be used for the secondary distributions."

%advanced_tab_bivariate_distribution_interface_setup( InterpolatedFullyTabularBasicBivariateDistribution_ ## INTERP ## _ ## GRID, InterpolatedFullyTabularBasicBivariateDistribution, TabularUnivariateDistribution, Utility::INTERP, Utility::GRID )

%enddef

// Add LinLinLin grid policies
%tabular_bivariate_distribution_interface_setup( Direct, LinLinLin )
%tabular_bivariate_distribution_interface_setup( UnitBase, LinLinLin )
%tabular_bivariate_distribution_interface_setup( Correlated, LinLinLin )
%tabular_bivariate_distribution_interface_setup( UnitBaseCorrelated, LinLinLin )

// Add LogLogLog grid policies
%tabular_bivariate_distribution_interface_setup( Direct, LogLogLog )
%tabular_bivariate_distribution_interface_setup( UnitBase, LogLogLog )
%tabular_bivariate_distribution_interface_setup( Correlated, LogLogLog )
%tabular_bivariate_distribution_interface_setup( UnitBaseCorrelated, LogLogLog )

// // Add LinLinLog grid policies
// %tabular_bivariate_distribution_interface_setup( Direct, LinLinLog )
// %tabular_bivariate_distribution_interface_setup( UnitBase, LinLinLog )
// %tabular_bivariate_distribution_interface_setup( Correlated, LinLinLog )
// %tabular_bivariate_distribution_interface_setup( UnitBaseCorrelated, LinLinLog )

//---------------------------------------------------------------------------//
// Add support for the InterpolatedPartiallyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the InterpolatedPartiallyTabularBasicBivariateDistribution
%import "Utility_InterpolatedPartiallyTabularBasicBivariateDistribution.hpp"

// There are many interpolated tabular distributions - use this macro to set up each
%define %partially_tabular_bivariate_distribution_interface_setup( GRID, INTERP )

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::GRID<Utility::INTERP>,void,void,void>
"The primary independent values can be stored as a python list or a NumPy array. The secondary distributions can be stored as a python list of univariate distributions."

%advanced_tab_bivariate_distribution_interface_setup( InterpolatedPartiallyTabularBasicBivariateDistribution_ ## INTERP ## _ ## GRID, InterpolatedPartiallyTabularBasicBivariateDistribution, UnivariateDistribution, Utility::INTERP, Utility::GRID )

%enddef

// Add LinLinLin grid policies
%partially_tabular_bivariate_distribution_interface_setup( Direct, LinLinLin )
%partially_tabular_bivariate_distribution_interface_setup( UnitBase, LinLinLin )

// Add LogLogLog grid policies
%partially_tabular_bivariate_distribution_interface_setup( Direct, LogLogLog )
%partially_tabular_bivariate_distribution_interface_setup( UnitBase, LogLogLog )

// // Add LinLinLog grid policies
// %partially_tabular_bivariate_distribution_interface_setup( Direct, LinLinLog )
// %partially_tabular_bivariate_distribution_interface_setup( UnitBase, LinLinLog )

//---------------------------------------------------------------------------//
// Add support for the HistogramTabularBasicBivariateDistributionImplBase
//---------------------------------------------------------------------------//

// The Impl Base class is abstract so a constructor is not needed for SWIG
%ignore Utility::UnitAwareHistogramTabularBasicBivariateDistributionImplBase::UnitAwareHistogramTabularBasicBivariateDistributionImplBase;

// Import the HistogramTabularBasicBivariateDistributionImplBase
%import "Utility_HistogramTabularBasicBivariateDistributionImplBase.hpp"

// There are many interpolated tabular distributions - use this macro to set up each
%define %histogram_bivariate_distribution_base_interface_setup( BASE )

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareHistogramTabularBasicBivariateDistributionImplBase< Utility::BASE ## <void,void,void> >
"The HistogramTabularBasicBivariateDistributionImplBase class should never be directly instantiated but always used with the HistogramFullyTabularBasicBivariateDistribution or the HistogramPartiallyTabularBasicBivariateDistribution classes."

%histogram_bivariate_tab_distribution_base_interface_setup( Histogram ## BASE ## TabularBasicBivariateDistributionImplBase, HistogramTabularBasicBivariateDistributionImplBase, Utility::UnitAware ## BASE ## TabularBasicBivariateDistribution )

%enddef

%histogram_bivariate_distribution_base_interface_setup( Fully )
%histogram_bivariate_distribution_base_interface_setup( Partially )

//---------------------------------------------------------------------------//
// Add support for the HistogramFullyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the HistogramFullyTabularBasicBivariateDistribution
%import "Utility_HistogramFullyTabularBasicBivariateDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareHistogramFullyTabularBasicBivariateDistribution<void,void,void>
"The primary independent values can be stored as a python list or a NumPy array. The secondary distributions can be stored as a python list of univariate distributions."

%advanced_histogram_bivariate_distribution_interface_setup( HistogramFullyTabularBasicBivariateDistribution, HistogramFullyTabularBasicBivariateDistribution, TabularUnivariateDistribution )

//---------------------------------------------------------------------------//
// Add support for the HistogramPartiallyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the HistogramPartiallyTabularBasicBivariateDistribution
%import "Utility_HistogramPartiallyTabularBasicBivariateDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<void,void,void>
"The primary independent values can be stored as a python list or a NumPy array. The secondary distributions can be stored as a python list of univariate distributions."

%advanced_histogram_bivariate_distribution_interface_setup( HistogramPartiallyTabularBasicBivariateDistribution, HistogramPartiallyTabularBasicBivariateDistribution, UnivariateDistribution )

//---------------------------------------------------------------------------//
// end Utility.BivariateDistribution.i
//---------------------------------------------------------------------------//
