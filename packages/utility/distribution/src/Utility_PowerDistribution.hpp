//---------------------------------------------------------------------------//
//!
//! \file   Utility_PowerDistribution.hpp
//! \author Alex Robinon
//! \brief  Power distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POWER_DISTRIBUTION_HPP
#define UTILITY_POWER_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_ExponentiationAlgorithms.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

/*! Power distribution class
 * \ingroup one_d_distributions
 */
template<unsigned N, typename IndependentUnit, typename DependentUnit>
class UnitAwarePowerDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
				   public ParameterListCompatibleObject<UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit> >
{

private:

  // The independent unit to power N+1
  typedef UnitTraits<typename UnitTraits<IndependentUnit>::template GetUnitToPowerType<N+1>::type> IndepUnitTraitsNp1;

  // The independent unit to power N+1 quantity type
  typedef typename IndepUnitTraitsNp1::template GetQuantityType<double>::type IndepQuantityNp1;

  // The distribution multiplier unit traits
  typedef UnitTraits<typename UnitTraits<DependentUnit>::template GetMultipliedUnitType<typename UnitTraits<IndependentUnit>::template GetUnitToPowerType<N,-1>::type>::type> DistMultiplierUnitTraits;

  // The distribution multiplier quantity type
  typedef typename DistMultiplierUnitTraits::template GetQuantityType<double>::type DistMultiplierQuantity;

  // The distribution normalization quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DistNormQuantity DistNormQuantity;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity> DQT;

  // Typedef for QuantityTraits<DistMultiplierQuantity>
  typedef QuantityTraits<DistMultiplierQuantity> DMQT;

public:

  //! This distribution type
  typedef UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;
  
  //! Default constructor
  UnitAwarePowerDistribution();

  //! Constructor ( A*x^N : x in (a,b) )
  template<typename InputIndepQuantity>
  UnitAwarePowerDistribution( const double constant_multiplier,
			      const InputIndepQuantity min_indep_limit,
			      const InputIndepQuantity max_indep_limit );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwarePowerDistribution( const UnitAwarePowerDistribution<N,InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwarePowerDistribution fromUnitlessDistribution( const UnitAwarePowerDistribution<N,void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwarePowerDistribution& operator=( const UnitAwarePowerDistribution& dist_instance );

  //! Destructor
  ~UnitAwarePowerDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value) const;

  //! Return a random sample from the distribution
  IndepQuantity sample() const;

  //! Return a random sample from the distribution
  static IndepQuantity sample( const IndepQuantity min_independent_value,
			       const IndepQuantity max_independent_value );

  //! Return a random sample and record the number of trials
  IndepQuantity sampleAndRecordTrials( unsigned& trials ) const;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Test if the distribution is continuous
  bool isContinuous() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const UnitAwarePowerDistribution& other ) const;

protected:
  
  //! Copy constructor (copying from unitless distribution only)
  UnitAwarePowerDistribution( const UnitAwarePowerDistribution<N,void,void>& unitless_dist_instance, int );

private:

  // Initialize the distribution
  void initializeDistribution();

  // All possible instantiations are friends
  template<unsigned M, typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwarePowerDistribution;

  // The multiplier
  DistMultiplierQuantity d_multiplier;

  // The min independent variable limit
  IndepQuantity d_min_indep_limit;

  // The min independent variable limit to the power N+1
  IndepQuantityNp1 d_min_indep_limit_to_power_Np1;

  // The max independent variable limit
  IndepQuantity d_max_indep_limit;
  
  // The max independent variable limit to the power N+1
  IndepQuantityNp1 d_max_indep_limit_to_power_Np1;

  // The normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The power distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
template<unsigned N> using PowerDistribution = 
  UnitAwarePowerDistribution<N,void,void>;

/*! Power distribution traits struct for power N
 * \ingroup one_d_distributions
 * \ingroup traits
 */
template<unsigned N>
struct PowerDistributionTraits
{
  //! The distribution type
  static const OneDDistributionType distribution_type = POWER_N_DISTRIBUTION;

  //! The N+1 root function
  template<typename Np1Quantity>
  static inline typename QuantityTraits<Np1Quantity>::template GetQuantityToPowerType<1,N+1>::type np1Root( const Np1Quantity& quantity )
  { return rpow<1,N+1>( quantity ); }

  //! The pow N function
  template<typename Quantity>
  static inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<N>::type powN( const Quantity& quantity )
  { 
    return QuantityTraits<typename QuantityTraits<Quantity>::template GetQuantityToPowerType<N>::type>::initializeQuantity( Exponentiation::recursive( getRawQuantity( quantity ), N ) );
  } 

  //! The pow Np1 function
  template<typename Quantity>
  static inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<N+1>::type powNp1( const Quantity& quantity )
  { 
    return QuantityTraits<typename QuantityTraits<Quantity>::template GetQuantityToPowerType<N+1>::type>::initializeQuantity( Exponentiation::recursive( getRawQuantity( quantity ), N+1 ) );
  } 
};

/*! Power distribution traits struct for power 2
 * \ingroup one_d_distributions
 * \ingroup traits
 */
template<>
struct PowerDistributionTraits<2>
{
  //! The distribution type
  static const OneDDistributionType distribution_type = POWER_2_DISTRIBUTION;

  //! The N+1 root function
  template<typename CubedQuantity>
  static inline typename QuantityTraits<CubedQuantity>::template GetQuantityToPowerType<1,3>::type np1Root( const CubedQuantity& quantity )
  { return rpow<1,3>( quantity ); }

  //! The pow N function
  template<typename Quantity>
  static inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<2>::type powN( const Quantity& quantity )
  {
    return quantity*quantity;
  }

  //! The pow N+1 function
  template<typename Quantity>
  static inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<3>::type powNp1( const Quantity& quantity )
  {
    return quantity*quantity*quantity;
  }
};

/*! Power distribution traits struct for power 1
 * \ingroup one_d_distributions
 * \ingroup traits
 */
template<>
struct PowerDistributionTraits<1>
{
  //! The distribution type
  static const OneDDistributionType distribution_type = POWER_1_DISTRIBUTION;

  //! The N+1 root function
  template<typename SquaredQuantity>
  static inline typename QuantityTraits<SquaredQuantity>::template GetQuantityToPowerType<1,2>::type np1Root( const SquaredQuantity& quantity )
  { return Utility::sqrt( quantity ); }

  //! The pow N function
  template<typename Quantity>
  static inline Quantity powN( const Quantity& quantity )
  {
    return quantity;
  }

  //! The pow N+1 function
  template<typename Quantity>
  static inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<2>::type powNp1( const Quantity& quantity )
  {
    return quantity*quantity;
  }
};

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::PowerDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<unsigned N>
class TypeNameTraits<Utility::PowerDistribution<N> >
{
public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Power " << N << " Distribution";
    
    return iss.str();
  }
  static std::string concreteName( 
				const Utility::PowerDistribution<N>& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the
 * Utility::UnitAwarePowerDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<unsigned N, typename U, typename V>
class TypeNameTraits<Utility::UnitAwarePowerDistribution<N,U,V> >
{
public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Unit-Aware Power " << N << " Distribution (" 
	<< Utility::UnitTraits<U>::symbol() << ","
	<< Utility::UnitTraits<V>::symbol() << ")";

    return iss.str();
  }
      
  static std::string concreteName(
		   const Utility::UnitAwarePowerDistribution<N,U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//
 
#include "Utility_PowerDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_POWER_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_PowerDistribution.hpp
//---------------------------------------------------------------------------//
