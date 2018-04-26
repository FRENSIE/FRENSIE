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
#include "MonteCarlo_AdjointElectronMaterial.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

//! The adjoint electroatom factory class
class AdjointElectroatomFactory
{

public:

  //! The adjoint electroatom name map
  typedef AdjointElectronMaterial::AdjointElectroatomNameMap AdjointElectroatomNameMap;

  //! The scattering center name set
  typedef MaterialDefinitionDatabase::ScatteringCenterNameSet ScatteringCenterNameSet;

  //! Constructor
  AdjointElectroatomFactory(
     const boost::filesystem::path& data_directory,
     const ScatteringCenterNameSet& adjoint_electroatom_names,
     const ScatteringCenterDefinitionDatabase& adjoint_electroatom_definitions,
     const SimulationProperties& properties,
     const bool verbose = false );

  //! Destructor
  ~AdjointElectroatomFactory()
  { /* ... */ }

  //! Create the map of adjoint electroatoms
  void createAdjointElectroatomMap(
               AdjointElectroatomNameMap& adjoint_electroatom_name_map ) const;

private:

  // Create a adjoint electroatom from a Native table
  void createAdjointElectroatomFromNativeTable(
               const boost::filesystem::path& data_directory,
               const std::string& adjoint_electroatom_name,
               const double atomic_weight,
               const Data::AdjointElectroatomicDataProperties& data_properties,
               const SimulationProperties& properties );
  
  // The adjoint electroatom map
  AdjointElectroatomNameMap d_adjoint_electroatom_name_map;

  // The table map
  std::map<Data::AdjointElectroatomicDataProperties::FileType,AdjointElectroatomNameMap>
  d_adjoint_electroatomic_table_name_map;

  // Verbose adjoint electroatom construction
  bool d_verbose;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomFactory.hpp
//---------------------------------------------------------------------------//
