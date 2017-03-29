//---------------------------------------------------------------------------//
//!
//! \file   Data_CrossSectionsXMLProperties.hpp
//! \author Alex Robinson
//! \brief  cross_sections.xml file properties and helper functions decls.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_CROSS_SECTIONS_XML_PROPERTIES_HPP
#define DATA_CROSS_SECTIONS_XML_PROPERTIES_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_RCP.hpp>

namespace Data{

//! The cross_sections.xml properties class
class CrossSectionsXMLProperties
{

public:

  static const std::string nuclear_file_path_prop;
  static const std::string nuclear_file_type_prop;
  static const std::string nuclear_table_name_prop;
  static const std::string nuclear_file_start_line_prop;
  static const std::string s_alpha_beta_file_path_prop;
  static const std::string s_alpha_beta_file_type_prop;
  static const std::string s_alpha_beta_table_name_prop;
  static const std::string s_alpha_beta_file_start_line_prop;
  static const std::string photoatomic_file_path_prop;
  static const std::string photoatomic_file_type_prop;
  static const std::string photoatomic_table_name_prop;
  static const std::string photoatomic_file_start_line_prop;
  static const std::string photonuclear_file_path_prop;
  static const std::string photonuclear_file_type_prop;
  static const std::string photonuclear_table_name_prop;
  static const std::string photonuclear_file_start_line_prop;
  static const std::string adjoint_photoatomic_file_path_prop;
  static const std::string adjoint_photoatomic_file_type_prop;
  static const std::string adjoint_photoatomic_table_name_prop;
  static const std::string adjoint_photoatomic_file_start_line_prop;
  static const std::string electroatomic_file_path_prop;
  static const std::string electroatomic_file_type_prop;
  static const std::string electroatomic_table_name_prop;
  static const std::string electroatomic_file_start_line_prop;
  static const std::string adjoint_electroatomic_file_path_prop;
  static const std::string adjoint_electroatomic_file_type_prop;
  static const std::string adjoint_electroatomic_table_name_prop;
  static const std::string adjoint_electroatomic_file_start_line_prop;
  static const std::string atomic_number_prop;
  static const std::string atomic_mass_number_prop;
  static const std::string isomer_number_prop;
  static const std::string atomic_weight_ratio_prop;
  static const std::string temperature_prop;
  static const std::string ace_file;
  static const std::string endl_file;
  static const std::string native_file;
  static const std::string moment_preserving_file;

  //! Extract the table info from the photoatom table info parameter list
  static void extractInfoFromPhotoatomTableInfoParameterList(
            const std::string& cross_sections_xml_directory,
            const std::string& photoatom_alias,
            const Teuchos::ParameterList& cross_section_table_info,
            std::string& data_file_path,
            std::string& data_file_type,
            std::string& data_file_table_name,
            int& data_file_start_line,
            double& atomic_weight );

  //! Extract the table info from the adjoint photoatom table info param list
  static void extractInfoFromAdjointPhotoatomTableInfoParameterList(
                        const std::string& cross_sections_xml_directory,
            const std::string& adjoint_photoatom_alias,
            const Teuchos::ParameterList& cross_section_table_info,
            std::string& data_file_path,
            std::string& data_file_type,
            std::string& data_file_table_name,
            int& data_file_start_line,
            double& atomic_weight );

  //! Extract the table info from the electroatom table info parameter list
  static void extractInfoFromElectroatomTableInfoParameterList(
            const std::string& cross_sections_xml_directory,
            const std::string& electroatom_alias,
            const Teuchos::ParameterList& cross_section_table_info,
            std::string& data_file_path,
            std::string& data_file_type,
            std::string& data_file_table_name,
            int& data_file_start_line,
            double& atomic_weight );

  //! Extract the table info from the adjoint electroatom table info param list
  static void extractInfoFromAdjointElectroatomTableInfoParameterList(
            const std::string& cross_sections_xml_directory,
            const std::string& adjoint_electroatom_alias,
            const Teuchos::ParameterList& cross_section_table_info,
            std::string& data_file_path,
            std::string& data_file_type,
            std::string& data_file_table_name,
            int& data_file_start_line,
            double& atomic_weight );                  

  //! Extract the table info from the nuclide table info parameter list
  static void extractInfoFromNuclideTableInfoParameterList(
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
};

} // end Data namespace

#endif // end DATA_CROSS_SECTIONS_XML_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_CrossSectionXMLProperties.hpp
//---------------------------------------------------------------------------//
