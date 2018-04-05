//---------------------------------------------------------------------------//
//!
//! \file   Utility_BivariateDistributionHelpers.i
//! \author Luke Kersting
//! \brief  The distribution helper macros
//!
//---------------------------------------------------------------------------//

%{
#include "PyFrensie_DistributionHelpers.hpp"
%}

// Include std::string support
%include <std_string.i>

// Import the PyFrensie utility
%import "PyFrensie_DistributionHelpers.hpp"

//---------------------------------------------------------------------------//
// Helper macros for getting the distribution name
//---------------------------------------------------------------------------//
// Get the name of a distribution that has 3,4,5,6 template parameters
// It must be included in both the interface file and the wrapper file since
// the preprocessor will have to parse it separately in both files
%{
#define _BI_DIST_NAME_6_ARGS( dist_base_name, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6 ) Utility::UnitAware ## dist_base_name<arg_2<arg_1>, arg_3<arg_4,arg_5,arg_6> >
%}
#define _BI_DIST_NAME_6_ARGS( dist_base_name, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6 ) Utility::UnitAware ## dist_base_name<arg_2<arg_1>, arg_3<arg_4,arg_5,arg_6> >

%{
#define _BI_DIST_NAME_5_ARGS( dist_base_name, arg_1, arg_2, arg_3, arg_4, arg_5 ) Utility::UnitAware ## dist_base_name<arg_2<arg_1>,arg_3,arg_4,arg_5>
%}
#define _BI_DIST_NAME_5_ARGS( dist_base_name, arg_1, arg_2, arg_3, arg_4, arg_5 ) Utility::UnitAware ## dist_base_name<arg_2<arg_1>,arg_3,arg_4,arg_5>

%{
#define _BI_DIST_NAME_4_ARGS( dist_base_name, arg_1, arg_2, arg_3, arg_4 ) Utility::UnitAware ## dist_base_name<arg_1,arg_2,arg_3,arg_4>
%}
#define _BI_DIST_NAME_4_ARGS( dist_base_name, arg_1, arg_2, arg_3, arg_4 ) Utility::UnitAware ## dist_base_name<arg_1,arg_2,arg_3,arg_4>

%{
#define _BI_DIST_NAME_3_ARGS( dist_base_name, arg_1, arg_2, arg_3 ) Utility::UnitAware ## dist_base_name<arg_1,arg_2,arg_3>
%}
#define _BI_DIST_NAME_3_ARGS( dist_base_name, arg_1, arg_2, arg_3 ) Utility::UnitAware ## dist_base_name<arg_1,arg_2,arg_3>

// Get the name of a distribution that has 2 template parameters
#define _BI_DIST_NAME_2_ARGS( dist_base_name, arg_1, arg_2 ) Utility::UnitAware ## dist_base_name<arg_1,arg_2>

%{
#define BI_DIST_BASE_NAME( dist_base_name ) Utility::UnitAware ## dist_base_name
%}
// Get theunit aware base name of a distribution
#define BI_DIST_BASE_NAME( dist_base_name ) Utility::UnitAware ## dist_base_name

// Use Preprocessor Metaprogramming to get the distribution name
#define _GET_BI_DIST_NAME_MACRO( _1, _2, _3, _4, _5, _6, _7, NAME, ... ) NAME
#define BI_DIST_NAME( ... ) _GET_BI_DIST_NAME_MACRO(__VA_ARGS__, _BI_DIST_NAME_6_ARGS, _BI_DIST_NAME_5_ARGS, _BI_DIST_NAME_4_ARGS, _BI_DIST_NAME_3_ARGS, _BI_DIST_NAME_2_ARGS)(__VA_ARGS__)

//---------------------------------------------------------------------------//
// Helper macro for setting up a basic BivariateDistribution class python interface
//---------------------------------------------------------------------------//
%define %basic_bivariate_distribution_interface_setup_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMS... )

%shared_ptr( BI_DIST_NAME( DISTRIBUTION, PARAMS ) )

%feature("docstring") BI_DIST_NAME( DISTRIBUTION, PARAMS )
"The RENAMED_DISTRIBUTION proxy class. This class can be evaluated and sampled.
Before sampling, make sure to initialize the Frensie Pseudo-Random Number
Generator (PyFrensie.Utility.initFrensiePrng())"

%feature("autodoc",
"evaluate(RENAMED_DISTRIBUTION self, double primary_indep_var_value, double secondary_indep_var_value ) -> double" )
BI_DIST_NAME( DISTRIBUTION, PARAMS )::evaluate;

%feature("autodoc",
"evaluateSecondaryConditionalPDF(RENAMED_DISTRIBUTION self, double primary_indep_var_value, double secondary_indep_var_value ) -> double" )
BI_DIST_NAME( DISTRIBUTION, PARAMS )::evaluateSecondaryConditionalPDF;

%feature("autodoc",
"sampleSecondaryConditional(RENAMED_DISTRIBUTION self, double primary_indep_var_value) -> double" )
BI_DIST_NAME( DISTRIBUTION, PARAMS )::sampleSecondaryConditional;

%feature("autodoc",
"sampleSecondaryConditionalAndRecordTrials(RENAMED_DISTRIBUTION self, double primary_indep_var_value, unsigned int & trials ) -> double, unsigned int

Sample from the RENAMED_DISTRIBUTION and record the number of trials
(iterations) that were required to generate the sample. The first element of
the returned tuple is the sample. The second element of the returned tuple is
the trials counter. The trials counter can be reused as such:

  PyFrensie.Utility.initFrensiePrng()

  u = PyFrensie.Utility.RENAMED_DISTRIBUTION( ... )
  trials_counter = 0

  sample,trials_counter = u.sampleSecondaryConditionalAndRecordTrials( trials_counter )
  sample,trials_counter = u.ssampleSecondaryConditionalAndRecordTrials( trials_counter )

  print trials_counter
  2")
BI_DIST_NAME( DISTRIBUTION, PARAMS )::sampleSecondaryConditionalAndRecordTrials;

%feature("autodoc",
"getUpperBoundOfPrimaryIndepVar(RENAMED_DISTRIBUTION self, double primary_indep_var_value) -> double" )
BI_DIST_NAME( DISTRIBUTION, PARAMS )::getUpperBoundOfPrimaryIndepVar;

%feature("autodoc",
"getLowerBoundOfPrimaryIndepVar(RENAMED_DISTRIBUTION self, double primary_indep_var_value) -> double" )
BI_DIST_NAME( DISTRIBUTION, PARAMS )::getLowerBoundOfPrimaryIndepVar;

// SWIG will not parse typedefs. Create some typemaps that map the
// typedefs to their true type (double)
%typemap(in) BI_DIST_NAME( DISTRIBUTION, PARAMS )::PrimaryIndepQuantity
{
  $1 = PyFloat_AsDouble($input);
}

%typemap(typecheck, precedence=90) (BI_DIST_NAME( DISTRIBUTION, PARAMS )::PrimaryIndepQuantity) {
  $1 = (PyFloat_Check($input) || PyInt_Check($input) || PyLong_Check($input)) ? 1 : 0;
}

%typemap(out) BI_DIST_NAME( DISTRIBUTION, PARAMS )::PrimaryIndepQuantity
{
  $result = PyFloat_FromDouble($1);
}

%typemap(in) BI_DIST_NAME( DISTRIBUTION, PARAMS )::SecondaryIndepQuantity
{
  $1 = PyFloat_AsDouble($input);
}

%typemap(typecheck, precedence=90) (BI_DIST_NAME( DISTRIBUTION, PARAMS )::SecondaryIndepQuantity) {
  $1 = (PyFloat_Check($input) || PyInt_Check($input) || PyLong_Check($input)) ? 1 : 0;
}

%typemap(out) BI_DIST_NAME( DISTRIBUTION, PARAMS )::SecondaryIndepQuantity
{
  $result = PyFloat_FromDouble($1);
}

%typemap(out) BI_DIST_NAME( DISTRIBUTION, PARAMS )::DepQuantity
{
  $result = PyFloat_FromDouble($1);
}

%typemap(out) BI_DIST_NAME( DISTRIBUTION, PARAMS )::InverseSecondaryIndepQuantity
{
  $result = PyFloat_FromDouble($1);
}

%template(RENAMED_DISTRIBUTION) BI_DIST_NAME( DISTRIBUTION, PARAMS );

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a basic TabularBivariateDistribution class py. int.
//---------------------------------------------------------------------------//
%define %standard_tab_bivariate_distribution_interface_setup_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMS... )

%feature("autodoc",
"evaluateSecondaryConditionalCDF(RENAMED_DISTRIBUTION self, double primary_indep_var_value, double secondary_indep_var_value ) -> double" )
BI_DIST_NAME( DISTRIBUTION, PARAMS )::evaluateSecondaryConditionalCDF;

%feature("autodoc",
"sampleSecondaryConditionalAndRecordBinIndices(RENAMED_DISTRIBUTION self, double primary_indep_var_value) -> double, size_t, size_t

Sample from the RENAMED_DISTRIBUTION and record the bin index corresponding to
the sample. The first element of the returned tuple is the sample. The second
and third elements of the returned tuple are the primary and secondary bin
indices. This method can be called as follows:

  PyFrensie.Utility.initFrensiePrng()

  u = PyFrensie.Utility.RENAMED_DISTRIBUTION( ... )
  primary_indep_var_value = 1.0

  sample,primary_bin_index,secondary_bin_index = u.sampleSecondaryConditionalAndRecordBinIndices( primary_indep_var_value)")
BI_DIST_NAME( DISTRIBUTION, PARAMS )::sampleSecondaryConditionalAndRecordBinIndices;

%feature("autodoc",
"sampleSecondaryConditionalWithRandomNumber(RENAMED_DISTRIBUTION self, double primary_indep_var_value, const double random_number) -> double

Sample from the RENAMED_DISTRIBUTION using the supplied random number instead
of using the hidden Utility::RandomNumberGenerator.")
BI_DIST_NAME( DISTRIBUTION, PARAMS )::sampleSecondaryConditionalWithRandomNumber;

%feature("autodoc",
"sampleSecondaryConditionalInSubrange(RENAMED_DISTRIBUTION self, double primary_indep_var_value, const double max_secondary_indep_var_value ) -> double

Sample from the RENAMED_DISTRIBUTION in the subrange
[self.getLowerBoundOfIndepVar(),max_secondary_indep_var_value]" )
BI_DIST_NAME( DISTRIBUTION, PARAMS )::sampleSecondaryConditionalInSubrange;

%feature("autodoc",
"sampleSecondaryConditionalWithRandomNumberInSubrange(RENAMED_DISTRIBUTION self, double primary_indep_var_value, const double random_number, const double max_secondary_indep_var_value ) -> double

Sample from the RENAMED_DISTRIBUTION using the supplied random number in the
subrange [self.getLowerBoundOfIndepVar(),max_indep_var]" )
BI_DIST_NAME( DISTRIBUTION, PARAMS )::sampleSecondaryConditionalWithRandomNumberInSubrange;

// Create unitless constructor
%extend BI_DIST_BASE_NAME( DISTRIBUTION )
{
  // Constructor
  BI_DIST_BASE_NAME( DISTRIBUTION )(
    const std::vector<double>& raw_prim_grid,
    const std::vector<std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<void,void> > >& vec )
  {
    std::vector<double> prim_grid(raw_prim_grid);
    std::vector<std::shared_ptr<const Utility::UnitAwareTabularUnivariateDistribution<void,void> > > sec_dists(2);

    for ( unsigned i = 0; i < vec.size(); ++i )
    {
      sec_dists[i] = vec[i];
    }

    return new BI_DIST_NAME( DISTRIBUTION, PARAMS )( prim_grid, sec_dists );
  }
}

%basic_bivariate_distribution_interface_setup_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a basic BivariateDistribution class python interface
//---------------------------------------------------------------------------//
%define %basic_bivariate_distribution_interface_setup( DISTRIBUTION )

%basic_bivariate_distribution_interface_setup_helper( DISTRIBUTION, DISTRIBUTION, void, void, void )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a standard Distribution class python interface
//---------------------------------------------------------------------------//
%define %standard_bivariate_distribution_interface_setup( DISTRIBUTION )

// Do the basic setup for this distribution
%basic_bivariate_distribution_interface_setup_helper( DISTRIBUTION, DISTRIBUTION, void ,void, void )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up an advanced Distribution class python interface
//---------------------------------------------------------------------------//
%define %advanced_bivariate_distribution_interface_setup( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMETER1, PARAMETER2, PARAMETER3 )

// Add a typedef for the renamed distribution so that the extended methods
// can be compiled
%inline %{
typedef BI_DIST_NAME( DISTRIBUTION, PARAMETER1, PARAMETER2, PARAMETER3, void, void, void ) RENAMED_DISTRIBUTION;
%}

// Do the basic setup for this distribution
%basic_bivariate_distribution_interface_setup_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMETER1, PARAMETER2, PARAMETER3, void, void, void )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a basic TabularBivariateDistribution class py. int.
//---------------------------------------------------------------------------//
%define %basic_tab_bivariate_distribution_interface_setup( DISTRIBUTION, PARAMETER )

// Add a typedef for the renamed distribution so that the extended methods
// can be compiled
%inline %{
typedef BI_DIST_NAME( DISTRIBUTION, void, void, void, PARAMETER ) DISTRIBUTION;
%}

// Do the basic tabular setup for this distribution
%basic_bivariate_distribution_interface_setup_helper( DISTRIBUTION, DISTRIBUTION, void , void, void, PARAMETER )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a standard Tabular Distribution class python interface
//---------------------------------------------------------------------------//
%define %standard_tab_bivariate_distribution_interface_setup( DISTRIBUTION )

%standard_tab_bivariate_distribution_interface_setup_helper( DISTRIBUTION, DISTRIBUTION, void, void, void )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up an advanced Tabular Distribution class python interface
//---------------------------------------------------------------------------//
%define %advanced_tab_bivariate_distribution_interface_setup( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMETER1, PARAMETER2 )

// Add a typedef for the renamed distribution so that the extended methods
// can be compiled
%inline %{
typedef BI_DIST_NAME( DISTRIBUTION, PARAMETER1, PARAMETER2, void, void, void ) RENAMED_DISTRIBUTION;
%}

// Do the basic tabular setup for this distribution
%standard_tab_bivariate_distribution_interface_setup_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMETER1, PARAMETER2, void, void, void )

%enddef


//---------------------------------------------------------------------------//
// end Utility_BivariateDistributionHelpers.i
//---------------------------------------------------------------------------//