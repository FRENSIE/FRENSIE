//---------------------------------------------------------------------------//
//!
//! \file   Data_SAlphaBetaXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  The S(alpha,beta) xsdir entry class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_SAlphaBetaXsdirEntry.hpp"
#include "Data_CrossSectionsXMLProperties.hpp"

namespace Data{

// Return the table alias
const std::string& SAlphaBetaXsdirEntry::getTableAlias() const
{
  return d_alias;
}

// Add information to parameter list
void SAlphaBetaXsdirEntry::addInfoToParameterList(
				 Teuchos::ParameterList& parameter_list ) const
{
  parameter_list.set( CrossSectionsXMLProperties::s_alpha_beta_file_path_prop,
                      this->getTableFilePath() );

  parameter_list.set( CrossSectionsXMLProperties::s_alpha_beta_file_type_prop,
                      CrossSectionsXMLProperties::ace_file );

  parameter_list.set( CrossSectionsXMLProperties::s_alpha_beta_table_name_prop,
                      this->getTableName() );

  parameter_list.set<int>(
                 CrossSectionsXMLProperties::s_alpha_beta_file_start_line_prop,
                 this->getTableFileStartLine() );

  parameter_list.set( CrossSectionsXMLProperties::temperature_prop,
		      this->getTableTemperatureMeV() );

}

} // end Data namespace
