#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"
#include <iostream>

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  if (neighborhood.empty()) {
    return Vector2f::zero();
  }

  // Try to match the heading of neighbors = Average velocity
  Vector2f avarageVelocity = {0,0};
  float numberOfBoidsInRadius = 0;

  //Runs through the boids vector to search for boids within the radius (includes itself)
  for (Boid* b : neighborhood) {
    const double distenceToBoid = (b->transform.position - boid->transform.position).getMagnitude(); //Gets distence to boid
    if (distenceToBoid <= boid->getDetectionRadius()) { //Checks if it is inside radius
      //Adds velocity and increments boids within the radius found
      avarageVelocity += b->getVelocity();
      numberOfBoidsInRadius++;
    }
  }

  //Calculates accurate average velocity
  avarageVelocity /= numberOfBoidsInRadius;

  return avarageVelocity;
}