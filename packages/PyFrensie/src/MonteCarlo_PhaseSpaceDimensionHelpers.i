//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimensionHelpers.i
//! \author Luke Kersting
//! \brief  The phase space dimension helper macros
//!
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
// Helper macros for getting the distribution name
//---------------------------------------------------------------------------//
// Get the name of a distribution that has 2 template parameters
// It must be included in both the interface file and the wrapper file since
// the preprocessor will have to parse it separately in both files
%{
#define _SPACE_DIST_NAME_2_ARGS( dist_base_name, arg_1, arg_2 ) MonteCarlo::dist_base_name ## PhaseSpaceDimensionDistribution<arg_1,arg_2>
%}
#define _SPACE_DIST_NAME_2_ARGS( dist_base_name, arg_1, arg_2 ) MonteCarlo::dist_base_name ## PhaseSpaceDimensionDistribution<arg_1,arg_2>

// Get the name of a distribution that has 1 template parameters
#define _SPACE_DIST_NAME_1_ARGS( dist_base_name, arg_1 ) MonteCarlo::dist_base_name ## PhaseSpaceDimensionDistribution<arg_1>

// Use Preprocessor Metaprogramming to get the distribution name
#define _GET_SPACE_DIST_NAME_MACRO( _1, _2, _3, NAME, ... ) NAME
#define SPACE_DIST_NAME( ... ) _GET_SPACE_DIST_NAME_MACRO(__VA_ARGS__, _SPACE_DIST_NAME_2_ARGS, _SPACE_DIST_NAME_1_ARGS)(__VA_ARGS__)


// Get the name of a distribution that has 3 template parameters
%{
#define _SPACE_DIST_RENAME_3_ARGS( dist_base_name, independent, dependent, arg3 ) arg3 ## independent ## dist_base_name ## dependent ## DimensionDistribution
%}
#define _SPACE_DIST_RENAME_3_ARGS( dist_base_name, independent, dependent, arg3 ) arg3 ## independent ## dist_base_name ## dependent ## DimensionDistribution

// Get the name of a distribution that has 2 template parameters
%{
#define _SPACE_DIST_RENAME_2_ARGS( dist_base_name, independent, dependent ) independent ## dist_base_name ## dependent ## DimensionDistribution
%}
#define _SPACE_DIST_RENAME_2_ARGS( dist_base_name, independent, dependent ) independent ## dist_base_name ## dependent ## DimensionDistribution

// Get the name of a distribution that has 1 template parameters
%{
#define _SPACE_DIST_RENAME_1_ARGS( dist_base_name, dimension ) dist_base_name ## dimension ## DimensionDistribution
%}
#define _SPACE_DIST_RENAME_1_ARGS( dist_base_name, dimension ) dist_base_name ## dimension ## DimensionDistribution

// Use Preprocessor Metaprogramming to get the distribution name
#define _GET_SPACE_DIST_RENAME_MACRO( _1, _2, _3, _4, NAME, ... ) NAME
#define SPACE_DIST_RENAME( ... ) _GET_SPACE_DIST_RENAME_MACRO(__VA_ARGS__, _SPACE_DIST_RENAME_3_ARGS, _SPACE_DIST_RENAME_2_ARGS, _SPACE_DIST_RENAME_1_ARGS)(__VA_ARGS__)

//---------------------------------------------------------------------------//
// Helper macro for setting up an IndependentPhaseSpaceDimensionDistribution class python interface
//---------------------------------------------------------------------------//
%define %independent_phase_space_dimension_setup_helper( DISTRIBUTION )

  // The DISTRIBUTION primary spatial phase space dimension distribution
  %template( SPACE_DIST_RENAME(DISTRIBUTION, PrimarySpatial) ) SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::PRIMARY_SPATIAL_DIMENSION);

  // The DISTRIBUTION secondary spatial phase space dimension distribution
  %template( SPACE_DIST_RENAME(DISTRIBUTION, SecondarySpatial) ) SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::SECONDARY_SPATIAL_DIMENSION);

  // The DISTRIBUTION tertiary spatial phase space dimension distribution
  %template( SPACE_DIST_RENAME(DISTRIBUTION, TertiarySpatial) ) SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::TERTIARY_SPATIAL_DIMENSION);

  // The DISTRIBUTION primary directional phase space dimension distribution
  %template( SPACE_DIST_RENAME(DISTRIBUTION, PrimaryDirectional) ) SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION);

  // The DISTRIBUTION secondary directional phase space dimension distribution
  %template( SPACE_DIST_RENAME(DISTRIBUTION, SecondaryDirectional) ) SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION);

  // The DISTRIBUTION tertiary directional phase space dimension distribution
  %template( SPACE_DIST_RENAME(DISTRIBUTION, TertiaryDirectional) ) SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION);

  // The DISTRIBUTION energy phase space dimension distribution
  %template( SPACE_DIST_RENAME(DISTRIBUTION, Energy) ) SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::ENERGY_DIMENSION);

  // The DISTRIBUTION time phase space dimension distribution
  %template( SPACE_DIST_RENAME(DISTRIBUTION, Time) ) SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::TIME_DIMENSION);

  // The DISTRIBUTION weight phase space dimension distribution
  %template( SPACE_DIST_RENAME(DISTRIBUTION, Weight) ) SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::WEIGHT_DIMENSION);

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a generic dependent class python interface
//---------------------------------------------------------------------------//
%define %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, INDEPENDENT, INDEPENDENT_TYPE, PARAMS... )

  %inline %{
  typedef SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::INDEPENDENT_TYPE ## _DIMENSION, MonteCarlo::DEPENDENT_TYPE ## _DIMENSION) SPACE_DIST_RENAME( Dependent, INDEPENDENT, DEPENDENT, PARAMS );
  %}

  %shared_ptr( SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::INDEPENDENT_TYPE ## _DIMENSION, MonteCarlo::DEPENDENT_TYPE ## _DIMENSION) );

  // The DISTRIBUTION INDEPENDENT dependent DEPENDENT dimension distribution
  %template(SPACE_DIST_RENAME( Dependent, INDEPENDENT, DEPENDENT, PARAMS ) ) SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::INDEPENDENT_TYPE ## _DIMENSION, MonteCarlo::DEPENDENT_TYPE ## _DIMENSION);

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up spatial dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, PARAMS... )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, PrimarySpatial, PRIMARY_SPATIAL, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, SecondarySpatial, SECONDARY_SPATIAL, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, TertiarySpatial, TERTIARY_SPATIAL, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up directional dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, PARAMS... )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, PrimaryDirectional, PRIMARY_DIRECTIONAL, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, SecondaryDirectional, SECONDARY_DIRECTIONAL, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, TertiaryDirectional, TERTIARY_DIRECTIONAL, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up other dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, PARAMS... )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, Energy, ENERGY, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, Time, TIME, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT, DEPENDENT_TYPE, Weight, WEIGHT, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up primary spatial dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %primary_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS... )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PrimarySpatial, PRIMARY_SPATIAL, SecondarySpatial, SECONDARY_SPATIAL, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PrimarySpatial, PRIMARY_SPATIAL, TertiarySpatial, TERTIARY_SPATIAL, PARAMS )

  %directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PrimarySpatial, PRIMARY_SPATIAL, PARAMS )

  %other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PrimarySpatial, PRIMARY_SPATIAL, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up secondary spatial dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %secondary_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS... )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SecondarySpatial, SECONDARY_SPATIAL, PrimarySpatial, PRIMARY_SPATIAL, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SecondarySpatial, SECONDARY_SPATIAL, TertiarySpatial, TERTIARY_SPATIAL, PARAMS )

  %directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SecondarySpatial, SECONDARY_SPATIAL, PARAMS )

  %other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SecondarySpatial, SECONDARY_SPATIAL, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up tertiary spatial dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %tertiary_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS... )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TertiarySpatial, TERTIARY_SPATIAL, PrimarySpatial, PRIMARY_SPATIAL, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TertiarySpatial, TERTIARY_SPATIAL, SecondarySpatial, SECONDARY_SPATIAL, PARAMS )

  %directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TertiarySpatial, TERTIARY_SPATIAL, PARAMS )

  %other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TertiarySpatial, TERTIARY_SPATIAL, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up primary directional dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %primary_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS... )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PrimaryDirectional, PRIMARY_DIRECTIONAL, SecondaryDirectional, SECONDARY_DIRECTIONAL, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PrimaryDirectional, PRIMARY_DIRECTIONAL, TertiaryDirectional, TERTIARY_DIRECTIONAL, PARAMS )

  %spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PrimaryDirectional, PRIMARY_DIRECTIONAL, PARAMS )

  %other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PrimaryDirectional, PRIMARY_DIRECTIONAL, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up secondary directional dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %secondary_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS... )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SecondaryDirectional, SECONDARY_DIRECTIONAL, PrimaryDirectional, PRIMARY_DIRECTIONAL, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SecondaryDirectional, SECONDARY_DIRECTIONAL, TertiaryDirectional, TERTIARY_DIRECTIONAL, PARAMS )

  %spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SecondaryDirectional, SECONDARY_DIRECTIONAL, PARAMS )

  %other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SecondaryDirectional, SECONDARY_DIRECTIONAL, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up tertiary directional dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %tertiary_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS... )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TertiaryDirectional, TERTIARY_DIRECTIONAL, PrimaryDirectional, PRIMARY_DIRECTIONAL, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TertiaryDirectional, TERTIARY_DIRECTIONAL, SecondaryDirectional, SECONDARY_DIRECTIONAL, PARAMS )

  %spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TertiaryDirectional, TERTIARY_DIRECTIONAL, PARAMS )

  %other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TertiaryDirectional, TERTIARY_DIRECTIONAL, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up energy dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %energy_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS... )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, Energy, ENERGY, Time, TIME, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, Energy, ENERGY, Weight, WEIGHT, PARAMS )

  %spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, Energy, ENERGY, PARAMS )

  %directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, Energy, ENERGY, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up time dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %time_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS... )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, Time, TIME, Energy, ENERGY, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, Time, TIME, Weight, WEIGHT, PARAMS )

  %spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, Time, TIME, PARAMS )

  %directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, Time, TIME, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up weight dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %weight_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS... )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, Weight, WEIGHT, Energy, ENERGY, PARAMS )

  %generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, Weight, WEIGHT, Time, TIME, PARAMS )

  %spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, Weight, WEIGHT, PARAMS )

  %directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, Weight, WEIGHT, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS... )

  %primary_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS )
  %secondary_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS )
  %tertiary_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS )

  %primary_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS )
  %secondary_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS)
  %tertiary_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS )

  %energy_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS )
  %time_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS )
  %weight_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PARAMS )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a (pre) generic dependent class python interface
//---------------------------------------------------------------------------//
%define %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE, INDEPENDENT_TYPE )

  %apply unsigned long long& INOUT { SPACE_DIST_NAME(DISTRIBUTION, MonteCarlo::INDEPENDENT_TYPE ## _DIMENSION, MonteCarlo::DEPENDENT_TYPE ## _DIMENSION)::Counter& trials };

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up spatial dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE, PRIMARY_SPATIAL )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE, SECONDARY_SPATIAL )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE, TERTIARY_SPATIAL )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up directional dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE, PRIMARY_DIRECTIONAL )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE, SECONDARY_DIRECTIONAL )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE, TERTIARY_DIRECTIONAL )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up other dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE, ENERGY )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE, TIME )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DEPENDENT_TYPE, WEIGHT )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up primary spatial dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_primary_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PRIMARY_SPATIAL, SECONDARY_SPATIAL )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PRIMARY_SPATIAL, TERTIARY_SPATIAL )

  %pre_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PRIMARY_SPATIAL )

  %pre_other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PRIMARY_SPATIAL )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up secondary spatial dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_secondary_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SECONDARY_SPATIAL, PRIMARY_SPATIAL )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SECONDARY_SPATIAL, TERTIARY_SPATIAL )

  %pre_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SECONDARY_SPATIAL )

  %pre_other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SECONDARY_SPATIAL )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up tertiary spatial dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_tertiary_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TERTIARY_SPATIAL, PRIMARY_SPATIAL )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TERTIARY_SPATIAL, SECONDARY_SPATIAL )

  %pre_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TERTIARY_SPATIAL )

  %pre_other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TERTIARY_SPATIAL )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up primary directional dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_primary_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PRIMARY_DIRECTIONAL, SECONDARY_DIRECTIONAL )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PRIMARY_DIRECTIONAL, TERTIARY_DIRECTIONAL )

  %pre_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PRIMARY_DIRECTIONAL )

  %pre_other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, PRIMARY_DIRECTIONAL )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up secondary directional dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_secondary_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SECONDARY_DIRECTIONAL, PRIMARY_DIRECTIONAL )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SECONDARY_DIRECTIONAL, TERTIARY_DIRECTIONAL )

  %pre_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SECONDARY_DIRECTIONAL )

  %pre_other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, SECONDARY_DIRECTIONAL )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up tertiary directional dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_tertiary_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TERTIARY_DIRECTIONAL, PRIMARY_DIRECTIONAL )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TERTIARY_DIRECTIONAL, SECONDARY_DIRECTIONAL )

  %pre_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TERTIARY_DIRECTIONAL )

  %pre_other_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TERTIARY_DIRECTIONAL )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up energy dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_energy_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, ENERGY, TIME )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, ENERGY, WEIGHT )

  %pre_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, ENERGY )

  %pre_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, ENERGY )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up time dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_time_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TIME, ENERGY )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TIME, WEIGHT )

  %pre_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TIME )

  %pre_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, TIME )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up weight dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_weight_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, WEIGHT, ENERGY )

  %pre_generic_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, WEIGHT, TIME )

  %pre_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, WEIGHT )

  %pre_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION, WEIGHT )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a dependent distribution classes python interface
//---------------------------------------------------------------------------//

%define %pre_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

  %pre_primary_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )
  %pre_secondary_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )
  %pre_tertiary_spatial_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

  %pre_primary_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )
  %pre_secondary_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION)
  %pre_tertiary_directional_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

  %pre_energy_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )
  %pre_time_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )
  %pre_weight_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up an independent distribution class python interface
//---------------------------------------------------------------------------//
%define %independent_phase_space_dimension_setup( DISTRIBUTION )

%independent_phase_space_dimension_setup_helper( DISTRIBUTION )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a basic dependent distribution class python interface
//---------------------------------------------------------------------------//

%define %basic_dependent_phase_space_dimension_setup( DISTRIBUTION )

  %dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up an advanced dependent distribution class python interface
//---------------------------------------------------------------------------//

%define %advanced_dependent_phase_space_dimension_setup( DISTRIBUTION, DISTRIBUTION_BASE )

  %dependent_phase_space_dimension_setup_helper( DISTRIBUTION, DISTRIBUTION_BASE )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up a pre dependent distribution class python interface
//---------------------------------------------------------------------------//

%define %pre_dependent_phase_space_dimension_setup( DISTRIBUTION )

  %pre_dependent_phase_space_dimension_setup_helper( DISTRIBUTION )

%enddef


//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionHelpers.i
//---------------------------------------------------------------------------//
