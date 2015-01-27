//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDInterpolationPolicy.hpp
//! \author Alex Robinson
//! \brief  Policy struct declarations for interpolating on 2D grids
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_INTERPOLATION_POLICY_HPP
#define UTILITY_TWO_D_INTERPOLATION_POLICY_HPP

namespace Utility{

/*! \brief Policy struct for interpolating 2D tables
 * \details A Z-Y interpolation policy and a Z-X interpolation policy must
 * be specified (the Z variable must be processed in the same way in both)
 */
template<typename ZYInterpPolicy,typename ZXInterpPolicy>
struct TwoDInterpolationPolicyImpl
{
  //! Conduct the interpolation between two grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T, 
	   typename YIterator,
	   typename ZIterator>
  static T interpolateGrids( const T indep_var_x_0,
			     const T indep_var_x_1,
			     const T indep_var_x,
			     const T indep_var_y,
			     YIterator start_indep_y_grid_0,
			     YIterator end_indep_y_grid_0,
			     ZIterator start_dep_grid_0,
			     ZIterator end_dep_grid_0,
			     YIterator start_indep_y_grid_1,
			     YIterator end_indep_y_grid_1,
			     ZIterator start_dep_grid_1,
			     ZIterator end_dep_grid_1 );

  //! Conduct the interpolation between two grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T,
	   typename Iterator>
  static T interpolateGrids( const T indep_var_x_0,
			     const T indep_var_x_1,
			     const T indep_var_x,
			     const T indep_var_y,
			     Iterator start_grid_0,
			     Iterator end_grid_0,
			     Iterator start_grid_1,
			     Iterator end_grid_1 );

  //! Conduct the interpolation between two grids (no tuples)
  template<typename T, typename YIterator, typename ZIterator>
  static T interpolateGrids( const T indep_var_x_0,
			     const T indep_var_x_1,
			     const T indep_var_x,
			     const T indep_var_y,
			     YIterator start_indep_var_y_0,
			     YIterator end_indep_var_y_0,
			     ZIterator start_dep_var_0,
			     ZIterator end_dep_var_0,
			     YIterator start_indep_var_y_1,
			     YIterator end_indep_var_y_1,
			     ZIterator start_dep_var_1,
			     ZIterator end_dep_var_1 );

  //! Conduct unit base interpolation between two grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T, 
	   typename YIterator,
	   typename ZIterator>
  static T interpolateGridsUnitBase( const T indep_var_x_0,
				     const T indep_var_x_1,
				     const T indep_var_x,
				     const T indep_var_y,
				     YIterator start_indep_y_grid_0,
				     YIterator end_indep_y_grid_0,
				     ZIterator start_dep_grid_0,
				     ZIterator end_dep_grid_0,
				     YIterator start_indep_y_grid_1,
				     YIterator end_indep_y_grid_1,
				     ZIterator start_dep_grid_1,
				     ZIterator end_dep_grid_1 );

  //! Conduct the interpolation between two grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T,
	   typename Iterator>
  static T interpolateGridsUnitBase( const T indep_var_x_0,
				     const T indep_var_x_1,
				     const T indep_var_x,
				     const T indep_var_y,
				     Iterator start_grid_0,
				     Iterator end_grid_0,
				     Iterator start_grid_1,
				     Iterator end_grid_1 );

  //! Conduct unit base interpolation between two grids (no tuples)
  template<typename T, typename YIterator, typename ZIterator>
  static T interpolateGridsUnitBase( const T indep_var_x_0,
				     const T indep_var_x_1,
				     const T indep_var_x,
				     const T indep_var_y,
				     YIterator start_indep_var_y_0,
				     YIterator end_indep_var_y_0,
				     ZIterator start_dep_var_0,
				     ZIterator end_dep_var_0,
				     YIterator start_indep_var_y_1,
				     YIterator end_indep_var_y_1,
				     ZIterator start_dep_var_1,
				     ZIterator end_dep_var_1 );
  
  //! Conduct the interpolation between two processed grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T, 
	   typename YIterator,
	   typename ZIterator>
  static T interpolateProcessedGrids( const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
				      YIterator start_processed_indep_y_grid_0,
				      YIterator end_processed_indep_y_grid_0,
				      ZIterator start_processed_dep_grid_0,
				      ZIterator end_processed_dep_grid_0,
				      YIterator start_processed_indep_y_grid_1,
				      YIterator end_processed_indep_y_grid_1,
				      ZIterator start_processed_dep_grid_1,
				      ZIterator end_processed_dep_grid_1 );

  //! Conduct the interpolation between two processed grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T, 
	   typename Iterator>
  static T interpolateProcessedGrids( const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
				      Iterator start_processed_grid_0,
				      Iterator end_processed_grid_0,
				      Iterator start_processed_grid_1,
				      Iterator end_processed_grid_1 );

  //! Conduct the interpolation between two processed grids (no tuples)
  template<typename T, typename YIterator, typename ZIterator>
  static T interpolateProcessedGrids( const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
				      YIterator start_processed_indep_y_grid_0,
				      YIterator end_processed_indep_y_grid_0,
				      ZIterator start_processed_dep_grid_0,
				      ZIterator end_processed_dep_grid_0,
				      YIterator start_processed_indep_y_grid_1,
				      YIterator end_processed_indep_y_grid_1,
				      ZIterator start_processed_dep_grid_1,
				      ZIterator end_processed_dep_grid_1 );

  //! Conduct unit base interpolation between two processed grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T, 
	   typename YIterator,
	   typename ZIterator>
  static T interpolateProcessedGridsUnitBase( 
				      const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
				      YIterator start_processed_indep_y_grid_0,
				      YIterator end_processed_indep_y_grid_0,
				      ZIterator start_processed_dep_grid_0,
				      ZIterator end_processed_dep_grid_0,
				      YIterator start_processed_indep_y_grid_1,
				      YIterator end_processed_indep_y_grid_1,
				      ZIterator start_processed_dep_grid_1,
				      ZIterator end_processed_dep_grid_1 );

  //! Conduct unit base interpolation between two processed grids
  template<TupleMember YIndepMember,
	   TupleMember DepMember,
	   typename T, 
	   typename Iterator>
  static T interpolateProcessedGridsUnitBase( 
				      const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
				      Iterator start_processed_grid_0,
				      Iterator end_processed_grid_0,
				      Iterator start_processed_grid_1,
				      Iterator end_processed_grid_1 );
				      

  //! Conduct unit base interpolation between two processed grids (no tuples)
  template<typename T, typename YIterator, typename ZIterator>
  static T interpolateProcessedGridsUnitBase( 
				      const T processed_indep_var_x_0,
				      const T processed_indep_var_x_1,
				      const T processed_indep_var_x,
				      const T processed_indep_var_y,
				      YIterator start_processed_indep_y_grid_0,
				      YIterator end_processed_indep_y_grid_0,
				      ZIterator start_processed_dep_grid_0,
				      ZIterator end_processed_dep_grid_0,
				      YIterator start_processed_indep_y_grid_1,
				      YIterator end_processed_indep_y_grid_1,
				      ZIterator start_processed_dep_grid_1,
				      ZIterator end_processed_dep_grid_1 );

  //! Calculate the unit base y independent variable
  template<typename T>
  static T calculateUnitBaseIndepYVariable( const T indep_var_y,
					    const T min_indep_var_y,
					    const T indep_var_y_range );
  
  //! Calculate the independent y variable
  template<typename T>
  static T calculateIndepYVariable( const T unit_base_indep_var_y,
				    const T min_indep_var_y,
				    const T indep_var_y_range );
};

//! Helper class used by unit base interpolation methods (Lin-Lin)
template<typename YProcessingTag, typename XProcessingTag>
struct UnitBaseHelper
{ /* ... */ };

//! Helper class used by unit base interpolation methods (Lin-Lin)
template<typename LinIndepVarProcessingTag, typename LinIndepVarProcessingTag>
struct UnitBaseHelper
{
  //! The YX interpolation policy
  typedef LinLin YXInterpPolicy;
};

//! Helper class used by unit base interpolation methods (Lin-Log)
template<typename LinIndepVarProcessingTag, typename LogIndepVarProcessingTag>
struct UnitBaseHelper
{
  //! The YX interpolation policy
  typedef LinLog YXInterpPolicy;
};

//! Helper class used by unit base interpolation methods (Log-Lin)
template<typename LogIndepVarProcessingTag, typename LinIndepVarProcessingTag>
struct UnitBaseHelper
{
  //! The YX interpolation policy
  typedef LogLin YXInterpPolicy;
};

//! Helper class used by unit base interpolation methods (Log-Lin)
template<typename LogIndepVarProcessingTag, typename LogIndepVarProcessingTag>
struct UnitBaseHelper
{
  //! The YX interpolation policy
  typedef LogLog YXInterpPolicy;
};

/*! \brief Policy struct for interpolating 2D tables (Z-Y interpolation policy
 * is Lin-Lin and Z-X policy interpolation policy is Lin-Lin).
 */
struct LinLinLin : public TwoDInterpolationPolicyImpl<LinLin,LinLin>
{ /* ... */ };

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_TwoDInterpolationPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TWO_D_INTERPOLATION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDInterpolationPolicy.hpp
//---------------------------------------------------------------------------//
