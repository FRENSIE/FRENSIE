//---------------------------------------------------------------------------//
// \file DataProcessorBase.hpp
// \author Alex Robinson
// \brief Data Processor Base Class declaration.
//---------------------------------------------------------------------------//

#ifndef DATA_PROCESSOR_BASE_HPP
#define DATA_PROCESSOR_BASE_HPP

// Std Lib Includes
#include <stdlib.h>
#include <stdio.h>
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// HDF5 includes
#include <hdf5.h>

// FACEMC includes


namespace FACEMC{

class DataProcessorBase
{

public:

  //! Default Constructor
  DataProcessorBase()
  { /* ... */ }

  //! Destructor
  virtual ~DataProcessorBase()
  { /* ... */ }

  //-------------------------------------------------------------------------//
  // Data Processing Interface
  //-------------------------------------------------------------------------//

  //! Process Data Files
  virtual void processDataFiles() = 0;

protected:

  //! Open an HDF5 file and overwrite any existing data
  hid_t openHDF5FileAndOverwrite( const std::string &file_name );

  //! Open an HDF5 file and append to any existing data
  hid_t openHDF5FileAndAppend( const std::string &file_name );

  //! Close an HDF5 file
  void closeHDF5File( hid_t file_id );

//! Write data in 1D array to HDF5 file
  // \param file_id HDF5 identifier for the binary file to write to
  // \param data 1xM data array to write to HDF5 file
  // \param location_in_file location in HDF5 file where data will be written
  template<typname T>
  void writeArrayToHDF5File( const hid_t file_id,
			     const Teuchos::Array<double>& data,
			     const std::string &location_in_file );
  
  //! Write data in 2D array to HDF5 file
  // \param file_id HDF5 identifier for the binary file to write to
  // \param data[N] NxM data array to write to HDF5 file
  // \param location_in_file location in HDF5 file where data will be written
  template<typename T, int N=2>
  void write2DArrayToHDF5File( const hid_t file_id, 
			       const Teuchos::Array<T>& data[N],
			       const std::string &location_in_file );

  //! Write a multi value attribute to HDF5 file ( 1xN array )
  // \param file_id HDF5 identifier for the binary file to write to
  template<typename T, int N=2>
  void writeMultiValueAttributToHDF5File( const hid_t file_id,
					  const T data[N],
					  const std::string &location_in_file,
					  const std::string &attribute_name );

  //! Write a single value attribute to HDF5 file
  // \param file_id HDF5 identifier for the binary file to write to
  template<typename T>
  void writeSingleValueAttributeToHDF5File( const hid_t file_id,
					    const T data,
					    const std::string &location_in_file,
					    const std::string &attribute_name );

  //! Read the first table header
  // \brief Read the first EPDL, EADL or EEDL table header and extract info
  // \param datafile EPDL, EADL or EEDL file
  // \param atomic_number Atomic number associated with the table
  // \param outgoing_particle_designator Outgoing particle from the reaction
  // \param interpolation_flag Type of interpolation required for the table
  void readFirstTableHeader( FILE* datafile,
			     int &atomic_number,
			     int &outgoing_particle_designator,
			     int &atomic_weight,
			     int &interpolation_flag );

  //! Read the second table header
  // \brief Read the second EPDL, EADL or EEDL table header and extract info
  // \param datafile EPDL, EADL or EEDL file
  // \param reaction_type Reaction type identifier (see EPDL doc files)
  // \param electron_shell Electron shell identifier for table
  void readSecondTableHeader( FILE* datafile,
			      int &reaction_type,
			      int &electron_shell );
  
  //! Skip two column table in EPDL file
  void skipTwoColumnTable( FILE* datafile );

  //! Read two column table in EPDL file within specified range
  template<typename DataProcessingPolicy>
  void readTwoColumnTableInRange( FILE* datafile,
				  Teuchos::Array<double> &data[2],
				  const double indep_var_min,
				  const double indep_var_max );

  //! Read two column table in EPDL file 
  template<typename DataProcessingPolicy>
  void readTwoColumnTable( FILE* datafile,
			   Teuchos::Array<double> &data[2] );

  //! Skip three column table in EPDL file
  void skipThreeColumnTable( FILE* datafile );

  //! Read three column table in EPDL file
  void readThreeColumnTable( FILE* datafile,
			     Teuchos::Array<double> &data[3] );

  //! Skip four column table in EPDL file
  void skipFourColumnTable( FILE* datafile );
  
  //! Read four column table in EPDL file
  void readFourColumnTable( FILE* datafile,
			    Teuchos::Array<double> &data[4] );

  /*! 
   * \brief Create the desired type from a printed fortran style fixed-width 
   * float. Undefined behavior is likely for types other than double and int.
   * Because this function will be called ~1e6 times while processing the
   * entire EPDL Library it has been inlined.
   */
  template<typename T>
  inline T extractValue( std::string mantissa,
			 std::string exponent );

  //! Convert an EPDL shell integer to a shell name
  std::string intToShellStr( const int shell );

  /*!
   * \brief Policy class for processing data tables that require log-log
   * interpolation between evaluated points.
   */
  class LogLogDataProcessingPolicy
  {
    //! Process Independent Variable
    static inline double processIndependentVar( const double indep_var );
    
    //! Process Dependent Variable
    static inline double processDependentVar( const double dep_var );
  };

  /*!
   * \brief Policy class for processing data tables that require linear-log
   * interpolation between evaluated points.
   */
   class LinearLogDataProcessingPolicy
   {
     //! Process Independent Variable
     static inline double processIndependentVar( const double indep_var );
     
     //! Process Dependent Variable
     static inline double processDependentVar( const double dep_var );
   };

  /*!
   * \brief Policy class for processing data tables that require log-linear
   * interpolation between evaluated points.
   */
  class LogLinearDataProcessingPolicy
  {
    //! Process Independent Variable
    static inline double processIndependentVar( const double indep_var );
    
    //! Process Dependent Variable
    static inline double processDependentVar( const double dep_var );
  };

  /*!
   * \brief Policy class for processing data tables that require linear-linear
   * interpolation between data points.
   */
  class LinearLinearDataProcessingPolicy
  {
    //! Process Independent Variable
    static inline double processIndependentVar( const double indep_var );
    
    //! Process Dependent Variable
    static inline double processDependentVar( const double dep_var );
  };
    
};

} // end FACEMC namespace
  
//-------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "DataProcessorBase_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_PROCESSOR_BASE_HPP

//---------------------------------------------------------------------------//
// end DataProcessorBase.hpp
//---------------------------------------------------------------------------//
