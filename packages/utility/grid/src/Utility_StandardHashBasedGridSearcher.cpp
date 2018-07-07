//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardHashBasedGridSearcher.cpp
//! \author Alex Robinson
//! \brief  The standard hash-based grid searcher
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_StandardHashBasedGridSearcher.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::StandardHashBasedGridSearcher<std::vector<double>,true> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::StandardHashBasedGridSearcher<std::vector<double>,true> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::StandardHashBasedGridSearcher<std::vector<double>,false> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::StandardHashBasedGridSearcher<std::vector<double>,false> );
  
//---------------------------------------------------------------------------//
// end Utility_StandardHashBasedGridSearcher.cpp
//---------------------------------------------------------------------------//
