//---------------------------------------------------------------------------//
//!
//! \file   Utility_PolynomialDistribution.hpp
//! \author Alex Robinson
//! \brief  Polynomial distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POLYNOMIAL_DISTRIBUTION_HPP
#define UTILITY_POLYNOMIAL_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

/*! Polynomial distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
class UnitAwarePolynomialDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
					public ParameterListCompatibleObject<UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit> >
{

private:

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

  // Typedef for QuantityTraits<DistNormQuantity>
  typedef QuantityTraits<DistNormQuantity> DNQT;

public:

  //! This distribution type
  typedef UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwarePolynomialDistribution();

  //! Constructor ( sum_(i=0)^(N-1) c_i*x^i : x in (a,b) )
  template<typename InputIndepQuantity>
  UnitAwarePolynomialDistribution( const Teuchos::Array<double>& coefficients,
				   const InputIndepQuantity min_indep_limit,
				   const InputIndepQuantity max_indep_limit );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwarePolynomialDistribution( const UnitAwarePolynomialDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwarePolynomialDistribution fromUnitlessDistribution( const UnitAwarePolynomialDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwarePolynomialDistribution& operator=(
			const UnitAwarePolynomialDistribution& dist_instance );

  //! Destructor
  ~UnitAwarePolynomialDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;

  //! Return a random sample from the distribution
  IndepQuantity sample() const;

  //! Return a random sample and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const;

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
  bool isEqual( const UnitAwarePolynomialDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwarePolynomialDistribution( const UnitAwarePolynomialDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

private:

  // Initialize the distribution
  void initializeDistribution( const IndepQuantity min_indep_limit,
			       const IndepQuantity max_indep_limit );

  // Test if the distribution can be used for sampling (each term must be a
  // positive function
  static bool isValidSamplingDistribution(
				  const Teuchos::Array<double>& coefficients,
				  const IndepQuantity min_indep_limit,
				  const IndepQuantity max_indep_limit );

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwarePolynomialDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type =
    POLYNOMIAL_DISTRIBUTION;

  // The polynomial coefficients (ignore units since each will be different)
  Teuchos::Array<double> d_coefficients;

  // The sampling cdf for the probability mixing technique
  Teuchos::Array<double> d_term_sampling_cdf;

  // The min and max indep limits to the powers of each term of the series + 1
  // first = a^(i+1), second = b^(i+1)
  Teuchos::Array<Pair<double,double> > d_indep_limits_to_series_powers_p1;

  // The normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The polynomial distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
  typedef UnitAwarePolynomialDistribution<void,void> PolynomialDistribution;
} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::PolynomialDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::PolynomialDistribution>
{
public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Polynomial Distribution";

    return iss.str();
  }
  static std::string concreteName(
			      const Utility::PolynomialDistribution& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the
 * Utility::UnitAwarePolynomialDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files
 */
template<typename U, typename V>
class TypeNameTraits<Utility::UnitAwarePolynomialDistribution<U,V> >
{
public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Unit-Aware Polynomial Distribution ("
	<< Utility::UnitTraits<U>::symbol() << ","
	<< Utility::UnitTraits<V>::symbol() << ")";

    return iss.str();
  }
  static std::string concreteName(
		const Utility::UnitAwarePolynomialDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "Utility_PolynomialDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_POLYNOMIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_PolynomialDistribution.hpp
//---------------------------------------------------------------------------//
