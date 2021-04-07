//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExplicitTemplateInstantiationMacros.hpp
//! \author Alex Robinson
//! \brief  Explicit template instantiation macros
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXPLICIT_TEMPLATE_INSTANTIATION_MACROS_HPP
#define UTILITY_EXPLICIT_TEMPLATE_INSTANTIATION_MACROS_HPP

// FRENSIE Includes
#include "FRENSIE_config.hpp"

/*! \defgroup explicit_instantiation_macros Explicit Instantiation Macros
 *
 * Explicit instantiation can be used to reduce compile times and compile
 * time memory overhead. When explicit instantiation has been enabled, these
 * macros will declare the templates to instantiate. Otherwise, these macros
 * will do nothing. Note that swig doesn't like the extern template declaration
 * so these macros will be turned off when SWIG is processing files.
 */

#if !defined SWIG

/*! Declare an external explicit instantiation of template class
 * \details This can only be called once for a given instantiation. It is
 * therefor recommended that it is called in the header file.
 * \ingroup explicit_instantiation_macros
 */
#define EXTERN_EXPLICIT_TEMPLATE_CLASS_INST_ALWAYS( ... )       \
  extern template class __VA_ARGS__

/*! Declare an external explicit instantiation of a template function
 * \details This can only be called once for a given instantiation. It is
 * therefor recommended that it is called in the header file. Note that
 * both stand-alone functions and member functions can be passed to this macro.
 * \ingroup explicit_instantiation_macros
 */
#define EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST_ALWAYS( ... )    \
  extern template __VA_ARGS__

/*! Declare an explicit instantiation of a template class
 * \details When paired with the corresponding extern declaration this macro
 * can only be called in a single compilation unit (e.g. a single .cpp file).
 * Otherwise this macro can be called in the header file as well.
 * \ingroup explicit_instantiation_macros
 */
#define EXPLICIT_TEMPLATE_CLASS_INST_ALWAYS( ... )       \
  template class __VA_ARGS__

/*! Declare an explicit instantiation of a template function
 * \details When paired with the corresponding extern declaration this macro
 * can only be called in a single compilation unit (e.g. a single .cpp file).
 * Otherwise this macro can be called in the header file as well. Note that
 * both stand-alone functions and member functions can be passed to this macro.
 * \ingroup explicit_instantiation_macros
 */
#define EXPLICIT_TEMPLATE_FUNCTION_INST_ALWAYS( ... ) \
  template __VA_ARGS__

#else

#define EXTERN_EXPLICIT_TEMPLATE_CLASS_INST_ALWAYS( ... )
#define EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST_ALWAYS( ... )
#define EXPLICIT_TEMPLATE_CLASS_INST_ALWAYS( ... )
#define EXPLICIT_TEMPLATE_FUNCTION_INST_ALWAYS( ... )

#endif // end !defined SWIG

#if HAVE_FRENSIE_ENABLE_EXPLICIT_TEMPLATE_INSTANTIATION && !defined SWIG

/*! Declare an external explicit instantiation of template class
 * \details This can only be called once for a given instantiation. It is
 * therefor recommended that it is called in the header file.
 * \ingroup explicit_instantiation_macros
 */
#define EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ... ) \
  extern template class __VA_ARGS__

/*! Declare an external explicit instantiation of a template function
 * \details This can only be called once for a given instantiation. It is
 * therefor recommended that it is called in the header file. Note that
 * both stand-alone functions and member functions can be passed to this macro.
 * \ingroup explicit_instantiation_macros
 */
#define EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( ... ) \
  extern template __VA_ARGS__

/*! Declare an explicit instantiation of a template class
 * \details When paired with the corresponding extern declaration this macro
 * can only be called in a single compilation unit (e.g. a single .cpp file).
 * Otherwise this macro can be called in the header file as well.
 * \ingroup explicit_instantiation_macros
 */
#define EXPLICIT_TEMPLATE_CLASS_INST( ... ) \
  template class __VA_ARGS__

/*! Declare an explicit instantiation of a template function
 * \details When paired with the corresponding extern declaration this macro
 * can only be called in a single compilation unit (e.g. a single .cpp file).
 * Otherwise this macro can be called in the header file as well. Note that
 * both stand-alone functions and member functions can be passed to this macro.
 * \ingroup explicit_instantiation_macros
 */
#define EXPLICIT_TEMPLATE_FUNCTION_INST( ... ) \
  template __VA_ARGS__

#else // HAVE_FRENSIE_ENABLE_EXPLICIT_TEMPLATE_INSTANTIATION

#define EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( ... )
#define EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( ... )
#define EXPLICIT_TEMPLATE_CLASS_INST( ... )
#define EXPLICIT_TEMPLATE_FUNCTION_INST( ... )

#endif // end HAVE_FRENSIE_ENABLE_EXPLICIT_TEMPLATE_INSTANTIATION && !defined SWIG

#endif // end UTILITY_EXPLICIT_TEMPLATE_INSTANTIATION_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_ExplicitTemplateInstantiationMacros.hpp
//---------------------------------------------------------------------------//
