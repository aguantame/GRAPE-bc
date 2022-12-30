diff --git a/../../sims/GRAPE-simulation/startSIM.cc b/GRAPE-CE/startSIM.cc
old mode 100644
new mode 100755
index 98ff1ad..1409f2d
--- a/../../sims/GRAPE-simulation/startSIM.cc
+++ b/GRAPE-CE/startSIM.cc
@@ -1,14 +1,12 @@
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
-//  
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//
 //
 //  Gamma-RAy Polarimeter Experiment (GRAPE)
-//  August 2023 Balloon Flight Campaign
-//  (V1) Created: Mar 2, 2022 by Camden Ertley
-//  (V2) Created: September 23, 2022 by Camden Ertley
-//  (V3) Edited: Dec 26, 2022 by Karla Onate Melecio
+//  2023 Balloon Flight Campaign
+//  Created: September 23, 2022 by Camden Ertley
 //
-// 
-//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
+//
+//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //
 //
 /// \file startSIM.cc
@@ -112,7 +110,7 @@ int main(int argc,char** argv)
   //
   if ( macro.size() ) {
     // batch mode
-    G4String command = "/control/execute ../macros/"; //! only name of macro file needs to be input if running ./startSIM from build dir
+    G4String command = "/control/execute ";
     UImanager->ApplyCommand(command+macro);
   }
   else  {  
