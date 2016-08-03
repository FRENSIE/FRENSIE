//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ContinuousEnergyNeutronXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  The continuous energy neutron xsdir entry class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_ContinuousEnergyNeutronXsdirEntry.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"

namespace DataGen{

// Return the table alias
const std::string& ContinuousEnergyNeutronXsdirEntry::getTableAlias() const
{
  return d_alias;
}

// Add information to parameter list
void ContinuousEnergyNeutronXsdirEntry::addInfoToParameterList(
				 Teuchos::ParameterList& parameter_list ) const
{
  parameter_list.set(
	        MonteCarlo::CrossSectionsXMLProperties::nuclear_file_path_prop,
		this->getTableFilePath() );

  parameter_list.set(
		MonteCarlo::CrossSectionsXMLProperties::nuclear_file_type_prop,
		MonteCarlo::CrossSectionsXMLProperties::ace_file );

  parameter_list.set(
	       MonteCarlo::CrossSectionsXMLProperties::nuclear_table_name_prop,
	       this->getTableName() );

  parameter_list.set<int>(
	  MonteCarlo::CrossSectionsXMLProperties::nuclear_file_start_line_prop,
	  this->getTableFileStartLine() );

  parameter_list.set<int>(
		    MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop,
		    d_atomic_number );

  parameter_list.set<int>(
	       MonteCarlo::CrossSectionsXMLProperties::atomic_mass_number_prop,
	       d_atomic_mass_number );

  parameter_list.set<int>(
		    MonteCarlo::CrossSectionsXMLProperties::isomer_number_prop,
		    d_isomer_number );

  parameter_list.set(
	      MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop,
	      this->getTableAtomicWeightRatio() );

  parameter_list.set( MonteCarlo::CrossSectionsXMLProperties::temperature_prop,
		      this->getTableTemperatureMeV() );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_ContinuousEnergyNeutronXsdirEntry.cpp
//---------------------------------------------------------------------------//
