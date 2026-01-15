#ifndef SimpleDetActionInitialization_h
#define SimpleDetActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "SimpleDetDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SimpleDetActionInitialization : public G4VUserActionInitialization
{
public:
SimpleDetActionInitialization();
~SimpleDetActionInitialization();

void Build() const;
void BuildForMaster() const;

void SetDetector(SimpleDetDetectorConstruction* detector);
void SetPhysicsListName(G4String PhysicsListName);

private:
G4String aiPhysicsListName;
SimpleDetDetectorConstruction * aiDetector;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
