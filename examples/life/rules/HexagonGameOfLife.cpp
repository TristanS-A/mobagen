//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
#include <iostream>

void HexagonGameOfLife::Step(World& world) {
  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {
      const bool currSpace = world.Get({i, j});
      const int liveNeighborCount = CountNeighbors(world, {i, j});
      if (currSpace) {
        if (liveNeighborCount < 2) {
          world.SetNext({i, j}, false);
        }
        else if (liveNeighborCount <= 3) {
          world.SetNext({i, j}, true);
        }
        else {
          world.SetNext({i, j}, false);
        }
      }
      else {
        if (liveNeighborCount == 2) {
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

  return count;
 }
