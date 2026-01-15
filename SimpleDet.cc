//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: SimpleDet.cc,v 1.16 2009-10-30 14:59:59 allison Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SimpleDetDetectorConstruction.hh"
#include "SimpleDetPhysicsList.hh"
#include "SimpleDetPrimaryGeneratorAction.hh"
#include "SimpleDetRunAction.hh"
#include "SimpleDetEventAction.hh"
#include "SimpleDetSteppingAction.hh"
#include "SimpleDetSteppingVerbose.hh"
#include "SimpleDetActionInitialization.hh"

#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "G4PhysListFactory.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{ //checks if there are 2 or 3 command-line arguments
if(argc == 2 || argc == 3)
	{
	// User Verbose output class
	//
	G4VSteppingVerbose* verbosity = new SimpleDetSteppingVerbose;
	G4VSteppingVerbose::SetInstance(verbosity);

	// Run manager
 	G4RunManager* runManager = new G4RunManager;

	// User Initialization classes (mandatory)
	//
	SimpleDetDetectorConstruction* detector = new SimpleDetDetectorConstruction;
	runManager->SetUserInitialization(detector);
	//
	//G4VUserPhysicsList* physics = new SimpleDetPhysicsList;
	G4PhysListFactory*physListFactory = new G4PhysListFactory();
	
	bool GoodList = false;
	string SelectedList = argv[1];
	for(unsigned int i = 0; i < physListFactory->AvailablePhysLists().size(); i++)
		{
		if(SelectedList.compare(physListFactory->AvailablePhysLists().at(i)) == 0)
			{
			GoodList = true;
			break;
			}
		}
	
	if(GoodList)
		{
		G4VUserPhysicsList * physics = physListFactory->GetReferencePhysList(argv[1]);	

		runManager->SetUserInitialization(physics);

		// User Action classes
		SimpleDetActionInitialization * temp_action_initialization = new SimpleDetActionInitialization;
		temp_action_initialization->SetDetector(detector);
		temp_action_initialization->SetPhysicsListName(argv[1]);
		G4VUserActionInitialization* action_initialization = temp_action_initialization;
		runManager->SetUserInitialization(action_initialization);

		// Initialize G4 kernel
		//
		runManager->Initialize();

		G4VisManager* visManager = new G4VisExecutive;
		visManager->Initialize();  

		// Get the pointer to the User Interface manager
		//
		G4UImanager * UImanager = G4UImanager::GetUIpointer();  

		if (argc != 2)   // batch mode  
			{
			G4String command = "/control/execute ";
			G4String fileName = argv[2];
			UImanager->ApplyCommand(command+fileName);
			}
		else           // interactive mode : define UI session
			{ 
			G4UIExecutive * ui = new G4UIExecutive(argc,argv);
			UImanager->ApplyCommand("/control/execute vis.mac");     
			ui->SessionStart();
			//delete ui;   
			}

		// Free the store: user actions, physics_list and detector_description are
		//                 owned and deleted by the run manager, so they should not
		//                 be deleted in the main() program !
		delete visManager;
		delete runManager;
		delete verbosity;
		}
	else 
		{
		cout<<"Use one of the following physics lists as the first argument:"<<endl;

		for(unsigned int i = 0; i < physListFactory->AvailablePhysLists().size(); i++) cout<<physListFactory->AvailablePhysLists().at(i)<<endl;
		}
	}
else 
	{
	cout<<"Use one of the following physics lists as the first argument:"<<endl;
	
	G4PhysListFactory*physListFactory = new G4PhysListFactory();

	for(unsigned int i = 0; i < physListFactory->AvailablePhysLists().size(); i++) cout<<physListFactory->AvailablePhysLists().at(i)<<endl;
	}

return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

