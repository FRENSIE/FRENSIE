//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronTemplateHelpers.i
//! \author Luke Kersting
//! \brief  The electron factory templated function helper macros
//!
//---------------------------------------------------------------------------//

// Include std::string support
%include <std_string.i>

//---------------------------------------------------------------------------//
// Helper macros for getting the function name
//---------------------------------------------------------------------------//
// Get the name of a function that has 3 template parameters
// It must be included in both the interface file and the wrapper file since
// the preprocessor will have to parse it separately in both files
%{
#define _FUNC_NAME_3_ARGS( func_base_name, arg_1, arg_2, arg_3 ) MonteCarlo::create ## func_base_name<arg_1,arg_2,arg_3>
%}
#define _FUNC_NAME_3_ARGS( func_base_name, arg_1, arg_2, arg_3 ) MonteCarlo::create ## func_base_name<arg_1,arg_2,arg_3>

%{
#define _FUNC_NEW_NAME_3_ARGS( func_base_name, arg_1, arg_2, arg_3 ) create ## arg_1 ## arg_2 ## arg_3 ## func_base_name
%}
#define _FUNC_NEW_NAME_3_ARGS( func_base_name, arg_1, arg_2, arg_3 ) create ## arg_1 ## arg_2 ## arg_3 ## func_base_name

// Get the name of a function that has 2 template parameters
#define _FUNC_NAME_2_ARGS( func_base_name, arg_1, arg_2 ) MonteCarlo::create ## func_base_name<arg_2<arg_1>>

%{
#define _FUNC_NEW_NAME_2_ARGS( func_base_name, arg_1, arg_2 ) create ## arg_1 ## arg_2 ## func_base_name
%}
#define _FUNC_NEW_NAME_2_ARGS( func_base_name, arg_1, arg_2 ) create ## arg_1 ## arg_2 ## func_base_name

// Use Preprocessor Metaprogramming to get the function name
#define _GET_FUNC_NAME_MACRO( _1, _2, _3, _4, NAME, ... ) NAME
#define FUNC_NAME( ... ) _GET_FUNC_NAME_MACRO(__VA_ARGS__, _FUNC_NAME_3_ARGS, _FUNC_NAME_2_ARGS)(__VA_ARGS__)

#define _GET_FUNC_NEW_NAME_MACRO( _1, _2, _3, _4, NEW_NAME, ... ) NEW_NAME
#define FUNC_NEW_NAME( ... ) _GET_FUNC_NEW_NAME_MACRO(__VA_ARGS__, _FUNC_NEW_NAME_3_ARGS, _FUNC_NEW_NAME_2_ARGS)(__VA_ARGS__)

//---------------------------------------------------------------------------//
// Helper macro for setting up a python interface for electron elastic factory
// class templated functions
//---------------------------------------------------------------------------//
%define %elastic_template_setup( DIST )

  // Add templates for the Correlated DIST ElasticDistribution
  %template(create ## DIST ## ElasticDistribution_LogLogCorrelated) create ## DIST ## ElasticDistribution<Utility::LogNudgedLogCosLog, Utility::Correlated>;
  %template(create ## DIST ## ElasticDistribution_LinLogCorrelated) create ## DIST ## ElasticDistribution<Utility::LinLinLog, Utility::Correlated>;
  %template(create ## DIST ## ElasticDistribution_LinLinCorrelated) create ## DIST ## ElasticDistribution<Utility::LinLinLin, Utility::Correlated>;
  // Add templates for the Direct DIST ElasticDistribution
  %template(create ## DIST ## ElasticDistribution_LogLogDirect) create ## DIST ## ElasticDistribution<Utility::LogNudgedLogCosLog, Utility::Direct>;
  %template(create ## DIST ## ElasticDistribution_LinLogDirect) create ## DIST ## ElasticDistribution<Utility::LinLinLog, Utility::Direct>;
  %template(create ## DIST ## ElasticDistribution_LinLinDirect) create ## DIST ## ElasticDistribution<Utility::LinLinLin, Utility::Direct>;

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a python interface for electron factory
// class templated functions
//---------------------------------------------------------------------------//
%define %electron_template_setup( DIST )

  // Add templates for the UnitBaseCorrelated DIST Distribution
  %template(create ## DIST ## Distribution_LogLogUnitBaseCorrelated) create ## DIST ## Distribution<Utility::LogLogLog, Utility::UnitBaseCorrelated>;
  %template(create ## DIST ## Distribution_LinLogUnitBaseCorrelated) create ## DIST ## Distribution<Utility::LinLinLog, Utility::UnitBaseCorrelated>;
  %template(create ## DIST ## Distribution_LinLinUnitBaseCorrelated) create ## DIST ## Distribution<Utility::LinLinLin, Utility::UnitBaseCorrelated>;

  // Add templates for the Correlated DIST Distribution
  %template(create ## DIST ## Distribution_LogLogCorrelated) create ## DIST ## Distribution<Utility::LogLogLog, Utility::Correlated>;
  %template(create ## DIST ## Distribution_LinLogCorrelated) create ## DIST ## Distribution<Utility::LinLinLog, Utility::Correlated>;
  %template(create ## DIST ## Distribution_LinLinCorrelated) create ## DIST ## Distribution<Utility::LinLinLin, Utility::Correlated>;

  // Add templates for the UnitBase DIST Distribution
  %template(create ## DIST ## Distribution_LogLogUnitBase) create ## DIST ## Distribution<Utility::LogLogLog, Utility::UnitBase>;
  %template(create ## DIST ## Distribution_LinLogUnitBase) create ## DIST ## Distribution<Utility::LinLinLog, Utility::UnitBase>;
  %template(create ## DIST ## Distribution_LinLinUnitBase) create ## DIST ## Distribution<Utility::LinLinLin, Utility::UnitBase>;

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a python interface for electron factory class templated functions
//---------------------------------------------------------------------------//
%define %electron_function_interface_setup( FUNCTION )

// Set LogLogLog Functions
%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LogLogLog, Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, UnitBaseCorrelated ) ) FUNC_NAME( FUNCTION, Utility::LogLogLog, Utility::UnitBaseCorrelated );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Direct ) ) FUNC_NAME( FUNCTION, Utility::LogLogLog, Utility::Direct );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, UnitBase ) ) FUNC_NAME( FUNCTION, Utility::LogLogLog, Utility::UnitBase );

// Set LinLinLin Functions
%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, UnitBaseCorrelated ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::UnitBaseCorrelated );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, Direct ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::Direct );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, UnitBase ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::UnitBase );

// Set LinLinLog Functions
%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, UnitBaseCorrelated ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::UnitBaseCorrelated );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, Direct ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::Direct );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, UnitBase ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::UnitBase );

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a python interface for electron factory class templated functions
//---------------------------------------------------------------------------//
%define %cos_electron_function_interface_setup( FUNCTION )

// Set LogLogLog Functions
%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog , Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, UnitBaseCorrelated ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog , Utility::UnitBaseCorrelated );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Direct ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog , Utility::Direct );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, UnitBase ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog , Utility::UnitBase );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LogNudgedLogCosLog , Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, UnitBaseCorrelated ) ) FUNC_NAME( FUNCTION, Utility::LogNudgedLogCosLog , Utility::UnitBaseCorrelated );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Direct ) ) FUNC_NAME( FUNCTION, Utility::LogNudgedLogCosLog , Utility::Direct );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, UnitBase ) ) FUNC_NAME( FUNCTION, Utility::LogNudgedLogCosLog , Utility::UnitBase );

// Set LinLinLin Functions
%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, UnitBaseCorrelated ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::UnitBaseCorrelated );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, Direct ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::Direct );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, UnitBase ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::UnitBase );

// Set LinLinLog Functions
%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, UnitBaseCorrelated ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::UnitBaseCorrelated );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, Direct ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::Direct );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, UnitBase ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::UnitBase );

%enddef

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronTemplateHelpers.i
//---------------------------------------------------------------------------//
