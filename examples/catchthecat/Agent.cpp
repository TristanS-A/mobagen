#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

std::vector<Point2D> Agent::generateBFSPath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat(); //Gets cat
  frontier.push(catPos); //Pushes cat/start onto the frontier
  frontierSet.insert(catPos); //Adds cat to set to keep track of points on the frontier
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    Point2D const point = frontier.front(); //Gets the current point from the queue
    frontier.pop(); //Removes the current point from the queue
    frontierSet.erase(point); //Removes the current point from the fronteirSet

    int const gridHalfSize = w->getWorldSideSize() / 2; //Gets half grid size
    if (point.y == gridHalfSize || point.y == -gridHalfSize || point.x == gridHalfSize || point.x == -gridHalfSize) { //Tests if it is a goal point
      borderExit = point;
      break;
    }

    visited[point] = true; //Sets the current point as visited
    std::vector<Point2D> neighbors = getVisitableNeightbors(w, point, frontierSet, visited); //Gets the neighbors of the current point

    //While neighbors exist, update the cameFrom map and add the neighbor to the frontier and frontierSet
    if (!neighbors.empty()) {
      for (auto const neighbor : neighbors) {
        cameFrom[neighbor] = point;
        frontier.push(neighbor);
        frontierSet.insert(neighbor);
      }
    }
  }

  vector<Point2D> path; //Path from goal to start
  if (borderExit != Point2D::INFINITE) { //Adds to the path if an exit was found
    Point2D current = borderExit;
    while (current != catPos) { //Builds path from cameFrom map starting at the goal
      path.push_back(current);
      current = cameFrom[current];
    }
  }

  return path;
}

std::vector<Point2D> Agent::generateAStarPath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<AStarNode> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element don't exist [] will give you wrong results
  Point2D goal = {0, 0}; //Sets up goal for manhattan heuristic

  // bootstrap state
  AStarNode start = AStarNode(w->getCat()); //Gets the cat as an AStart node

  //Tests if using the manhattan heuristic
  if (w->getUsingManhattan()) {
    goal = probobalExit(w, start.point); //For using Manhattan heuristic
    start.heuristic = start.calculateManhattanHeuristic(goal); //Calculates start node heuristic
  } else { //Otherwise use other heuristic
    start.heuristic = start.calculateClosestSideHeuristic(start.point, w->getWorldSideSize() / 2);
  }

  //Adds the start node to the frontier and adds the point to the frontier set to keep track of it
  frontier.push(start);
  frontierSet.insert(start.point);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we don't find a border, we have to return random points

  while (!frontier.empty()) {
    AStarNode const currNode = frontier.top(); //Gets the current node from the priority queue
    frontier.pop(); //Removes the current node from the priority queue
    frontierSet.erase(currNode.point); //Removes the current node point from the fronteirSet

    int const gridHalfSize = w->getWorldSideSize() / 2; //Gets the half grid size
    if (currNode.point.y == gridHalfSize || currNode.point.y == -gridHalfSize || currNode.point.x == gridHalfSize || currNode.point.x == -gridHalfSize) { //Checks if the point is a goal point
      borderExit = currNode.point;
      break;
    }

    visited[currNode.point] = true; //Sets the current point as visited
    std::vector<Point2D> neighbors = getVisitableNeightbors(w, currNode.point, frontierSet, visited); //Gets the neighbors of the current point

    //While the neighbors exist, update the cameFrom map with them and add them to the priority queue
    if (!neighbors.empty()) {
      for (Point2D const neighbor : neighbors) {
        cameFrom[neighbor] = currNode.point;
        AStarNode newNeighborNode = AStarNode(neighbor); //Converts neighbor point into AStar node
        newNeighborNode.weight = currNode.weight + 1; //Updates neighbor weights

        //Tests if using the manhattan heuristic
        if (w->getUsingManhattan()) {
          start.heuristic = start.calculateManhattanHeuristic(goal); //Calculates start node heuristic
        } else { //Otherwise use other heuristic
          start.heuristic = start.calculateClosestSideHeuristic(start.point, w->getWorldSideSize() / 2);
        }

        frontier.push(newNeighborNode);
        frontierSet.insert(neighbor);
      }
    }
  }

  vector<Point2D> path; //Path from the goal to the start
  if (borderExit != Point2D::INFINITE) { //Builds path only if a goal was found
    Point2D current = borderExit;
    while (current != start.point) { //Runs backwards through cameFrom map to build path from the goal to the start
      path.push_back(current);
      current = cameFrom[current];
    }
  }

  return path;
}

Point2D Agent::probobalExit(World* w, Point2D p) { //Calculates the probable exit for the manhattan A* heuristic
  int const gridHalfSize = w->getWorldSideSize() / 2;
  int yDistToWall = gridHalfSize - abs(p.y);
  int xDistToWall = gridHalfSize - abs(p.x);

  if (yDistToWall > xDistToWall && p.x > 0) { //Checks if closer to right wall
    return {gridHalfSize, p.y};
  }
  else if (yDistToWall < xDistToWall && p.y > 0) { //Checks if closer to bottom wall
    return {p.x, gridHalfSize};
  }
  else if (xDistToWall < yDistToWall && p.x < 0) { //Checks if closer to left wall
    return {-gridHalfSize, p.y};
  }
  else if (xDistToWall > yDistToWall && p.y < 0) { //Checks if closer to top wall
    return {p.x, -gridHalfSize};
  }


  return {p.x, p.y}; //Returns the points own position to find the closest exit point
}

std::vector<Point2D> Agent::getVisitableNeightbors(World* world, Point2D point, std::unordered_set<Point2D> &queue, std::unordered_map<Point2D, bool> &visited) {
  int start = point.x - static_cast<int>(point.y % 2 == 0); //Calculates x offset start based on the y level
  std::vector<Point2D> visitables;

  //Finds neighbors above
  for (int i = start; i < start + 2; i++) {
    Point2D const checkPoint = {i, point.y - 1};
    if (!queue.contains(checkPoint) && !visited.contains(checkPoint) && !world->getContent(checkPoint) && world->getCat() != checkPoint) {
      visitables.push_back(checkPoint);
    }
  }

  //Finds neighbors below
  for (int i = start; i < start + 2; i++) {
    Point2D const checkPoint = {i, point.y + 1};
    if (!queue.contains(checkPoint) && !visited.contains(checkPoint) && !world->getContent(checkPoint) && world->getCat() != checkPoint) {
      visitables.push_back(checkPoint);
    }
  }

  //Finds neighbors on sides
  start = point.x - 1;
  for (int i = start; i < start + 3; i++) {
    if (i != point.x) { //Excludes the current point
      Point2D const checkPoint = {i, point.y};
      if (!queue.contains(checkPoint) && !visited.contains(checkPoint) && !world->getContent(checkPoint) && world->getCat() != checkPoint) {
        visitables.push_back(checkPoint);
      }
    }
  }

  return visitables; //Returns neighbors found
}