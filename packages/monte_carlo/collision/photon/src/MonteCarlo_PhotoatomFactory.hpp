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
#include <memory>
#include <unordered_set>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_Photoatom.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_SimulationProperties.hpp"

namespace MonteCarlo{

//! The photoatom factory class
class PhotoatomFactory
{

// public:

//   //! Constructor
//   PhotoatomFactory( const std::string& cross_sections_xml_directory,
//                     const Teuchos::ParameterList& cross_section_table_info,
//                     const std::unordered_set<std::string>& photoatom_aliases,
// 		    const std::shared_ptr<AtomicRelaxationModelFactory>&
// 		    atomic_relaxation_model_factory,
// 		    const SimulationProperties& properties,
// 		    std::ostream* os_message = &std::cout );

//   //! Destructor
//   ~PhotoatomFactory()
//   { /* ... */ }

//   //! Create the map of photoatoms
//   void createPhotoatomMap(
// 		    std::unordered_map<std::string,std::shared_ptr<Photoatom> >&
// 		    photoatom_map ) const;

// private:

//   // Create a photoatom from an ACE table
//   void createPhotoatomFromACETable(
// 			  const std::string& cross_sections_xml_directory,
// 			  const std::string& photoatom_alias,
// 			  const std::string& ace_file_path,
// 			  const std::string& photoatomic_table_name,
// 			  const int photoatomic_file_start_line,
// 			  const double atomic_weight,
// 			  const std::shared_ptr<AtomicRelaxationModelFactory>&
// 			  atomic_relaxation_model_factory,
// 			  const SimulationProperties& properties );

//   // Create a photoatom from a Native table
//   void createPhotoatomFromNativeTable(
// 			  const std::string& cross_sections_xml_directory,
// 			  const std::string& photoatom_alias,
// 			  const std::string& native_file_path,
// 			  const double atomic_weight,
// 			  const std::shared_ptr<AtomicRelaxationModelFactory>&
// 			  atomic_relaxation_model_factory,
// 			  const SimulationProperties& properties );

//   // The photoatom map
//   std::unordered_map<std::string,std::shared_ptr<Photoatom> >
//   d_photoatom_name_map;

//   // The table map
//   std::unordered_map<std::string,std::shared_ptr<Photoatom> >
//   d_photoatomic_table_name_map;

//   // The message output stream
//   std::ostream* d_os_message;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomFactory.hpp
//---------------------------------------------------------------------------//
