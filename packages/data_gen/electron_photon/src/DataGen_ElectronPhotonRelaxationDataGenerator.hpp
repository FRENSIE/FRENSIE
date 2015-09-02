//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElectronPhotonRelaxationDataGenerator.hpp
//! \author Alex Robinson
//! \brief  The electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP
#define DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"

namespace DataGen{

//! The electron-photon-relaxation data generator base class
class ElectronPhotonRelaxationDataGenerator
{
  
public:

  //! Constructor
  ElectronPhotonRelaxationDataGenerator( const unsigned atomic_number );

  //! Destructor
  virtual ~ElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

  //! Populate the electron-photon-relaxation data container
  virtual void populateEPRDataContainer( 
                           Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const = 0;

protected:

  //! Set the atomic number
  void setAtomicNumber( Data::ElectronPhotonRelaxationVolatileDataContainer&
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
// end DataGen_ElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
