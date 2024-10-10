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
  std::cout << pos.x << " ed " << pos.y << std::endl;
  std::vector<Point2D> directions = {};
  directions.push_back(World::NE(pos));
  std::cout << directions[directions.size()-1].x << " ed " << directions[directions.size()-1].y << std::endl;
  directions.push_back(World::NW(pos));
  std::cout << directions[directions.size()-1].x << " ed " << directions[directions.size()-1].y << std::endl;
  directions.push_back(World::E(pos));
  std::cout << directions[directions.size()-1].x << " ed " << directions[directions.size()-1].y << std::endl;
  directions.push_back(World::W(pos));
  std::cout << directions[directions.size()-1].x << " ed " << directions[directions.size()-1].y << std::endl;
  directions.push_back(World::SW(pos));
  std::cout << directions[directions.size()-1].x << " ed " << directions[directions.size()-1].y << std::endl;
  directions.push_back(World::SE(pos));
  std::cout << directions[directions.size()-1].x << " ed " << directions[directions.size()-1].y << std::endl;

  std::cout << (world->getContent(directions[rand])) << " " << rand << " " << index << " " << directions[rand].x << " ed " << directions[rand].y  << std::endl;
  if (world->getContent(directions[rand])) {
    index++;
    while (rand != index) {
      if (index >= directions.size()) {
        index = 0;
      }

      if (!world->getContent(directions[index])) {
        std::cout << "3 No path cesaedfghjhat found" << std::endl;
        std::cout << directions.size() << " " << index << " " << directions[index].x << " ed " << directions[index].y << std::endl;
        std::cout << pos.x << " ed " << pos.y << std::endl;
        return directions[index];
      }
      else {
        std::cout << (!world->getContent(directions[index])) << " " << directions.size() << " " << index << " " << directions[index].x << " ed " << directions[index].y  << std::endl;
      }

      index++;
    }

    std::cout << directions.size() << " " << index << " " << directions[index].x << " ed " << directions[index].y << std::endl;
    std::cout << pos.x << " ed " << pos.y << std::endl;
    std::cout << "2 No path cesaedfghjhat found" << std::endl;
    return Point2D::INFINITE;
  }


  std::cout << "No path cesaedfghjhat found" << std::endl;
  return directions[rand];
}
