//---------------------------------------------------------------------------//
//! 
//! \file   Test_Root_Geometry.C
//! \author Eli Moll
//! \brief  Geometry for unit testing on ROOT implementation
//!
//---------------------------------------------------------------------------//

/* Definition of geometry consisting of two volumes. The innermost volume is
 * sphere of radius 2.5cm, centered at (0,0,0) and filled with hydrogen. The
 * surrounding volume is a cube of side length 10cm centered at (0,0,0) filled
 * with the terminal material. 
 */ 
void Test_Root_Geometry()
{
  // Set up manager of geometry world
  gSystem->Load( "libGeom" );
  new TGeoManager( "Test_Geometry",
                   "Geometry for testing root implementation" );
   
  // Define materials and media (space filling materials)
  TGeoMaterial *void_mat = new TGeoMaterial( "void",0,0,0 );
  TGeoMedium   *void_med = new TGeoMedium( "void_med",1,void_mat );
   
  TGeoMaterial *mat_1 = new TGeoMaterial( "mat_1",1,1,1 );
  TGeoMedium   *med_1 = new TGeoMedium( "med_1",2,mat_1 );

  // Define the cube volume and set it to be the highest node
  TGeoVolume *cube = gGeoManager->MakeBox( "CUBE",void_med,5.,5.,5. );
  gGeoManager->SetTopVolume( cube );
  cube->SetUniqueID(1);

  // Define the spherical volume
  TGeoVolume *sphere = gGeoManager->MakeSphere( "SPHERE",med_1,0.,2.5 );
  sphere->SetUniqueID(2);

  // Add the sphere as a daughter of the cube
  cube->AddNode( sphere, 1 );
  
  // Close the geometry and draw it for visualization
  gGeoManager->CloseGeometry();

  gGeoManager->SetVisLevel(10);
  gGeoManager->SetTopVisible();
  cube->Draw();

}  // end Test_Root_Geometry


//---------------------------------------------------------------------------//
// end Test_Root_Geometry.C
//---------------------------------------------------------------------------//
