//---------------------------------------------------------------------------//
//!
//! \file   DataGen_SoftElasticElectronDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The soft elastic electron scattering data generator bazse decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_SOFT_ELASTIC_ELECTRON_DATA_GENERATOR_HPP
#define DATA_GEN_SOFT_ELASTIC_ELECTRON_DATA_GENERATOR_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Data_SoftElasticElectronVolatileDataContainer.hpp"

namespace DataGen{

//! The soft elastic electron scattering data generator
class SoftElasticElectronDataGenerator
{

public:

  //! Constructor
  SoftElasticElectronDataGenerator( const unsigned atomic_number );

  //! Destructor
  virtual ~SoftElasticElectronDataGenerator()
  { /* ... */ }

  //! Populate the soft elastic electron data container
  virtual void populateSoftElasticDataContainer(
    Data::SoftElasticElectronVolatileDataContainer& data_container,
    const int& number_of_discrete_angles ) const = 0;

protected:

  //! Set the atomic number
  void setAtomicNumber( Data::SoftElasticElectronVolatileDataContainer&
                        data_container ) const;

  //! Get the atomic number
  unsigned getAtomicNumber() const;

private:

  // The atomic number for which soft elastic data can be generated
  unsigned d_atomic_number;
};

} // end DataGen namespace

#endif // end DATA_GEN_SOFT_ELASTIC_ELECTRON_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_SoftElasticElectronDataGenerator.hpp
//---------------------------------------------------------------------------//
