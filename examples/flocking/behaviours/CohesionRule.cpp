#include "CohesionRule.h"
#include "../gameobjects/Boid.h"
#include <iostream>

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  if (!neighborhood.empty()) {
    Vector2f centerOfMass = {0,0};
    int numberOfBoidsInRadius = 0;

    //Runs through the boids vector to search for boids within the radius
    for (Boid* b : neighborhood) {
      const double distenceToBoid = (b->transform.position - boid->transform.position).getMagnitude(); //Gets distence to boid
      if (distenceToBoid <= boid->getDetectionRadius() && b != boid) { //Checks if distance is under radius and excludes self

        //Adds position of mass and increments boids within the radius found
        centerOfMass += b->transform.position;
        numberOfBoidsInRadius++;
      }
    }

    //Calculates accurate center of mass
    centerOfMass /= numberOfBoidsInRadius;

    //Finds vector to center of mass from agent
    Vector2f agentDirection = centerOfMass - boid->transform.position;

    //Make sure that center of mass is in radius
    if (agentDirection.getMagnitude() <= boid->getDetectionRadius()) {
      return (agentDirection / boid->getDetectionRadius());
    }
  }

  //Else returns no force
  return {0, 0};
}