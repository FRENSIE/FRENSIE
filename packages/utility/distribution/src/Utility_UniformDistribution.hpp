//---------------------------------------------------------------------------//
//!
//! \file   Utility_UniformDistribution.hpp
//! \author Alex Robinson
//! \brief  Uniform distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIFORM_DISTRIBUTION_HPP
#define UTILITY_UNIFORM_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

/*! The unit-aware uniform distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareUniformDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>
                                     
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
  typedef UnitAwareUniformDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwareUniformDistribution();

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareUniformDistribution(const InputIndepQuantity& min_independent_value,
			       const InputIndepQuantity& max_independent_value,
			       const InputDepQuantity& dependent_value );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit, typename Dummy=void>
  UnitAwareUniformDistribution( const UnitAwareUniformDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareUniformDistribution fromUnitlessDistribution( const UnitAwareUniformDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareUniformDistribution& operator=( const UnitAwareUniformDistribution& dist_instance );

  //! Destructor
  ~UnitAwareUniformDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the CDF
  double evaluateCDF( const IndepQuantity indep_var_value ) const override;

  //! Return a random sample from the distribution
  IndepQuantity sample() const override;

  //! Return a random sample from the distribution
  static IndepQuantity sample( const IndepQuantity min_independent_value,
			       const IndepQuantity max_independent_value );

  //! Return a random sample from the corresponding CDF and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const override;

  //! Return a random sample from the distribution and record the number of trials
  static IndepQuantity sampleAndRecordTrials(
			        const IndepQuantity min_independent_value,
			        const IndepQuantity max_independent_value,
				DistributionTraits::Counter& trials );

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const override;

  //! Return a random sample from the distribution at the given CDF value
  static IndepQuantity sampleWithRandomNumber(
				const IndepQuantity min_independent_value,
				const IndepQuantity max_independent_value,
				const double random_number );

  //! Return a random sample and sampled index from the corresponding CDF
  IndepQuantity sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const override;

  //! Return a random sample from the corresponding CDF in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const override;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
                            const double random_number,
			    const IndepQuantity max_indep_var ) const override;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const override;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const override;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const override;

  // Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is, const std::string& delims ) override;

  //! Method for initializing the object from an input stream
  using IStreamableObject::fromStream;

  //! Method for placing an object in the desired property tree node
  void toNode( const std::string& node_key,
               Utility::PropertyTree& ptree,
               const bool inline_data ) const override;

  //! Method for placing an object in the desired property tree node
  using PropertyTreeCompatibleObject::toNode;

  //! Method for initializing the object from a property tree node
  void fromNode( const Utility::PropertyTree& node,
                 std::vector<std::string>& unused_children ) override;

  //! Method for initializing the object from a property tree node
  using PropertyTreeCompatibleObject::fromNode;

  //! Equality comparison operator
  bool operator==( const UnitAwareUniformDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareUniformDistribution& other ) const;
  
protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareUniformDistribution( const UnitAwareUniformDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

private:

  // Verify the distribution type
  static void verifyDistributionType( const Utility::Variant& type_data );

  // Set the min indep value
  void setMinIndependentValue( const Utility::Variant& min_indep_data );

  // Set the max indep value
  void setMaxIndependentValue( const Utility::Variant& max_indep_data );

  // Verify that the independent values are valid
  void verifyValidIndependentValues();

  // Set the dependent indep value
  void setDependentValue( const Utility::Variant& dep_data );

  // Calculate the PDF value
  void calculatePDFValue();

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareUniformDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = UNIFORM_DISTRIBUTION;

  // The min independent value
  IndepQuantity d_min_independent_value;

  // The max independent value
  IndepQuantity d_max_independent_value;

  // The uniform distribution dependent value
  DepQuantity d_dependent_value;

  // The uniform distribution PDF value
  InverseIndepQuantity d_pdf_value;
};

/*! The uniform distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareUniformDistribution<void,void> UniformDistribution;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::UniformDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::UniformDistribution>
{
public:
  static std::string name()
  {
    return "Uniform Distribution";
  }
  static std::string concreteName(
			     const Utility::UniformDistribution& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the
 * Utility::UnitAwareUniformDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename U, typename V>
class TypeNameTraits<Utility::UnitAwareUniformDistribution<U,V> >
{
public:
  static std::string name()
  {
    return "Unit-Aware Uniform Distribution (" +
      Utility::UnitTraits<U>::symbol() + "," +
      Utility::UnitTraits<V>::symbol() + ")";
  }
  static std::string concreteName(
		   const Utility::UnitAwareUniformDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_UniformDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_UNIFORM_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_UniformDistribution.hpp
//---------------------------------------------------------------------------//
