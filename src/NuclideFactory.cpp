//---------------------------------------------------------------------------//
//!
//! \file   NuclideFactory.cpp
//! \author Alex Robinson
//! \brief  The nuclide factory class definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include "NuclideFactory.hpp"
#include "Teuchos_XMLParameterListCoreHelpers.hpp"

namespace FACEMC{

// Constructor
NuclideFactory::NuclideFactory( 
			    const std::string& ace_table_directory,
			    const boost::unordered_set<std::string>& nuclides )
  : d_ace_table_directory( ace_table_directory ),
    d_nuclides( nuclides )
{ 
  // Assign the name of the cross_sections.xml file with path
  std::string cross_section_xml_file = ace_table_directory;
  cross_section_xml_file += "/cross_sections.xml";

  // Read in the xml file storing the cross section table information 
  Teuchos::updateParametersFromXmlFile( 
			       cross_section_xml_file,
			       Teuchos::inoutArg(d_cross_section_table_info) );
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end NuclideFactory.cpp
//---------------------------------------------------------------------------//
