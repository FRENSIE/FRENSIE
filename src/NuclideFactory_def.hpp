//---------------------------------------------------------------------------//
//!
//! \file   NuclideFactory_def.hpp
//! \author Alex Robinson
//! \brief  The nuclide factory class template definitions
//! 
//---------------------------------------------------------------------------//

#ifndef NUCLIDE_FACTORY_DEF_HPP
#define NUCLIDE_FACTORY_DEF_HPP

// FACEMC Includes
#include "NuclideFactory.hpp"
#include "NuclearReactionFactory.hpp"
#include "ACEFileHandler.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Create the map of nuclides
/*! \details Any map concept model that can be passed as an argument to this
 * function. The key value must be a standard string and the mapped value must
 * be a Teuchos::RCP<Nuclide>.
 */
template<typename NuclideNameMap>
void NuclideFactory::create( NuclideNameMap& nuclide_map ) const
{ 
  // Make sure the key and map values are correct
  testStaticPrecondition((boost::is_same<typename NuclideNameMap::key_type,std::string>::value));
  testStaticPrecondition((boost::is_same<typename NuclideNameMap::mapped_type,Teuchos::RCP<Nuclide> >::value));
  
  // Reset the nuclide map
  nuclide_map.clear();

  // The ACE table reader
  Teuchos::RCP<ACEFileHandler> ace_file_handler;

  // The path to the ace file
  std::string ace_file_path;

  // The XSS neutron data extractor
  Teuchos::RCP<XSSNeutronDataExtractor> xss_data_extractor;

  // The nuclide that will be created
  Teuchos::RCP<Nuclide> nuclide;

  // Create each nuclide in the set
  boost::unordered_set<std::string>::const_iterator nuclide_name,
    end_nuclide_name;
  nuclide_name = d_nuclides.begin();
  end_nuclide_name = d_nuclides.end();

  while( nuclide_name != end_nuclide_name )
  {
    const Teuchos::ParameterList& table_info =
      d_cross_section_table_info.sublist( *nuclide_name );

    std::cout << "Loading ACE cross section table: " 
	      << table_info.get<std::string>( "table_name" )
	      << " (" << *nuclide_name << ")." << std::endl;

    // Set the abs. path to the ace library file containing the desired table
    ace_file_path = d_ace_table_directory + "/" + 
      table_info.get<std::string>( "file_path" );
    
    // Create a file handler for the desired library file
    ace_file_handler.reset( new ACEFileHandler( 
			ace_file_path,
			table_info.get<std::string>( "table_name" ),
			table_info.get<unsigned>( "start_line" ),
			d_cross_section_table_info.get<bool>( "is_ascii" ) ) );

    // Create the XSS data extractor
    xss_data_extractor.reset( 
	 new XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
    
    // Create a standard nuclide
    if( !xss_data_extractor->hasFissionData() &&
	!xss_data_extractor->hasUnresolvedResonanceData() )
    {
      nuclide.reset( new Nuclide( 
		              *nuclide_name,
			      table_info.get<unsigned>( "atomic_number" ),
		              table_info.get<unsigned>( "atomic_mass_number" ),
			      table_info.get<unsigned>( "isomer_number" ),
			      table_info.get<double>( "atomic_weight_ratio" ),
			      table_info.get<double>( "temperature" ),
			      *xss_data_extractor ) );
    }
    // Create a fissionable nuclide
    else if( xss_data_extractor->hasFissionData() &&
	     !xss_data_extractor->hasUnresolvedResonanceData() )
    {
      throw std::runtime_error( "Fissionable nuclei are not currently supported. " );
    }
    // Create a nuclide with unresolved resonances
    else if( !xss_data_extractor->hasFissionData() &&
	     xss_data_extractor->hasUnresolvedResonanceData() )
    {
      throw std::runtime_error( "Nuclei with unresolved resonance data are not currently supported." );
    }
    // Create a complex nuclide
    else
    {
      throw std::runtime_error( "Fissionable nuclei with unresolved resonance data are not currently supported." );
    }				     

    // Add the nuclide to the map
    nuclide_map[*nuclide_name] = nuclide;

    ++nuclide_name;
  }
}

} // end FACEMC namespace

#endif // end NUCLIDE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// NuclideFactory_def.hpp
//---------------------------------------------------------------------------//
