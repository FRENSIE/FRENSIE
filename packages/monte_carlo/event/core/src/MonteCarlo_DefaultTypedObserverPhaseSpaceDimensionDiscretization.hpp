//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Default observer dimension discretization class declarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

// Std Lib Includes
#include <type_traits>

// FRENSIE Includes
#include "MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretizationDecl.hpp"
#include "MonteCarlo_FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"

namespace MonteCarlo{

/*! \brief The default typed observer phase space dimension discretization
 * class specialization for floating point ordered dimensions.
 */
template<ObserverPhaseSpaceDimension dimension>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value && ObserverPhaseSpaceDimensionTraits<dimension>::isOrdered::value>::type> : public FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>
{ 
  // Typedef for the base type
  typedef FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension> BaseType;

protected:

  //! Typedef for the dimension value type
  typedef typename BaseType::DimensionValueType DimensionValueType;
  
public:

  //! Typedef for the input data type
  typedef typename BaseType::BinBoundaryArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization(
                                     const InputDataType& discretization_data )
    : BaseType( discretization_data )
  { /* ... */ }

  //! Constructor (with number of hash grid bins specified)
  DefaultTypedObserverPhaseSpaceDimensionDiscretization(
                                      const InputDataType& discretization_data,
                                      const unsigned hash_grid_bins );

  //! Destructor
  ~DefaultTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

private:

  // Default constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

  // Serialize the discretization
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

/*! \brief The default typed observer phase space dimension discretization
 * class specialization for integral ordered dimensions.
 */
template<ObserverPhaseSpaceDimension dimension>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value && ObserverPhaseSpaceDimensionTraits<dimension>::isOrdered::value>::type> : public IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>
{
  // Typedef for the base type
  typedef IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension> BaseType;

protected:

  //! Typedef for the dimension value type
  typedef typename BaseType::DimensionValueType DimensionValueType;

public:

  //! Typedef for the input data type
  typedef typename BaseType::BinBoundaryArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization(
                                     const InputDataType& discretization_data )
    : BaseType( discretization_data )
  { /* ... */ }

  //! Destructor
  ~DefaultTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

private:

  // Default constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

  // Serialize the discretization
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

/*! \brief The default typed observer phase space dimension discretization
 * class specialization for unordered dimensions.
 */
template<ObserverPhaseSpaceDimension dimension>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename std::enable_if<std::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>::value && !ObserverPhaseSpaceDimensionTraits<dimension>::isOrdered::value>::type> : public UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>
{
  // Typedef for the base type
  typedef UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension> BaseType;

protected:

  //! Typedef for the dimension value type
  typedef typename BaseType::DimensionValueType DimensionValueType;
  
public:

  //! Typedef for the input data type
  typedef typename BaseType::BinSetArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization(
                                     const InputDataType& discretization_data )
    : BaseType( discretization_data )
  { /* ... */ }

  //! Destructor
  ~DefaultTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

private:

  // Default constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

  // Serialize the discretization
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

//! The observer cosine dimension discretization
typedef DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_COSINE_DIMENSION> ObserverCosineDimensionDiscretization;

//! The observer source energy dimension discretization
typedef DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_ENERGY_DIMENSION> ObserverSourceEnergyDimensionDiscretization;

//! The observer energy dimension discretization
typedef DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_ENERGY_DIMENSION> ObserverEnergyDimensionDiscretization;

//! The observer source time dimension discretization
typedef DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_TIME_DIMENSION> ObserverSourceTimeDimensionDiscretization;

//! The observer time dimension discretization
typedef DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_TIME_DIMENSION> ObserverTimeDimensionDiscretization;

//! The observer collision number dimension discretization
typedef DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_COLLISION_NUMBER_DIMENSION> ObserverCollisionNumberDimensionDiscretization;

//! The observer source id dimension discretization
typedef DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_ID_DIMENSION> ObserverSourceIdDimensionDiscretization;

} // end MonteCarlo namespace

#define BOOST_SERIALIZATION_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_VERSION( version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
      DefaultTypedObserverPhaseSpaceDimensionDiscretization, MonteCarlo, version, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( MonteCarlo::ObserverPhaseSpaceDimension Dim ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( Dim ) )

BOOST_SERIALIZATION_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_VERSION( 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_GeneralEstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
