//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventHelpers.i
//! \author Luke Kersting
//! \brief  The MonteCarlo event module helper macros
//!
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
// Helper macro for the pre-include event module class python interface
//---------------------------------------------------------------------------//
%define %pre_template_setup_helper( NAME, RENAME )

// Set typedef
%inline %{ typedef MonteCarlo::NAME RENAME; %}

// Set shared_ptr
%shared_ptr( MonteCarlo::NAME )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for the post-include event module class python interface
//---------------------------------------------------------------------------//
%define %post_template_setup_helper( NAME, RENAME )

// Set template
%template( RENAME ) MonteCarlo::NAME;

%enddef

//---------------------------------------------------------------------------//
// Helper macro for the pre-include dimesion discretization class python interface
//---------------------------------------------------------------------------//
%define %pre_dimesion_discretization_setup_helper( BASE, TEMPLATE, DIMENSION )

// Set pre-include for the dimension
%pre_template_setup_helper( BASE ## PhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ ## TEMPLATE ## _DIMENSION>, BASE ## DIMENSION ## DimensionDiscretization )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for the post-include dimesion discretization class python interface
//---------------------------------------------------------------------------//
%define %post_dimesion_discretization_setup_helper( BASE, TEMPLATE, DIMENSION )

// Set pre-include for the dimension
%post_template_setup_helper( BASE ## PhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ ## TEMPLATE ## _DIMENSION>, BASE ## DIMENSION ## DimensionDiscretization )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up all the pre-include for the default typed classes
//---------------------------------------------------------------------------//
%define %pre_default_typed_setup_helper( BASE, TEMPLATE, DIMENSION, DATA_TYPE )

// Add typemaps for converting InputDataType from Python list
%apply const std::vector<DATA_TYPE>& { const MonteCarlo::BASE ## PhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ ## TEMPLATE ## _DIMENSION>::InputDataType& }

  // // Add typemaps for converting InputDataType from Python list
  // %typemap(in) const MonteCarlo::BASE ## PhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ ## TEMPLATE ## _DIMENSION>::InputDataType& ( std::vector<DATA_TYPE> temp ){
  //   temp = PyFrensie::convertFromPython<std::vector<DATA_TYPE> >( $input );

  //   $1 = &temp;
  // }

  // %typemap(typecheck, precedence=1090) (const MonteCarlo::BASE ## PhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ ## TEMPLATE ## _DIMENSION>::InputDataType&) {
  //   $1 = (PyArray_Check($input) || PySequence_Check($input)) ? 1 : 0;
  // }

%pre_template_setup_helper( BASE ## PhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ ## TEMPLATE ## _DIMENSION>, Observer ## DIMENSION ## DimensionDiscretization)

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up all the post-include for the default typed classes
//---------------------------------------------------------------------------//
%define %post_default_typed_setup_helper( BASE, TEMPLATE, DIMENSION )

%post_template_setup_helper( BASE ## PhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ ## TEMPLATE ## _DIMENSION>, Observer ## DIMENSION ## DimensionDiscretization)

%enddef

//---------------------------------------------------------------------------//
// Macro for ignoring the default constructor of the class
//---------------------------------------------------------------------------//
%define %ignore_default_constructor( NAME )

%ignore MonteCarlo::NAME::NAME();

%enddef

//---------------------------------------------------------------------------//
// Macro for extending the class functions using boost::any
//---------------------------------------------------------------------------//
%define %extend_boost_any_functions( TEMPLATE, TYPE )

%extend MonteCarlo::TypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ ## TEMPLATE ## _DIMENSION>
{
  // Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue( const TYPE value,
                                   BinIndexArray& bin_indices ) const
  {
    // Cast value to boost::any
    auto any_value = boost::any((MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_ ## TEMPLATE ## _DIMENSION>::dimensionType) value);

    // Call class function
    $self->calculateBinIndicesOfValue( any_value, bin_indices );
  }

  // Check if the value is contained in the discretization
  bool isValueInDiscretization( const TYPE value ) const
  {
    // Cast value to boost::any
    auto any_value = boost::any((MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_ ## TEMPLATE ## _DIMENSION>::dimensionType) value);

    // Call class function
    return $self->isValueInDiscretization( any_value );
  }
};

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the pre-include python interface
//---------------------------------------------------------------------------//
%define %pre_all_dimesion_discretization_setup( BASE )

%pre_dimesion_discretization_setup_helper( BASE, COSINE, Cosine)
%pre_dimesion_discretization_setup_helper( BASE, SOURCE_ENERGY, SourceEnergy)
%pre_dimesion_discretization_setup_helper( BASE, ENERGY, Energy)
%pre_dimesion_discretization_setup_helper( BASE, SOURCE_TIME, SourceTime)
%pre_dimesion_discretization_setup_helper( BASE, TIME, Time)
%pre_dimesion_discretization_setup_helper( BASE, COLLISION_NUMBER, CollisionNumber)
%pre_dimesion_discretization_setup_helper( BASE, SOURCE_ID, SourceId)

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the post-include python interface
//---------------------------------------------------------------------------//
%define %post_all_dimesion_discretization_setup( BASE )

%post_dimesion_discretization_setup_helper( BASE, COSINE, Cosine)
%post_dimesion_discretization_setup_helper( BASE, SOURCE_ENERGY, SourceEnergy)
%post_dimesion_discretization_setup_helper( BASE, ENERGY, Energy)
%post_dimesion_discretization_setup_helper( BASE, SOURCE_TIME, SourceTime)
%post_dimesion_discretization_setup_helper( BASE, TIME, Time)
%post_dimesion_discretization_setup_helper( BASE, COLLISION_NUMBER, CollisionNumber)
%post_dimesion_discretization_setup_helper( BASE, SOURCE_ID, SourceId)

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the pre-include for the floating point class
//---------------------------------------------------------------------------//
%define %pre_floating_point_setup( BASE )

// Ignore the default constructor
%ignore_default_constructor( BASE ## PhaseSpaceDimensionDiscretization )

// Set up the dimensions
%pre_dimesion_discretization_setup_helper( BASE, COSINE, Cosine)
%pre_dimesion_discretization_setup_helper( BASE, SOURCE_ENERGY, SourceEnergy)
%pre_dimesion_discretization_setup_helper( BASE, ENERGY, Energy)
%pre_dimesion_discretization_setup_helper( BASE, SOURCE_TIME, SourceTime)
%pre_dimesion_discretization_setup_helper( BASE, TIME, Time)

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the post-include for the floating point class
//---------------------------------------------------------------------------//
%define %post_floating_point_setup( BASE )

// Set up the dimensions
%post_dimesion_discretization_setup_helper( BASE, COSINE, Cosine)
%post_dimesion_discretization_setup_helper( BASE, SOURCE_ENERGY, SourceEnergy)
%post_dimesion_discretization_setup_helper( BASE, ENERGY, Energy)
%post_dimesion_discretization_setup_helper( BASE, SOURCE_TIME, SourceTime)
%post_dimesion_discretization_setup_helper( BASE, TIME, Time)

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the pre-include for the hashed floating point class
//---------------------------------------------------------------------------//
%define %pre_hashed_floating_point_setup( BASE )
// Ignore the default constructor
%ignore_default_constructor( BASE ## PhaseSpaceDimensionDiscretization )

// Set up the dimensions
%pre_dimesion_discretization_setup_helper( BASE, SOURCE_ENERGY, SourceEnergy)
%pre_dimesion_discretization_setup_helper( BASE, ENERGY, Energy)
%pre_dimesion_discretization_setup_helper( BASE, SOURCE_TIME, SourceTime)
%pre_dimesion_discretization_setup_helper( BASE, TIME, Time)

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the post-include for the hashed floating point class
//---------------------------------------------------------------------------//
%define %post_hashed_floating_point_setup( BASE )

// Set up the dimensions
%post_dimesion_discretization_setup_helper( BASE, SOURCE_ENERGY, SourceEnergy)
%post_dimesion_discretization_setup_helper( BASE, ENERGY, Energy)
%post_dimesion_discretization_setup_helper( BASE, SOURCE_TIME, SourceTime)
%post_dimesion_discretization_setup_helper( BASE, TIME, Time)

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the pre-include for the integral class
//---------------------------------------------------------------------------//
%define %pre_integral_setup( BASE )

// Ignore the default constructor
%ignore_default_constructor( BASE ## PhaseSpaceDimensionDiscretization )

// Set up the dimensions
%pre_dimesion_discretization_setup_helper( BASE, COLLISION_NUMBER, CollisionNumber)

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the post-include for the integral class
//---------------------------------------------------------------------------//
%define %post_integral_setup( BASE )

// Set up the dimensions
%post_dimesion_discretization_setup_helper( BASE, COLLISION_NUMBER, CollisionNumber)

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the pre-include for the unordered class
//---------------------------------------------------------------------------//
%define %pre_unordered_setup( BASE )

// Ignore the default constructor
%ignore_default_constructor( BASE ## PhaseSpaceDimensionDiscretization )

// Set up the dimensions
%pre_dimesion_discretization_setup_helper( BASE, SOURCE_ID, SourceId)

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the post-include for the unordered class
//---------------------------------------------------------------------------//
%define %post_unordered_setup( BASE )

// Set up the dimensions
%post_dimesion_discretization_setup_helper( BASE, SOURCE_ID, SourceId)

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the pre-include for the default typed classes
//---------------------------------------------------------------------------//
%define %pre_default_typed_setup( BASE )

// Ignore the default constructor
%ignore_default_constructor( BASE ## PhaseSpaceDimensionDiscretization )

// Set up the dimensions
%pre_default_typed_setup_helper( BASE, COSINE, Cosine, double )
%pre_default_typed_setup_helper( BASE, SOURCE_ENERGY, SourceEnergy, double)
%pre_default_typed_setup_helper( BASE, ENERGY, Energy, double)
%pre_default_typed_setup_helper( BASE, SOURCE_TIME, SourceTime, double)
%pre_default_typed_setup_helper( BASE, TIME, Time, double)
%pre_default_typed_setup_helper( BASE, COLLISION_NUMBER, CollisionNumber, unsigned)
%pre_default_typed_setup_helper( BASE, SOURCE_ID, SourceId, std::set<unsigned>)

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the post-include python interface
//---------------------------------------------------------------------------//
%define %post_default_typed_setup( BASE )

// Set up the dimensions
%post_default_typed_setup_helper( BASE, COSINE, Cosine)
%post_default_typed_setup_helper( BASE, SOURCE_ENERGY, SourceEnergy)
%post_default_typed_setup_helper( BASE, ENERGY, Energy)
%post_default_typed_setup_helper( BASE, SOURCE_TIME, SourceTime)
%post_default_typed_setup_helper( BASE, TIME, Time)
%post_default_typed_setup_helper( BASE, COLLISION_NUMBER, CollisionNumber)
%post_default_typed_setup_helper( BASE, SOURCE_ID, SourceId)

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up all the post-include for the default typed classes
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHelpers.i
//---------------------------------------------------------------------------//
