//---------------------------------------------------------------------------//
//!
//! \file   tstMaterialHelpers.cpp
//! \author Alex Robinson
//! \brief  Material helper function unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_MaterialHelpers.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types.
//---------------------------------------------------------------------------//

typedef std::tuple<
  std::tuple<std::integral_constant<size_t,0>,std::pair<double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::pair<double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::tuple<unsigned,double,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::tuple<double,double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::tuple<unsigned,unsigned,double,double> >,
  std::tuple<std::integral_constant<size_t,3>,std::tuple<unsigned,unsigned,double,double> >
  > SingleIndexTestTypes;

typedef std::tuple<
  std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,1>,
             std::pair<double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,0>,
             std::tuple<double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,1>,
             std::tuple<double,double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,2>,
             std::tuple<unsigned,double,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,0>,
             std::tuple<double,double,double> >,
  std::tuple<std::integral_constant<size_t,0>,std::integral_constant<size_t,1>,
             std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,1>,std::integral_constant<size_t,2>,
             std::tuple<double,double,double,double> >,
  std::tuple<std::integral_constant<size_t,2>,std::integral_constant<size_t,3>,
             std::tuple<unsigned,unsigned,double,double> >,
  std::tuple<std::integral_constant<size_t,3>,std::integral_constant<size_t,2>,
             std::tuple<unsigned,unsigned,double,double> >
  > DoubleIndexTestTypes;

#define UNIT_TEST_INSTANTIATION_ARRAY( type, name, array )		\
  UTILITY_UNIT_TEST_TYPE_1_ARRAY_TEMPLATE_INSTANT( type, name, double, array ) \

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
template<size_t member,
	 typename T,
	 template<typename,typename...> class Array>
void fillWeightFractions( Array<T>& array )
{
  Utility::set<member>( array[0], -0.25 );
  Utility::set<member>( array[1], -0.25 );
  Utility::set<member>( array[2], -0.25 );
  Utility::set<member>( array[3], -0.25 );
}

template<size_t member,
	 typename T,
	 template<typename,typename...> class Array>
void fillAtomicWeights( Array<T>& array )
{
  Utility::set<member>( array[0], 10.0 );
  Utility::set<member>( array[1], 20.0 );
  Utility::set<member>( array[2], 30.0 );
  Utility::set<member>( array[3], 40.0 );
}

template<size_t member,
	 typename T,
	 template<typename,typename...> class Array>
void fillReferenceAtomFractions( Array<T>& array )
{
  Utility::set<member>( array[0], 12.0/25.0 );
  Utility::set<member>( array[1], 6.0/25.0 );
  Utility::set<member>( array[2], 4.0/25.0 );
  Utility::set<member>( array[3], 3.0/25.0 );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that fractional values can be tested as valid
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( MaterialHelpers,
                                   areFractionValuesValid,
                                   SingleIndexTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedIndex );
  FETCH_TEMPLATE_PARAM( 1, type );

  constexpr size_t member = WrappedIndex::value;
  
  // Test weight fractions
  std::vector<type> weight_fractions( 4 );
  fillWeightFractions<member>( weight_fractions );

  FRENSIE_CHECK( MonteCarlo::areFractionValuesValid<member>(
					            weight_fractions.begin(),
					            weight_fractions.end() ) );

  Utility::set<member>( weight_fractions[0],
		       -1.0*Utility::get<member>( weight_fractions[0] ) );

  FRENSIE_CHECK( !MonteCarlo::areFractionValuesValid<member>(
					            weight_fractions.begin(),
					            weight_fractions.end() ) );

  weight_fractions.clear();

  // Test atom fractions
  std::vector<type> atom_fractions( 4 );
  fillReferenceAtomFractions<member>( atom_fractions );

  FRENSIE_CHECK( MonteCarlo::areFractionValuesValid<member>(
					              atom_fractions.begin(),
					              atom_fractions.end() ) );

  Utility::set<member>( atom_fractions[0],
		       -1.0*Utility::get<member>( atom_fractions[0] ) );

  FRENSIE_CHECK( !MonteCarlo::areFractionValuesValid<member>(
					              atom_fractions.begin(),
					              atom_fractions.end() ) );

}

//---------------------------------------------------------------------------//
// Check that fractional values can be tested as valid
FRENSIE_UNIT_TEST_TEMPLATE( MaterialHelpers,
                            areFractionValuesValid_basic,
                            double )
{
  FETCH_TEMPLATE_PARAM( 0, type );
  
  // Test weight fractions
  std::vector<type> weight_fractions( 4 );
  fillWeightFractions<Utility::FIRST>( weight_fractions );

  FRENSIE_CHECK( MonteCarlo::areFractionValuesValid( weight_fractions.begin(),
					       weight_fractions.end() ) );

  weight_fractions[0] *= -1.0;

  FRENSIE_CHECK( !MonteCarlo::areFractionValuesValid( weight_fractions.begin(),
						weight_fractions.end() ) );

  weight_fractions.clear();

  // Test atom fractions
  std::vector<type> atom_fractions( 4 );
  fillReferenceAtomFractions<Utility::FIRST>( atom_fractions );

  FRENSIE_CHECK( MonteCarlo::areFractionValuesValid( atom_fractions.begin(),
					       atom_fractions.end() ) );

  atom_fractions[0] *= -1.0;

  FRENSIE_CHECK( !MonteCarlo::areFractionValuesValid( atom_fractions.begin(),
						atom_fractions.end() ) );
}

//---------------------------------------------------------------------------//
// Check that fractional values can be tested as normalized
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( MaterialHelpers,
                                   areFractionValuesNormalized,
                                   SingleIndexTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedIndex );
  FETCH_TEMPLATE_PARAM( 1, type );

  constexpr size_t member = WrappedIndex::value;
  
  // Test weight fractions
  std::vector<type> weight_fractions( 4 );
  fillWeightFractions<member>( weight_fractions );

  FRENSIE_CHECK( MonteCarlo::areFractionValuesNormalized<member>(
						    weight_fractions.begin(),
						    weight_fractions.end() ) );

  Utility::set<member>( weight_fractions[0],
		       2.0*Utility::get<member>( weight_fractions[0] ) );

  FRENSIE_CHECK( !MonteCarlo::areFractionValuesNormalized<member>(
						    weight_fractions.begin(),
						    weight_fractions.end() ) );
  weight_fractions.clear();

  // Test atom fractions
  std::vector<type> atom_fractions( 4 );
  fillReferenceAtomFractions<member>( atom_fractions );

  FRENSIE_CHECK( MonteCarlo::areFractionValuesNormalized<member>(
					              atom_fractions.begin(),
					              atom_fractions.end() ) );

  Utility::set<member>( atom_fractions[0],
		       2.0*Utility::get<member>( atom_fractions[0] ) );

  FRENSIE_CHECK( !MonteCarlo::areFractionValuesNormalized<member>(
					              atom_fractions.begin(),
					              atom_fractions.end() ) );
}

//---------------------------------------------------------------------------//
// Check that fractional values can be tested as normalized
FRENSIE_UNIT_TEST_TEMPLATE( MaterialHelpers,
                            areFractionValuesNormalized_basic,
                            double )
{
  FETCH_TEMPLATE_PARAM( 0, type );
  
  // Test weight fractions
  std::vector<type> weight_fractions( 4 );
  fillWeightFractions<Utility::FIRST>( weight_fractions );

  FRENSIE_CHECK( MonteCarlo::areFractionValuesNormalized( weight_fractions.begin(),
						    weight_fractions.end() ) );

  weight_fractions[0] *= 2.0;

  FRENSIE_CHECK( !MonteCarlo::areFractionValuesNormalized(weight_fractions.begin(),
						    weight_fractions.end() ) );

  weight_fractions.clear();

  // Test atom fractions
  std::vector<type> atom_fractions( 4 );
  fillReferenceAtomFractions<Utility::FIRST>( atom_fractions );

  FRENSIE_CHECK( MonteCarlo::areFractionValuesNormalized( atom_fractions.begin(),
						    atom_fractions.end() ) );

  atom_fractions[0] *= -1.0;

  FRENSIE_CHECK( !MonteCarlo::areFractionValuesNormalized( atom_fractions.begin(),
						     atom_fractions.end() ) );
}

//---------------------------------------------------------------------------//
// Check that a set of fractional values can be normalized
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( MaterialHelpers,
                                   normalizeFractionValues,
                                   SingleIndexTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedIndex );
  FETCH_TEMPLATE_PARAM( 1, type );

  constexpr size_t member = WrappedIndex::value;
  
  // Test weight fractions
  std::vector<type> weight_fractions( 4 );
  fillWeightFractions<member>( weight_fractions );

  Utility::set<member>( weight_fractions[0],
		       2.0*Utility::get<member>( weight_fractions[0] ) );

  MonteCarlo::normalizeFractionValues<member>( weight_fractions.begin(),
					   weight_fractions.end() );

  FRENSIE_CHECK( MonteCarlo::areFractionValuesNormalized<member>(
						    weight_fractions.begin(),
						    weight_fractions.end() ) );
  FRENSIE_CHECK_EQUAL( Utility::get<member>( weight_fractions[0] ), -0.4 );
  FRENSIE_CHECK_EQUAL( Utility::get<member>( weight_fractions[1] ), -0.2 );
  FRENSIE_CHECK_EQUAL( Utility::get<member>( weight_fractions[2] ), -0.2 );
  FRENSIE_CHECK_EQUAL( Utility::get<member>( weight_fractions[3] ), -0.2 );

  weight_fractions.clear();

  // Test atom fractions
  std::vector<type> atom_fractions( 4 );
  fillReferenceAtomFractions<member>( atom_fractions );

  Utility::set<member>( atom_fractions[0],
		       2.0*Utility::get<member>( atom_fractions[0] ) );

  MonteCarlo::normalizeFractionValues<member>( atom_fractions.begin(),
					   atom_fractions.end() );

  FRENSIE_CHECK( MonteCarlo::areFractionValuesNormalized<member>(
					              atom_fractions.begin(),
					              atom_fractions.end() ) );
  FRENSIE_CHECK_EQUAL( Utility::get<member>( atom_fractions[0] ), 24.0/37 );
  FRENSIE_CHECK_EQUAL( Utility::get<member>( atom_fractions[1] ), 6.0/37 );
  FRENSIE_CHECK_EQUAL( Utility::get<member>( atom_fractions[2] ), 4.0/37 );
  FRENSIE_CHECK_EQUAL( Utility::get<member>( atom_fractions[3] ), 3.0/37 );
}

//---------------------------------------------------------------------------//
// Check that a set of fractional values can be normalized
FRENSIE_UNIT_TEST_TEMPLATE( MaterialHelpers,
                            normalizeFractionValues_basic,
                            double )
{
  FETCH_TEMPLATE_PARAM( 0, type );
  
  // Test weight fractions
  std::vector<type> weight_fractions( 4 );
  fillWeightFractions<Utility::FIRST>( weight_fractions );

  weight_fractions[0] *= 2.0;

  MonteCarlo::normalizeFractionValues( weight_fractions.begin(),
				   weight_fractions.end() );

  FRENSIE_CHECK( MonteCarlo::areFractionValuesNormalized( weight_fractions.begin(),
						    weight_fractions.end() ) );
  FRENSIE_CHECK_EQUAL( weight_fractions[0], -0.4 );
  FRENSIE_CHECK_EQUAL( weight_fractions[1], -0.2 );
  FRENSIE_CHECK_EQUAL( weight_fractions[2], -0.2 );
  FRENSIE_CHECK_EQUAL( weight_fractions[3], -0.2 );

  weight_fractions.clear();

  // Test atom fractions
  std::vector<type> atom_fractions( 4 );
  fillReferenceAtomFractions<Utility::FIRST>( atom_fractions );

  atom_fractions[0] *= 2.0;

  MonteCarlo::normalizeFractionValues( atom_fractions.begin(),
				   atom_fractions.end() );

  FRENSIE_CHECK( MonteCarlo::areFractionValuesNormalized( atom_fractions.begin(),
						    atom_fractions.end() ) );
  FRENSIE_CHECK_EQUAL( atom_fractions[0], 24.0/37 );
  FRENSIE_CHECK_EQUAL( atom_fractions[1], 6.0/37 );
  FRENSIE_CHECK_EQUAL( atom_fractions[2], 4.0/37 );
  FRENSIE_CHECK_EQUAL( atom_fractions[3], 3.0/37 );
}

//---------------------------------------------------------------------------//
// Check that weight fractions can be converted to atom fractions
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( MaterialHelpers,
                                   convertWeightFractionsToAtomFractions,
                                   DoubleIndexTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedFractionIndex );
  FETCH_TEMPLATE_PARAM( 1, WrappedWeightIndex );
  FETCH_TEMPLATE_PARAM( 2, type );

  constexpr size_t fracMember = WrappedFractionIndex::value;
  constexpr size_t atomicWgtMember = WrappedWeightIndex::value;
  
  std::vector<type> fraction_data( 4 );
  fillWeightFractions<fracMember>( fraction_data );
  fillAtomicWeights<atomicWgtMember>( fraction_data );

  MonteCarlo::convertWeightFractionsToAtomFractions<fracMember,atomicWgtMember>(
							fraction_data.begin(),
							fraction_data.end(),
							fraction_data.begin(),
							fraction_data.end() );

  std::vector<type> ref_fraction_data( 4 );
  fillReferenceAtomFractions<fracMember>( ref_fraction_data );
  fillAtomicWeights<atomicWgtMember>( ref_fraction_data );

  FRENSIE_CHECK_EQUAL( fraction_data, ref_fraction_data );
}

//---------------------------------------------------------------------------//
// Check that weight fractions can be converted to atom fractions
FRENSIE_UNIT_TEST_TEMPLATE( MaterialHelpers,
                            convertWeightFractionsToAtomFractions_basic,
                            double )
{
  FETCH_TEMPLATE_PARAM( 0, type );
  
  std::vector<type> fractions( 4 );
  std::vector<type> weights( 4 );
  fillWeightFractions<Utility::FIRST>( fractions );
  fillAtomicWeights<Utility::FIRST>( weights );

  MonteCarlo::convertWeightFractionsToAtomFractions( fractions.begin(),
                                                     fractions.end(),
                                                     weights.begin(),
                                                     weights.end() );

  std::vector<type> ref_fractions( 4 );
  fillReferenceAtomFractions<Utility::FIRST>( ref_fractions );

  FRENSIE_CHECK_EQUAL( fractions, ref_fractions );
}

//---------------------------------------------------------------------------//
// Check that a mass density can be converted to a number density
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( MaterialHelpers,
                                   convertMassDensityToNumberDensity,
                                   DoubleIndexTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedFractionIndex );
  FETCH_TEMPLATE_PARAM( 1, WrappedWeightIndex );
  FETCH_TEMPLATE_PARAM( 2, type );

  constexpr size_t fracMember = WrappedFractionIndex::value;
  constexpr size_t atomicWgtMember = WrappedWeightIndex::value;
  
  std::vector<type> fraction_data( 4 );
  fillReferenceAtomFractions<fracMember>( fraction_data );
  fillAtomicWeights<atomicWgtMember>( fraction_data );

  double number_density =
    MonteCarlo::convertMassDensityToNumberDensity<fracMember,atomicWgtMember>(
							1.0,
							fraction_data.begin(),
							fraction_data.end(),
							fraction_data.begin(),
							fraction_data.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( number_density, 0.031365319232812, 1e-13 );
}

//---------------------------------------------------------------------------//
// Check that a mass density can be converted to a number density
FRENSIE_UNIT_TEST_TEMPLATE( MaterialHelpers,
                            convertMassDensityToNumberDensity_basic,
                            double )
{
  FETCH_TEMPLATE_PARAM( 0, type );
  
  std::vector<type> fractions( 4 );
  std::vector<type> weights( 4 );
  fillReferenceAtomFractions<Utility::FIRST>( fractions );
  fillAtomicWeights<Utility::FIRST>( weights );

  double number_density =
    MonteCarlo::convertMassDensityToNumberDensity( 1.0,
					       fractions.begin(),
					       fractions.end(),
					       weights.begin(),
					       weights.end() );

  FRENSIE_CHECK_FLOATING_EQUALITY( number_density, 0.031365319232812, 1e-13 );
}

//---------------------------------------------------------------------------//
// Check that a set of atom fractions can be scaled by a number density
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( MaterialHelpers,
                                   scaleAtomFractionsByNumberDensity,
                                   SingleIndexTestTypes )
{
  FETCH_TEMPLATE_PARAM( 0, WrappedIndex );
  FETCH_TEMPLATE_PARAM( 1, type );

  constexpr size_t member = WrappedIndex::value;
  
  std::vector<type> number_densities( 4 );
  fillReferenceAtomFractions<member>( number_densities );

  MonteCarlo::scaleAtomFractionsByNumberDensity<member>( 0.01,
						     number_densities.begin(),
						     number_densities.end() );

  FRENSIE_CHECK_EQUAL( Utility::get<member>( number_densities[0] ), 0.0048 );
  FRENSIE_CHECK_EQUAL( Utility::get<member>( number_densities[1] ), 0.0024 );
  FRENSIE_CHECK_EQUAL( Utility::get<member>( number_densities[2] ), 0.0016 );
  FRENSIE_CHECK_EQUAL( Utility::get<member>( number_densities[3] ), 0.0012 );
}

//---------------------------------------------------------------------------//
// Check that a set of atom fractions can be scaled by a number density
FRENSIE_UNIT_TEST_TEMPLATE( MaterialHelpers,
                            scaleAtomFractionsByNumberDensity_basic,
                            double )
{
  FETCH_TEMPLATE_PARAM( 0, type );
  
  std::vector<type> number_densities( 4 );
  fillReferenceAtomFractions<Utility::FIRST>( number_densities );

  MonteCarlo::scaleAtomFractionsByNumberDensity( 0.01,
					     number_densities.begin(),
					     number_densities.end() );

  FRENSIE_CHECK_EQUAL( number_densities[0], 0.0048 );
  FRENSIE_CHECK_EQUAL( number_densities[1], 0.0024 );
  FRENSIE_CHECK_EQUAL( number_densities[2], 0.0016 );
  FRENSIE_CHECK_EQUAL( number_densities[3], 0.0012 );
}

//---------------------------------------------------------------------------//
// end tstMaterialHelpers.cpp
//---------------------------------------------------------------------------//
