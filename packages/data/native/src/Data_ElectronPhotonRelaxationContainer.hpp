//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationContainer.hpp
//! \author Alex Robinson
//! \brief  The native electron-photon-relaxation data container class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ELECTRON_PHOTON_RELAXATION_CONTAINER_HPP
#define DATA_ELECTRON_PHOTON_RELAXATION_CONTAINER_HPP

namespace Data{

//! The electron-photon-relaxation data container
class ElectronPhotonRelaxationContainer
{

public:

  //! Return the photon energy grid
  Teuchos::ArrayView<const double>
  getPhotonEnergyGrid() const;

  //! Return the incoherent photon cross section using Waller-Hartree theory
  Teuchos::ArrayView<const double> 
  getWallerHartreeIncoherentCrossSection() const;

  //! Return the incoherent photon cross section threshold energy bin index
  unsigned
  getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex() const;

  //! Return the incoherent photon cross section using the impulse approx.
  Teuchos::ArrayView<const double>
  getImpulseApproxIncoherentCrossSection() const;

  //! Return the incoherent photon cross section threshold energy bin index
  unsigned
  getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex() const;

  //! Return the subshell incoherent photon cs using the impulse approx.
  Teuchos::ArrayView<const double>
  getImpulseApproxSubshellIncoherentCrossSection( 
					   const SubshellType subshell ) const;

  //! Return the subshell incoherent photon cs threshold energy bin index
  unsigned
  getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 
					   const SubshellType subshell ) const;

  //! Return the coherent cross section using Waller-Hartree theory
  Teuchos::ArrayView<const double>
  getWallerHartreeCoherentCrossSection() const;

  //! Return the coherent cross section threshold energy bin index
  Teuchos::ArrayView<const double>
  getWallerHartreeCoherentCrossSectionThresholdEnergyIndex() const;

  //! Return the pair production cross section
  Teuchos::ArrayView<const double>
  getPairProductionCrossSection() const;

  //! Return the pair production cross section threshold energy bin index
  unsigned getPairProductionCrossSectionThresholdEnergyIndex() const;

  //! Return the triplet production cross section
  Teuchos::ArrayView<const double>
  getTripletProductionCrossSection() const;

  //! Return the triplet production cross section threshold energy bin index
  unsigned getTripletProductionCrossSectionThresholdEnergyIndex() const;

  //! Return the Photoelectric effect cross section
  Teuchos::ArrayView<const double>
  getPhotoelectricCrossSection() const;

  //! Return the Photoelectric effect cross section theshold energy bin index
  unsigned getPhotoelectricCrossSectionThresholdEnergyIndex() const;

  //! Return the Photoelectric effect cross section for a subshell
  Teuchos::ArrayView<const double>
  getSubshellPhotoelectricCrossSection( const SubshellType subshell ) const;

  //! Return the subshell Photoelectric effect cross section threshold index
  unsigned
  getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 
					   const SubshellType subshell ) const;

protected:

private:

};

} // end Data namespace

#endif // end DATA_ELECTRON_PHOTON_RELAXATION_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationContainer.hpp
//---------------------------------------------------------------------------//

