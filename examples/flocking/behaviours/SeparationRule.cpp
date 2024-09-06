#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"
#include <iostream>

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  if (neighborhood.empty()) {
    return Vector2f::zero();
  }

  Vector2f seperationForce = {0,0};

  //Runs through the boids vector to search for boids within the radius
  for (Boid* b : neighborhood) {
    if (b != boid) { //Excludes the agent's self
      const double distenceToBoid = (boid->transform.position - b->transform.position).getMagnitude(); //Gets distence to boid
      if (distenceToBoid <= desiredMaximalDistance) { //Checks if inside large radius
        //Constructs vector from boid to agent and scales it inversely proportional to the distance between them
        Vector2f otherBoidToAgentVector = boid->transform.position - b->transform.position;
        seperationForce += desiredMinimalDistance * otherBoidToAgentVector / otherBoidToAgentVector.sqrMagnitude(); // More efficient than otherBoidToAgentVector.normalized() / otherBoidToAgentVector.getMagnitude() and multiplies by smallDistence / bigDistence instead of 1 / distence
      }
    }
  }

  return seperationForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
