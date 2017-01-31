//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

// Boost Includes
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/mpl/logical.hpp>

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
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::mpl::and_<boost::is_floating_point<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>,typename ObserverPhaseSpaceDimensionTraits<dimension>::isOrdered> > > : public FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>
{ 

public:

  //! Typedef for the dimension value type
  typedef typename FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::DimensionValueType DimensionValueType;

  //! Typedef for the input data type
  typedef typename FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::BinBoundariesArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization(
                                     const InputDataType& discretization_data )
    : FloatingPointOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>( discretization_data )
  { /* ... */ }

  //! Destructor
  ~DefaultTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }
};

/*! \brief The default typed observer phase space dimension discretization
 * class specialization for integral ordered dimensions.
 */
template<ObserverPhaseSpaceDimension dimension>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::mpl::and_<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>,typename ObserverPhaseSpaceDimensionTraits<dimension>::isOrdered> > > : public IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>
{ 

public:

  //! Typedef for the dimension value type
  typedef typename IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::DimensionValueType DimensionValueType;

  //! Typedef for the input data type
  typedef typename IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::BinBoundariesArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization(
                                     const InputDataType& discretization_data )
    : IntegralOrderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>( discretization_data )
  { /* ... */ }

  //! Destructor
  ~DefaultTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }
};

/*! \brief The default typed observer phase space dimension discretization
 * class specialization for unordered dimensions.
 */
template<ObserverPhaseSpaceDimension dimension>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::mpl::and_<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>,boost::mpl::not_<typename ObserverPhaseSpaceDimensionTraits<dimension>::isOrdered> > > > : public UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>
{
  
public:

  //! Typedef for the dimension value type
  typedef typename UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::DimensionValueType DimensionValueType;

  //! Typedef for the input data type
  typedef typename UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>::BinSetArray InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization(
                                     const InputDataType& discretization_data )
    : UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension>( discretization_data )
  { /* ... */ }

  //! Destructor
  ~DefaultTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_GeneralEstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
