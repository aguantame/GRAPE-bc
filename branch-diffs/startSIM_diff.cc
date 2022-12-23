diff --git a/../GRAPE-MM/startSIM.cc b/../GRAPE-CE/startSIM.cc
old mode 100644
new mode 100755
index 570d5f1..1409f2d
--- a/../GRAPE-MM/startSIM.cc
+++ b/../GRAPE-CE/startSIM.cc
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
 /// \file startSIM.cc
@@ -47,7 +47,6 @@ int main(int argc,char** argv)
   
   G4String macro;
   G4String session;
-  G4bool verboseBestUnits = true;
 #ifdef G4MULTITHREADED
   G4int nThreads = 0;
 #endif
@@ -59,10 +58,6 @@ int main(int argc,char** argv)
       nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
     }
 #endif
-    else if ( G4String(argv[i]) == "-vDefault" ) {
-      verboseBestUnits = false;
-      --i;  // this option is not followed with a parameter
-    }
     else {
       PrintUsage();
       return 1;
@@ -120,7 +115,7 @@ int main(int argc,char** argv)
   }
   else  {  
     // interactive mode : define UI session
-    UImanager->ApplyCommand("/control/execute macros/init_vis.mac");
+    UImanager->ApplyCommand("/control/execute ../macros/init_vis.mac");
     // if (ui->IsGUI()) {
     //   UImanager->ApplyCommand("/control/execute macros/gui.mac");
     // }
