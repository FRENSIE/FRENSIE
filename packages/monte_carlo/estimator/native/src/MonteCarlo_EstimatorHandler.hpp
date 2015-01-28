//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorHandler.hpp
//! \author Alex Robinson
//! \brief  Estimator handler class declaration.
//! 
//---------------------------------------------------------------------------//

#ifndef FACEMC_ESTIMATOR_HANDLER_HPP
#define FACEMC_ESTIMATOR_HANDLER_HPP

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_Estimator.hpp"

namespace MonteCarlo{

//! The estimator handler class (singleton)
class EstimatorHandler{

public:
  
  //! Add an estimator to the handler
  template<typename EstimatorType, typename EntityHandle>
  static void addEstimator( Teuchos::RCP<EstimatorType>& estimator,
			    const Teuchos::Array<EntityHandle>& entity_ids );

  //! Add a global estimator to the handler
  template<typename EstimatorType>
  static void addGlobalEstimator( Teuchos::RCP<EstimatorType>& estimator );

  //! Return the number of estimators that have been added
  static unsigned getNumberOfEstimators();

  //! Enable support for multiple threads
  static void enableThreadSupport( const unsigned num_threads );

  //! Commit the estimator history contributions
  static void commitEstimatorHistoryContributions();

  //! Print the estimators
  static void printEstimators( std::ostream& os,
			       const double num_histories,
			       const double start_time,
			       const double end_time );

  //! Reset estimator data
  static void resetEstimatorData();

  //! Reduce estimator data on all processes in comm and collect on the root
  static void reduceEstimatorData( 
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process );

  //! Export the estimator data and process
  static void exportEstimatorData(const std::string& data_file_name,
				  const unsigned long long last_history_number,
				  const unsigned long long histories_completed,
				  const double start_time,
				  const double end_time,
				  const bool process_data );
  
private:

  // Constructor
  EstimatorHandler();

  // Typedef for the estimator list
  typedef Teuchos::Array<Teuchos::RCP<Estimator> > EstimatorArray;

  static EstimatorArray master_array;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_EstimatorHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_ESTIMATOR_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHandler.hpp
//---------------------------------------------------------------------------//
