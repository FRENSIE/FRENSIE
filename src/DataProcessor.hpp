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
   * \brief Process the indepMember and the depMember using the desired 
   * processing policy. This function will only compile if the desired
   * tuple members are actually available in tuple Tuple.
   */
  template<typename DataProcessingPolicy,
	   TupleMember indepMember,
	   TupleMember depMember,
	   typename Tuple,
	   template<typename> Array>
  void processData( Array<Tuple> &data );

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
   * tuple member is actually available in tuple T.
   */
  template<TupleMember indepMember,
	   TupleMember pdfMember,
	   TupleMember cdfMember,
	   typename Tuple,
	   template<typename> class Array>
  void calculateContinuousCDF( Array<Tuple> &data );

  /*!
   * \brief Create a discrete CDF from an array of data and store at 
   * the desired tuple member. By default, this function will calculate the CDF
   * in place. This function will only compile if the desired tuple member is 
   * actually available in tuple T.
   */
  template<TupleMember pdfMember,
	   TupleMember cdfMember = pdfMember,
	   typename Tuple,
	   template<typename> class Array>
  void calculateDiscreteCDF( Array<Tuple> &data );

  /*!
   * \brief Swap the data in the desired tuple members.
   */
  template<TupleMember member1, 
	   TupleMember member2,
	   typename Tuple,
	   template<typename> class Array>
  void swapMemberData( Array<Tuple> &data );

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
   * \brief Policy class for processing data tables that require square-square
   * interpolation between data points.
   */
  class SquareSquareDataProcessingPolicy
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
 
