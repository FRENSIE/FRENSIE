//---------------------------------------------------------------------------//
// \file   PhotonDataCollectionBase.hpp
// \author Alex Robinson
// \brief  Photon Data Collection base class declaration.
//---------------------------------------------------------------------------//

#ifndef PHOTON_DATA_COLLECTION_BASE_HPP
#define PHOTON_DATA_COLLECTION_BASE_HPP

//Std Lib Includes
#include <string>

//Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_Map.hpp>

// FACEMC Includes
#include "ElectronShell.hpp"
#include "PhotonReactionType.hpp"

namespace FACEMC{

class PhotonDataCollectionBase
{

protected:

  //------------------------------------------------------------------------//
  // Basic Photon Physics Member Functions
  //------------------------------------------------------------------------//

  //! Return the atomic number of the element stored
  unsigned int getAtomicNumber() const;

  //! Return the atomic weight of the element stored
  double getAtomicWeight() const;

  //! Return the integrated coherent cross section for a given energy
  double getCoherentCrossSection( const double energy ) const;

  //! Return the form factor for a given argument
  double getFormFactorValue( const double argument ) const;

  //! Return the integrated incoherent cross section for a given energy
  double getIncoherentCrossSection( const double energy ) const;

  //! Return the scattering function for a given argument
  double getScatteringFunctionValue( const double argument ) const;

  //! Return the integrated photoelectric cross section for a given energy
  double getPhotoelectricCrossSection( const double energy ) const;

  //! Return the integrated pair production cross section for a given energy
  double getPairProductionCrossSection( const double energy ) const;

  //! Return the integrated triplet production cross section for a given energy
  double getTripletProductionCrossSection( const double energy ) const;

  //! Return the total cross section for a given energy
  double getTotalCrossSection( const double energy ) const;

  //! Return the non absorption probability for a given energy
  double getNonAbsorptionProbability( const double energy ) const;

  //! Return the reaction type
  template<bool implicit_capture>
  PhotonReactionType getReaction( const double energy,
				  const double random_number ) const;

  //------------------------------------------------------------------------//
  // Detailed Photon Physics Member Functions
  //------------------------------------------------------------------------//
  
  //! Sample the atomic shell that will be used for doppler broadening
  AtomicShell sampleAtomicShell( const double random_number ) const;

  //! Return the valence atomic shell
  AtomicShell getValenceShell( const double random_number ) const;

  //! Return the binding energy of electrons in a given shell 
  double getElectronBe( const AtomicShell shell ) const;
  
  //! Return the kinetic energy of electrons in a given shell
  double getElectronKe( const AtomicShell shell ) const;
  
  //! Sample the electron momentum projection for a given shell
  double sampleElectronMomentum( const double random_number,
				 const AtomicShell shell ) const;

protected:

// Protect the constructor and destructor so that this base class can never
// be instantiated without being inherited. If the construct and destructor
// were public, we could use pointers to the base class to refer to refer
// to derived classes, which would necessitate the use of a virtual destructor.

//! Default Constructor.
  PhotonDataCollectionBase()
  { /* ... */ }

  /*!
   * \brief Constructor.
   *
   * \param atomic_number the atomic number of the element that will be loaded
   * from the data library
   */
  PhotonDataCollectionBase( unsigned int atomic_number );

  //! Destructor
  ~PhotonDataCollectionBase()
  { /* ... */ }

private:

  //@{
  //! Private Typedefs.
  // These typdefs should only be used inside of this class
  typedef Teuchos::Array<unsigned int> PDCBintarray;
  typedef Teuchos::Array<double> PDCBfloatarray;
  typedef Teuchos::Array<AtomicShell> PDCBshellarray;
  typedef Teuchos::Array< Teuchos::Array<double> > PDCB2dfloatarray;
  //@}
  
  // Atomic Number
  unsigned int d_z;

  // Atomic Weight
  double d_aw;
  
  //-------------------------------------------------------------------------//
  // Coherent Scattering Data
  //-------------------------------------------------------------------------//

  // Integrated coherent cross section
  //    array[0] contains the evaluated energies
  //    array[1] contains the cross section values
  PDCBfloatarray d_integrated_coherent_cross_section[2];

  // Coherent cross section form factor
  //    array[0] contains the evaluated arguments
  //    array[1] constains the form factor values
  PDCBfloatarray d_form_factor[2];

  //-------------------------------------------------------------------------//
  // Incoherent Scattering
  //-------------------------------------------------------------------------//

  // Integrated incoherent cross section
  //   array[0] contains the evaluated energies
  //   array[1] contains the cross section values
  PDCBfloatarray d_integrated_incoherent_cross_section[2];

  // Incoherent cross section scattering function
  //    array[0] contains the evaluated arguments
  //    array[1] contains the scattering function values
  PDCBfloatarray d_scattering_function_values[2];

  //-------------------------------------------------------------------------//
  // Doppler Broadening
  //-------------------------------------------------------------------------//
  
  // Discrete CDF of the number of electrons per shell
  PDCBfloatarray d_electrons_per_shell_cdf;

  // Electron binding energy per shell
  PDCBfloatarray d_electron_be_per_shell;

  // Electron kinetic energy per shell
  PDCBfloatarray d_electron_ke_per_shell;

  // Compton profile cdf for each shell
  PDCB2dfloatarray d_compton_profile_cdf_per_shell;

  // Atomic shell index of electrons in each shell
  PDCBshellarray d_electrons_shell_index;

  //-------------------------------------------------------------------------//
  // Photoelectric Effect
  //-------------------------------------------------------------------------//

  // Integrated photoelectric cross section
  //    array[0] contains the evaluated energies
  //    array[1] contains the cross section values
  PDCBfloatarray d_integrated_photoelectric_cross_section[2];

  //-------------------------------------------------------------------------//
  // Pair Production
  //-------------------------------------------------------------------------//

  // Integrated pair production cross section
  //    array[0] contains the evaluated energies
  //    array[1] contains the cross section values
  PDCBfloatarray d_integrated_pair_production_cross_section[2];

  //-------------------------------------------------------------------------//
  // Triplet Production
  //-------------------------------------------------------------------------//

  // Integrated triplet production cross section
  //    array[0] contains the evaluated energies
  //    array[1] contains the cross section values
  PDCBfloatarray d_integrated_triplet_production_cross_section[2];
  
//---------------------------------------------------------------------------//

} // end namespace FACEMC

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "PhotonDataCollectionBase_def.hpp"

//---------------------------------------------------------------------------//

#endif // end PHOTON_DATA_COLLECTION_BASE_HPP

//---------------------------------------------------------------------------//
// end PhotonDataCollectionBase.hpp
//---------------------------------------------------------------------------//

