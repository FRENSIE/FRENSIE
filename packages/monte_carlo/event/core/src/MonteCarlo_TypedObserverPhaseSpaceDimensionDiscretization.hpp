//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Typed observer phase space dimension discretization base class
//!         declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"

namespace MonteCarlo{

//! The typed estimator dimension discretization base class
template<ObserverPhaseSpaceDimension dimension>
class TypedObserverPhaseSpaceDimensionDiscretization : public ObserverPhaseSpaceDimensionDiscretization
{

protected:

  //! Typedef for the dimension traits
  typedef ObserverPhaseSpaceDimensionTraits<dimension> DT;

  //! Typedef for the dimension value type
  typedef typename DT::dimensionType DimensionValueType;

public:

  //! Typedef for bin index array
  typedef ObserverPhaseSpaceDimensionDiscretization::BinIndexArray BinIndexArray;

  //! Typedef for bin index and weight pair
  typedef ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPair BinIndexWeightPair;

  //! Typedef for bin index and weight pair array
  typedef ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray BinIndexWeightPairArray;

  //! Constructor
  TypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

  //! Destructor
  virtual ~TypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

  //! Return the dimension that has been discretized
  ObserverPhaseSpaceDimension getDimension() const override;

  //! Return the dimension name that has been discretized
  std::string getDimensionName() const override;

  //! Check if the value is in the discretization
  bool isValueInDiscretization(
   const ObserverParticleStateWrapper& particle_state_wrapper ) const override;

  //! Check if the value is contained in the discretization
  bool isValueInDiscretization( const boost::any& any_value ) const override;

  //! Check if the range intersects the discretization
  bool doesRangeIntersectDiscretization(
   const ObserverParticleStateWrapper& particle_state_wrapper ) const override;

  //! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue(
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& bin_indices ) const override;

  //! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue(
             const ObserverParticleStateWrapper& particle_state_wrapper,
             BinIndexWeightPairArray& bin_indices_and_weights ) const override;

  //! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue( const boost::any& any_value,
                                   BinIndexArray& bin_indices ) const override;

  //! Calculate the index of bins that the value range falls in
  void calculateBinIndicesOfRange(
             const ObserverParticleStateWrapper& particle_state_wrapper,
             BinIndexWeightPairArray& bin_indices_and_weights ) const override;

protected:

  //! Check if the value is contained in the discretization
  virtual bool isValueInDiscretization(
                                    const DimensionValueType value ) const = 0;

  //! Check if the value range intersects the discretization
  virtual bool doesRangeIntersectDiscretization(
                                const DimensionValueType range_start,
                                const DimensionValueType range_end ) const = 0;

  //! Calculate the index of bins that the value falls in
  virtual void calculateBinIndicesOfValue(
                                        const DimensionValueType value,
                                        BinIndexArray& bin_indices ) const = 0;

  //! Calculate the index of bins that the value falls in
  virtual void calculateBinIndicesOfValue(
                  const DimensionValueType value,
                  BinIndexWeightPairArray& bin_indices_and_weights ) const = 0;

  //! Calculate the index of bins that the range falls in
  virtual void calculateBinIndicesOfRange(
                  const DimensionValueType range_start,
                  const DimensionValueType range_end,
                  BinIndexWeightPairArray& bin_indices_and_weights ) const = 0;

private:

  // Serialize the discretization
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

#define BOOST_SERIALIZATION_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_VERSION( version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
      TypedObserverPhaseSpaceDimensionDiscretization, MonteCarlo, version, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( MonteCarlo::ObserverPhaseSpaceDimension Dim ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( Dim ) )

BOOST_SERIALIZATION_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_VERSION( 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( TypedObserverPhaseSpaceDimensionDiscretization, MonteCarlo );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
