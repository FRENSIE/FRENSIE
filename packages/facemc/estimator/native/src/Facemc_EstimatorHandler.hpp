//---------------------------------------------------------------------------//
//!
//! \file   Facemc_EstimatorHandler.hpp
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
#include "Facemc_Estimator.hpp"

namespace Facemc{

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
  static void printEstimators( std::ostream& os );

private:

  // Constructor
  EstimatorHandler();

  // Typedef for the estimator list
  typedef Teuchos::Array<Teuchos::RCP<Estimator> > EstimatorArray;

  static EstimatorArray master_array;
};

} // end Facemc namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Facemc_EstimatorHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_ESTIMATOR_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Facemc_EstimatorHandler.hpp
//---------------------------------------------------------------------------//
