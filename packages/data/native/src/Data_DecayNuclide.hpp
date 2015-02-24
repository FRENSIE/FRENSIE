//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayNuclide.hpp
//! \author Alex Robinson
//! \brief  The decay nuclide class declaration (based on DecayData.hpp written
//!         by CJ Solomon
//!
//---------------------------------------------------------------------------//

#ifndef DATA_DECAY_NUCLIDE_HPP
#define DATA_DECAY_NUCLIDE_HPP

// Std Lib Includes
#include <vector>

// Boost Includes
#include <boost/serialization/split_member.hpp>

namespace Data{

//! The decay nuclide class
class DecayNuclide
{
  
public:

  //! Default constructor
  DecayNuclide();

  //! Constructor
  DecayNuclide( const unsigned atomic_number, 
		const unsigned atomic_mass_number, 
		const unsigned isomer_number = 0u );

  //! Return the atomic number (Z)
  unsigned getAtomicNumber() const;

  //! Set the atomic number (Z)
  void setAtomicNumber( const unsigned atomic_number );
  
  //! Return the atomic mass number (A)
  unsigned getAtomicMassNumber() const;

  //! Set the atomic mass number
  void setAtomicMassNumber( const unsigned atomic_mass_number );

  //! Return the isomer number (S)
  double getIsomerNumber();

  //! Set the isomer number (S)
  void setIsomerNumber( const unsigned isomer_number );

  //! Return the half-life of the nuclide
  double getHalfLife() const;

  //! Return the half-life error of the nuclide
  double getHalfLifeError() const;

  //! Return the decay constant of the nuclide
  double getDecayConstant() const;
  
  //! Return the decay constant error of the nuclide
  double getDecayConstantError() const;

  //! Set the half-life of the nuclide
  void setHalfLife( const double half_life,
		    const double half_life_error = 0.0 );

  //! Return the number of decay branches
  unsigned getNumberOfDecayBranches() const;

  //! Return the branching ratio of the desired decay branch
  unsigned getBranchingRatio( const unsigned branch ) const;

  //! Return the branching ratio error of the desired decay branch
  unsigned getBranchingRatioErr( const unsigned branch ) const;

  //! Return the daughter from the desired decay branch
  unsigned getDaughter( const unsigned branch ) const;

  //! Return the decay type of the desired decay branch
  unsigned getDecayType( const unsigned branch ) const;

  //! Return the primary decay type of the desired decay branch
  unsigned getPrimaryDecayType( const unsigned branch ) const;

  //! Add a decay branch
  void addDecayBranch( const unsigned daughter_szaid,
		       const unsigned decay_type,
		       const double branching_ratio,
		       const double branching_ratio_error );
  
private:

  // Serialize the data
  template<typename Archive>
  void serialize( Archive &ar, const unsigned int version );

  // A struct for store the decay branch data
  struct DecayBranch
  {
    double branching_ratio;
    double branching_ratio_error;
    double daughter;
    double decay_type;

    // Serialize the struct data
    template<typename Archive>
    void serialize( Archive &ar, const unsigned int version );
  };

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The atomic number (Z)
  unsigned d_atomic_number;

  // The atomic mass number (A)
  unsigned d_atomic_mass_number;

  // The isomer number (S)
  unsigned d_isomer_number;

  // The half-life
  double d_half_life;
  
  // The half-life error
  double d_half_life_error;

  // The decay constant
  double d_decay_constant;

  // The decay constant error
  double d_decay_constant_error;

  // The decay branch data
  std::vector<DecayBranch> d_decay_branches;
};

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_DecayNuclide_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_DECAY_NUCLIDE_HPP

//---------------------------------------------------------------------------//
// end Data_DecayNuclide.hpp
//---------------------------------------------------------------------------//
