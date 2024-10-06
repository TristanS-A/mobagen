#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop

    Point2D const point = frontier.front(); //Gets the current point from the stack
    frontier.pop(); //Removes the current point from the stack
    frontierSet.erase(point); //Removes the current point from the fronteirSet

    int const gridHalfSize = w->getWorldSideSize() / 2;
    if (point.y == gridHalfSize || point.y == -gridHalfSize || point.x == gridHalfSize || point.x == -gridHalfSize) {
      borderExit = point;
      break;
    }

    visited[point] = true; //Sets the current point to be visited
    std::vector<Point2D> neighbors = getVisitableNeightbors(w, point, frontierSet, visited); //Gets the neighbors of the current point

    if (!neighbors.empty()) {
      for (auto const neighbor : neighbors) {
        cameFrom[neighbor] = point;
        frontier.push(neighbor);
        frontierSet.insert(neighbor);
      }
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  vector<Point2D> path;
  if (borderExit != Point2D::INFINITE) {
    Point2D current = borderExit;
    while (current != catPos) {
      path.push_back(current);
      current = cameFrom[current];
    }
  }
  return path;
}

std::vector<Point2D> Agent::getVisitableNeightbors(World* world, Point2D point, std::unordered_set<Point2D> &queue, std::unordered_map<Point2D, bool> &visited) {
  int start = point.x - static_cast<int>(point.y % 2 == 0);
  std::vector<Point2D> visitables;

  //Calculates live neighbors above
  for (int i = start; i < start + 2; i++) {
    Point2D const checkPoint = {i, point.y - 1};
    if (!queue.contains(checkPoint) && !visited.contains(checkPoint) && !world->getContent(checkPoint) && world->getCat() != checkPoint) {
      visitables.push_back(checkPoint);
    }
  }

  //Calculates live neighbors below
  for (int i = start; i < start + 2; i++) {
    Point2D const checkPoint = {i, point.y + 1};
    if (!queue.contains(checkPoint) && !visited.contains(checkPoint) && !world->getContent(checkPoint) && world->getCat() != checkPoint) {
      visitables.push_back(checkPoint);
    }
  }

  //Calculates live neighbors on sides
  start = point.x - 1;
  for (int i = start; i < start + 3; i++) {
    if (i != point.x) { //Excludes the current point
      Point2D const checkPoint = {i, point.y};
      if (!queue.contains(checkPoint) && !visited.contains(checkPoint) && !world->getContent(checkPoint) && world->getCat() != checkPoint) {
        visitables.push_back(checkPoint);
      }
    }
  }

  return visitables; //Returns total live neighbor count
}