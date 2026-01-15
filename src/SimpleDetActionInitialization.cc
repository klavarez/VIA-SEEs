#include "SimpleDetActionInitialization.hh"
#include "SimpleDetRunAction.hh"
#include "SimpleDetPrimaryGeneratorAction.hh"
#include "SimpleDetEventAction.hh"
#include "SimpleDetSteppingAction.hh"
#include "SimpleDetDetectorConstruction.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4UserRunAction.hh"

//----------------------------------------------------------------------

SimpleDetActionInitialization::SimpleDetActionInitialization()
{
;
}

//----------------------------------------------------------------------

SimpleDetActionInitialization::~SimpleDetActionInitialization()
{
;	
}

//----------------------------------------------------------------------

void SimpleDetActionInitialization::SetDetector(SimpleDetDetectorConstruction* detector)
{
aiDetector = detector;
}

//----------------------------------------------------------------------


void SimpleDetActionInitialization::SetPhysicsListName(G4String PhysicsListName)
{
aiPhysicsListName = PhysicsListName;
}

//----------------------------------------------------------------------

void SimpleDetActionInitialization::Build() const
{
G4VUserPrimaryGeneratorAction* gen_action = new SimpleDetPrimaryGeneratorAction(aiDetector);
SetUserAction(gen_action);

SimpleDetRunAction * temp_run_action = new SimpleDetRunAction;
temp_run_action->SetPhysicsListName(aiPhysicsListName);
G4UserRunAction* run_action = temp_run_action;
SetUserAction(run_action);

SetUserAction(new SimpleDetEventAction);
SetUserAction(new SimpleDetSteppingAction);
}

//----------------------------------------------------------------------

void SimpleDetActionInitialization::BuildForMaster() const
{
SimpleDetRunAction * temp_run_action = new SimpleDetRunAction;
temp_run_action->SetPhysicsListName(aiPhysicsListName);
G4UserRunAction* run_action = temp_run_action;
SetUserAction(run_action);
}
