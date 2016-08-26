//---------------------------------------------------------------------------//
//!
//! \file   Data_PhotonuclearXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  The photonuclear xsdir entry class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_PhotonuclearXsdirEntry.hpp"
#include "Data_CrossSectionsXMLProperties.hpp"

namespace Data{

// Return the table alias
const std::string& PhotonuclearXsdirEntry::getTableAlias() const
{
  return d_alias;
}

// Add information to parameter list
void PhotonuclearXsdirEntry::addInfoToParameterList(
				 Teuchos::ParameterList& parameter_list ) const
{
  parameter_list.set( CrossSectionsXMLProperties::photonuclear_file_path_prop,
                      this->getTableFilePath() );

  parameter_list.set( CrossSectionsXMLProperties::photonuclear_file_type_prop,
                      CrossSectionsXMLProperties::ace_file );

  parameter_list.set( CrossSectionsXMLProperties::photonuclear_table_name_prop,
                      this->getTableName() );

  parameter_list.set<int>(
                 CrossSectionsXMLProperties::photonuclear_file_start_line_prop,
                 this->getTableFileStartLine() );

  if( !parameter_list.isParameter(
                             CrossSectionsXMLProperties::atomic_number_prop ) )
  {
    parameter_list.set<int>( CrossSectionsXMLProperties::atomic_number_prop,
                             d_atomic_number );
  }

  if( !parameter_list.isParameter(
                        CrossSectionsXMLProperties::atomic_mass_number_prop ) )
  {
    parameter_list.set<int>(
                           CrossSectionsXMLProperties::atomic_mass_number_prop,
                           d_atomic_mass_number );
  }

  if( !parameter_list.isParameter(
                             CrossSectionsXMLProperties::isomer_number_prop ) )
  {
    parameter_list.set<int>( CrossSectionsXMLProperties::isomer_number_prop,
                             d_isomer_number );
  }

  if( !parameter_list.isParameter(
                       CrossSectionsXMLProperties::atomic_weight_ratio_prop ) )
  {
    parameter_list.set( CrossSectionsXMLProperties::atomic_weight_ratio_prop,
                        this->getTableAtomicWeightRatio() );
  }
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_PhotonuclearXsdirEntry.cpp
//---------------------------------------------------------------------------//
