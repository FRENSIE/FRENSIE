//---------------------------------------------------------------------------//
//! 
//! \file   DagMCHelpers.hpp
//! \author Alex Robinson
//! \brief  DagMC helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef DAGMC_HELPERS_HPP
#define DAGMC_HELPERS_HPP

// Std Lib Includes
#include <vector>
#include <string>

namespace FACEMC{

//! Initialize DagMC 
void initializeDagMC( const std::string& geometry_file_name, 
		      const std::vector<std::string>& property_names,
		      const double facet_tol = 0 );

//! Validate the properties that DagMC found in the geometry file
void validatePropertyNames( 
		      const std::vector<std::string>& available_property_names,
		      const std::vector<std::string>& valid_property_names,
		      std::string& invalid_property_names );

} // end FACEMC namespace

#endif // end DAGMC_HELPERS_HPP

//---------------------------------------------------------------------------//
// end DagMCHelpers.hpp
//---------------------------------------------------------------------------//
