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

// Boost Includes
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "MonteCarlo_Photoatom.hpp"
#include "MonteCarlo_PhotonMaterial.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

//! The photoatom factory class
class PhotoatomFactory
{

public:

  //! The photoatom name map
  typedef PhotonMaterial::PhotoatomNameMap PhotoatomNameMap;

  //! The scattering center name set
  typedef MaterialDefinitionDatabase::ScatteringCenterNameSet ScatteringCenterNameSet;

  //! Constructor
  PhotoatomFactory(
       const boost::filesystem::path& data_directory,
       const ScatteringCenterNameSet& photoatom_names,
       const ScatteringCenterDefinitionDatabase& photoatom_definitions,
       const std::shared_ptr<AtomicRelaxationModelFactory>&
       atomic_relaxation_model_factory,
       const SimulationProperties& properties,
       const bool verbose = false );

  //! Destructor
  ~PhotoatomFactory()
  { /* ... */ }

  //! Create the map of photoatoms
  void createPhotoatomMap( PhotoatomNameMap& photoatom_name_map ) const;

private:

  // Create a photoatom from an ACE table
  void createPhotoatomFromACETable(
                        const boost::filesystem::path& data_directory,
                        const std::string& photoatom_name,
                        const double atomic_weight,
			const Data::PhotoatomicDataProperties& data_properties,
                        const std::shared_ptr<AtomicRelaxationModelFactory>&
                        atomic_relaxation_model_factory,
                        const SimulationProperties& properties );

  // Create a photoatom from a Native table
  void createPhotoatomFromNativeTable(
			const boost::filesystem::path& data_directory,
                        const std::string& photoatom_name,
                        const double atomic_weight,
                        const Data::PhotoatomicDataProperties& data_properties,
                        const std::shared_ptr<AtomicRelaxationModelFactory>&
                        atomic_relaxation_model_factory,
                        const SimulationProperties& properties );

  // The photoatom map
  PhotoatomNameMap d_photoatom_name_map;

  // The table map (used to prevent multiple reads of the same data file)
  std::map<Data::PhotoatomicDataProperties::FileType,PhotoatomNameMap>
  d_photoatomic_table_name_map;

  // Verbose photoatom construction
  bool d_verbose;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomFactory.hpp
//---------------------------------------------------------------------------//
