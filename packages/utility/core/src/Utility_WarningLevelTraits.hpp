//---------------------------------------------------------------------------//
//!
//! \file   Utility_WarningLevelTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Warning level traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_WARNING_LEVEL_TRAITS_HPP
#define UTILITY_WARNING_LEVEL_TRAITS_HPP

// Boost Includes
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/has_key.hpp>

// FRENSIE Includes
#include "Utility_WarningLevelTraitsDecl.hpp"

namespace Utility{

/*! Specialization of the WarningLevelTraits class for UTILITY::NO_WARNINGS
 * \ingroup warning_level_traits
 */
template<>
struct WarningLevelTraits<NO_WARNINGS>
{
  typedef boost::mpl::set_c<WarningType> SupportedWarningTypes;
};

/*! \brief Specialization of the WarningLevelTraits class for 
 * Utility::CRITICAL_WARNINGS_ONLY
 * \ingroup warning_level_traits
 */
template<>
struct WarningLevelTraits<CRITICAL_WARNINGS_ONLY>
{
  typedef boost::mpl::set_c<WarningType,CRITICAL_WARNING> SupportedWarningTypes;
};

/*! \brief Specialization of the WarningLevelTraits class for
 * Utility::HIGH_PRIORITY_OR_HIGHER_WARNINGS
 * \ingroup warning_level_traits
 */
template<>
struct WarningLevelTraits<HIGH_PRIORITY_OR_HIGHER_WARNINGS>
{
  typedef boost::mpl::set_c<WarningType,CRITICAL_WARNING,HIGH_PRIORITY_WARNING> SupportedWarningTypes;
};

/*! \brief Specialization of the WarningLevelTraits class for
 * Utility::HIGH_PRIORITY_WARNINGS_ONLY
 * \ingroup warning_level_traits
 */
template<>
struct WarningLevelTraits<HIGH_PRIORITY_WARNINGS_ONLY>
{
  typedef boost::mpl::set_c<WarningType,HIGH_PRIORITY_WARNING> SupportedWarningTypes;
};

/*! \brief Specialization of the WarningLevelTraits class for
 * Utility::MEDIUM_PRIORITY_OR_HIGHER_WARNINGS
 * \ingroup warning_level_traits
 */
template<>
struct WarningLevelTraits<MEDIUM_PRIORITY_OR_HIGHER_WARNINGS>
{
  typedef boost::mpl::set_c<WarningType,CRITICAL_WARNING,HIGH_PRIORITY_WARNING,MEDIUM_PRIORITY_WARNING> SupportedWarningTypes;
};

/*! \brief Specialization of the WarningLevelTraits class for
 * Utility::MEDIUM_PRIORITY_WARNINGS_ONLY
 * \ingroup warning_level_traits
 */
template<>
struct WarningLevelTraits<MEDIUM_PRIORITY_WARNINGS_ONLY>
{
  typedef boost::mpl::set_c<WarningType,MEDIUM_PRIORITY_WARNING> SupportedWarningTypes;
};

/*! \brief Specialization of the WarningLevelTraits class for
 * Utility::LOW_PRIORITY_OR_HIGHER_WARNINGS
 * \ingroup warning_level_traits
 */
template<>
struct WarningLevelTraits<LOW_PRIORITY_OR_HIGHER_WARNINGS>
{
  typedef boost::mpl::set_c<WarningType,CRITICAL_WARNING,HIGH_PRIORITY_WARNING,MEDIUM_PRIORITY_WARNING,LOW_PRIORITY_WARNING> SupportedWarningTypes;
};

/*! \brief Specialization of the WarningLevelTraits class for
 * Utility::LOW_PRIORITY_WARNINGS_ONLY
 * \ingroup warning_level_traits
 */
template<>
struct WarningLevelTraits<LOW_PRIORITY_WARNINGS_ONLY>
{
  typedef boost::mpl::set_c<WarningType,LOW_PRIORITY_WARNING> SupportedWarningTypes;
};

/*! \brief Specialization of the WarningLevelTraits class for
 * Utility::PEDANDIC_OR_HIGHER_WARNINGS
 * \ingroup warning_level_traits
 */
template<>
struct WarningLevelTraits<PEDANDIC_OR_HIGHER_WARNINGS>
{
  typedef boost::mpl::set_c<WarningType,CRITICAL_WARNING,HIGH_PRIORITY_WARNING,MEDIUM_PRIORITY_WARNING,LOW_PRIORITY_WARNING,PEDANTIC_WARNING> SupportedWarningTypes;
};

/*! \brief Specialization of the WarningLevelTraits class for
 * Utility::PEDANTIC_WARNINGS_ONLY
 * \ingroup warning_level_traits
 */
template<>
struct WarningLeveLTraits<PEDANTIC_WARNINGS_ONLY>
{
  typedef boost::mpl::set_c<WarningType,PEDANTIC_WARNING> SupportedWarningTypes;
};

/*! \brief Specialization of the WarningLevelTraits class for
 * Utility::ALL_WARNINGS
 * \ingroup warning_level_traits
 */
template<>
struct WarningLevelTraits<ALL_WARNINGS>
{
  typedef boost::mpl::set_c<WarningType,CRITICAL_WARNING,HIGH_PRIORITY_WARNING,MEDIUM_PRIORITY_WARNING,LOW_PRIORITY_WARNING,PEDANTIC_WARNING> SupportedWarningTypes;
};
  
} // end Utility namespace

#endif // end UTILITY_WARNING_LEVEL_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_WarningLevelTraits.hpp
//---------------------------------------------------------------------------//
