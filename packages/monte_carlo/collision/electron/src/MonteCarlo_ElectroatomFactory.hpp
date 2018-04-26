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

// Boost Includes
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_ElectronMaterial.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

//! The electroatom factory class
class ElectroatomFactory
{

public:

  //! The electroatom name map
  typedef ElectronMaterial::ElectroatomNameMap ElectroatomNameMap;

  //! The scattering center name set
  typedef MaterialDefinitionDatabase::ScatteringCenterNameSet ScatteringCenterNameSet;

  //! Constructor
  ElectroatomFactory(
             const boost::filesystem::path& data_directory,
             const ScatteringCenterNameSet& electroatom_names,
             const ScatteringCenterDefinitionDatabase& electroatom_definitions,
             const std::shared_ptr<AtomicRelaxationModelFactory>&
             atomic_relaxation_model_factory,
             const SimulationProperties& properties,
             const bool verbose = false );

  //! Destructor
  ~ElectroatomFactory()
  { /* ... */ }

  //! Create the map of electroatoms
  void createElectroatomMap( ElectroatomNameMap& electroatom_name_map ) const;

private:

  // Create a electroatom from an ACE table
  void createElectroatomFromACETable(
                      const boost::filesystem::path& data_directory,
                      const std::string& electroatom_name,
                      const double atomic_weight,
		      const Data::ElectroatomicDataProperties& data_properties,
                      const std::shared_ptr<AtomicRelaxationModelFactory>&
                      atomic_relaxation_model_factory,
                      const SimulationProperties& properties );

  // Create a electroatom from a Native table
  void createElectroatomFromNativeTable(
                      const boost::filesystem::path& data_directory,
                      const std::string& electroatom_name,
                      const double atomic_weight,
                      const Data::ElectroatomicDataProperties& data_properties,
                      const std::shared_ptr<AtomicRelaxationModelFactory>&
                      atomic_relaxation_model_factory,
                      const SimulationProperties& properties );

  // The electroatom map
  ElectroatomNameMap d_electroatom_name_map;

  // The table map
  std::map<Data::ElectroatomicDataProperties::FileType,ElectroatomNameMap>
  d_electroatomic_table_name_map;

  // Verbose electroatom construction
  bool d_verbose;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomFactory.hpp
//---------------------------------------------------------------------------//
