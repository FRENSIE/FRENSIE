//---------------------------------------------------------------------------//
//!
//! \file   facemcCore.hpp
//! \author Alex Robinson
//! \brief  main facemc function declaration
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Comm.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationManager.hpp"

// The simulation manager
extern std::shared_ptr<MonteCarlo::SimulationManager> facemc_manager;

//! The core facemc function (problem setup and execution)
int facemcCore( int argc, 
                char** argv,
                Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm );

//---------------------------------------------------------------------------//
// end facemcCore.hpp
//---------------------------------------------------------------------------//
