//---------------------------------------------------------------------------//
//!
//! \file   Data_Xsdir.i
//! \author Alex Robinson
//! \brief  The xsdir class interface file
//!
//---------------------------------------------------------------------------//

%{
// Std Lib Includes
#include <sstream>
  
// Boost Includes
#include <boost/algorithm/string.hpp>
  
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"
#include "Data_Xsdir.hpp"
%}

// Include typemaps support
%include <typemaps.i>

// Standard exception handling
%include "exception.i"

// General exception handling
%exception
{
  try{
    $action;
    if( PyErr_Occurred() )
      SWIG_fail;
  }
  catch( Utility::ContractException& e )
  {
    SWIG_exception( SWIG_ValueError, e.what() );
  }
  catch( Data::InvalidScatteringCenterPropertiesData& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( std::runtime_error& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

//---------------------------------------------------------------------------//
// Add support for the Xsdir
//---------------------------------------------------------------------------//
// Import the scattering center properties database interface
%import(module="PyFrensie.Data") Data_ScatteringCenterPropertiesDatabase.i

%extend Data::Xsdir
{
  //! Show all entries with table data
  void showEntriesWithTableData( const bool human_readable_only = false )
  {
    $self->showEntriesWithTableData( std::cout, human_readable_only );
  }

  //! Return all entries with table data
  PyObject* getEntriesWithTableData( const bool human_readable_only = false )
  {
    std::ostringstream oss;
    
    $self->showEntriesWithTableData( oss, human_readable_only );

    std::string output_string = oss.str();

    std::vector<std::string> entries;
    
    boost::split( entries, output_string, boost::is_any_of("\n") );

    return PyFrensie::convertToPython( entries );
  }

  //! Show all entries with the desired table type key
  void showEntriesWithTableTypeKey( const char key,
                                    const bool human_readable_only = false )
  {
    $self->showEntriesWithTableTypeKey( std::cout, key, human_readable_only );
  }

  //! Return all entries with the desired table type key
  PyObject* getEntriesWithTableTypeKey( const char key,
                                        const bool human_readable_only = false )
  {
    std::ostringstream oss;
    
    $self->showEntriesWithTableTypeKey( oss, key, human_readable_only );

    std::string output_string = oss.str();

    std::vector<std::string> entries;
    
    boost::split( entries, output_string, boost::is_any_of("\n") );

    return PyFrensie::convertToPython( entries );
  }

  //! Show all entries with the desired table type key and version
  void showEntriesWithTableTypeKeyAndVersion(
                                       const unsigned version,
                                       const char key,
                                       const bool human_readable_only = false )
  {
    $self->showEntriesWithTableTypeKeyAndVersion( std::cout, version, key, human_readable_only );
  }

  //! Return all entries with the desired table type key and version
  PyObject* getEntriesWithTableTypeKeyAndVersion(
                                       const unsigned version,
                                       const char key,
                                       const bool human_readable_only = false )
  {
    std::ostringstream oss;
    
    $self->showEntriesWithTableTypeKeyAndVersion( oss, version, key, human_readable_only );

    std::string output_string = oss.str();

    std::vector<std::string> entries;
    
    boost::split( entries, output_string, boost::is_any_of("\n") );

    return PyFrensie::convertToPython( entries );
  }

  //! Show all entries with the desired zaid
  void showEntriesWithZAID( const Data::ZAID& zaid,
                            const bool human_readable_only = false )
  {
    $self->showEntriesWithZAID( std::cout, zaid, human_readable_only );
  }

  //! Return all entries with the desired zaid
  PyObject* getEntriesWithZAID( const Data::ZAID& zaid,
                                const bool human_readable_only = false )
  {
    std::ostringstream oss;
    
    $self->showEntriesWithZAID( oss, zaid, human_readable_only );

    std::string output_string = oss.str();

    std::vector<std::string> entries;
    
    boost::split( entries, output_string, boost::is_any_of("\n") );

    return PyFrensie::convertToPython( entries );
  }

  //! Show all entries with the basic table name
  void showEntriesWithBasicTableName( const std::string& basic_table_name,
                                      const bool human_readable_only = false )
  {
    $self->showEntriesWithBasicTableName( std::cout, basic_table_name, human_readable_only );
  }

  //! Return all entries with the basic table name
  PyObject* getEntriesWithBasicTableName( const std::string& basic_table_name,
                                          const bool human_readable_only = false )
  {
    std::ostringstream oss;
    
    $self->showEntriesWithBasicTableName( oss, basic_table_name, human_readable_only );

    std::string output_string = oss.str();

    std::vector<std::string> entries;
    
    boost::split( entries, output_string, boost::is_any_of("\n") );

    return PyFrensie::convertToPython( entries );
  }

  //! Show all entries with the desired zaid and table type key
  void showEntriesWithZAIDAndTableTypeKey(
                                       const Data::ZAID& zaid,
                                       const char key,
                                       const bool human_readable_only = false )
  {
    $self->showEntriesWithZAIDAndTableTypeKey( std::cout, zaid, key, human_readable_only );
  }

  //! Return all entries with the desired zaid and table type key
  PyObject* getEntriesWithZAIDAndTableTypeKey(
                                       const Data::ZAID& zaid,
                                       const char key,
                                       const bool human_readable_only = false )
  {
    std::ostringstream oss;
    
    $self->showEntriesWithZAIDAndTableTypeKey( oss, zaid, key, human_readable_only );

    std::string output_string = oss.str();

    std::vector<std::string> entries;
    
    boost::split( entries, output_string, boost::is_any_of("\n") );

    return PyFrensie::convertToPython( entries );
  }
  
  //! Show all entries with the desired zaid and table evaluation temp
  void showEntriesWithZAIDAndTableEvaluationTemp(
                                       const Data::ZAID& zaid,
                                       const double evaluation_temp,
                                       const bool human_readable_only = false )
  {
    $self->showEntriesWithZAIDAndTableEvaluationTemp( std::cout, zaid, Data::Xsdir::Energy::from_value(evaluation_temp), human_readable_only );
  }

  //! Return all entries with the desired zaid and table evaluation temp
  PyObject* getEntriesWithZAIDAndTableEvaluationTemp(
                                       const Data::ZAID& zaid,
                                       const double evaluation_temp,
                                       const bool human_readable_only = false )
  {
    std::ostringstream oss;
    
    $self->showEntriesWithZAIDAndTableEvaluationTemp( oss, zaid, Data::Xsdir::Energy::from_value(evaluation_temp), human_readable_only );

    std::string output_string = oss.str();

    std::vector<std::string> entries;
    
    boost::split( entries, output_string, boost::is_any_of("\n") );

    return PyFrensie::convertToPython( entries );
  }
};

%ignore *::showEntriesWithTableData;
%ignore *::showEntriesWithTableTypeKey;
%ignore *::showEntriesWithTableTypeKeyAndVersion;
%ignore *::showEntriesWithZAID;
%ignore *::showEntriesWithBasicTableName;
%ignore *::showEntriesWithZAIDAndTableTypeKey;
%ignore *::showEntriesWithZAIDAndTableEvaluationTemp;

 // Include the Xsdir class
%include "Data_Xsdir.hpp"

//---------------------------------------------------------------------------//
// end Data_Xsdir.i
//---------------------------------------------------------------------------//
