diff --git a/../../GRAPE-MM/include/ActionInitialization.hh b/../../GRAPE-CE/include/ActionInitialization.hh
old mode 100644
new mode 100755
index 790c37c..22c07d5
--- a/../../GRAPE-MM/include/ActionInitialization.hh
+++ b/../../GRAPE-CE/include/ActionInitialization.hh
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
 /// \file ActionInitialization.hh
diff --git a/../../GRAPE-MM/include/Constants.hh b/../../GRAPE-CE/include/Constants.hh
old mode 100644
new mode 100755
index 3fdf754..dce2432
--- a/../../GRAPE-MM/include/Constants.hh
+++ b/../../GRAPE-CE/include/Constants.hh
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
 /// \file Constants.hh
@@ -27,43 +27,33 @@ namespace grape
   ///
   //****************************************************************************
   constexpr auto kNumKeep = 8;
-  
-  
-  //--------------------------------------------------------
-  // WORLD Volume Dimesnions
-  //--------------------------------------------------------
-  constexpr auto kWorld_Xsize = 5.0*m;
-  constexpr auto kWorld_Ysize = 5.0*m;
-  constexpr auto kWorld_Zsize = 5.0*m;
-  
+  constexpr auto kDim = 245;
+  constexpr auto kNumC = 145;
+  constexpr auto kNumP = 100;
+
   //--------------------------------------------------------
-  // Scintillator Element Dimensions
+  // SCINTILLATOR
   //--------------------------------------------------------
   constexpr auto kScint_Xsize = 12.5*mm;
   constexpr auto kScint_Ysize = 12.5*mm;
   constexpr auto kScint_Zsize = 12.5*mm;
 
-  //--------------------------------------------------------
-  // Scintillator Pitch
-  //--------------------------------------------------------
-  //constexpr auto kScint_Xpitch = 21.1*mm;
-  //constexpr auto kScint_Ypitch = 21.1*mm;
-  
   constexpr auto kScint_Xpitch = 21.1*mm;
   constexpr auto kScint_Ypitch = 21.1*mm;
   constexpr auto kScint_Zpitch = 20.0*mm;
 
-  //--------------------------------------------------------
-  // Scintillator Array Dimensions
-  //--------------------------------------------------------
   constexpr auto kNumScint_X = 7;
   constexpr auto kNumScint_Y = 7;
   constexpr auto kNumScint_Z = 5;
 
+  constexpr auto kNumScint = kNumScint_X * kNumScint_Y * kNumScint_Z;
+
   //--------------------------------------------------------
-  // Total Number of Scintillators
+  // CALIBRATION SOURCE
   //--------------------------------------------------------
-  constexpr auto kNumScint = kNumScint_X * kNumScint_Y * kNumScint_Z;
+  constexpr auto kCal_Rmin = 0.0*mm;
+  constexpr auto kCal_Rmax = 5.0*mm;
+  constexpr auto kCal_Zsize = 10.0*mm;
 
   //--------------------------------------------------------
   // Optical Pad
@@ -86,9 +76,6 @@ namespace grape
   constexpr auto kSiPM_PCB_Ysize = kSiPM_Xsize;
   constexpr auto kSiPM_PCB_Zsize = 1.6*mm;
 
-  //--------------------------------------------------------
-  // SiPM Gap
-  //-------------------------------------------------------- 
   // constexpr auto kDet_Gap = 2.0*mm;
   constexpr auto kDet_Gap = ( 107.0*mm - 
                   5 * ( kScint_Zsize + 
@@ -135,19 +122,19 @@ namespace grape
   //--------------------------------------------------------
   // constexpr auto kMIB_Xsize = 164.0*mm;
   // constexpr auto kMIB_Ysize = 164.0*mm;
-  constexpr auto kMIB_Xsize = kNumScint_X * kScint_Xpitch + 10.0*mm;
-  constexpr auto kMIB_Ysize = kNumScint_Y * kScint_Ypitch + 10.0*mm;
+  constexpr auto kMIB_Xsize = 152.0*mm;
+  constexpr auto kMIB_Ysize = 152.0*mm;
   constexpr auto kMIB_Zsize = 1.5*mm;
-  constexpr auto kAPB_MIB_Zoffset = 2.0*mm;
-  
+
   //--------------------------------------------------------
   // Analog Power Board (APB)
   //--------------------------------------------------------
   constexpr auto kAPB_Xsize = 1.5*mm;
   constexpr auto kAPB_Ysize = 147.0*mm;
   constexpr auto kAPB_Zsize = 120.0*mm;
-  constexpr auto kAPB_Zoffset = 4.0*mm; // baseplate offset
 
+  constexpr auto kAPB_Zoffset = 4.0*mm; // baseplate offset
+  constexpr auto kAPB_MIB_Zoffset = 2.0*mm;
 
   //--------------------------------------------------------
   // APB - MIB Connectors
@@ -160,26 +147,10 @@ namespace grape
   // Enclosure (ENCL) Base Plate 
   //--------------------------------------------------------
   constexpr auto kENCL_Thickness = 5.0*mm;
-  constexpr auto kENCL_Bot_Xsize = kNumScint_X * kScint_Xpitch + 20.0*mm;
-  constexpr auto kENCL_Bot_Ysize = kNumScint_X * kScint_Ypitch + 20.0*mm;
+  constexpr auto kENCL_Bot_Xsize = 162.0*mm;
+  constexpr auto kENCL_Bot_Ysize = 162.0*mm;
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
@@ -243,11 +214,9 @@ namespace grape
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
@@ -272,59 +241,17 @@ namespace grape
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
 
   //--------------------------------------------------------
-  // Enclosure (SHPB) Side - Lead
+  // WORLD
   //--------------------------------------------------------
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
-
-
-
-
+  constexpr auto kWorld_Xsize = 5.0*m;
+  constexpr auto kWorld_Ysize = 5.0*m;
+  constexpr auto kWorld_Zsize = 5.0*m;
 }
 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 
diff --git a/../../GRAPE-MM/include/DetectorConstruction.hh b/../../GRAPE-CE/include/DetectorConstruction.hh
old mode 100644
new mode 100755
index edaf8ed..ae94d4d
--- a/../../GRAPE-MM/include/DetectorConstruction.hh
+++ b/../../GRAPE-CE/include/DetectorConstruction.hh
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
 /// \file DetectorConstruction.hh
@@ -42,11 +42,7 @@ namespace grape
       
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
@@ -56,13 +52,6 @@ namespace grape
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
diff --git a/../../GRAPE-MM/include/DetectorMessenger.hh b/../../GRAPE-CE/include/DetectorMessenger.hh
old mode 100644
new mode 100755
index f1dbeae..ad3f5a9
--- a/../../GRAPE-MM/include/DetectorMessenger.hh
+++ b/../../GRAPE-CE/include/DetectorMessenger.hh
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
diff --git a/../../GRAPE-MM/include/EventAction.hh b/../../GRAPE-CE/include/EventAction.hh
old mode 100644
new mode 100755
index 6cdffc6..4c384c5
--- a/../../GRAPE-MM/include/EventAction.hh
+++ b/../../GRAPE-CE/include/EventAction.hh
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
diff --git a/../../GRAPE-MM/include/PhysicsList.hh b/../../GRAPE-CE/include/PhysicsList.hh
old mode 100644
new mode 100755
index e8bc985..63194f9
--- a/../../GRAPE-MM/include/PhysicsList.hh
+++ b/../../GRAPE-CE/include/PhysicsList.hh
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
 /// \file PhysicsList.hh
diff --git a/../../GRAPE-MM/include/PhysicsListMessenger.hh b/../../GRAPE-CE/include/PhysicsListMessenger.hh
old mode 100644
new mode 100755
index 789ea6a..82c6289
--- a/../../GRAPE-MM/include/PhysicsListMessenger.hh
+++ b/../../GRAPE-CE/include/PhysicsListMessenger.hh
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
 /// \file PhysicsListMessenger.hh
 /// \brief Definition of the PhysicsListMessenger class
diff --git a/../../GRAPE-MM/include/PrimaryGeneratorAction.hh b/../../GRAPE-CE/include/PrimaryGeneratorAction.hh
old mode 100644
new mode 100755
index 8484e1f..db5d047
--- a/../../GRAPE-MM/include/PrimaryGeneratorAction.hh
+++ b/../../GRAPE-CE/include/PrimaryGeneratorAction.hh
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
diff --git a/../../GRAPE-MM/include/RunAction.hh b/../../GRAPE-CE/include/RunAction.hh
old mode 100644
new mode 100755
index 22e3160..1807545
--- a/../../GRAPE-MM/include/RunAction.hh
+++ b/../../GRAPE-CE/include/RunAction.hh
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
diff --git a/../../GRAPE-MM/include/ScintHit.hh b/../../GRAPE-CE/include/ScintHit.hh
old mode 100644
new mode 100755
index b4703f2..663e302
--- a/../../GRAPE-MM/include/ScintHit.hh
+++ b/../../GRAPE-CE/include/ScintHit.hh
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
 
diff --git a/../../GRAPE-MM/include/ScintSD.hh b/../../GRAPE-CE/include/ScintSD.hh
old mode 100644
new mode 100755
index 8360c44..7583a05
--- a/../../GRAPE-MM/include/ScintSD.hh
+++ b/../../GRAPE-CE/include/ScintSD.hh
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
 
