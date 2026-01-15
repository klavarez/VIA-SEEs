#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	// Number of particles per event generated
	fParticleGun = new G4ParticleGun();

	// Setting up particle type for event
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "e-";
	G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

	// Set starting position and direction of particle beam
	G4ThreeVector pos(0., 0., 0.);
	G4ThreeVector mom(0., 0., 1.);

	// Add the setup to the particle gun
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(500.*keV);
	fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	fParticleGun->GeneratePrimaryVertex(anEvent);
}
