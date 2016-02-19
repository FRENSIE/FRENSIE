//---------------------------------------------------------------------------//
//!
//! \file   facemcCore.hpp
//! \author Alex Robinson
//! \brief  main facemc function declaration
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationManager.hpp"

// The simulation manager
extern std::shared_ptr<MonteCarlo::SimulationManager> facemc_manager;

//! The core facemc function (problem setup and execution)
int facemcCore( int argc, char** argv );

//---------------------------------------------------------------------------//
// end facemcCore.hpp
//---------------------------------------------------------------------------//
