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
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_Positronatom.hpp"
#include "MonteCarlo_PositronMaterial.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

//! The positron-atom factory class
class PositronatomFactory
{

public:

  //! The positronatom name map
  typedef PositronMaterial::PositronatomNameMap PositronatomNameMap;

  //! The scattering center name set
  typedef MaterialDefinitionDatabase::ScatteringCenterNameSet ScatteringCenterNameSet;

  //! Constructor
  PositronatomFactory(
            const boost::filesystem::path& data_directory,
            const ScatteringCenterNameSet& positronatom_names,
            const ScatteringCenterDefinitionDatabase& positronatom_definitions,
            const std::shared_ptr<AtomicRelaxationModelFactory>&
            atomic_relaxation_model_factory,
            const SimulationProperties& properties,
            const bool verbose = false );

  //! Destructor
  ~PositronatomFactory()
  { /* ... */ }

  //! Create the map of positron-atoms
  void createPositronatomMap( PositronatomNameMap& positronatom_name_map ) const;

private:

  // Create a positron-atom from an ACE table
  void createPositronatomFromACETable(
                      const boost::filesystem::path& data_directory,
                      const std::string& positronatom_name,
                      const double atomic_weight,
		      const Data::ElectroatomicDataProperties& data_properties,
                      const std::shared_ptr<AtomicRelaxationModelFactory>&
                      atomic_relaxation_model_factory,
                      const SimulationProperties& properties );

  // Create a positron-atom from a Native table
  void createPositronatomFromNativeTable(
                      const boost::filesystem::path& data_directory,
                      const std::string& positronatom_name,
                      const double atomic_weight,
                      const Data::ElectroatomicDataProperties& data_properties,
                      const std::shared_ptr<AtomicRelaxationModelFactory>&
                      atomic_relaxation_model_factory,
                      const SimulationProperties& properties );

  // The positron-atom map
  PositronatomNameMap d_positronatom_name_map;

  // The table map
  std::map<Data::ElectroatomicDataProperties::FileType,PositronatomNameMap>
  d_positronatomic_table_name_map;

  // Verbose electroatom construction
  bool d_verbose;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRONATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomFactory.hpp
//---------------------------------------------------------------------------//
