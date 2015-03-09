//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CrossSectionInfoHelpers.cpp
//! \author Alex Robinson
//! \brief  Cross section info helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CrossSectionInfoHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Extract the table info from the photoatom table info parameter list
void extractInfoFromPhotoatomTableInfoParameterList(
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
    data_file_path +=
      photoatom_table_info.get<std::string>( "photoatomic_file_path" );    
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << photoatom_alias <<
			   " is invalid! Please fix this entry." );
  
  try{
    data_file_type = 
      photoatom_table_info.get<std::string>( "photoatomic_file_type" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << photoatom_alias <<
			   " is invalid! Please fix this entry." );

  try{
    data_file_table_name = 
      photoatom_table_info.get<std::string>( "photoatomic_table_name" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << photoatom_alias <<
			   " is invalid! Please fix this entry." );

   try{
    data_file_start_line =
      photoatom_table_info.get<int>( "photoatomic_file_start_line" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << photoatom_alias <<
			   " is invalid! Please fix this entry." );
  
  try{
    atomic_weight = photoatom_table_info.get<double>( "atomic_weight_ratio" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << photoatom_alias <<
			   " is invalid! Please fix this entry." );

  atomic_weight *= Utility::PhysicalConstants::neutron_rest_mass_amu;
}

//! Extract the table info from the nuclide table info parameter list
void extractInfoFromNuclideTableInfoParameterList(
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
    data_file_path +=
      nuclide_table_info.get<std::string>( "nuclear_file_path" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );
  
  try{ 
    data_file_type = 
      nuclide_table_info.get<std::string>( "nuclear_file_type" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );

  try{
    data_file_table_name = 
      nuclide_table_info.get<std::string>( "nuclear_table_name" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );

  try{
    data_file_start_line = 
      nuclide_table_info.get<int>( "nuclear_file_start_line" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );
  
  try{
    atomic_number = nuclide_table_info.get<int>( "atomic_number" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );

  try{
    atomic_mass_number = nuclide_table_info.get<int>( "atomic_mass_number" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );
  
  try{
    isomer_number = nuclide_table_info.get<int>( "isomer_number" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );
  
  try{
    atomic_weight_ratio = 
      nuclide_table_info.get<double>( "atomic_weight_ratio" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );

  try{
    temperature = nuclide_table_info.get<double>( "temperature" );
  }
  EXCEPTION_CATCH_RETHROW( Teuchos::Exceptions::InvalidParameter,
			   "Error: cross section table entry "
			   << nuclide_alias <<
			   " is invalid! Please fix this entry." );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CrossSectionInfoHelpers.cpp
//---------------------------------------------------------------------------//
