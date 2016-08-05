//---------------------------------------------------------------------------//
//!
//! \file   DataGen_SAlphaBetaXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  The S(alpha,beta) xsdir entry class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_SAlphaBetaXsdirEntry.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"

namespace DataGen{

// Return the table alias
const std::string& SAlphaBetaXsdirEntry::getTableAlias() const
{
  return d_alias;
}

// Add information to parameter list
void SAlphaBetaXsdirEntry::addInfoToParameterList(
				 Teuchos::ParameterList& parameter_list ) const
{
  parameter_list.set(
	   MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_file_path_prop,
	   this->getTableFilePath() );

  parameter_list.set(
	   MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_file_type_prop,
	   MonteCarlo::CrossSectionsXMLProperties::ace_file );

  parameter_list.set(
	  MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_table_name_prop,
	  this->getTableName() );

  parameter_list.set<int>(
     MonteCarlo::CrossSectionsXMLProperties::s_alpha_beta_file_start_line_prop,
     this->getTableFileStartLine() );

  parameter_list.set( MonteCarlo::CrossSectionsXMLProperties::temperature_prop,
		      this->getTableTemperatureMeV() );

}

} // end DataGen namespace
