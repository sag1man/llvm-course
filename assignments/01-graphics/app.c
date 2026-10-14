#include "sim.h"

#define NUMBER_OF_BALLS 12
#define uint unsigned int

static int random_in_range(const int min_bound, const int max_bound) {
  const int random = simRand();
  return min_bound + (random < 0 ? -random : random) % (max_bound - min_bound + 1);
}

static int random_velocity(void) {
  const int velocity = random_in_range(1, 4);
  return simRand() % 2 ? velocity : -velocity;
}

void app(void) {
  uint balls_x_coordinates[NUMBER_OF_BALLS];
  uint balls_y_coordinates[NUMBER_OF_BALLS];
  int balls_x_velocity[NUMBER_OF_BALLS];
  int balls_y_velocity[NUMBER_OF_BALLS];
  uint balls_powers[NUMBER_OF_BALLS];

  for (uint ball_index = 0; ball_index < NUMBER_OF_BALLS; ball_index++) {
    balls_x_coordinates[ball_index] = random_in_range(0 + (SIM_X_SIZE / 16), SIM_X_SIZE - (SIM_X_SIZE / 16));
    balls_y_coordinates[ball_index] = random_in_range(0 + (SIM_Y_SIZE / 16), SIM_Y_SIZE - (SIM_Y_SIZE / 16));
    balls_x_velocity[ball_index] = random_velocity();
    balls_y_velocity[ball_index] = random_velocity();
    balls_powers[ball_index] = random_in_range(1000, 3000);
  }

  while (1) {
    for (int index = 0; index < NUMBER_OF_BALLS; index++) {
      int next_x = (int) balls_x_coordinates[index] + balls_x_velocity[index];
      int next_y = (int) balls_y_coordinates[index] + balls_y_velocity[index];

      if (next_x < 0) {
        next_x = 0;
        balls_x_velocity[index] = -balls_x_velocity[index];
      } else if (next_x >= SIM_X_SIZE) {
        next_x = SIM_X_SIZE - 1;
        balls_x_velocity[index] = -balls_x_velocity[index];
      }

      if (next_y < 0) {
        next_y = 0;
        balls_y_velocity[index] = -balls_y_velocity[index];
      } else if (next_y >= SIM_Y_SIZE) {
        next_y = SIM_Y_SIZE - 1;
        balls_y_velocity[index] = -balls_y_velocity[index];
      }

      balls_x_coordinates[index] = (uint) next_x;
      balls_y_coordinates[index] = (uint) next_y;
    }

    for (uint y = 0; y < SIM_Y_SIZE; y++) {
      for (uint x = 0; x < SIM_X_SIZE; x++) {
        uint field = 0;

        for (int i = 0; i < NUMBER_OF_BALLS; i++) {
          const int dx = (int) x - (int) balls_x_coordinates[i];
          const int dy = (int) y - (int) balls_y_coordinates[i];

          const uint dist2 = (uint) (dx * dx + dy * dy);

          field += balls_powers[i] / (dist2 / 100 + 1);
        }

        uint r = 0;
        uint g = 0;
        uint b = 0;

        if (field < 30) {
          b = field * 2;
        } else if (field < 80) {
          const uint t = field - 30;

          r = t * 3;
          b = 100 + t * 3;

          if (r > 255) {
            r = 255;
          }
          if (b > 255) {
            b = 255;
          }
        } else if (field < 160) {
          const uint t = field - 80;

          r = 255 - t * 3;
          g = t * 3;
          b = 255;

          if (r > 255) {
            r = 0;
          }
          if (g > 255) {
            g = 255;
          }
        } else {
          r = 255;
          g = 255;
          b = 255;
        }

        const uint color = 0xFF000000u | (r << 16) | (b << 8) | g;

        simPutPixel(x, y, color);
      }
    }

    simFlush();
  }
}
