//
// Created by tropi on 9/6/2024.
//

#include "CongaLineRule.h"
#include "WindRule.h"
#include <imgui.h>
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"
#include <iostream>

Vector2f CongaLineRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f force = Vector2f::zero();

  // Initial assignment of leader
  if (world->boidSlots.empty()) {
    world->boidSlots.push_back(boid);
    return force;
  }

  //Handles adding boids to slots list
  int const locationInSlots = slotsContainsBoid(boid);
  if (locationInSlots != -1) {
    for (Boid* b : world->boids) {
      const double distenceToBoid = (b->transform.position - boid->transform.position).getMagnitude();  // Gets distence to boid
      if (distenceToBoid <= joinDistance) {
        if (slotsContainsBoid(b) == -1) {
          world->boidSlots.push_back(b);
        }
      }
    }
  }

  //Handles chancing person ahead of self
  if (locationInSlots != -1) {
    if (locationInSlots != 0) {
      Boid* boidToChase = world->boidSlots[locationInSlots - 1];
      Vector2f targetPosition = boidToChase->getPosition() - (boidToChase->velocity.normalized() * distanceBehind);

      force += (targetPosition - boid->getPosition()).normalized();
    }
  }

  return force;
}
int CongaLineRule::slotsContainsBoid(const Boid* boidToFind) const {
  for (int i = 0; i < world->boidSlots.size(); i++) {
    if (world->boidSlots[i] == boidToFind) {
      return i;
    }
  }

  return -1;
}

bool CongaLineRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valueHasChanged = false;

  if (ImGui::SliderFloat("Join Distance", &joinDistance, 0, 10000)) {
    valueHasChanged = true;
  }

  if (ImGui::InputFloat("Follow Distance", &distanceBehind)) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}

