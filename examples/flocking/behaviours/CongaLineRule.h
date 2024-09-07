//
// Created by tropi on 9/6/2024.
//

#ifndef CongaLINERULE_H
#define CongaLINERULE_H

#include "FlockingRule.h"

class CongaLineRule : public FlockingRule {
private:
  float joinDistance = 25;
  float distanceBehind = 10;

public:
  explicit CongaLineRule(World* pWorld, float weight = 1., bool isEnabled = true)
      : FlockingRule(pWorld, Color::White, weight, isEnabled) {}

  CongaLineRule(const CongaLineRule& toCopy) : FlockingRule(toCopy) { joinDistance = toCopy.joinDistance; distanceBehind = toCopy.distanceBehind; }

  std::unique_ptr<FlockingRule> clone() override { return std::make_unique<CongaLineRule>(*this); }

  const char* getRuleName() override { return "Conga Line Force"; }

  const char* getRuleExplanation() override { return "Apply a constant force to all boids."; }

  virtual float getBaseWeightMultiplier() override { return 0.5; }

  Vector2f computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) override;

  int slotsContainsBoid(const Boid* boidToFind) const;

  bool drawImguiRuleExtra() override;
};

#endif //CongaLINERULE_H
