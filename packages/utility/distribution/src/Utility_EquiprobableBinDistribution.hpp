//---------------------------------------------------------------------------//
//!
//! \file   Utility_EquiprobableBinDistribution.hpp
//! \author Alex Robinson
//! \brief  Equiprobable bin distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EQUIPROBABLE_BIN_DISTRIBUTION_HPP
#define UTILITY_EQUIPROBABLE_BIN_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_Vector.hpp"

namespace Utility{

/*! The unit-aware equiprobable bin distribution class
 * \ingroup univariate_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareEquiprobableBinDistribution : public UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit>
{
  // Typedef for base type
  typedef UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit> BaseType;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename BaseType::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename BaseType::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename BaseType::DepQuantity> DQT;

public:

  //! This distribution type
  typedef UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Basic constructor (potentially dangerous)
  explicit UnitAwareEquiprobableBinDistribution(
                                 const std::vector<double>& bin_boundaries =
                                 ThisType::getDefaultBinBoundaries<double>() );

  //! Basic view constructor (potentially dangerous)
  explicit UnitAwareEquiprobableBinDistribution(
                      const Utility::ArrayView<const double>& bin_boundaries );

  //! Constructor
  template<typename InputIndepQuantity>
  explicit UnitAwareEquiprobableBinDistribution( const std::vector<InputIndepQuantity>& bin_boundaries );

  //! View constructor
  template<typename InputIndepQuantity>
  explicit UnitAwareEquiprobableBinDistribution( const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareEquiprobableBinDistribution(
      const UnitAwareEquiprobableBinDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareEquiprobableBinDistribution fromUnitlessDistribution( const UnitAwareEquiprobableBinDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareEquiprobableBinDistribution& operator=(
		   const UnitAwareEquiprobableBinDistribution& dist_instance );

  //! Destructor
  ~UnitAwareEquiprobableBinDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the CDF
  double evaluateCDF( const IndepQuantity indep_var_value ) const override;

  //! Return a random sample from the distribution
  IndepQuantity sample() const override;

  //! Return a random sample and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const override;

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const override;

  //! Return a random sample and sampled index from the corresponding CDF
  IndepQuantity sampleAndRecordBinIndex( size_t& sampled_bin_index ) const override;

  //! Return a random sample from the corresponding CDF in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const override;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
                            const double random_number,
			    const IndepQuantity max_indep_var ) const override;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const override;

  //! Return a random sample from the distribution and the sampled index
  IndepQuantity getLowerBoundOfIndepVar() const override;

  //! Return the distribution type
  UnivariateDistributionType getDistributionType() const override;

  //! Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Equality comparison operator
  bool operator==( const UnitAwareEquiprobableBinDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareEquiprobableBinDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareEquiprobableBinDistribution( const UnitAwareEquiprobableBinDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const override;

  //! Get the default bin boundaries
  template<typename InputIndepQuantity>
  static std::vector<InputIndepQuantity> getDefaultBinBoundaries()
  { return std::vector<InputIndepQuantity>({Utility::QuantityTraits<InputIndepQuantity>::zero(),Utility::QuantityTraits<InputIndepQuantity>::one()}); }

private:

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
				      size_t& sampled_bin_index ) const;

  // Initialize the distribution
  void initializeDistribution( const Utility::ArrayView<const double>& bin_boundaries );

  // Initialize the distribution
  template<typename InputIndepQuantity>
  void initializeDistribution(
          const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries );

  // Verify that the bin boundaries are valid
  template<typename InputIndepQuantity>
  static void verifyValidBinBoundaries(
          const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries );

  // Save the distribution to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the distribution from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareEquiprobableBinDistribution;

  // The disribution type
  static const UnivariateDistributionType distribution_type =
    EQUIPROBABLE_BIN_DISTRIBUTION;

    // The distribution
  std::vector<IndepQuantity> d_bin_boundaries;
};

/*! The equiprobable bin distribution (unit-agnostic)
 * \ingroup univariate_distributions
 */
typedef UnitAwareEquiprobableBinDistribution<void,void> EquiprobableBinDistribution;

} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION2_VERSION( UnitAwareEquiprobableBinDistribution, 0 );
BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_STANDARD_KEY( EquiprobableBinDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_EquiprobableBinDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_EQUIPROBABLE_BIN_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_EquiprobableBinDistribution.hpp
//---------------------------------------------------------------------------//
