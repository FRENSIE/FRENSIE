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
#define _FUNC_NAME_2_ARGS( func_base_name, arg_1, arg_2 ) MonteCarlo::create ## func_base_name<arg_1,arg_2>

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
// Helper macro for setting up a python interface for electron factory class templated functions
//---------------------------------------------------------------------------//
%define %electron_function_interface_setup( FUNCTION )

// Set LogLogLog Functions
%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LogLogLog, Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Exact ) ) FUNC_NAME( FUNCTION, Utility::LogLogLog, Utility::Exact );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Stochastic ) ) FUNC_NAME( FUNCTION, Utility::LogLogLog, Utility::Stochastic );

// Set LinLinLin Functions
%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, Exact ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::Exact );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, Stochastic ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::Stochastic );

// Set LinLinLog Functions
%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, Exact ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::Exact );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, Stochastic ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::Stochastic );

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a python interface for electron factory class templated functions
//---------------------------------------------------------------------------//
%define %cos_electron_function_interface_setup( FUNCTION )

// Set LogLogLog Functions
%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog, Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Exact ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog, Utility::Exact );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Stochastic ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog, Utility::Stochastic );

// Set LinLinLin Functions
%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, Exact ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::Exact );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLin, Stochastic ) ) FUNC_NAME( FUNCTION, Utility::LinLinLin, Utility::Stochastic );

// Set LinLinLog Functions
%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, Exact ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::Exact );

%template( FUNC_NEW_NAME( FUNCTION, LinLinLog, Stochastic ) ) FUNC_NAME( FUNCTION, Utility::LinLinLog, Utility::Stochastic );

%enddef

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronTemplateHelpers.i
//---------------------------------------------------------------------------//
