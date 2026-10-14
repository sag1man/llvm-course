#ifndef SIM_H
#define SIM_H

#define SIM_X_SIZE 1280
#define SIM_Y_SIZE 720

#ifndef __sim__
void simInit();
void app();
void simExit();
void simFlush();
void simPutPixel(int x, int y, int argb);
int simRand();
int simHasClick();
int simGetClick();
#endif // __sim__

#endif // SIM_H
