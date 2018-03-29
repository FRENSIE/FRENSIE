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
#include <memory>
#include <unordered_set>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_SimulationProperties.hpp"

namespace MonteCarlo{

//! The electroatom factory class
class ElectroatomFactory
{

public:

  //! Constructor
  ElectroatomFactory(
    const std::string& cross_sections_xml_directory,
    const Teuchos::ParameterList& cross_section_table_info,
    const std::unordered_set<std::string>& electroatom_aliases,
    const std::shared_ptr<const AtomicRelaxationModelFactory>&
    atomic_relaxation_model_factory,
    const SimulationProperties& properties,
    std::ostream* os_message = &std::cout );

  //! Destructor
  ~ElectroatomFactory()
  { /* ... */ }

  //! Create the map of electroatoms
  void createElectroatomMap(
            std::unordered_map<std::string,std::shared_ptr<const Electroatom> >&
            electroatom_map ) const;

private:

  // Create a electroatom from an ACE table
  void createElectroatomFromACETable(
              const std::string& electroatom_alias,
              const std::string& ace_file_path,
              const std::string& electroatomic_table_name,
              const int electroatomic_file_start_line,
              const double atomic_weight,
              const std::shared_ptr<const AtomicRelaxationModelFactory>&
                          atomic_relaxation_model_factory,
              const SimulationProperties& properties );

  // Create a electroatom from a Native table
  void createElectroatomFromNativeTable(
              const std::string& electroatom_alias,
              const std::string& ace_file_path,
              const double atomic_weight,
              const std::shared_ptr<const AtomicRelaxationModelFactory>&
                          atomic_relaxation_model_factory,
              const SimulationProperties& properties );

  // The electroatom map
  std::unordered_map<std::string,std::shared_ptr<const Electroatom> >
  d_electroatom_name_map;

  // The table map
  std::unordered_map<std::string,std::shared_ptr<const Electroatom> >
  d_electroatomic_table_name_map;

  // The message output stream
  std::ostream* d_os_message;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomFactory.hpp
//---------------------------------------------------------------------------//
