//---------------------------------------------------------------------------//
// \file   PhotonDataDopplerBroadening.hpp
// \author Alex Robinson
// \brief  PhotonDataDopplerBroadening class declaration
//---------------------------------------------------------------------------//

#ifndef PHOTON_DATA_DOPPLER_BROADENING_HPP
#define PHOTON_DATA_DOPPLER_BROADENING_HPP

// Std Lib Includes
#include <map>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_TwoDArray.hpp>

// FACEMC Includes
#include "Tuple.hpp"

namespace FACEMC{

class PhotonDataDopplerBroadening
{

protected:

  //! Constructor
  PhotonDataDopplerBroadening( unsigned int atomic_number,
			       double energy_min,
			       double energy_max );

  //! Destructor
  ~PhotonDataDopplerBroadening()
  { /* ... */ }

  //! Return the data corresponding to the shell with a vacancy after an 
  // incoherent scattering event
  Pair<unsigned int, unsigned int> getIncoherentScatteringVacancyShellData( 
						 const double cdf_value ) const;

  //! Return the Compton Profile cdf value for a given momentum projection value
  double getComptonProfileCDF( const unsigned int compton_profile_index,
			       const double momentum ) const;

  //! Return the Compton Profile momentum projection for a given cdf value
  double getComptonProfileMomentum( const unsigned int compton_profile_index,
				    const double cdf_value ) const;

  //! Return the binding energy of electrons in a given shell
  double getShellBindingEnergy( const unsigned int shell ) const;

  //! Return the kinetic energy of electrons in a given shell
  double getShellKineticEnergy( const unsigned int shell ) const;


private:

  //@{
  //! Typedefs
  typedef Teuchos::ArrayRCP<Trip<double, unsigned int, unsigned int> > ShellOccupancyArray;
  typedef Teuchos::TwoDArray<Quad<double,double,double,double> > ComptonProfileArray;
  typedef Teuchos::ArrayView<Quad<double,double,double,double> > ComptonProfileSubArray;
  typedef Teuchos::ArrayRCP<double> MomentumProjectionArray;
  typedef std::map<unsigned int, double> ShellMap;
  //@}

  //--------------------------------------------------------------------------//
  // Shell Occupancy Data
  //--------------------------------------------------------------------------//
  
  // Shell occupancy cdf, shell number, and compton profile index
  ShellOccupancyArray d_shell_occupancy;

  //--------------------------------------------------------------------------//
  // Compton Profile Data
  //--------------------------------------------------------------------------//

  // Compton profile cdf for each shell
  ComptonProfileArray d_compton_profiles;

  // Compton profile momentum projections
  MomentumProjectionArray d_momentum_projections;

  //--------------------------------------------------------------------------//
  // Electron Shell Data
  //--------------------------------------------------------------------------//

  // Electron shell binding energy
  ShellMap d_electron_shell_binding_energy;

  // Electron shell kinetic energy
  ShellMap d_electron_shell_kinetic_energy;

};

} // end FACEMC namespace

#endif // end PHOTON_DATA_DOPPLER_BROADENING_HPP

//---------------------------------------------------------------------------//
// end PhotonDataDopplerBroadening.hpp
//---------------------------------------------------------------------------//

