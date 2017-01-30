//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_GeneralEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

// FRENSIE Includes
#include "MonteCarlo_GeneralEstimatorDimensionDiscretizationHelper.hpp"

namespace MonteCarlo{

/*! The general estimator dimension discretization class
 * \details If the dimension is not compatible with the continuous ordered,
 * discrete ordered or unordered treatments provided by the
 * StandardOrderedEstimatorDimensionDiscretization class or the
 * UnorderedEstimatorDimensionDiscretization class respectively then a 
 * specialization of this class should be made.
 */
template<ObserverPhaseSpaceDimension dimension>
class GeneralEstimatorDimensionDiscretization : public typename GeneralEstimatorDimensionDiscretizationHelper<dimension>::BaseEstimatorDimensionDiscretization
{

private:

  // Estimator phase space dimension traits typedef
  typedef ObserverPhaseSpaceDimensionTraits<dimension> DT;

  // The base distribution type
  typedef typename GeneralEstimatorDimensionDiscretizationHelper<dimension>::BaseEstimatorDimensionDiscretization BaseEstimatorDimensionDiscretization;

  // The input bin array type
  typedef typename GeneralEstimatorDimensionDiscretizationHelper<dimension>::InputArray InputArray;

public:

  //! Constructor
  GeneralEstimatorDimensionDiscretization(
                                        const InputArray& dimension_bin_data );

  //! Destructor
  virtual ~GeneralEstimatorDimensionDiscretization()
  { /* ... */ }

  //! Return the dimension name that has been discretized
  std::string getDimensionName() const override;

  //! Check if the value is contained in the dimension discretization
  bool isValueInDiscretization( const EstimatorParticleStateWrapper& particle_state_wrapper ) const override;

  //! Check if the value is contained in the dimension discretization
  bool isValueInDiscretization( const Teuchos::any& any_value ) const override;

  //! Check if the range intersects the discretization
  bool doesRangeIntersectDiscretization( const EstimatorParticleStateWrapper& particle_state_wrapper ) const override;

  //! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& bin_indices ) const override;

  //! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue(
                             const Teuchos::any& any_value,
                             BinIndexArray& bin_indices ) const override;

  //! Calculate the index of bins that the value range falls in
  void calculateBinIndicesOfRange(
             const EstimatorParticleStateWrapper& particle_state_wrapper,
             BinIndexWeightPairArray& bin_indices_and_weights ) const override;

  //! Export the bin boundaries
  void exportData( const ParticleHistoryObserver::idType estimator_id,
                   EstimatorHDF5FileHandler& hdf5_file ) const;

private:

  using StandardBasicEstimatorDimensionDiscretization<typename DT::dimensionType>::isValueInDiscretization;
  using StandardBasicEstimatorDimensionDiscretization<typename DT::dimensionType>::calculateBinIndex;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_GeneralEstimatorDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_GeneralEstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
