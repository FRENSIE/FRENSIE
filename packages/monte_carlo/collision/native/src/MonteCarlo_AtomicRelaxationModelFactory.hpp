//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicRelaxationModelFactory.hpp
//! \author Alex Robinson
//! \brief  The atomic relaxation model factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_RELAXATION_MODEL_FACTORY_HPP
#define MONTE_CARLO_ATOMIC_RELAXATION_MODEL_FACTORY_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_SubshellRelaxationModel.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

/*! The atomic relaxation model factory class 
 * \details This class will cache the relaxation models associated with
 * a particular atom so that they will not be duplicated (e.g. when 
 * constructing a photoatom and an electroatom). To create an atomic relaxation
 * model using different data, create an overload of the
 * createAtomicRelaxationModel static member function and 
 * createAndCacheAtomicRelaxationModel member function.
 */
class AtomicRelaxationModelFactory
{

public:

  //! Create the atomic relaxation model (using ACE data)
  static void createAtomicRelaxationModel(
		  const Data::XSSEPRDataExtractor& raw_photoatom_data,
		  Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
		  const bool use_atomic_relaxation_data );

  //! Create the atomic relaxation model (using Native data)
  static void createAtomicRelaxationModel(
	const Data::ElectronPhotonRelaxationDataContainer& raw_photoatomc_data,
	Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	const bool use_atomic_relaxation_data );

  //! Constructor
  AtomicRelaxationModelFactory()
  { /* ... */ }
  
  //! Destructor
  ~AtomicRelaxationModelFactory()
  { /* ... */ }

  //! Create and cache the atomic relaxation model
  void createAndCacheAtomicRelaxationModel(
		  const Data::XSSEPRDataExtractor& raw_photoatom_data,
		  Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
		  const bool use_atomic_relaxation_data );

  //! Create and cache the atomic relaxation model
  void createAndCacheAtomicRelaxationModel(
         const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	 const bool use_atomic_relaxation_data ); 

private:

  //! Create the subshell relaxation models
  static void createSubshellRelaxationModels(
		  const Teuchos::Array<SubshellType>& subshell_designators,
		  const Teuchos::ArrayView<const double>& subshell_transitions,
		  const Teuchos::ArrayView<const double>& relo_block,
		  const Teuchos::ArrayView<const double>& xprob_block,
		  Teuchos::Array<Teuchos::RCP<const SubshellRelaxationModel> >&
		  subshell_relaxation_models );
  
  // The default void atomic relaxation model
  static const Teuchos::RCP<AtomicRelaxationModel> default_void_model;

  // The map of atomic numbers and atomic relaxation models
  boost::unordered_map<unsigned,Teuchos::RCP<AtomicRelaxationModel> >
  d_relaxation_models;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_RELAXATION_MODEL_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicRelaxationModelFactory.hpp
//---------------------------------------------------------------------------//

