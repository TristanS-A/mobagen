#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  std::vector<Point2D> path = generateAStarPath(world);
  if (!path.empty()) {
    return path[path.size() - 1];
  }

  auto rand = Random::Range(0, 5);
  int index = rand;
  auto pos = world->getCat();
  std::vector<Point2D> directions = {};
  directions.push_back(World::NE(pos));
  directions.push_back(World::NW(pos));
  directions.push_back(World::E(pos));
  directions.push_back(World::W(pos));
  directions.push_back(World::SW(pos));
  directions.push_back(World::SE(pos));

  if (world->getContent(directions[rand])) {
    index++;
    while (rand != index) {
      index++;
      if (index == directions.size()) {
        index = 0;
      }

      if (!world->getContent(directions[index])) {
        std::cout << "3 No path cesaedfghjhat found" << std::endl;
        std::cout << directions[index].x << " ed " << directions[index].y << std::endl;
        std::cout << pos.x << " ed " << pos.y << std::endl;
        return directions[index];
      }
    }

    std::cout << "2 No path cesaedfghjhat found" << std::endl;
    return Point2D::INFINITE;
  }


  std::cout << "No path cesaedfghjhat found" << std::endl;
  return directions[rand];
}
