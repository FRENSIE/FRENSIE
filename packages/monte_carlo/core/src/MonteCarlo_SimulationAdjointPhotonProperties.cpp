//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointPhotonProperties.hpp
//! \author Alex Robinson
//! \brief  Simulation adjoint photon properties class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// The absolute mimimum adjoint photon energy (MeV)
const double SimulationAdjointPhotonProperties::s_absolute_min_adjoint_photon_energy = 1e-3;

// The absolute maximum adjoint photon energy (MeV)
const double SimulationAdjointPhotonProperties::s_absolute_max_adjoint_photon_energy = 20.0;

// Constructor
SimulationAdjointPhotonProperties::SimulationAdjointPhotonProperties()
  : d_min_adjoint_photon_energy( s_absolute_min_adjoint_photon_energy ),
    d_max_adjoint_photon_energy( s_absolute_max_adjoint_photon_energy ),
    d_num_adjoint_photon_hash_grid_bins( 500 ),
    d_incoherent_adjoint_model_type( DB_IMPULSE_INCOHERENT_ADJOINT_MODEL ),
    d_critical_line_energies()
{ /* ... */ }

// Set the minimum adjoint photon energy (MeV)
void SimulationAdjointPhotonProperties::setMinAdjointPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy >= s_absolute_min_adjoint_photon_energy );
  testPrecondition( energy < d_max_adjoint_photon_energy );

  d_min_adjoint_photon_energy = energy;
}

// Return the minimum adjoint photon energy (MeV)
double SimulationAdjointPhotonProperties::getMinAdjointPhotonEnergy() const
{
  return d_min_adjoint_photon_energy;
}

// Return the absolute minimum adjoint photon energy (MeV)
double SimulationAdjointPhotonProperties::getAbsoluteMinAdjointPhotonEnergy()
{
  return s_absolute_min_adjoint_photon_energy;
}

// Set the maximum adjoint photon energy (MeV)
void SimulationAdjointPhotonProperties::setMaxAdjointPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy > d_min_adjoint_photon_energy );
  testPrecondition( energy <= s_absolute_max_adjoint_photon_energy );

  d_max_adjoint_photon_energy = energy;
}

// Return the maximum adjoint photon energy (MeV)
double SimulationAdjointPhotonProperties::getMaxAdjointPhotonEnergy() const
{
  return d_max_adjoint_photon_energy;
}

// Return the absolute maximum adjoint photon energy (MeV)
double SimulationAdjointPhotonProperties::getAbsoluteMaxAdjointPhotonEnergy()
{
  return s_absolute_max_adjoint_photon_energy;
}

// Set the number of adjoint photon hash grid bins
void SimulationAdjointPhotonProperties::setNumberOfAdjointPhotonHashGridBins(
                                                          const unsigned bins )
{
  // Make sure the number of bins is valid
  testPrecondition( bins >= 1 );

  d_num_adjoint_photon_hash_grid_bins = bins;
}

// Get the number of adjoint photon hash grid bins
unsigned SimulationAdjointPhotonProperties::getNumberOfAdjointPhotonHashGridBins() const
{
  return d_num_adjoint_photon_hash_grid_bins;
}

// Set the incoherent adjoint model type
void SimulationAdjointPhotonProperties::setIncoherentAdjointModelType(
                                       const IncoherentAdjointModelType model )
{
  d_incoherent_adjoint_model_type = model;
}

// Return the incoherent adjoint model type
IncoherentAdjointModelType SimulationAdjointPhotonProperties::getIncoherentAdjointModelType() const
{
  return d_incoherent_adjoint_model_type;
}

// Set the critical line energies
/*! \details Do not change with min/max adjoint photon energy after setting
 * the critical line energies as the line energies may become invalid!
 */
void SimulationAdjointPhotonProperties::setCriticalAdjointPhotonLineEnergies(
                         const std::vector<double>& critical_line_energies )
{
  // Make sure there is at least one energy
  testPrecondition( critical_line_energies.size() > 0 );
  // Make sure the critical line energies are sorted
  testPrecondition( Utility::Sort::isSortedAscending(
                                              critical_line_energies.begin(),
                                              critical_line_energies.end() ) );
  // Make sure the critical line energies are valid
  testPrecondition( critical_line_energies.back() <=
                    d_max_adjoint_photon_energy );
  testPrecondition( critical_line_energies.front() >=
                    d_min_adjoint_photon_energy );

  d_critical_line_energies = critical_line_energies;
}

// Get the critical line energies
const std::vector<double>&
SimulationAdjointPhotonProperties::getCriticalAdjointPhotonLineEnergies() const
{
  return d_critical_line_energies;
}

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( SimulationAdjointPhotonProperties );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SimulationAdjointPhotonProperties );

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointPhotonProperties.cpp
//---------------------------------------------------------------------------//
