//---------------------------------------------------------------------------//
//!
//! \file   Utility_BivariateDistribution.i
//! \author Luke Kersting
//! \brief  The BivariateDistribution class interface file
//!
//---------------------------------------------------------------------------//

%{
#define NO_IMPORT_ARRAY
#include "numpy_include.h"

// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_DistributionSerializationHelpers.hpp"
#include "Utility_DistributionTraits.hpp"
#include "Utility_BasicBivariateDistribution.hpp"
#include "Utility_BivariateDistribution.hpp"
// #include "Utility_SeparableBivariateDistribution.hpp"
#include "Utility_TabularBasicBivariateDistribution.hpp"
#include "Utility_FullyTabularBasicBivariateDistribution.hpp"
#include "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_TwoDGridPolicy.hpp"

// Add the Utility namespace to the global lookup scope
using namespace Utility;
%}

// Include std::string support
%include <std_string.i>

// Include typemaps support
%include <typemaps.i>

// Include macros to find initialized numpy
%include "numpy.i"

// Include the distribution serialization helpers
%include "Utility_SerializationHelpers.hpp"
%include "Utility_DistributionSerializationHelpers.hpp"

// Import the explicit template instantiation helpers
%import "Utility_ExplicitTemplateInstantiationMacros.hpp"

// Import the distribution traits class
%import "Utility_DistributionTraits.hpp"

// Include the univariate distribution
%include "Utility_UnivariateDistribution.i"

// Include the bivariate distribution helpers
%include "Utility_BivariateDistributionHelpers.i"

// Add a few general typemaps
typedef unsigned int size_t;
%apply Utility::DistributionTraits::Counter& INOUT { Utility::DistributionTraits::Counter& trials };
%apply unsigned& OUTPUT { unsigned& primary_bin_index };
%apply unsigned& OUTPUT { unsigned& secondary_bin_index };

%typemap(in) const std::vector<double>& (std::vector<double> temp)
{
  temp = PyFrensie::convertFromPython<std::vector<double> >( $input );

  $1 = &temp;
}

%typemap(in) const std::vector<std::vector<double> >& (std::vector<std::vector<double> > temp)
{
  temp = PyFrensie::convertFromPython<std::vector<std::vector<double> > >( $input );

  $1 = &temp;
}

// The typecheck precedence, which is used by SWIG to determine which
// overloaded method should be called, should be set to
// SWIG_TYPECHECK_DOUBLE_ARRAY (1050) for the std::vector<double>&. You will
// get a Python error when calling the overloaded method in Python without this
// typecheck
%typemap(typecheck, precedence=1050) (const std::vector<double>&) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

// The typecheck precedence, which is used by SWIG to determine which
// overloaded method should be called, should be set to
// SWIG_TYPECHECK_DOUBLE_ARRAY (1050) for the std::vector<std::vector<double> >&. You will
// get a Python error when calling the overloaded method in Python without this
// typecheck
%typemap(typecheck, precedence=1050) (const std::vector<std::vector<double> >&) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

// General ignore directives
%ignore *::PrimaryIndepUnit;
%ignore *::SecondaryIndepUnit;
%ignore *::DepUnit;
%ignore *::ThisType;
%ignore *::PrimaryIndepQuantity;
%ignore *::SecondaryIndepQuantity;
%ignore *::InverseSecondaryIndepQuantity;
%ignore *::DepQuantity;
%ignore *::operator=;
%ignore *::toStream;
%ignore *::fromStream;

//---------------------------------------------------------------------------//
// Add support for the BasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the BasicBivariateDistribution
%import "Utility_BasicBivariateDistribution.hpp"

// Basic distribution interface setup
%basic_bivariate_distribution_interface_setup( BasicBivariateDistribution )

//---------------------------------------------------------------------------//
// Add support for the BivariateDistribution
//---------------------------------------------------------------------------//
// Import the BivariateDistribution
%import "Utility_BivariateDistribution.hpp"

// Basic distribution interface setup
%basic_bivariate_distribution_interface_setup( BivariateDistribution )

// //---------------------------------------------------------------------------//
// // Add support for the TabularBasicBivariateDistribution
// //---------------------------------------------------------------------------//
// // Import the TabularBasicBivariateDistribution
// %import "Utility_TabularBasicBivariateDistribution.hpp"

// // Basic distribution interface setup
// %basic_bivariate_distribution_interface_setup( TabularBasicBivariateDistribution )

//---------------------------------------------------------------------------//
// Add support for the FullyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the FullyTabularBasicBivariateDistribution
%import "Utility_FullyTabularBasicBivariateDistribution.hpp"

// Basic distribution interface setup
%basic_tab_bivariate_distribution_interface_setup( FullyTabularBasicBivariateDistribution )

// //---------------------------------------------------------------------------//
// // Add support for the InterpolatedTabularBasicBivariateDistributionImplBase
// //---------------------------------------------------------------------------//
// // Import the InterpolatedTabularBasicBivariateDistributionImplBase
// %import "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"

// // There are many interpolated tabular distributions - use this macro to set up each
// %define %tabular_bivariate_distribution_base_interface_setup( GRID, INTERP, BASE )

// // Add a more detailed docstring for the constructor
// %feature("docstring")
// Utility::UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase< Utility::GRID< Utility::INTERP >,UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> >
// "The primary independent values should be stored in a NumPy array. The secondary independent values and dependent values should be stored in a list of NumPy arrays.
// "

// %advanced_bivariate_distribution_interface_setup( InterpolatedTabularBasicBivariateDistributionImplBase_ ## INTERP ## _ ## GRID, InterpolatedTabularBasicBivariateDistributionImplBase, Utility::INTERP, Utility::GRID, Utility::BASE )

// %enddef

// // Basic distribution interface setup
// %tabular_bivariate_distribution_base_interface_setup( UnitBase, LinLinLin, UnitAwareFullyTabularBasicBivariateDistribution )

//---------------------------------------------------------------------------//
// Add support for the InterpolatedFullyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the InterpolatedFullyTabularBasicBivariateDistribution
%include "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"
%import "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

// There are many interpolated tabular distributions - use this macro to set up each
%define %tabular_bivariate_distribution_interface_setup( GRID, INTERP )

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::GRID<Utility::INTERP>,void,void,void>::InterpolatedFullyTabularBasicBivariateDistribution
"The primary independent values should be stored in a NumPy array. The secondary independent values and dependent values should be stored in a list of NumPy array.
"

// Typemaps for constructor data input arrays
%typemap(in) const std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity > > & (std::vector<double> temp)
{
  temp = PyFrensie::convertFromPython<std::vector<double> >( $input );

  $1 = &temp;
}

%typemap(typecheck, precedence=1050) (const std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity > > &) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

%typemap(in) const std::vector< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity > >,std::allocator< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity > > > > & (std::vector<std::vector<double> > temp)
{
  temp = PyFrensie::convertFromPython<std::vector<std::vector<double> > >( $input );

  $1 = &temp;
}

%typemap(typecheck, precedence=1050) (const std::vector< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity > >,std::allocator< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity > > > > &) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

%typemap(in) const std::vector< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity > >,std::allocator< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity > > > > & (std::vector<std::vector<double> > temp)
{
  temp = PyFrensie::convertFromPython<std::vector<std::vector<double> > >( $input );

  $1 = &temp;
}

%typemap(typecheck, precedence=1050) (const std::vector< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity > >,std::allocator< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity > > > > &) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

%advanced_tab_bivariate_distribution_interface_setup( InterpolatedFullyTabularBasicBivariateDistribution_ ## INTERP ## _ ## GRID, InterpolatedFullyTabularBasicBivariateDistribution, Utility::INTERP, Utility::GRID )

%enddef

%tabular_bivariate_distribution_interface_setup( Direct, LinLinLin )
%tabular_bivariate_distribution_interface_setup( Direct, LinLinLog )
%tabular_bivariate_distribution_interface_setup( Direct, LogLogLog )
%tabular_bivariate_distribution_interface_setup( UnitBase, LinLinLin )
%tabular_bivariate_distribution_interface_setup( UnitBase, LinLinLog )
%tabular_bivariate_distribution_interface_setup( UnitBase, LogLogLog )
%tabular_bivariate_distribution_interface_setup( Correlated, LinLinLin )
%tabular_bivariate_distribution_interface_setup( Correlated, LinLinLog )
%tabular_bivariate_distribution_interface_setup( Correlated, LogLogLog )
%tabular_bivariate_distribution_interface_setup( UnitBaseCorrelated, LinLinLin )
%tabular_bivariate_distribution_interface_setup( UnitBaseCorrelated, LinLinLog )
%tabular_bivariate_distribution_interface_setup( UnitBaseCorrelated, LogLogLog )

//---------------------------------------------------------------------------//
// end Utility_BivariateDistribution.i
//---------------------------------------------------------------------------//

