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

// Include the serialization helpers
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
// %apply Utility::DistributionTraits::Counter& INOUT { Utility::DistributionTraits::Counter& trials };
%apply unsigned& OUTPUT { unsigned& primary_bin_index };
%apply unsigned& OUTPUT { unsigned& secondary_bin_index };

%typemap(in) const std::vector<std::vector<double> >& (std::vector<std::vector<double> > temp)
{
  temp = PyFrensie::convertFromPython<std::vector<std::vector<double> > >( $input );

  $1 = &temp;
}

// Set the typecheck precedence
%typemap(typecheck, precedence=1050) (const std::vector<std::vector<double> >&) {
  $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
}

// General ignore directives
%ignore *::PrimaryIndepUnit;
%ignore *::SecondaryIndepUnit;
%ignore *::PrimaryIndepQuantity;
%ignore *::SecondaryIndepQuantity;
%ignore *::InverseSecondaryIndepQuantity;

//---------------------------------------------------------------------------//
// Add support for the BasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the BasicBivariateDistribution
%import "Utility_BasicBivariateDistribution.hpp"

// Basic distribution interface setup
%basic_bivariate_distribution_interface_setup( BasicBivariateDistribution )

// //---------------------------------------------------------------------------//
// // Add support for the BivariateDistribution
// //---------------------------------------------------------------------------//
// // Import the BivariateDistribution
// %import "Utility_BivariateDistribution.hpp"

// // Basic distribution interface setup
// %basic_bivariate_distribution_interface_setup( BivariateDistribution )

/* NOTE: Currently the TabularBasicBivariateDistribution cannot be imported due
 *       to the complexity of its template structure. It appears that similar
 *       structures are supported by Swig but all attempts have failed to import
 *       the class.
 */
// //---------------------------------------------------------------------------//
// // Add support for the TabularBasicBivariateDistribution
// //---------------------------------------------------------------------------//
// // Import the TabularBasicBivariateDistribution
// %import "Utility_TabularBasicBivariateDistribution.hpp"

// // Create unitless constructor
// %extend Utility::UnitAwareTabularBasicBivariateDistribution
// {
//   // Constructor
//   Utility::UnitAwareTabularBasicBivariateDistribution<double,double,double, Utility::UnitAwareTabularUnivariateDistribution>::UnitAwareTabularBasicBivariateDistribution(
//     const std::vector<double>& raw_prim_grid,
//     const std::vector<std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<void,void> > >& vec )
//   {
//     std::vector<double> prim_grid(raw_prim_grid);
//     std::vector<std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<void,void> > > sec_dists(2);

//     for ( unsigned i = 0; i < vec.size(); ++i )
//     {
//       sec_dists[i] = vec[i];
//     }

//     return new Utility::UnitAwareTabularBasicBivariateDistribution<double,double,double, Utility::UnitAwareTabularUnivariateDistribution<double,double> >::UnitAwareTabularBasicBivariateDistribution( prim_grid, sec_dists );
//   }
// }

// // typedef Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void, Utility::UnitAwareTabularUnivariateDistribution<void,void> > TabularBasicBivariateDistribution;

// // // %shared_ptr(TabularBasicBivariateDistribution)
// %shared_ptr(Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void, Utility::UnitAwareTabularUnivariateDistribution<void,void> > )

// %feature("docstring") Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void, Utility::UnitAwareTabularUnivariateDistribution<void,void> >
// "The RENAMED_DISTRIBUTION proxy class. This class can be evaluated and sampled.
// Before sampling, make sure to initialize the Frensie Pseudo-Random Number
// Generator (PyFrensie.Utility.initFrensiePrng())"

// %template(TabularBasicBivariateDistribution) Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void, Utility::UnitAwareTabularUnivariateDistribution<void,void> >;

// Basic distribution interface setup
// %basic_tab_bivariate_distribution_interface_setup( TabularBasicBivariateDistribution, TabularUnivariateDistribution )

/* NOTE: Currently importing the
 *       PartiallyTabularBasicBivariateDistribution class causes
 *       an error when importing the
 *       InterpolatedPartiallyTabularBasicBivariateDistribution class. For now the
 *       class will be included but not imported.
 */
//---------------------------------------------------------------------------//
// Add support for the PartiallyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
%include "Utility_PartiallyTabularBasicBivariateDistribution.hpp"
// // Import the PartiallyTabularBasicBivariateDistribution
// %import "Utility_PartiallyTabularBasicBivariateDistribution.hpp"

// // Standard tabular distribution interface setup
// %standard_tab_bivariate_distribution_interface_setup( PartiallyTabularBasicBivariateDistribution )

//---------------------------------------------------------------------------//
// Add support for the FullyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the FullyTabularBasicBivariateDistribution
%import "Utility_FullyTabularBasicBivariateDistribution.hpp"

// Standard tabular distribution interface setup
%standard_tab_bivariate_distribution_interface_setup( FullyTabularBasicBivariateDistribution )

/* NOTE: Currently importing the
 *       InterpolatedTabularBasicBivariateDistributionImplBase class causes
 *       an error when importing the
 *       InterpolatedFullyTabularBasicBivariateDistribution class. For now the
 *       class will be included but not imported.
 */
//---------------------------------------------------------------------------//
// Add support for the InterpolatedTabularBasicBivariateDistributionImplBase
//---------------------------------------------------------------------------//
%include "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"
// // Import the InterpolatedTabularBasicBivariateDistributionImplBase
// %import "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"

// // There are many interpolated tabular distributions - use this macro to set up each
// %define %tabular_bivariate_distribution_base_interface_setup( GRID, INTERP, BASE )

// // Add a more detailed docstring for the constructor
// %feature("docstring")
// Utility::UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase< Utility::GRID< Utility::INTERP >,UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> >
// "The InterpolatedTabularBasicBivariateDistributionImplBase class should never be directly instantiated but always used with the InterpolatedFullyTabularBasicBivariateDistribution or the InterpolatedPartiallyTabularBasicBivariateDistribution classes."

// %advanced_bivariate_distribution_interface_setup( InterpolatedTabularBasicBivariateDistributionImplBase_ ## INTERP ## _ ## GRID, InterpolatedTabularBasicBivariateDistributionImplBase, Utility::INTERP, Utility::GRID, Utility::BASE )

// %enddef

// // Basic distribution interface setup
// %tabular_bivariate_distribution_base_interface_setup( UnitBase, LinLinLin, UnitAwareFullyTabularBasicBivariateDistribution )

//---------------------------------------------------------------------------//
// Add support for the InterpolatedFullyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the InterpolatedFullyTabularBasicBivariateDistribution
%import "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

// There are many interpolated tabular distributions - use this macro to set up each
%define %tabular_bivariate_distribution_interface_setup( GRID, INTERP )

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::GRID<Utility::INTERP>,void,void,void>::InterpolatedFullyTabularBasicBivariateDistribution
"The primary independent values can be stored as a python list or a NumPy array. The secondary independent values and dependent values can be stored as a python list of NumPy array or of a python list. Alternatively, a list of univariate distributions can be used for the secondary distributions."

// // Typemap for std::vector<PrimaryIndepQuantity
// %typemap(in) const std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity > > & (std::vector<double> temp)
// {
//   temp = PyFrensie::convertFromPython<std::vector<double> >( $input );

//   $1 = &temp;
// }

// // Typecheck for std::vector<PrimaryIndepQuantity>
// %typemap(typecheck, precedence=1050) (const std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity > > &) {
//   $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
// }

// // Typemap for std::vector< std::vector< SecondaryIndepQuantity > >
// %typemap(in) const std::vector< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity > >,std::allocator< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity > > > > & (std::vector<std::vector<double> > temp)
// {
//   temp = PyFrensie::convertFromPython<std::vector<std::vector<double> > >( $input );

//   $1 = &temp;
// }

// // Typecheck for std::vector< std::vector< SecondaryIndepQuantity > >
// %typemap(typecheck, precedence=1050) (const std::vector< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity > >,std::allocator< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::SecondaryIndepQuantity > > > > &) {
//   $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
// }

// // Typemap for std::vector< std::vector< DepQuantity > >
// %typemap(in) const std::vector< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity > >,std::allocator< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity > > > > & (std::vector<std::vector<double> > temp)
// {
//   temp = PyFrensie::convertFromPython<std::vector<std::vector<double> > >( $input );

//   $1 = &temp;
// }

// // Typecheck for std::vector< std::vector< DepQuantity > >
// %typemap(typecheck, precedence=1050) (const std::vector< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity > >,std::allocator< std::vector< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity,std::allocator< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::DepQuantity > > > > &) {
//   $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
// }

// // %typemap(in) const std::vector< std::shared_ptr< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::BaseUnivariateDistributionType const >,std::allocator< std::shared_ptr< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::BaseUnivariateDistributionType const > > > & (std::vector<std::shared_ptr<TabularUnivariateDistribution> > temp)
// // {
// //   temp = PyFrensie::convertFromPython<std::vector<std::shared_ptr<TabularUnivariateDistribution> > >( $input );

// //   $1 = &temp;
// // }

// // %typemap(typecheck, precedence=1050) (const std::vector< std::shared_ptr< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::BaseUnivariateDistributionType const >,std::allocator< std::shared_ptr< Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::BaseUnivariateDistributionType const > > > &) {
// //   $1 = (PyList_Check($input)) ? 1 : 0;
// // }


%advanced_tab_bivariate_distribution_interface_setup( InterpolatedFullyTabularBasicBivariateDistribution_ ## INTERP ## _ ## GRID, InterpolatedFullyTabularBasicBivariateDistribution, TabularUnivariateDistribution, Utility::INTERP, Utility::GRID )

// %typedef double Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity;
// %template(VectorPrim) std::vector<Utility::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution< Utility::GRID< Utility::INTERP >,void,void,void >::PrimaryIndepQuantity>;

%enddef

// %tabular_bivariate_distribution_interface_setup( Direct, LinLinLin )
// %tabular_bivariate_distribution_interface_setup( Direct, LinLinLog )
// %tabular_bivariate_distribution_interface_setup( Direct, LogLogLog )
%tabular_bivariate_distribution_interface_setup( UnitBase, LinLinLin )
// %tabular_bivariate_distribution_interface_setup( UnitBase, LinLinLog )
// %tabular_bivariate_distribution_interface_setup( UnitBase, LogLogLog )
// %tabular_bivariate_distribution_interface_setup( Correlated, LinLinLin )
// %tabular_bivariate_distribution_interface_setup( Correlated, LinLinLog )
// %tabular_bivariate_distribution_interface_setup( Correlated, LogLogLog )
// %tabular_bivariate_distribution_interface_setup( UnitBaseCorrelated, LinLinLin )
// %tabular_bivariate_distribution_interface_setup( UnitBaseCorrelated, LinLinLog )
// %tabular_bivariate_distribution_interface_setup( UnitBaseCorrelated, LogLogLog )

//---------------------------------------------------------------------------//
// Add support for the InterpolatedPartiallyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the InterpolatedPartiallyTabularBasicBivariateDistribution
%import "Utility_InterpolatedPartiallyTabularBasicBivariateDistribution.hpp"

// There are many interpolated tabular distributions - use this macro to set up each
%define %partially_tabular_bivariate_distribution_interface_setup( GRID, INTERP )

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::GRID<Utility::INTERP>,void,void,void>::InterpolatedPartiallyTabularBasicBivariateDistribution
"The primary independent values can be stored as a python list or a NumPy array. The secondary distributions can be stored as a python list of univariate distributions."

%extend Utility::UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::GRID<Utility::INTERP>,void,void,void>
{
  // Return a random sample from the secondary conditional PDF
  SecondaryIndepQuantity Utility::UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::GRID<Utility::INTERP>,void,void,void>::sampleSecondaryConditional(
                const PrimaryIndepQuantity primary_indep_var_value ) const
  {
    return $self->sampleSecondaryConditional( primary_indep_var_value );
  }

  // Return a random sample and record the number of trials
  SecondaryIndepQuantity Utility::UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::GRID<Utility::INTERP>,void,void,void>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            DistributionTraits::Counter& trials ) const
  {
    return $self->sampleSecondaryConditionalAndRecordTrials( primary_indep_var_value, trials);
  }
};

%advanced_tab_bivariate_distribution_interface_setup( InterpolatedPartiallyTabularBasicBivariateDistribution_ ## INTERP ## _ ## GRID, InterpolatedPartiallyTabularBasicBivariateDistribution, UnivariateDistribution, Utility::INTERP, Utility::GRID )

%enddef

// %partially_tabular_bivariate_distribution_interface_setup( Direct, LinLinLin )
// %partially_tabular_bivariate_distribution_interface_setup( Direct, LinLinLog )
// %partially_tabular_bivariate_distribution_interface_setup( Direct, LogLogLog )
%partially_tabular_bivariate_distribution_interface_setup( UnitBase, LinLinLin )
// %partially_tabular_bivariate_distribution_interface_setup( UnitBase, LinLinLog )
// %partially_tabular_bivariate_distribution_interface_setup( UnitBase, LogLogLog )






//---------------------------------------------------------------------------//
// Add support for the HistogramTabularBasicBivariateDistributionImplBase
//---------------------------------------------------------------------------//
%include "Utility_HistogramTabularBasicBivariateDistributionImplBase.hpp"

//---------------------------------------------------------------------------//
// Add support for the HistogramFullyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the HistogramFullyTabularBasicBivariateDistribution
%import "Utility_HistogramFullyTabularBasicBivariateDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareHistogramFullyTabularBasicBivariateDistribution<void,void,void>::HistogramFullyTabularBasicBivariateDistribution
"The primary independent values can be stored as a python list or a NumPy array. The secondary distributions can be stored as a python list of univariate distributions."

%advanced_histogram_bivariate_distribution_interface_setup( HistogramFullyTabularBasicBivariateDistribution, HistogramFullyTabularBasicBivariateDistribution, TabularUnivariateDistribution )

//---------------------------------------------------------------------------//
// Add support for the HistogramPartiallyTabularBasicBivariateDistribution
//---------------------------------------------------------------------------//
// Import the HistogramPartiallyTabularBasicBivariateDistribution
%import "Utility_HistogramPartiallyTabularBasicBivariateDistribution.hpp"

// Add a more detailed docstring for the constructor
%feature("docstring")
Utility::UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<void,void,void>::HistogramPartiallyTabularBasicBivariateDistribution
"The primary independent values can be stored as a python list or a NumPy array. The secondary distributions can be stored as a python list of univariate distributions."

%advanced_histogram_bivariate_distribution_interface_setup( HistogramPartiallyTabularBasicBivariateDistribution, HistogramPartiallyTabularBasicBivariateDistribution, UnivariateDistribution )

// //---------------------------------------------------------------------------//
// // end Utility_BivariateDistribution.i
// //---------------------------------------------------------------------------//
