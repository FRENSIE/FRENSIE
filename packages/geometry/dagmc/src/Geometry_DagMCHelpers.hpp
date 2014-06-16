//---------------------------------------------------------------------------//
//! 
//! \file   Geometry_DagMCHelpers.hpp
//! \author Alex Robinson
//! \brief  DagMC helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_HELPERS_HPP
#define GEOMETRY_DAGMC_HELPERS_HPP

// Std Lib Includes
#include <vector>
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Geometry_ModuleTraits.hpp"

namespace Geometry{

//! Initialize DagMC 
void initializeDagMC( 
	   const std::string& geometry_file_name, 
	   const std::vector<std::string>& property_names,
	   const double facet_tol = 0 );

//! Validate the properties that DagMC found in the geometry file
void validatePropertyNames( 
		      const std::vector<std::string>& available_property_names,
		      const std::vector<std::string>& valid_property_names,
		      std::string& invalid_property_names );

//! Validate the synonym names
void validateSynonymNames(const std::vector<std::string>& valid_property_names,
			  const std::map<std::string,std::string>& synonyms,
			  std::string& invalid_property_names );

/*! Return all of the property values associated with a property name and cell
 * id.
 */
void getCellPropertyValues( 
          const std::string& property,
          boost::unordered_map<ModuleTraits::InternalCellHandle,
			       std::vector<std::string> >&
	  cell_id_prop_val_map );

/*! Return all of the property values associated with a property name and 
 * surface id.
 */
void getSurfacePropertyValues( 
      const std::string& property,
      boost::unordered_map<ModuleTraits::InternalSurfaceHandle,
			   std::vector<std::string> >&
      surface_id_prop_val_map );

//! Return all of the cell ids with a property value
void getCellIdsWithPropertyValue(
	  const std::string& property,
          boost::unordered_map<std::string,
			       std::vector<ModuleTraits::InternalCellHandle> >&
	  prop_val_cell_id_map );

//! Return all of the surface ids with a property value
void getSurfaceIdsWithPropertyValue(
      const std::string& property,
      boost::unordered_map<std::string,
			   std::vector<ModuleTraits::InternalSurfaceHandle> >&
      prop_val_surface_id_map );
  
} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCHelpers.hpp
//---------------------------------------------------------------------------//
