//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclideFactory.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  The nuclide factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLIDE_FACTORY_HPP
#define MONTE_CARLO_NUCLIDE_FACTORY_HPP

// Std Lib Includes
#include <string>
#include <unordered_set>
#include <unordered_map>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Nuclide.hpp"

namespace MonteCarlo{

//! The nuclide factory class
class NuclideFactory
{
public:

  //! Constructor
  NuclideFactory( const std::string& cross_sections_xml_directory,
		  const Teuchos::ParameterList& cross_section_table_info,
		  const std::unordered_set<std::string>& nuclide_aliases,
		  const bool use_unresolved_resonance_data,
		  const bool use_photon_production_data,
		  std::ostream* os_message = &std::cout );
		  
	//! S(alpha,beta) Constructor
	NuclideFactory( const std::string& cross_sections_xml_directory,
		  const Teuchos::ParameterList& cross_section_table_info,
		  const std::unordered_set<std::string>& nuclide_aliases,
		  const bool use_unresolved_resonance_data,
		  const bool use_photon_production_data,
		  const bool use_sab_data,
		  std::unordered_map<std::string,std::string>& sab_file_paths,
		  std::unordered_map<std::string,std::string>& sab_table_names,
		  std::ostream* os_message = &std::cout );

  //! Destructor
  ~NuclideFactory()
  { /* ... */ }

  //! Create the map of nuclides
  void createNuclideMap( 
                      std::unordered_map<std::string,Teuchos::RCP<Nuclide> >&
		                  nuclide_map ) const;

private:

  // Create a nuclide from an ACE table
  void createNuclideFromACETable(
			      const std::string& cross_sections_xml_directory,
			      const std::string& nuclide_alias,
			      const std::string& ace_file_path,
			      const std::string& nuclear_table_name,
			      const int nuclide_file_start_line,
			      const int atomic_number,
			      const int atomic_mass_number,
			      const int isomer_number,
			      const double atomic_weight_ratio,
			      const double temperature,
			      const bool use_unresolved_resonance_data,
			      const bool use_photon_production_data );
			      
	// Create a nuclide from an ACE table with S(alpha,beta)
  void createNuclideFromACETable(
			      const std::string& cross_sections_xml_directory,
			      const std::string& nuclide_alias,
			      const std::string& ace_file_path,
			      const std::string& nuclear_table_name,
			      const int nuclide_file_start_line,
			      const int atomic_number,
			      const int atomic_mass_number,
			      const int isomer_number,
			      const double atomic_weight_ratio,
			      const double temperature,
			      const bool use_unresolved_resonance_data,
			      const bool use_photon_production_data,
			      const std::string& sab_file_path,
			      const std::string& sab_table_name );	

  // The nuclide id map
  std::unordered_map<std::string,Teuchos::RCP<Nuclide> > d_nuclide_name_map;

  // The message output stream
  std::ostream* d_os_message;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLIDE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclideFactory.hpp
//---------------------------------------------------------------------------//
