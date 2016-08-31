//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5FileHandler_def.hpp
//! \author Alex Robinson
//! \brief  HDF5 file handler template member function definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_FILE_HANDLER_DEF_HPP
#define UTILITY_HDF5_FILE_HANDLER_DEF_HPP

//Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_TwoDArray.hpp>

// HDF5 includes
#include <H5Cpp.h>

// FRENSIE includes
#include "Utility_Tuple.hpp"
#include "Utility_HDF5TypeTraits.hpp"
#include "Utility_ArrayTraits.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_Assertion.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Write data in array to HDF5 file dataset
/*! \tparam Array An array class. Any array class that has a
 *          Utility::ArrayTraits specialization can be used.
 * \param[in] data The data array to write to the HDF5 file dataset.
 * \param[in] location_in_file The location in the HDF5 file where the data will
 * \pre A valid location string, which is any string that does not start with
 * a "/", must be given to this function.
 * \note Developers:
 * <ul>
 *  <li> The template parameters should never be given explicitly.
 *       The compiler will be able to deduce the template parameters based on
 *       the array that is passed to the function.
 *  <li> The Utility::ArrayTraits and Utility::HDF5TypeTraits
 *       structs are critical to the generality of this function. Review these
 *       structs to better understand how this function operates.
 * </ul>
 */
template<typename Array>
void HDF5FileHandler::writeArrayToDataSet(const Array &data,
					  const std::string &location_in_file )
{
  // The dataset_location must be absolute (start with /)
  testPrecondition( location_in_file.compare( 0, 1, "/" ) == 0 );

  // Type contained in the array
  typedef typename ArrayTraits<Array>::value_type value_type;

  // HDF5 exceptions can be thrown when creating a dataset or writing to a
  // dataset
  try
  {
    if( this->doesDataSetExist( location_in_file ) )
    {
      H5::DataSet dataset( d_hdf5_file->openDataSet( location_in_file ) );

      dataset.write( getHeadPtr( data ),
		     HDF5TypeTraits<value_type>::dataType() );
    }
    else
    {
      // Create any parent groups that do not exist yet in the location path
      createParentGroups( location_in_file );

      hsize_t dim = getArraySize( data );
      H5::DataSpace space( 1, &dim );
      H5::DataSet dataset( d_hdf5_file->createDataSet(
					location_in_file,
					HDF5TypeTraits<value_type>::dataType(),
					space ) );
      dataset.write( getHeadPtr( data ),
		     HDF5TypeTraits<value_type>::dataType() );
    }
  }

  HDF5_EXCEPTION_CATCH( std::runtime_error,
			HDF5FileHandler::print_and_exit,
			"Write Array to Data Set Error" );
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const std::vector<double>&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::Array<double>&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayView<double>&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayView<const double>&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayRCP<double>&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayRCP<const double>&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const std::vector<Pair<double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::Array<Pair<double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayView<Pair<double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayView<const Pair<double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayRCP<Pair<double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayRCP<const Pair<double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const std::vector<Trip<double,double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::Array<Trip<double,double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayView<Trip<double,double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayView<const Trip<double,double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayRCP<Trip<double,double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayRCP<const Trip<double,double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const std::vector<Quad<double,double,double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::Array<Quad<double,double,double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayView<Quad<double,double,double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayView<const Quad<double,double,double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayRCP<Quad<double,double,double,double> >&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSet( const Teuchos::ArrayRCP<const Quad<double,double,double,double> >&, const std::string& ) );

// Read in HDF5 file dataset and save the data to an array
/*! \tparam Array An array class. Any array class that has a
 *          Utility::ArrayTraits specialization can be used.
 * \param[in,out] data The data array that will be used to store the HDF5 file
 *                dataset.
 * \param[in] location_in_file The location in the HDF5 file where the data
 *            will be read from.
 * \pre A valid location string, which is any string that does not start with
 * a "/", must be given to this function.
 * \note Developers:
 * <ul>
 *  <li> The template parameters should never be given explicitly.
 *       The compiler will be able to deduce the template parameters based on
 *       the array that is passed to the function.
 *  <li> The Utility::ArrayTraits and Utility::HDF5TypeTraits
 *       structs are critical to the generality of this function. Review these
 *       structs to better understand how this function operates.
 * </ul>
 */
template<typename Array>
void HDF5FileHandler::readArrayFromDataSet(
				    Array &data,
				    const std::string &location_in_file ) const
{
  // The dataset_location must be absolute (start with /)
  testPrecondition( location_in_file.compare( 0, 1, "/" ) == 0 );

  // Type contained in the array
  typedef typename ArrayTraits<Array>::value_type value_type;
  // The size type associated with the array
  typedef typename ArrayTraits<Array>::size_type size_type;


  // HDF5 exceptions can be thrown when opening and reading from datasets
  try
  {
    H5::DataSet dataset(d_hdf5_file->openDataSet( location_in_file ) );

    // Get the dataspace of the dataset
    H5::DataSpace dataspace = dataset.getSpace();

    // Get the number of dimensions in the dataspace
    int rank = dataspace.getSimpleExtentNdims();

    // Get the dimension size of each dimension in the dataspace
    hsize_t dims[rank];
    int ndims = dataspace.getSimpleExtentDims( dims, NULL );

    // Resize the output array to the size of the dataspace
    size_type size = dims[0];
    for( unsigned int i = 1; i < rank; ++i )
      size *= dims[i];

    resizeArray( data, size );

    // Read the data in the dataset and save it to the output array
    dataset.read( getHeadPtr( data ),
		  HDF5TypeTraits<value_type>::dataType() );
  }

  HDF5_EXCEPTION_CATCH( std::runtime_error,
			HDF5FileHandler::print_and_exit,
			"Read Array from Data Set Error" );
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( std::vector<double>&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( Teuchos::Array<double>&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( Teuchos::ArrayView<double>&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( Teuchos::ArrayRCP<double>&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( std::vector<Pair<double,double> >&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( Teuchos::Array<Pair<double,double> >&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( Teuchos::ArrayView<Pair<double,double> >&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( Teuchos::ArrayRCP<Pair<double,double> >&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( std::vector<Trip<double,double,double> >&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( Teuchos::Array<Trip<double,double,double> >&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( Teuchos::ArrayView<Trip<double,double,double> >&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( Teuchos::ArrayRCP<Trip<double,double,double> >&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( std::vector<Quad<double,double,double,double> >&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( Teuchos::Array<Quad<double,double,double,double> >&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( Teuchos::ArrayView<Quad<double,double,double,double> >&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSet( Teuchos::ArrayRCP<Quad<double,double,double,double> >&, const std::string& ) const );

// Write attribute to HDF5 file dataset
/*! \tparam Array An array class. Any array class that has a
 *          Utility::ArrayTraits specialization can be used.
 * \param[in] data The data array to write to the HDF5 file dataset attribute.
 * \param[in] location_in_file The location in the HDF5 file where the dataset
 *            attribute will written.
 * \param[in] attribute_name The name of the dataset attribute.
 * \pre
 * <ul>
 *  <li> A valid location string, which is any string that does not start with
 *       a "/", must be given to this function.
 *  <li> A valid attribute name string, which is any string that does not
 *       contian a "/", must be given to this function.
 * </ul>
 * \note Developers:
 * <ul>
 *  <li> The template parameters should never be given explicitly.
 *       The compiler will be able to deduce the template parameters based on
 *       the array that is passed to the function.
 *  <li> The Utility::ArrayTraits and Utility::HDF5TypeTraits
 *       structs are critical to the generality of this function. Review these
 *       structs to better understand how this function operates.
 * </ul>
 */
template<typename Array>
void HDF5FileHandler::writeArrayToDataSetAttribute(
					   const Array &data,
					   const std::string &dataset_location,
					   const std::string &attribute_name )
{
  // The dataset_location must be absolute (start with /)
  testPrecondition( (dataset_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  testPrecondition( (attribute_name.find( "/" ) == std::string::npos ) );

  typedef typename ArrayTraits<Array>::value_type value_type;

  // HDF5 exceptions can be thrown when opening a group, creating an attribute,
  // or writing an attribute to a group
  try
  {
    hsize_t dim = getArraySize(data);
    H5::DataSpace space( 1, &dim );
    H5::DataSet dataset(d_hdf5_file->openDataSet( dataset_location ) );

    if( this->doesDataSetAttributeExist( dataset_location, attribute_name ) )
    {
      H5::Attribute attribute( dataset.openAttribute( attribute_name ) );

      attribute.write( HDF5TypeTraits<value_type>::dataType(),
		       getHeadPtr( data ) );
    }
    else
    {
      H5::Attribute attribute(dataset.createAttribute(
				attribute_name,
				HDF5TypeTraits<value_type>::dataType(),
				space ) );

      attribute.write( HDF5TypeTraits<value_type>::dataType(),
		       getHeadPtr( data ) );
    }
  }

  HDF5_EXCEPTION_CATCH( std::runtime_error,
			HDF5FileHandler::print_and_exit,
			"Write Array to Data Set Attribute Error" );
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const std::vector<double>&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::Array<double>&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayView<double>&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayView<const double>&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayRCP<double>&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayRCP<const double>&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const std::vector<Pair<double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::Array<Pair<double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayView<Pair<double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayView<const Pair<double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayRCP<Pair<double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayRCP<const Pair<double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const std::vector<Trip<double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::Array<Trip<double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayView<Trip<double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayView<const Trip<double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayRCP<Trip<double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayRCP<const Trip<double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const std::vector<Quad<double,double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::Array<Quad<double,double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayView<Quad<double,double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayView<const Quad<double,double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayRCP<Quad<double,double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToDataSetAttribute( const Teuchos::ArrayRCP<const Quad<double,double,double,double> >&, const std::string&, const std::string& ) );

// Read in HDF5 file dataset attribute and save the data to an array
/*! \tparam Array An array class. Any array class that has a
 *          Utility::ArrayTraits specialization can be used.
 * \param[in,out] data The data array that will be used to store the HDF5 file
 *                dataset attribute.
 * \param[in] location_in_file The location in the HDF5 file where the data
 *            will be read from.
 * \param[in] attribute_name The name of the dataset attribute.
 * \pre
 * <ul>
 *  <li> A valid location string, which is any string that does not start with
 *       a "/", must be given to this function.
 *  <li> A valid attribute name string, which is any string that does not
 *       contian a "/", must be given to this function.
 * </ul>
 * \note Developers:
 * <ul>
 *  <li> The template parameters should never be given explicitly.
 *       The compiler will be able to deduce the template parameters based on
 *       the array that is passed to the function.
 *  <li> The Utility::ArrayTraits and Utility::HDF5TypeTraits
 *       structs are critical to the generality of this function. Review these
 *       structs to better understand how this function operates.
 * </ul>
 */
template<typename Array>
void HDF5FileHandler::readArrayFromDataSetAttribute(
				      Array &data,
				      const std::string &dataset_location,
				      const std::string &attribute_name ) const
{
  // The dataset_location must be absolute (start with /)
  testPrecondition( (dataset_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  testPrecondition( (attribute_name.find( "/" ) == std::string::npos ) );

  typedef typename ArrayTraits<Array>::value_type value_type;
  typedef typename ArrayTraits<Array>::size_type size_type;

  // HDF5 exceptions can be thrown when opening and reading from datasets
  try
  {
    H5::DataSet dataset( d_hdf5_file->openDataSet( dataset_location ) );

    // Get the attribute associated with the dataset
    H5::Attribute attribute( dataset.openAttribute( attribute_name) );

    // Get the dataspace of the attribute
    H5::DataSpace dataspace = attribute.getSpace();

    // Get the number of dimensions in the dataspace
    int rank = dataspace.getSimpleExtentNdims();

    // Get the dimension size of each dimension in the dataspace
    hsize_t dims[rank];
    int ndims = dataspace.getSimpleExtentDims( dims, NULL );

    // Resize the output array to the size of the dataspace
    size_type size = dims[0];
    for( unsigned int i = 1; i < rank; ++i )
      size *= dims[i];

    resizeArray( data, size );

    // Read the data in the dataset and save it to the output array
    attribute.read( HDF5TypeTraits<value_type>::dataType(),
		    getHeadPtr( data ) );
  }

  HDF5_EXCEPTION_CATCH( std::runtime_error,
			HDF5FileHandler::print_and_exit,
			"Read Array from Data Set Attribute Error" );
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( std::vector<double>&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( Teuchos::Array<double>&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( Teuchos::ArrayView<double>&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( Teuchos::ArrayRCP<double>&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( std::vector<Pair<double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( Teuchos::Array<Pair<double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( Teuchos::ArrayView<Pair<double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( Teuchos::ArrayRCP<Pair<double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( std::vector<Trip<double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( Teuchos::Array<Trip<double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( Teuchos::ArrayView<Trip<double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( Teuchos::ArrayRCP<Trip<double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( std::vector<Quad<double,double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( Teuchos::Array<Quad<double,double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( Teuchos::ArrayView<Quad<double,double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromDataSetAttribute( Teuchos::ArrayRCP<Quad<double,double,double,double> >&, const std::string&, const std::string& ) const );

// Write attribute to HDF5 file dataset
/*! \tparam T Data type to be written.
 * \param[in] value The data value to write to the HDF5 file dataset attribute.
 * \param[in] dataset_location The location in the HDF5 file where the dataset
 * attribute will written.
 * \param[in] attribute_name The name of the dataset attribute.
 * \pre
 * <ul>
 *  <li> A valid location string, which is any string that does not start with
 *       a "/", must be given to this function.
 *  <li> A valid attribute name string, which is any string that does not
 *       contian a "/", must be given to this function.
 * </ul>
 * \note Developers:
 * <ul>
 *  <li> The template parameter should never be given explicitly.
 *       The compiler will be able to deduce the template parameter based on
 *       the value that is passed to the function.
 *  <li> The Utility::HDF5TypeTraits struct is critical to the
 *       generality of this function. Review this structs to better understand
 *       how this function operates.
 * </ul>
 */
template<typename T>
void HDF5FileHandler::writeValueToDataSetAttribute(
					   const T &value,
					   const std::string &dataset_location,
					   const std::string &attribute_name )
{
  // The dataset_location must be absolute (start with /)
  testPrecondition( (dataset_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  testPrecondition( (attribute_name.find( "/" ) == std::string::npos ) );

  // HDF5 exceptions can be thrown when opening a group, creating an attribute,
  // or writing an attribute to a group
  try
  {
    hsize_t dim = 1;
    H5::DataSpace space( 1, &dim );
    H5::DataSet dataset( d_hdf5_file->openDataSet( dataset_location ) );

    if( this->doesDataSetAttributeExist( dataset_location, attribute_name ) )
    {
      H5::Attribute attribute( dataset.openAttribute( attribute_name ) );

      attribute.write( HDF5TypeTraits<T>::dataType(), &value );
    }
    else
    {
      H5::Attribute attribute( dataset.createAttribute(
					 attribute_name,
				         HDF5TypeTraits<T>::dataType(),
					 space ) );

      attribute.write( HDF5TypeTraits<T>::dataType(),
		       &value );
    }
  }

  HDF5_EXCEPTION_CATCH( std::runtime_error,
			HDF5FileHandler::print_and_exit,
			"Write Value to Data Set Attribute Error" );
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToDataSetAttribute( const float&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToDataSetAttribute( const double&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToDataSetAttribute( const char&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToDataSetAttribute( const unsigned char&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToDataSetAttribute( const int&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToDataSetAttribute( const unsigned&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToDataSetAttribute( const long&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToDataSetAttribute( const unsigned long&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToDataSetAttribute( const long long&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToDataSetAttribute( const unsigned long long&, const std::string&, const std::string& ) );

// Read in HDF5 file dataset attribute and save the single value
/*! \tparam T Data type to be read.
 * \param[in,out] value The data value that will store the HDF5 file dataset
 * attribute.
 * \param[in] dataset_location The location in the HDF5 file where the dataset
 * attribute will written.
 * \param[in] attribute_name The name of the dataset attribute.
 * \pre
 * <ul>
 *  <li> A valid location string, which is any string that does not start with
 *       a "/", must be given to this function.
 *  <li> A valid attribute name string, which is any string that does not
 *       contian a "/", must be given to this function.
 * </ul>
 * \note Developers:
 * <ul>
 *  <li> The template parameter should never be given explicitly.
 *       The compiler will be able to deduce the template parameter based on
 *       the value that is passed to the function.
 *  <li> The Utility::HDF5TypeTraits struct is critical to the
 *       generality of this function. Review this structs to better understand
 *       how this function operates.
 * </ul>
 */
template<typename T>
void HDF5FileHandler::readValueFromDataSetAttribute(
				      T &value,
				      const std::string &dataset_location,
				      const std::string &attribute_name ) const
{
  // The dataset_location must be absolute (start with /)
  testPrecondition( (dataset_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  testPrecondition( (attribute_name.find( "/" ) == std::string::npos ) );

  // HDF5 exceptions can be thrown when opening and reading from datasets
  try
  {
    H5::DataSet dataset(d_hdf5_file->openDataSet( dataset_location ) );

    // Get the attribute associated with the dataset
    H5::Attribute attribute(dataset.openAttribute( attribute_name) );

    // Get the dataspace of the attribute
    H5::DataSpace dataspace = attribute.getSpace();

    // Get the number of dimensions in the dataspace
    int rank = dataspace.getSimpleExtentNdims();

    // Get the dimension size of each dimension in the dataspace
    hsize_t dims[rank];
    int ndims = dataspace.getSimpleExtentDims( dims, NULL );

    ASSERT_ALWAYS( (rank == 1 && dims[0] == 1) );

    // Read the data in the dataset and save it to the output array
    attribute.read( HDF5TypeTraits<T>::dataType(),
		    &value );
  }

  HDF5_EXCEPTION_CATCH( std::runtime_error,
			HDF5FileHandler::print_and_exit,
			"Read Value from Data Set Attribute Error" );
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromDataSetAttribute( float&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromDataSetAttribute( double&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromDataSetAttribute( char&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromDataSetAttribute( unsigned char&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromDataSetAttribute( int&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromDataSetAttribute( unsigned&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromDataSetAttribute( long&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromDataSetAttribute( unsigned long&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromDataSetAttribute( long long&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromDataSetAttribute( unsigned long long&, const std::string&, const std::string& ) const );

// Write attribute to HDF5 file group
/*! \tparam Array An array class. Any array class that has a
 *          Utility::ArrayTraits specialization can be used.
 * \param[in] data The data array to write to the HDF5 file group attribute.
 * \param[in] group_location The location in the HDF5 file where the group
 *            attribute will written.
 * \param[in] attribute_name The name of the group attribute.
 * \pre
 * <ul>
 *  <li> A valid location string, which is any string that does not start with
 *       a "/", must be given to this function.
 *  <li> A valid attribute name string, which is any string that does not
 *       contian a "/", must be given to this function.
 * </ul>
 * \note Developers:
 * <ul>
 *  <li> The template parameters should never be given explicitly.
 *       The compiler will be able to deduce the template parameters based on
 *       the array that is passed to the function.
 *  <li> The Utility::ArrayTraits and Utility::HDF5TypeTraits
 *       structs are critical to the generality of this function. Review these
 *       structs to better understand how this function operates.
 * </ul>
 */
template<typename Array>
void HDF5FileHandler::writeArrayToGroupAttribute(
					    const Array &data,
					    const std::string &group_location,
					    const std::string &attribute_name )
{
  // The dataset_location must be absolute (start with /)
  testPrecondition( (group_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  testPrecondition( (attribute_name.find( "/" ) == std::string::npos ) );

  typedef typename ArrayTraits<Array>::value_type value_type;

  // HDF5 exceptions can be thrown when opening a group, creating an attribute,
  // or writing an attribute to a group
  try
  {
    // Create any parent groups that do not exist yet in the location path
    createParentGroups( group_location );

    hsize_t dim = getArraySize( data );
    H5::DataSpace space( 1, &dim );
    H5::Group group(d_hdf5_file->openGroup( group_location ) );

    if( this->doesGroupAttributeExist( group_location, attribute_name ) )
    {
      H5::Attribute attribute( group.openAttribute( attribute_name ) );

      attribute.write( HDF5TypeTraits<value_type>::dataType(),
		       getHeadPtr( data ) );
    }
    else
    {
      H5::Attribute attribute( group.createAttribute(
				attribute_name,
			        HDF5TypeTraits<value_type>::dataType(),
				space ) );

      attribute.write( HDF5TypeTraits<value_type>::dataType(),
		       getHeadPtr( data ) );
    }
  }

  HDF5_EXCEPTION_CATCH( std::runtime_error,
			HDF5FileHandler::print_and_exit,
			"Write Array to Group Attribute Error" );
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const std::vector<double>&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::Array<double>&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayView<double>&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayView<const double>&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayRCP<double>&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayRCP<const double>&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const std::vector<Pair<double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::Array<Pair<double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayView<Pair<double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayView<const Pair<double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayRCP<Pair<double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayRCP<const Pair<double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const std::vector<Trip<double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::Array<Trip<double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayView<Trip<double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayView<const Trip<double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayRCP<Trip<double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayRCP<const Trip<double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const std::vector<Quad<double,double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::Array<Quad<double,double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayView<Quad<double,double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayView<const Quad<double,double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayRCP<Quad<double,double,double,double> >&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeArrayToGroupAttribute( const Teuchos::ArrayRCP<const Quad<double,double,double,double> >&, const std::string&, const std::string& ) );

// Read in HDF5 file group attribute and save the data to an array
/*! \tparam Array An array class. Any array class that has a
 *          Utility::ArrayTraits specialization can be used.
 * \param[in,out] data The data array that will be used to store the HDF5 file
 *                group attribute.
 * \param[in] group_location The location in the HDF5 file where the group is
 *            located.
 * \param[in] attribute_name The name of the group attribute.
 * \pre
 * <ul>
 *  <li> A valid location string, which is any string that does not start with
 *       a "/", must be given to this function.
 *  <li> A valid attribute name string, which is any string that does not
 *       contian a "/", must be given to this function.
 * </ul>
 * \note Developers:
 * <ul>
 *  <li> The template parameters should never be given explicitly.
 *       The compiler will be able to deduce the template parameters based on
 *       the array that is passed to the function.
 *  <li> The Utility::ArrayTraits and Utility::HDF5TypeTraits
 *       structs are critical to the generality of this function. Review these
 *       structs to better understand how this function operates.
 * </ul>
 */
template<typename Array>
void HDF5FileHandler::readArrayFromGroupAttribute(
				      Array &data,
				      const std::string &group_location,
				      const std::string &attribute_name ) const
{
  // The group_location must be absolute (start with /)
  testPrecondition( (group_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  testPrecondition( (attribute_name.find( "/" ) == std::string::npos ) );

  typedef typename ArrayTraits<Array>::value_type value_type;
  typedef typename ArrayTraits<Array>::size_type size_type;

  // HDF5 exceptions can be thrown when opening and reading from datasets
  try
  {
    H5::Group group(d_hdf5_file->openGroup( group_location ) );

    // Get the attribute associated with the group
    H5::Attribute attribute(group.openAttribute( attribute_name) );

    // Get the dataspace of the attribute
    H5::DataSpace dataspace = attribute.getSpace();

    // Get the number of dimensions in the dataspace
    int rank = dataspace.getSimpleExtentNdims();

    // Get the dimension size of each dimension in the dataspace
    hsize_t dims[rank];
    int ndims = dataspace.getSimpleExtentDims( dims, NULL );

    // Resize the output array to the size of the dataspace
    size_type size = dims[0];
    for( unsigned int i = 1; i < rank; ++i )
      size *= dims[i];

    resizeArray( data, size );

    // Read the data in the dataset and save it to the output array
    attribute.read( HDF5TypeTraits<value_type>::dataType(),
		    getHeadPtr( data ) );
  }

  HDF5_EXCEPTION_CATCH( std::runtime_error,
			HDF5FileHandler::print_and_exit,
			"Read Array from Group Attribute Error" );
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( std::vector<double>&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( Teuchos::Array<double>&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( Teuchos::ArrayView<double>&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( Teuchos::ArrayRCP<double>&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( std::vector<Pair<double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( Teuchos::Array<Pair<double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( Teuchos::ArrayView<Pair<double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( Teuchos::ArrayRCP<Pair<double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( std::vector<Trip<double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( Teuchos::Array<Trip<double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( Teuchos::ArrayView<Trip<double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( Teuchos::ArrayRCP<Trip<double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( std::vector<Quad<double,double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( Teuchos::Array<Quad<double,double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( Teuchos::ArrayView<Quad<double,double,double,double> >&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readArrayFromGroupAttribute( Teuchos::ArrayRCP<Quad<double,double,double,double> >&, const std::string&, const std::string& ) const );

// Write attribute to HDF5 file group
/*! \tparam T Data type of value to write
 * \param[in] value The data value to write to the HDF5 file group attribute.
 * \param[in] group_location The location in the HDF5 file where the group
 * is located.
 * \param[in] attribute_name The name of the group attribute.
 * \pre
 * <ul>
 *  <li> A valid location string, which is any string that does not start with
 *       a "/", must be given to this function.
 *  <li> A valid attribute name string, which is any string that does not
 *       contian a "/", must be given to this function.
 * </ul>
 * \note Developers:
 * <ul>
 *  <li> The template parameter should never be given explicitly.
 *       The compiler will be able to deduce the template parameter based on
 *       the value that is passed to the function.
 *  <li> The Utility::HDF5TypeTraits struct is critical to the
 *       generality of this function. Review this structs to better understand
 *       how this function operates.
 * </ul>
 */
template<typename T>
void HDF5FileHandler::writeValueToGroupAttribute(
					    const T &value,
					    const std::string &group_location,
					    const std::string &attribute_name )
{
  // The dataset_location must be absolute (start with /)
  testPrecondition( (group_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  testPrecondition( (attribute_name.find( "/" ) == std::string::npos ) );

  // HDF5 exceptions can be thrown when opening a group, creating an attribute,
  // or writing an attribute to a group
  try
  {
    // Create any parent groups that do not exist yet in the location path
    createParentGroups( group_location );

    hsize_t dim = 1;
    H5::DataSpace space( 1, &dim );
    H5::Group group(d_hdf5_file->openGroup( group_location ) );

    if( this->doesGroupAttributeExist( group_location, attribute_name ) )
    {
      H5::Attribute attribute( group.openAttribute( attribute_name ) );

      attribute.write( HDF5TypeTraits<T>::dataType(), &value );
    }
    else
    {
      H5::Attribute attribute(group.createAttribute(
					 attribute_name,
					 HDF5TypeTraits<T>::dataType(),
					 space ) );

      attribute.write( HDF5TypeTraits<T>::dataType(), &value );
    }
  }

  HDF5_EXCEPTION_CATCH( std::runtime_error,
			HDF5FileHandler::print_and_exit,
			"Write Value to Group Attribute Error" );
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToGroupAttribute( const float&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToGroupAttribute( const double&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToGroupAttribute( const char&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToGroupAttribute( const unsigned char&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToGroupAttribute( const int&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToGroupAttribute( const unsigned&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToGroupAttribute( const long&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToGroupAttribute( const unsigned long&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToGroupAttribute( const long long&, const std::string&, const std::string& ) );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::writeValueToGroupAttribute( const unsigned long long&, const std::string&, const std::string& ) );

// Read in HDF5 file group attribute and save the single value
/*! \tparam T Data type to be read.
 * \param[in,out] value The data value that will store the HDF5 file group
 * attribute.
 * \param[in] group_location The location in the HDF5 file where the group
 * is located.
 * \param[in] attribute_name The name of the group attribute.
 * \pre
 * <ul>
 *  <li> A valid location string, which is any string that does not start with
 *       a "/", must be given to this function.
 *  <li> A valid attribute name string, which is any string that does not
 *       contian a "/", must be given to this function.
 * </ul>
 * \note Developers:
 * <ul>
 *  <li> The template parameter should never be given explicitly.
 *       The compiler will be able to deduce the template parameter based on
 *       the value that is passed to the function.
 *  <li> The Utility::HDF5TypeTraits struct is critical to the
 *       generality of this function. Review this structs to better understand
 *       how this function operates.
 * </ul>
 */
template<typename T>
void HDF5FileHandler::readValueFromGroupAttribute(
				      T &value,
				      const std::string &group_location,
				      const std::string &attribute_name ) const
{
  // The group_location must be absolute (start with /)
  testPrecondition( (group_location.compare( 0, 1, "/" ) == 0) );
  // The attribute name can contain any character except /
  testPrecondition( (attribute_name.find( "/" ) == std::string::npos ) );

  // HDF5 exceptions can be thrown when opening and reading from datasets
  try
  {
    H5::Group group(d_hdf5_file->openGroup( group_location ) );

    // Get the attribute associated with the group
    H5::Attribute attribute(group.openAttribute( attribute_name) );

    // Get the dataspace of the attribute
    H5::DataSpace dataspace = attribute.getSpace();

    // Get the number of dimensions in the dataspace
    int rank = dataspace.getSimpleExtentNdims();

    // Get the dimension size of each dimension in the dataspace
    hsize_t dims[rank];
    int ndims = dataspace.getSimpleExtentDims( dims, NULL );

    ASSERT_ALWAYS_MSG( (rank == 1 && dims[0] == 1),
			      "Fatal Error: Cannot read a single value from an attribute array.");

    // Read the data in the dataset and save it to the output array
    attribute.read( HDF5TypeTraits<T>::dataType(),
		    &value );
  }

  HDF5_EXCEPTION_CATCH( std::runtime_error,
			HDF5FileHandler::print_and_exit,
			"Read Value from Group Attribute Error" );
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromGroupAttribute( float&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromGroupAttribute( double&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromGroupAttribute( char&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromGroupAttribute( unsigned char&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromGroupAttribute( int&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromGroupAttribute( unsigned&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromGroupAttribute( long&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromGroupAttribute( unsigned long&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromGroupAttribute( long long&, const std::string&, const std::string& ) const );
EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void HDF5FileHandler::readValueFromGroupAttribute( unsigned long long&, const std::string&, const std::string& ) const );

} // end Utility namespace

#endif // end UTILITY_HDF5_FILE_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5FileHandler_def.hpp
//---------------------------------------------------------------------------//
