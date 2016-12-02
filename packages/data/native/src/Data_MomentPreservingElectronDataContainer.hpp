//---------------------------------------------------------------------------//
//!
//! \file   Data_MomentPreservingElectronDataContainer.hpp
//! \author Luke Kersting
//! \brief  The native moment preserving electron data container class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_MOMENT_PRESERVING_ELECTRON_DATA_CONTAINER_HPP
#define DATA_MOMENT_PRESERVING_ELECTRON_DATA_CONTAINER_HPP

// Std Lib Includes
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <string>

// Boost Includes
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_StandardArchivableObject.hpp"
#include "Utility_StandardSerializableObject.hpp"

namespace Data{

/*! The moment preserving electron data container
 * \details Linear-linear interpolation should be used for all data.
 */
class MomentPreservingElectronDataContainer : public Utility::StandardArchivableObject<MomentPreservingElectronDataContainer,false>, public Utility::StandardSerializableObject<MomentPreservingElectronDataContainer,false>
{

public:

  //! Constructor (from saved archive)
  MomentPreservingElectronDataContainer(
		  const std::string& archive_name,
                  const Utility::ArchivableObject::ArchiveType archive_type =
		  Utility::ArchivableObject::XML_ARCHIVE );

  //! Destructor
  virtual ~MomentPreservingElectronDataContainer()
  { /* ... */ }

  //! Return the atomic number
  unsigned getAtomicNumber() const;

  //! Return the elastic cutoff angle cosine
  double getCutoffAngleCosine() const;

  //! Return the elastic angular energy grid
  const std::vector<double>& getElasticAngularEnergyGrid() const;

  //! Return the number of discrete angles for an angular energy bin
  unsigned getNumberOfDiscreteAngles( const unsigned angular_energy_bin ) const;

  //! Return the moment preserving discrete angles for an angular energy bin
  const std::vector<double>& getMomentPreservingDiscreteAngles(
					       const unsigned angular_energy_bin ) const;

  //! Return the moment preserving weights for an angular energy bin
  const std::vector<double>& getMomentPreservingWeights(
					       const unsigned angular_energy_bin ) const;

protected:

  //! Default constructor
  MomentPreservingElectronDataContainer()
  { /* ... */ }

  //! Set the atomic number
  void setAtomicNumber( const unsigned atomic_number );

  //! Set the elastic cutoff angle cosine
  void setCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Set the elastic angular energy grid
  void setElasticAngularEnergyGrid(
            const std::vector<double>& angular_energy_grid );

  //! Set the number of discrete angles for an angular energy bin
  void setNumberOfDiscreteAngles(
             const unsigned angular_energy_bin,
             const unsigned number_of_discrete_angles );

  //! Set the moment preserving discrete angles for an angular energy bin
  void setMomentPreservingDiscreteAngles(
		     const unsigned angular_energy_bin,
		     const std::vector<double>& moment_preserving_elastic_discrete_angles );

  //! Set the moment preserving weights for an angular energy bin
  void setMomentPreservingWeights(
			 const unsigned angular_energy_bin,
			 const std::vector<double>& moment_preserving_elastic_weights );

private:

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The atomic number
  unsigned d_atomic_number;

  // The elastic cutoff angle cosine
  double d_cutoff_angle_cosine;

  // The elastic angular energy grid (MeV)
  std::vector<double> d_angular_energy_grid;

  // The number of discrete angles for angular energy bin
  std::map<unsigned,unsigned> d_number_of_discrete_angles;

  // The moment preserving discrete angles
  std::map<unsigned,std::vector<double> > d_moment_preserving_elastic_discrete_angles;

  // The moment preserving weights
  std::map<unsigned,std::vector<double> > d_moment_preserving_elastic_weights;
};

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_MomentPreservingElectronDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_MOMENT_PRESERVING_ELECTRON_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_MomentPreservingElectronDataContainer.hpp
//---------------------------------------------------------------------------//

