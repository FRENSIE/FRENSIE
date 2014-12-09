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

  //! Return the number of estimators that have been added
  static unsigned getNumberOfEstimators();

  //! Commit the estimator history contributions
  static void commitEstimatorHistoryContributions();

  //! Print the estimators
  static void printEstimators( std::ostream& os,
			       const double num_histories,
			       const double start_time,
			       const double end_time );

  //! Export the estimator data
  static void exportEstimatorData( const std::string& data_file_name,
				   const unsigned last_history_number,
				   const unsigned histories_completed,
				   const double start_time,
				   const double end_time );

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
