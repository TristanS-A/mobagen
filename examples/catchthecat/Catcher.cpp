#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  std::vector<Point2D> path = world->getUsingBFS() ? generateAStarPath(world) : generateBFSPath(world); //Selects current path algorithm
  if (!path.empty()) { //If path is not empty, return the first element in the path
    return path[0];
  }

  //If path is empty then randomly choose a neighbor to block
  std::vector<Point2D> neighbors = getVisitableNeightbors(world);
  auto rand = Random::Range(0, neighbors.size() - 1);
  return neighbors[rand];
}

std::vector<Point2D> Catcher::getVisitableNeightbors(World* world) {
  auto cat = world->getCat(); //Gets cat's pos
  int start = cat.x - static_cast<int>(cat.y % 2 == 0); //Calculates x offset start based on the y level
  std::vector<Point2D> visitables;

  //Finds cat's neighbors above
  for (int i = start; i < start + 2; i++) {
    Point2D const checkPoint = {i, cat.y - 1};
    if (!world->getContent(checkPoint)) {
      visitables.push_back(checkPoint);
    }
  }

  //Finds cat's neighbors below
  for (int i = start; i < start + 2; i++) {
    Point2D const checkPoint = {i, cat.y + 1};
    if (!world->getContent(checkPoint)) {
      visitables.push_back(checkPoint);
    }
  }

  //Finds cat's neighbors on the same y level
  start = cat.x - 1;
  for (int i = start; i < start + 3; i++) {
    if (i != cat.x) { //Excludes the current point
      Point2D const checkPoint = {i, cat.y};
      if (!world->getContent(checkPoint)) {
        visitables.push_back(checkPoint);
      }
    }
  }

  return visitables; //Returns total live neighbor count
}