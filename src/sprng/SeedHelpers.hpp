//---------------------------------------------------------------------------//
//!
//! \file    SeedHelpers.hpp
//! \author  ?
//! \brief   Declaration of seed helper functions.
//! \details This file originally appeared in the sprng4 library. It has been
//!          modified by Alex Robinson (aprobinson@wisc.edu) to better support
//!          the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef SEED_HELPERS_HPP
#define SEED_HELPERS_HPP

namespace sprng{

//! Make a new seed from the time
int make_new_seed();

//! Make a new seed from the time and broadcast to all procs
int make_new_seed_mpi();

} // end namespace sprng

//---------------------------------------------------------------------------//
// Definition includes.
//---------------------------------------------------------------------------//

#include "SeedHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end SEED_HELPERS_HPP

//---------------------------------------------------------------------------//
// end SeedHelpers.hpp
//---------------------------------------------------------------------------//

