//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventHandlerFactory.hpp
//! \author Alex Robinson
//! \brief  The event handler factory base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_EVENT_HANDLER_FACTORY_HPP
#define MONTE_CARLO_EVENT_HANDLER_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_EventHandler.hpp"

//! The event handler factory (abstract)
class EventHandlerFactory
{

public:

  //! Constructor
  EventHandlerFactory( std::ostream& os_warn = std::cerr );

  //! Destructor
  virtual ~EventHandlerFactory()
  { /* ... */ }

  //! Create the event handler
  virtual void createHandler( 
                       std::shared_ptr<EventHandler>& event_handler,
                       const Teuchos::ParameterList& response_reps,
                       const Teuchos::ParameterList& observer_reps ) const = 0;

protected:

  //! Get the default surface current estimator name
  static const std::string& getDefaultSurfaceCurrentEstimatorName();

  //! Get the default surface flux estimator name
  static const std::string& getDefaultSurfaceFluxEstimatorName();

  //! Get the default cell pulse height estimator name
  static const std::string& getDefaultCellPulseHeightEstimatorName();

  //! Get the default cell track-length flux estimator name
  static const std::string& getDefaultCellTrackLengthFluxEstimatorName();

  //! Get the default cell collision flux estimator name
  static const std::string& getDefaultCellCollisionFluxEstimatorName();

  //! Get the default tet mesh track-length flux estimator name
  static const std::string& getDefaultTetMeshTrackLengthFluxEstimatorName();

  //! Test if an observer type is a cell pulse height estimator
  virtual bool isCellPulseHeightEstimator( 
                                      const std::string& observer_name ) const;

  //! Test if an observer type is a cell track length flux estimator
  virtual bool isCellTrackLengthFluxEstimator( 
				      const std::string& observer_name ) const;

  //! Test if an observer type is a cell collision flux estimator
  virtual bool isCellCollisionFluxEstimator(
                                      const std::string& observer_name ) const;

  //! Test if an observer type is a surface flux estimator
  virtual bool isSurfaceFluxEstimator(const std::string& observer_name ) const;

  //! Test if an observer type is a surface current estimator
  virtual bool isSurfaceCurrentEstimator( 
                                      const std::string& observer_name ) const;

  //! Test if an observer type is a tet mesh track length flux estimator
  virtual bool isTetMeshTrackLenghtFluxEstimator( 
                                      const std::string& observer_name ) const;

  //! Return the warning output stream
  std::ostream& getWarningOutputStream() const;

private:

  // The warning output stream
  std::ostream* d_os_warn;  
};

#endif // end MONTE_CARLO_EVENT_HANDLER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandlerFactory.hpp
//---------------------------------------------------------------------------//
