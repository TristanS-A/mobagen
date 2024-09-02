#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  if (neighborhood.empty()) {
    return Vector2f::zero();
  }

  // Try to match the heading of neighbors = Average velocity
  Vector2f avarageVelocity = {0,0};
  int numberOfBoidsInRadius = 0;

  //Runs through the boids vector to search for boids within the radius (includes itself)
  for (Boid* b : neighborhood) {
    const double distenceToBoid = (b->getPosition() - boid->getPosition()).getMagnitude();
    if (distenceToBoid <= boid->getDetectionRadius()) {
      //Adds position of mass and increments boids within the radius found
      avarageVelocity += b->getVelocity();
      numberOfBoidsInRadius += 1;
    }
  }

  //cout << "alignment" << endl;
  //Calculates accurate average velocity
  avarageVelocity /= numberOfBoidsInRadius;
  avarageVelocity *= getBaseWeightMultiplier();

  return avarageVelocity;
}