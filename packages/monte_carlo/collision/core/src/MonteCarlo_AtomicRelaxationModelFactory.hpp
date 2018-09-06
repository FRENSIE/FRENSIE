//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicRelaxationModelFactory.hpp
//! \author Alex Robinson
//! \brief  The atomic relaxation model factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_RELAXATION_MODEL_FACTORY_HPP
#define MONTE_CARLO_ATOMIC_RELAXATION_MODEL_FACTORY_HPP

// Std Lib Includes
#include <memory>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_SubshellRelaxationModel.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_Vector.hpp"

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
		  std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
                  const double min_photon_energy,
                  const double min_electron_energy,
		  const bool use_atomic_relaxation_data );

  //! Create the atomic relaxation model (using Native data)
  static void createAtomicRelaxationModel(
	const Data::ElectronPhotonRelaxationDataContainer& raw_photoatomic_data,
	std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
        const double min_photon_energy,
        const double min_electron_energy,
	const bool use_atomic_relaxation_data );

  //! Create the atomic relaxation model (using Native eedl data)
  static void createAtomicRelaxationModel(
	const Data::ENDLDataContainer& raw_photoatomic_data,
	std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
        const double min_photon_energy,
        const double min_electron_energy,
	const bool use_atomic_relaxation_data );

  //! Constructor
  AtomicRelaxationModelFactory()
  { /* ... */ }

  //! Destructor
  ~AtomicRelaxationModelFactory()
  { /* ... */ }

  //! Create and cache the atomic relaxation model (ACE)
  void createAndCacheAtomicRelaxationModel(
                  const Data::XSSEPRDataExtractor& raw_photoatom_data,
                  std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
                  const double min_photon_energy,
                  const double min_electron_energy,
                  const bool use_atomic_relaxation_data );

  //! Create and cache the atomic relaxation model (Native)
  void createAndCacheAtomicRelaxationModel(
         const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
         const double min_photon_energy,
         const double min_electron_energy,
	 const bool use_atomic_relaxation_data );

  //! Create and cache the atomic relaxation model (ENDL)
  void createAndCacheAtomicRelaxationModel(
                  const Data::ENDLDataContainer& raw_photoatom_data,
                  std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
                  const double min_photon_energy,
                  const double min_electron_energy,
                  const bool use_atomic_relaxation_data );

private:

  //! Create the subshell relaxation models
  static void createSubshellRelaxationModels(
		const std::vector<Data::SubshellType>& subshell_designators,
                const Utility::ArrayView<const double>& subshell_transitions,
                const Utility::ArrayView<const double>& relo_block,
                const Utility::ArrayView<const double>& xprob_block,
                std::vector<std::shared_ptr<const SubshellRelaxationModel> >&
                subshell_relaxation_models );

  // The default void atomic relaxation model
  static const std::shared_ptr<const AtomicRelaxationModel> default_void_model;

  // The map of atomic numbers and atomic relaxation models
  std::unordered_map<unsigned,std::shared_ptr<const AtomicRelaxationModel> >
  d_relaxation_models;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_RELAXATION_MODEL_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicRelaxationModelFactory.hpp
//---------------------------------------------------------------------------//

