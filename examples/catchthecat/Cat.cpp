#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  std::vector<Point2D> path = world->getUsingBFS() ? generateBFSPath(world) : generateAStarPath(world); //Selects current path algorithm
  if (!path.empty()) { //If path is not empty, return the last element in the path
    return path[path.size() - 1];
  }

  //If path is empty then randomly choose a neighbor to go to
  auto rand = Random::Range(0, 5);
  int index = rand;
  auto pos = world->getCat();

  //Adds all movement options to a vector
  std::vector<Point2D> directions = {};
  directions.push_back(World::NE(pos));
  directions.push_back(World::NW(pos));
  directions.push_back(World::E(pos));
  directions.push_back(World::W(pos));
  directions.push_back(World::SW(pos));
  directions.push_back(World::SE(pos));

  //If the random direction is blocked, then iterate through the vector until it either finds an unblocked neighbor to move to or loops back to the initial direction
  if (world->getContent(directions[rand])) {
    index++;
    while (rand != index) {
      if (index >= directions.size()) {
        index = 0;
      }

      if (!world->getContent(directions[index])) {
        return directions[index]; //Returns next available neighbor to move to
      }

      index++;
    }

    return Point2D::INFINITE; //All neighbors are blocked
  }


  return directions[rand];
}
