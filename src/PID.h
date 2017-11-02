#ifndef PID_H
#define PID_H


class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  double Kp;
  double Ki;
  double Kd;
  */ 
  double p[3];
  double dp[3];

  double best_error;
  double total_error = 0.0;
  int settle_count = 20;
  int eval_count = 200;
  int p_index;
  int twiddle_state;
  int count;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);
  void EvalTwiddle();
  void NewRun();

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  double SteerValue();

  double ThrottleValue();
};

#endif /* PID_H */
