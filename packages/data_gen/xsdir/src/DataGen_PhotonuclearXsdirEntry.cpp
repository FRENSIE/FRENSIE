//---------------------------------------------------------------------------//
//!
//! \file   DataGen_PhotonuclearXsdirEntry.cpp
//! \author Alex Robinson
//! \brief  The photonuclear xsdir entry class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_PhotonuclearXsdirEntry.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"

namespace DataGen{

// Return the table alias
const std::string& PhotonuclearXsdirEntry::getTableAlias() const
{
  return d_alias;
}

// Add information to parameter list
void PhotonuclearXsdirEntry::addInfoToParameterList( 
				 Teuchos::ParameterList& parameter_list ) const
{
  parameter_list.set( 
	   MonteCarlo::CrossSectionsXMLProperties::photonuclear_file_path_prop,
	   this->getTableFilePath() );
  
  parameter_list.set( 
	   MonteCarlo::CrossSectionsXMLProperties::photonuclear_file_type_prop,
	   MonteCarlo::CrossSectionsXMLProperties::ace_file );
  
  parameter_list.set( 
	  MonteCarlo::CrossSectionsXMLProperties::photonuclear_table_name_prop,
	  this->getTableName() );
  
  parameter_list.set<int>( 
     MonteCarlo::CrossSectionsXMLProperties::photonuclear_file_start_line_prop,
     this->getTableFileStartLine() );
  
  if( !parameter_list.isParameter(
		 MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop ) )
  {
    parameter_list.set<int>( 
		    MonteCarlo::CrossSectionsXMLProperties::atomic_number_prop,
		    d_atomic_number );
  }
  
  if( !parameter_list.isParameter(
	    MonteCarlo::CrossSectionsXMLProperties::atomic_mass_number_prop ) )
  {
    parameter_list.set<int>( 
	       MonteCarlo::CrossSectionsXMLProperties::atomic_mass_number_prop,
	       d_atomic_mass_number );			   
  }
  
  if( !parameter_list.isParameter(
		 MonteCarlo::CrossSectionsXMLProperties::isomer_number_prop ) )
  {
    parameter_list.set<int>( 
		    MonteCarlo::CrossSectionsXMLProperties::isomer_number_prop,
		    d_isomer_number );
  }

  if( !parameter_list.isParameter(
	   MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop ) )
  {
    parameter_list.set( 
	      MonteCarlo::CrossSectionsXMLProperties::atomic_weight_ratio_prop,
	      this->getTableAtomicWeightRatio() );
  }
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_PhotonuclearXsdirEntry.cpp
//---------------------------------------------------------------------------//
