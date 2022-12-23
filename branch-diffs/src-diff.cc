diff --git a/../../GRAPE-MM/src/ActionInitialization.cc b/../../GRAPE-CE/src/ActionInitialization.cc
old mode 100644
new mode 100755
index 93df918..b3f7c97
--- a/../../GRAPE-MM/src/ActionInitialization.cc
+++ b/../../GRAPE-CE/src/ActionInitialization.cc
@@ -1,12 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  Cube Balloon Flight
-//  Created: Mar 2, 2022 by Camden Ertley
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file ActionInitialization.cc
@@ -20,8 +20,6 @@
 
 #include "G4GeneralParticleSource.hh"
 
-using namespace grape;
-
 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 namespace grape
 {
@@ -46,7 +44,9 @@ namespace grape
   //****************************************************************************
   void ActionInitialization::BuildForMaster() const
   {
-    SetUserAction(new RunAction);
+    auto eventAct = new EventAction();
+    auto runAct = new RunAction( eventAct );
+    SetUserAction( runAct );
   }
 
 
@@ -55,14 +55,15 @@ namespace grape
   //****************************************************************************
   void ActionInitialization::Build() const
   {
-    PrimaryGeneratorAction* prim = new PrimaryGeneratorAction();
-    SetUserAction(prim);
+    auto priGenAct = new PrimaryGeneratorAction();
+    SetUserAction( priGenAct );
+
+    auto eventAct = new EventAction();
+    SetUserAction( eventAct );
 
-    RunAction* run = new RunAction();
-    SetUserAction(run);
+    auto runAct = new RunAction( eventAct );
+    SetUserAction( runAct );
 
-    EventAction* event = new EventAction();
-    SetUserAction(event);
   }  
 
 }
diff --git a/../../GRAPE-MM/src/DetectorConstruction.cc b/../../GRAPE-CE/src/DetectorConstruction.cc
old mode 100644
new mode 100755
index a0dbbbc..19bea7b
--- a/../../GRAPE-MM/src/DetectorConstruction.cc
+++ b/../../GRAPE-CE/src/DetectorConstruction.cc
@@ -1,12 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  Cube Balloon Flight
-//  Created: Mar 2, 2022 by Camden Ertley
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file DetectorConstruction.cc
@@ -46,8 +46,6 @@
 #include "G4PhysicalConstants.hh"
 #include "G4SystemOfUnits.hh"
 
-#include "G4AssemblyVolume.hh"
-
 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 namespace grape
 {
@@ -94,13 +92,14 @@ namespace grape
     //======================================================
     auto isotopes = true;
     G4Element* eH  = nistManager -> FindOrBuildElement( "H" , isotopes ); // 1
-    G4Element* eBe = nistManager -> FindOrBuildElement( "Be", isotopes ); // 4
+    // G4Element* eBe = nistManager -> FindOrBuildElement( "Be", isotopes ); // 4
     G4Element* eC  = nistManager -> FindOrBuildElement( "C" , isotopes ); // 6
     G4Element* eO  = nistManager -> FindOrBuildElement( "O" , isotopes ); // 8
     G4Element* eF  = nistManager -> FindOrBuildElement( "F" , isotopes ); // 9
     G4Element* eMg = nistManager -> FindOrBuildElement( "Mg", isotopes ); // 12
     G4Element* eAl = nistManager -> FindOrBuildElement( "Al", isotopes ); // 13
     G4Element* eSi = nistManager -> FindOrBuildElement( "Si", isotopes ); // 14
+    G4Element* eCl = nistManager -> FindOrBuildElement( "Cl", isotopes ); // 17
     G4Element* eTi = nistManager -> FindOrBuildElement( "Ti", isotopes ); // 22
     G4Element* eCr = nistManager -> FindOrBuildElement( "Cr", isotopes ); // 24
     G4Element* eMn = nistManager -> FindOrBuildElement( "Mn", isotopes ); // 25
@@ -108,8 +107,9 @@ namespace grape
     G4Element* eCu = nistManager -> FindOrBuildElement( "Cu", isotopes ); // 29
     G4Element* eZn = nistManager -> FindOrBuildElement( "Zn", isotopes ); // 30
     G4Element* eGa = nistManager -> FindOrBuildElement( "Ga", isotopes ); // 31
+    G4Element* eBr = nistManager -> FindOrBuildElement( "Br", isotopes ); // 35
     G4Element* eSn = nistManager -> FindOrBuildElement( "Sn", isotopes ); // 50
-    // G4Element* eI  = nistManager -> FindOrBuildElement( "I" , isotopes ); // 53
+    // G4Element* eI  = nistManager -> FindOrBuildElement( "I", isotopes ); // 53
     // G4Element* eCs = nistManager -> FindOrBuildElement( "Cs", isotopes ); // 55
     G4Element* eGd = nistManager -> FindOrBuildElement( "Gd", isotopes ); // 30
     G4Element* ePb = nistManager -> FindOrBuildElement( "Pb", isotopes ); // 82
@@ -117,16 +117,21 @@ namespace grape
     //======================================================
     // define materials
     //======================================================
-    // Vacuum ( Nist G4_Galactic )
+    //----------------------------------
+    // Vacuum and Air
+    //----------------------------------
     nistManager -> FindOrBuildMaterial("G4_Galactic");
     nistManager -> FindOrBuildMaterial("G4_AIR");
 
+    //----------------------------------
     // Elements as materials
+    //----------------------------------
     nistManager -> FindOrBuildMaterial("G4_Pb");
     nistManager -> FindOrBuildMaterial("G4_Si");
-    nistManager -> FindOrBuildMaterial("G4_Sn");
 
+    //----------------------------------
     // ALUMINUM 6061
+    //----------------------------------
     auto mAl6061 = new G4Material( "Aluminum6061", 2.6989*g/cm3, 9 );
       mAl6061 -> AddElement( eSi,  0.60*perCent );
       mAl6061 -> AddElement( eFe,  0.70*perCent );
@@ -138,72 +143,149 @@ namespace grape
       mAl6061 -> AddElement( eTi,  0.15*perCent );
       mAl6061 -> AddElement( eAl, 96.65*perCent );
 
-    // PC Baord 80% G10 circuit board, 20% generic electronics
-    auto mPC = new G4Material( "PCmaterial", 1.8*g/cm3, 9 );
-      mPC -> AddElement( eH ,  3.0*perCent );
-      mPC -> AddElement( eC , 17.4*perCent );
-      mPC -> AddElement( eO , 39.2*perCent );
-      mPC -> AddElement( eAl, 10.0*perCent );
-      mPC -> AddElement( eSi, 24.4*perCent );
-      mPC -> AddElement( eFe,  1.0*perCent );
-      mPC -> AddElement( eCu,  3.0*perCent );
-      mPC -> AddElement( eSn,  1.0*perCent );
-      mPC -> AddElement( ePb,  1.0*perCent );
-
-    // Delrin
+    //----------------------------------
+    // Connector
+    //----------------------------------
     auto mDelrin = new G4Material( "Delrin", 1.415*g/cm3, 3 );
       mDelrin -> AddElement( eH , 2 );
       mDelrin -> AddElement( eC , 1 );
       mDelrin -> AddElement( eO , 1 );
     
-    // Connector
-    auto mConnector = new G4Material( "ConnectorMaterial", 5.158*g/cm3, 2 );
+    auto mConnector = new G4Material( "Connector_Mat", 5.158*g/cm3, 2 );
       mConnector -> AddElement( eCu , 50.*perCent );
       mConnector -> AddMaterial( mDelrin , 50.*perCent );
 
-//     // SiPM
-//     auto mSiPM = new G4Material( "SiPM", 2.329*g/cm3, 1 );
-//       mSiPM -> AddElement( eSi , 100.*perCent );
-// 
-//     // Optical Pad
-//     auto mOPad = new G4Material( "OpticalPad", 2.329*g/cm3, 1 );
-//       mOPad -> AddElement( eSi , 100.*perCent );
-      
-    // MAPMT Material
-    auto mPMT = new G4Material( "PMTmaterial", 0.741*g/cm3, 4 );
-      mPMT -> AddElement( eO , 26.63*perCent );
-      mPMT -> AddElement( eSi, 23.37*perCent );
-      mPMT -> AddElement( eBe, 25.00*perCent );
-      mPMT -> AddElement( eCu, 25.00*perCent );
+    //----------------------------------
+    // PCB Epoxy
+    //----------------------------------
+    auto mPCB_Epoxy = new G4Material( "PCB_Epoxy", 1.125*g/cm3, 3 );
+      mPCB_Epoxy -> AddElement( eC, 15 );
+      mPCB_Epoxy -> AddElement( eH, 44 );
+      mPCB_Epoxy -> AddElement( eO,  7 );
 
+    //----------------------------------
+    // PCB Fiberglass
+    //----------------------------------
+    auto mPCB_FiberGlass = new G4Material( "PCB_FiberGlass", 2.65*g/cm3, 1 );
+      mPCB_FiberGlass -> AddMaterial( nistManager->FindOrBuildMaterial( "G4_SILICON_DIOXIDE" ), 1 );
+
+    //----------------------------------
+    // NEMA G10 (from advanced examples)
+    //----------------------------------
+    auto mG10 = new G4Material( "G10", 1.850*g/cm3, 3 );
+      mG10 -> AddMaterial( mPCB_FiberGlass, 77.3*perCent );
+      mG10 -> AddMaterial( mPCB_Epoxy,      14.7*perCent );
+      mG10 -> AddElement(  eCl,              8.0*perCent );
+
+    //----------------------------------
+    // NEMA FR4 (from advanced examples)
+    //----------------------------------
+    auto mFR4 = new G4Material( "FR4", 1.850*g/cm3, 4 );
+      mFR4 -> AddMaterial( mPCB_FiberGlass, 61.3*perCent );
+      mFR4 -> AddMaterial( mPCB_Epoxy,      14.7*perCent );
+      mFR4 -> AddElement(  eBr,              8.0*perCent );
+      mFR4 -> AddElement(  eO,              16.0*perCent );
+
+    //----------------------------------
+    // PC Baord 80% G10 circuit board, 20% generic electronics
+    //----------------------------------
+    auto mPCB = new G4Material( "PCB_Mat", 1.8*g/cm3, 7 );
+      mPCB -> AddMaterial( mG10, 80.0*perCent );
+      mPCB -> AddElement(  eSi,   8.0*perCent );
+      mPCB -> AddElement(  eCu,   6.0*perCent );
+      mPCB -> AddElement(  eAl,   3.0*perCent );
+      mPCB -> AddElement(  eFe,   1.0*perCent );
+      mPCB -> AddElement(  eSn,   1.0*perCent );
+      mPCB -> AddElement(  ePb,   1.0*perCent );
+
+    //----------------------------------
+    // SiPM (Hamamatsu S13361-3050AE-04)
+    //----------------------------------
+    // Bisphenol A which is the basis of each epoxy [G4SiPM toolkit].
+    auto mSiPM_Epoxy = new G4Material( "BisphenolA", 1.2*g/cm3, 3);
+      mSiPM_Epoxy -> AddElement( eSi, 15 );
+      mSiPM_Epoxy -> AddElement( eH,  16 );
+      mSiPM_Epoxy -> AddElement( eO,   2 );
+
+    auto mSiPM_Sensor = new G4Material( "SiPM_Sensor", 1.2*g/cm3, 5 ); // density is a guess
+      mSiPM_Sensor -> AddMaterial( mSiPM_Epoxy, 60.1*perCent );
+      mSiPM_Sensor -> AddElement( eSi, 36.9*perCent );
+      mSiPM_Sensor -> AddElement( eCu,  1.0*perCent );
+      mSiPM_Sensor -> AddElement( eSn,  1.0*perCent );
+      mSiPM_Sensor -> AddElement( ePb,  1.0*perCent );
+
+    auto mSiPM_PCB = new G4Material( "SiPM_PCB", 1.983*g/cm3, 5 );
+      mSiPM_PCB -> AddMaterial( mFR4, 94.0*perCent);
+      mSiPM_PCB -> AddElement( eFe,    1.0*perCent );
+      mSiPM_PCB -> AddElement( eCu,    3.0*perCent );
+      mSiPM_PCB -> AddElement( eSn,    1.0*perCent );
+      mSiPM_PCB -> AddElement( ePb,    1.0*perCent );
+
+    auto mSiPM = new G4Material( "SiPM_Mat", 4.0*g/cm3, 2 ); // density is a guess, sensor ~1g (1.3 cm x 1.3 cm x .135 cm)
+      mSiPM -> AddMaterial( mSiPM_PCB,    66.7*perCent );
+      mSiPM -> AddMaterial( mSiPM_Sensor, 33.3*perCent );
+
+    //----------------------------------
     // Gigahertz Optik ODM98 Optical Diffuse Material
     // http://www.gigahertz-optik.de/476-1-ODM98+Specification.html
+    //----------------------------------
     auto mODM = new G4Material( "ODM", 1.5*g/cm3, 2 );
       mODM -> AddElement( eC, 24.0183*perCent );
       mODM -> AddElement( eF, 75.9817*perCent );
 
+    //----------------------------------
+    // Optical Pad (EJ-560, guess it's Methyl phenyl silicone)
+    //----------------------------------
+    auto mOpticalPad = new G4Material( "OpticalPad_Mat", 1.03*g/cm3, 4 );
+      mOpticalPad -> AddElement( eC, 22 );
+      mOpticalPad -> AddElement( eH, 34 );
+      mOpticalPad -> AddElement( eSi, 4 );
+      mOpticalPad -> AddElement( eO,  3 );
+
+    //----------------------------------
+    // Peek (Polyether ether ketone, C19H14F2O3) wikipedia
+    //----------------------------------
+    auto mPEEK = new G4Material( "PEEK_Mat", 1.32*g/cm3, 4 );
+      mPEEK -> AddElement( eC, 19);
+      mPEEK -> AddElement( eH, 14);
+      mPEEK -> AddElement( eF,  2);
+      mPEEK -> AddElement( eO,  3);
+
+    //------------------------------------------------------
+    // Scintillators
+    //------------------------------------------------------
+    //----------------------------------
     // PLASTIC ( Nist G4_PLASTIC_SC_VINYLTOLUENE ? )
+    //----------------------------------
     auto mPlastic = nistManager->FindOrBuildMaterial( "G4_PLASTIC_SC_VINYLTOLUENE" );
       // auto birk = 0.0159*g/(cm2*MeV) / mPlastic->GetDensity();// Craun & Smith NIM 80 (1970)
       mPlastic -> GetIonisation() -> SetBirksConstant(0.154*mm/MeV); // original
 
+    //----------------------------------
     // CESIUM IODIDE ( Nist G4_CESIUM_IODIDE ? )
+    //----------------------------------
     auto mCsI = nistManager->FindOrBuildMaterial( "G4_CESIUM_IODIDE" );
       // auto birk = 0.0032*g/(cm2*MeV) / mCsI->GetDensity(); // Tretyak Astroparticl Physics 33 (2010)
       // auto birk = 0.0023*g/(cm2*MeV) / mCsI->GetDensity(); // Tretyak Astroparticl Physics 33 (2010)
       mCsI -> GetIonisation() -> SetBirksConstant(0.006*mm/MeV);
 
+    //----------------------------------
     // STILBENE  ( Nist G4_STILBENE ? )
+    //----------------------------------
     auto mStilbene = nistManager -> FindOrBuildMaterial( "G4_STILBENE" );
       // auto birk = 0.00955*g/(cm2*MeV) / mStilbene->GetDensity();// Craun & Smith NIM 80 (1970)
       // auto birk = 0.113*mm/MeV; // Papadopoulos NIM 401
       mStilbene -> GetIonisation() -> SetBirksConstant(0.098*mm/MeV);
     
+    //----------------------------------
     // p-TERPHENYL  ( Nist G4_TERPHENYL ? )
+    //----------------------------------
     auto mTerphenyl = nistManager -> FindOrBuildMaterial( "G4_TERPHENYL" );
       mTerphenyl -> GetIonisation() -> SetBirksConstant(0.098*mm/MeV); // needs updated
    
+    //----------------------------------
     // GAGG  ( Gd3Al2Ga3O12 )
+    //----------------------------------
     auto mGAGG = new G4Material( "GAGG", 6.67*g/cm3, 4 );
       mGAGG -> AddElement( eGa,  3 );
       mGAGG -> AddElement( eAl,  2 );
@@ -237,18 +319,19 @@ namespace grape
     //======================================================
     auto mVacuum = G4Material::GetMaterial("G4_Galactic");
     // auto mAir = G4Material::GetMaterial("G4_AIR");
-    auto mPb = G4Material::GetMaterial("G4_Pb");
-    auto mSn = G4Material::GetMaterial("G4_Sn");
-    
+    // auto mPb = G4Material::GetMaterial("G4_Pb");
+
     auto mAl6061 = G4Material::GetMaterial( "Aluminum6061" );
-    auto mPC = G4Material::GetMaterial( "PCmaterial" );
-    auto mConnector = G4Material::GetMaterial( "ConnectorMaterial" );
-    auto mSiPM = G4Material::GetMaterial( "PMTmaterial" );
+    auto mPCB = G4Material::GetMaterial( "PCB_Mat" );
+    auto mConnector = G4Material::GetMaterial( "Connector_Mat" );
+    auto mSiPM = G4Material::GetMaterial( "SiPM_Mat" );
+    auto mPEEK = G4Material::GetMaterial( "PEEK_Mat" );
+    auto mOPad = G4Material::GetMaterial( "OpticalPad_Mat" );
     auto mODM = G4Material::GetMaterial( "ODM" );
-    auto mOPad = G4Material::GetMaterial( "G4_Si" );
 
     auto mScintC = G4Material::GetMaterial("GAGG");
     auto mScintS = G4Material::GetMaterial("G4_TERPHENYL");
+    auto mScintCal = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
 
     //======================================================
     // Volumes
@@ -287,8 +370,6 @@ namespace grape
     //------------------------------------------------------
     // Instrument
     //------------------------------------------------------
-
-    
     //----------------------------------
     // Module
     //----------------------------------
@@ -312,15 +393,12 @@ namespace grape
     // PHYSICAL VOLUME
     // auto mod_Xpos = 0.0*mm;
     auto mod_Xpos = 0.0*mm;
-    auto mod_Ypos = (kENCL_Side1_Zsize/2 - kScint_Zsize/2)*std::sin( fZenithAngle );
-    auto mod_Zpos = mod_Z/2*std::cos( fZenithAngle ) + mod_X/2*(std::cos( fAzimuthAngle ) + std::sin( fAzimuthAngle ))*std::sin( fZenithAngle );
+    auto mod_Ypos = 0.0*mm;
+    auto mod_Zpos = 0.0*mm;
     auto mod_Pos = G4ThreeVector( mod_Xpos, mod_Ypos, mod_Zpos );
-    auto mod_RotMat = new G4RotationMatrix();
-    mod_RotMat -> setTheta( fZenithAngle );
-    mod_RotMat -> setPsi( fAzimuthAngle );
 
-    fPhysicalModule = new G4PVPlacement(
-                  mod_RotMat,           // its rotation
+    new G4PVPlacement(
+                  0,                    // its rotation
                   mod_Pos,              // its position
                   module_LV,            // its logical volume
                   "Module_PV",          // its name
@@ -329,79 +407,6 @@ namespace grape
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 
 
-    //----------------------------------
-    // Base Shield - Lead 
-    //----------------------------------
-    // Solid Volume
-    auto SHPB_Bot_X = kSHPB_Bot_Xsize;
-    auto SHPB_Bot_Y = kSHPB_Bot_Ysize;
-    auto SHPB_Bot_Z = kSHPB_Bot_Zsize;
-
-    auto SHPB_Bot_S = new G4Box(
-                  "SHPB_Bot_S",         // its name
-                  SHPB_Bot_X/2,         // its X dimension 
-                  SHPB_Bot_Y/2,         // its Y dimension
-                  SHPB_Bot_Z/2);        // its Z dimension
-    
-    // Logical Volume
-    auto SHPB_Bot_LV = new G4LogicalVolume(
-                  SHPB_Bot_S,           // its solid
-                  mPb,                  // its material
-                  "SHPB_Bot_LV");       // its name
-
-    // Pysical Volume
-    auto SHPB_Bot_Xpos = 0.0*mm;
-    auto SHPB_Bot_Ypos = 0.0*mm;
-    auto SHPB_Bot_Zpos = -mod_Z/2 + SHPB_Bot_Z/2;
-    auto SHPB_Bot_Pos = G4ThreeVector( SHPB_Bot_Xpos, SHPB_Bot_Ypos, SHPB_Bot_Zpos );
-
-    new G4PVPlacement(
-                  0,                    // its rotation
-                  SHPB_Bot_Pos,         // its position
-                  SHPB_Bot_LV,          // its logical volume
-                  "SHPB_Bot_PV",        // its name
-                  module_LV,            // its mother  volume
-                  false,                // no boolean operation
-                  0,                    // copy number
-                  fCheckOverlaps);      // checking overlaps 
-
-    //----------------------------------
-    // Base Shield - Tin 
-    //----------------------------------
-    // Solid Volume
-    auto SHSN_Bot_X = kSHSN_Bot_Xsize;
-    auto SHSN_Bot_Y = kSHSN_Bot_Ysize;
-    auto SHSN_Bot_Z = kSHSN_Bot_Zsize;
-
-    auto SHSN_Bot_S = new G4Box(
-                  "SHSN_Bot_S",         // its name
-                  SHSN_Bot_X/2,         // its X dimension 
-                  SHSN_Bot_Y/2,         // its Y dimension
-                  SHSN_Bot_Z/2);        // its Z dimension
-    
-    // Logical Volume
-    auto SHSN_Bot_LV = new G4LogicalVolume(
-                  SHSN_Bot_S,           // its solid
-                  mSn,                  // its material
-                  "SHSN_Bot_LV");       // its name
-
-    // Pysical Volume
-    auto SHSN_Bot_Xpos = 0.0*mm;
-    auto SHSN_Bot_Ypos = 0.0*mm;
-    auto SHSN_Bot_Zpos = -mod_Z/2 + SHPB_Bot_Z + SHSN_Bot_Z/2;
-    auto SHSN_Bot_Pos = G4ThreeVector( SHSN_Bot_Xpos, SHSN_Bot_Ypos, SHSN_Bot_Zpos );
-
-    new G4PVPlacement(
-                  0,                    // its rotation
-                  SHSN_Bot_Pos,         // its position
-                  SHSN_Bot_LV,          // its logical volume
-                  "SHSN_Bot_PV",        // its name
-                  module_LV,            // its mother  volume
-                  false,                // no boolean operation
-                  0,                    // copy number
-                  fCheckOverlaps);      // checking overlaps 
-
-
         
     //----------------------------------
     // Base Plate
@@ -426,7 +431,7 @@ namespace grape
     // Pysical Volume
     auto ENCL_Bot_Xpos = 0.0*mm;
     auto ENCL_Bot_Ypos = 0.0*mm;
-    auto ENCL_Bot_Zpos = -mod_Z/2 + SHPB_Bot_Z + SHSN_Bot_Z + ENCL_Bot_Z/2;
+    auto ENCL_Bot_Zpos = -mod_Z/2 + ENCL_Bot_Z/2;
     auto ENCL_Bot_Pos = G4ThreeVector( ENCL_Bot_Xpos, ENCL_Bot_Ypos, ENCL_Bot_Zpos );
 
     new G4PVPlacement(
@@ -439,112 +444,6 @@ namespace grape
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 
 
-
-    //----------------------------------
-    // Side1 Shield - Lead
-    //----------------------------------
-    // Solid Volume
-    auto SHPB_Side1_X = kSHPB_Side1_Xsize;
-    auto SHPB_Side1_Y = kSHPB_Side1_Ysize;
-    auto SHPB_Side1_Z = kSHPB_Side1_Zsize;
-
-    auto SHPB_Side1_S = new G4Box(
-                  "SHPB_Side1_S",       // its name
-                  SHPB_Side1_X/2,       // its X dimension 
-                  SHPB_Side1_Y/2,       // its Y dimension
-                  SHPB_Side1_Z/2);      // its Z dimension
-    
-    // Logical Volume
-    auto SHPB_Side1_LV = new G4LogicalVolume(
-                  SHPB_Side1_S,         // its solid
-                  mPb,              // its material
-                  "SHPB_Side1_LV");     // its name
-
-    // Pysical Volume
-    auto SHPB_Side1_Xpos = 0.0*mm;
-    auto SHPB_Side1_Ypos = 0.0*mm;
-    auto SHPB_Side1_Zpos = SHPB_Bot_Zpos - SHPB_Bot_Z/2 + SHPB_Side1_Z/2;
-    auto SHPB_Side1_Pos = G4ThreeVector();
-
-    SHPB_Side1_Xpos = SHPB_Bot_X/2 + SHPB_Side1_X/2;
-    SHPB_Side1_Pos = G4ThreeVector( SHPB_Side1_Xpos, SHPB_Side1_Ypos, SHPB_Side1_Zpos );
-
-    new G4PVPlacement(
-                  0,                    // its rotation
-                  SHPB_Side1_Pos,       // its position
-                  SHPB_Side1_LV,        // its logical volume
-                  "SHPB_Side1_PV",      // its name
-                  module_LV,            // its mother  volume
-                  false,                // no boolean operation
-                  0,                    // copy number
-                  fCheckOverlaps);      // checking overlaps 
-
-    SHPB_Side1_Xpos = -SHPB_Bot_X/2 - SHPB_Side1_X/2;
-    SHPB_Side1_Pos = G4ThreeVector( SHPB_Side1_Xpos, SHPB_Side1_Ypos, SHPB_Side1_Zpos );
-
-    new G4PVPlacement(
-                  0,                    // its rotation
-                  SHPB_Side1_Pos,       // its position
-                  SHPB_Side1_LV,        // its logical volume
-                  "SHPB_Side1_PV",      // its name
-                  module_LV,            // its mother  volume
-                  false,                // no boolean operation
-                  0,                    // copy number
-                  fCheckOverlaps);      // checking overlaps 
-
-    //----------------------------------
-    // Side1 Shield - Tin
-    //----------------------------------
-    // Solid Volume
-    auto SHSN_Side1_X = kSHSN_Side1_Xsize;
-    auto SHSN_Side1_Y = kSHSN_Side1_Ysize;
-    auto SHSN_Side1_Z = kSHSN_Side1_Zsize;
-
-    auto SHSN_Side1_S = new G4Box(
-                  "SHSN_Side1_S",       // its name
-                  SHSN_Side1_X/2,       // its X dimension 
-                  SHSN_Side1_Y/2,       // its Y dimension
-                  SHSN_Side1_Z/2);      // its Z dimension
-    
-    // Logical Volume
-    auto SHSN_Side1_LV = new G4LogicalVolume(
-                  SHSN_Side1_S,         // its solid
-                  mPb,              // its material
-                  "SHSN_Side1_LV");     // its name
-
-    // Pysical Volume
-    auto SHSN_Side1_Xpos = 0.0*mm;
-    auto SHSN_Side1_Ypos = 0.0*mm;
-    auto SHSN_Side1_Zpos = SHSN_Bot_Zpos - SHSN_Bot_Z/2 + SHSN_Side1_Z/2;
-    auto SHSN_Side1_Pos = G4ThreeVector();
-
-    SHSN_Side1_Xpos = SHSN_Bot_X/2 + SHSN_Side1_X/2;
-    SHSN_Side1_Pos = G4ThreeVector( SHSN_Side1_Xpos, SHSN_Side1_Ypos, SHSN_Side1_Zpos );
-
-    new G4PVPlacement(
-                  0,                    // its rotation
-                  SHSN_Side1_Pos,       // its position
-                  SHSN_Side1_LV,        // its logical volume
-                  "SHSN_Side1_PV",      // its name
-                  module_LV,            // its mother  volume
-                  false,                // no boolean operation
-                  0,                    // copy number
-                  fCheckOverlaps);      // checking overlaps 
-
-    SHSN_Side1_Xpos = -SHSN_Bot_X/2 - SHSN_Side1_X/2;
-    SHSN_Side1_Pos = G4ThreeVector( SHSN_Side1_Xpos, SHSN_Side1_Ypos, SHSN_Side1_Zpos );
-
-    new G4PVPlacement(
-                  0,                    // its rotation
-                  SHSN_Side1_Pos,       // its position
-                  SHSN_Side1_LV,        // its logical volume
-                  "SHSN_Side1_PV",      // its name
-                  module_LV,            // its mother  volume
-                  false,                // no boolean operation
-                  0,                    // copy number
-                  fCheckOverlaps);      // checking overlaps 
-
-
     //----------------------------------
     // Side1 Plate
     //----------------------------------
@@ -597,114 +496,6 @@ namespace grape
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 
 
-
-    //----------------------------------
-    // Side2 Shield - Lead
-    //----------------------------------
-    // Solid Volume
-    auto SHPB_Side2_X = kSHPB_Side2_Xsize;
-    auto SHPB_Side2_Y = kSHPB_Side2_Ysize;
-    auto SHPB_Side2_Z = kSHPB_Side2_Zsize;
-
-    auto SHPB_Side2_S = new G4Box(
-                  "SHPB_Side2_S",       // its name
-                  SHPB_Side2_X/2,       // its X dimension 
-                  SHPB_Side2_Y/2,       // its Y dimension
-                  SHPB_Side2_Z/2);      // its Z dimension
-    
-    // Logical Volume
-    auto SHPB_Side2_LV = new G4LogicalVolume(
-                  SHPB_Side2_S,         // its solid
-                  mPb,              // its material
-                  "SHPB_Side2_LV");     // its name
-
-    // Pysical Volume
-    auto SHPB_Side2_Xpos = 0.0*mm;
-    auto SHPB_Side2_Ypos = 0.0*mm;
-    auto SHPB_Side2_Zpos = SHPB_Bot_Zpos - SHPB_Bot_Z/2 + SHPB_Side2_Z/2;
-    auto SHPB_Side2_Pos = G4ThreeVector();
-
-    SHPB_Side2_Ypos = SHPB_Bot_Y/2 + SHPB_Side2_Y/2;
-    SHPB_Side2_Pos = G4ThreeVector( SHPB_Side2_Xpos, SHPB_Side2_Ypos, SHPB_Side2_Zpos );
-
-    new G4PVPlacement(
-                  0,                    // its rotation
-                  SHPB_Side2_Pos,       // its position
-                  SHPB_Side2_LV,        // its logical volume
-                  "SHPB_Side2_PV",      // its name
-                  module_LV,            // its mother  volume
-                  false,                // no boolean operation
-                  0,                    // copy number
-                  fCheckOverlaps);      // checking overlaps 
-
-    SHPB_Side2_Ypos = -SHPB_Bot_Y/2 - SHPB_Side2_Y/2;
-    SHPB_Side2_Pos = G4ThreeVector( SHPB_Side2_Xpos, SHPB_Side2_Ypos, SHPB_Side2_Zpos );
-
-    new G4PVPlacement(
-                  0,                    // its rotation
-                  SHPB_Side2_Pos,       // its position
-                  SHPB_Side2_LV,        // its logical volume
-                  "SHPB_Side2_PV",      // its name
-                  module_LV,            // its mother  volume
-                  false,                // no boolean operation
-                  0,                    // copy number
-                  fCheckOverlaps);      // checking overlaps 
-
-
-    //----------------------------------
-    // Side2 Shield - Tin
-    //----------------------------------
-    // Solid Volume
-    auto SHSN_Side2_X = kSHSN_Side2_Xsize;
-    auto SHSN_Side2_Y = kSHSN_Side2_Ysize;
-    auto SHSN_Side2_Z = kSHSN_Side2_Zsize;
-
-    auto SHSN_Side2_S = new G4Box(
-                  "SHSN_Side2_S",       // its name
-                  SHSN_Side2_X/2,       // its X dimension 
-                  SHSN_Side2_Y/2,       // its Y dimension
-                  SHSN_Side2_Z/2);      // its Z dimension
-    
-    // Logical Volume
-    auto SHSN_Side2_LV = new G4LogicalVolume(
-                  SHSN_Side2_S,         // its solid
-                  mPb,              // its material
-                  "SHSN_Side2_LV");     // its name
-
-    // Pysical Volume
-    auto SHSN_Side2_Xpos = 0.0*mm;
-    auto SHSN_Side2_Ypos = 0.0*mm;
-    auto SHSN_Side2_Zpos = SHSN_Bot_Zpos - SHSN_Bot_Z/2 + SHSN_Side2_Z/2;
-    auto SHSN_Side2_Pos = G4ThreeVector();
-
-    SHSN_Side2_Ypos = SHSN_Bot_Y/2 + SHSN_Side2_Y/2;
-    SHSN_Side2_Pos = G4ThreeVector( SHSN_Side2_Xpos, SHSN_Side2_Ypos, SHSN_Side2_Zpos );
-
-    new G4PVPlacement(
-                  0,                    // its rotation
-                  SHSN_Side2_Pos,       // its position
-                  SHSN_Side2_LV,        // its logical volume
-                  "SHSN_Side2_PV",      // its name
-                  module_LV,            // its mother  volume
-                  false,                // no boolean operation
-                  0,                    // copy number
-                  fCheckOverlaps);      // checking overlaps 
-
-    SHSN_Side2_Ypos = -SHSN_Bot_Y/2 - SHSN_Side2_Y/2;
-    SHSN_Side2_Pos = G4ThreeVector( SHSN_Side2_Xpos, SHSN_Side2_Ypos, SHSN_Side2_Zpos );
-
-    new G4PVPlacement(
-                  0,                    // its rotation
-                  SHSN_Side2_Pos,       // its position
-                  SHSN_Side2_LV,        // its logical volume
-                  "SHSN_Side2_PV",      // its name
-                  module_LV,            // its mother  volume
-                  false,                // no boolean operation
-                  0,                    // copy number
-                  fCheckOverlaps);      // checking overlaps 
-
-
-
     //----------------------------------
     // Side2 Plate
     //----------------------------------
@@ -829,7 +620,7 @@ namespace grape
     // Logical Volume
     auto APB_LV = new G4LogicalVolume(
                   APB_S,                // its solid
-                  mPC,                  // its material
+                  mPCB,                 // its material
                   "APB_LV");            // its name
 
     auto APB_Xnum = kNumScint_X;
@@ -914,7 +705,7 @@ namespace grape
     // Logical Volume     
     auto MIB_LV = new G4LogicalVolume(
                   MIB_S,                // its solid
-                  mPC,                  // its material
+                  mPCB,                 // its material
                   "MIB_LV");            // its name
 
     auto MIB_Xpos = 0.0*mm;
@@ -1013,9 +804,14 @@ namespace grape
                   mVacuum,              // its material
                   "DetColumn_LV");      // its name
 
+    auto detColumn_Cal_LV = new G4LogicalVolume(
+                  detColumn_S,          // its solid
+                  mVacuum,              // its material
+                  "DetColumn_LV");      // its name
+
     // PHYSICAL VOLUME
-    auto offsetX = ( kScint_Xpitch * (kNumScint_X-1) / 2 );
-    auto offsetY = ( kScint_Ypitch * (kNumScint_Y-1) / 2 );
+    auto detColumn_offsetX = ( kScint_Xpitch * (kNumScint_X-1) / 2 );
+    auto detColumn_offsetY = ( kScint_Ypitch * (kNumScint_Y-1) / 2 );
     auto detColumn_Xpos = 0.0*mm;
     auto detColumn_Ypos = 0.0*mm;
     auto detColumn_Zpos = MIB_Zpos + MIB_Z/2 + detColumn_Z/2;
@@ -1026,15 +822,33 @@ namespace grape
     auto copyNum = 0;
     for (auto col = 0; col<kNumScint_Y; col++) {
       for (auto row = 0; row<kNumScint_X; row++) {
-        detColumn_Xpos =  ( row * kScint_Xpitch ) - offsetX;
-        detColumn_Ypos = -( col * kScint_Ypitch ) + offsetY;
+        detColumn_Xpos =  ( row * kScint_Xpitch ) - detColumn_offsetX;
+        detColumn_Ypos = -( col * kScint_Ypitch ) + detColumn_offsetY;
 
         detColumn_Pos = G4ThreeVector( detColumn_Xpos, detColumn_Ypos, detColumn_Zpos );
 
         // G4cout << "----> Copy Number: " << copyNum;
-        // G4cout << " (" << det_Xpos << ", " << det_Ypos << ")" << G4endl;
+        // G4cout << " (" << detColumn_Xpos << ", " << detColumn_Ypos << ")" << G4endl;
+
+        if ( copyNum == 24 ) { // Calibration
+          new G4PVPlacement(
+                  0,                    // its rotation
+                  detColumn_Pos,        // its position
+                  detColumn_Cal_LV,     // its logical volume
+                  "DetColumn_PV",       // its name
+                  module_LV,            // its mother  volume
+                  false,                // no boolean operation
+                  copyNum,              // copy number
+                  fCheckOverlaps);      // checking overlaps 
 
-        if ( (row == 0) || (row == kNumScint_X-1) ) { // Calorimeter
+          G4cout << "Cal ";
+          G4cout << "Calibration Element: ";
+          G4cout << " (" << copyNum << ", " << detColumn_Xpos << ", " << detColumn_Ypos << ")" << G4endl;
+
+          copyNum++;
+        }
+
+        else if ( (row == 0) || (row == kNumScint_X-1) ) { // Calorimeter
           new G4PVPlacement(
                   0,                    // its rotation
                   detColumn_Pos,        // its position
@@ -1143,6 +957,16 @@ namespace grape
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 
 
+    new G4PVPlacement(
+                  0,                    // its rotation
+                  MIBP_Pos,             // its position
+                  MIBP_LV,              // its logical volume
+                  "MIB_Plate_PV",       // its name
+                  detColumn_Cal_LV,     // its mother  volume
+                  false,                // no boolean operation
+                  0,                    // copy number
+                  fCheckOverlaps);      // checking overlaps 
+
     //----------------------------------
     // Scintillator Case
     //----------------------------------
@@ -1181,7 +1005,7 @@ namespace grape
     // Logical Volume
     auto SCINT_Case_LV = new G4LogicalVolume(
                   SCINT_Case_S,         // its solid
-                  mODM,                 // its material
+                  mPEEK,                // its material
                   "Scint_Case_LV");     // its name
 
     // Physical Volume
@@ -1210,6 +1034,16 @@ namespace grape
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 
 
+    new G4PVPlacement(
+                  0,                    // its rotation
+                  SCINT_Case_Pos,       // its position
+                  SCINT_Case_LV,        // its logical volume
+                  "Scint_Case_PV",      // its name
+                  detColumn_Cal_LV,       // its mother  volume
+                  false,                // no boolean operation
+                  0,                    // copy number
+                  fCheckOverlaps);      // checking overlaps 
+
     //----------------------------------
     // Scintillator Case Bot
     //----------------------------------
@@ -1237,7 +1071,7 @@ namespace grape
     // Logical Volume
     auto SCINT_Case_Bot_LV = new G4LogicalVolume(
                   SCINT_Case_Bot_S,     // its solid
-                  mODM,                 // its material
+                  mPEEK,                // its material
                   "Scint_Case_Bot_LV"); // its name
 
     // Physical Volume
@@ -1266,6 +1100,16 @@ namespace grape
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 
 
+    new G4PVPlacement(
+                  0,                    // its rotation
+                  SCINT_Case_Bot_Pos,   // its position
+                  SCINT_Case_Bot_LV,    // its logical volume
+                  "Scint_Case_Bot_PV",  // its name
+                  detColumn_Cal_LV,       // its mother  volume
+                  false,                // no boolean operation
+                  0,                    // copy number
+                  fCheckOverlaps);      // checking overlaps 
+
     //----------------------------------
     // Scintillator Case Top
     //----------------------------------
@@ -1293,7 +1137,7 @@ namespace grape
     // Logical Volume
     auto SCINT_Case_Top_LV = new G4LogicalVolume(
                   SCINT_Case_Top_S,     // its solid
-                  mODM,                 // its material
+                  mPEEK,                // its material
                   "Scint_Case_Top_LV"); // its name
 
     // Physical Volume
@@ -1322,6 +1166,16 @@ namespace grape
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 
 
+    new G4PVPlacement(
+                  0,                    // its rotation
+                  SCINT_Case_Top_Pos,   // its position
+                  SCINT_Case_Top_LV,    // its logical volume
+                  "Scint_Case_Top_PV",  // its name
+                  detColumn_Cal_LV,       // its mother  volume
+                  false,                // no boolean operation
+                  0,                    // copy number
+                  fCheckOverlaps);      // checking overlaps 
+
     //----------------------------------
     // Enclosure Top/Support Frame
     //----------------------------------
@@ -1388,6 +1242,16 @@ namespace grape
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 
 
+    new G4PVPlacement(
+                  0,                    // its rotation
+                  ENCL_Top_Pos,         // its position
+                  ENCL_Top_LV,          // its logical volume
+                  "ENCL_Top_PV",        // its name
+                  detColumn_Cal_LV,       // its mother  volume
+                  false,                // no boolean operation
+                  0,                    // copy number
+                  fCheckOverlaps);      // checking overlaps 
+
     //----------------------------------
     // Detector Element
     //----------------------------------
@@ -1413,6 +1277,11 @@ namespace grape
                   mVacuum,               // its material
                   "DetElement_LV");      // its name
 
+    auto detElement_Cal_LV = new G4LogicalVolume(
+                  detElement_S,          // its solid
+                  mVacuum,               // its material
+                  "DetElement_LV");      // its name
+
     // PHYSICAL VOLUME
     auto detElement_Xpos = 0.0*mm;
     auto detElement_Ypos = 0.0*mm;
@@ -1427,8 +1296,8 @@ namespace grape
 
       detElement_Pos = G4ThreeVector( detElement_Xpos, detElement_Ypos, detElement_Zpos );
 
-      G4cout << "----> Copy Number: " << copyNum;
-      G4cout << " (" << detElement_Xpos << ", " << detElement_Ypos << ", " << detElement_Zpos << ")" << G4endl;
+      // G4cout << "----> Copy Number: " << copyNum;
+      // G4cout << " (" << detElement_Xpos << ", " << detElement_Ypos << ", " << detElement_Zpos << ")" << G4endl;
 
       new G4PVPlacement(
                   0,                    // its rotation
@@ -1448,8 +1317,8 @@ namespace grape
 
       detElement_Pos = G4ThreeVector( detElement_Xpos, detElement_Ypos, detElement_Zpos );
 
-      G4cout << "----> Copy Number: " << copyNum;
-      G4cout << " (" << detElement_Xpos << ", " << detElement_Ypos << ", " << detElement_Zpos << ")" << G4endl;
+      // G4cout << "----> Copy Number: " << copyNum;
+      // G4cout << " (" << detElement_Xpos << ", " << detElement_Ypos << ", " << detElement_Zpos << ")" << G4endl;
 
       if (ele < kNumScint_Z-1) {
         new G4PVPlacement(
@@ -1477,6 +1346,53 @@ namespace grape
       }
     }
 
+    copyNum = 0;
+    for (auto ele = 0; ele<kNumScint_Z; ele++) {
+      detElement_Zpos = SCINT_Case_Top_Zpos + SCINT_Case_Top_Z/2 - kScint_Case_Thickness/2 - ele * detElement_Z - detElement_Z/2;
+
+      detElement_Pos = G4ThreeVector( detElement_Xpos, detElement_Ypos, detElement_Zpos );
+
+      // G4cout << "----> Copy Number: " << copyNum;
+      // G4cout << " (" << detElement_Xpos << ", " << detElement_Ypos << ", " << detElement_Zpos << ")" << G4endl;
+
+      if (ele == 3) {
+        new G4PVPlacement(
+                  0,                    // its rotation
+                  detElement_Pos,       // its position
+                  detElement_Cal_LV,      // its logical volume
+                  "DetElement_PV",      // its name
+                  detColumn_Cal_LV,       // its mother  volume
+                  false,                // no boolean operation
+                  copyNum,              // copy number
+                  fCheckOverlaps);      // checking overlaps 
+        copyNum++;
+      }
+      else if (ele < kNumScint_Z-1) {
+        new G4PVPlacement(
+                  0,                    // its rotation
+                  detElement_Pos,       // its position
+                  detElement_S_LV,      // its logical volume
+                  "DetElement_PV",      // its name
+                  detColumn_Cal_LV,       // its mother  volume
+                  false,                // no boolean operation
+                  copyNum,              // copy number
+                  fCheckOverlaps);      // checking overlaps 
+        copyNum++;
+      }
+      else {
+        new G4PVPlacement(
+                  0,                    // its rotation
+                  detElement_Pos,       // its position
+                  detElement_C_LV,      // its logical volume
+                  "DetElement_PV",      // its name
+                  detColumn_Cal_LV,       // its mother  volume
+                  false,                // no boolean operation
+                  copyNum,              // copy number
+                  fCheckOverlaps);      // checking overlaps 
+        copyNum++;
+      }
+    }
+
     //----------------------------------
     // Scintillator
     //----------------------------------
@@ -1529,25 +1445,125 @@ namespace grape
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 
 
+    //----------------------------------
+    // Calibration Source Housing
+    //----------------------------------
+    // SOLID VOLUME
+    auto calHouse_X = kScint_Xsize;
+    auto calHouse_Y = kScint_Ysize;
+    auto calHouse_Z = kScint_Zsize;
+
+    G4VSolid* calHouse_S = new G4Box(
+                  "CalHouse_S",         // its name
+                  calHouse_X/2,         // its X dimension
+                  calHouse_Y/2,         // its Y dimension
+                  calHouse_Z/2);        // its Z dimension
+
+    // Hole
+    auto calHouse_Hole_Rmin = kCal_Rmin;
+    auto calHouse_Hole_Rmax = kCal_Rmax;
+    auto calHouse_Hole_Z = kCal_Zsize;
+
+    auto calHouse_Hole_S = new G4Tubs(
+                  "CalHouse_Hole_S",    // its name
+                  calHouse_Hole_Rmin,   // its minimum radius 
+                  calHouse_Hole_Rmax,   // its maximum radius
+                  calHouse_Hole_Z/2,    // its Z dimension
+                  0.*deg,               // its starting segment angle
+                  360.*deg);            // its ending segment angle
+
+    auto calHouse_Hole_Xpos = 0.0*mm;
+    auto calHouse_Hole_Ypos = 0.0*mm;
+    auto calHouse_Hole_Zpos = calHouse_Hole_Z/2 - calHouse_Z/2;
+    auto calHouse_Hole_pos = G4ThreeVector( calHouse_Hole_Xpos, calHouse_Hole_Ypos, calHouse_Hole_Zpos );
+    calHouse_S = new G4SubtractionSolid( 
+                  "calHouse_S",         // its name
+                  calHouse_S,           // starting solid
+                  calHouse_Hole_S,      // solid to be subtracted
+                  0,                    // its rotation
+                  calHouse_Hole_pos );  // its position
+
+
+    // LOGICAL VOLUME
+    auto calHouse_LV = new G4LogicalVolume(
+                  calHouse_S,           // its solid
+                  mODM,                 // its material
+                  "CalHouse_LV");       // its name
+
+    // PHYSICAL VOLUME
+    auto calHouse_Xpos = 0.0*mm;
+    auto calHouse_Ypos = 0.0*mm;
+    auto calHouse_Zpos = detElement_Z/2 - calHouse_Z/2;
+    auto calHouse_Pos = G4ThreeVector( calHouse_Xpos, calHouse_Ypos, calHouse_Zpos );
+
+    new G4PVPlacement(
+                  0,                    // its rotation
+                  calHouse_Pos,         // its position
+                  calHouse_LV,          // its logical volume
+                  "CalHouse_PV",        // its name
+                  detElement_Cal_LV,    // its mother  volume
+                  false,                // no boolean operation
+                  0,                    // copy number
+                  fCheckOverlaps);      // checking overlaps 
+
+    //----------------------------------
+    // Calibration Source
+    //----------------------------------
+    // SOLID VOLUME
+    auto cal_Rmin = kCal_Rmin;
+    auto cal_Rmax = kCal_Rmax;
+    auto cal_Z    = kCal_Zsize;
+
+    auto cal_S = new G4Tubs(
+                  "Cal_S",              // its name
+                  cal_Rmin,             // its minimum radius 
+                  cal_Rmax,             // its maximum radius
+                  cal_Z/2,              // its Z dimension
+                  0.*deg,               // its starting segment angle
+                  360.*deg);            // its ending segment angle
+
+    // LOGICAL VOLUME
+    auto cal_LV = new G4LogicalVolume(
+                  cal_S,              // its solid
+                  mScintCal,            // its material
+                  "Cal_LV");            // its name
+
+    // PHYSICAL VOLUME
+    auto cal_Xpos = 0.0*mm;
+    auto cal_Ypos = 0.0*mm;
+    auto cal_Zpos = calHouse_Zpos - calHouse_Z/2 + cal_Z/2 ;
+    // auto cal_Zpos = scint_Zpos - scint_Z/2 + cal_Z/2;
+    auto cal_Pos = G4ThreeVector( cal_Xpos, cal_Ypos, cal_Zpos );
+
+    new G4PVPlacement(
+                  0,                    // its rotation
+                  cal_Pos,              // its position
+                  cal_LV,               // its logical volume
+                  "Cal_PV",             // its name
+                  detElement_Cal_LV,    // its mother  volume
+                  false,                // no boolean operation
+                  0,                    // copy number
+                  fCheckOverlaps);      // checking overlaps 
+
     //----------------------------------
     // Optical Pad
     //----------------------------------
     // Solid Volume
     auto OPad_X = kOpticalPad_Xsize;
     auto OPad_Y = kOpticalPad_Ysize;
-    auto OPad_Z = kOpticalPad_Zsize;
+    auto OPad_Z    = kOpticalPad_Zsize;
 
     auto OPad_S = new G4Box(
-                  "OPad_S",              // its name
-                  OPad_X/2,              // its X dimension
-                  OPad_Y/2,              // its Y dimension
-                  OPad_Z/2);             // its Z dimension
+                  "OPad_S",             // its name
+                  OPad_X/2,             // its X dimension
+                  OPad_Y/2,             // its Y dimension
+                  OPad_Z/2);            // its Z dimension
                           
     // Logical Volume
     auto OPad_LV = new G4LogicalVolume(
-                  OPad_S,                // its solid
-                  mOPad,                 // its material
-                  "OPad_LV");            // its name
+                  OPad_S,               // its solid
+                  mOPad,                // its material
+                  "OPad_LV");           // its name
 
     // Physical Volume
     auto OPad_Xpos = 0.0*mm;
@@ -1575,25 +1591,35 @@ namespace grape
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 
 
+    new G4PVPlacement(
+                  0,                    // its rotation
+                  OPad_Pos,             // its position
+                  OPad_LV,              // its logical volume
+                  "OPad_PV",            // its name
+                  detElement_Cal_LV,      // its mother  volume
+                  false,                // no boolean operation
+                  0,                    // copy number
+                  fCheckOverlaps);      // checking overlaps 
+
     //----------------------------------
     // SiPM
     //----------------------------------
     // Solid Volume
     auto SiPM_X = kSiPM_Xsize;
     auto SiPM_Y = kSiPM_Ysize;
-    auto SiPM_Z = kSiPM_Zsize;
+    auto SiPM_Z    = kSiPM_Zsize;
 
     auto SiPM_S = new G4Box(
-                  "SiPM_S",              // its name
-                  SiPM_X/2,              // its X dimension
-                  SiPM_Y/2,              // its Y dimension
-                  SiPM_Z/2);             // its Z dimension
+                  "SiPM_S",             // its name
+                  SiPM_X/2,             // its X dimension
+                  SiPM_Y/2,             // its Y dimension
+                  SiPM_Z/2);            // its Z dimension
                           
     // Logical Volume
     auto SiPM_LV = new G4LogicalVolume(
-                  SiPM_S,                // its solid
-                  mSiPM,                 // its material
-                  "SiPM_LV");            // its name
+                  SiPM_S,               // its solid
+                  mSiPM,                // its material
+                  "SiPM_LV");           // its name
 
     // Physical Volume
     auto SiPM_Xpos = 0.0*mm;
@@ -1621,6 +1647,16 @@ namespace grape
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 
 
+    new G4PVPlacement(
+                  0,                    // its rotation
+                  SiPM_Pos,             // its position
+                  SiPM_LV,              // its logical volume
+                  "SiPM_PV",            // its name
+                  detElement_Cal_LV,      // its mother  volume
+                  false,                // no boolean operation
+                  0,                    // copy number
+                  fCheckOverlaps);      // checking overlaps 
+
 
     //----------------------------------
     // SiPM PCB
@@ -1631,16 +1667,16 @@ namespace grape
     auto SiPM_PCB_Z = kSiPM_PCB_Zsize;
 
     auto SiPM_PCB_S = new G4Box(
-                  "SiPM_PCB_S",          // its name
-                  SiPM_PCB_X/2,          // its X dimension 
-                  SiPM_PCB_Y/2,          // its Y dimension
-                  SiPM_PCB_Z/2);         // its Z dimension
+                  "SiPM_PCB_S",         // its name
+                  SiPM_PCB_X/2,         // its X dimension 
+                  SiPM_PCB_Y/2,         // its Y dimension
+                  SiPM_PCB_Z/2);        // its Z dimension
                           
     // Logical Volume
     auto SiPM_PCB_LV = new G4LogicalVolume(
-                  SiPM_PCB_S,            // its solid
-                  mPC,                   // its material
-                  "SiPM_PCB_LV");        // its name
+                  SiPM_PCB_S,           // its solid
+                  mPCB,                 // its material
+                  "SiPM_PCB_LV");       // its name
 
     // Physical Volume
     auto SiPM_PCB_Xpos = 0.0*mm;
@@ -1672,21 +1708,47 @@ namespace grape
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 
 
+    new G4PVPlacement(
+                  0,                    // its rotation
+                  SiPM_PCB_Pos,         // its position
+                  SiPM_PCB_LV,          // its logical volume
+                  "SiPM_PCB_PV",        // its name
+                  detElement_Cal_LV,      // its mother  volume
+                  false,                // no boolean operation
+                  0,                    // copy number
+                  fCheckOverlaps);      // checking overlaps 
+
     //======================================================
     // Visualization attributes
     //======================================================
+    G4Color red(0.9843, 0.0000, 0.0275, 1.0);
+    G4Color red_orange(0.9843, 0.3098, 0.0275, 1.0);
+    G4Color orange(0.9843, 0.5294, 0.0314, 1.0);
+    G4Color yellow_orange(0.9922, 0.7647, 0.0353, 1.0);
+    G4Color yellow(0.9922, 1.0000, 0.0431, 1.0);
+    G4Color yellow_green(0.3412, 0.7725, 0.0235, 1.0);
+    G4Color green(0.0745, 0.5412, 0.0118, 1.0);
+    G4Color blue_green(0.0745, 0.7451, 0.7059, 1.0);
+    G4Color blue(0.0745, 0.3098, 0.7647, 1.0);
+    G4Color blue_violet(0.3608, 0.0000, 0.5020, 1.0);
+    G4Color violet(0.5020, 0.0000, 0.5020, 1.0);
+    G4Color red_violet(0.7647, 0.0000, 0.5020, 1.0);
+
     world_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
     module_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
     detColumn_C_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
     detColumn_S_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
+    detColumn_Cal_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
     SCINT_Case_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
     SCINT_Case_Top_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
     SCINT_Case_Bot_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
     detElement_C_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
     detElement_S_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
+    detElement_Cal_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
 
     auto metal_VisAtt = new G4VisAttributes( G4Color::Gray() );
-    metal_VisAtt -> SetVisibility( true );
+    // metal_VisAtt -> SetVisibility( true );
+    metal_VisAtt -> SetVisibility( false );
     ENCL_Bot_LV -> SetVisAttributes( metal_VisAtt );
     ENCL_Side1_LV -> SetVisAttributes( metal_VisAtt );
     ENCL_Side2_LV -> SetVisAttributes( metal_VisAtt );
@@ -1695,30 +1757,44 @@ namespace grape
     MIBP_LV -> SetVisAttributes( metal_VisAtt );
     MIBP_Edge_LV -> SetVisAttributes( metal_VisAtt );
 
-    auto pc_VisAtt = new G4VisAttributes( G4Color::Green() );
-    pc_VisAtt -> SetVisibility( true );
+    auto pc_VisAtt = new G4VisAttributes( green );
+    pc_VisAtt -> SetVisibility( false );
     APB_LV -> SetVisAttributes( pc_VisAtt );
     MIB_LV -> SetVisAttributes( pc_VisAtt );
     SiPM_PCB_LV -> SetVisAttributes( pc_VisAtt );
 
-    auto con_VisAtt = new G4VisAttributes( G4Colour( 0.92, 0.79, 0.61 ) );
+    auto con_VisAtt = new G4VisAttributes( yellow );
+    con_VisAtt -> SetVisibility( false );
     APB_Con_LV -> SetVisAttributes( con_VisAtt );
     
-    auto pmt_VisAtt = new G4VisAttributes( G4Color::Blue() );
-    pmt_VisAtt -> SetVisibility( true );
+    auto pmt_VisAtt = new G4VisAttributes( G4Color::White() );
+    pmt_VisAtt -> SetVisibility( false );
     SiPM_LV -> SetVisAttributes( pmt_VisAtt );
-    OPad_LV -> SetVisAttributes( pmt_VisAtt );
 
-    auto scintC_VisAtt = new G4VisAttributes( G4Color::Red() );
+    auto opad_VisAtt = new G4VisAttributes( blue_green );
+    opad_VisAtt -> SetVisibility( false );
+    OPad_LV -> SetVisAttributes( opad_VisAtt );
+
+    auto scintC_VisAtt = new G4VisAttributes( blue );
     scintC_VisAtt -> SetVisibility(true);
     scintC_LV -> SetVisAttributes(scintC_VisAtt);
     // scintC_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
 
-    auto scintS_VisAtt = new G4VisAttributes( G4Color::White() );
+    auto scintS_VisAtt = new G4VisAttributes( red );
     scintS_VisAtt -> SetVisibility(true);
     scintS_LV -> SetVisAttributes(scintS_VisAtt);
     // scintS_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
 
+    auto cal_VisAtt = new G4VisAttributes( yellow_orange  );
+    cal_VisAtt -> SetVisibility(true);
+    cal_LV -> SetVisAttributes(cal_VisAtt);
+    // scintS_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
+
+    auto calHouse_VisAtt = new G4VisAttributes( G4Color::Black()  );
+    calHouse_VisAtt -> SetVisibility(false);
+    calHouse_LV -> SetVisAttributes(calHouse_VisAtt);
+    // calHouse_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
+
     //======================================================
     // Step Limits
     //======================================================
@@ -1726,242 +1802,59 @@ namespace grape
     auto stepLimit = new G4UserLimits( maxStep );
     scintC_LV->SetUserLimits( stepLimit );
     scintS_LV->SetUserLimits( stepLimit );
-
-
-
-
-	G4cout << " " << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "World Volume Dimensions: " << G4endl;
-	G4cout << "           dX: kWorld_Xsize      = " << kWorld_Xsize << " m" << G4endl;
-	G4cout << "           dY: kWorld_Ysize      = " << kWorld_Ysize << " m" << G4endl;
-	G4cout << "           dZ: kWorld_Zsize      = " << kWorld_Zsize << " m" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Scintillator Element Dimensions: " << G4endl;
-	G4cout << "           dX: kScint_Xsize      = " << kScint_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kScint_Ysize      = " << kScint_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kScint_Zsize      = " << kScint_Zsize << " mm" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Scintillator Pitch: " << G4endl;
-	G4cout << "           dX: kScint_Xpitch     = " << kScint_Xpitch << " mm" << G4endl;
-	G4cout << "           dY: kScint_Ypitch     = " << kScint_Ypitch << " mm" << G4endl;
-	G4cout << "           dZ: kScint_Zpitch     = " << kScint_Zpitch << " mm" << G4endl;		
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Scintillator Array Dimensions: " << G4endl;
-	G4cout << "          N_x: kNumScint_X       = " << kNumScint_X << G4endl;
-	G4cout << "          N_y: kNumScint_Y       = " << kNumScint_Y << G4endl;
-	G4cout << "          N_z: kNumScint_Z       = " << kNumScint_Z << G4endl;		
-	G4cout << "        N_tot: kNumScint         = " << kNumScint   << G4endl;		
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Optical Pad Dimensions: " << G4endl;
-	G4cout << "           dX: kOpticalPad_Xsize = " << kOpticalPad_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kOpticalPad_Ysize = " << kOpticalPad_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kOpticalPad_Zsize = " << kOpticalPad_Zsize << " mm" << G4endl;		
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "SiPM Dimensions: " << G4endl;
-	G4cout << "           dX: kSiPM_Xsize       = " << kSiPM_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kSiPM_Ysize       = " << kSiPM_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kSiPM_Zsize       = " << kSiPM_Zsize << " mm" << G4endl;		
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "SiPM Power Board Dimensions: " << G4endl;
-	G4cout << "           dX: kSiPM_PCB_Xsize   = " << kSiPM_PCB_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kSiPM_PCB_Ysize   = " << kSiPM_PCB_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kSiPM_PCB_Zsize   = " << kSiPM_PCB_Zsize << " mm" << G4endl;		
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "SiPM Gap Size: " << G4endl;
-	G4cout << "          Gap: kDet_Gap          = " << kDet_Gap << " mm" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Detector Element Dimensions: " << G4endl;
-	G4cout << "           dX: kDetElement_Xsize = " << kDetElement_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kDetElement_Ysize = " << kDetElement_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kDetElement_Zsize = " << kDetElement_Zsize << " mm" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Scintillator Case Thickness: " << G4endl;
-	G4cout << "      Thickness: kScint_Case_Thickness = " << kScint_Case_Thickness << " mm" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Scintillator Case Dimensions - TOP: " << G4endl;
-	G4cout << "           dX: kScint_Case_Top_Xsize = " << kScint_Case_Top_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kScint_Case_Top_Ysize = " << kScint_Case_Top_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kScint_Case_Top_Zsize = " << kScint_Case_Top_Zsize << " mm" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Scintillator Case Dimensions - BOTTOM: " << G4endl;
-	G4cout << "           dX: kScint_Case_Bot_Xsize = " << kScint_Case_Bot_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kScint_Case_Bot_Ysize = " << kScint_Case_Bot_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kScint_Case_Bot_Zsize = " << kScint_Case_Bot_Zsize << " mm" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Scintillator Case Dimensions: " << G4endl;
-	G4cout << "           dX: kScint_Case_Xsize = " << kScint_Case_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kScint_Case_Ysize = " << kScint_Case_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kScint_Case_Zsize = " << kScint_Case_Zsize << " mm" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Module Interface Board (MIB) Dimensions: " << G4endl;
-	G4cout << "           dX: kMIB_Xsize = " << kMIB_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kMIB_Ysize = " << kMIB_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kMIB_Zsize = " << kMIB_Zsize << " mm" << G4endl;
-	G4cout << "          Gap: kAPB_MIB_Zoffset = " << kAPB_MIB_Zoffset << " mm" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Analog Power Board (APB) Dimensions: " << G4endl;
-	G4cout << "           dX: kAPB_Xsize = " << kAPB_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kAPB_Ysize = " << kAPB_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kAPB_Zsize = " << kAPB_Zsize << " mm" << G4endl;
-	G4cout << "          Gap: kAPB_Zoffset = " << kAPB_Zoffset << " mm" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "APB-MIB Connector Dimensions: " << G4endl;
-	G4cout << "           dX: kAPB_Con_Xsize = " << kAPB_Con_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kAPB_Con_Ysize = " << kAPB_Con_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kAPB_Con_Zsize = " << kAPB_Con_Zsize << " mm" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Base Plate (Al) Dimensions: " << G4endl;
-	G4cout << "           dX: kENCL_Bot_Xsize = " << kENCL_Bot_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kENCL_Bot_Ysize = " << kENCL_Bot_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kENCL_Bot_Zsize = " << kENCL_Bot_Zsize << " mm" << G4endl;	
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Base Plate (Sn) Dimensions: " << G4endl;
-	G4cout << "           dX: kSHSN_Bot_Xsize = " << kSHSN_Bot_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kSHSN_Bot_Ysize = " << kSHSN_Bot_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kSHSN_Bot_Zsize = " << kSHSN_Bot_Zsize << " mm" << G4endl;		
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Base Plate (Pb) Dimensions: " << G4endl;
-	G4cout << "           dX: kSHPB_Bot_Xsize = " << kSHPB_Bot_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kSHPB_Bot_Ysize = " << kSHPB_Bot_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kSHPB_Bot_Zsize = " << kSHPB_Bot_Zsize << " mm" << G4endl;	
-
-
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Detector Column Dimensions: " << G4endl;
-	G4cout << "           dX: kDetColumn_Xsize = " << kDetColumn_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kDetColumn_Ysize = " << kDetColumn_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kDetColumn_Zsize = " << kDetColumn_Zsize << " mm" << G4endl;		
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Module Dimensions: " << G4endl;
-	G4cout << "           dX: kModule_Xsize = " << kModule_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kModule_Ysize = " << kModule_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kModule_Zsize = " << kModule_Zsize << " mm" << G4endl;		
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Enclose Side1 (Al) Dimensions: " << G4endl;
-	G4cout << "           dX: kENCL_Side1_Xsize = " << kENCL_Side1_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kENCL_Side1_Ysize = " << kENCL_Side1_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kENCL_Side1_Zsize = " << kENCL_Side1_Zsize << " mm" << G4endl;			
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Enclose Side1 (Sn) Dimensions: " << G4endl;
-	G4cout << "           dX: kSHSN_Side1_Xsize = " << kSHSN_Side1_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kSHSN_Side1_Ysize = " << kSHSN_Side1_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kSHSN_Side1_Zsize = " << kSHSN_Side1_Zsize << " mm" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Enclose Side1 (Pb) Dimensions: " << G4endl;
-	G4cout << "           dX: kSHPB_Side1_Xsize = " << kSHPB_Side1_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kSHPB_Side1_Ysize = " << kSHPB_Side1_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kSHPB_Side1_Zsize = " << kSHPB_Side1_Zsize << " mm" << G4endl;	
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Enclose Side2 (Al) Dimensions: " << G4endl;
-	G4cout << "           dX: kENCL_Side2_Xsize = " << kENCL_Side2_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kENCL_Side2_Ysize = " << kENCL_Side2_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kENCL_Side2_Zsize = " << kENCL_Side2_Zsize << " mm" << G4endl;			
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Enclose Side2(Sn) Dimensions: " << G4endl;
-	G4cout << "           dX: kSHSN_Side2_Xsize = " << kSHSN_Side2_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kSHSN_Side2_Ysize " << kSHSN_Side2_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kSHSN_Side2_Zsize " << kSHSN_Side2_Zsize << " mm" << G4endl;
-	G4cout << "*********************************************************" << G4endl;
-	G4cout << "Enclose Side2 (Pb) Dimensions: " << G4endl;
-	G4cout << "           dX: kSHPB_Side2_Xsize = " << kSHPB_Side2_Xsize << " mm" << G4endl;
-	G4cout << "           dY: kSHPB_Side2_Ysize = " << kSHPB_Side2_Ysize << " mm" << G4endl;
-	G4cout << "           dZ: kSHPB_Side2_Zsize = " << kSHPB_Side2_Zsize << " mm" << G4endl;
-	
-	
-	
-	
-				
-// 	G4cout << "*********************************************************" << G4endl;
-// 	G4cout << "W Shield - Type A: " << G4endl;
-// 	G4cout << "           dX: " << ShieldA_WShield_dX << " mm" << G4endl;
-// 	G4cout << "           dY: " << ShieldA_WShield_dY << " mm" << G4endl;
-// 	G4cout << "           dZ: " << ShieldA_WShield_dZ << " mm" << G4endl;
-// 	G4cout << " " << G4endl;
-// 	G4cout << "*********************************************************" << G4endl;
-// 	G4cout << "Sn Shield - Type B: " << G4endl;
-// 	G4cout << "           dX: " << ShieldB_SnShield_dX << " mm" << G4endl;
-// 	G4cout << "           dY: " << ShieldB_SnShield_dY << " mm" << G4endl;
-// 	G4cout << "           dZ: " << ShieldB_SnShield_dZ << " mm" << G4endl;
-// 	G4cout << "*********************************************************" << G4endl;
-// 	G4cout << "W Shield - Type B: " << G4endl;
-// 	G4cout << "           dX: " << ShieldB_WShield_dX << " mm" << G4endl;
-// 	G4cout << "           dY: " << ShieldB_WShield_dY << " mm" << G4endl;
-// 	G4cout << "           dZ: " << ShieldB_WShield_dZ << " mm" << G4endl;		
-// 	G4cout << " " << G4endl;
-// 	G4cout << "*********************************************************" << G4endl;
-// 	G4cout << "Sn Shield - Type C: " << G4endl;
-// 	G4cout << "           dX: " << ShieldC_SnShield_dX << " mm" << G4endl;
-// 	G4cout << "           dY: " << ShieldC_SnShield_dY << " mm" << G4endl;
-// 	G4cout << "           dZ: " << ShieldC_SnShield_dZ << " mm" << G4endl;
-// 	G4cout << "*********************************************************" << G4endl;
-// 	G4cout << "W Shield - Type C: " << G4endl;
-// 	G4cout << "           dX: " << ShieldC_WShield_dX << " mm" << G4endl;
-// 	G4cout << "           dY: " << ShieldC_WShield_dY << " mm" << G4endl;
-// 	G4cout << "           dZ: " << ShieldC_WShield_dZ << " mm" << G4endl;		
-// 	G4cout << " " << G4endl;
-// 	G4cout << "*********************************************************" << G4endl;
-// 	G4cout << "Sn Shield - Type D: " << G4endl;
-// 	G4cout << "           dX: " << ShieldD_SnShield_dX << " mm" << G4endl;
-// 	G4cout << "           dY: " << ShieldD_SnShield_dY << " mm" << G4endl;
-// 	G4cout << "           dZ: " << ShieldD_SnShield_dZ << " mm" << G4endl;
-// 	G4cout << "*********************************************************" << G4endl;
-// 	G4cout << "W Shield - Type D: " << G4endl;
-// 	G4cout << "           dX: " << ShieldD_WShield_dX << " mm" << G4endl;
-// 	G4cout << "           dY: " << ShieldD_WShield_dY << " mm" << G4endl;
-// 	G4cout << "           dZ: " << ShieldD_WShield_dZ << " mm" << G4endl;						
-// 	G4cout << " " << G4endl;
-// 	G4cout << "*********************************************************" << G4endl;
-// 	G4cout << "FRAM Plate: " << G4endl;
-// 	G4cout << "           dX: " << FRAM_X << " mm" << G4endl;
-// 	G4cout << "           dY: " << FRAM_Y << " mm" << G4endl;
-// 	G4cout << "           dZ: " << FRAM_Z << " mm" << G4endl;
-// 	G4cout << "            X: " << FRAM_Xpos << " mm" << G4endl;
-// 	G4cout << "            Y: " << FRAM_Ypos << " mm" << G4endl;
-// 	G4cout << "            Z: " << FRAM_Zpos << " mm" << G4endl;
-// 
-// 
-
-
-
-
-
-
-
-
-
-
-
+    cal_LV->SetUserLimits( stepLimit );
 
     //======================================================
     // Print some information
     //======================================================
-    // G4ThreeVector TopCenter = G4ThreeVector( 0., 0., (mod_Zpos + mod_Z/2) );
-    // G4RotationMatrix TopCenter_rot = G4RotationMatrix( 0., fZenithAngle, 0. );
-    // TopCenter.transform( TopCenter_rot );
+    G4ThreeVector TopCenter = G4ThreeVector( 0., 0., (mod_Zpos + mod_Z/2) );
 
     // G4ThreeVector ColimatorHole = G4ThreeVector( 0., 0., (collimator_Zpos - collimator_Z/2 + ELC1_Z + BLC_Z - BLC_Slot_Z) );
     // G4RotationMatrix ColimatorHole_rot = G4RotationMatrix( 0., fZenithAngle, 0. );
     // TopCenter.transform( TopCenter_rot );
 
-    // G4cout << G4endl;
-    // G4cout << "------ Instrument Dimensions: " << G4endl;
-    // G4cout << "           X: " << mod_X/mm << " mm" << G4endl;
-    // G4cout << "           Y: " << mod_Y/mm << " mm" << G4endl;
-    // G4cout << "           Z: " << mod_Z/mm << " mm" << G4endl;
+    G4cout << G4endl;
+    G4cout << "------ Instrument Dimensions: " << G4endl;
+    G4cout << "           X: " << mod_X/mm << " mm" << G4endl;
+    G4cout << "           Y: " << mod_Y/mm << " mm" << G4endl;
+    G4cout << "           Z: " << mod_Z/mm << " mm" << G4endl;
 
-    // G4cout << "------ Center of Top of Instrument: " << G4endl;
-    // G4cout << "           X: " << TopCenter.x()/mm << " mm" << G4endl;
-    // G4cout << "           Y: " << TopCenter.y()/mm << " mm" << G4endl;
-    // G4cout << "           Z: " << TopCenter.z()/mm << " mm" << G4endl;
+    G4cout << "------ Center of Top of Instrument: " << G4endl;
+    G4cout << "           X: " << TopCenter.x()/mm << " mm" << G4endl;
+    G4cout << "           Y: " << TopCenter.y()/mm << " mm" << G4endl;
+    G4cout << "           Z: " << TopCenter.z()/mm << " mm" << G4endl;
 
     // G4cout << "------ Collimator Hole Position:" << G4endl;
     // G4cout << "           X: " << ColimatorHole.x()/mm << " mm" << G4endl;
     // G4cout << "           Y: " << ColimatorHole.y()/mm << " mm" << G4endl;
     // G4cout << "           Z: " << ColimatorHole.z()/mm << " mm" << G4endl;
 
-    // G4cout << G4endl;
-    // G4cout << G4endl;
+    // G4cout << "------ Detector Columns: " << G4endl;
+    // copyNum = 0;
+    // for (auto col = 0; col<kNumScint_Y; col++) {
+    //   for (auto row = 0; row<kNumScint_X; row++) {
+    //     detColumn_Xpos =  ( row * kScint_Xpitch ) - detColumn_offsetX;
+    //     detColumn_Ypos = -( col * kScint_Ypitch ) + detColumn_offsetY;
+    //     G4cout << "         Num: " << copyNum++;
+    //     G4cout << " ( " << detColumn_Xpos/mm;
+    //     G4cout << ", " << detColumn_Ypos/mm;
+    //     G4cout << ", " << detColumn_Zpos/mm << " )" << G4endl;
+    //   }
+    // }
+
+    // G4cout << "------ Detector Elements in Columns: " << G4endl;
+    // copyNum = 0;
+    // for (auto ele = 0; ele<kNumScint_Z; ele++) {
+    //   detElement_Zpos = SCINT_Case_Top_Zpos + SCINT_Case_Top_Z/2 - kScint_Case_Thickness/2 - ele * detElement_Z - detElement_Z/2;
+    //     G4cout << "         Num: " << copyNum++;
+    //     G4cout << " ( " << detElement_Xpos/mm;
+    //     G4cout << ", " << detElement_Ypos/mm;
+    //     G4cout << ", " << detElement_Zpos/mm << " )" << G4endl;
+    // }
+
+
+    G4cout << G4endl;
+    G4cout << G4endl;
 
 
     //======================================================
@@ -1985,112 +1878,9 @@ namespace grape
     SDManager->AddNewDetector( scint_SD );
     LVS->GetVolume("ScintC_LV")->SetSensitiveDetector( scint_SD );
     LVS->GetVolume("ScintS_LV")->SetSensitiveDetector( scint_SD );
+    LVS->GetVolume("Cal_LV")->SetSensitiveDetector( scint_SD );
 
   }
 
-  //****************************************************************************
-  // Method
-  //****************************************************************************
-  void DetectorConstruction::SetZenithAngle( G4double zang )
-  {
-    if (fZenithAngle != zang) {
-      fZenithAngle = zang;
-
-      auto Xpos = 0.0*mm;
-      auto Ypos = (kENCL_Side1_Zsize/2 - kScint_Zsize/2)*std::sin( fZenithAngle );
-      auto Zpos = kModule_Zsize/2*std::cos( fZenithAngle ) + kModule_Xsize/2*(std::cos( fAzimuthAngle ) + std::sin( fAzimuthAngle ))*std::sin( fZenithAngle );
-      auto Pos = G4ThreeVector( Xpos, Ypos, Zpos );
-      auto RotMat = new G4RotationMatrix();
-      RotMat -> setTheta( fZenithAngle );
-      RotMat -> setPsi( fAzimuthAngle );
-
-      if (fPhysicalModule) {
-        fPhysicalModule->SetRotation(RotMat);
-        fPhysicalModule->SetTranslation(Pos);
-        G4cout
-          << G4endl 
-          << "----> The zenith angle is " << fZenithAngle/deg << " deg" << G4endl;
-      
-        UpdateGeometry();
-      } else {
-          G4cout
-            << G4endl
-            << "-->  WARNING from SetZenithAngle : "
-            << "fPhysicalModule" << " not found" << G4endl;
-      }
-
-    }
-  }
-
-  //****************************************************************************
-  // Method
-  //****************************************************************************
-  void DetectorConstruction::SetAzimuthAngle( G4double aang )
-  {
-    if (fAzimuthAngle != aang) {
-      fAzimuthAngle = aang;
-
-      auto Xpos = 0.0*mm;
-      auto Ypos = (kENCL_Side1_Zsize/2 - kScint_Zsize/2)*std::sin( fZenithAngle );
-      auto Zpos = kModule_Zsize/2*std::cos( fZenithAngle ) + kModule_Xsize/2*(std::cos( fAzimuthAngle ) + std::sin( fAzimuthAngle ))*std::sin( fZenithAngle );
-      auto Pos = G4ThreeVector( Xpos, Ypos, Zpos );
-      auto RotMat = new G4RotationMatrix();
-      RotMat -> setTheta( fZenithAngle );
-      RotMat -> setPsi( fAzimuthAngle );
-    
-      if (fPhysicalModule) {
-        fPhysicalModule->SetRotation(RotMat);
-        fPhysicalModule->SetTranslation(Pos);
-        G4cout
-          << G4endl 
-          << "----> The azimuth angle is " << fAzimuthAngle/deg << " deg" << G4endl;
-      
-        UpdateGeometry();
-      } else {
-          G4cout
-            << G4endl
-            << "-->  WARNING from SetZenithAngle : "
-            << "fPhysicalModule" << " not found" << G4endl;
-      }
-
-    } 
-  }
-
-  //****************************************************************************
-  // Method
-  //****************************************************************************
-  void DetectorConstruction::SetPolarizationAngle( G4double pang )
-  {
-    
-    if (fPolarizationAngle != pang) {
-      fPolarizationAngle = pang;
-
-      auto RotMat = new G4RotationMatrix();
-      RotMat -> setPhi( fPolarizationAngle );
-
-      if (fPhysicalCollimator) {
-        fPhysicalCollimator->SetRotation(RotMat);
-        G4cout
-          << G4endl 
-          << "----> The polarization angle is " << fPolarizationAngle/deg << " deg" << G4endl;
-      
-        UpdateGeometry();
-      } else {
-          G4cout
-            << G4endl
-            << "-->  WARNING from SetPolarizationAngle : "
-            << "fPhysicalCollimator" << " not found" << G4endl;
-      }
-    }
-  }
-
-  //****************************************************************************
-  // Method
-  //****************************************************************************
-  void DetectorConstruction::UpdateGeometry()
-  {
-    G4RunManager::GetRunManager()->GeometryHasBeenModified();
-    G4RunManager::GetRunManager()->ReinitializeGeometry();
-  }
 }
 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
diff --git a/../../GRAPE-MM/src/DetectorMessenger.cc b/../../GRAPE-CE/src/DetectorMessenger.cc
old mode 100644
new mode 100755
index dc90bab..e4113c8
--- a/../../GRAPE-MM/src/DetectorMessenger.cc
+++ b/../../GRAPE-CE/src/DetectorMessenger.cc
@@ -1,12 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  Cube Balloon Flight
-//  Created: Mar 2, 2022 by Camden Ertley
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file DetectorMessenger.cc
@@ -41,49 +41,12 @@ namespace grape
     fOverlapCmd->SetParameterName("flag",false);
     fOverlapCmd->SetDefaultValue(true);
     fOverlapCmd->AvailableForStates(G4State_PreInit);
-
-    fZenithCmd = new G4UIcmdWithADoubleAndUnit("/user/det/setZenithAngle",this);  
-    fZenithCmd->SetGuidance("Set zenith angle.");
-    fZenithCmd->SetParameterName("zenith",false);
-    fZenithCmd->SetUnitCategory("Angle");
-    fZenithCmd->SetRange("zenith>=0.0 && zenith<=180.");
-    fZenithCmd->SetDefaultValue(0.);
-    fZenithCmd->SetDefaultUnit("degree");
-    fZenithCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
-
-    fAzimuthCmd = new G4UIcmdWithADoubleAndUnit("/user/det/setAzimuthAngle",this);  
-    fAzimuthCmd->SetGuidance("Set azimuth angle.");
-    fAzimuthCmd->SetParameterName("azimuth",false);
-    fAzimuthCmd->SetUnitCategory("Angle");
-    fAzimuthCmd->SetRange("azimuth>=0.0 && azimuth<=360.");
-    fAzimuthCmd->SetDefaultValue(0.);
-    fAzimuthCmd->SetDefaultUnit("degree");
-    fAzimuthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
-
-    fPolarizationCmd = new G4UIcmdWithADoubleAndUnit("/user/det/setPolarizationAngle",this);  
-    fPolarizationCmd->SetGuidance("Set poloarization angle.");
-    fPolarizationCmd->SetParameterName("polar",false);
-    fPolarizationCmd->SetUnitCategory("Angle");
-    fPolarizationCmd->SetRange("polar>=0.0 && polar<=360.");
-    fPolarizationCmd->SetDefaultValue(0.);
-    fPolarizationCmd->SetDefaultUnit("degree");
-    fPolarizationCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
-
-    fUpdateCmd = new G4UIcmdWithoutParameter("/user/det/update",this);
-    fUpdateCmd->SetGuidance("Update geometry.");
-    fUpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
-    fUpdateCmd->SetGuidance("if you changed geometrical value(s).");
-    fUpdateCmd->AvailableForStates(G4State_Idle);
   }
 
   //****************************************************************************
   // Destructor
   //****************************************************************************
   DetectorMessenger::~DetectorMessenger() {
-    delete fUpdateCmd;
-    delete fPolarizationCmd;
-    delete fAzimuthCmd;
-    delete fZenithCmd;
     delete fOverlapCmd;
     delete fDetDir;
     delete fUSERDir;
@@ -94,19 +57,7 @@ namespace grape
   //****************************************************************************
   void DetectorMessenger::SetNewValue( G4UIcommand* command,G4String newValue) 
   {
-    if( command == fZenithCmd ) 
-      { fDetectorConstruction->SetZenithAngle( fZenithCmd->GetNewDoubleValue(newValue) ); }
-
-    else if( command == fAzimuthCmd ) 
-      { fDetectorConstruction->SetAzimuthAngle( fAzimuthCmd->GetNewDoubleValue(newValue) ); }
-
-    else if( command == fPolarizationCmd ) 
-      { fDetectorConstruction->SetPolarizationAngle( fPolarizationCmd->GetNewDoubleValue(newValue) ); }
-
-    else if ( command == fUpdateCmd )
-      { fDetectorConstruction->UpdateGeometry(); }
-
-    else if ( command == fOverlapCmd )
+    if ( command == fOverlapCmd )
         { fDetectorConstruction->SetOverlapFlag( fOverlapCmd->GetNewBoolValue(newValue)); }
     }
 
diff --git a/../../GRAPE-MM/src/EventAction.cc b/../../GRAPE-CE/src/EventAction.cc
old mode 100644
new mode 100755
index 0bb98f8..4c002f3
--- a/../../GRAPE-MM/src/EventAction.cc
+++ b/../../GRAPE-CE/src/EventAction.cc
@@ -1,12 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  Cube Balloon Flight
-//  Created: Mar 2, 2022 by Camden Ertley
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file EventAction.cc
@@ -102,10 +102,9 @@ namespace grape
     auto nHits = scintHC->GetSize();
 
     // Check if there were any hits in instrument
-    if ( nHits > 0 && nHits < kNumKeep ){
+    if ( nHits > 0 ){
       // G4cout << "Scint hits: " << nHits << G4endl;
-      // G4cout << "Scat hits:  " << scatHits << G4endl;
-
+ 
       // get analysis manager
       auto analysisManager = G4AnalysisManager::Instance();
 
@@ -114,39 +113,34 @@ namespace grape
       analysisManager->FillNtupleIColumn(col++, event->GetEventID());
 
       auto primaryE = event->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy()/keV;
-      analysisManager->FillNtupleIColumn(col++, primaryE);
+      analysisManager->FillNtupleDColumn(col++, primaryE);
 
       // Add number of hits
       analysisManager->FillNtupleIColumn(col++, nHits);
 
-      // Data for each element
-      auto totalE = 0.;
-      for (unsigned long i=0; i<kNumKeep; i++ ) {
-        if ( i < nHits ){
+      // Data for each hit element
+      // auto fID = -1;
+      // fEdep = std::vector<G4double>(kDim, NAN);
+      // fGEB = std::vector<G4double>(kDim, NAN);
+      // fTime = std::vector<G4double>(kDim, NAN);
+      
+      fID = std::vector<G4int>(nHits, NAN);
+      fEdep = std::vector<G4double>(nHits, NAN);
+      fGEB = std::vector<G4double>(nHits, NAN);
+      fTime = std::vector<G4double>(nHits, NAN);
+      for (unsigned long i=0; i<nHits; i++ ) {
           auto hit = static_cast<ScintHit*>(scintHC->GetHit(i));
 
-          analysisManager->FillNtupleIColumn(col++, hit->GetID());        // 1
-          analysisManager->FillNtupleDColumn(col++, hit->GetPos().x());   // 2
-          analysisManager->FillNtupleDColumn(col++, hit->GetPos().y());   // 3
-          analysisManager->FillNtupleDColumn(col++, hit->GetPos().z());   // 4
-          analysisManager->FillNtupleDColumn(col++, hit->GetEdep()/keV);  // 5
-          analysisManager->FillNtupleDColumn(col++, BroadenEnergy(hit->GetType(),hit->GetEdep()/keV)); // 6
-          analysisManager->FillNtupleDColumn(col++, hit->GetBirkEdep()/keV);  // 7
-          analysisManager->FillNtupleDColumn(col++, BroadenEnergy(hit->GetType(),hit->GetBirkEdep()/keV)); // 8
-          analysisManager->FillNtupleDColumn(col++, hit->GetVisEdep()/keV);  // 9
-          analysisManager->FillNtupleDColumn(col++, BroadenEnergy(hit->GetType(),hit->GetVisEdep()/keV)); // 10
-          analysisManager->FillNtupleDColumn(col++, hit->GetTime()/ns);   // 11
-          analysisManager->FillNtupleSColumn(col++, hit->GetType());      // 12
-          analysisManager->FillNtupleIColumn(col++, hit->GetDetType());      // 13
-         // G4cout << "DetType:  " << hit->GetDetType() << G4endl;
-
-          totalE += hit->GetEdep()/keV;
-        } else {
-          col += 13;
-        }
-      }
+          // fID = hit->GetID();
+          // fEdep[fID] = hit->GetEdep()/keV;
+          // fGEB[fID] = BroadenEnergy( hit->GetType(), hit->GetEdep()/keV );
+          // fTime[fID] = hit->GetTime()/ns;
 
-      analysisManager->FillNtupleDColumn(col++, totalE);
+          fID[i] = hit->GetID();
+          fEdep[i] = hit->GetEdep()/keV;
+          fGEB[i] = BroadenEnergy( hit->GetType(), hit->GetEdep()/keV );
+          fTime[i] = hit->GetTime()/ns;
+      }
 
       // Finish event
       analysisManager->AddNtupleRow();  
@@ -166,7 +160,7 @@ namespace grape
       // auto sigma = -8.3195 + ( 3.1992 * sqrt( energy ) ); // old GEANT4 sims
       // auto sigma = sqrt( 0.5692 + ( 2.837 * energy ) ); // fit to GRAPE calibration data
       // auto sigma = ( 0.478 / 2.35 ) * sqrt( 60. * energy ); // Peter's old numbers ( 47.8% at 60 keV )
-      auto sigma = -1.035 + ( 1.66 * sqrt( energy ) ); // fit to LEAP calibration data
+      auto sigma = -1.035 + ( 1.66 * sqrt( energy ) ); // fit to GRAPE calibration data
       energy = G4RandGauss::shoot( energy, sigma) ;
     }
 
@@ -174,7 +168,9 @@ namespace grape
       // auto sigma = 1.89 + 1.20 * sqrt( energy ); // old GEANT4 sims
       // auto sigma = sqrt( -83.43 + ( 4.88 * energy ) ); // fit to calibration data
       // auto sigma = ( 0.14 / 2.35 ) * sqrt( 662. * energy ); // 14% at 662 keV
-      auto sigma = 0.1146 + ( 1.662 * sqrt( energy ) ); // fit to LEAP calibration data
+      // auto sigma = 0.1146 + ( 1.662 * sqrt( energy ) ); // fit to GRAPE calibration data
+      auto sigma = 1.3846 + ( 1.2179 * sqrt( energy ) ); // fit to GRAPE calibration data 5/10/22
+      // auto sigma = ( 0.116 / 2.35 ) * sqrt( 662. * energy ); // 11.6% at 662 keV 5/10/22
       energy = G4RandGauss::shoot( energy, sigma );
     }
 
@@ -184,12 +180,12 @@ namespace grape
     }
 
     else if ( type == "p-Terphenyl" ) { 
-      auto sigma = ( 0.227 / 2.35 ) * sqrt( 59.6 * energy ); // GRAPE Cube measured 22.7% at 60 keV
+      auto sigma = 1.42 + 0.90 * sqrt( energy ) ; // Needs updated
       energy = G4RandGauss::shoot( energy, sigma );
     }
     
     else if ( type == "GAGG" ) { 
-      auto sigma = ( 0.033306 * energy ) + 4.218475; // fit to GRAPE calibration data
+      auto sigma = 1.42 + 0.90 * sqrt( energy ) ;
       energy = G4RandGauss::shoot( energy, sigma );
     }
 
diff --git a/../../GRAPE-MM/src/PhysicsList.cc b/../../GRAPE-CE/src/PhysicsList.cc
old mode 100644
new mode 100755
index 0daa812..74e9645
--- a/../../GRAPE-MM/src/PhysicsList.cc
+++ b/../../GRAPE-CE/src/PhysicsList.cc
@@ -1,12 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  Cube Balloon Flight
-//  Created: Mar 2, 2022 by Camden Ertley
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file PhysicsList.cc
@@ -163,15 +163,18 @@ namespace grape
     G4cout << "    G4EmLivermorePolarizedPhysics" << G4endl;
     G4cout << "### Option1: Electromagnetic & Hadronic" << G4endl;
     G4cout << "    G4DecayPhysics" << G4endl;
-    G4cout << "    G4EmStandardPhysics_option4" << G4endl;
+    G4cout << "    G4EmLivermorePolarizedPhysics" << G4endl;
+    // G4cout << "    G4EmStandardPhysics_option4" << G4endl;
     G4cout << "    G4HadronPhysicsFTFP_BERT" << G4endl;
     G4cout << "    G4HadronElasticPhysics" << G4endl;
     G4cout << "    G4IonPhysics" << G4endl;
     G4cout << "    G4StoppingPhysics" << G4endl;
     G4cout << "    G4EmExtraPhysics" << G4endl;
+    G4cout << "    G4RadioactiveDecayPhysics" << G4endl;
     G4cout << "### Option2: Electromagnetic & Hadronic with high precision option" << G4endl;
     G4cout << "    G4DecayPhysics" << G4endl;
-    G4cout << "    G4EmStandardPhysics_option4" << G4endl;
+    G4cout << "    G4EmLivermorePolarizedPhysics" << G4endl;
+    // G4cout << "    G4EmStandardPhysics_option4" << G4endl;
     G4cout << "    G4HadronPhysicsFTFP_BERT_HP" << G4endl;
     G4cout << "    G4HadronElasticPhysicsHP" << G4endl;
     G4cout << "    G4IonPhysicsXS" << G4endl;
@@ -241,13 +244,13 @@ namespace grape
     // fEmPhysicsList = new G4EmStandardPhysics_option1(verboseLevel);
     // fEmPhysicsList = new G4EmStandardPhysics_option2(verboseLevel);
     // fEmPhysicsList = new G4EmStandardPhysics_option3(verboseLevel);
-    fEmPhysicsList = new G4EmStandardPhysics_option4(verboseLevel);
+    // fEmPhysicsList = new G4EmStandardPhysics_option4(verboseLevel);
     // fEmPhysicsList = new G4EmStandardPhysicsGS(verboseLevel);
     // fEmPhysicsList = new G4EmStandardPhysicsSS(verboseLevel);
     // fEmPhysicsList = new G4EmStandardPhysicsWVI(verboseLevel);
     // fEmPhysicsList = new G4EmLowEPPHysics(verboseLevel);
     // fEmPhysicsList = new G4EmLivermorePhysics(verboseLevel);
-    // fEmPhysicsList = new G4EmLivermorePolarizedPhysics(verboseLevel);
+    fEmPhysicsList = new G4EmLivermorePolarizedPhysics(verboseLevel);
     // fEmPhysicsList = new G4EmPenelopePhysics(verboseLevel);
     
     // Hadron Inelastic Physics
@@ -292,7 +295,7 @@ namespace grape
 
     // Radioactive decay
     //
-    // fHadronPhys.push_back( new G4RadioactiveDecayPhysics(verboseLevel) );  
+    fHadronPhys.push_back( new G4RadioactiveDecayPhysics(verboseLevel) );  
 
   }
 
@@ -319,13 +322,13 @@ namespace grape
     // fEmPhysicsList = new G4EmStandardPhysics_option1(verboseLevel);
     // fEmPhysicsList = new G4EmStandardPhysics_option2(verboseLevel);
     // fEmPhysicsList = new G4EmStandardPhysics_option3(verboseLevel);
-    fEmPhysicsList = new G4EmStandardPhysics_option4(verboseLevel);
+    // fEmPhysicsList = new G4EmStandardPhysics_option4(verboseLevel);
     // fEmPhysicsList = new G4EmStandardPhysicsGS(verboseLevel);
     // fEmPhysicsList = new G4EmStandardPhysicsSS(verboseLevel);
     // fEmPhysicsList = new G4EmStandardPhysicsWVI(verboseLevel);
     // fEmPhysicsList = new G4EmLowEPPHysics(verboseLevel);
     // fEmPhysicsList = new G4EmLivermorePhysics(verboseLevel);
-    // fEmPhysicsList = new G4EmLivermorePolarizedPhysics(verboseLevel);
+    fEmPhysicsList = new G4EmLivermorePolarizedPhysics(verboseLevel);
     // fEmPhysicsList = new G4EmPenelopePhysics(verboseLevel);
     
     // Hadron Inelastic Physics
diff --git a/../../GRAPE-MM/src/PhysicsListMessenger.cc b/../../GRAPE-CE/src/PhysicsListMessenger.cc
old mode 100644
new mode 100755
index 2c268d8..7996d38
--- a/../../GRAPE-MM/src/PhysicsListMessenger.cc
+++ b/../../GRAPE-CE/src/PhysicsListMessenger.cc
@@ -1,12 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  Cube Balloon Flight
-//  Created: Mar 2, 2022 by Camden Ertley
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file PhysicsListMessenger.cc
diff --git a/../../GRAPE-MM/src/PrimaryGeneratorAction.cc b/../../GRAPE-CE/src/PrimaryGeneratorAction.cc
old mode 100644
new mode 100755
index bc4239b..5a48e2b
--- a/../../GRAPE-MM/src/PrimaryGeneratorAction.cc
+++ b/../../GRAPE-CE/src/PrimaryGeneratorAction.cc
@@ -1,12 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  Cube Balloon Flight
-//  Created: Mar 2, 2022 by Camden Ertley
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file PrimaryGeneratorAction.cc
diff --git a/../../GRAPE-MM/src/RunAction.cc b/../../GRAPE-CE/src/RunAction.cc
old mode 100644
new mode 100755
index 3df6ddd..9eda393
--- a/../../GRAPE-MM/src/RunAction.cc
+++ b/../../GRAPE-CE/src/RunAction.cc
@@ -1,18 +1,19 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  Cube Balloon Flight
-//  Created: Mar 2, 2022 by Camden Ertley
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file RunAction.cc
 /// \brief Implementation of the RunAction class
 
 #include "RunAction.hh"
+#include "EventAction.hh"
 #include "Constants.hh"
 
 #include "G4AnalysisManager.hh"
@@ -30,7 +31,8 @@ namespace grape
   //****************************************************************************
   // Constructor
   //****************************************************************************
-  RunAction::RunAction()
+  RunAction::RunAction( EventAction* eventAct )
+   : fEventAction( eventAct )
   { 
     // set printing event number per each event
     G4RunManager::GetRunManager()->SetPrintProgress(100);     
@@ -57,69 +59,24 @@ namespace grape
 
     // Default output file
     //
-    G4String fileName = "data/Test_ntuple.root";
+    G4String fileName = "../data/Test_ntuple.root";
     // Other supported output types:
-    // G4String fileName = "data/Test_ntuple.csv";
-    // G4String fileName = "data/Test_ntuple.hdf5";
-    // G4String fileName = "data/Test_ntuple.xml";
+    // G4String fileName = "../data/Test_ntuple.csv";
+    // G4String fileName = "../data/Test_ntuple.hdf5";
+    // G4String fileName = "../data/Test_ntuple.xml";
     analysisManager->SetFileName(fileName);
 
     // Creating ntuple
     //
-    analysisManager->CreateNtuple("data", "GRAPE Balooon Data");
+    analysisManager->CreateNtuple("data", "ScintTest Data");
     analysisManager->CreateNtupleIColumn("EventNumber");
-    analysisManager->CreateNtupleIColumn("PrimaryEnergy");
+    analysisManager->CreateNtupleDColumn("PrimaryEnergy");
     analysisManager->CreateNtupleIColumn("Hits");
 
-    
-    G4String col_name = "";
-    for (G4int i=0; i<kNumKeep; i++ ) {
-      std::ostringstream os;
-      os << i;
-
-      col_name = "D" + os.str() + "_ID";
-      analysisManager->CreateNtupleIColumn( col_name );
-
-      col_name = "D" + os.str() + "_PosX";
-      analysisManager->CreateNtupleDColumn( col_name );
-
-      col_name = "D" + os.str() + "_PosY";
-      analysisManager->CreateNtupleDColumn( col_name );
-
-      col_name = "D" + os.str() + "_PosZ";
-      analysisManager->CreateNtupleDColumn( col_name );
-
-      col_name = "D" + os.str() + "_Energy"; // Energy deposited
-      analysisManager->CreateNtupleDColumn( col_name );
-
-      col_name = "D" + os.str() + "_GEB"; // Gaussian Energy Broadening
-      analysisManager->CreateNtupleDColumn( col_name );
-
-      col_name = "D" + os.str() + "_BirkEnergy"; // Energy deposited with Birks
-      analysisManager->CreateNtupleDColumn( col_name );
-
-      col_name = "D" + os.str() + "_BirkGEB"; // Gaussian Energy Broadening
-      analysisManager->CreateNtupleDColumn( col_name );
-
-      col_name = "D" + os.str() + "_VisEnergy"; // Energy deposited with Birks
-      analysisManager->CreateNtupleDColumn( col_name );
-
-      col_name = "D" + os.str() + "_VisGEB"; // Gaussian Energy Broadening
-      analysisManager->CreateNtupleDColumn( col_name );
-
-      col_name = "D" + os.str() + "_Time";
-      analysisManager->CreateNtupleDColumn( col_name );
-
-      col_name = "D" + os.str() + "_Type";
-      analysisManager->CreateNtupleSColumn( col_name );
-      
-      col_name = "D" + os.str() + "_DetType";
-      analysisManager->CreateNtupleIColumn( col_name );
-
-      os.clear();
-    }
-
-    analysisManager->CreateNtupleDColumn("TotalEnergy");
+    analysisManager->CreateNtupleIColumn("ID", fEventAction->GetID());
+    analysisManager->CreateNtupleDColumn("Edep", fEventAction->GetEdep());
+    analysisManager->CreateNtupleDColumn("GEB", fEventAction->GetGEB());
+    analysisManager->CreateNtupleDColumn("Time", fEventAction->GetTime());
 
     analysisManager->FinishNtuple();
 
diff --git a/../../GRAPE-MM/src/ScintHit.cc b/../../GRAPE-CE/src/ScintHit.cc
old mode 100644
new mode 100755
index a831ce7..0f40c61
--- a/../../GRAPE-MM/src/ScintHit.cc
+++ b/../../GRAPE-CE/src/ScintHit.cc
@@ -1,12 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  Cube Balloon Flight
-//  Created: Mar 2, 2022 by Camden Ertley
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file ScintHit.cc
diff --git a/../../GRAPE-MM/src/ScintSD.cc b/../../GRAPE-CE/src/ScintSD.cc
old mode 100644
new mode 100755
index e853bb9..dda6537
--- a/../../GRAPE-MM/src/ScintSD.cc
+++ b/../../GRAPE-CE/src/ScintSD.cc
@@ -1,12 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  Cube Balloon Flight
-//  Created: Mar 2, 2022 by Camden Ertley
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file ScintSD.cc
@@ -70,8 +70,9 @@ namespace grape
     if ( edep == 0. ) return false;      
 
     // visible energy deposit
-    auto fEmSaturation = G4LossTableManager::Instance()->EmSaturation();
-    auto visedep = fEmSaturation -> VisibleEnergyDepositionAtAStep( step );
+    // auto fEmSaturation = G4LossTableManager::Instance()->EmSaturation();
+    // auto visedep = fEmSaturation -> VisibleEnergyDepositionAtAStep( step );
+    auto visedep = 0;
 
     //  Energy deposit with manual Birks attenuation
     auto birkedep = BirksAttenuation( step );
@@ -123,32 +124,17 @@ namespace grape
 
       // set material
       G4String type = "";
-      G4int dtype = 0;
-      
       auto matName = logical->GetMaterial()->GetName();
-      if ( matName == "G4_CESIUM_IODIDE" ) {
-      	type = "CsI";
-      	dtype = 2;
-      }
-      else if ( matName == "G4_PLASTIC_SC_VINYLTOLUENE" ) {
-      	type = "Plastic";
-      	dtype = 1;
-      }
-      else if ( matName == "G4_TERPHENYL" ) {
-      	type = "p-Terphenyl";
-      	dtype = 1;
-      }
-      else if ( matName == "GAGG" ) {
-      	type = "GAGG";
-      	dtype = 2;
-      }
+      if ( matName == "G4_CESIUM_IODIDE" ) type = "CsI";
+      else if ( matName == "G4_PLASTIC_SC_VINYLTOLUENE" ) type = "Plastic";
+      else if ( matName == "G4_STILBENE" ) type = "Stilbene";
+      else if ( matName == "G4_TERPHENYL" ) type = "p-Terphenyl";
+      else if ( matName == "GAGG" ) type = "GAGG";
       else {
         G4cerr << "---> Type: " << matName << G4endl;
         type = "unknown";
-        dtype = 0;
       }
       hit->SetType( type );
-      hit->SetDetType( dtype );
 
       // set the volume id
       hit->SetID( copyNo );
