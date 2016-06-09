//---------------------------------------------------------------------------//
//!
//! \file   tstArrayString.cpp
//! \author Alex Robinson
//! \brief  Array string unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_ArrayString.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_arrays_list;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the pi keyword can be replaced with the actual value
TEUCHOS_UNIT_TEST( ArrayString, locateAndReplacePi )
{
  std::string array_string( "{0.0, pi}" );

  Utility::ArrayString::locateAndReplacePi( array_string );

  TEST_EQUALITY_CONST( array_string, "{0.0,3.14159265358979312}" );

  array_string = "{0.0, 1*pi}";

  Utility::ArrayString::locateAndReplacePi( array_string );

  TEST_EQUALITY_CONST( array_string, "{0.0,3.14159265358979312}" );

  array_string = "{0.0, 2pi}";

  Utility::ArrayString::locateAndReplacePi( array_string );

  TEST_EQUALITY_CONST( array_string, "{0.0,6.28318530717958623}" );

  array_string = "{-2pi, -pi, 0.0}";

  Utility::ArrayString::locateAndReplacePi( array_string );

  TEST_EQUALITY_CONST( array_string, "{-6.28318530717958623,-3.14159265358979312, 0.0}" );

  array_string = "{0.0, pi/2, 3pi / 4, pi, 2*pi}";

  Utility::ArrayString::locateAndReplacePi( array_string );

  TEST_EQUALITY_CONST( array_string, "{0.0,1.57079632679489656,2.35619449019234484,3.14159265358979312,6.28318530717958623}" );
}

//---------------------------------------------------------------------------//
// Check that the interval operator can be parsed
TEUCHOS_UNIT_TEST( ArrayString, locateAndReplaceIntervalOperator )
{
  std::string array_string( "{0.0, 2i, 1.0}" );

  Utility::ArrayString::locateAndReplaceIntervalOperator( array_string );

  TEST_EQUALITY_CONST( array_string, "{0.0,0.333333333333333315,0.66666666666666663, 1.0}" );

  array_string = "{-1.0, 3i, 1.0}";

  Utility::ArrayString::locateAndReplaceIntervalOperator( array_string );

  TEST_EQUALITY_CONST( array_string, "{-1.0,-0.5,0,0.5, 1.0}" );

  array_string = "{1e-3, 10l, 10.0}";

  Utility::ArrayString::locateAndReplaceIntervalOperator( array_string );

  TEST_EQUALITY_CONST( array_string, "{1e-3,0.00231012970008315915,0.00533669923120631134,0.0123284673944206707,0.0284803586843580293,0.0657933224657567955,0.151991108295293442,0.351119173421513442,0.811130830789687507,1.87381742286038433,4.32876128108305736, 10.0}" );

  array_string = "{-10.0, 2i, -1.0, 1i, 1.0, 2l, 10.0}";

  Utility::ArrayString::locateAndReplaceIntervalOperator( array_string );

  TEST_EQUALITY_CONST( array_string, "{-10.0,-7,-4, -1.0,0, 1.0,2.15443469003188381,4.6415888336127793, 10.0}" );

  array_string = "{-pi, 3i, pi}";

  Utility::ArrayString::locateAndReplacePi( array_string );
  Utility::ArrayString::locateAndReplaceIntervalOperator( array_string );

  TEST_EQUALITY_CONST( array_string, "{-3.14159265358979312,-1.57079632679489656,0,1.57079632679489656,3.14159265358979312}" );
}

//---------------------------------------------------------------------------//
// Check that the parsed array string can be returned
TEUCHOS_UNIT_TEST( ArrayString, getString )
{
  Utility::ArrayString array_string( "{-pi, 2i, pi/2, 2.0, 2l, 10.0}" );

  TEST_EQUALITY_CONST( array_string.getString(), "{-3.14159265358979312,-1.57079632679489656,0,1.57079632679489656, 2.0,3.41995189335339411,5.84803547642573118, 10.0}" );
}

//---------------------------------------------------------------------------//
// Check that the concrete array can be returned
TEUCHOS_UNIT_TEST( ArrayString, getConcreteArray )
{
  Utility::ArrayString array_string( "{-pi, 2i, pi/2, 2.0, 2l, 10.0}" );

  Teuchos::Array<double> array = array_string.getConcreteArray<double>();

  TEST_EQUALITY_CONST( array.size(), 8 );
  TEST_EQUALITY_CONST( array[0], -3.14159265358979312 );
  TEST_EQUALITY_CONST( array[1], -1.57079632679489656 );
  TEST_EQUALITY_CONST( array[2], 0.0 );
  TEST_EQUALITY_CONST( array[3], 1.57079632679489656 );
  TEST_EQUALITY_CONST( array[4], 2.0 );
  TEST_EQUALITY_CONST( array[5], 3.41995189335339411 );
  TEST_EQUALITY_CONST( array[6], 5.84803547642573118 );
  TEST_EQUALITY_CONST( array[7], 10.0 );

  Utility::ArrayString array_string2( "{0, 3i, 4}" );

  Teuchos::Array<unsigned> uarray = array_string2.getConcreteArray<unsigned>();

  TEST_EQUALITY_CONST( uarray.size(), 5 );
  TEST_EQUALITY_CONST( uarray[0], 0 );
  TEST_EQUALITY_CONST( uarray[1], 1 );
  TEST_EQUALITY_CONST( uarray[2], 2 );
  TEST_EQUALITY_CONST( uarray[3], 3 );
  TEST_EQUALITY_CONST( uarray[4], 4 );
}

//---------------------------------------------------------------------------//
// Check that boolean data can be tested for
TEUCHOS_UNIT_TEST( ArrayString, isBooleanDataPresent )
{
  Utility::ArrayString array_string( "{0.0, 1.0, 2.0}" );

  TEST_ASSERT( !array_string.isBooleanDataPresent() );

  Utility::ArrayString bool_array_string( "{0, 1, 0, 1, 1}" );

  TEST_ASSERT( bool_array_string.isBooleanDataPresent() );
}

//---------------------------------------------------------------------------//
// Check that floating point data can be tested for
TEUCHOS_UNIT_TEST( ArrayString, isFloatingPointDataPresent )
{
  Utility::ArrayString array_string1( "{0.0, 1.0, 2.0}" );

  TEST_ASSERT( array_string1.isFloatingPointDataPresent() );

  Utility::ArrayString array_string2( "{0, 1e-3, 1} " );

  TEST_ASSERT( array_string2.isFloatingPointDataPresent() );

  Utility::ArrayString array_string3( "{0, 1E-03, 1} " );

  TEST_ASSERT( array_string3.isFloatingPointDataPresent() );

  Utility::ArrayString array_string4( "{0, 1, 2}" );

  TEST_ASSERT( !array_string4.isFloatingPointDataPresent() );
}

//---------------------------------------------------------------------------//
// Check that multidimentional data can be tested for
TEUCHOS_UNIT_TEST( ArrayString, isMultidimensionalDataPresent )
{
  Utility::ArrayString array_string( "{0.0, 1.0, 2.0}" );

  TEST_ASSERT( !array_string.isMultidimentionalDataPresent() );

  Utility::ArrayString multi_array_string( "{{0.0, 1.0, 2.0},{0.0,1.0,2.0}}" );

  TEST_ASSERT( multi_array_string.isMultidimentionalDataPresent() );
}

//---------------------------------------------------------------------------//
// Check that the array string can be written to an xml file
TEUCHOS_UNIT_TEST( ArrayString, toParameterList )
{
  Utility::ArrayString array_string( "{0.0, 1.0, 2.0}" );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<Utility::ArrayString>( "test array string",
					    array_string );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"array_string_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "array_string_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Utility::ArrayString copy_array_string =
    read_parameter_list->get<Utility::ArrayString>( "test array string" );

  TEST_EQUALITY( array_string.getString(), copy_array_string.getString() );
}

//---------------------------------------------------------------------------//
// Check that the array string can be read from an xml file
TEUCHOS_UNIT_TEST( ArrayString, fromParameterList )
{
  Utility::ArrayString test_array_string;

  test_array_string =
    test_arrays_list->get<Utility::ArrayString>( "test pi array" );

  TEST_EQUALITY_CONST( test_array_string.getString(),
		       "{-3.14159265358979312,-1.57079632679489656, 0.0,2.35619449019234484,3.14159265358979312,6.28318530717958623}" );

  test_array_string =
    test_arrays_list->get<Utility::ArrayString>( "test linear interval op float array" );

  TEST_EQUALITY_CONST( test_array_string.getString(),
		       "{-1.0,-0.5,0,0.5, 1.0}" );

  test_array_string =
    test_arrays_list->get<Utility::ArrayString>( "test linear interval op int array" );

  TEST_EQUALITY_CONST( test_array_string.getString(),
		       "{0,1,2,3, 4}" );

  test_array_string =
    test_arrays_list->get<Utility::ArrayString>( "test log interval op float array" );

  TEST_EQUALITY_CONST( test_array_string.getString(),
		       "{1e-3,0.00231012970008315915,0.00533669923120631134,0.0123284673944206707,0.0284803586843580293,0.0657933224657567955,0.151991108295293442,0.351119173421513442,0.811130830789687507,1.87381742286038433,4.32876128108305736, 10.0}" );

  test_array_string =
    test_arrays_list->get<Utility::ArrayString>( "test all array" );

  TEST_EQUALITY_CONST( test_array_string.getString(),
		       "{-3.14159265358979312,-1.57079632679489656,0,1.57079632679489656, 2.0,3.41995189335339411,5.84803547642573118, 10.0}" );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_array_xml_file;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_array_xml_file",
		 &test_array_xml_file,
		 "Test array xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::ArrayString );

  test_arrays_list = Teuchos::getParametersFromXmlFile( test_array_xml_file );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstArrayString.cpp
//---------------------------------------------------------------------------//
