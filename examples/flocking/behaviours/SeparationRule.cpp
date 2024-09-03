#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"
#include <iostream>

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  //Vector2f separatingForce = Vector2f::zero();

  //    float desiredDistance = desiredMinimalDistance;
  //
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  //    if (!neighborhood.empty()) {
  //        Vector2f position = boid->transform.position;
  //        int countCloseFlockmates = 0;
  //        // todo: find and apply force only on the closest mates
  //    }

  //separatingForce = Vector2f::normalized(separatingForce);

  //return separatingForce;

  if (neighborhood.empty()) {
    return Vector2f::zero();
  }

  Vector2f seperationForce = {0,0};

  //Runs through the boids vector to search for boids within the radius
  for (Boid* b : neighborhood) {
    if (b != boid) { //Excludes the agent's self
      const double distenceToBoid = (boid->getPosition() - b->getPosition()).getMagnitude();
      if (distenceToBoid <= this->desiredMinimalDistance) {
        Vector2f otherBoidToAgentVector = boid->getPosition() - b->getPosition();

        seperationForce += otherBoidToAgentVector.normalized() / otherBoidToAgentVector.getMagnitude();
      }
    }
  }

  return seperationForce * weight;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
