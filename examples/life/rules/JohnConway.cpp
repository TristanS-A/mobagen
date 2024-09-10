#include "JohnConway.h"

#include <iostream>

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
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
        if (liveNeighborCount == 3) {
          world.SetNext({i, j}, true);
        }
      }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int count = 0;

  for (int i = point.x - 1; i < point.x + 2; i++) {
    for (int j = point.y - 1; j < point.y + 2; j++) {
      if (point.x != i || point.y != j) {
        count += static_cast<int>(world.Get({i, j}));
      }
    }
  }

  return count;
}
