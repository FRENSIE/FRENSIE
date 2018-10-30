//---------------------------------------------------------------------------//
//!
//! \file   DataGen_MomentPreservingElectronDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The moment preserving electron scattering data generator base decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_MOMENT_PRESERVING_ELECTRON_DATA_GENERATOR_HPP
#define DATA_GEN_MOMENT_PRESERVING_ELECTRON_DATA_GENERATOR_HPP

// FRENSIE Includes
#include "Data_MomentPreservingElectronVolatileDataContainer.hpp"

namespace DataGen{

//! The moment preserving electron scattering data generator
class MomentPreservingElectronDataGenerator
{

public:

  //! Constructor
  MomentPreservingElectronDataGenerator( const unsigned atomic_number );

  //! Destructor
  virtual ~MomentPreservingElectronDataGenerator()
  { /* ... */ }

  //! Populate the moment preserving electron data container
  virtual void populateMomentPreservingDataContainer(
    Data::MomentPreservingElectronVolatileDataContainer& data_container,
    const int& number_of_discrete_angles ) const = 0;

protected:

  //! Set the atomic number
  void setAtomicNumber( Data::MomentPreservingElectronVolatileDataContainer&
                        data_container ) const;

  //! Get the atomic number
  unsigned getAtomicNumber() const;

private:

  // The atomic number for which moment preserving data can be generated
  unsigned d_atomic_number;
};

} // end DataGen namespace

#endif // end DATA_GEN_MOMENT_PRESERVING_ELECTRON_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_MomentPreservingElectronDataGenerator.hpp
//---------------------------------------------------------------------------//
