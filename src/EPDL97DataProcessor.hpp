//---------------------------------------------------------------------------//
// \file EPDL97DataProcessor.hpp
// \author Alex Robinson
// \brief EPDL97 data processor base Class declaration.
//---------------------------------------------------------------------------//

#ifndef EPDL97_DATA_PROCESSOR_HPP
#define EPDL97_DATA_PROCESSOR_HPP

// Std Lib Includes
#include <stdlib.h>
#include <stdio.h>
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "HDF5FileHandler.hpp"
#include "DataPoint.hpp"

namespace FACEMC{

class EPDL97DataProcessor
{

public:

  //! Default Constructor
  EPDL97DataProcessor()
  { /* ... */ }

  //! Destructor
  virtual ~EPDL97DataProcessor()
  { /* ... */ }

  //-------------------------------------------------------------------------//
  // Data Processing Interface
  //-------------------------------------------------------------------------//

  //! Process Data Files
  virtual void processDataFiles() = 0;

protected:

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
				  Teuchos::Array<DataPoint<double,double> > 
				   &data,
				  const double indep_var_min,
				  const double indep_var_max );

  //! Read two column table in EPDL file 
  template<typename DataProcessingPolicy>
  void readTwoColumnTable( FILE* datafile,
			   Teuchos::Array<DataPoint<double,double> &data );

  //! Skip three column table in EPDL file
  void skipThreeColumnTable( FILE* datafile );

  //! Read three column table in EPDL file
  void readThreeColumnTable( FILE* datafile,
			     Teuchos::Array<DataPoint<int,double,double> &data );

  //! Skip four column table in EPDL file
  void skipFourColumnTable( FILE* datafile );
  
  //! Read four column table in EPDL file
  void readFourColumnTable( FILE* datafile,
			    Teuchos::Array<DataPoint<int,int,double,double> > 
			     &data );

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

  // HDF5 File Handler
  HDF5FileHandler d_hdf5_file_handler;
    
};

} // end FACEMC namespace
  
//-------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "EPDL97DataProcessor_def.hpp"

//---------------------------------------------------------------------------//

#endif // end EPDL97_DATA_PROCESSOR_HPP

//---------------------------------------------------------------------------//
// end EPDL97DataProcessor.hpp
//---------------------------------------------------------------------------//
