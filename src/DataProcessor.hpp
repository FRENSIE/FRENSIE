//---------------------------------------------------------------------------//
// \file   DataProcessor.hpp
// \author Alex Robinson
// \brief  Data Processor base class declaration
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

  /*!
   * \brief Process the indepMember and the depMember using the desired 
   * processing policy. This function will only compile if the desired
   * tuple members are actually available in tuple Tuple.
   */
  template<typename DataProcessingPolicy,
	   TupleMember indepMember,
	   TupleMember depMember,
	   typename Tuple,
	   template<typename> class Array>
  void processContinuousData( Array<Tuple> &data );

  /*!
   * \brief Search the data array for constant regions and reduce the number
   * of bins in these regions to one. Only the Teuchos::Array can be used 
   * because the erase member function is needed.
   */
  template<TupleMember member,
	   typename Tuple>
  void coarsenConstantRegions( Teuchos::Array<Tuple> &data );

  /*!
   * \brief Calculate the slope between indepMember and depMember and store
   * at the slopeMember. This function will only compile if the desired
   * tuple members are actually available in tuple Tuple.
   */
  template<TupleMember indepMember, 
	   TupleMember depMember,
	   TupleMember slopeMember,
	   typename Tuple, 
	   template<typename> class Array>
  void calculateSlopes( Array<Tuple> &data );

  /*!
   * \brief Create a continuous CDF from an array of data and store at the 
   * desired tuple member. This function will only compile if the desired 
   * tuple member is actually available in tuple Tuple.
   */
  template<TupleMember indepMember,
	   TupleMember pdfMember,
	   TupleMember cdfMember,
	   typename Tuple,
	   template<typename> class Array>
  void calculateContinuousCDF( Array<Tuple> &data );

  /*!
   * \brief Create a discrete CDF from an array of data and store at 
   * the desired tuple member. To create the CDF in place the pdfMember and the
   * cdfMember should be the same. This function will only compile if the 
   * desired tuple member is actually available in tuple Tuple.
   */
  template<TupleMember pdfMember,
	   TupleMember cdfMember,
	   typename Tuple,
	   template<typename> class Array>
  void calculateDiscreteCDF( Array<Tuple> &data );

  /*!
   * \brief Swap the data in the desired tuple members. If the desired tuple
   * members have the same type, pass the same data array as the swap_data.
   */
  template<TupleMember member1, 
	   TupleMember member2,
	   typename Tuple1,
	   typename Tuple2,
	   template<typename> class Array>
  void swapTupleMemberData( const Array<Tuple1> &data,
			    Array<Tuple2> &swap_data );

  /*!
   * \brief Convert an unsigned int to an electron shell string
   */
  std::string uintToShellStr( unsigned int shell );

  /*!
   * \brief Policy struct for processing data tables that require log-log
   * interpolation between evaluated points.
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

  /*!
   * \brief Policy struct for processing data tables that require square-square
   * interpolation between data points.
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
 
