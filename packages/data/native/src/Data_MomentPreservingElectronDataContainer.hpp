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
#include <string>

// Boost Includes
#include <boost/filesystem/path.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_ArchivableObject.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

/*! The moment preserving electron data container
 * \details Linear-linear interpolation should be used for all data.
 */
class MomentPreservingElectronDataContainer : public Utility::ArchivableObject<MomentPreservingElectronDataContainer>
{

public:

  //! Constructor (from saved archive)
  MomentPreservingElectronDataContainer(
                          const boost::filesystem::path& file_name_with_path );

  //! Destructor
  virtual ~MomentPreservingElectronDataContainer()
  { /* ... */ }

  //! The database name used in an archive
  const char* getArchiveName() const override;

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
  
  // The name used in archive name-value pairs
  static const std::string s_archive_name;

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
  
BOOST_SERIALIZATION_CLASS_VERSION( MomentPreservingElectronDataContainer, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( MomentPreservingElectronDataContainer, Data );

EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Data, MomentPreservingElectronDataContainer );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_MomentPreservingElectronDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_MOMENT_PRESERVING_ELECTRON_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_MomentPreservingElectronDataContainer.hpp
//---------------------------------------------------------------------------//

