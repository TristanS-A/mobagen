#include "PrimExample.h"
#include "../World.h"
#include "Random.h"

#include <array>

bool PrimExample::Step(World* w) {
  if (!initialized) { //Checks if this is the first step in the maze
    auto sideOver2 = w->GetSize() / 2;
    toBeVisited.push_back({-sideOver2, -sideOver2}); //Adds top left point
    initialized = true;
  }

  if (!toBeVisited.empty()) { //While there are points to be visited, it gets the next point to visit, visits it, and then adds the next random neighbor to be visited
    Point2D const nextPoint = toBeVisited[getRandomNumber()%toBeVisited.size()]; //Gets random point that is marked to be visited
    Node nextNode = w->GetNode(nextPoint); //Gets the node of that point
    std::vector<Point2D> connectingPoints = getVisitables(w, nextPoint); //Gets that point's connectable point back into the maze

    //Removes it from the toBeVisited vector
    auto it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), nextPoint);
    if (it != toBeVisited.end()) {
      toBeVisited.erase(it);
    }

    if (!connectingPoints.empty()) { //If there are connecting points (which there always should be) it visits the current point, breaks its walls into the maze, and adds another random neighbor to be visited
      w->SetNodeColor(nextPoint, Color::Green); //Sets the points color to green
      Point2D selectedNeighborPoint = connectingPoints[getRandomNumber()%connectingPoints.size()]; //Selects a random point in the maze to connect the current point to

      Point2D const direction = selectedNeighborPoint - nextPoint; //Gets the direction from the current point to the maze point to break walls

      if (direction.y == -1) { //Checks if going upwards in the grid
        nextNode.SetNorth(false);
      }
      else if (direction.x == 1) { //Checks if going right in the grid
        nextNode.SetEast(false);
      }
      else if (direction.y == 1) { //Checks if going down in the grid
        nextNode.SetSouth(false);
      }
      else if (direction.x == -1) { //Checks if going left in the grid
        nextNode.SetWest(false);
      }

      w->SetNode(nextPoint, nextNode); //Updates the current node

      std::vector<Point2D> neighbors = getVisitedNeighbors(w, nextPoint); //Gets the neighbors of the current node

      for (Point2D const neighbor : neighbors) { //Marks the neighbors of the current node to be visited and changes their color to reflect this
        w->SetNodeColor(neighbor, Color::Blue);
        toBeVisited.push_back(neighbor);
      }
    } else { //This will only happen for the first point in the maze because there is no maze to connect it to yet
      w->SetNodeColor(nextPoint, Color::Green); //Changes it's color to mark it as visited
      std::vector<Point2D> neighbors = getVisitedNeighbors(w, nextPoint); //Gets it's neighbors

      for (Point2D const neighbor : neighbors) { //Marks the neighbors of the current node to be visited and changes their color to reflect this
        w->SetNodeColor(neighbor, Color::Blue);
        toBeVisited.push_back(neighbor);
      }
    }
  }

  return !toBeVisited.empty(); //Returns true until there are no more points to be visited
}
void PrimExample::Clear(World* world) {
  toBeVisited.clear();
  initialized = false;
}

int PrimExample::getRandomNumber() { //Function to get a "random" number from the random number array
  static int randomIndex = 0;
  const std::array randomInts = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

  if (randomIndex == std::size(randomInts)) { //Loop index if reaches the end of the array
    randomIndex = 0;
  }
  return randomInts[randomIndex++]; //Returns the random number at the current index and increments index
}

std::vector<Point2D> PrimExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  //Checks top visitable
  auto it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Up());
  if (p.y - 1 >= -sideOver2 && w->GetNodeColor(p.Up()) == Color::Green && it == toBeVisited.end()) {
    visitables.emplace_back(p.x, p.y - 1);
  }

  //Checks right visitable
  it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Right());
  if (p.x + 1 <= sideOver2 && w->GetNodeColor(p.Right()) == Color::Green && it == toBeVisited.end()) {
    visitables.emplace_back(p.x + 1, p.y);
  }

  //Checks bottom visitable
  it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Down());
  if (p.y + 1 <= sideOver2 && w->GetNodeColor(p.Down()) == Color::Green && it == toBeVisited.end()) {
    visitables.emplace_back(p.x, p.y + 1);
  }

  //Checks left visitable
  it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Left());
  if (p.x - 1 >= -sideOver2 && w->GetNodeColor(p.Left()) == Color::Green && it == toBeVisited.end()) {
    visitables.emplace_back(p.x - 1, p.y);
  }

  return visitables;
}

std::vector<Point2D> PrimExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> deltas = {Point2D::UP, Point2D::DOWN, Point2D::LEFT, Point2D::RIGHT};
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> neighbors;

  //Checks top neighbor
  auto it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Up());
  if (p.y - 1 >= -sideOver2 && w->GetNodeColor(p.Up()) != Color::Green && it == toBeVisited.end()) {
    neighbors.emplace_back(p.x, p.y - 1);
  }

  //Checks right neighbor
  it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Right());
  if (p.x + 1 <= sideOver2 && w->GetNodeColor(p.Right()) != Color::Green && it == toBeVisited.end()) {
    neighbors.emplace_back(p.x + 1, p.y);
  }

  //Checks bottom neighbor
  it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Down());
  if (p.y + 1 <= sideOver2 && w->GetNodeColor(p.Down()) != Color::Green && it == toBeVisited.end()) {
    neighbors.emplace_back(p.x, p.y + 1);
  }

  //Checks left neighbor
  it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Left());
  if (p.x - 1 >= -sideOver2 && w->GetNodeColor(p.Left()) != Color::Green && it == toBeVisited.end()) {
    neighbors.emplace_back(p.x - 1, p.y);
  }

  return neighbors;
}
