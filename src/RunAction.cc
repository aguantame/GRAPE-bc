//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
//  Gamma-RAy Polarimeter Experiment (GRAPE)
//  August 2023 Balloon Flight Campaign
//  (V1) Created: Mar 2, 2022 by Camden Ertley
//  (V2) Created: September 23, 2022 by Camden Ertley
//  (V3) Modified: Dec 26, 2022 by Karla Onate Melecio
//
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
/// \file RunAction.cc
/// \brief Implementation of the RunAction class

#include "RunAction.hh"
#include "Constants.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Timer.hh"
#include "G4UIcommand.hh"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  //****************************************************************************
  // Constructor
  //****************************************************************************
  RunAction::RunAction()
  { 
    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(100);     

    // Create analysis manager
    // The choice of the output format is done via the specified
    // file extension.
    auto analysisManager = G4AnalysisManager::Instance();


    // Create directories
    //
    //analysisManager->SetHistoDirectoryName("histograms");
    //analysisManager->SetNtupleDirectoryName("ntuple");

    // Default Settings
    //
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetDefaultFileType("root");
      // Note: If the filename extension is not provided, the default file 
      // type (root) will be used for all files specified without extension.
    analysisManager->SetNtupleMerging(true);
      // Note: merging ntuples is available only with Root output

    // Default output file
    //
    G4String fileName = "data/Test_ntuple.root";
    // Other supported output types:
    // G4String fileName = "data/Test_ntuple.csv";
    // G4String fileName = "data/Test_ntuple.hdf5";
    // G4String fileName = "data/Test_ntuple.xml";
    analysisManager->SetFileName(fileName);

    // Creating ntuple
    //
    analysisManager->CreateNtuple("data", "GRAPE Balooon Data");
    analysisManager->CreateNtupleIColumn("EventNumber");
    analysisManager->CreateNtupleIColumn("PrimaryEnergy");
    analysisManager->CreateNtupleIColumn("Hits");

    
    G4String col_name = "";
    for (G4int i=0; i<kNumKeep; i++ ) {
      std::ostringstream os;
      os << i;

      col_name = "D" + os.str() + "_ID";
      analysisManager->CreateNtupleIColumn( col_name );

      col_name = "D" + os.str() + "_PosX";
      analysisManager->CreateNtupleDColumn( col_name );

      col_name = "D" + os.str() + "_PosY";
      analysisManager->CreateNtupleDColumn( col_name );

      col_name = "D" + os.str() + "_PosZ";
      analysisManager->CreateNtupleDColumn( col_name );

      col_name = "D" + os.str() + "_Energy"; // Energy deposited
      analysisManager->CreateNtupleDColumn( col_name );

      col_name = "D" + os.str() + "_GEB"; // Gaussian Energy Broadening
      analysisManager->CreateNtupleDColumn( col_name );

      col_name = "D" + os.str() + "_BirkEnergy"; // Energy deposited with Birks
      analysisManager->CreateNtupleDColumn( col_name );

      col_name = "D" + os.str() + "_BirkGEB"; // Gaussian Energy Broadening
      analysisManager->CreateNtupleDColumn( col_name );

      col_name = "D" + os.str() + "_VisEnergy"; // Energy deposited with Birks
      analysisManager->CreateNtupleDColumn( col_name );

      col_name = "D" + os.str() + "_VisGEB"; // Gaussian Energy Broadening
      analysisManager->CreateNtupleDColumn( col_name );

      col_name = "D" + os.str() + "_Time";
      analysisManager->CreateNtupleDColumn( col_name );

      col_name = "D" + os.str() + "_Type";
      analysisManager->CreateNtupleSColumn( col_name );
      
      col_name = "D" + os.str() + "_DetType";
      analysisManager->CreateNtupleIColumn( col_name );

      // col_name = "D" + os.str() + "_PhysType";
      // analysisManager->CreateNtupleSColumn( col_name );

      os.clear();
    }

    analysisManager->CreateNtupleDColumn("TotalEnergy");

    analysisManager->FinishNtuple();

    // Create run timer
    if (isMaster) {
      fTimer = new G4Timer;
    }

  }

  //****************************************************************************
  // Destructor
  //****************************************************************************
  RunAction::~RunAction()
  {
    delete fTimer;
  }

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void RunAction::BeginOfRunAction(const G4Run* /*run*/)
  { 
    // start timer
    //
    if (isMaster) {
      fTimer->Start();
    }

    // inform the runManager to save random number seed
    // G4RunManager::GetRunManager()->SetRandomNumberStore(true);
    
    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // Open an output file
    // The default file name is set in RunAction::RunAction(),
    // it can be overwritten in a macro
    analysisManager->OpenFile();

  }

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void RunAction::EndOfRunAction(const G4Run* /*run*/)
  {
    auto analysisManager = G4AnalysisManager::Instance();

    // save histograms & ntuple
    //
    analysisManager->Write();
    analysisManager->CloseFile();

    // stop timer and print stats
    //
    if (isMaster) {
      fTimer->Stop();
      G4cout << G4endl;
      // G4cout << "  Events: " << iEvents << G4endl;
      // G4cout << "  Hits: " << iHits << G4endl;
      G4cout << "### Complete ###" << G4endl;
      G4cout << "  Timer: " << fTimer->GetRealElapsed() << " s" << G4endl;
      G4cout << G4endl;
    }

  }

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
