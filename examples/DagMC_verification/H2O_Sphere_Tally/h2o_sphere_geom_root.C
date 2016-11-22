void h2o_sphere() 
{
    // Load the geometry library and initialize the geometry handler
    gSystem->Load("libGeom");
    new TGeoManager( "h2o_sphere", "Simple geometry used for verification of FaceMC results against MCNP." );

//---------------------------------------------------------------------------//
    // Material Definitions
    // TGeoMaterial( "name", A, Z, Density )
    // TGeoMedium( "name", Index, TGeoMaterial )
//---------------------------------------------------------------------------//

    // Light Water ( rho = 0.995 g/cm^3 )
    TGeoMaterial *H2O_mat = new TGeoMaterial( "mat_1", 1, 1, -0.995 );
    TGeoMedium *H2O_med = new TGeoMedium( "med_1", 1, H2O_mat );

    // Void
    TGeoMaterial *void_mat = new TGeoMaterial( "void_mat", 0, 0, 0 );
    TGeoMedium *void_med = new TGeoMedium( "void_med", 2, void_mat );

    // Graveyard
    TGeoMaterial *terminal_mat = new TGeoMaterial( "graveyard", 0, 0, 0 );
    TGeoMedium *terminal_med = new TGeoMedium( "graveyard", 3, terminal_mat );

//---------------------------------------------------------------------------//
    // Volume Definition Form:
    // MakeSphere( "name", TGeoMedium, Minimum_Radius, Maximum_Radius )
//---------------------------------------------------------------------------//

    // Light Water Sphere of radius 20cm
    TGeoVolume *H2O_Sphere = gGeoManager->MakeSphere( "H2O_Sphere", H2O_med, 0.0, 20.0 );
    H2O_Sphere->SetUniqueID(1);

    // Void Cube of Side Height 50cm
    TGeoVolume *void_geom = gGeoManager->MakeBox("void_geom", void_med, 25., 25., 25.);
    void_geom->SetUniqueID(2);

    // Graveyard Cube of Side Height 55cm
    TGeoVolume *terminal_geom = gGeoManager->MakeBox("terminal_geom", terminal_med, 27.5, 27.5, 27.5);
    terminal_geom->SetUniqueID(3);
    gGeoManager->SetTopVolume( terminal_geom );

//---------------------------------------------------------------------------//
    // Heirarchy (Volume) Definitions
    // AddNode( Daughter_Node, Copy_Number )
//---------------------------------------------------------------------------//
    
    // Adding that the water sphere is a daughter of the void
    void_geom->AddNode( H2O_Sphere, 1 );

    // Adding that the void is a daughter of the graveyard
    terminal_geom->AddNode( void_geom, 1 );

//---------------------------------------------------------------------------//
    // Export and Drawing Capabilities
//---------------------------------------------------------------------------//

  // Close the geometry
  gGeoManager->CloseGeometry();
  gGeoManager->SetTopVisible();
  
  // Uncomment to draw the geometry in an X-Window
  terminal_geom->Draw();
  
  gGeoManager->Export("sample01.root");
}  // end sample
//---------------------------------------------------------------------------//
// end sample01.C
//---------------------------------------------------------------------------//


