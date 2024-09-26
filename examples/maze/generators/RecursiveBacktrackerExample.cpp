#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  if (stack.empty() && visited.empty()) {
    stack.push_back(randomStartPoint(w));
  }
  else if (!stack.empty()) {
    Point2D point = stack.back();
    Node node = w->GetNode(point);
    std::vector<Point2D> neighbors = getVisitables(w, point);

    if (neighbors.size() > 0) {

      //Should pick only one neighbor to add to the stack
      //Change color of visited
      //Break walls

      /*for (Point2D p : neighbors) {
        if (visited.find(p) == visited.end()) {
          stack.push_back(p);
        }
      }*/

    }
    else {
      stack.pop_back();
    }
  }

  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  if (p.x - 1 >= -sideOver2) {
    visitables.emplace_back(p.x - 1, p.y);
  }
  else if (p.x + 1 <= sideOver2) {
    visitables.emplace_back(p.x + 1, p.y);
  }

  if (p.y - 1 >= -sideOver2) {
    visitables.emplace_back(p.x, p.y - 1);
  }
  else if (p.y + 1 <= sideOver2) {
    visitables.emplace_back(p.x, p.y + 1);
  }

  return visitables;
}
