#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
  std::vector<Point2D> getVisitableNeightbors(World* world, Point2D point, std::unordered_set<Point2D> &queue, std::unordered_map<Point2D, bool> &visited);
};

#endif  // AGENT_H
