//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ENDLElectronPhotonRelaxationDataGenerator_def.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The ENDL electron-photon-relaxation data generator template
//!         definitions
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ENDL_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_DEF_HPP
#define DATA_GEN_ENDL_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_DEF_HPP

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"

namespace DataGen{

// Extract the average photon heating numbers
template<typename InterpPolicy>
void ENDLElectronPhotonRelaxationDataGenerator::extractPhotonCrossSection(
           Utility::ArrayView<const double> raw_energy_grid,
           Utility::ArrayView<const double> raw_cross_section,
           std::shared_ptr<const Utility::UnivariateDistribution>& cross_section,
           const bool processed_raw_data ) const
{
  // Find the first non-zero cross section value
  Utility::ArrayView<const double>::iterator start =
    std::find_if( raw_cross_section.begin(),
                  raw_cross_section.end(),
                  notEqualZero );

  std::vector<double> processed_cross_section;
  processed_cross_section.assign( start, raw_cross_section.end() );

  unsigned start_energy_index =
    raw_energy_grid.size() - processed_cross_section.size();

  start = raw_energy_grid.begin();
  std::advance( start, start_energy_index );

  std::vector<double> energy_grid;
  energy_grid.assign( start, raw_energy_grid.end() );

  // Recover the original energy grid and cross_section
  if( processed_raw_data )
  {
    for( unsigned i = 0; i < energy_grid.size(); ++i )
    {
      energy_grid[i] =
        InterpPolicy::recoverProcessedIndepVar( energy_grid[i] );

      processed_cross_section[i] =
        InterpPolicy::recoverProcessedDepVar( processed_cross_section[i] );
    }
  }

  cross_section.reset( new Utility::TabularDistribution<InterpPolicy>(
                                                   energy_grid,
                                                   processed_cross_section ) );
}

// Extract electron cross section
template<typename InterpPolicy>
void ENDLElectronPhotonRelaxationDataGenerator::extractElectronCrossSection(
        const std::vector<double>& raw_energy_grid,
        const std::vector<double>& raw_cross_section,
        std::shared_ptr<const Utility::UnivariateDistribution>& cross_section ) const
{
  // Find the first non-zero cross section value
  std::vector<double>::const_iterator start =
    std::find_if( raw_cross_section.begin(),
                  raw_cross_section.end(),
                  notEqualZero );

  std::vector<double> processed_cross_section( start, raw_cross_section.end() );

  unsigned start_energy_index =
    raw_energy_grid.size() - processed_cross_section.size();

  start = raw_energy_grid.begin();
  std::advance( start, start_energy_index );

  std::vector<double> energy_grid( start, raw_energy_grid.end() );

  cross_section.reset( new Utility::TabularDistribution<InterpPolicy>(
                                                   energy_grid,
                                                   processed_cross_section ) );
}

} // end DataGen namespace

#endif // end DATA_GEN_ENDL_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_ENDLElectronPhotonRelaxationDataGenerator_def.hpp
//---------------------------------------------------------------------------//
