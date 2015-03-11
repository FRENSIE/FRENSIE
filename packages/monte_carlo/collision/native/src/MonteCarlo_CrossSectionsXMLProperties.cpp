//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CrossSectionsXMLProperties.cpp
//! \author Alex Robinson
//! \brief  cross_sections.xml file properties and helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Initialize the static member data
const std::string CrossSectionsXMLProperties::nuclear_file_path_prop =  
  "nuclear_file_path";
const std::string CrossSectionsXMLProperties::nuclear_file_type_prop = 
  "nuclear_file_type";
const std::string CrossSectionsXMLProperties::nuclear_table_name_prop = 
  "nuclear_table_name";
const std::string CrossSectionsXMLProperties::nuclear_file_start_line_prop = 
  "nuclear_file_start_line";
const std::string CrossSectionsXMLProperties::photoatomic_file_path_prop = 
  "photoatomic_file_path";
const std::string CrossSectionsXMLProperties::photoatomic_file_type_prop = 
  "photoatomic_file_type";
const std::string CrossSectionsXMLProperties::photoatomic_table_name_prop = 
  "photoatomic_table_name";
const std::string CrossSectionsXMLProperties::photoatomic_file_start_line_prop=
  "photoatomic_file_start_line";
const std::string CrossSectionsXMLProperties::photonuclear_file_path_prop = 
  "photonuclear_file_path";
const std::string CrossSectionsXMLProperties::photonuclear_file_type_prop = 
  "photonuclear_file_type";
const std::string CrossSectionsXMLProperties::photonuclear_table_name_prop = 
  "photonuclear_table_name";
const std::string 
CrossSectionsXMLProperties::photonuclear_file_start_line_prop = 
  "photonuclear_file_start_line";
const std::string CrossSectionsXMLProperties::electroatomic_file_path_prop = 
  "electroatomic_file_path";
const std::string CrossSectionsXMLProperties::electroatomic_file_type_prop = 
  "electroatomic_file_type";
const std::string CrossSectionsXMLProperties::electroatomic_table_name_prop = 
  "electroatomic_table_name";
const std::string 
CrossSectionsXMLProperties::electroatomic_file_start_line_prop = 
  "electroatomic_file_start_line";
const std::string CrossSectionsXMLProperties::sab_file_path_prop = 
  "sab_file_path";
const std::string CrossSectionsXMLProperties::sab_file_type_prop = 
  "sab_file_type";
const std::string CrossSectionsXMLProperties::sab_table_name_prop = 
  "sab_table_name";
const std::string CrossSectionsXMLProperties::sab_file_start_line_prop = 
  "sab_file_start_line";
const std::string CrossSectionsXMLProperties::atomic_number_prop = 
  "atomic_number";
const std::string CrossSectionsXMLProperties::atomic_mass_number_prop = 
  "atomic_mass_number";
const std::string CrossSectionsXMLProperties::isomer_number_prop = 
  "isomer_number";
const std::string CrossSectionsXMLProperties::atomic_weight_ratio_prop = 
  "atomic_weight_ratio";
const std::string CrossSectionsXMLProperties::temperature_prop = 
  "temperature";
const std::string CrossSectionsXMLProperties::ace_file = "ACE";
const std::string CrossSectionsXMLProperties::native_file = "Native";

// Extract the table info from the photoatom table info parameter list
void 
CrossSectionsXMLProperties::extractInfoFromPhotoatomTableInfoParameterList(
			const std::string& cross_sections_xml_directory,
			const std::string& photoatom_alias,
			const Teuchos::ParameterList& cross_section_table_info,
			std::string& data_file_path,
			std::string& data_file_type,
			std::string& data_file_table_name,
			int& data_file_start_line,
			double& atomic_weight )
{
  Teuchos::ParameterList photoatom_table_info;
 
  try{
    photoatom_table_info = cross_section_table_info.sublist( photoatom_alias );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
			    "There is no data present in the "
			    "cross_sections.xml file at "
			    << cross_sections_xml_directory <<
			    " for atom " << photoatom_alias << "!" );
  
  data_file_path = cross_sections_xml_directory + "/";
  
  try{
    data_file_path +=photoatom_table_info.get<std::string>(
		      CrossSectionsXMLProperties::photoatomic_file_path_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << photoatom_alias <<
			   " is invalid! Please fix this entry." );
  
  try{
    data_file_type = photoatom_table_info.get<std::string>( 
		      CrossSectionsXMLProperties::photoatomic_file_type_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << photoatom_alias <<
			   " is invalid! Please fix this entry." );

  try{
    data_file_table_name = photoatom_table_info.get<std::string>( 
		     CrossSectionsXMLProperties::photoatomic_table_name_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << photoatom_alias <<
			   " is invalid! Please fix this entry." );

   try{
    data_file_start_line = photoatom_table_info.get<int>( 
	        CrossSectionsXMLProperties::photoatomic_file_start_line_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << photoatom_alias <<
			   " is invalid! Please fix this entry." );
  
  try{
    atomic_weight = photoatom_table_info.get<double>( 
			CrossSectionsXMLProperties::atomic_weight_ratio_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << photoatom_alias <<
			   " is invalid! Please fix this entry." );

  atomic_weight *= Utility::PhysicalConstants::neutron_rest_mass_amu;
}

// Extract the table info from the electroatom table info parameter list
void 
CrossSectionsXMLProperties::extractInfoFromElectroatomTableInfoParameterList(
			const std::string& cross_sections_xml_directory,
			const std::string& electroatom_alias,
			const Teuchos::ParameterList& cross_section_table_info,
			std::string& data_file_path,
			std::string& data_file_type,
			std::string& data_file_table_name,
			int& data_file_start_line,
			double& atomic_weight )
{
  Teuchos::ParameterList electroatom_table_info;
 
  try{
    electroatom_table_info = 
      cross_section_table_info.sublist( electroatom_alias );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
			    "There is no data present in the "
			    "cross_sections.xml file at "
			    << cross_sections_xml_directory <<
			    " for atom " << electroatom_alias << "!" );
  
  data_file_path = cross_sections_xml_directory + "/";
  
  try{
    data_file_path += electroatom_table_info.get<std::string>(
		    CrossSectionsXMLProperties::electroatomic_file_path_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << electroatom_alias <<
			   " is invalid! Please fix this entry." );
  
  try{
    data_file_type = electroatom_table_info.get<std::string>( 
		    CrossSectionsXMLProperties::electroatomic_file_type_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << electroatom_alias <<
			   " is invalid! Please fix this entry." );

  try{
    data_file_table_name = electroatom_table_info.get<std::string>( 
		   CrossSectionsXMLProperties::electroatomic_table_name_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << electroatom_alias <<
			   " is invalid! Please fix this entry." );

   try{
    data_file_start_line = electroatom_table_info.get<int>( 
	      CrossSectionsXMLProperties::electroatomic_file_start_line_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << electroatom_alias <<
			   " is invalid! Please fix this entry." );
  
  try{
    atomic_weight = electroatom_table_info.get<double>( 
			CrossSectionsXMLProperties::atomic_weight_ratio_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << electroatom_alias <<
			   " is invalid! Please fix this entry." );

  atomic_weight *= Utility::PhysicalConstants::neutron_rest_mass_amu;
}

// Extract the table info from the nuclide table info parameter list
void CrossSectionsXMLProperties::extractInfoFromNuclideTableInfoParameterList(
			const std::string& cross_sections_xml_directory,
			const std::string& nuclide_alias,
			const Teuchos::ParameterList& cross_section_table_info,
			std::string& data_file_path,
			std::string& data_file_type,
			std::string& data_file_table_name,
			int& data_file_start_line,
			int& atomic_number,
			int& atomic_mass_number,
			int& isomer_number,
			double& atomic_weight_ratio,
			double& temperature )
{
  Teuchos::ParameterList nuclide_table_info;
  
  try{
    nuclide_table_info = cross_section_table_info.sublist( nuclide_alias );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
			    "There is no data present in the "
			    "cross_sections.xml file at "
			    << cross_sections_xml_directory <<
			    " for nuclide " << nuclide_alias << "!" );

  data_file_path = cross_sections_xml_directory + "/";

  try{
    data_file_path += nuclide_table_info.get<std::string>( 
			  CrossSectionsXMLProperties::nuclear_file_path_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );
  
  try{ 
    data_file_type = nuclide_table_info.get<std::string>( 
			  CrossSectionsXMLProperties::nuclear_file_type_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );

  try{
    data_file_table_name = nuclide_table_info.get<std::string>( 
			 CrossSectionsXMLProperties::nuclear_table_name_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );

  try{
    data_file_start_line = nuclide_table_info.get<int>( 
		    CrossSectionsXMLProperties::nuclear_file_start_line_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );
  
  try{
    atomic_number = nuclide_table_info.get<int>( 
			      CrossSectionsXMLProperties::atomic_number_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );

  try{
    atomic_mass_number = nuclide_table_info.get<int>( 
			 CrossSectionsXMLProperties::atomic_mass_number_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );
  
  try{
    isomer_number = nuclide_table_info.get<int>( 
			      CrossSectionsXMLProperties::isomer_number_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );
  
  try{
    atomic_weight_ratio = 
      nuclide_table_info.get<double>( 
			CrossSectionsXMLProperties::atomic_weight_ratio_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );

  try{
    temperature = nuclide_table_info.get<double>( 
				CrossSectionsXMLProperties::temperature_prop );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CrossSectionsXMLProperties.cpp
//---------------------------------------------------------------------------//
