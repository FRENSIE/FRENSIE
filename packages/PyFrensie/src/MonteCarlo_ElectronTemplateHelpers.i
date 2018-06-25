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
%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog<false> , Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, UnitBaseCorrelated ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog<false> , Utility::UnitBaseCorrelated );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Direct ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog<false> , Utility::Direct );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, UnitBase ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog<false> , Utility::UnitBase );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Correlated ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog<true> , Utility::Correlated );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, UnitBaseCorrelated ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog<true> , Utility::UnitBaseCorrelated );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, Direct ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog<true> , Utility::Direct );

%template( FUNC_NEW_NAME( FUNCTION, LogLogLog, UnitBase ) ) FUNC_NAME( FUNCTION, Utility::LogLogCosLog<true> , Utility::UnitBase );

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
