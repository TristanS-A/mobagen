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
  struct AStarNode {
    AStarNode(Point2D p) : point(p){};
    AStarNode() = default;
    Point2D point;
    int weight = 0;
    int heuristic = 0;
    bool operator < (const AStarNode& rhs) const {
      return (weight + heuristic) > (rhs.weight + rhs.heuristic);
    }

    int calculateManhattanHeuristic(const Point2D& other) const {
      return abs(point.x - other.x) + abs(point.y - other.y); //Manhattan
    }

    int calculateClosestSideHeuristic(const Point2D& other, int halfSideSize) const {
      //The other way of calculating heuristic based on finding the closest side
      if (other.x - other.y > 0 && other.x + other.y > 0) { //Tests if right side is closest
        return halfSideSize - other.x; //returns distance from right side
      }
      else if (other.x - other.y < 0 && other.x + other.y > 0) { //Tests if top side is closest
        return halfSideSize - other.y; //returns distance from top side
      }
      else if (other.x - other.y < 0 && other.x + other.y < 0) { //Tests if left side is closest
        return other.x - halfSideSize; //returns distance from left side
      }
      else {
        return other.y - halfSideSize; //Otherwise returns distance from bottom side
      }
    }
  };

  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generateBFSPath(World* w);
  std::vector<Point2D> generateAStarPath(World* w);
  std::vector<Point2D> getVisitableNeightbors(World* world, Point2D point, std::unordered_set<Point2D> &queue, std::unordered_map<Point2D, bool> &visited);
  Point2D probobalExit(World* w, Point2D p);
};

#endif  // AGENT_H
