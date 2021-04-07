//---------------------------------------------------------------------------//
//!
//! \file   Utility_WattDistribution.hpp
//! \author Aaron Tumulak
//! \brief  Watt distribution class declaration. Modified by Alex Robinson
//!         to accommodate units.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_WATT_DISTRIBUTION_HPP
#define UTILITY_WATT_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/units/physical_dimensions/energy.hpp>

// FRENSIE Includes
#include "Utility_UnivariateDistribution.hpp"

namespace Utility{

/*! Watt distribution class
 * \ingroup univariate_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareWattDistribution : public UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>
{
  // Only allow construction when the independent unit corresponds to energy
  RESTRICT_UNIT_TO_BOOST_DIMENSION( IndependentUnit, energy_dimension );

  // Typedef for base type
  typedef UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit> BaseType;

  // The distribution multiplier quantity type
  typedef typename BaseType::DepQuantity DistMultiplierQuantity;

  // The distribution normalization quantity type
  typedef typename BaseType::DistNormQuantity DistNormQuantity;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename BaseType::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename BaseType::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename BaseType::DepQuantity> DQT;

  // Typedef for QuantityTraits<DistMultiplierQuantity>
  typedef QuantityTraits<DistMultiplierQuantity> DMQT;

public:

  //! The distribution type
  typedef UnitAwareWattDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Constructor
  template<typename InputIndepQuantityA = IndepQuantity,
	   typename InputIndepQuantityB = IndepQuantity,
	   typename InputInverseIndepQuantity = InverseIndepQuantity,
	   typename InputIndepQuantityC = IndepQuantity>
  UnitAwareWattDistribution(
                  const InputIndepQuantityA incident_energy =
                  ThisType::getDefaultIncidentEnergy<InputIndepQuantityA>(),
                  const InputIndepQuantityB a_parameter =
                  ThisType::getDefaultAParameter<InputIndepQuantityB>(),
                  const InputInverseIndepQuantity b_parameter =
                  ThisType::getDefaultBParameter<InputInverseIndepQuantity>(),
                  const InputIndepQuantityC restriction_energy =
                  ThisType::getDefaultRestrictionEnergy<InputIndepQuantityC>(),
                  const double constant_multiplier =
                  ThisType::getDefaultConstantMultiplier() );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareWattDistribution( const UnitAwareWattDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareWattDistribution fromUnitlessDistribution( const UnitAwareWattDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareWattDistribution& operator=( const UnitAwareWattDistribution& dist_instance );

  //! Destructor
  ~UnitAwareWattDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const override;

  //! Return a sample from the distribution
  IndepQuantity sample() const override;

  //! Return a sample from the distribution
  static IndepQuantity sample( const IndepQuantity incident_energy,
			       const IndepQuantity a_parameter,
			       const InverseIndepQuantity b_parameter,
			       const IndepQuantity restriction_energy );

  //! Return a random sample from the distribution and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const override;

  //! Return a random sample from the corresponding CDF and record the number of trials
  static IndepQuantity sampleAndRecordTrials(
                                        const IndepQuantity incident_energy,
                                        const IndepQuantity a_parameter,
                                        const InverseIndepQuantity b_parameter,
                                        const IndepQuantity restriction_energy,
                                        DistributionTraits::Counter& trials );

  //! Test if the distribution is continuous
  bool isContinuous() const override;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const override;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const override;

  //! Return the distribution type
  UnivariateDistributionType getDistributionType() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;
  
  //! Equality comparison operator
  bool operator==( const UnitAwareWattDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareWattDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareWattDistribution( const UnitAwareWattDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const override;

  //! Get the default incident energy
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultIncidentEnergy()
  { return QuantityTraits<InputIndepQuantity>::one(); }

  //! Get the default a parameter
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultAParameter()
  { return QuantityTraits<InputIndepQuantity>::one(); }

  //! Get the default b parameter
  template<typename InputInverseIndepQuantity>
  static InputInverseIndepQuantity getDefaultBParameter()
  { return QuantityTraits<InputInverseIndepQuantity>::one(); }

  //! Get the default restriction energy
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultRestrictionEnergy()
  { return QuantityTraits<InputIndepQuantity>::zero(); }

  //! Get the default constant multiplier
  static double getDefaultConstantMultiplier()
  { return 1.0; }

private:

  // Calculate the normalization constant of the distribution
  void calculateNormalizationConstant();

  // Verify that the shape parameters are valid
  static void verifyValidShapeParameters( IndepQuantity& incident_energy,
                                          IndepQuantity& a_parameter,
                                          InverseIndepQuantity& b_parameter,
                                          IndepQuantity& restriction_energy,
                                          DistMultiplierQuantity& multiplier );

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
  friend class UnitAwareWattDistribution;

  // The distribution type
  static const UnivariateDistributionType distribution_type = WATT_DISTRIBUTION;

  // The incident neutron energy of the distribution
  IndepQuantity d_incident_energy;

  // The a_parameter of the distribution
  IndepQuantity d_a_parameter;

  // The b_parameter of the distribution
  InverseIndepQuantity d_b_parameter;

  // The restriction energy of the distribution
  IndepQuantity d_restriction_energy;

  // The distribution multiplier
  DistMultiplierQuantity d_multiplier;

  // The distribution normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The Watt distribution (unit-agnostic)
 * \ingroup univariate_distributions
 */
typedef UnitAwareWattDistribution<void,void> WattDistribution;

} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION2_VERSION( UnitAwareWattDistribution, 0 );
BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_STANDARD_KEY( WattDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_WattDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_WATT_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_WattDistribution.hpp
//---------------------------------------------------------------------------//
