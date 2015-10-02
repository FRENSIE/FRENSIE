//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularDistribution.hpp
//! \author Alex Robinson
//! \brief  Tabular distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_DISTRIBUTION_HPP
#define UTILITY_TABULAR_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

//! The interpolated distribution class declaration
template<typename InterpolationPolicy>
class TabularDistribution : public TabularOneDDistribution,
	  public ParameterListCompatibleObject<TabularDistribution<InterpolationPolicy> >
{

<<<<<<< HEAD
=======
private:

  // The unnormalized cdf quantity
  typedef typename QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DistNormQuantity>::template GetQuantityToPowerType<-1>::type UnnormCDFQuantity;

  // The slope unit traits
  typedef UnitTraits<typename UnitTraits<DependentUnit>::template GetMultipliedUnitType<typename UnitTraits<IndependentUnit>::InverseUnit>::type> SlopeUnitTraits;

  // The slope quantity
  typedef typename SlopeUnitTraits::template GetQuantityType<double>::type SlopeQuantity;

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

>>>>>>> Working on refactoring the TabularDistribution class.
public:

  //! Default constructor
  TabularDistribution();

  //! Constructor
  TabularDistribution( const Teuchos::Array<double>& independent_values,
		               const Teuchos::Array<double>& dependent_values,
                       const bool interpret_dependent_values_as_cdf = false );

  //! Copy constructor
  TabularDistribution( 
	       const TabularDistribution<InterpolationPolicy>& dist_instance );

  //! Assignment operator
  TabularDistribution<InterpolationPolicy>& operator=( 
	       const TabularDistribution<InterpolationPolicy>& dist_instance );

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;
  
  //! Evaluate the PDF
<<<<<<< HEAD
  double evaluatePDF( const double indep_var_value ) const;
=======
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;
>>>>>>> Working on refactoring the TabularDistribution class.

  //! Evaluate the CDF
  double evaluateCDF( const double indep_var_value ) const;

  //! Return a random sample from the distribution
  double sample() const;

  //! Return a random sample and record the number of trials
<<<<<<< HEAD
  double sampleAndRecordTrials( unsigned& trials ) const;
=======
  IndepQuantity sampleAndRecordTrials( unsigned& trials ) const;
>>>>>>> Working on refactoring the TabularDistribution class.

  //! Return a random sample and bin index from the distribution
  double sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const;

  //! Return a random sample from the distribution at the given CDF value
  double sampleWithRandomNumber( const double random_number ) const;

  //! Return a random sample from the distribution in a subrange
  double sampleInSubrange( const double max_indep_var ) const;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  double sampleWithRandomNumberInSubrange( const double random_number,
					   const double max_indep_var ) const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;
  
  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Test if the distribution is continuous
  bool isContinuous() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const TabularDistribution<InterpolationPolicy>& other ) const;

private:

  // Initialize the distribution
  void initializeDistribution(const Teuchos::Array<double>& independent_values,
<<<<<<< HEAD
			      const Teuchos::Array<double>& dependent_values );
=======
			      const Teuchos::Array<double>& dependent_values,
			      const bool interpret_dependent_values_as_cdf );

  // Initialize the distribution from a cdf
  template<typename InputIndepQuantity>
  void initializeDistributionFromCDF(
		  const Teuchos::Array<InputIndepQuantity>& independent_values,
		  const Teuchos::Array<double>& cdf_values );

  // Initialize the distribution
  template<typename InputIndepQuantity, typename InputDepQuantity>
  void initializeDistribution( 
		  const Teuchos::Array<InputIndepQuantity>& independent_values,
		  const Teuchos::Array<InputDepQuantity>& dependent_values );

  // Reconstruct original distribution
  void reconstructOriginalDistribution(
			 Teuchos::Array<IndepQuantity>& independent_values,
			 Teuchos::Array<DepQuantity>& dependent_values ) const;

  // Reconstruct original distribution w/o units
  void reconstructOriginalUnitlessDistribution(
			      Teuchos::Array<double>& independent_values,
			      Teuchos::Array<double>& dependent_values ) const;

  // Convert the unitless values to the correct units
  template<typename Quantity>
  static void convertUnitlessValues( 
		                 const Teuchos::Array<double>& unitless_values,
				 Teuchos::Array<Quantity>& quantitites );
>>>>>>> Working on refactoring the TabularDistribution class.

  // Return a random sample using the random number and record the bin index
  double sampleImplementation( double random_number,
			       unsigned& sampled_bin_index ) const;

  // The distribution type
  static const OneDDistributionType distribution_type = TABULAR_DISTRIBUTION;

  // The distribution (first = indep_var, second = cdf, third = pdf, 
<<<<<<< HEAD
  // fourth = slope)
  typedef Teuchos::Array<Quad<double,double,double,double> > DistributionArray;
=======
  // fourth = pdf slope): both the pdf and cdf are left unnormalized to
  // prevent altering the grid with log interpolation
  typedef Teuchos::Array<Quad<IndepQuantity,UnnormCDFQuantity,DepQuantity,SlopeQuantity> > DistributionArray;
>>>>>>> Working on refactoring the TabularDistribution class.
  DistributionArray d_distribution;

  // The normalization constant
  double d_norm_constant;
};

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::TabularDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename InterpolationPolicy>
class TypeNameTraits<Utility::TabularDistribution<InterpolationPolicy> >
{
public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Tabular " << InterpolationPolicy::name() << " Distribution";
    
    return iss.str();
  }
  static std::string concreteName( 
	    const Utility::TabularDistribution<InterpolationPolicy>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template inludes.
//---------------------------------------------------------------------------//

#include "Utility_TabularDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TABULAR_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_TabularDistribution.hpp
//---------------------------------------------------------------------------//
