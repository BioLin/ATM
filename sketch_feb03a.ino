

// Plotclock
// cc - by Johannes Heberlein 2014
// v 1.01
// thingiverse.com/joo   wiki.fablab-nuernberg.de

// units: mm; microseconds; radians
// origin: bottom left of drawing surface

// time library see http://playground.arduino.cc/Code/time 

// delete or mark the next line as comment when done with calibration  
//#define CALIBRATION

// When in calibration mode, adjust the following factor until the servos move exactly 90 degrees
#define SERVOFAKTOR 580

// Zero-position of left and right servo
// When in calibration mode, adjust the NULL-values so that the servo arms are at all times parallel
// either to the X or Y axis
#define SERVOLEFTNULL 2025
#define SERVORIGHTNULL 903

#define SERVOPINLIFT  2
#define SERVOPINLEFT  4
#define SERVOPINRIGHT 3

// lift positions of lifting servo
#define LIFT0 1800 // on drawing surface
#define LIFT1 1200  // between numbers
#define LIFT2 800  // going towards sweeper
 
// speed of liftimg arm, higher is slower
#define LIFTSPEED 1500

// length of arms
#define L1 35
#define L2 55.1
#define L3 13.2


// origin points of left and right servo 
#define O1X 22
#define O1Y -25
#define O2X 47
#define O2Y -25

// The point of the sweeper
#define O0X 72.5
#define O0Y 41.5

#define PI 3.14159

#include <Time.h>
#include <Servo.h>

int servoLift = 1500;

Servo servo1;  // 
Servo servo2;  // 
Servo servo3;  // 

volatile double lastX = 75;
volatile double lastY = 47.5;

int last_min = 0;

void setup() 
{ 
  // Set current time only the first to values, hh,mm are needed
  setTime(19,38,0,0,0,0);

  drawTo(O0X, O0Y);
  lift(0);
  servo1.attach(SERVOPINLIFT);  //  lifting servo
  servo2.attach(SERVOPINLEFT);  //  left servo
  servo3.attach(SERVOPINRIGHT);  //  right servo
  delay(1000);

} 

void loop() 
{ 

#ifdef CALIBRATION

  // Servohorns will have 90° between movements, parallel to x and y axis
  drawTo(-3, 29.2);
  delay(5000);
  drawTo(74.1, 28);
  delay(5000);

#else 


  int i = 0;
  if (last_min != minute()) {

    if (!servo1.attached()) servo1.attach(SERVOPINLIFT);
    if (!servo2.attached()) servo2.attach(SERVOPINLEFT);
    if (!servo3.attached()) servo3.attach(SERVOPINRIGHT);

    lift(0);

    //number(8, 3, 111, 1);
    lift(2);
    
    number(20, 20, 8, 2);
    //number(26, 20, 2, 1);

   
    //number(50, 20, 3, 1);
    //number(60, 20, 4, 1);
    lift(2);
    drawTo(O0X, O0Y);
    lift(1);
    last_min = minute();

    servo1.detach();
    servo2.detach();
    servo3.detach();
  }

#endif

} 

// Writing numeral with bx by being the bottom left originpoint. Scale 1 equals a 20 mm high font.
// The structure follows this principle: move to first startpoint of the numeral, lift down, draw numeral, lift up
void number(float bx, float by, int num, float scale) {

  //O0X = 72.5 O0Y = 41.5
  float px = O0X+5,py = O0Y;
  
  switch (num) {

  case 0:
    drawTo(bx + 12 * scale, by + 6 * scale);
    lift(0);
    bogenGZS(bx + 7 * scale, by + 10 * scale, 10 * scale, -45, 383, 0.5);
    lift(1);
    break;
  case 1:

    drawTo(bx + 3 * scale, by + 15 * scale);
    lift(0);
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 10 * scale, by + 0 * scale);
    lift(1);
    break;
  case 2:
    drawTo(bx + 2 * scale, by + 12 * scale);
    lift(0);
    bogenUZS(bx + 8 * scale, by + 14 * scale, 6 * scale, 170, -45, 1);
    drawTo(bx + 1 * scale, by + 0 * scale);
    drawTo(bx + 12 * scale, by + 0 * scale);
    lift(1);
    break;
  case 3:
    drawTo(bx + 2 * scale, by + 17 * scale);
    lift(0);
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 170, -114, 1);
    bogenUZS(bx + 5 * scale, by + 5 * scale, 5 * scale, 90, -170, 1);
    lift(1);
    break;
  case 4:
    drawTo(bx + 10 * scale, by + 0 * scale);
    lift(0);
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 6 * scale);
    drawTo(bx + 12 * scale, by + 6 * scale);
    lift(1);
    break;
  case 5:
    drawTo(bx + 2 * scale, by + 5 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 6 * scale, 6 * scale, -143, 114, 1);
    drawTo(bx + 5 * scale, by + 20 * scale);
    drawTo(bx + 12 * scale, by + 20 * scale);
    lift(1);
    break;
  case 6:
    drawTo(bx + 2 * scale, by + 10 * scale);
    lift(0);
    bogenUZS(bx + 7 * scale, by + 6 * scale, 6 * scale, 114, -252, 1);
    drawTo(bx + 11 * scale, by + 20 * scale);
    lift(1);
    break;
  case 7:
    drawTo(bx + 2 * scale, by + 20 * scale);
    lift(0);
    drawTo(bx + 12 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 0);
    lift(1);
    break;
  case 8:
    drawTo(bx + 5 * scale, by + 10 * scale);
    lift(0);
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 270, -90, 1);
    bogenGZS(bx + 5 * scale, by + 5 * scale, 5 * scale, -270, 114, 1);
    lift(1);
    break;

  case 9:
    drawTo(bx + 9 * scale, by + 11 * scale);
    lift(0);
    bogenUZS(bx + 7 * scale, by + 15 * scale, 5 * scale, 230, -30, 1);
    drawTo(bx + 5 * scale, by + 0);
    lift(1);
    break;
    
  //case A;
    //drawTo(bx +  * scale, by +  * scale);
    //lift(0);
    //drawTo(bx +  * scale, by +  * scale);
    //lift(1);    
    //drawTo(bx +  * scale, by +  * scale);
    //lift(0);
    //drawTo(bx +  * scale, by +  * scale);
    //lift(1);    
    //drawTo(bx +  * scale, by +  * scale);
    //lift(0); 
    //drawTo(bx +  * scale, by +  * scale);
    //lift(1);       
  //case B;
    //drawTo(bx +  * scale, by +  * scale);
    //lift(0);
    
  //case C;
  //case D;
  //case E;
  //case F;  
  //case G;
  //case H;
  //case I;
  //case J;
  //case K;
  //case L;
  //case M;
  //case N;
  //case O; 
  //case P;
  //case Q;
  //case R; 
  //case S;
  //case T;
  //case U;  
  //case V;
  //case W;
  //case X;
  //case Y;
  //case Z;
   
  case 111:

    lift(0);
    drawTo(O0X, O0Y);
    drawTo(O0X-5, O0Y-3);
    //O0X = 72.5 O0Y = 41.5
    
    px-=7;py+=3;//65.5,44.5
    drawTo(px, py);
    // X-60 //5.5,44.5
    px-=60;
    drawTo(px, py);
    //Y-4 //5.5,40.5
    py-=4;
    drawTo(px, py);
    //X+60 //65.5,40.5
    px+=60;
    drawTo(px, py);
    //Y-5 //65.5,35.5
    py-=5;
    drawTo(px, py);

    //X-60 //5.5,35.5
    px-=60;
    drawTo(px, py);
    py-=5;
    drawTo(px, py);
    px+=60;
    drawTo(px, py);
    py-=5;
    drawTo(px, py);

    px-=60;
    drawTo(px, py);
    py-=5;
    drawTo(px, py);
    px+=60;
    drawTo(px, py);
    py-=5;
    drawTo(px, py);

    px-=60;
    drawTo(px, py);
    drawTo(60, 44);

    drawTo(O0X, O0Y);
    lift(2);

    break;

  case 11:
    drawTo(bx + 5 * scale, by + 15 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 15 * scale, 0.1 * scale, 57, -57, 1);
    lift(1);
    drawTo(bx + 5 * scale, by + 5 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 5 * scale, 0.1 * scale, 57, -57, 1);
    lift(1);
    break;

  }
}



void lift(char lift) {
  switch (lift) {
    // room to optimize  !

  case 0: //850

      if (servoLift >= LIFT0) {
      while (servoLift >= LIFT0) 
      {
        servoLift--;
        servo1.writeMicroseconds(servoLift);				
        delayMicroseconds(LIFTSPEED);
      }
    } 
    else {
      while (servoLift <= LIFT0) {
        servoLift++;
        servo1.writeMicroseconds(servoLift);
        delayMicroseconds(LIFTSPEED);

      }

    }

    break;

  case 1: //150

    if (servoLift >= LIFT1) {
      while (servoLift >= LIFT1) {
        servoLift--;
        servo1.writeMicroseconds(servoLift);
        delayMicroseconds(LIFTSPEED);

      }
    } 
    else {
      while (servoLift <= LIFT1) {
        servoLift++;
        servo1.writeMicroseconds(servoLift);
        delayMicroseconds(LIFTSPEED);
      }

    }

    break;

  case 2:

    if (servoLift >= LIFT2) {
      while (servoLift >= LIFT2) {
        servoLift--;
        servo1.writeMicroseconds(servoLift);
        delayMicroseconds(LIFTSPEED);
      }
    } 
    else {
      while (servoLift <= LIFT2) {
        servoLift++;
        servo1.writeMicroseconds(servoLift);				
        delayMicroseconds(LIFTSPEED);
      }
    }
    break;
  }
}


void bogenUZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float startrad=PI*start/180;
  float endrad=PI*ende/180;
  float inkr = -0.05;
  float count = 0;
  

  do {
    drawTo(sqee * radius * cos(startrad + count) + bx,
    radius * sin(startrad + count) + by);
    count += inkr;
  } 
  while ((startrad + count) > endrad);

}

void bogenGZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float startrad=PI*start/180;
  float endrad=PI*ende/180;
  float inkr = 0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(startrad + count) + bx,
    radius * sin(startrad + count) + by);
    count += inkr;
  } 
  while ((startrad + count) <= endrad);
}


void drawTo(double pX, double pY) {
  double dx, dy, c;
  int i;

  // dx dy of new point
  dx = pX - lastX;
  dy = pY - lastY;
  //path lenght in mm, times 4 equals 4 steps per mm
  c = floor(4 * sqrt(dx * dx + dy * dy));

  if (c < 1) c = 1;

  for (i = 0; i <= c; i++) {
    // draw line point by point
    set_XY(lastX + (i * dx / c), lastY + (i * dy / c));

  }

  lastX = pX;
  lastY = pY;
}

double return_angle(double a, double b, double c) {
  // cosine rule for angle between c and a
  return acos((a * a + c * c - b * b) / (2 * a * c));
}

void set_XY(double Tx, double Ty) 
{
  delay(1);
  double dx, dy, c, a1, a2, Hx, Hy;

  // calculate triangle between pen, servoLeft and arm joint
  // cartesian dx/dy
  dx = Tx - O1X;
  dy = Ty - O1Y;

  // polar lemgth (c) and angle (a1)
  c = sqrt(dx * dx + dy * dy); // 
  a1 = atan2(dy, dx); //
  a2 = return_angle(L1, L2, c);

  servo2.writeMicroseconds(floor(((a2 + a1 - M_PI) * SERVOFAKTOR) + SERVOLEFTNULL));

  // calculate joinr arm point for triangle of the right servo arm
  a2 = return_angle(L2, L1, c);
  Hx = Tx + L3 * cos((a1 - a2 + 0.621) + M_PI); //36,5°
  Hy = Ty + L3 * sin((a1 - a2 + 0.621) + M_PI);

  // calculate triangle between pen joint, servoRight and arm joint
  dx = Hx - O2X;
  dy = Hy - O2Y;

  c = sqrt(dx * dx + dy * dy);
  a1 = atan2(dy, dx);
  a2 = return_angle(L1, (L2 - L3), c);

  servo3.writeMicroseconds(floor(((a1 - a2) * SERVOFAKTOR) + SERVORIGHTNULL));

}





