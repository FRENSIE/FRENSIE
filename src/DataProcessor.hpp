//---------------------------------------------------------------------------//
// \file   DataProcessor.hpp
// \author Alex Robinson
// \brief  Data Processor base class declaration
//---------------------------------------------------------------------------//

#ifndef DATA_PROCESSOR_HPP
#define DATA_PROCESSOR_HPP

// Std Lib Includes
#include <string>

// FACEMC Includes
#include "Tuple.hpp"

namespace FACEMC{

class DataProcessor
{

public:

  //-------------------------------------------------------------------------//
  // Data Processing Interface
  //-------------------------------------------------------------------------//

  //! Process Data Files
  virtual void processDataFiles() = 0;

protected:

  /*!
   * \brief Calculate the slope between each pair of data points and store
   * at the desired tuple member. This function will only compile if the desired
   * tuple member is actually available in tuple T.
   */
  template<TupleMember member, 
	   typename T, 
	   template<typename> class Array>
  void calculateSlopesAtTupleMember( Array<T> &data );

  /*!
   * \brief Create a continuous CDF from an array of data and store at the 
   * desired tuple member. This function will only compile if the desired 
   * tuple member is actually available in tuple T.
   */
  template<TupleMember member,
	   typename T,
	   template<typename> class Array>
  void calculateContinuousCDFAtTupleMember( Array<T> &data );

  /*!
   * \brief Create a discrete CDF IN PLACE from an array of data and store at 
   * the desired tuple member. This function will only compile if the desired 
   * tuple member is actually available in tuple T.
   */
  template<TupleMember member,
	   typename T,
	   template<typename> class Array>
  void calculateDiscreteCDFInPlaceAtTupleMember( Array<T> &data );

  /*!
   * \brief Swap the data in the desired tuple members.
   */
  template<TupleMember member1, 
	   TupleMember member2,
	   typename T,
	   template<typename> class Array>
  void swapDataAtTupleMembers( Array<T> &data );

  /*!
   * \brief Convert an unsigned int to an electron shell string
   */
  std::string uintToShellStr( unsigned int shell );

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
 
