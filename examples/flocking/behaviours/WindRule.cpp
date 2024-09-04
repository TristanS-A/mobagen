#include "WindRule.h"
#include <imgui.h>
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"
#include <iostream>

Vector2f WindRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f force = Vector2f(cos(windAngle), sin(windAngle)); //Calculates wind force vector

  return force;
}

bool WindRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valueHasChanged = false;

  if (ImGui::SliderAngle("Wind Direction", &windAngle, 0)) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}