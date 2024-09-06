//
// Created by tropi on 9/6/2024.
//

#ifndef CIRCLERULE_H
#define CIRCLERULE_H

#include "FlockingRule.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

class CircleRule : public FlockingRule {
private:
  Vector2f circleTarget = {1280 / 2, 720 / 2};
  float minCircleDistance = 100;
  float maxCircleDistance = 200;
  float circlePullForce = 1000;
  bool counterClockwise = true;

public:
  explicit CircleRule(World* pWorld, float weight = 100., bool isEnabled = true, bool counterClockwise = true)
      : FlockingRule(pWorld, Color::White, weight, isEnabled), counterClockwise(counterClockwise) {}

  CircleRule(const CircleRule& toCopy) : FlockingRule(toCopy) { circleTarget = toCopy.circleTarget; counterClockwise = toCopy.counterClockwise; minCircleDistance = toCopy.minCircleDistance; maxCircleDistance = toCopy.maxCircleDistance; }

  std::unique_ptr<FlockingRule> clone() override { return std::make_unique<CircleRule>(*this); }

  const char* getRuleName() override { return "Circle Force"; }

  const char* getRuleExplanation() override { return "Apply a constant force to all boids."; }

  virtual float getBaseWeightMultiplier() override { return 0.5; }

  Vector2f computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) override;

  bool drawImguiRuleExtra() override;
};

#endif //CIRCLERULE_H
