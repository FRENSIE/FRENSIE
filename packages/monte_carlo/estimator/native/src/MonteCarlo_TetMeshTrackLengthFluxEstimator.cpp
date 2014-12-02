//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TetMeshTrackLengthFluxEstimator.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tet mesh flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/mpl/vector.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Moab Includes
#include <moab/Interface.hpp>
#include <moab/AdaptiveKDTree.hpp>
#include <moab/OreintedBoxTreeTool.hpp>
#include <moab/Matrix3.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Estimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Constructor
TetMeshTrackLengthFluxEstimator(
		     const Estimator::idType id,
		     const double multiplier,
		     const std::string input_mesh_file_name,
		     const std::string output_mesh_file_name = "tetmesh.h5m" )
    : Teuchos::RCP<new moab::Core()>,
      Teuchos::RCP<new moab::AdaptiveKDTree(d_moab_interface)>,
      d_kd_tree_root[],
      Teuchos::RCP< new moab::OrientedBoxTreeTool(d_moab_interface),
      d_obb_tree_root[],
      d_last_visited_tet[],
      d_last_visited_cell,
      boost::unordered_map<moab::EntityHandle,const double> 
      boost::unordered_map<moab::EntityHandle,moab::Matrix3>,
      boost::unordered_map<moab::EntityHandle,Teuchos::Array<Utility> >,
      boost::unordered_map<moab::EntityHandle,Teuchos::Array<Double> >,
      boost::unordered_set<moab::EntityHandle,Teuchos::Array<Double> >
{

  // ------------------------ Load Meshset -------------------------------------

  // Create empty MOAB meshset
  moab::EntityHandle meshset_from_input;
  moab::ErrorCode return_value = moab::create_meshset(
                                         moab::MESHSET_SET, meshset_from_input);
                                          
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  // Populate MOAB meshset with data from input file                   
  return_value = moab::load_file(
                             input_mesh_file_name.c_str(), &meshset_from_input);
                             
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );                
  
  // Range (domain) of all tetrahedral elements
  moab::Range all_tet_elements;
  
  // ---------------------------- KD Trees -------------------------------------
  
  moab::Range surface_triangles;
  moab::ErrorCode return_value;
  int current_dimension;
  
  // Get dimension of the input set
  dimension = d_moab_interface->dimension_from_handle(all_tet_elements[0]);
  
  // Determine the edges from the input set
  return_value = d_moab_interface->get_adjacencies(
                            all_tet_elements, current_dimension - 1, true,
                            surface_triangles, Interface::UNION);
                            
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
  
  all_tet_elements.merge( surface_triangles );
  
  // QUESTION - Where does KDTREE_ROOT come from (see DagMC::TLMT - l492) ?
  d_kd_tree->build_tree(all_tet_elements, d_kd_tree_root);
  
  // ---------------------- Reduce Meshset to 3D -------------------------------  
  
  moab::ErrorCode return_value;
  
  // Extract 3D elements from meshset
  return_value = d_moab_interface->get_entities_by_dimension(
                        meshset_from_input, 3, all_tet_elements);
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
  
  // Clear the meshset                    
  return_value = d_moab_interface->clear_meshset(&meshset_from_input, 1);
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
                      
  // Reconstruct the meshset using only 3D entitites                    
  return_value = d_moab_interface->add_entities(
                                          meshset_from_input, all_tet_elements);  
                                          
  unsigned int number_of_tets = all_tet_elements.size();
  
  for( Range::const_iterator i=all_tet_elements.begion(); 
                                                 i!=all_tet_elements.end(); ++i)
    {
      moab::EntityHandle tet = *i;
     
      // Map array for the estimator moments of a specific tetrahdron
      Teuchos::Array<Utility::Pair<double,double> > > entity_array =
                                                   d_tet_estimator_moments[tet];
     
      moab::CartVect vertices[4];
      entity_array.resize(1);
     
      // Extract the vertex data for the given tet
      std::vector<moab::EntityHandle> vertex;
      d_moab_interface->get_connectivity( &tet, 1, vertex );
     
      // Test that the vertex entity contains four points
      TEST_ASSERT( vertex.size() == 4);
     
      int k = 0;
      for( std::vector<EntityHandle>::iterator j = vertex.begin();
                                                            j!=vertex.end; ++j )
      {
        moab::EntityHandle vertex_j = *j;
        d_moab_interface->get_coords( &vertex_j, vertices[k++].array() );
      }               
      
      // Calculate Tetrahedral Volumes
      const double volume = Utility::calculateTetrahedronVolume( vertices[0],
                                                                vertices[1],
                                                                vertices[2],
                                                                vertices[3] );
                                                                
      // Map Tetrahedral Volumes
      d_tet_volumes[tet] = volume;
      
      // Calculate Barycentric Matrix
      moab::Matrix3 barycentric_transform_matrix;
      Utility::calculateBarycentricTransformMatrix( vertices[0],
                                                    vertices[1],
                                                    vertices[2],
                                                    vertices[3],
                                                 barycentric_transform_matrix );
                                    
      // Map Barycentric Matrix
      d_tet_barycentric_transform_matrices[tet] = barycentric_transform_matrix;
      
      // QUESTION - How to consider multiple energy bins in map?
   
   } // end tet iteration

} // end Constructor
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
