//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointPhotonProperties.hpp
//! \author Alex Robinson
//! \brief  Simulation adjoint photon properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_ADJOINT_PHOTON_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_ADJOINT_PHOTON_PROPERTIES_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointModelType.hpp"
#include "MonteCarlo_AdjointKleinNishinaSamplingType.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The simulation adjoint photon properties class
class SimulationAdjointPhotonProperties
{

public:

  //! Constructor
  SimulationAdjointPhotonProperties();

  //! Destructor
  virtual ~SimulationAdjointPhotonProperties()
  { /* ... */ }

  //! Set the minimum adjoint photon energy (MeV)
  void setMinAdjointPhotonEnergy( const double energy );

  //! Return the minimum adjoint photon energy (MeV)
  double getMinAdjointPhotonEnergy() const;

  //! Return the absolute minimum adjoint photon energy (MeV)
  static double getAbsoluteMinAdjointPhotonEnergy();

  //! Set the maximum adjoint photon energy (MeV)
  void setMaxAdjointPhotonEnergy( const double energy );

  //! Return the maximum adjoint photon energy (MeV)
  double getMaxAdjointPhotonEnergy() const;

  //! Return the absolute maximum adjoint photon energy (MeV)
  static double getAbsoluteMaxAdjointPhotonEnergy();

  //! Set the number of adjoint photon hash grid bins
  void setNumberOfAdjointPhotonHashGridBins( const unsigned bins );

  //! Get the number of adjoint photon hash grid bins
  unsigned getNumberOfAdjointPhotonHashGridBins() const;

  //! Set the incoherent adjoint model type
  void setIncoherentAdjointModelType( const IncoherentAdjointModelType model );

  //! Return the incoherent adjoint model type
  IncoherentAdjointModelType getIncoherentAdjointModelType() const;

  //! Set the adjoint Klein-Nishina sampling type
  AdjointKleinNishinaSamplingType setAdjointKleinNishinaSamplingType(
                         const AdjointKleinNishinaSamplingType sampling_type );

  //! Return the adjoint Klein-Nishina sampling type
  AdjointKleinNishinaSamplingType getAdjointKleinNishinaSamplingType() const;

  //! Set the critical line energies
  void setCriticalAdjointPhotonLineEnergies(
                        const std::vector<double>& critical_line_energies );

  //! Get the critical line energies
  const std::vector<double>& getCriticalAdjointPhotonLineEnergies() const;

  //! Set the cutoff roulette threshold weight
  void setAdjointPhotonRouletteThresholdWeight( const double threshold_weight );

  //! Return the cutoff roulette threshold weight
  double getAdjointPhotonRouletteThresholdWeight() const;

  //! Set the cutoff roulette survival weight
  void setAdjointPhotonRouletteSurvivalWeight( const double survival_weight );

  //! Return the cutoff roulette survival weight
  double getAdjointPhotonRouletteSurvivalWeight() const;

private:

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The absolute mimimum adjoint photon energy (MeV)
  static const double s_absolute_min_adjoint_photon_energy;

  // The absolute maximum adjoint photon energy (MeV)
  static const double s_absolute_max_adjoint_photon_energy;

  // The minimum adjoint photon energy (MeV)
  double d_min_adjoint_photon_energy;

  // The maximum adjoint photon energy (MeV)
  double d_max_adjoint_photon_energy;

  // The number of adjoint photon hash grid bins
  unsigned d_num_adjoint_photon_hash_grid_bins;

  // The incoherent adjoint model
  IncoherentAdjointModelType d_incoherent_adjoint_model_type;

  // The adjoint klein-nishina sampling type
  AdjointKleinNishinaSamplingType d_adjoint_kn_sampling_type;

  // The critical line energies
  std::vector<double> d_critical_line_energies;

  // The roulette threshold weight
  double d_threshold_weight;

  // The roulette survival weight
  double d_survival_weight;
};

// Save the state to an archive
template<typename Archive>
void SimulationAdjointPhotonProperties::serialize( Archive& ar,
                                                   const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_min_adjoint_photon_energy );
  ar & BOOST_SERIALIZATION_NVP( d_max_adjoint_photon_energy );
  ar & BOOST_SERIALIZATION_NVP( d_num_adjoint_photon_hash_grid_bins );
  ar & BOOST_SERIALIZATION_NVP( d_incoherent_adjoint_model_type );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_kn_sampling_type );
  ar & BOOST_SERIALIZATION_NVP( d_critical_line_energies );
  ar & BOOST_SERIALIZATION_NVP( d_threshold_weight );
  ar & BOOST_SERIALIZATION_NVP( d_survival_weight );
}

} // end MonteCarlo namespace

#if !defined SWIG

BOOST_CLASS_VERSION( MonteCarlo::SimulationAdjointPhotonProperties, 0 );
BOOST_CLASS_EXPORT_KEY2( MonteCarlo::SimulationAdjointPhotonProperties, "SimulationAdjointPhotonProperties" );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SimulationAdjointPhotonProperties );

#endif // end !defined SWIG

#endif // end MONTE_CARLO_SIMULATION_ADJOINT_PHOTON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointPhotonProperties.hpp
//---------------------------------------------------------------------------//
