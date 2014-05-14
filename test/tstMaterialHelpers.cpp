//---------------------------------------------------------------------------//
//!
//! \file   tstMaterialHelpers.cpp
//! \author Alex Robinson
//! \brief  Material helper function unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ArrayView.hpp>

// FACEMC Includes
#include "MaterialHelpers.hpp"
#include "Tuple.hpp"
#include "TupleMemberTraits.hpp"
#include "FACEMC_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Instantiation macros.
//---------------------------------------------------------------------------//
#define TUPLE_TYPEDEFS()			\
  typedef FACEMC::Pair<double,double> pair_d_d;			\
  typedef FACEMC::Pair<double,unsigned> pair_d_u;			\
  typedef FACEMC::Trip<double,double,double> trip_d_d_d;		\
  typedef FACEMC::Trip<unsigned,double,double> trip_u_d_d;		\
  typedef FACEMC::Quad<double,double,double,double> quad_d_d_d_d;	\
  typedef FACEMC::Quad<unsigned,unsigned,double,double> quad_u_u_d_d;	\
  
#define UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_ARRAY( type, name, array ) \
  TUPLE_TYPEDEFS()							\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    pair_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    pair_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    trip_d_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    trip_u_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    trip_d_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    quad_d_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    quad_d_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    quad_u_u_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    quad_u_u_d_d, \
							    array )	\

#define UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_ARRAY( type, name, array ) \
  TUPLE_TYPEDEFS()							\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    SECOND,	\
							    pair_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    FIRST,	\
							    pair_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    SECOND,	\
							    trip_d_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    THIRD,	\
							    trip_u_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    FIRST,	\
							    trip_d_d_d,	\
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FIRST,	\
							    SECOND,	\
							    quad_d_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    SECOND,	\
							    THIRD,	\
							    quad_d_d_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    THIRD,	\
							    FOURTH,	\
							    quad_u_u_d_d, \
							    array )	\
  FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_INSTANT( type,	\
							    name,	\
							    FOURTH,	\
							    THIRD,	\
							    quad_u_u_d_d, \
							    array )	\

#define UNIT_TEST_INSTANTIATION_ARRAY( type, name, array )		\
  FACEMC_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_INSTANT( type, name, double, array ) \

//---------------------------------------------------------------------------//
// Helper functions.
//---------------------------------------------------------------------------//
template<FACEMC::TupleMember member,
	 typename T,
	 template<typename> class Array>
void fillWeightFractions( Array<T>& array )
{
  FACEMC::set<member>( array[0], -0.25 );
  FACEMC::set<member>( array[1], -0.25 );
  FACEMC::set<member>( array[2], -0.25 );
  FACEMC::set<member>( array[3], -0.25 );
}

template<FACEMC::TupleMember member,
	 typename T,
	 template<typename> class Array>
void fillAtomicWeights( Array<T>& array )
{
  FACEMC::set<member>( array[0], 10.0 );
  FACEMC::set<member>( array[1], 20.0 );
  FACEMC::set<member>( array[2], 30.0 );
  FACEMC::set<member>( array[3], 40.0 );
}

template<FACEMC::TupleMember member,
	 typename T,
	 template<typename> class Array>
void fillReferenceAtomFractions( Array<T>& array )
{
  FACEMC::set<member>( array[0], 12.0/25.0 );
  FACEMC::set<member>( array[1], 6.0/25.0 );
  FACEMC::set<member>( array[2], 4.0/25.0 );
  FACEMC::set<member>( array[3], 3.0/25.0 );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that fractional values can be tested as valid
FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL( MaterialHelpers,
						       areFractionValuesValid,
						       member,
						       type,
						       array )
{
  // Test weight fractions
  array<type> weight_fractions( 4 );
  fillWeightFractions<member>( weight_fractions );

  TEST_ASSERT( FACEMC::areFractionValuesValid<member>( 
					            weight_fractions.begin(),
					            weight_fractions.end() ) );

  FACEMC::set<member>( weight_fractions[0], 
		       -1.0*FACEMC::get<member>( weight_fractions[0] ) );

  TEST_ASSERT( !FACEMC::areFractionValuesValid<member>( 
					            weight_fractions.begin(),
					            weight_fractions.end() ) );

  weight_fractions.clear();

  // Test atom fractions
  array<type> atom_fractions( 4 );
  fillReferenceAtomFractions<member>( atom_fractions );

  TEST_ASSERT( FACEMC::areFractionValuesValid<member>( 
					              atom_fractions.begin(),
					              atom_fractions.end() ) );

  FACEMC::set<member>( atom_fractions[0], 
		       -1.0*FACEMC::get<member>( atom_fractions[0] ) );

  TEST_ASSERT( !FACEMC::areFractionValuesValid<member>( 
					              atom_fractions.begin(),
					              atom_fractions.end() ) );

}

UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_ARRAY( MaterialHelpers,
					      areFractionValuesValid,
					      Array );
UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_ARRAY( MaterialHelpers,
					      areFractionValuesValid,
					      ArrayRCP );

//---------------------------------------------------------------------------//
// Check that fractional values can be tested as valid
FACEMC_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_DECL( MaterialHelpers,
					     areFractionValuesValid_basic,
					     type,
					     array )
{
  // Test weight fractions
  array<type> weight_fractions( 4 );
  fillWeightFractions<FACEMC::FIRST>( weight_fractions );

  TEST_ASSERT( FACEMC::areFractionValuesValid( weight_fractions.begin(),
					       weight_fractions.end() ) );

  weight_fractions[0] *= -1.0;
  
  TEST_ASSERT( !FACEMC::areFractionValuesValid( weight_fractions.begin(),
						weight_fractions.end() ) );

  weight_fractions.clear();

  // Test atom fractions
  array<type> atom_fractions( 4 );
  fillReferenceAtomFractions<FACEMC::FIRST>( atom_fractions );

  TEST_ASSERT( FACEMC::areFractionValuesValid( atom_fractions.begin(),
					       atom_fractions.end() ) );

  atom_fractions[0] *= -1.0;

  TEST_ASSERT( !FACEMC::areFractionValuesValid( atom_fractions.begin(),
						atom_fractions.end() ) );
}

UNIT_TEST_INSTANTIATION_ARRAY( MaterialHelpers,
			       areFractionValuesValid_basic,
			       Array );
UNIT_TEST_INSTANTIATION_ARRAY( MaterialHelpers,
			       areFractionValuesValid_basic,
			       ArrayRCP );

//---------------------------------------------------------------------------//
// Check that fractional values can be tested as normalized
FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL( 
						   MaterialHelpers,
						   areFractionValuesNormalized,
						   member,
						   type,
						   array )
{
  // Test weight fractions
  array<type> weight_fractions( 4 );
  fillWeightFractions<member>( weight_fractions );

  TEST_ASSERT( FACEMC::areFractionValuesNormalized<member>( 
						    weight_fractions.begin(),
						    weight_fractions.end() ) );

  FACEMC::set<member>( weight_fractions[0], 
		       2.0*FACEMC::get<member>( weight_fractions[0] ) );

  TEST_ASSERT( !FACEMC::areFractionValuesNormalized<member>(
						    weight_fractions.begin(),
						    weight_fractions.end() ) );
  weight_fractions.clear();
  
  // Test atom fractions
  array<type> atom_fractions( 4 );
  fillReferenceAtomFractions<member>( atom_fractions );

  TEST_ASSERT( FACEMC::areFractionValuesNormalized<member>( 
					              atom_fractions.begin(),
					              atom_fractions.end() ) );

  FACEMC::set<member>( atom_fractions[0], 
		       2.0*FACEMC::get<member>( atom_fractions[0] ) );

  TEST_ASSERT( !FACEMC::areFractionValuesNormalized<member>( 
					              atom_fractions.begin(),
					              atom_fractions.end() ) );
}

UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_ARRAY( MaterialHelpers,
					      areFractionValuesNormalized,
					      Array );
UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_ARRAY( MaterialHelpers,
					      areFractionValuesNormalized,
					      ArrayRCP );

//---------------------------------------------------------------------------//
// Check that fractional values can be tested as normalized
FACEMC_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_DECL( MaterialHelpers,
					     areFractionValuesNormalized_basic,
					     type,
					     array )
{
  // Test weight fractions
  array<type> weight_fractions( 4 );
  fillWeightFractions<FACEMC::FIRST>( weight_fractions );

  TEST_ASSERT( FACEMC::areFractionValuesNormalized( weight_fractions.begin(),
						    weight_fractions.end() ) );

  weight_fractions[0] *= 2.0;
  
  TEST_ASSERT( !FACEMC::areFractionValuesNormalized(weight_fractions.begin(),
						    weight_fractions.end() ) );

  weight_fractions.clear();

  // Test atom fractions
  array<type> atom_fractions( 4 );
  fillReferenceAtomFractions<FACEMC::FIRST>( atom_fractions );

  TEST_ASSERT( FACEMC::areFractionValuesNormalized( atom_fractions.begin(),
						    atom_fractions.end() ) );

  atom_fractions[0] *= -1.0;

  TEST_ASSERT( !FACEMC::areFractionValuesNormalized( atom_fractions.begin(),
						     atom_fractions.end() ) );
}

UNIT_TEST_INSTANTIATION_ARRAY( MaterialHelpers,
			       areFractionValuesNormalized_basic,
			       Array );
UNIT_TEST_INSTANTIATION_ARRAY( MaterialHelpers,
			       areFractionValuesNormalized_basic,
			       ArrayRCP );

//---------------------------------------------------------------------------//
// Check that a set of fractional values can be normalized
FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL( 
						   MaterialHelpers,
						   normalizeFractionValues,
						   member,
						   type,
						   array )
{
  // Test weight fractions
  array<type> weight_fractions( 4 );
  fillWeightFractions<member>( weight_fractions );

  FACEMC::set<member>( weight_fractions[0], 
		       2.0*FACEMC::get<member>( weight_fractions[0] ) );

  FACEMC::normalizeFractionValues<member>( weight_fractions.begin(),
					   weight_fractions.end() );

  TEST_ASSERT( FACEMC::areFractionValuesNormalized<member>( 
						    weight_fractions.begin(),
						    weight_fractions.end() ) );
  TEST_EQUALITY_CONST( FACEMC::get<member>( weight_fractions[0] ), -0.4 );
  TEST_EQUALITY_CONST( FACEMC::get<member>( weight_fractions[1] ), -0.2 );
  TEST_EQUALITY_CONST( FACEMC::get<member>( weight_fractions[2] ), -0.2 );
  TEST_EQUALITY_CONST( FACEMC::get<member>( weight_fractions[3] ), -0.2 );

  weight_fractions.clear();
  
  // Test atom fractions
  array<type> atom_fractions( 4 );
  fillReferenceAtomFractions<member>( atom_fractions );

  FACEMC::set<member>( atom_fractions[0], 
		       2.0*FACEMC::get<member>( atom_fractions[0] ) );

  FACEMC::normalizeFractionValues<member>( atom_fractions.begin(),
					   atom_fractions.end() );

  TEST_ASSERT( FACEMC::areFractionValuesNormalized<member>( 
					              atom_fractions.begin(),
					              atom_fractions.end() ) );
  TEST_EQUALITY_CONST( FACEMC::get<member>( atom_fractions[0] ), 24.0/37 );
  TEST_EQUALITY_CONST( FACEMC::get<member>( atom_fractions[1] ), 6.0/37 );
  TEST_EQUALITY_CONST( FACEMC::get<member>( atom_fractions[2] ), 4.0/37 );
  TEST_EQUALITY_CONST( FACEMC::get<member>( atom_fractions[3] ), 3.0/37 );
}

UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_ARRAY( MaterialHelpers,
					      normalizeFractionValues,
					      Array );
UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_ARRAY( MaterialHelpers,
					      normalizeFractionValues,
					      ArrayRCP );

//---------------------------------------------------------------------------//
// Check that a set of fractional values can be normalized
FACEMC_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_DECL( MaterialHelpers,
					     normalizeFractionValues_basic,
					     type,
					     array )
{
  // Test weight fractions
  array<type> weight_fractions( 4 );
  fillWeightFractions<FACEMC::FIRST>( weight_fractions );

  weight_fractions[0] *= 2.0;

  FACEMC::normalizeFractionValues( weight_fractions.begin(),
				   weight_fractions.end() );

  TEST_ASSERT( FACEMC::areFractionValuesNormalized( weight_fractions.begin(),
						    weight_fractions.end() ) );
  TEST_EQUALITY_CONST( weight_fractions[0], -0.4 );
  TEST_EQUALITY_CONST( weight_fractions[1], -0.2 );
  TEST_EQUALITY_CONST( weight_fractions[2], -0.2 );
  TEST_EQUALITY_CONST( weight_fractions[3], -0.2 );

  weight_fractions.clear();
  
  // Test atom fractions
  array<type> atom_fractions( 4 );
  fillReferenceAtomFractions<FACEMC::FIRST>( atom_fractions );

  atom_fractions[0] *= 2.0;

  FACEMC::normalizeFractionValues( atom_fractions.begin(),
				   atom_fractions.end() );

  TEST_ASSERT( FACEMC::areFractionValuesNormalized( atom_fractions.begin(),
						    atom_fractions.end() ) );
  TEST_EQUALITY_CONST( atom_fractions[0], 24.0/37 );
  TEST_EQUALITY_CONST( atom_fractions[1], 6.0/37 );
  TEST_EQUALITY_CONST( atom_fractions[2], 4.0/37 );
  TEST_EQUALITY_CONST( atom_fractions[3], 3.0/37 );
}

UNIT_TEST_INSTANTIATION_ARRAY( MaterialHelpers,
			       normalizeFractionValues_basic,
			       Array );
UNIT_TEST_INSTANTIATION_ARRAY( MaterialHelpers,
			       normalizeFractionValues_basic,
			       ArrayRCP );

//---------------------------------------------------------------------------//
// Check that weight fractions can be converted to atom fractions
FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_DECL( 
					 MaterialHelpers,
					 convertWeightFractionsToAtomFractions,
					 fracMember,
					 atomicWgtMember,
					 type,
					 array )
{
  array<type> fraction_data( 4 );
  fillWeightFractions<fracMember>( fraction_data );
  fillAtomicWeights<atomicWgtMember>( fraction_data );

  FACEMC::convertWeightFractionsToAtomFractions<fracMember,atomicWgtMember>( 
							fraction_data.begin(),
							fraction_data.end(),
							fraction_data.begin(),
							fraction_data.end() ); 

  array<type> ref_fraction_data( 4 );
  fillReferenceAtomFractions<fracMember>( ref_fraction_data );
  fillAtomicWeights<atomicWgtMember>( ref_fraction_data );

  FACEMC_TEST_COMPARE_ARRAYS( fraction_data, ref_fraction_data );
}

UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_ARRAY( 
					 MaterialHelpers,
					 convertWeightFractionsToAtomFractions,
					 Array );
UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_ARRAY( 
					 MaterialHelpers,
					 convertWeightFractionsToAtomFractions,
					 ArrayRCP );

//---------------------------------------------------------------------------//
// Check that weight fractions can be converted to atom fractions
FACEMC_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_DECL(
				   MaterialHelpers,
				   convertWeightFractionsToAtomFractions_basic,
				   type,
				   array )
{
  array<type> fractions( 4 );
  array<type> weights( 4 );
  fillWeightFractions<FACEMC::FIRST>( fractions );
  fillAtomicWeights<FACEMC::FIRST>( weights );

  FACEMC::convertWeightFractionsToAtomFractions( fractions.begin(),
						 fractions.end(),
						 weights.begin(),
						 weights.end() );
  
  array<type> ref_fractions( 4 );
  fillReferenceAtomFractions<FACEMC::FIRST>( ref_fractions );

  FACEMC_TEST_COMPARE_ARRAYS( fractions, ref_fractions );
}

UNIT_TEST_INSTANTIATION_ARRAY( MaterialHelpers,
			       convertWeightFractionsToAtomFractions_basic,
			       Array );
UNIT_TEST_INSTANTIATION_ARRAY( MaterialHelpers,
			       convertWeightFractionsToAtomFractions_basic,
			       ArrayRCP );

//---------------------------------------------------------------------------//
// Check that a mass density can be converted to a number density
FACEMC_UNIT_TEST_MEMBER_2_TUPLE_1_ARRAY_TEMPLATE_DECL( 
					     MaterialHelpers,
					     convertMassDensityToNumberDensity,
					     fracMember,
					     atomicWgtMember,
					     type,
					     array )
{
  array<type> fraction_data( 4 );
  fillReferenceAtomFractions<fracMember>( fraction_data );
  fillAtomicWeights<atomicWgtMember>( fraction_data );

  double number_density = 
    FACEMC::convertMassDensityToNumberDensity<fracMember,atomicWgtMember>( 
							1.0,
							fraction_data.begin(),
							fraction_data.end(),
							fraction_data.begin(),
							fraction_data.end() ); 

  TEST_FLOATING_EQUALITY( number_density, 0.031365319232812, 1e-13 );
}

UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_ARRAY( 
					 MaterialHelpers,
					 convertMassDensityToNumberDensity,
					 Array );
UNIT_TEST_INSTANTIATION_MEMBER_2_TUPLE_ARRAY( 
					 MaterialHelpers,
					 convertMassDensityToNumberDensity,
					 ArrayRCP );

//---------------------------------------------------------------------------//
// Check that a mass density can be converted to a number density
FACEMC_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_DECL( 
				       MaterialHelpers,
				       convertMassDensityToNumberDensity_basic,
				       type,
				       array )
{
  array<type> fractions( 4 );
  array<type> weights( 4 );
  fillReferenceAtomFractions<FACEMC::FIRST>( fractions );
  fillAtomicWeights<FACEMC::FIRST>( weights );

  double number_density = 
    FACEMC::convertMassDensityToNumberDensity( 1.0,
					       fractions.begin(),
					       fractions.end(),
					       weights.begin(),
					       weights.end() );
  
  TEST_FLOATING_EQUALITY( number_density, 0.031365319232812, 1e-13 );
}

UNIT_TEST_INSTANTIATION_ARRAY( MaterialHelpers,
			       convertMassDensityToNumberDensity_basic,
			       Array );
UNIT_TEST_INSTANTIATION_ARRAY( MaterialHelpers,
			       convertMassDensityToNumberDensity_basic,
			       ArrayRCP );

//---------------------------------------------------------------------------//
// Check that a set of atom fractions can be scaled by a number density
FACEMC_UNIT_TEST_MEMBER_1_TUPLE_1_ARRAY_TEMPLATE_DECL( 
					     MaterialHelpers,
					     scaleAtomFractionsByNumberDensity,
					     member,
					     type,
					     array )
{
  array<type> number_densities( 4 );
  fillReferenceAtomFractions<member>( number_densities );
  
  FACEMC::scaleAtomFractionsByNumberDensity<member>( 0.01,
						     number_densities.begin(),
						     number_densities.end() );

  TEST_EQUALITY_CONST( FACEMC::get<member>( number_densities[0] ), 0.0048 );
  TEST_EQUALITY_CONST( FACEMC::get<member>( number_densities[1] ), 0.0024 );
  TEST_EQUALITY_CONST( FACEMC::get<member>( number_densities[2] ), 0.0016 );
  TEST_EQUALITY_CONST( FACEMC::get<member>( number_densities[3] ), 0.0012 );
}

UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_ARRAY(MaterialHelpers,
					     scaleAtomFractionsByNumberDensity,
					     Array );
UNIT_TEST_INSTANTIATION_MEMBER_1_TUPLE_ARRAY(MaterialHelpers,
					     scaleAtomFractionsByNumberDensity,
					     ArrayRCP );

//---------------------------------------------------------------------------//
// Check that a set of atom fractions can be scaled by a number density
FACEMC_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_DECL( 
				       MaterialHelpers,
				       scaleAtomFractionsByNumberDensity_basic,
				       type,
				       array )
{
  array<type> number_densities( 4 );
  fillReferenceAtomFractions<FACEMC::FIRST>( number_densities );
  
  FACEMC::scaleAtomFractionsByNumberDensity( 0.01,
					     number_densities.begin(),
					     number_densities.end() );

  TEST_EQUALITY_CONST( number_densities[0], 0.0048 );
  TEST_EQUALITY_CONST( number_densities[1], 0.0024 );
  TEST_EQUALITY_CONST( number_densities[2], 0.0016 );
  TEST_EQUALITY_CONST( number_densities[3], 0.0012 );
}

UNIT_TEST_INSTANTIATION_ARRAY( MaterialHelpers,
			       scaleAtomFractionsByNumberDensity_basic,
			       Array );
UNIT_TEST_INSTANTIATION_ARRAY( MaterialHelpers,
			       scaleAtomFractionsByNumberDensity_basic,
			       ArrayRCP );

//---------------------------------------------------------------------------//
// end tstMaterialHelpers.cpp
//---------------------------------------------------------------------------//
