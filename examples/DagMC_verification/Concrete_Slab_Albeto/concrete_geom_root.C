void concrete_geom_root() 
{
    // Load the geometry library and initialize the geometry handler
    gSystem->Load("libGeom");
    new TGeoManager( "concrete", "Simple geometry used for verification of FaceMC results against MCNP." );

//---------------------------------------------------------------------------//
    // Material Definitions
    // TGeoMaterial( "name", A, Z, Density )
    // TGeoMedium( "name", Index, TGeoMaterial )
//---------------------------------------------------------------------------//

    // Iron Portland Concrete ( rho = 5.90 g/cm^3 )
    TGeoMaterial *concrete_mat = new TGeoMaterial( "mat_1", 1, 1, -5.90 );
    TGeoMedium *concrete_med = new TGeoMedium( "med_1", 1, concrete_mat );

    // Void
    TGeoMaterial *void_mat = new TGeoMaterial( "void_mat", 0, 0, 0 );
    TGeoMedium *void_med = new TGeoMedium( "void_med", 2, void_mat );

    // Graveyard
    TGeoMaterial *terminal_mat = new TGeoMaterial( "graveyard", 0, 0, 0 );
    TGeoMedium *terminal_med = new TGeoMedium( "graveyard", 3, terminal_mat );

//---------------------------------------------------------------------------//
    // Volume Definition Form:
    // MakeBox( "name", TGeoMedium, x-width, y-width, z-width )
//---------------------------------------------------------------------------//

    // Iron Portlnd Concrete Slab with dimensions 15cm x 300cm x 300cm
    TGeoVolume *concrete_box = gGeoManager->MakeBox( "concrete_box", concrete_med, 7.5, 150., 150.);
    concrete_box->SetUniqueID(1);

    // Void Cube of Side Height 50cm
    TGeoVolume *void_geom = gGeoManager->MakeBox("void_geom", void_med, 25., 160., 160.);
    void_geom->SetUniqueID(2);

    // Graveyard Cube of Side Height 55cm
    TGeoVolume *terminal_geom = gGeoManager->MakeBox("terminal_geom", terminal_med, 50., 175., 175.);
    terminal_geom->SetUniqueID(3);
    gGeoManager->SetTopVolume( terminal_geom );

//---------------------------------------------------------------------------//
    // Heirarchy (Volume) Definitions
    // AddNode( Daughter_Node, Copy_Number )
//---------------------------------------------------------------------------//
    
    // Adding that the concrete slab is a daughter of the void
    void_geom->AddNode( concrete_box, 1 );

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
  
  gGeoManager->Export("concrete_geom.root");
}  // end sample
//---------------------------------------------------------------------------//
// end sample01.C
//---------------------------------------------------------------------------//

