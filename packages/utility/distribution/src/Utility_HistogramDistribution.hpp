//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramDistribution.hpp
//! \author Alex Robinson
//! \brief  Histogram distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_DISTRIBUTION_HPP
#define UTILITY_HISTOGRAM_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

/*! The unit-aware histogram distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
class UnitAwareHistogramDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>,
				       public ParameterListCompatibleObject<UnitAwareHistogramDistribution<IndependentUnit,DependentUnit> >
{

private:

  // The unnormalized cdf quantity
  typedef typename QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DistNormQuantity>::template GetQuantityToPowerType<-1>::type UnnormCDFQuantity;

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
  typedef UnitAwareHistogramDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwareHistogramDistribution();

  //! Basic constructor (potentially dangerous)
  UnitAwareHistogramDistribution( const Teuchos::Array<double>& bin_boundaries,
				  const Teuchos::Array<double>& bin_values,
				  const bool interpret_dependent_values_as_cdf = false );

  //! CDF constructor
  template<typename InputIndepQuantity>
  UnitAwareHistogramDistribution(
		      const Teuchos::Array<InputIndepQuantity>& bin_boundaries,
		      const Teuchos::Array<double>& cdf_values );

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareHistogramDistribution(
		      const Teuchos::Array<InputIndepQuantity>& bin_boundaries,
		      const Teuchos::Array<InputDepQuantity>& bin_values );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareHistogramDistribution( const UnitAwareHistogramDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareHistogramDistribution fromUnitlessDistribution( const UnitAwareHistogramDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareHistogramDistribution& operator=(
			 const UnitAwareHistogramDistribution& dist_instance );

  //! Destructor
  ~UnitAwareHistogramDistribution()
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

  //! Return a random sample and bin index from the distribution
  IndepQuantity sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const;

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const;

  //! Return a random sample from the corresponding CDF in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const;

  //! Return a sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
				     const double random_number,
				     const IndepQuantity max_indep_var ) const;

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
  bool isEqual( const UnitAwareHistogramDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareHistogramDistribution( const UnitAwareHistogramDistribution<void,void>& unitless_dist_instance, int );

private:

  // Initialize the distribution
  void initializeDistribution( const Teuchos::Array<double>& bin_boundaries,
			       const Teuchos::Array<double>& bin_values,
			       const bool interpret_dependent_values_as_cdf );

  // Initialize the distribution from a cdf
  template<typename InputIndepQuantity>
  void initializeDistributionFromCDF(
		  const Teuchos::Array<InputIndepQuantity>& bin_boundaries,
		  const Teuchos::Array<double>& cdf_values );

  // Initialize the distribution
  template<typename InputIndepQuantity, typename InputDepQuantity>
  void initializeDistribution(
		  const Teuchos::Array<InputIndepQuantity>& bin_boundaries,
		  const Teuchos::Array<InputDepQuantity>& bin_values );

  // Reconstruct original distribution
  void reconstructOriginalDistribution(
			 Teuchos::Array<IndepQuantity>& bin_boundaries,
			 Teuchos::Array<DepQuantity>& bin_values ) const;

  // Reconstruct original distribution w/o units
  void reconstructOriginalUnitlessDistribution(
			      Teuchos::Array<double>& bin_boundaries,
			      Teuchos::Array<double>& bin_values ) const;

  // Convert the unitless values to the correct units
  template<typename Quantity>
  static void convertUnitlessValues(
		                 const Teuchos::Array<double>& unitless_values,
				 Teuchos::Array<Quantity>& quantities );

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
				      unsigned& sampled_bin_index ) const;

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareHistogramDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = HISTOGRAM_DISTRIBUTION;

  // The distribution (first = bin_min, second = bin_PDF, third = bin_CDF)
  // Note: The bin_CDF value is the value of the CDF at the lower bin boundary
  typedef Teuchos::Array<Trip<IndepQuantity,DepQuantity,UnnormCDFQuantity> > DistributionArray;
  DistributionArray d_distribution;

  // The normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The histogram distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareHistogramDistribution<void,void> HistogramDistribution;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::HistogramDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::HistogramDistribution>
{
public:
  static std::string name()
  {
    return "Histogram Distribution";
  }
  static std::string concreteName(
			       const Utility::HistogramDistribution& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the
 * Utility::UnitAwareHistogramDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files
 */
template<typename U, typename V>
class TypeNameTraits<Utility::UnitAwareHistogramDistribution<U,V> >
{
public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Unit-Aware Histogram Distribution ("
	<< Utility::UnitTraits<U>::symbol() << ","
	<< Utility::UnitTraits<V>::symbol() << ")";

    return iss.str();
  }
  static std::string concreteName(
		 const Utility::UnitAwareHistogramDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Utility_HistogramDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HISTOGRAM_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramDistribution.hpp
//---------------------------------------------------------------------------//
