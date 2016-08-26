//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  The electron-photon-relaxation xsdir entry class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationXsdirEntry.hpp"
#include "Data_CrossSectionsXMLProperties.hpp"

namespace Data{

// Return the table alias
const std::string& ElectronPhotonRelaxationXsdirEntry::getTableAlias() const
{
  return d_alias;
}

// Add information to parameter list
void ElectronPhotonRelaxationXsdirEntry::addInfoToParameterList(
				 Teuchos::ParameterList& parameter_list ) const
{
  parameter_list.set( CrossSectionsXMLProperties::photoatomic_file_path_prop,
                      this->getTableFilePath() );

  parameter_list.set( CrossSectionsXMLProperties::photoatomic_file_type_prop,
                      CrossSectionsXMLProperties::ace_file );

  parameter_list.set( CrossSectionsXMLProperties::photoatomic_table_name_prop,
                      this->getTableName() );

  parameter_list.set<int>(
                  CrossSectionsXMLProperties::photoatomic_file_start_line_prop,
                  this->getTableFileStartLine() );

  parameter_list.set( CrossSectionsXMLProperties::electroatomic_file_path_prop,
                      this->getTableFilePath() );

  parameter_list.set( CrossSectionsXMLProperties::electroatomic_file_type_prop,
                      CrossSectionsXMLProperties::ace_file );

  parameter_list.set(CrossSectionsXMLProperties::electroatomic_table_name_prop,
                     this->getTableName() );

  parameter_list.set<int>(
                CrossSectionsXMLProperties::electroatomic_file_start_line_prop,
                this->getTableFileStartLine() );

  if( !parameter_list.isParameter(
                             CrossSectionsXMLProperties::atomic_number_prop ) )
  {
    parameter_list.set<int>( CrossSectionsXMLProperties::atomic_number_prop,
                             d_atomic_number );
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
// end Data_ElectronPhotonRelaxationXsdirEntry.cpp
//---------------------------------------------------------------------------//
