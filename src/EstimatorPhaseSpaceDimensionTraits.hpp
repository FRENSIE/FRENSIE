//---------------------------------------------------------------------------//
//!
//! \file   EstimatorPhaseSpaceDimensionTraits.hpp
//! \author Alex Robinson
//! \brief  Estimator phase space dimension traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef ESTIMATOR_PHASE_SPACE_DIMENSION_TRAITS_HPP
#define ESTIMATOR_PHASE_SPACE_DIMENSION_TRAITS_HPP

// Std Lib Includes
#include <limits>

// FACEMC Includes
#include "EstimatorPhaseSpaceDimensionTraitsDecl.hpp"
#include "EstimatorPhaseSpaceDimension.hpp"

namespace FACEMC{

namespace Traits{

/*! The specialization of the EstimatorPhaseSpaceDimensionTraits for 
 * ENERGY_DIMENSION
 * \ingroup estimator_phase_space_dim_traits
 */
template<>
struct EstimatorPhaseSpaceDimensionTraits<ENERGY_DIMENSION>
{
  typedef double dimensionType;
  
  static inline std::string name()
  { return "Energy"; }

  static inline dimensionType lowerBound()
  { return 0.0; }

  static inline dimensionType upperBound()
  { return std::numeric_limits<dimensionType>::infinity(); }

  static inline dimensionType& getValue( Teuchos::any& any_container )
  { return Teuchos::any_cast<dimensionType>( any_container ); }

  static inline const dimensionType& getValue( const Teuchos::any& any_container )
  { return Teuchos::any_cast<dimensionType>( any_container );  }
};

/*! The specialization of the EstimatorPhaseSpaceDimensionTraits for
 * COSINE_DIMENSION
 * \ingroup estimator_phase_space_dim_traits
 */
template<>
struct EstimatorPhaseSpaceDimensionTraits<COSINE_DIMENSION>
{
  typedef double dimensionType;
    
  static inline std::string name()
  { return "Cosine"; }

  static inline dimensionType lowerBound()
  { return -1.0; }

  static inline dimensionType upperBound()
  { return 1.0; }

  static inline dimensionType& getValue( Teuchos::any& any_container )
  { return Teuchos::any_cast<dimensionType>( any_container ); }

  static inline const dimensionType& getValue( const Teuchos::any& any_container )
  { return Teuchos::any_cast<dimensionType>( any_container );  }
};

/*! The specialization of the EstimatorPhaseSpaceDimensionTraits for
 * TIME_DIMENSION
 * \ingroup estimator_phase_space_dim_traits
 */
template<>
struct EstimatorPhaseSpaceDimensionTraits<TIME_DIMENSION>
{
  typedef double dimensionType;
    
  static inline std::string name()
  { return "Time"; }

  static inline dimensionType lowerBound()
  { return 0.0; }

  static inline dimensionType upperBound()
  { return std::numeric_limits<dimensionType>::infinity(); }

  static inline dimensionType& getValue( Teuchos::any& any_container )
  { return Teuchos::any_cast<dimensionType>( any_container ); }

  static inline const dimensionType& getValue( const Teuchos::any& any_container )
  { return Teuchos::any_cast<dimensionType>( any_container );  }
};

/*! The specialization of the EstimatorPhaseSpaceDimensionTraits for
 * COLLISION_NUMBER_DIMENSION
 * \ingroup estimator_phase_space_dim_traits
 */
template<>
struct EstimatorPhaseSpaceDimensionTraits<COLLISION_NUMBER_DIMENSION>
{
  typedef unsigned dimensionType;
    
  static inline std::string name()
  { return "Collision Number"; }

  static inline dimensionType lowerBound()
  { return 0u; }

  static inline dimensionType upperBound()
  { return std::numeric_limits<dimensionType>::max(); }

  static inline dimensionType& getValue( Teuchos::any& any_container )
  { return Teuchos::any_cast<dimensionType>( any_container ); }

  static inline const dimensionType& getValue( const Teuchos::any& any_container )
  { return Teuchos::any_cast<dimensionType>( any_container );  }
};

} // end Traits namespace

} // end FACEMC namespace

#endif // end ESTIMATOR_PHASE_SPACE_DIMENSION_TRAITS_HPP

//---------------------------------------------------------------------------//
// end EstimatorPhaseSpaceDimensionTraits.hpp
//---------------------------------------------------------------------------//
