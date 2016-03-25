//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEstimatorFactory.hpp
//! \author Alex Robinson
//! \brief  The standard estimator factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ESTIMATOR_FACTORY_HPP
#define MONTE_CARLO_STANDARD_ESTIMATOR_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_EstimatorFactory.hpp"

namespace MonteCarlo{

//! The standard estimator factory class
template<typename GeometryHandler>
class StandardEstimatorFactory : public EstimatorFactory
{
  
public:

  //! Constructor
  StandardEstimatorFactory( 
          const std::shared_ptr<EventHandler>& event_handler,
          const boost::unordered_map<unsigned,Teuchos::RCP<ResponseFunction> >&
          response_function_id_map,
          std::ostream* os_warn = &std::cerr )
  { GeometryHandler::geometry_handler_is_missing_specialization(); }

  //! Destructor
  ~StandardEstimatorFactory()
  { /* ... */ }

  //! Create and register cached estimators
  void createAndRegisterCachedEstimators()
  { GeometryHandler::geometry_handler_is_missing_specialization(); }
};

//! Helper function for creating an estimator factory instance
template<typename GeometryHandler>
inline std::shared_ptr<EstimatorFactory>
getEstimatorFactoryInstance( 
       const std::shared_ptr<EventHandler>& event_handler,
       const boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
       response_function_id_map,
       std::ostream* os_warn = &std::cerr )
{
  return std::shared_ptr<EstimatorFactory>( 
       new StandardEstimatorFactory<GeometryHandler>( event_handler,
                                                      response_function_id_map,
                                                      os_warn ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_ESTIMATOR_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEstimatorFactory.hpp
//---------------------------------------------------------------------------//
