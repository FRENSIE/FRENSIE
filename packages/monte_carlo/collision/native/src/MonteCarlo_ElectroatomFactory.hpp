//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatom factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_FACTORY_HPP
#define MONTE_CARLO_ELECTROATOM_FACTORY_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

namespace MonteCarlo{

//! The electroatom factory class
class ElectroatomFactory
{
  
public:

  //! Constructor
  ElectroatomFactory( 
		const std::string& cross_sections_xml_directory,
		const Teuchos::ParameterList& cross_section_table_info,
		const boost::unordered_set<std::string>& electroatom_aliases,
		const Teuchos::RCP<AtomicRelaxationModelFactory>& 
            atomic_relaxation_model_factory,
		const unsigned hash_grid_bins,
		const BremsstrahlungAngularDistributionType 
		    photon_distribution_function,
		const bool use_atomic_relaxation_data,
		const double cutoff_angle_cosine = 0.999999,
		std::ostream* os_message = &std::cout );

  //! Destructor
  ~ElectroatomFactory()
  { /* ... */ }

  //! Create the map of electroatoms
  void createElectroatomMap(
		    boost::unordered_map<std::string,Teuchos::RCP<Electroatom> >&
		    electroatom_map ) const;

private:

  // Create a electroatom from an ACE table
  void createElectroatomFromACETable(
			  const std::string& electroatom_alias,
			  const std::string& ace_file_path,
			  const std::string& electroatomic_table_name,
			  const int electroatomic_file_start_line,
			  const double atomic_weight,
			  const Teuchos::RCP<AtomicRelaxationModelFactory>& 
			    atomic_relaxation_model_factory,
			  const unsigned hash_grid_bins,
              const BremsstrahlungAngularDistributionType 
                photon_distribution_function,
              const bool use_atomic_relaxation_data,
              const double cutoff_angle_cosine = 0.999999 );

  // Create a electroatom from a Native table
  void createElectroatomFromNativeTable(
			  const std::string& electroatom_alias,
			  const std::string& ace_file_path,
			  const double atomic_weight,
			  const Teuchos::RCP<AtomicRelaxationModelFactory>&
			    atomic_relaxation_model_factory,
			  const unsigned hash_grid_bins, 
              const BremsstrahlungAngularDistributionType 
                photon_distribution_function,
              const bool use_atomic_relaxation_data,
              const double cutoff_angle_cosine = 0.999999 );

  // The electroatom map
  boost::unordered_map<std::string,Teuchos::RCP<Electroatom> > 
  d_electroatom_name_map;
  
  // The table map
  boost::unordered_map<std::string,Teuchos::RCP<Electroatom> >
  d_electroatomic_table_name_map;
  
  // The message output stream
  std::ostream* d_os_message;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomFactory.hpp
//---------------------------------------------------------------------------//
