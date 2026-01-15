#include "SimpleDetEventAction.hh"
#include "SimpleDetHit.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4ParticleGun.hh"

//----------------------------------------------------------------------

SimpleDetEventAction::SimpleDetEventAction()
{
//evtMessenger = new SimpleDetEventActionMessenger(this);
evtSaveRoot = false;
}

//----------------------------------------------------------------------

SimpleDetEventAction::~SimpleDetEventAction()
{
//delete evtMessenger;	
}

//----------------------------------------------------------------------

SimpleDetRunAction * SimpleDetEventAction::GetCurrentRun()
{
return dynamic_cast<SimpleDetRunAction*> (const_cast<G4UserRunAction*> (G4RunManager::GetRunManager()->GetUserRunAction()));
}

//----------------------------------------------------------------------

SimpleDetPrimaryGeneratorAction * SimpleDetEventAction::GetCurrentPrimaryGeneratorAction()
{
return dynamic_cast<SimpleDetPrimaryGeneratorAction*> (const_cast<G4VUserPrimaryGeneratorAction*> (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction()));
}

//----------------------------------------------------------------------

void SimpleDetEventAction::BeginOfEventAction(const G4Event*)
{
}

//----------------------------------------------------------------------

void SimpleDetEventAction::EndOfEventAction(const G4Event* evt)
{
/*G4int event_id = evt->GetEventID();

// get number of stored trajectories
//
G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
G4int n_trajectories = 0;
if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

// periodic printing
//
if (event_id < 100 || event_id%100 == 0) 
	{
	G4cout << ">>> Event " << evt->GetEventID() << G4endl;
	G4cout << "    " << n_trajectories 
	<< " trajectories stored in this event." << G4endl;
	}*/

if(evtSaveRoot) SaveRoot(evt);
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------

void SimpleDetEventAction::SetRoot(TTree * RootTree)
{
evtRootTree = RootTree;
evtSaveRoot = true;	
}

//----------------------------------------------------------------------

void  SimpleDetEventAction::CloseRoot()
{
evtSaveRoot = false;
}

//----------------------------------------------------------------------

void SimpleDetEventAction::SaveRoot(const G4Event* evt)
{
G4SDManager* SDman = G4SDManager::GetSDMpointer();
G4int ID = SDman->GetCollectionID("Collection");

G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
SimpleDetHitsCollection* Collection = 0;

//Save Event
vector<int> checkTrackID;
if(HCE) 
	{
	GetCurrentRun()->SetPrimaryParticlePdg(GetCurrentPrimaryGeneratorAction()->GetParticleGun()->GetParticleDefinition()->GetPDGEncoding());
	GetCurrentRun()->SetPrimaryParticleEnergy(GetCurrentPrimaryGeneratorAction()->GetParticleGun()->GetParticleEnergy());
	GetCurrentRun()->SetPrimaryParticlePosition(GetCurrentPrimaryGeneratorAction()->GetParticleGun()->GetParticlePosition());
	GetCurrentRun()->SetPrimaryParticleTime(GetCurrentPrimaryGeneratorAction()->GetParticleGun()->GetParticleTime());
	GetCurrentRun()->SetPrimaryParticleMomentumDirection(GetCurrentPrimaryGeneratorAction()->GetParticleGun()->GetParticleMomentumDirection());

	Collection = (SimpleDetHitsCollection*)HCE->GetHC(ID);

	for(int i = 0; i < Collection->entries(); i++)
		{
		SimpleDetHit* Hit = (*Collection)[i];
		
		GetCurrentRun()->SetParentID(Hit->GetParentID());
		GetCurrentRun()->SetTrackID(Hit->GetTrackID());
		GetCurrentRun()->SetVolumeID(Hit->GetVolumeId());
		GetCurrentRun()->SetPdg(Hit->GetPdg());
		GetCurrentRun()->SetEdep(Hit->GetEdep());
		GetCurrentRun()->SetPos(Hit->GetPos());
		GetCurrentRun()->SetMomentumDirection(Hit->GetMomentumDirection());
		GetCurrentRun()->SetKineticEnergy(Hit->GetKineticEnergy());
		GetCurrentRun()->SetGlobalTime(Hit->GetGlobalTime());
		
		//save vertex information
		bool VertexAlreadySaved = false;
		for(unsigned int j = 0; j < checkTrackID.size(); j++)
			{
			if(checkTrackID[j] == Hit->GetTrackID())
				{
				VertexAlreadySaved = true;
				break;
				}
			}
		if(!VertexAlreadySaved)
			{
			GetCurrentRun()->SetVertexTrackID(Hit->GetTrackID());
			GetCurrentRun()->SetVertexMomentumDirection(Hit->GetVertexMomentumDirection());
			GetCurrentRun()->SetVertexPosition(Hit->GetVertexPosition());
			GetCurrentRun()->SetVertexKineticEnergy(Hit->GetVertexKineticEnergy());
		
			checkTrackID.push_back(Hit->GetTrackID());
			}
		}
	}

evtRootTree->Fill();
GetCurrentRun()->Clear();
}
