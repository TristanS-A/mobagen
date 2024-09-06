#include "MouseInfluenceRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f MouseInfluenceRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
      ImGuiIO& io = ImGui::GetIO();
      if (ImGui::IsMousePosValid() && io.MouseDown[0]) {
          Vector2f mousePos(io.MousePos.x, io.MousePos.y);
          Vector2f displacement = {2000, 2000}; //Sets displacement
          float distance = 500; //Sets mouse interaction radius distance

          Vector2f force = Vector2f::zero();

          double distanceFromBoid = (mousePos - boid->getPosition()).getMagnitude(); //Gets distance to boid
          if (distanceFromBoid <= distance) { //Checks if boid is within the distance/range
            force = mousePos - boid->getPosition(); //Gets vector from boid to mouse
            force /= distanceFromBoid; //The force is inversely proportional to distance
          }

          force *= displacement; //Multiplies displacement to make value higher

          if (isRepulsive)
              force *= -1.f;

          return force;
      }
      else {
        return Vector2f::zero();
      }
}

bool MouseInfluenceRule::drawImguiRuleExtra() {
  bool valueHasChanged = false;

  if (ImGui::RadioButton("Attractive", !isRepulsive)) {
    isRepulsive = false;
    valueHasChanged = true;
  }

  ImGui::SameLine();
  if (ImGui::RadioButton("Repulsive", isRepulsive)) {
    isRepulsive = true;
    valueHasChanged = true;
  }

  return valueHasChanged;
}