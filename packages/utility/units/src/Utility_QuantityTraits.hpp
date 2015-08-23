//---------------------------------------------------------------------------//
//!
//! \file   Utility_QuantityTraits.hpp
//! \author Alex Robinson
//! \brief  Quantity traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_QUANTITY_TRAITS_HPP
#define UTILITY_QUANTITY_TRAITS_HPP

// FRENSIE Includes
#include "Utility_QuantityTraitsDecl.hpp"

namespace Utility{

/*! The specialization of QuantityTraits for double (no units).
 *
 * Note that having no units is different from a dimensionless unit.
 * \ingroup unit_traits
 */
template<>
struct QuantityTraits<double>
{
  typedef void Unit;
  typedef double RawType;

  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetQuantityToPowerType
  { typedef double type; };

  static inline double zero()
  { return 0.0; }

  static inline double one()
  { return 1.0; }

  static inline double sqrt( const double quantity )
  { return std::sqrt( quantity ); }

  template<boost::units::integer_type N, boost::units::integer_type D>
  static inline double rpow( const double quantity )
  { return boost::units::pow<boost::units::static_rational<N,D> >( quantity ); }
  
  static inline double initializeQuantity( const double& raw_quantity )
  { return raw_quantity; }

  static inline const double& getRawQuantity( const double& quantity )
  { return quantity; }

  static inline void setQuantity( double& quantity,
				  const double& raw_quantity )
  { quantity = raw_quantity; }
};

/*! The specialization of QuantityTraits for int (no units).
 *
 * Note that having no units is different from a dimensionless unit.
 * \ingroup unit_traits
 */
template<>
struct QuantityTraits<int>
{
  typedef void Unit;
  typedef int RawType;

  static inline int zero()
  { return 0; }

  static inline int one()
  { return 1; }
  
  static inline int initializeQuantity( const int& raw_quantity )
  { return raw_quantity; }

  static inline const int& getRawQuantity( const int& quantity )
  { return quantity; }

  static inline void setQuantity( int& quantity,
				  const int& raw_quantity )
  { quantity = raw_quantity; }
};

/*! The specialization of QuantityTraits for unsigned (no units).
 *
 * Note that having no units is different from a dimensionless unit.
 * \ingroup unit_traits
 */
template<>
struct QuantityTraits<unsigned>
{
  typedef void Unit;
  typedef unsigned RawType;

  static inline unsigned zero()
  { return 0; }

  static inline unsigned one()
  { return 1; }
  
  static inline unsigned initializeQuantity( const unsigned& raw_quantity )
  { return raw_quantity; }

  static inline const unsigned& getRawQuantity( const unsigned& quantity )
  { return quantity; }

  static inline void setQuantity( unsigned& quantity,
				  const unsigned& raw_quantity )
  { quantity = raw_quantity; }
};

} // end Utility namespace

#endif // end UTILITY_QUANTITY_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_QuantityTraits.hpp
//---------------------------------------------------------------------------//
