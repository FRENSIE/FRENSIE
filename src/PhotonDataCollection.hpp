#ifndef PHOTON_DATA_COLLECTION_HPP
#define PHOTON_DATA_COLLECTION_HPP

#include "PhotonDataCollectionBase.hpp"
#include "ParticleType.hpp"

// Trilinos Includes
#include "Teuchos_RCP.hpp"


namespace FAPMC{

class PhotonDataCollection : public PhotonDataCollectionBase
{

public:

  //@{
  //! Typedefs.
  // All Data Collection Types are refered to as "DataCollection" in 
  // template parameters for other classes. The following typedefs need
  // to be defined for all Data Collections since they are an integral
  // part of the data collection interface design.
  //
  // It might be better to move this to a traits class, but for now it will
  // stay here...
  typedef Teuchos::RCP<PhotonDataCollection> DataCollectionPointer;
  typedef PhotonDataCollection& DataCollectionReference;
  //@}

  //! Default Constructor
  PhotonDataCollection() : PhotonDataCollectionBase()
  { /* ... */ }

  /*!
   * \brief Constructor.
   *
   * \param atomic_number the atomic number of the element that will be loaded
   * from the data library
   */
  PhotonDataCollection( unsigned int atomic_number );

  //! Destructor
  ~PhotonDataCollection()
  { /* ... */ }

  //! Return the total cross section
  // Only photons should be able to call this function. Calling this function
  // for any other particle type will result in a compile time error.
  template<ParticleType partice_type>
  inline double totalCrossSection( const double energy )
  { invalidParticleType() }

  template<>
  inline double totalCrossSection<PHOTON>( const double energy )
  { return getTotalCrossSection( energy ) }
    
