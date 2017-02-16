//---------------------------------------------------------------------------//
//!
//! \file   Utility_DataProcessor.hpp
//! \author Alex Robinson
//! \brief  Data Processor base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DATA_PROCESSOR_HPP
#define UTILITY_DATA_PROCESSOR_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_DataProcessingPolicy.hpp"
#include "Utility_ArrayTraits.hpp"
#include "Utility_QuantityTraits.hpp"

/*! \defgroup data_proc Data Processing
 *
 * A data processing interface is defined which allows the necessary data to
 * be processed in very simple way. Each type of particle has its own data
 * processor defined, which implements the abstract data processing interface.
 */

namespace Utility{

/*! \brief Abstract base class which defines the data processing interface
 *
 * This abstract base class defines the interface that is used to process all
 * data files. A variety of useful protected member functions are also defined.
 * These protected member functions comprise the low level data processing
 * functionality that is needed to process any data file.
 * \ingroup data_proc
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

  //! Process the data points in a table of continuous data.
  template<typename DataProcessingPolicy,
	   TupleMember indepMember,
	   TupleMember depMember,
	   typename Tuple>
  static void processContinuousData( Teuchos::Array<Tuple> &data );

  //! Remove elements with a tuple member less than the specified value
  template<TupleMember member,
	   typename Tuple>
  static void removeElementsLessThanValue( Teuchos::Array<Tuple> &data,
					   const double value );

  //! Remove elements with a tuple member greater than the specified value
  template<TupleMember member,
	   typename Tuple>
  static void removeElementsGreaterThanValue( Teuchos::Array<Tuple> &data,
					      const double value );

  //! Eliminate adjacent data points with the same values.
  template<TupleMember member,
	   typename Tuple>
  static void coarsenConstantRegions( Teuchos::Array<Tuple> &data );

  //! Calculate the slope between each pair of data points.
  template<TupleMember indepMember,
	   TupleMember depMember,
	   TupleMember slopeMember,
	   typename Array>
  static void calculateSlopes( Array &data );

  //! Create a cdf from an array of data using a taylor series expansion to O(2)
  template<TupleMember indepMember,
	   TupleMember pdfMember,
	   TupleMember cdfMember,
	   typename Array>
  static typename QuantityTraits<typename GetMemberType<cdfMember,typename ArrayTraits<Array>::value_type>::type>::template GetQuantityToPowerType<-1>::type
  calculateContinuousCDF( Array &data,
			  const bool normalize = true );

  //! Create a pdf from an array of data using a first order, lin. approx.
  template<TupleMember indepMember,
	   TupleMember pdfMember,
	   TupleMember cdfMember,
	   typename Array>
  static void calculateContinuousPDF( Array &data );

  //! Create a discrete CDF from an array of data.
  template<TupleMember pdfMember,
	   TupleMember cdfMember,
	   typename Tuple>
  static void calculateDiscreteCDF( Teuchos::Array<Tuple> &data );

  //! Copy the data in the desired tuple member of the original tuple to the desired tuple member of the copy tuple.
  template<TupleMember origMember,
	   TupleMember copyMember,
	   typename OrigArray,
	   typename CopyArray>
  static void copyTupleMemberData( const OrigArray &orig_data,
			    CopyArray &copy_data );

  //! Swap the data in a desired tuple member with the data in another tuple member
  template<TupleMember member1,
	   TupleMember member2,
	   typename Array>
  static void swapTupleMemberData( Array &data );

  //! Convert an unsigned int to an electron shell string
  static std::string uintToShellStr( const unsigned int shell );

};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Utility_DataProcessor_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_DATA_PROCESSOR_HPP

//---------------------------------------------------------------------------//
// end Utility_DataProcessor.hpp
//---------------------------------------------------------------------------//

