//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomFactory.cpp
//! \author Alex Robinson
//! \brief  The photoatom factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_ContractException.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Constructor
PhotoatomFactory::PhotoatomFactory( 
		    const std::string& cross_sections_xml_directory,
		    const Teuchos::ParameterList& cross_section_table_info,
		    const boost::unordered_set<std::string>& nuclide_aliases )
  : d_photoatom_name_map()
{
  // The photoatom that will be created
  Teuchos::RCP<Photoatom> photoatom;

  // Create each photoatom in the set
}

// Create the map of photoatoms
void PhotoatomFactory::createPhotoatom(
		    boost::unordered_map<std::string,Teuchos::RCP<Photoatom> >&
		    photoatom_map ) const
{
  // Reset the photoatom map
  photoatom_map.clear();

  // Copy the stored map
  photoatom_map.insert( d_photoatom_name_map.begin(),
			d_photoatom_name_map.end() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomFactory.cpp
//---------------------------------------------------------------------------//
