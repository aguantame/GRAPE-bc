diff --git a/../../sims/GRAPE-simulation/include/.DS_Store b/../../sims/GRAPE-simulation/include/.DS_Store
deleted file mode 100644
index 9b54243..0000000
Binary files a/../../sims/GRAPE-simulation/include/.DS_Store and /dev/null differ
diff --git a/../../sims/GRAPE-simulation/include/ActionInitialization.hh b/GRAPE-CE/include/ActionInitialization.hh
old mode 100644
new mode 100755
index e3f27e0..22c07d5
--- a/../../sims/GRAPE-simulation/include/ActionInitialization.hh
+++ b/GRAPE-CE/include/ActionInitialization.hh
@@ -1,14 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  August 2023 Balloon Flight Campaign
-//  (V1) Created: Mar 2, 2022 by Camden Ertley
-//  (V2) Created: September 23, 2022 by Camden Ertley
-//  (V3) Edited: Dec 26, 2022 by Karla Onate Melecio
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file ActionInitialization.hh
diff --git a/../../sims/GRAPE-simulation/include/Constants.hh b/GRAPE-CE/include/Constants.hh
old mode 100644
new mode 100755
index 7033de8..dce2432
--- a/../../sims/GRAPE-simulation/include/Constants.hh
+++ b/GRAPE-CE/include/Constants.hh
@@ -1,14 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  August 2023 Balloon Flight Campaign
-//  (V1) Created: Mar 2, 2022 by Camden Ertley
-//  (V2) Created: September 23, 2022 by Camden Ertley
-//  (V3) Edited: Dec 26, 2022 by Karla Onate Melecio
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file Constants.hh
@@ -29,13 +27,12 @@ namespace grape
   ///
   //****************************************************************************
   constexpr auto kNumKeep = 8;
-  
   constexpr auto kDim = 245;
   constexpr auto kNumC = 145;
-  constexpr auto kNumP = 100; //! not including tagged sources
-  
+  constexpr auto kNumP = 100;
+
   //--------------------------------------------------------
-  // Scintillator Elements and Array
+  // SCINTILLATOR
   //--------------------------------------------------------
   constexpr auto kScint_Xsize = 12.5*mm;
   constexpr auto kScint_Ysize = 12.5*mm;
@@ -43,9 +40,7 @@ namespace grape
 
   constexpr auto kScint_Xpitch = 21.1*mm;
   constexpr auto kScint_Ypitch = 21.1*mm;
-  constexpr auto kScint_Zpitch = 21.84*mm; //! based on avg measurements
-  // constexpr auto kScint_Zpitch = 17.5*mm;
-
+  constexpr auto kScint_Zpitch = 20.0*mm;
 
   constexpr auto kNumScint_X = 7;
   constexpr auto kNumScint_Y = 7;
@@ -53,60 +48,46 @@ namespace grape
 
   constexpr auto kNumScint = kNumScint_X * kNumScint_Y * kNumScint_Z;
 
-  // Calibration source
+  //--------------------------------------------------------
+  // CALIBRATION SOURCE
+  //--------------------------------------------------------
   constexpr auto kCal_Rmin = 0.0*mm;
   constexpr auto kCal_Rmax = 5.0*mm;
   constexpr auto kCal_Zsize = 10.0*mm;
 
   //--------------------------------------------------------
-  // Optical Interface and Readout Board
-  //--------------------------------------------------------
-
   // Optical Pad
+  //--------------------------------------------------------
   constexpr auto kOpticalPad_Xsize = kScint_Xsize;
   constexpr auto kOpticalPad_Ysize = kScint_Ysize;
   constexpr auto kOpticalPad_Zsize = 1.0*mm;
 
+  //--------------------------------------------------------
   // SiPM (Hamamatsu S13361-3050NE-04)
+  //--------------------------------------------------------
   constexpr auto kSiPM_Xsize = 13.0*mm;
   constexpr auto kSiPM_Ysize = 13.0*mm;
   constexpr auto kSiPM_Zsize = 1.35*mm;
 
+  //--------------------------------------------------------
   // SiPM Power Board
+  //--------------------------------------------------------
   constexpr auto kSiPM_PCB_Xsize = kSiPM_Xsize;
   constexpr auto kSiPM_PCB_Ysize = kSiPM_Xsize;
-  constexpr auto kSiPM_PCB_Zsize = 1.57*mm;
+  constexpr auto kSiPM_PCB_Zsize = 1.6*mm;
 
+  // constexpr auto kDet_Gap = 2.0*mm;
+  constexpr auto kDet_Gap = ( 107.0*mm - 
+                  5 * ( kScint_Zsize + 
+                    kOpticalPad_Zsize + 
+                    kSiPM_Zsize + 
+                    kSiPM_PCB_Zsize ) ) / 5;
 
   //--------------------------------------------------------
-  // Detector Elements
+  // DETECTOR Element
   //--------------------------------------------------------
-  //! Individual Det Assembly
-  constexpr auto kDetAssembly_Zsize = kScint_Zsize + kOpticalPad_Zsize + kSiPM_Zsize + kSiPM_PCB_Zsize;
-  
-  //! Scintillator wrap  (adds ~2.05 mm in xyz)
-  constexpr auto kDetWrap_Thickness = 1.025*mm;
-
-  constexpr auto kDetWrap_Xsize = kSiPM_Xsize + 2*kDetWrap_Thickness;
-  constexpr auto kDetWrap_Ysize = kSiPM_Ysize + 2*kDetWrap_Thickness;
-  constexpr auto kDetWrap_Zsize = kDetAssembly_Zsize + 2*kDetWrap_Thickness;
-
-  constexpr auto kDetWrap_Hole_Xsize = kSiPM_Xsize;
-  constexpr auto kDetWrap_Hole_Ysize = kSiPM_Ysize;
-  constexpr auto kDetWrap_Hole_Zsize = kDetAssembly_Zsize;
-
-  constexpr auto kWrappedDetAssembly_Zsize = kScint_Zsize + kOpticalPad_Zsize + kSiPM_Zsize + kSiPM_PCB_Zsize + 2*kDetWrap_Thickness;
-
-  //! SiPM Gap (5.07 mm without wrap based on drawings)
-  constexpr auto kDet_Gap = 21.84 -
-                           (kScint_Zsize + 
-                            kOpticalPad_Zsize + 
-                            kSiPM_Zsize + 
-                            kSiPM_PCB_Zsize + 
-                            kDetWrap_Thickness); //! Where does the 107 come from?
-
   constexpr auto kDetElement_Xsize = kSiPM_Xsize;
-  constexpr auto kDetElement_Ysize = kSiPM_Ysize;
+  constexpr auto kDetElement_Ysize = kSiPM_Xsize;
   constexpr auto kDetElement_Zsize = 
                   kScint_Zsize +
                   kOpticalPad_Zsize +
@@ -114,104 +95,62 @@ namespace grape
                   kSiPM_PCB_Zsize +
                   kDet_Gap;
 
-  //! Vertical Circuit Boards (VCB)
-  constexpr auto kVCB_Thickness = 0.7874*mm;
-
-  //   constexpr auto kVCB_XYsize = 14.224*mm;
-  constexpr auto kfullVCB_Zsize = 110.998*mm;
-  constexpr auto kVCB_Zsize = 110.998*mm;
-  // constexpr auto kVCB_Zsize = kfullVCB_Zsize - (kfullVCB_Zsize - (kNumScint_Z *kScint_Zpitch));
-  constexpr auto kVCB_Side1_Xsize = kVCB_Thickness;
-  constexpr auto kVCB_Side1_Ysize = kSiPM_Ysize + 2*kDetWrap_Thickness;
-  constexpr auto kVCB_Side1_Zsize = kVCB_Zsize;
-  // constexpr auto kVCB_Side1_Zsize = kDetElement_Zsize * kNumScint_Z;
-
-  constexpr auto kVCB_Side2_Xsize = kSiPM_Xsize + 2*kDetWrap_Thickness;
-  constexpr auto kVCB_Side2_Ysize = kVCB_Thickness;
-  constexpr auto kVCB_Side2_Zsize = kVCB_Side1_Zsize;   
-
-
-  // Detector Housing (115*mm assembled height without pins)
-  constexpr auto kScint_Case_Thickness = 1.91*mm;
-
-  constexpr auto kScint_Case_Top_Xsize = 20.8*mm;
-  constexpr auto kScint_Case_Top_Ysize = 20.8*mm;
-  constexpr auto kScint_Case_Top_Zsize = 7.20*mm;
-
-  constexpr auto kScint_Case_Bot_Xsize = 20.8*mm;
-  constexpr auto kScint_Case_Bot_Ysize = 20.8*mm;
-  constexpr auto kScint_Case_Bot_Zsize = 8.20*mm;
-
-  constexpr auto kScint_Case_Xsize = 22.62*mm;
-  constexpr auto kScint_Case_Ysize = 22.62*mm;
-  constexpr auto kScint_Case_Zsize = 99.60*mm;
-
-  constexpr auto kScint_Case_Hole_Xsize = kScint_Case_Xsize - 2*kScint_Case_Thickness;
-  constexpr auto kScint_Case_Hole_Ysize = kScint_Case_Ysize - 2*kScint_Case_Thickness;
-  constexpr auto kScint_Case_Hole_Zsize = 2*kScint_Case_Zsize + 2*kScint_Case_Thickness;
-
-// O-Ring (rectangular shape assumed)
-  constexpr auto kORing_Thickness = 1.5*mm;
-
-  constexpr auto kORing_Xsize = kScint_Case_Hole_Xsize;
-  constexpr auto kORing_Ysize = kScint_Case_Hole_Xsize;
-  constexpr auto kORing_Zsize = kORing_Thickness;
-
-  constexpr auto kORing_Hole_Xsize = kSiPM_Xsize + 2*kDetWrap_Thickness + 2*kVCB_Thickness;
-  constexpr auto kORing_Hole_Ysize = kSiPM_Ysize + 2*kDetWrap_Thickness + 2*kVCB_Thickness;
-  constexpr auto kORing_Hole_Zsize = 2*kORing_Zsize + 2*kORing_Thickness;
-
-
-
   //--------------------------------------------------------
-  // Electronics
+  // SCINTILLATOR CASE
   //--------------------------------------------------------
+  constexpr auto kScint_Case_Thickness = 2.0*mm;
+
+  constexpr auto kScint_Case_Top_Xsize = kSiPM_Xsize + kScint_Case_Thickness;
+  constexpr auto kScint_Case_Top_Ysize = kSiPM_Ysize + kScint_Case_Thickness;
+  constexpr auto kScint_Case_Top_Zsize = 10.0*mm;
 
+  constexpr auto kScint_Case_Bot_Xsize = kSiPM_Xsize + kScint_Case_Thickness;
+  constexpr auto kScint_Case_Bot_Ysize = kSiPM_Ysize + kScint_Case_Thickness;
+  constexpr auto kScint_Case_Bot_Zsize = 8.0*mm;
 
+  constexpr auto kScint_Case_Xsize = kSiPM_Xsize + 2*kScint_Case_Thickness;
+  constexpr auto kScint_Case_Ysize = kSiPM_Ysize + 2*kScint_Case_Thickness;
+  // constexpr auto kScint_Case_Zsize = 107*mm;
+  constexpr auto kScint_Case_Zsize = 
+                  kDetElement_Zsize * kNumScint_Z +
+                  kScint_Case_Thickness -
+                  kScint_Case_Top_Zsize - 
+                  kScint_Case_Bot_Zsize;
 
+  //--------------------------------------------------------
   // Module Interface Board (MIB)
-  constexpr auto kMIB_Xsize = 152.0;
-  constexpr auto kMIB_Ysize = 152.0;
+  //--------------------------------------------------------
+  // constexpr auto kMIB_Xsize = 164.0*mm;
+  // constexpr auto kMIB_Ysize = 164.0*mm;
+  constexpr auto kMIB_Xsize = 152.0*mm;
+  constexpr auto kMIB_Ysize = 152.0*mm;
   constexpr auto kMIB_Zsize = 1.5*mm;
 
+  //--------------------------------------------------------
   // Analog Power Board (APB)
+  //--------------------------------------------------------
   constexpr auto kAPB_Xsize = 1.5*mm;
   constexpr auto kAPB_Ysize = 147.0*mm;
   constexpr auto kAPB_Zsize = 120.0*mm;
+
   constexpr auto kAPB_Zoffset = 4.0*mm; // baseplate offset
+  constexpr auto kAPB_MIB_Zoffset = 2.0*mm;
 
+  //--------------------------------------------------------
   // APB - MIB Connectors
-  constexpr auto kAPB_MIB_Zoffset = 2.0*mm;
+  //--------------------------------------------------------
   constexpr auto kAPB_Con_Xsize = 5.0*mm;
   constexpr auto kAPB_Con_Ysize = 75.0*mm;
   constexpr auto kAPB_Con_Zsize = 10.0*mm;
 
   //--------------------------------------------------------
-  // Instrument Structural Compenents
-  //--------------------------------------------------------
-
   // Enclosure (ENCL) Base Plate 
+  //--------------------------------------------------------
   constexpr auto kENCL_Thickness = 5.0*mm;
   constexpr auto kENCL_Bot_Xsize = 162.0*mm;
   constexpr auto kENCL_Bot_Ysize = 162.0*mm;
   constexpr auto kENCL_Bot_Zsize = kENCL_Thickness;
 
-  //--------------------------------------------------------
-  // Shield (SHSN) Base Plate - Tin
-  //--------------------------------------------------------
-  constexpr auto kSHSN_Thickness = 2.0*mm;
-  constexpr auto kSHSN_Bot_Xsize = kENCL_Bot_Xsize + 2.0*kENCL_Thickness;
-  constexpr auto kSHSN_Bot_Ysize = kENCL_Bot_Ysize + 2.0*kENCL_Thickness;
-  constexpr auto kSHSN_Bot_Zsize = kSHSN_Thickness;
-
-  //--------------------------------------------------------
-  // Shield (SHPB) Base Plate - Lead
-  //--------------------------------------------------------
-  constexpr auto kSHPB_Thickness = 4.0*mm;
-  constexpr auto kSHPB_Bot_Xsize = kENCL_Bot_Xsize + 2.0*kENCL_Thickness + 2.0*kSHSN_Thickness;
-  constexpr auto kSHPB_Bot_Ysize = kENCL_Bot_Ysize + 2.0*kENCL_Thickness + 2.0*kSHSN_Thickness;
-  constexpr auto kSHPB_Bot_Zsize = kSHPB_Thickness;
-
   //--------------------------------------------------------
   // Enclosure (ENCL) Top
   //--------------------------------------------------------
@@ -275,11 +214,9 @@ namespace grape
   //--------------------------------------------------------
   // MODULE
   //--------------------------------------------------------
-  constexpr auto kModule_Xsize = kENCL_Bot_Xsize + 2*kENCL_Thickness + 2*kSHSN_Thickness + 2*kSHPB_Thickness;
-  constexpr auto kModule_Ysize = kENCL_Bot_Ysize + 2*kENCL_Thickness + 2*kSHSN_Thickness + 2*kSHPB_Thickness;
+  constexpr auto kModule_Xsize = kENCL_Bot_Xsize + 2*kENCL_Thickness;
+  constexpr auto kModule_Ysize = kENCL_Bot_Ysize + 2*kENCL_Thickness;
   constexpr auto kModule_Zsize = 
-  			      kSHPB_Bot_Zsize +
-				  kSHSN_Bot_Zsize +
                   kENCL_Bot_Zsize +
                   kAPB_Zoffset +
                   kAPB_Zsize +
@@ -304,55 +241,10 @@ namespace grape
                   kENCL_Top_Zoffset +
                   kENCL_Top_Zsize;
 
-  constexpr auto kENCL_Side2_Xsize = kENCL_Bot_Ysize + 2*kENCL_Thickness;
+  constexpr auto kENCL_Side2_Xsize = kENCL_Bot_Ysize;
   constexpr auto kENCL_Side2_Ysize = kENCL_Thickness;
   constexpr auto kENCL_Side2_Zsize = kENCL_Side1_Zsize;
 
-  //--------------------------------------------------------
-  // Enclosure (SHSN) Side - Tin
-  //--------------------------------------------------------
-  constexpr auto kSHSN_Side1_Xsize = kSHSN_Thickness;
-  constexpr auto kSHSN_Side1_Ysize = kSHSN_Bot_Ysize + 2*kSHSN_Thickness;
-  constexpr auto kSHSN_Side1_Zsize = 
-                  kSHSN_Bot_Zsize +
-                  kENCL_Bot_Zsize +
-                  kAPB_Zoffset +
-                  kAPB_Zsize +
-                  kAPB_MIB_Zoffset +
-                  kMIB_Zsize +
-                  kMIBP_Zoffset +
-                  kMIBP_Zsize +
-                  kScint_Case_Zsize +
-                  kENCL_Top_Zoffset +
-                  kENCL_Top_Zsize;
-
-  constexpr auto kSHSN_Side2_Xsize = kSHSN_Bot_Ysize + 2*kSHSN_Thickness;
-  constexpr auto kSHSN_Side2_Ysize = kSHSN_Thickness;
-  constexpr auto kSHSN_Side2_Zsize = kSHSN_Side1_Zsize;
-
-
-  //--------------------------------------------------------
-  // Enclosure (SHPB) Side - Lead
-  //--------------------------------------------------------
-  constexpr auto kSHPB_Side1_Xsize = kSHPB_Thickness;
-  constexpr auto kSHPB_Side1_Ysize = kSHPB_Bot_Ysize + 2*kSHPB_Thickness;
-  constexpr auto kSHPB_Side1_Zsize = 
-                  kSHPB_Bot_Zsize +
-                  kSHSN_Bot_Zsize +
-                  kENCL_Bot_Zsize +
-                  kAPB_Zoffset +
-                  kAPB_Zsize +
-                  kAPB_MIB_Zoffset +
-                  kMIB_Zsize +
-                  kMIBP_Zoffset +
-                  kMIBP_Zsize +
-                  kScint_Case_Zsize +
-                  kENCL_Top_Zoffset +
-                  kENCL_Top_Zsize;
-
-  constexpr auto kSHPB_Side2_Xsize = kSHPB_Bot_Ysize + 2*kSHPB_Thickness;
-  constexpr auto kSHPB_Side2_Ysize = kSHPB_Thickness;
-  constexpr auto kSHPB_Side2_Zsize = kSHPB_Side1_Zsize;
 
   //--------------------------------------------------------
   // WORLD
@@ -360,8 +252,6 @@ namespace grape
   constexpr auto kWorld_Xsize = 5.0*m;
   constexpr auto kWorld_Ysize = 5.0*m;
   constexpr auto kWorld_Zsize = 5.0*m;
-
-
 }
 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 
diff --git a/../../sims/GRAPE-simulation/include/DetectorConstruction.hh b/GRAPE-CE/include/DetectorConstruction.hh
old mode 100644
new mode 100755
index e5e1e40..ae94d4d
--- a/../../sims/GRAPE-simulation/include/DetectorConstruction.hh
+++ b/GRAPE-CE/include/DetectorConstruction.hh
@@ -1,14 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  August 2023 Balloon Flight Campaign
-//  (V1) Created: Mar 2, 2022 by Camden Ertley
-//  (V2) Created: September 23, 2022 by Camden Ertley
-//  (V3) Edited: Dec 26, 2022 by Karla Onate Melecio
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file DetectorConstruction.hh
@@ -17,38 +15,6 @@
 #ifndef DetectorConstruction_h
 #define DetectorConstruction_h 1
 
-
-#include "G4RunManager.hh"
-#include "G4GeometryManager.hh"
-#include "G4PhysicalVolumeStore.hh"
-#include "G4LogicalVolumeStore.hh"
-#include "G4SolidStore.hh"
-
-#include "G4Material.hh"
-#include "G4NistManager.hh"
-
-#include "G4Box.hh"
-#include "G4Tubs.hh"
-#include "G4Sphere.hh"
-#include "G4Cons.hh"
-#include "G4UnionSolid.hh"
-#include "G4SubtractionSolid.hh"
-
-#include "G4LogicalVolume.hh"
-#include "G4PVPlacement.hh"
-#include "G4AutoDelete.hh"
-
-#include "G4UserLimits.hh"
-#include "G4SDManager.hh"
-
-#include "G4VisAttributes.hh"
-#include "G4Colour.hh"
-
-#include "G4PhysicalConstants.hh"
-#include "G4SystemOfUnits.hh"
-
-#include "G4AssemblyVolume.hh"
-
 #include "globals.hh"
 #include "G4VUserDetectorConstruction.hh"
 
@@ -76,11 +42,7 @@ namespace grape
       
       // set methods
       void SetOverlapFlag( G4bool flag ) {fCheckOverlaps = flag;};          
-      void SetZenithAngle( G4double zang );          
-      void SetAzimuthAngle( G4double aang );          
-      void SetPolarizationAngle( G4double pang );          
-      void UpdateGeometry();
-
+ 
     private:
       // methods
       void DefineMaterials();
@@ -90,13 +52,6 @@ namespace grape
       DetectorMessenger* fDetMessenger = nullptr;   // messenger
 
       G4bool fCheckOverlaps = true; // option to activate checking of volumes overlaps
-
-      G4VPhysicalVolume* fPhysicalModule = nullptr;
-      G4VPhysicalVolume* fPhysicalCollimator = nullptr;
-      
-      G4double fZenithAngle = 0.;
-      G4double fAzimuthAngle = 0.;
-      G4double fPolarizationAngle = 0.;
   };
 }
 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
diff --git a/../../sims/GRAPE-simulation/include/DetectorMessenger.hh b/GRAPE-CE/include/DetectorMessenger.hh
old mode 100644
new mode 100755
index f1dbeae..ad3f5a9
--- a/../../sims/GRAPE-simulation/include/DetectorMessenger.hh
+++ b/GRAPE-CE/include/DetectorMessenger.hh
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
@@ -51,11 +51,6 @@ namespace grape
       
       G4UIcmdWithABool* fOverlapCmd = nullptr;
 
-      G4UIcmdWithADoubleAndUnit* fZenithCmd = nullptr;
-      G4UIcmdWithADoubleAndUnit* fAzimuthCmd = nullptr;
-      G4UIcmdWithADoubleAndUnit* fPolarizationCmd = nullptr;
-
-      G4UIcmdWithoutParameter* fUpdateCmd = nullptr;
   };
 
 }
diff --git a/../../sims/GRAPE-simulation/include/EventAction.hh b/GRAPE-CE/include/EventAction.hh
old mode 100644
new mode 100755
index 6cdffc6..4c384c5
--- a/../../sims/GRAPE-simulation/include/EventAction.hh
+++ b/GRAPE-CE/include/EventAction.hh
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
 /// \file EventAction.hh
@@ -19,14 +19,15 @@
 #include "G4UserEventAction.hh"
 
 #include "ScintHit.hh"
+#include "Constants.hh"
+
+#include <array>
+#include <vector>
 
 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 namespace grape
 {
 
-  class PrimaryGeneratorAction;
-  class RunAction;
-
   //****************************************************************************
   /// Event action class
   ///
@@ -41,12 +42,26 @@ namespace grape
       void  BeginOfEventAction(const G4Event* ) override;
       void    EndOfEventAction(const G4Event* ) override;
 
+      // methods
+      std::vector<G4int>& GetID() { return fID; }
+      std::vector<G4double>& GetEdep() { return fEdep; }
+      std::vector<G4double>& GetGEB() { return fGEB; }
+      std::vector<G4double>& GetTime() { return fTime; }
+
     private:      
       // methods
       G4double BroadenEnergy(const G4String& type, G4double energy);
 
       // data members
       G4int  fScintHCID = -1;
+
+      std::vector<G4int> fID;
+      std::vector<G4double> fEdep;
+      std::vector<G4double> fGEB;
+      std::vector<G4double> fTime;
+      // std::vector<G4double> fEdep = std::vector<G4double>(kDim);
+      // std::vector<G4double> fGEB = std::vector<G4double>(kDim);
+      // std::vector<G4double> fTime = std::vector<G4double>(kDim);
   };
                      
 }
diff --git a/../../sims/GRAPE-simulation/include/PhysicsList.hh b/GRAPE-CE/include/PhysicsList.hh
old mode 100644
new mode 100755
index c6c77d3..63194f9
--- a/../../sims/GRAPE-simulation/include/PhysicsList.hh
+++ b/GRAPE-CE/include/PhysicsList.hh
@@ -1,14 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  August 2023 Balloon Flight Campaign
-//  (V1) Created: Mar 2, 2022 by Camden Ertley
-//  (V2) Created: September 23, 2022 by Camden Ertley
-//  (V3) Edited: Dec 26, 2022 by Karla Onate Melecio
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file PhysicsList.hh
@@ -20,59 +18,6 @@
 #include "globals.hh"
 #include "G4VModularPhysicsList.hh"
 
-#include "G4DecayPhysics.hh"
-#include "G4RadioactiveDecayPhysics.hh"
-
-#include "G4EmStandardPhysics.hh"
-#include "G4EmStandardPhysics_option1.hh"
-#include "G4EmStandardPhysics_option2.hh"
-#include "G4EmStandardPhysics_option3.hh"
-#include "G4EmStandardPhysics_option4.hh"
-#include "G4EmStandardPhysicsGS.hh"
-#include "G4EmStandardPhysicsSS.hh"
-#include "G4EmStandardPhysicsWVI.hh"
-#include "G4EmLowEPPHysics.hh"
-#include "G4EmLivermorePhysics.hh"
-#include "G4EmLivermorePolarizedPhysics.hh"
-#include "G4EmPenelopePhysics.hh"
-#include "G4EmExtraPhysics.hh"
-#include "G4EmParameters.hh"
-
-#include "G4HadronElasticPhysics.hh"
-#include "G4HadronElasticPhysicsXS.hh"
-#include "G4HadronElasticPhysicsHP.hh"
-#include "G4HadronHElasticPhysics.hh"
-#include "G4ChargeExchangePhysics.hh"
-#include "G4NeutronTrackingCut.hh"
-#include "G4NeutronCrossSectionXS.hh"
-#include "G4StoppingPhysics.hh"
-#include "G4IonBinaryCascadePhysics.hh"
-#include "G4IonPhysics.hh"
-#include "G4IonPhysicsXS.hh"
-#include "G4IonElasticPhysics.hh"
-
-#include "G4HadronPhysicsFTFP_BERT.hh"
-#include "G4HadronPhysicsFTFP_BERT_HP.hh"
-#include "G4HadronPhysicsFTFP_BERT_TRV.hh"
-#include "G4HadronPhysicsFTF_BIC.hh"
-#include "G4HadronInelasticQBBC.hh"
-#include "G4HadronPhysicsQGSP_BERT.hh"
-#include "G4HadronPhysicsQGSP_BERT_HP.hh"
-#include "G4HadronPhysicsQGSP_BIC.hh"
-#include "G4HadronPhysicsQGSP_BIC_HP.hh"
-#include "G4HadronPhysicsQGSP_FTFP_BERT.hh"
-#include "G4HadronPhysicsQGS_BIC.hh"
-
-#include "G4ProcessManager.hh"
-#include "G4ParticleTypes.hh"
-#include "G4ParticleTable.hh"
-#include "G4Gamma.hh"
-#include "G4Electron.hh"
-#include "G4Positron.hh"
-#include "G4Proton.hh"
-
-
-
 class G4VPhysicsConstructor;
 
 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
diff --git a/../../sims/GRAPE-simulation/include/PhysicsListMessenger.hh b/GRAPE-CE/include/PhysicsListMessenger.hh
old mode 100644
new mode 100755
index e38c6c3..82c6289
--- a/../../sims/GRAPE-simulation/include/PhysicsListMessenger.hh
+++ b/GRAPE-CE/include/PhysicsListMessenger.hh
@@ -1,14 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  August 2023 Balloon Flight Campaign
-//  (V1) Created: Mar 2, 2022 by Camden Ertley
-//  (V2) Created: September 23, 2022 by Camden Ertley
-//  (V3) Edited: Dec 26, 2022 by Karla Onate Melecio
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
 //
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 /// \file PhysicsListMessenger.hh
 /// \brief Definition of the PhysicsListMessenger class
diff --git a/../../sims/GRAPE-simulation/include/PrimaryGeneratorAction.hh b/GRAPE-CE/include/PrimaryGeneratorAction.hh
old mode 100644
new mode 100755
index 8484e1f..db5d047
--- a/../../sims/GRAPE-simulation/include/PrimaryGeneratorAction.hh
+++ b/GRAPE-CE/include/PrimaryGeneratorAction.hh
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
 /// \file PrimaryGeneratorAction.hh
diff --git a/../../sims/GRAPE-simulation/include/RunAction.hh b/GRAPE-CE/include/RunAction.hh
old mode 100644
new mode 100755
index 22e3160..1807545
--- a/../../sims/GRAPE-simulation/include/RunAction.hh
+++ b/GRAPE-CE/include/RunAction.hh
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
 /// \file RunAction.hh
@@ -25,6 +25,8 @@ class G4Timer;
 namespace grape
 {
 
+  class EventAction;
+  
   //****************************************************************************
   /// Run action class
   ///
@@ -32,7 +34,7 @@ namespace grape
   class RunAction : public G4UserRunAction
   {
     public:
-      RunAction();
+      RunAction( EventAction* eventAct );
       ~RunAction() override;
 
       // methods from base class
@@ -43,6 +45,8 @@ namespace grape
       // data members
       G4Timer* fTimer = nullptr;
 
+      EventAction* fEventAction = nullptr;
+  
   };
 
 }
diff --git a/../../sims/GRAPE-simulation/include/ScintHit.hh b/GRAPE-CE/include/ScintHit.hh
old mode 100644
new mode 100755
index b4703f2..663e302
--- a/../../sims/GRAPE-simulation/include/ScintHit.hh
+++ b/GRAPE-CE/include/ScintHit.hh
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
 /// \file ScintHit.hh
@@ -70,15 +70,10 @@ namespace grape
 
       void SetType ( G4String& mat ) { fType = mat; }
       const G4String& GetType() const { return fType; }
-      
-      void SetDetType ( G4int det ) { fDetType = det; }
-      G4int GetDetType() const { return fDetType; }
-
         
     private:
       // data members
       G4int    fID = 0;
-      G4int    fDetType = 0;
 
       G4double fTime = 0.;
 
diff --git a/../../sims/GRAPE-simulation/include/ScintSD.hh b/GRAPE-CE/include/ScintSD.hh
old mode 100644
new mode 100755
index 8360c44..7583a05
--- a/../../sims/GRAPE-simulation/include/ScintSD.hh
+++ b/GRAPE-CE/include/ScintSD.hh
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
 /// \file ScintSD.hh
@@ -19,8 +19,6 @@
 
 #include "ScintHit.hh"
 
-#include <vector>
-
 class G4Step;
 class G4HCofThisEvent;
 
