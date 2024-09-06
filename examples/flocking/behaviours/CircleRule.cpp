//
// Created by tropi on 9/6/2024.
//

#include "CircleRule.h"
#include <imgui.h>
#include "MouseInfluenceRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"
#include <iostream>

Vector2f CircleRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f force = Vector2f::zero();

  //Gets vector from boid to circle center
  Vector2f toCircleTarget = circleTarget - boid->getPosition();

  //Gets a vector perpendicular (right angle vector) to the circleTarget vector
  Vector2f perpendicularToCircleTarget = {-toCircleTarget.y, toCircleTarget.x};

  //Flips vector to rotate clockwise
  if (counterClockwise) {
    perpendicularToCircleTarget *= -1;
  }

  //Checks if boid is outside the outside radius and returns force to pull it back in
  if (toCircleTarget.getMagnitude() > maxCircleDistance) {
    return toCircleTarget.normalized();
  }

  //Checks if boid is inside the inner radius and returns force to slowly push it back out
  if (toCircleTarget.getMagnitude() < minCircleDistance) {
    return perpendicularToCircleTarget.normalized();
  }

  //Calculates half vector between vector directly towards the circleTarget and perpendicular vector to keep the boid within the radius
  force += perpendicularToCircleTarget.normalized() + toCircleTarget.normalized();

  return force.normalized();
}

bool CircleRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valueHasChanged = false;

  if (ImGui::Checkbox("Circle Clockwise", &counterClockwise)) {
    valueHasChanged = true;
  }

  if (ImGui::DragFloat("Min Circle Distence", &minCircleDistance)) {
    valueHasChanged = true;
  }

  if (ImGui::DragFloat("Max Circle Distence", &maxCircleDistance)) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}