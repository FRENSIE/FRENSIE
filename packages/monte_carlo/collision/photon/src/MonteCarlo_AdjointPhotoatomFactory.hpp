//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomFactory.hpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTOATOM_FACTORY_HPP
#define MONTE_CARLO_ADJOINT_PHOTOATOM_FACTORY_HPP

// Std Lib Includes
#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatom.hpp"
#include "MonteCarlo_AdjointPhotonMaterial.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

//! The adjoint photoatom factory class
class AdjointPhotoatomFactory
{

public:

  //! The photoatom name map
  typedef AdjointPhotonMaterial::AdjointPhotoatomNameMap AdjointPhotoatomNameMap;

  //! The scattering center name set
  typedef MaterialDefinitionDatabase::ScatteringCenterNameSet ScatteringCenterNameSet;

  //! Constructor
  AdjointPhotoatomFactory(
       const boost::filesystem::path& data_directory,
       const ScatteringCenterNameSet& adjoint_photoatom_names,
       const ScatteringCenterDefinitionDatabase& adjoint_photoatom_definitions,
       const SimulationAdjointPhotonProperties& properties,
       const bool verbose = false );

  //! Destructor
  ~AdjointPhotoatomFactory()
  { /* ... */ }

  //! Create the map of adjoint photoatoms
  void createAdjointPhotoatomMap(
                        AdjointPhotoatomNameMap& adjoint_photoatom_map ) const;

private:

  // Create an adjoint photoatom from a Native table
  void createAdjointPhotoatomFromNativeTable(
                 const boost::filesystem::path& data_directory,
                 const std::string& adjoint_photoatom_name,
                 const double atomic_weight,
                 const Data::AdjointPhotoatomicDataProperties& data_properties,
                 const SimulationAdjointPhotonProperties& properties );

  // The adjoint photoatom map
  AdjointPhotoatomNameMap d_adjoint_photoatom_name_map;

  // The table map
  std::map<Data::AdjointPhotoatomicDataProperties::FileType,AdjointPhotoatomNameMap>
  d_adjoint_photoatomic_table_name_map;

  // Verbose adjoint photoatom construction
  bool d_verbose;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTOATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomFactory.hpp
//---------------------------------------------------------------------------//
