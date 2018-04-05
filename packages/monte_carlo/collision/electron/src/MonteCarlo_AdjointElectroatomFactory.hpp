//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomFactory.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOM_FACTORY_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOM_FACTORY_HPP

// Std Lib Includes
#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatom.hpp"
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The adjoint electroatom factory class
class AdjointElectroatomFactory
{

public:

  //! Constructor
  AdjointElectroatomFactory(
    const std::string& cross_sections_xml_directory,
    const Teuchos::ParameterList& cross_section_table_info,
    const std::unordered_set<std::string>& adjoint_electroatom_aliases,
    const SimulationAdjointElectronProperties& properties,
    std::ostream* os_message = &std::cout );

  //! Destructor
  ~AdjointElectroatomFactory()
  { /* ... */ }

  //! Create the map of adjoint electroatoms
  void createAdjointElectroatomMap(
            std::unordered_map<std::string,std::shared_ptr<const AdjointElectroatom> >&
            adjoint_electroatom_map ) const;

private:

  // Create a adjoint electroatom from a Native table
  void createAdjointElectroatomFromNativeTable(
                    const std::string& cross_sections_xml_directory,
                    const std::string& adjoint_electroatom_alias,
                    const std::string& native_file_path,
                    const double atomic_weight,
                    const SimulationAdjointElectronProperties& properties );

  // The adjoint electroatom map
  std::unordered_map<std::string,std::shared_ptr<const AdjointElectroatom> >
  d_adjoint_electroatom_name_map;

  // The table map
  std::unordered_map<std::string,std::shared_ptr<const AdjointElectroatom> >
  d_adjoint_electroatomic_table_name_map;

  // The message output stream
  std::ostream* d_os_message;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomFactory.hpp
//---------------------------------------------------------------------------//
