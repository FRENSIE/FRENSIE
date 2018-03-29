//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomFactory.hpp
//! \author Luke Kersting
//! \brief  The positron-atom factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONATOM_FACTORY_HPP
#define MONTE_CARLO_POSITRONATOM_FACTORY_HPP

// Std Lib Includes
#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_Positronatom.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_SimulationProperties.hpp"

namespace MonteCarlo{

//! The positron-atom factory class
class PositronatomFactory
{

public:

  //! Constructor
  PositronatomFactory(
    const std::string& cross_sections_xml_directory,
    const Teuchos::ParameterList& cross_section_table_info,
    const std::unordered_set<std::string>& positronatom_aliases,
    const std::shared_ptr<AtomicRelaxationModelFactory>&
    atomic_relaxation_model_factory,
    const SimulationProperties& properties,
    std::ostream* os_message = &std::cout );

  //! Destructor
  ~PositronatomFactory()
  { /* ... */ }

  //! Create the map of positron-atoms
  void createPositronatomMap(
            std::unordered_map<std::string,std::shared_ptr<Positronatom> >&
            positronatom_map ) const;

private:

  // Create a positron-atom from an ACE table
  void createPositronatomFromACETable(
              const std::string& positronatom_alias,
              const std::string& ace_file_path,
              const std::string& positronatomic_table_name,
              const int positronatomic_file_start_line,
              const double atomic_weight,
              const std::shared_ptr<AtomicRelaxationModelFactory>&
                          atomic_relaxation_model_factory,
              const SimulationProperties& properties );

  // Create a positron-atom from a Native table
  void createPositronatomFromNativeTable(
              const std::string& positronatom_alias,
              const std::string& ace_file_path,
              const double atomic_weight,
              const std::shared_ptr<AtomicRelaxationModelFactory>&
                          atomic_relaxation_model_factory,
              const SimulationProperties& properties );

  // The positron-atom map
  std::unordered_map<std::string,std::shared_ptr<Positronatom> >
  d_positronatom_name_map;

  // The table map
  std::unordered_map<std::string,std::shared_ptr<Positronatom> >
  d_positronatomic_table_name_map;

  // The message output stream
  std::ostream* d_os_message;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRONATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomFactory.hpp
//---------------------------------------------------------------------------//
