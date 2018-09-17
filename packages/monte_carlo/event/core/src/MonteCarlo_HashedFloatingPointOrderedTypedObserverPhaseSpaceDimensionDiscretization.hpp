//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Hashed floating point ordered typed observer phase space dimension
//!         discretization declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HASHED_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_HASHED_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

// FRENSIE Includes
#include "MonteCarlo_FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "Utility_HashBasedGridSearcher.hpp"

namespace MonteCarlo{

/*! \brief The hashed floating point ordered typed observer phase space
 * dimension discretization class.
 *
 * This class specialization will only be used if the dimension value type
 * associated with a dimension is a floating point type. If a dimension is used
 * that doesn't meet this requirement a compilation error will occur.
 */
template<ObserverPhaseSpaceDimension dimension>
class HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization :
public FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>
{
  // Typedef for the base type
  typedef FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension> BaseType;

protected:

  //! Typedef for the dimension value type
  typedef typename BaseType::DimensionValueType DimensionValueType;

public:

  //! Typedef for bin index array
  typedef typename BaseType::BinIndexArray BinIndexArray;

  //! Typedef for bin index and weight pair
  typedef typename BaseType::BinIndexWeightPair BinIndexWeightPair;

  //! Typedef for bin index and weight pair array
  typedef typename BaseType::BinIndexWeightPairArray BinIndexWeightPairArray;

  //! Typedef for the bin boundaries array
  typedef typename BaseType::BinBoundaryArray BinBoundaryArray;

  //! Destructor
  virtual ~HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

protected:

  //! Default constructor
  HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization();

  //! Constructor
  HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization(
                            const BinBoundaryArray& dimension_bin_boundaries );

  //! Constructor (with number of hash grid bins specified)
  HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization(
                              const BinBoundaryArray& dimension_bin_boundaries,
                              const unsigned hash_grid_bins );

  //! Calculate the index of the bin  that the value falls in
  size_t calculateBinIndexOfValue(
                         const DimensionValueType value ) const final override;

private:

  // Serialize the discretization
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The hash-based grid searcher
  std::unique_ptr<Utility::HashBasedGridSearcher<DimensionValueType> >
  d_grid_searcher;
};

} // end MonteCarlo namespace

#define BOOST_SERIALIZATION_HASHED_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_VERSION( version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
      HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization, MonteCarlo, version, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( MonteCarlo::ObserverPhaseSpaceDimension Dim ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( Dim ) )

BOOST_SERIALIZATION_HASHED_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_VERSION( 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_HASHED_FLOATING_POINT_ORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HashedFloatingPointOrderedTypedPhaseSpaceDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
