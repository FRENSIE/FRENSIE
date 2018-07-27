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
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"

namespace MonteCarlo{

/*! \brief The default typed observer phase space dimension discretization
 * class
 *
 * If the dimension is not compatible with the floating point ordered,
 * integral ordered or unordered discretization treatments provided then
 * a specialization of this class for the dimension must be made. The layout
 * that has been given for this class should be used for all specializations.
 * Note that specializations of this class are only meant to provide a
 * convenient and homogenized interface for creating dimension discretizations.
 */
template<ObserverPhaseSpaceDimension dimension>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization
{ /* ... */ };

/*! \brief The default typed observer phase space dimension discretization
 * class specialization for MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION
 */
template<>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_ENERGY_DIMENSION> : public HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_ENERGY_DIMENSION>
{
  // Typedef for the base type
  typedef HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_ENERGY_DIMENSION> BaseType;

public:

  //! Typedef for input data type
  typedef BaseType::BinBoundaryArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization( const InputDataType& data )
    : BaseType( data )
  { /* ... */ }

  //! Constructor (with number of hash grid bins specified)
  DefaultTypedObserverPhaseSpaceDimensionDiscretization( const InputDataType& data,
                                                         const unsigned hash_grid_bins )
    : BaseType( data, hash_grid_bins )
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
 * class specialization for MonteCarlo::OBSERVER_ENERGY_DIMENSION
 */
template<>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_ENERGY_DIMENSION> : public HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_ENERGY_DIMENSION>
{
  // Typedef for the base type
  typedef HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_ENERGY_DIMENSION> BaseType;

public:

  //! Typedef for input data type
  typedef BaseType::BinBoundaryArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization( const InputDataType& data )
    : BaseType( data )
  { /* ... */ }

  //! Constructor (with number of hash grid bins specified)
  DefaultTypedObserverPhaseSpaceDimensionDiscretization( const InputDataType& data,
                                                         const unsigned hash_grid_bins )
    : BaseType( data, hash_grid_bins )
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
 * class specialization for MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION
 */
template<>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_TIME_DIMENSION> : public HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_TIME_DIMENSION>
{
  // Typedef for the base type
  typedef HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_TIME_DIMENSION> BaseType;

public:

  //! Typedef for input data type
  typedef BaseType::BinBoundaryArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization( const InputDataType& data )
    : BaseType( data )
  { /* ... */ }

  //! Constructor (with number of hash grid bins specified)
  DefaultTypedObserverPhaseSpaceDimensionDiscretization( const InputDataType& data,
                                                         const unsigned hash_grid_bins )
    : BaseType( data, hash_grid_bins )
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
 * class specialization for MonteCarlo::OBSERVER_TIME_DIMENSION
 */
template<>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_TIME_DIMENSION> : public HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_TIME_DIMENSION>
{
  // Typedef for the base type
  typedef HashedFloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_TIME_DIMENSION> BaseType;

public:

  //! Typedef for input data type
  typedef BaseType::BinBoundaryArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization( const InputDataType& data )
    : BaseType( data )
  { /* ... */ }

  //! Constructor (with number of hash grid bins specified)
  DefaultTypedObserverPhaseSpaceDimensionDiscretization( const InputDataType& data,
                                                         const unsigned hash_grid_bins )
    : BaseType( data, hash_grid_bins )
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
 * class specialization for MonteCarlo::OBSERVER_COSINE_DIMENSION
 */
template<>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_COSINE_DIMENSION> : public FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_COSINE_DIMENSION>
{
  // Typedef for the base type
  typedef FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_COSINE_DIMENSION> BaseType;

public:

  //! Typedef for input data type
  typedef BaseType::BinBoundaryArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization( const InputDataType& data )
    : BaseType( data )
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
 * class specialization for MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION
 */
template<>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_COLLISION_NUMBER_DIMENSION> : public IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_COLLISION_NUMBER_DIMENSION>
{
  // Typedef for the base type
  typedef IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_COLLISION_NUMBER_DIMENSION> BaseType;

public:

  //! Typedef for input data type
  typedef BaseType::BinBoundaryArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization( const InputDataType& data )
    : BaseType( data )
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
 * class specialization for MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION
 */
template<>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_ID_DIMENSION> : public UnorderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_ID_DIMENSION>
{
  // Typedef for the base type
  typedef UnorderedTypedObserverPhaseSpaceDimensionDiscretization<OBSERVER_SOURCE_ID_DIMENSION> BaseType;

public:

  //! Typedef for input data type
  typedef BaseType::BinSetArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization( const InputDataType& data )
    : BaseType( data )
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
