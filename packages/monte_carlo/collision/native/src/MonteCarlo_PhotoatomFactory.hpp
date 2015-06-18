//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomFactory.hpp
//! \author Alex Robinson
//! \brief  The photoatom factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOM_FACTORY_HPP
#define MONTE_CARLO_PHOTOATOM_FACTORY_HPP

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
#include "MonteCarlo_Photoatom.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_IncoherentModelType.hpp"

namespace MonteCarlo{

//! The photoatom factory class
class PhotoatomFactory
{
  
public:

  //! Constructor
  PhotoatomFactory( const std::string& cross_sections_xml_directory,
                    const Teuchos::ParameterList& cross_section_table_info,
                    const boost::unordered_set<std::string>& photoatom_aliases,
		    const Teuchos::RCP<AtomicRelaxationModelFactory>& 
		    atomic_relaxation_model_factory,
		    const unsigned hash_grid_bins,
		    const IncoherentModelType incoherent_model,
		    const double kahn_sampling_cutoff_energy,
		    const bool use_detailed_pair_production_data,
		    const bool use_atomic_relaxation_data );

  //! Destructor
  ~PhotoatomFactory()
  { /* ... */ }

  //! Create the map of photoatoms
  void createPhotoatomMap(
		    boost::unordered_map<std::string,Teuchos::RCP<Photoatom> >&
		    photoatom_map ) const;

private:

  // Create a photoatom from an ACE table
  void createPhotoatomFromACETable(
			  const std::string& cross_sections_xml_directory,
			  const std::string& photoatom_alias,
			  const std::string& ace_file_path,
			  const std::string& photoatomic_table_name,
			  const int photoatomic_file_start_line,
			  const double atomic_weight,
			  const Teuchos::RCP<AtomicRelaxationModelFactory>& 
			  atomic_relaxation_model_factory,
			  const unsigned hash_grid_bins,
			  const IncoherentModelType incoherent_model,
			  const double kahn_sampling_cutoff_energy,
			  const bool use_detailed_pair_production_data,
			  const bool use_atomic_relaxation_data );

  // Create a photoatom from a Native table
  void createPhotoatomFromNativeTable(
			  const std::string& cross_sections_xml_directory,
			  const std::string& photoatom_alias,
			  const std::string& native_file_path,
			  const double atomic_weight,
			  const Teuchos::RCP<AtomicRelaxationModelFactory>&
			  atomic_relaxation_model_factory,
			  const unsigned hash_grid_bins,
			  const IncoherentModelType incoherent_model,
			  const double kahn_sampling_cutoff_energy,
			  const bool use_detailed_pair_production_data,
			  const bool use_atomic_relaxation_data );

  // The photoatom map
  boost::unordered_map<std::string,Teuchos::RCP<Photoatom> > 
  d_photoatom_name_map;
  
  // The table map
  boost::unordered_map<std::string,Teuchos::RCP<Photoatom> >
  d_photoatomic_table_name_map;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomFactory.hpp
//---------------------------------------------------------------------------//
