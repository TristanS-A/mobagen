//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
#include <iostream>

void HexagonGameOfLife::Step(World& world) {
  //Iterates over the whole grid
  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {
      const bool currSpace = world.Get({i, j}); //Gets the current space state
      const int liveNeighborCount = CountNeighbors(world, {i, j}); //Gets the live neighbor count of that point
      if (currSpace) { //Conditions for if the currSpace state is alive
        if (liveNeighborCount < 2) { //Rule for killing space due to underpopulation
          world.SetNext({i, j}, false);
        }
        else if (liveNeighborCount <= 3) { //Rule for setting space to alive for next generation
          world.SetNext({i, j}, true);
        }
        else { //Rule for killing space due to overpopulation
          world.SetNext({i, j}, false);
        }
      }
      else { //Rules for dead particles
        if (liveNeighborCount == 2) { //Rule for birthing new particle
          world.SetNext({i, j}, true);
        }
      }
    }
  }
}

int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  int start = point.x - static_cast<int>(point.y % 2 == 0);
  int count = 0;

  //Calculates live neighbors above
  for (int i = start; i < start + 2; i++) {
    if (world.Get({i, point.y - 1})) {
      count++;
    }
  }

  //Calculates live neighbors below
  for (int i = start; i < start + 2; i++) {
    if (world.Get({i, point.y + 1})) {
      count++;
    }
  }

  //Calculates live neighbors on sides
  start = point.x - 1;
  for (int i = start; i < start + 3; i++) {
    if (i != point.x) {
      if (world.Get({i, point.y})) {
        count++;
      }
    }
  }

  return count; //Returns total live neighbor count
 }
