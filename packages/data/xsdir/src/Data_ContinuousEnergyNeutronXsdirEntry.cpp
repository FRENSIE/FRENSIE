//---------------------------------------------------------------------------//
//!
//! \file   Data_ContinuousEnergyNeutronXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  The continuous energy neutron xsdir entry class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_ContinuousEnergyNeutronXsdirEntry.hpp"
#include "Data_CrossSectionsXMLProperties.hpp"

namespace Data{

// Return the table alias
const std::string& ContinuousEnergyNeutronXsdirEntry::getTableAlias() const
{
  return d_alias;
}

// Add information to parameter list
void ContinuousEnergyNeutronXsdirEntry::addInfoToParameterList(
				 Teuchos::ParameterList& parameter_list ) const
{
  parameter_list.set( CrossSectionsXMLProperties::nuclear_file_path_prop,
                      this->getTableFilePath() );

  parameter_list.set( CrossSectionsXMLProperties::nuclear_file_type_prop,
                      CrossSectionsXMLProperties::ace_file );

  parameter_list.set( CrossSectionsXMLProperties::nuclear_table_name_prop,
                      this->getTableName() );

  parameter_list.set<int>( 
                      CrossSectionsXMLProperties::nuclear_file_start_line_prop,
                      this->getTableFileStartLine() );

  parameter_list.set<int>( CrossSectionsXMLProperties::atomic_number_prop,
                           d_atomic_number );

  parameter_list.set<int>( CrossSectionsXMLProperties::atomic_mass_number_prop,
                           d_atomic_mass_number );

  parameter_list.set<int>( CrossSectionsXMLProperties::isomer_number_prop,
                           d_isomer_number );

  parameter_list.set( CrossSectionsXMLProperties::atomic_weight_ratio_prop,
                      this->getTableAtomicWeightRatio() );

  parameter_list.set( CrossSectionsXMLProperties::temperature_prop,
		      this->getTableTemperatureMeV() );
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_ContinuousEnergyNeutronXsdirEntry.cpp
//---------------------------------------------------------------------------//
