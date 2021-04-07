//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclideFactory.hpp
//! \author Alex Robinson
//! \brief  The nuclide factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLIDE_FACTORY_HPP
#define MONTE_CARLO_NUCLIDE_FACTORY_HPP

// Std Lib Includes
#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_Nuclide.hpp"
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

//! The nuclide factory class
class NuclideFactory
{

public:

  //! The nuclide name map
  typedef NeutronMaterial::NuclideNameMap NuclideNameMap;

  //! The scattering center name set
  typedef MaterialDefinitionDatabase::ScatteringCenterNameSet ScatteringCenterNameSet;

  //! Constructor
  NuclideFactory( const boost::filesystem::path& data_directory,
                  const ScatteringCenterNameSet& nuclide_names,
                  const ScatteringCenterDefinitionDatabase& nuclide_definitions,
                  const SimulationProperties& properties,
                  const bool verbose = false );

  //! Destructor
  ~NuclideFactory()
  { /* ... */ }

  //! Create the map of nuclides
  void createNuclideMap( NuclideNameMap& nuclide_map ) const;

private:

  // Create a nuclide from an ACE table
  void createNuclideFromACETable(
                            const boost::filesystem::path& data_directory,
                            const std::string& nuclide_name,
                            const double atomic_weight_ratio,
                            const Data::NuclearDataProperties& data_properties,
                            const SimulationProperties& properties );

  // The nuclide  map
  NuclideNameMap d_nuclide_name_map;

  // The table map (used to prevent multiple reads of the same data file
  std::map<Data::NuclearDataProperties::FileType,NuclideNameMap>
  d_nuclear_table_name_map;

  // Verbose nuclide construction
  bool d_verbose;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLIDE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclideFactory.hpp
//---------------------------------------------------------------------------//
