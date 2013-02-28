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
#include <fstream>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "HDF5FileHandler.hpp"
#include "Tuple.hpp"

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
  void readFirstTableHeader( std::ifstream &datafile,
			     unsigned int &atomic_number,
			     unsigned int &outgoing_particle_designator,
			     double &atomic_weight,
			     unsigned int &interpolation_flag );

  //! Read the second table header
  // \brief Read the second EPDL, EADL or EEDL table header and extract info
  // \param datafile EPDL, EADL or EEDL file
  // \param reaction_type Reaction type identifier (see EPDL doc files)
  // \param electron_shell Electron shell identifier for table
  void readSecondTableHeader( std::ifstream &datafile,
			      unsigned int &reaction_type,
			      unsigned int &electron_shell );
  
  //! Skip two column table in EPDL file
  void skipTwoColumnTable( std::ifstream &datafile );

  //! Read two column table in EPDL file within specified range
  // \brief T is assumed to be a FACEMC::Tuple struct
  template<typename DataProcessingPolicy, 
	   typename T, 
	   template<typename> class Array>
  void readTwoColumnTableInRange( std::ifstream &datafile,
				  Array<T> &data,
				  const double indep_var_min,
				  const double indep_var_max );

  //! Read two column table in EPDL file 
  // \brief T is assumed to be a FACEMC::Tuple struct
  template<typename DataProcessingPolicy,
	   typename T,
	   template<typename> class Array>
  void readTwoColumnTable( std::ifstream &datafile,
			   Array<T> &data );

  //! Skip three column table in EPDL file
  void skipThreeColumnTable( std::ifstream &datafile );

  //! Read three column table in EPDL file
  void readThreeColumnTable( std::ifstream &datafile,
			     Teuchos::Array<Trip<unsigned int,double,double> > &data );

  //! Skip four column table in EPDL file
  void skipFourColumnTable( std::ifstream &datafile );
  
  //! Read four column table in EPDL file
  void readFourColumnTable( std::ifstream &datafile,
			    Teuchos::Array<Quad<unsigned int,unsigned int,double,double> > 
			     &data );

  /*! 
   * \brief Create the desired type from a printed fortran style fixed-width 
   * float. Undefined behavior is likely for types other than double and int.
   * Because this function will be called ~1e6 times while processing the
   * entire EPDL Library it has been inlined.
   */
  template<typename T>
  T extractValue( std::string mantissa,
		  std::string exponent );

  /*!
   * \brief Calculate the slope between each pair of data points.
   * This function will only compile if the FACEMC::Trip<double,double,double>
   * or the FACEMC::Quad<double,double,double,double> structs are used as 
   * the first template parameter. The slope values will be stored in the 
   * third tuple position.
   */
  template<typename T,template<typename> class Array>
  void calculateSlopesAtThirdTupleLoc( Array<T> &data );

  /*!
   * \brief Create a continuous CDF from an array of data using a Taylor 
   * Series expansion to second order. The second derivative is approximated as 
   * (/_\pdf)/(/_\indep). The cdf values will be stored in the fourth tuple
   * position.
   */
  template<typename T,template<typename> class Array>
  void createContinuousCDFAtFourthTupleLoc( Array<T> &data );

  /*!
   * \brief Create a discrete CDF from an array of data. The CDF will
   * be calculated in place (second tuple location).
   */
  template<typename T,template<typename> class Array>
  void createDiscreteCDFAtSecondTupleLoc( Array<T> &data );

  /*!
   * \brief Create a discrete CDF from an array of data. The CDF will
   * be calculated in place (third tuple location).
   */
  template<typename T,template<typename> class Array>
  void createDiscreteCDFAtThirdTupleLoc( Array<T> &data );

  //! Convert an EPDL shell integer to a shell name
  std::string uintToShellStr( const unsigned int shell );

  /*!
   * \brief Policy class for processing data tables that require log-log
   * interpolation between evaluated points.
   */
  class LogLogDataProcessingPolicy
  {
  public:
    //! Process Independent Variable
    static double processIndependentVar( const double indep_var );
    
    //! Process Dependent Variable
    static double processDependentVar( const double dep_var );
  };

  /*!
   * \brief Policy class for processing data tables that require linear-log
   * interpolation between evaluated points.
   */
   class LinearLogDataProcessingPolicy
   {
   public:
     //! Process Independent Variable
     static double processIndependentVar( const double indep_var );
     
     //! Process Dependent Variable
     static double processDependentVar( const double dep_var );
   };

  /*!
   * \brief Policy class for processing data tables that require log-linear
   * interpolation between evaluated points.
   */
  class LogLinearDataProcessingPolicy
  {
  public:
    //! Process Independent Variable
    static double processIndependentVar( const double indep_var );
    
    //! Process Dependent Variable
    static double processDependentVar( const double dep_var );
  };

  /*!
   * \brief Policy class for processing data tables that require linear-linear
   * interpolation between data pointns.
   */
  class LinearLinearDataProcessingPolicy
  {
  public:
    //! Process Independent Variable
    static double processIndependentVar( const double indep_var );
    
    //! Process Dependent Variable
    static double processDependentVar( const double dep_var );
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
