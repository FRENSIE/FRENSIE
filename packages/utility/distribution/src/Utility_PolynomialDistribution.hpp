//---------------------------------------------------------------------------//
//!
//! \file   Utility_PolynomialDistribution.hpp
//! \author Alex Robinson
//! \brief  Polynomial distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POLYNOMIAL_DISTRIBUTION_HPP
#define UTILITY_POLYNOMIAL_DISTRIBUTION_HPP

// Std Lib Includes
#include <unordered_map>
#include <limits>

// Boost Includes
#include <boost/scoped_ptr.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

/*! Polynomial distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
class UnitAwarePolynomialDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
					public ParameterListCompatibleObject<UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit> >
{

private:

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity> DQT;

public:

  //! This distribution type
  typedef UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! The distribution normalization quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DistNormQuantity DistNormQuantity;

  //! Default constructor
  UnitAwarePolynomialDistribution();

  //! Constructor ( sum_(i=0)^(N-1) c_i*x^i : x in (a,b) )
  template<typename InputIndepQuantity>
  UnitAwarePolynomialDistribution(const Teuchos::Array<double>& coefficients,
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

  //! Evaluate the CDF
  double evaluateCDF( const IndepQuantity indep_var_value ) const;

  //! Return a random sample from the distribution
  IndepQuantity sample() const;

  //! Return a random sample and record the number of trials
  IndepQuantity sampleAndRecordTrials( unsigned& trials ) const;

  //! Return the normalization constant
  DistNormQuantity getNormConstant() const;

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

private:

  // Test if the distribution can be used for sampling (each term must have
  // the same sign)
  static bool isValidSamplingDistribution(
				    const Teuchos::Array<double>& coefficients,
				    const double min_indep_limit,
				    const double max_indep_limit );
				  

  // All possible instantiations are friends
  template<typename FriendUnit, typename FriendDepUnit>
  friend class UnitAwarePolynomialDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = 
    POLYNOMIAL_DISTRIBUTION;

  // The min independent variable limit
  IndepQuantity d_min_indep_limit;

  // The max independent variable limit
  IndepQuantity d_max_indep_limit;

  // The normalization constant
  DistNormQuantity d_norm_constant;

  // The polynomial terms
  Teuchos::Array<Pair<double,boost::scoped_ptr<UnitAwareOneDDistribution<IndependentUnit,DependentUnit> > > d_terms;
};

/*! The polynomial distribution (unit-agnostic)
 * \ingroup one_d_distribution
 */
typedef UnitAwarePolynomialDistribution<void,void> PolynomialDistribution;

/*! Polynomial term construction helper  
 * \ingroup one_d_distributions
 */
template<unsigned N, typename IndependentUnit, typename DependentUnit>
struct PolynomialTermConstructionHelper
{
  //! Convert the polynomial terms
  template<typename InputIndepUnit, typename InputDepUnit>
  static void convertTerms( 
	 const Teuchos::Array<Pair<double,boost::scoped_ptr<UnitAwareOneDDistribution<InputIndependentUnit,InputDependentUnit> > >& old_terms,
	 typename UnitAwareOneDDistribution<IndependentUnit,DependnetUnit>::DistNormQuantity& norm_constant,
	 Teuchos::Array<Pair<double,boost::scoped_ptr<UnitAwareOneDDistribution<IndependentUnit,DependentUnit> > >& new_terms )
  {
    if( old_terms.size() > N )
    {
      new_terms[N].first = old_terms[N].first;
      
      new_terms[N].second.reset( new UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>( *dynamic_cast<const UnitAwarePowerDistribution<N,InputIndepUnit,InputDepUnit>*>( old_terms[N] ) ) );
      
      norm_constant += new_terms[N].second->getNormConstant();

      // Construct the next term
      PolynomialTermConstructionHelper<N+1,IndependentUnit,DependentUnit>::convertTerms( old_terms, norm_constant, new_terms );
    }
  }

  //! Convert the polynomial terms
  static void convertTerms( 
	 const Teuchos::Array<Pair<double,boost::scoped_ptr<UnitAwareOneDDistribution<void,void> > >& old_terms,
	 typename UnitAwareOneDDistribution<IndependentUnit,DependnetUnit>::DistNormQuantity& norm_constant,
	 Teuchos::Array<Pair<double,boost::scoped_ptr<UnitAwareOneDDistribution<IndependentUnit,DependentUnit> > >& new_terms )
  {
    if( old_terms.size() > N )
    {
      new_terms[N].first = old_terms[N].first;
      
      new_terms[N].second.reset( new UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>() );
      
      *new_terms[N].second = UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::fromUnitlessDistribution( *dynamic_cast<const UnitAwarePowerDistribution<N,void,void>*>( old_terms[N] ) ) );
      
      norm_constant += new_terms[N].second->getNormConstant();

      // Construct the next term
      PolynomialTermConstructionHelper<N+1,IndependentUnit,DependentUnit>::convertTerms( old_terms, norm_constant, new_terms );
    }
  }
			   
  //! Construct all terms of the polynomial starting with the Nth
  template<typename InputIndepQuantity>
  static void createTerms( 
	   const Teuchos::Array<double>& coefficients,
	   const InputIndepQuantity min_indep_limit,
	   const InputIndepQuantity max_indep_limit,
	   typename UnitAwareOneDDistribution<IndependentUnit,DependnetUnit>::DistNormQuantity& norm_constant,
				Teuchos::Array<Pair<double,boost::scoped_ptr<UnitAwareOneDDistribution<IndependentUnit,DependentUnit> > >& polynomial_terms )
  {
    if( coefficients.size() > N )
    {
      // Create the Nth term
      if( coefficients[N] != 0.0 )
      {
	polynomial_terms[N].second.reset(
	       new UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>(
							   coefficients[N], 
							   min_indep_limit, 
							   max_indep_limit ) );

	// Store the unormalized discrete cdf value
	polynomial_terms[N].first = 
	  1.0/getRawQuantity( polynomial_terms[N].second->getNormConstant() );

	// Calculate the normalization constant
	norm_constant += polynomial_terms[N].second->getNormConstant();
      }
      else
	polynomial_terms[N].first = 0.0;

      // Add the previous discrete cdf value to the current partial cdf value
      if( N > 0u )
	polynomial_terms[N].first += polynomial_terms[N-1].first;
      
      // Construct the next term
      PolynomialTermConstructionHelper<N+1,IndependentUnit,DependentUnit>::createTerms( 
							    coefficients,
							    min_indep_limit,
							    max_indep_limit,
							    norm_constant,
							    polynomial_terms );
    }
    // Normalize the discrete term CDF
    else
    {
      for( unsigned i = 0; i < N; ++i )
	polynomial_terms[i].first /= polynomial_terms.back().first;
    }
  }
};

/*! Polynomial construction helper  
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
struct PolynomialConstructionHelper
{
  //! Convert the polynomial term by term
  template<typename InputIndepUnit, typename InputDepUnit>
  static void convertPolynomial( 
	 const Teuchos::Array<Pair<double,boost::scoped_ptr<UnitAwareOneDDistribution<InputIndependentUnit,InputDependentUnit> > >& old_terms,
	 typename UnitAwareOneDDistribution<IndependentUnit,DependnetUnit>::DistNormQuantity& norm_constant,
	 Teuchos::Array<Pair<double,boost::scoped_ptr<UnitAwareOneDDistribution<IndependentUnit,DependentUnit> > >& new_terms )
  {
    setQuantity( norm_constant, 0.0 );
    
    new_terms.resize( old_terms.size() );
    
    PolynomialTermConstructionHelper<0u,IndependentUnit,DependentUnit>::convertTerms( old_terms, norm_constant, new_terms );
  }

  //! Construct polynomial term by term 
  template<typename InputIndepQuantity>
  static void createPolynomial( 
	 const Teuchos::Array<double>& coefficients,
	 const InputIndepQuantity min_indep_limit,
	 const InputIndepQuantity max_indep_limit,
	 typename UnitAwareOneDDistribution<IndependentUnit,DependnetUnit>::DistNormQuantity& norm_constant,
	 Teuchos::Array<Utility::Pair<double,boost::scoped_ptr<UnitAwareOneDDistribution<IndependentUnit,DependentUnit> > >& polynomial_terms )
  {
    TEST_FOR_EXCEPTION( coefficients.size() > 
			std::numeric_limits<unsigned>::max() + 1ull,
			std::logic_error,
			"Error: the polynomial has more terms than are "
			"currently supported (" 
			<< std::numeric_limits<unsigned>::max() + 1ull );

    setQuantity( norm_constant, 0.0 );

    polynomial_terms.resize( coefficients.size() );

    PolynomialTermConstructionHelper<0u,IndependentUnit,DependentUnit>::createTerms( 
							    coefficients,
							    min_indep_limit,
							    max_indep_limit,
							    norm_constant,
							    polynomial_terms );
  }
};

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
 * xml files.
 */
template<typename U, typename V>
class TypeNameTraits<Utility::PolynomialDistribution<U,V> >
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
			 const Utility::PolynomialDistribution<U,V>& instance )
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
