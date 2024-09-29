#include "PrimExample.h"
#include "../World.h"
#include "Random.h"

#include <array>

bool PrimExample::Step(World* w) {
  if (!initialized) {
    auto sideOver2 = w->GetSize() / 2;
    toBeVisited.push_back({-sideOver2, -sideOver2});
    initialized = true;
  }

  if (!toBeVisited.empty()) {
    Point2D const nextPoint = toBeVisited[getRandomNumber()%toBeVisited.size()];
    Node nextNode = w->GetNode(nextPoint);
    std::vector<Point2D> connectingPoints = getVisitables(w, nextPoint);

    std::cout <<toBeVisited.size() << std::endl;
    auto it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), nextPoint);
    if (it != toBeVisited.end()) {
      toBeVisited.erase(it);
    }

    std::cout <<toBeVisited.size() << std::endl;

    if (!connectingPoints.empty()) {
      w->SetNodeColor(nextPoint, Color::Green);
      Point2D selectedNeighborPoint = connectingPoints[getRandomNumber()%connectingPoints.size()];

      Point2D const direction = selectedNeighborPoint - nextPoint;

      if (direction.y == -1) {
        nextNode.SetNorth(false);
      }
      else if (direction.x == 1) {
        nextNode.SetEast(false);
      }
      else if (direction.y == 1) {
        nextNode.SetSouth(false);
      }
      else if (direction.x == -1) {
        nextNode.SetWest(false);
      }

      w->SetNode(nextPoint, nextNode);

      std::vector<Point2D> neighbors = getVisitedNeighbors(w, nextPoint);

      for (Point2D const neighbor : neighbors) {
        w->SetNodeColor(neighbor, Color::Blue);
        toBeVisited.push_back(neighbor);
      }
    } else { //This will only happen for the first point in the maze
      w->SetNodeColor(nextPoint, Color::Green);
      std::vector<Point2D> neighbors = getVisitedNeighbors(w, nextPoint);

      for (Point2D const neighbor : neighbors) {
        w->SetNodeColor(neighbor, Color::Blue);
        toBeVisited.push_back(neighbor);
      }
    }
  }

  return !toBeVisited.empty();
}
void PrimExample::Clear(World* world) {
  toBeVisited.clear();
  initialized = false;
}

int PrimExample::getRandomNumber() {
  static int randomIndex = 0;
  const std::array randomInts = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

  if (randomIndex == std::size(randomInts)) {
    randomIndex = 0;
  }
  return randomInts[randomIndex++];
}

std::vector<Point2D> PrimExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  auto it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Up());
  if (p.y - 1 >= -sideOver2 && w->GetNodeColor(p.Up()) == Color::Green && it == toBeVisited.end()) {
    visitables.emplace_back(p.x, p.y - 1);
  }

  it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Right());
  if (p.x + 1 <= sideOver2 && w->GetNodeColor(p.Right()) == Color::Green && it == toBeVisited.end()) {
    visitables.emplace_back(p.x + 1, p.y);
  }

  it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Down());
  if (p.y + 1 <= sideOver2 && w->GetNodeColor(p.Down()) == Color::Green && it == toBeVisited.end()) {
    visitables.emplace_back(p.x, p.y + 1);
  }

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

  auto it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Up());
  if (p.y - 1 >= -sideOver2 && w->GetNodeColor(p.Up()) != Color::Green && it == toBeVisited.end()) {
    neighbors.emplace_back(p.x, p.y - 1);
  }

  it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Right());
  if (p.x + 1 <= sideOver2 && w->GetNodeColor(p.Right()) != Color::Green && it == toBeVisited.end()) {
    neighbors.emplace_back(p.x + 1, p.y);
  }

  it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Down());
  if (p.y + 1 <= sideOver2 && w->GetNodeColor(p.Down()) != Color::Green && it == toBeVisited.end()) {
    neighbors.emplace_back(p.x, p.y + 1);
  }

  it = std::ranges::find(toBeVisited.begin(), toBeVisited.end(), p.Left());
  if (p.x - 1 >= -sideOver2 && w->GetNodeColor(p.Left()) != Color::Green && it == toBeVisited.end()) {
    neighbors.emplace_back(p.x - 1, p.y);
  }

  return neighbors;
}
