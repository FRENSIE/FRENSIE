//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronMaterial.hpp
//! \author Luke Kersting
//! \brief  Positron material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRON_MATERIAL_HPP
#define MONTE_CARLO_POSITRON_MATERIAL_HPP

// FRENSIE Includes
#include "MonteCarlo_Positronatom.hpp"
#include "MonteCarlo_Material.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The positron material class
class PositronMaterial : public Material<Positronatom>
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

  // Typedef for the base type
  typedef Material<Positronatom> BaseType;

public:

  //! The material handle type
  typedef typename BaseType::InternalMaterialHandle InternalMaterialHandle;

  //! The photoatom name map type
  typedef typename BaseType::ScatteringCenterNameMap PositronatomNameMap;

  //! Constructor
  PositronMaterial( const InternalMaterialHandle id,
                    const double density,
                    const PositronatomNameMap& positronatom_name_map,
                    const std::vector<double>& positronatom_fractions,
                    const std::vector<std::string>& positronatom_names );

  //! Destructor
  ~PositronMaterial()
  { /* ... */ }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronMaterial.hpp
//---------------------------------------------------------------------------//
