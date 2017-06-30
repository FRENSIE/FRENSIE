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

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_DataProcessingPolicy.hpp"
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
	   size_t indepMember,
	   size_t depMember,
           template<typename,typename...> class STLCompliantContainer,
	   typename Tuple>
  static void processContinuousData( STLCompliantContainer<Tuple>& data );

  //! Remove elements with a tuple member less than the specified value
  template<size_t member,
           template<typename,typename...> class STLCompliantContainer,
	   typename Tuple>
  static void removeElementsLessThanValue( STLCompliantContainer<Tuple> &data,
					   const double value );

  //! Remove elements with a tuple member greater than the specified value
  template<size_t member,
           template<typename,typename...> class STLCompliantContainer,
	   typename Tuple>
  static void removeElementsGreaterThanValue(
                                            STLCompliantContainer<Tuple>& data,
                                            const double value );

  //! Eliminate adjacent data points with the same values.
  template<size_t member,
           template<typename,typename...> class STLCompliantContainer,
	   typename Tuple>
  static void coarsenConstantRegions( STLCompliantContainer<Tuple>& data );

  //! Calculate the slope between each pair of data points.
  template<size_t indepMember,
	   size_t depMember,
	   size_t slopeMember,
           template<typename,typename...> class STLCompliantContainer,
	   typename Tuple>
  static void calculateSlopes( STLCompliantContainer<Tuple>& data );

  //! Create a cdf from an array of data using a taylor series expansion to O(2)
  template<size_t indepMember,
	   size_t pdfMember,
	   size_t cdfMember,
           template<typename,typename...> class STLCompliantContainer,
	   typename Tuple>
  static typename QuantityTraits<typename TupleElement<cdfMember,Tuple>::type>::template GetQuantityToPowerType<-1>::type
  calculateContinuousCDF( STLCompliantContainer<Tuple>& data,
			  const bool normalize = true );

  //! Create a pdf from an array of data using a first order, lin. approx.
  template<size_t indepMember,
	   size_t pdfMember,
	   size_t cdfMember,
	   template<typename,typename...> class STLCompliantContainer,
           typename Tuple>
  static void calculateContinuousPDF( STLCompliantContainer<Tuple>& data );

  //! Create a discrete CDF from an array of data.
  template<size_t pdfMember,
	   size_t cdfMember,
           template<typename,typename...> class STLCompliantContainer,
	   typename Tuple>
  static void calculateDiscreteCDF( STLCompliantContainer<Tuple>& data );

  //! Copy the data in the desired tuple member of the original tuple to the desired tuple member of the copy tuple.
  template<size_t origMember,
	   size_t copyMember,
           template<typename,typename...> class STLCompliantContainerA,
           template<typename,typename...> class STLCompliantContainerB,
           typename TupleA,
	   typename TupleB>
  static void copyTupleMemberData(
                               const STLCompliantContainerA<TupleA>& orig_data,
                               STLCompliantContainerB<TupleB>& copy_data );

  //! Swap the data in a desired tuple member with the data in another tuple member
  template<size_t member1,
	   size_t member2,
           template<typename,typename...> class STLCompliantContainer,
	   typename Tuple>
  static void swapTupleMemberData( STLCompliantContainer<Tuple>& data );

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

