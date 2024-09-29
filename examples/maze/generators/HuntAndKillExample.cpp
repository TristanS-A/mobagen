#include "HuntAndKillExample.h"
#include "../World.h"
#include "Random.h"

#include <array>
#include <climits>
bool HuntAndKillExample::Step(World* w) {
  if (stack.empty() && visitedIsEmpty()) { //Checks if this is the first step in the maze
    stack.push_back(randomStartPoint(w)); //Adds random point as starting point
  }

  if (!stack.empty()) { //While the stack is not empty, performs random DFS until hitting a dead end where it will pick up from another random connecting point in the maze
    Point2D const point = stack.back(); //Gets the next point
    Node node = w->GetNode(point); //Gets the nod of that point
    std::vector<Point2D> neighbors = getVisitables(w, point); //Gets the neighbors of that point to visit

    w->SetNodeColor(point, Color::Green); //Marks the current point as visited with color
    visited[point.y][point.x] = true; //Marks the current point as visited in the visited map

    if (!neighbors.empty()) { //While there are neighbors to visit
      Point2D const nextPoint = neighbors[getRandomNumber()%neighbors.size()]; //Selects a random neighbor to visits
      stack.push_back(nextPoint); //Adds that neighbor to the stack

      Point2D const direction = nextPoint - point; //Gets the direction to that neighbor to break walls

      if (direction.y == -1) { //Checks if going upwards in the grid
        node.SetNorth(false);
      }
      else if (direction.x == 1) { //Checks if going right in the grid
        node.SetEast(false);
      }
      else if (direction.y == 1) { //Checks if going down in the grid
        node.SetSouth(false);
      }
      else if (direction.x == -1) { //Checks if going left in the grid
        node.SetWest(false);
      }

      w->SetNode(point, node); //Updates the current node with new wall information
    } else { //This is if the maze hits a dead end
      Point2D* nextPoint = getNextVisitableNeighborConnector(w, point); //Gets a point in the maze that connects to a visitable neighbor that has not been visited
      if (nextPoint != nullptr) { //Checks if that next point exists
        stack.push_back(*nextPoint); //Adds the point to the stack to be visited
      }
      else { //This means that there are no more points to visit so it clears the stack
        stack.clear();
      }
    }
  }

  return !stack.empty(); //Returns true when there are no more points to visit
}
void HuntAndKillExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

int HuntAndKillExample::getRandomNumber() { //Function to get a "random" number
  static int randomIndex = 0;
  const std::array randomInts = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

  if (randomIndex == std::size(randomInts)) { //Loops index if reaches the end of the random number array
    randomIndex = 0;
  }
  return randomInts[randomIndex++]; //Returns the random number at the current index and increments the index
}

bool HuntAndKillExample::visitedIsEmpty() { //Poorly optimized way of checking if there are no visited points in the grid
  int count = 0;
  for (auto it : visited)  {
    for (auto it2 : it.second) {
      count += static_cast<int>(it2.second);
    }
  }

  return count == 0;
}

Point2D HuntAndKillExample::randomStartPoint(World* world) {
  // Todo: improve this if you want
  auto sideOver2 = world->GetSize() / 2;

  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> HuntAndKillExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  //Checks top visitable
  if (p.y - 1 >= -sideOver2 && w->GetNodeColor(p.Up()) != Color::Green) {
    visitables.emplace_back(p.x, p.y - 1);
  }

  //Checks right visitable
  if (p.x + 1 <= sideOver2 && w->GetNodeColor(p.Right()) != Color::Green) {
    visitables.emplace_back(p.x + 1, p.y);
  }

  //Checks bottom visitable
  if (p.y + 1 <= sideOver2 && w->GetNodeColor(p.Down()) != Color::Green) {
    visitables.emplace_back(p.x, p.y + 1);
  }

  //Checks left visitable
  if (p.x - 1 >= -sideOver2 && w->GetNodeColor(p.Left()) != Color::Green) {
    visitables.emplace_back(p.x - 1, p.y);
  }

  return visitables;

}

//Function to get the next point in the stack that has visitable neighbors
Point2D* HuntAndKillExample::getNextVisitableNeighborConnector(World* w, const Point2D& p) {
  if (!stack.empty()) {
    for (Point2D& point : stack) {
      if (!getVisitables(w, point).empty()) {
        return &point; //Returns the first point in the stack that has visitable neighbors
      }
    }
  }

  return nullptr;
}
