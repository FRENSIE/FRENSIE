//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnivariateDistributionHelpers.i
//! \author Alex Robinson, Luke Kersting
//! \brief  The distribution helper macros
//!
//---------------------------------------------------------------------------//

// Include std::string support
%include <std_string.i>

//---------------------------------------------------------------------------//
// Helper macros for getting the distribution name
//---------------------------------------------------------------------------//
// Get the name of a distribution that has 3 template parameters
// It must be included in both the interface file and the wrapper file since
// the preprocessor will have to parse it separately in both files
%{
#define _DIST_NAME_3_ARGS( dist_base_name, arg_1, arg_2, arg_3 ) Utility::UnitAware ## dist_base_name<arg_1,arg_2,arg_3>
%}
#define _DIST_NAME_3_ARGS( dist_base_name, arg_1, arg_2, arg_3 ) Utility::UnitAware ## dist_base_name<arg_1,arg_2,arg_3>

// Get the name of a distribution that has 2 template parameters
#define _DIST_NAME_2_ARGS( dist_base_name, arg_1, arg_2 ) Utility::UnitAware ## dist_base_name<arg_1,arg_2>

// Use Preprocessor Metaprogramming to get the distribution name
#define _GET_DIST_NAME_MACRO( _1, _2, _3, _4, NAME, ... ) NAME
#define DIST_NAME( ... ) _GET_DIST_NAME_MACRO(__VA_ARGS__, _DIST_NAME_3_ARGS, _DIST_NAME_2_ARGS)(__VA_ARGS__)

//---------------------------------------------------------------------------//
// Helper macro for setting up a basic UnivariateDistribution class python interface
//---------------------------------------------------------------------------//
%define %basic_distribution_interface_setup_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMS... )

%shared_ptr(DIST_NAME( DISTRIBUTION, PARAMS ) )

%feature("docstring") DIST_NAME( DISTRIBUTION, PARAMS )
"The RENAMED_DISTRIBUTION proxy class. This class can be evaluated and sampled.
Before sampling, make sure to initialize the Frensie Pseudo-Random Number
Generator (PyFrensie.Utility.initFrensiePrng())"

%feature("autodoc",
"evaluate(RENAMED_DISTRIBUTION self, double indep_var_value ) -> double" )
DIST_NAME( DISTRIBUTION, PARAMS )::evaluate;

%feature("autodoc",
"evaluatePDF(RENAMED_DISTRIBUTION self, double indep_var_value ) -> double" )
DIST_NAME( DISTRIBUTION, PARAMS )::evaluatePDF;

%feature("autodoc",
"sample(RENAMED_DISTRIBUTION self) -> double" )
DIST_NAME( DISTRIBUTION, PARAMS )::sample;

%feature("autodoc",
"sampleAndRecordTrials(RENAMED_DISTRIBUTION self, unsigned int & trials ) -> double, unsigned int

Sample from the RENAMED_DISTRIBUTION and record the number of trials
(iterations) that were required to generate the sample. The first element of
the returned tuple is the sample. The second element of the returned tuple is
the trials counter. The trials counter can be reused as such:

  PyFrensie.Utility.initFrensiePrng()

  u = PyFrensie.Utility.RENAMED_DISTRIBUTION( ... )
  trials_counter = 0

  sample,trials_counter = u.sampleAndRecordTrials( trials_counter )
  sample,trials_counter = u.sampleAndRecordTrials( trials_counter )

  print trials_counter
  2")
DIST_NAME( DISTRIBUTION, PARAMS )::sampleAndRecordTrials;

%feature("autodoc",
"getUpperBoundOfIndepVar(RENAMED_DISTRIBUTION self) -> double" )
DIST_NAME( DISTRIBUTION, PARAMS )::getUpperBoundOfIndepVar;

%feature("autodoc",
"getLowerBoundOfIndepVar(RENAMED_DISTRIBUTION self) -> double" )
DIST_NAME( DISTRIBUTION, PARAMS )::getLowerBoundOfIndepVar;

// Apply typemaps for various class typedefs
%apply double {DIST_NAME( DISTRIBUTION, PARAMS )::DepQuantity}
%apply double {DIST_NAME( DISTRIBUTION, PARAMS )::IndepQuantity}
%apply double {DIST_NAME( DISTRIBUTION, PARAMS )::InverseIndepQuantity}

%template(RENAMED_DISTRIBUTION) DIST_NAME( DISTRIBUTION, PARAMS );

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a basic TabularUnivariateDistribution class py. int.
//---------------------------------------------------------------------------//
%define %basic_tab_distribution_interface_setup_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMS... )

%feature("autodoc",
"evaluateCDF(RENAMED_DISTRIBUTION self, double indep_var_value ) -> double" )
DIST_NAME( DISTRIBUTION, PARAMS )::evaluateCDF;

%feature("autodoc",
"sampleAndRecordBinIndex(RENAMED_DISTRIBUTION self) -> double, size_t

Sample from the RENAMED_DISTRIBUTION and record the bin index corresponding to
the sample. The first element of the returned tuple is the sample. The second
element of the returned tuple is the bin index. This method can be called
as follows:

  PyFrensie.Utility.initFrensiePrng()

  u = PyFrensie.Utility.RENAMED_DISTRIBUTION( ... )

  sample,bin_index = u.sampleAndRecordBinIndex()")
DIST_NAME( DISTRIBUTION, PARAMS )::sampleAndRecordBinIndex;

%feature("autodoc",
"sampleWithRandomNumber(RENAMED_DISTRIBUTION self, const double random_number) -> double

Sample from the RENAMED_DISTRIBUTION using the supplied random number instead
of using the hidden Utility::RandomNumberGenerator.")
DIST_NAME( DISTRIBUTION, PARAMS )::sampleWithRandomNumber;

%feature("autodoc",
"sampleInSubrange(RENAMED_DISTRIBUTION self, const double max_indep_var ) -> double

Sample from the RENAMED_DISTRIBUTION in the subrange
[self.getLowerBoundOfIndepVar(),max_indep_var]" )
DIST_NAME( DISTRIBUTION, PARAMS )::sampleInSubrange;

%feature("autodoc",
"sampleWithRandomNumberInSubrange(RENAMED_DISTRIBUTION self, const double random_number, const double max_indep_var ) -> double

Sample from the RENAMED_DISTRIBUTION using the supplied random number in the
subrange [self.getLowerBoundOfIndepVar(),max_indep_var]" )
DIST_NAME( DISTRIBUTION, PARAMS )::sampleWithRandomNumberInSubrange;

%basic_distribution_interface_setup_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macros for extending a UnivariateDistribution class python interface
//---------------------------------------------------------------------------//
%define %extend_distribution_interface_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMS... )

%feature("autodoc",
"__str__(RENAMED_DISTRIBUTION self) -> string

Convert the RENAMED_DISTRIBUTION to a string.")
DIST_NAME( DISTRIBUTION, PARAMS )::__str__;

%feature("autodoc",
"__repr__(RENAMED_DISTRIBUTION self) -> string

Convert the RENAMED_DISTRIBUTION to a string wrapped inside of
RENAMED_DISTRIBUTION(...).")
DIST_NAME( DISTRIBUTION, PARAMS )::__repr__;

%feature("autodoc",
"__eq__(RENAMED_DISTRIBUTION self, RENAMED_DISTRIBUTION other_dist ) -> bool

Check if two RENAMED_DISTRIBUTION objects are equal (using the == operator).
This will return the same value as self.isEqual( other_dist )" )
DIST_NAME( DISTRIBUTION, PARAMS )::__eq__;

%feature("autodoc",
"__ne__(RENAMED_DISTRIBUTION self, RENAMED_DISTRIBUTION other_dist ) -> bool

Check if two RENAMED_DISTRIBUTION objects are not equal (using the !=
operator). This will return the same value as !self.isEqual( other_dist )" )
DIST_NAME( DISTRIBUTION, PARAMS )::__ne__;

// Add some useful methods to the distribution class
%extend DIST_NAME( DISTRIBUTION, PARAMS )
{
  // String representation method
  PyObject* __repr__() const
  {
    std::string repr_string( #RENAMED_DISTRIBUTION );
    repr_string += "(";

    std::ostringstream oss;

    $self->toStream( oss );

    repr_string += oss.str() + ")";

    return PyString_FromString( repr_string.c_str() );
  }

  // String conversion method
  PyObject* __str__() const
  {
    std::ostringstream oss;

    $self->toStream( oss );

    return PyString_FromString( oss.str().c_str() );
  }
};

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a basic UnivariateDistribution class python interface
//---------------------------------------------------------------------------//
%define %basic_distribution_interface_setup( DISTRIBUTION )

%basic_distribution_interface_setup_helper( DISTRIBUTION, DISTRIBUTION, void, void )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a standard Distribution class python interface
//---------------------------------------------------------------------------//
%define %standard_distribution_interface_setup( DISTRIBUTION )

// Extend the distribution interface
%extend_distribution_interface_helper( DISTRIBUTION, DISTRIBUTION, void, void )

// Do the basic setup for this distribution
%basic_distribution_interface_setup_helper( DISTRIBUTION, DISTRIBUTION, void ,void )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up an advanced Distribution class python interface
//---------------------------------------------------------------------------//
%define %advanced_distribution_interface_setup( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMETER )

// Add a typedef for the renamed distribution so that the extended methods
// can be compiled
%inline %{
typedef DIST_NAME( DISTRIBUTION, PARAMETER, void, void ) RENAMED_DISTRIBUTION;
%}

// Extend the distribution interface
%extend_distribution_interface_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMETER, void, void )

// Do the basic setup for this distribution
%basic_distribution_interface_setup_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMETER, void, void )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a basic TabularUnivariateDistribution class py. int.
//---------------------------------------------------------------------------//
%define %basic_tab_distribution_interface_setup( DISTRIBUTION )

%basic_tab_distribution_interface_setup_helper( DISTRIBUTION, DISTRIBUTION, void, void )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a standard Tabular Distribution class python interface
//---------------------------------------------------------------------------//
%define %standard_tab_distribution_interface_setup( DISTRIBUTION )

// Extend the distribution inteface
%extend_distribution_interface_helper( DISTRIBUTION, DISTRIBUTION, void, void )

// Do the basic tabular setup for this distribution
%basic_tab_distribution_interface_setup_helper( DISTRIBUTION, DISTRIBUTION, void , void  )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up an advanced Tabular Distribution class python interface
//---------------------------------------------------------------------------//
%define %advanced_tab_distribution_interface_setup( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMETER )

// Add a typedef for the renamed distribution so that the extended methods
// can be compiled
%inline %{
typedef DIST_NAME( DISTRIBUTION, PARAMETER, void, void ) RENAMED_DISTRIBUTION;
%}

// Extend the distribution inteface
%extend_distribution_interface_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMETER, void, void )

// Do the basic tabular setup for this distribution
%basic_tab_distribution_interface_setup_helper( RENAMED_DISTRIBUTION, DISTRIBUTION, PARAMETER, void, void )

%enddef


//---------------------------------------------------------------------------//
// end Utility_UnivariateDistributionHelpers.i
//---------------------------------------------------------------------------//
