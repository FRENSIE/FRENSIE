//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP
#define DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationVolatileDataContainer.hpp"

namespace DataGen{

//! The adjoint electron-photon-relaxation data generator base class
class AdjointElectronPhotonRelaxationDataGenerator
{

public:

  //! Constructor
  AdjointElectronPhotonRelaxationDataGenerator( const unsigned atomic_number );

  //! Destructor
  virtual ~AdjointElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

  //! Populate the electron-photon-relaxation data container
  virtual void populateEPRDataContainer(
                           Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const = 0;

protected:

  //! Set the atomic number
  void setAtomicNumber( Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
			data_container ) const;

  //! Get the atomic number
  unsigned getAtomicNumber() const;

private:

  // The atomic number for which relaxation data can be generated
  unsigned d_atomic_number;
};

} // end DataGen namespace

#endif // end DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
