//---------------------------------------------------------------------------//
//!
//! \file   DataProcessor.hpp
//! \author Alex Robinson
//! \brief  Data Processor base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_PROCESSOR_HPP
#define DATA_PROCESSOR_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "Tuple.hpp"

namespace FACEMC{

/*! \brief Abstract base class which defines the data processing interface
 * 
 * This abstract base class defines the interface that is used to process all
 * data files. A variety of useful protected member functions are also defined.
 * These protected member functions comprise the low level data processing
 * functionality that is needed to process any data file.
 */ 
class DataProcessor
{
  
public:
  
  //! Constructor
  DataProcessor()
  { /* ... */ }

  //! Destructor
  virtual ~DataProcessor()
  { /* ... */ }

  //-------------------------------------------------------------------------//
  // Data Processing Interface
  //-------------------------------------------------------------------------//

  //! Process Data Files
  virtual void processDataFiles() = 0;

protected:

  //! Process the data points in a table of continuous data.
  template<typename DataProcessingPolicy,
	   TupleMember indepMember,
	   TupleMember depMember,
	   typename Tuple>
  void processContinuousData( Teuchos::Array<Tuple> &data );

  //! Remove elements with a tuple member less than the specified value
  template<TupleMember member,
	   typename Tuple>
  void removeElementsLessThanValue( Teuchos::Array<Tuple> &data,
				    const double value );

  //! Remove elements with a tuple member greater than the specified value
  template<TupleMember member,
	   typename Tuple>
  void removeElementsGreaterThanValue( Teuchos::Array<Tuple> &data,
				       const double value );

  //! Eliminate adjacent data points with the same values.
  template<TupleMember member,
	   typename Tuple>
  void coarsenConstantRegions( Teuchos::Array<Tuple> &data );

  //! Calculate the slope between each pair of data points.
  template<TupleMember indepMember, 
	   TupleMember depMember,
	   TupleMember slopeMember,
	   typename Tuple,
	   template<typename> class Array>
  void calculateSlopes( Array<Tuple> &data );

  //! Create a cdf from an array of data using a taylor series expansion to O(2)
  template<TupleMember indepMember,
	   TupleMember pdfMember,
	   TupleMember cdfMember,
	   typename Tuple,
	   template<typename> class Array>
  void calculateContinuousCDF( Array<Tuple> &data );

  //! Create a discrete CDF from an array of data.
  template<TupleMember pdfMember,
	   TupleMember cdfMember,
	   typename Tuple>
  void calculateDiscreteCDF( Teuchos::Array<Tuple> &data );

  //! Copy the data in the desired tuple member of the original tuple to the desired tuple member of the copy tuple.
  template<TupleMember origMember, 
	   TupleMember copyMember,
	   typename origTuple,
	   typename copyTuple,
	   template<typename> class Array>
  void copyTupleMemberData( const Array<origTuple> &orig_data,
			    Array<copyTuple> &copy_data );

  //! Swap the data in a desired tuple member with the data in another tuple member
  template<TupleMember member1,
	   TupleMember member2,
	   typename Tuple,
	   template<typename> class Array>
  void swapTupleMemberData( Array<Tuple> &data );

  //! Convert an unsigned int to an electron shell string
  std::string uintToShellStr( const unsigned int shell );

  /*! \brief Policy struct for processing data tables that require log-log 
   * interpolation between evaluated points.
   * 
   * This policy class implements the data processing policy interface that is
   * expected by certain protected member functions of the DataProcessor base
   * class. All data processed with this policy will be converted to log-log
   * format. 
   */
  struct LogLogDataProcessingPolicy
  {
    //! Process Independent Variable
    template<typename T>
    static T processIndependentVar( const T indep_var );
    
    //! Process Dependent Variable
    template<typename T>
    static T processDependentVar( const T dep_var );
  };

  /*! \brief Policy struct for processing data tables that require square-square
   * interpolation between data points.
   *
   * This policy class implements the data processing policy interface that is
   * expected by certain protected member functions of the DataProcessor base
   * class. All data processed with this policy will be converted to 
   * square-square format. 
   */
  struct SquareSquareDataProcessingPolicy
  {
    //! Process Independent Variable
    template<typename T>
    static T processIndependentVar( const T indep_var );
    
    //! Process Dependent Variable
    template<typename T>
    static T processDependentVar( const T dep_var );
  };

};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "DataProcessor_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_PROCESSOR_HPP

//---------------------------------------------------------------------------//
// end DataProcessor.hpp
//---------------------------------------------------------------------------//
 
