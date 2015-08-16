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
  TGeoMaterial *term_mat = new TGeoMaterial( "Terminal",0,0,0 );
  TGeoMedium   *term_med = new TGeoMedium( "Terminal",1,term_mat );
   
  TGeoMaterial *H_mat = new TGeoMaterial( "mat_1",1,1,1 );
  TGeoMedium   *H_med = new TGeoMedium( "med_1",2,H_mat );

  // Define the cube volume and set it to be the highest node
  TGeoVolume *cube = gGeoManager->MakeBox( "CUBE",term_med,5.,5.,5. );
  gGeoManager->SetTopVolume( cube );
  cube->SetUniqueID(1);

  // Define the spherical volume
  TGeoVolume *sphere = gGeoManager->MakeSphere( "SPHERE",H_med,0.,2.5 );
  sphere->SetUniqueID(2);

  // Add the sphere as a daughter of the cube
  cube->AddNodeOverlap( sphere, 1 );
  
  // Close the geometry and draw it for visualization
  gGeoManager->CloseGeometry();

  gGeoManager->SetVisLevel(10);
  gGeoManager->SetTopVisible();
  cube->Draw();

}  // end Test_Root_Geometry


//---------------------------------------------------------------------------//
// end Test_Root_Geometry.C
//---------------------------------------------------------------------------//
