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
#include <unordered_set>
#include <unordered_map>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatom.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

namespace MonteCarlo{

//! The adjoint electroatom factory class
class AdjointElectroatomFactory
{

public:

  //! Constructor
  AdjointElectroatomFactory(
    const std::string& cross_sections_xml_directory,
    const Teuchos::ParameterList& cross_section_table_info,
    const std::unordered_set<std::string>& electroatom_aliases,
    const unsigned hash_grid_bins,
    const bool use_atomic_relaxation_data = false,
    const double cutoff_angle_cosine = 1.0,
    std::ostream* os_message = &std::cout );

  //! Destructor
  ~AdjointElectroatomFactory()
  { /* ... */ }

  //! Create the map of adjoint electroatoms
  void createAdjointElectroatomMap(
            std::unordered_map<std::string,Teuchos::RCP<AdjointElectroatom> >&
            electroatom_map ) const;

private:

  // Create a adjoint electroatom from a Native table
  void createAdjointElectroatomFromNativeTable(
              const std::string& electroatom_alias,
              const std::string& ace_file_path,
              const double atomic_weight,
              const unsigned hash_grid_bins,
              const bool use_atomic_relaxation_data,
              const double cutoff_angle_cosine = 1.0 );

  // The adjoint electroatom map
  std::unordered_map<std::string,Teuchos::RCP<AdjointElectroatom> >
  d_electroatom_name_map;

  // The table map
  std::unordered_map<std::string,Teuchos::RCP<AdjointElectroatom> >
  d_electroatomic_table_name_map;

  // The message output stream
  std::ostream* d_os_message;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomFactory.hpp
//---------------------------------------------------------------------------//
