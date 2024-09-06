#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"
#include <iostream>

Vector2f BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f force = Vector2f::zero();

  float lookAheadDistence = 1.0f; //Defines look ahead distence
  Vector2f lookAheadTarget = boid->getPosition() + boid->velocity.normalized() * lookAheadDistence; //Finds target to check collision with
  Point2D windowSize = this->world->engine->window->size(); //Gets window size
  const Vector2f windowPosition = Vector2f::zero(); //Defines window position variable (Avoids magic numbers)

  //Checks all 4 sides of the window borders
  if (lookAheadTarget.y > windowSize.y - desiredDistance) { //Bottom wall
    float distenceToReflect = abs(boid->getPosition().y - windowSize.y);
    Vector2f wallNormal = {0, -1};

    force += wallNormal * distenceToReflect; //Calculates avoidance force from wallNormal and distance to reflect
  }
  if (lookAheadTarget.y < windowPosition.y + desiredDistance) { //Top wall
    float distenceToReflect = abs(0 - boid->getPosition().y);
    Vector2f wallNormal = {0, 1};

    force += wallNormal * distenceToReflect; //Calculates avoidance force from wallNormal and distance to reflect
  }
  if (lookAheadTarget.x > windowSize.x - desiredDistance) { //Right wall
    float distenceToReflect = abs(boid->getPosition().x - windowSize.x);
    Vector2f wallNormal = {-1, 0};

    force += wallNormal * distenceToReflect; //Calculates avoidance force from wallNormal and distance to reflect
  }
  if (lookAheadTarget.x < windowPosition.x + desiredDistance) { //Right wall
    float distenceToReflect = abs(0 - boid->getPosition().x);
    Vector2f wallNormal = {1, 0};

    force += wallNormal * distenceToReflect; //Calculates avoidance force from wallNormal and distance to reflect
  }

  return force;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  auto size = this->world->engine->window->size();
  auto widthWindows = size.x;
  auto heightWindows = size.y;
  bool valueHasChanged = false;

  // We cap the max separation as the third of the min of the width.height
  auto minHeightWidth = std::min(widthWindows, heightWindows);

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0.0f, (int)(minHeightWidth / 3), "%i")) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
  FlockingRule::draw(boid, renderer);
  auto size = this->world->engine->window->size();
  auto dist = (float)desiredDistance;

  // Draw a rectangle on the map
  Polygon::DrawLine(renderer, Vector2f(dist, dist), Vector2f(size.x - dist, dist), Color::Gray);                    // TOP
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, dist), Vector2f(size.x - dist, size.y - dist), Color::Gray);  // RIGHT
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, size.y - dist), Vector2f(dist, size.y - dist), Color::Gray);  // Bottom
  Polygon::DrawLine(renderer, Vector2f(dist, size.y - dist), Vector2f(dist, dist), Color::Gray);                    // LEFT
}