# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

# Overview
This repository contains all the code needed to complete the PID control project in Udacity's Self-Driving Car Nanodegree.

The original repository for this project is located at: [CarND-Controls-PID](https://github.com/udacity/CarND-Controls-PID)

### Attribution
The infrastructure code in this project is supplied from project repository listed above.

---

[//]: # (Image References)

[image1]: ./writeup_images/Twiddle_overview.png "Twiddle Data"
[image2]: ./writeup_images/twiddle_cycles.png "Tiddle changes"
[image3]: ./writeup_images/oscillation.png "Oscillation"
[image4]: ./writeup_images/pid_overview.png "PID Overview"
[image5]: ./writeup_images/p_comp.png "P error view"
[image6]: ./writeup_images/d_comp.png "D error view"
[image7]: ./writeup_images/i_comp.png "I error view"

## Running the Code
This project involves the Term 2 Simulator which can be downloaded [here](https://github.com/udacity/self-driving-car-sim/releases)

This repository includes two files that can be used to set up and intall uWebSocketIO for either Linux or Mac systems. For windows you can use either Docker, VMware, or even Windows 10 Bash on Ubuntu to install uWebSocketIO.

Once the install for uWebSocketIO is complete, the main program can be built and ran by doing the following from the project top directory.

1. mkdir build
2. cd build
3. cmake ..
4. make
5. ./pid

##  Sucessful run

With the settings chosen from a manual search of settings a starting default value of:

```
  pid.Init(0.20, 0.001, 2.7);  // order is P I D 
```

The manual tuning was required to get a stable set of values such that using twiddle and it's adjustments were unlikely to run the car off the track.

One big tool that is missing in this project is a way to reset the car to start so that the successive runs can encounter the same conditions.

It's unclear that using twiddle on the live running car will converge or give
useful data.  I am running with short evaluation times of 200 data points.  A
longer time near the time of a full track loop may give good data without the
need to reset the car to a common starting point.

The car will complete any number of loops with a target speed of 25 mph.  It will actually run successfully at 50mph, but I dropped the target speed to 25
to experiment with a twiddle search on parameters.

The following is an overview of a longer twiddle search with about 17 laps and 120 twiddle 'cycles'.  The way I'm defining a cycle in this case is a test of
a parameter change.  Since a twiddle loop includes an increment up and an increment down, it could have 2 cycles by this definition.

The 17 laps can be seen by the i_err shape based on the shape of the track.

![alt text][image1]

The p[3] and dp[3] parameters and their changes in the mentioned 120 twiddle cycles are presented below.  There are 4 scales to get the data on the same
graph.  I won't be using the scales, only the trends and relative values.

Note the parameter order here is PDI as used in the lessons.
```
  p[0] = Kp; p[1] = Kd; p[2] = Ki;
  dp[0] = 0.02;
  dp[1] = 0.2;
  dp[2] = 0.0001;
```

Note that all 3 dp values have a downward trend.  It is uncertain with this testing method that twiddle will converge, although the somewhat consistent
downward trend of dp values suggests it will.

![alt text][image2]

P2 still has an upward trend.  P0 and P1 are somewhat stable near the initial
manually searched.

The downward trend of dp2 with the generally upward trend of p2 suggests a problem.  This parameter is likely most succeptable to position on the track and the short testing cycle.  It would probably benefit from a much longer 
evaluation time.  (Or a consistent reset method.)

The ossilation of steering value at time suggests that p1 could be significantly higher.  My manual search did not do well much higher p1 values, although those tests were down with a target speed of 50 mph.

The oscilations seen here some of the larger ones seen in my testing.  There is a noticeable error problem shortly after the bridge and near the dirt entrance that seems to have a discontinous CTE value that almost always generates some degree of oscillation for my model.

![alt text][image3]

## Rubric

### Your code should compile.
It does with the default procedure.

### The PID procedure follows what was taught in the lessons.

It follows the PID procedure.

### Describe the effect each of the P, I, D components had in your implementation.

Here is an overview of the components controlling the steering angle.
Displayed are the p_error, d_error and i_error terms.  Also displayed are the products of those terms and their p[0-2] values.  For example p_error * p[0] is labeled as p_err_p0.

![alt text][image4]

The graph is somewhat confusing, so I'll break it down starting with the
p_error related components.  In the image below, the p_err line is not
visable as it is equal to cte, as can be seen in the boxed values.

The p_err_p0 product can be seen as a scaled version of p_err as expected.

![alt text][image5]

The d_err can be seen in the next plot as a derivitive(approximate) of the
CTE.  It is positive as the cte is increasing and negative as it is decreasing.  This ends up reinforcing the P component when CTE is still increasing giving it a counter steer effect on the steering as D(CTE slope) goes negative.

NOTE that the "spikiness" in the steering angle comes from the d_err component.  The simple subtraction of the previous cte value does not produce a smooth function.  Some additional prior values would not likely impede the intent of the D component and likely smooth it out.

![alt text][image6]

As can be seen on any given steering adjustment the i_error and i_err_p2 product are not significantly affected.  If you look at the overview data in one of the first graphs in this presentation, the values do reflect the shape of the track.  The i_error component goes negative only in the section of the track where the car does a right turn.  This does suggest the car simulation has a bias based on the direction it is turning.

![alt text][image7]

### Describe how the final hyperparameters were chosen.

See above.  The initial values were chosen by a manual search with input from the class lesson.  The twiddle search values are still converging.

### The vehicle must successfully drive a lap around the track.

It does.  It also does even with the twiddle parameter search continueing.




