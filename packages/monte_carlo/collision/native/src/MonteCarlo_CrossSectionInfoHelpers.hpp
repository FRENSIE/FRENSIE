//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CrossSectionInfoHelpers.hpp
//! \author Alex Robinson
//! \brief  Cross section info helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CROSS_SECTION_INFO_HELPERS_HPP
#define MONTE_CARLO_CROSS_SECTION_INFO_HELPERS_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_RCP.hpp>

namespace MonteCarlo{

//! Extract the table info from the photoatom table info parameter list
void extractInfoFromPhotoatomTableInfoParameterList(
			const std::string& cross_sections_xml_directory,
			const std::string& photoatom_alias,
			const Teuchos::ParameterList& cross_section_table_info,
			std::string& data_file_path,
			std::string& data_file_type,
			std::string& data_file_table_name,
			int& data_file_start_line,
			double& atomic_weight );

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
			double& temperature );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CROSS_SECTION_INFO_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CrossSectionInfoHelpers.hpp
//---------------------------------------------------------------------------//
