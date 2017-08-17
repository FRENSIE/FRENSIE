//---------------------------------------------------------------------------//
//!
//! \file   Utility_CutoffElasticDistribution.hpp
//! \author Luke Kersting
//! \brief  Cutoff elastic distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_CUTOFF_ELASTIC_DISTRIBUTION_HPP
#define UTILITY_CUTOFF_ELASTIC_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

/*! The cutoff elastic distribution class declaration
 * \ingroup one_d_distributions
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
class UnitAwareCutoffElasticDistribution : public UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>
{

  // Only allow construction when the independent unit dimensionless
  RESTRICT_UNIT_TO_BOOST_DIMENSION( IndependentUnit, dimensionless_type );

private:

  // The Parent type (TabularDistribution)
  typedef UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit> ParentType;

public:

  //! This distribution type
  typedef UnitAwareCutoffElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename ParentType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename ParentType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename ParentType::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwareCutoffElasticDistribution();

  //! Basic constructor (potentially dangerous)
  UnitAwareCutoffElasticDistribution(
                    const Teuchos::Array<double>& independent_values,
                    const Teuchos::Array<double>& dependent_values )
  : ParentType( independent_values, dependent_values  )
  { /* ... */ }

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareCutoffElasticDistribution(
                    const Teuchos::Array<InputIndepQuantity>& independent_values,
                    const Teuchos::Array<InputDepQuantity>& dependent_values )
  : ParentType( independent_values, dependent_values  )
  { /* ... */ }

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareCutoffElasticDistribution( const UnitAwareCutoffElasticDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>& dist_instance )
  : ParentType( dist_instance )
  { /* ... */ }

  //! Destructor
  ~UnitAwareCutoffElasticDistribution()
  { /* ... */ }

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

protected:

  //! Test if the independent variable is compatible with Lin processing
  bool isIndepVarCompatibleWithProcessingType(
                                        const LinIndepVarProcessingTag ) const;
  
  //! Test if the independent variable is compatible with Log processing
  bool isIndepVarCompatibleWithProcessingType(
                                        const LogIndepVarProcessingTag ) const;

  //! Test if the dependent variable is compatible with Lin processing
  bool isDepVarCompatibleWithProcessingType(
                                          const LinDepVarProcessingTag ) const;

  //! Test if the dependent variable is compatible with Log processing
  bool isDepVarCompatibleWithProcessingType(
                                          const LogDepVarProcessingTag ) const;

private:

  // All possible instantiations are friends
  template<typename FriendInterpolationPolicy,
           typename FriendIndepUnit,
           typename FriendDepUnit>
  friend class UnitAwareCutoffElasticDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = CUTOFF_ELASTIC_DISTRIBUTION;
};

/*! The cutoff elastic distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
template<typename InterpolationPolicy> using CutoffElasticDistribution =
  UnitAwareCutoffElasticDistribution<InterpolationPolicy,void,void>;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::CutoffElasticDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename InterpolationPolicy>
class TypeNameTraits<Utility::CutoffElasticDistribution<InterpolationPolicy> >
{
public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Cutoff Elastic " << InterpolationPolicy::name() << " Distribution";

    return iss.str();
  }
  static std::string concreteName(
            const Utility::CutoffElasticDistribution<InterpolationPolicy>& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the
 * Utility::UnitAwareCutoffElasticDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files
 */
template<typename InterpolationPolicy, typename U, typename V>
class TypeNameTraits<Utility::UnitAwareCutoffElasticDistribution<InterpolationPolicy,U,V> >
{
  public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Unit-Aware Cutoff Elastic " << InterpolationPolicy::name()
        << " Distribution ("
        << Utility::UnitTraits<U>::symbol() << ","
        << Utility::UnitTraits<V>::symbol() << ")";

    return iss.str();
  }
  static std::string concreteName( const Utility::UnitAwareCutoffElasticDistribution<InterpolationPolicy,U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template inludes.
//---------------------------------------------------------------------------//

#include "Utility_CutoffElasticDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_CUTOFF_ELASTIC_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_CutoffElasticDistribution.hpp
//---------------------------------------------------------------------------//
