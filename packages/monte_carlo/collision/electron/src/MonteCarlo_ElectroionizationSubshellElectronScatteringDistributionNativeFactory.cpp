//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The electroionization subshell scattering distribution Native factory definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Calculate full outgoing energy bins and pdf from recoil energy
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::calculateOutgoingEnergyAndPDFBins(
    const std::map<double,std::vector<double> >& recoil_energy_data,
    const std::map<double,std::vector<double> >& recoil_pdf_data,
    const std::vector<double>& energy_grid,
    const double binding_energy,
    const bool renormalize_max_knock_on_energy,
    std::map<double,std::vector<double> >& processed_energy_data,
    std::map<double,std::vector<double> >& processed_pdf_data,
    std::vector<double>& processed_energy_grid )
{
  // Make sure the energy_grid is valid
  testPrecondition( energy_grid.size() > 0 );
  // Make sure the recoil data is valid
  testPrecondition( recoil_energy_data.size() == energy_grid.size() );
  testPrecondition( recoil_pdf_data.size() == energy_grid.size() );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );

  processed_energy_grid = energy_grid;

  for( size_t n = 0; n < processed_energy_grid.size(); ++n )
  {
    // Calculate the energy bin and pdf data
    std::vector<double> energy_bins, pdfs;
    ThisType::calculateOutgoingEnergyAndPDFBins(
        recoil_energy_data.find( energy_grid[n] )->second,
        recoil_pdf_data.find( energy_grid[n] )->second,
        processed_energy_grid[n],
        binding_energy,
        renormalize_max_knock_on_energy,
        energy_bins,
        pdfs );

    // Assign data to the map with processed energy
    processed_energy_data[ processed_energy_grid[n] ] = energy_bins;
    processed_pdf_data[ processed_energy_grid[n] ] = pdfs;
  }
}

// Calculate full outgoing energy bins and pdf from recoil energy
void ElectroionizationSubshellElectronScatteringDistributionNativeFactory::calculateOutgoingEnergyAndPDFBins(
    const std::vector<double>& knock_on_energy,
    const std::vector<double>& knock_on_pdf,
    double& energy,
    const double binding_energy,
    const bool renormalize_max_knock_on_energy,
    std::vector<double>& processed_energy_bins,
    std::vector<double>& processed_pdf )
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  // Make sure the knock-on data is valid
  testPrecondition( knock_on_energy.size() == knock_on_pdf.size() );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );

  double max_knock_on_energy = knock_on_energy.back();
  if( renormalize_max_knock_on_energy )
  {
    // If the grid point is not greater than the binding energy assumes for interpolation only
    if( energy <= binding_energy )
        energy = binding_energy + 2.0*knock_on_energy.back();

    // Make sure the max knock-on energy matches the incoming energy
    else
      max_knock_on_energy = 0.5*( energy - binding_energy);
  }

  if( max_knock_on_energy + binding_energy > energy )
  {
      THROW_EXCEPTION( std::logic_error,
                        "The energy loss ("
                        << knock_on_energy.back() + binding_energy
                        << ") is greater than the available energy ("
                        << energy
                        << "). The energy bounds must be changed or the "
                        << "distribution renormalized." );
  }

  // Resize the processed data
  unsigned size = 2.0*knock_on_energy.size()-1;
  processed_energy_bins.resize( size );
  processed_pdf.resize( size );

  // Calculate the full outgoing energy bins
  for( unsigned i = 0; i < knock_on_energy.size()-1; ++i )
  {
    // Calculate the outgoing energy and pdf for the lower energy electron
    processed_energy_bins[i] = knock_on_energy[i];
    processed_pdf[i] = knock_on_pdf[i];

    // Calculate the outgoing energy and pdf for the higher energy electron
    processed_energy_bins[size-1 - i] = ( energy - binding_energy ) - knock_on_energy[i];
    processed_pdf[size-1 - i] = knock_on_pdf[i];
  }

  // insert middle bin
  processed_energy_bins[knock_on_energy.size()-1] = max_knock_on_energy;
  processed_pdf[knock_on_energy.size()-1] = knock_on_pdf.back();
}


} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
