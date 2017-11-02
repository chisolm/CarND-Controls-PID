#include <cmath>
#include <iostream>
#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    p_error = 0.0;
    i_error = 0.0;
    d_error = 0.0;

    best_error = std::numeric_limits<double>::max();
    total_error = 0.0;

    p[0] = Kp; p[1] = Kd; p[2] = Ki;
    dp[0] = 0.02;
    dp[1] = 0.2;
    dp[2] = 0.0001;

    // first twiddle
    twiddle_state = 0;
    p_index = 0;
}

void PID::NewRun() {
    total_error = 0.0;
    count = 0;
    d_error = 0.0;
    p_error = 0.0;
    i_error = 0.0;
}

void PID::EvalTwiddle() {
    // start twiddle
    switch (twiddle_state) {
        case 0: {
            p[p_index] += dp[p_index];
            // do a run before next state
            twiddle_state = 1;
            NewRun();
            return;
        }
        case 1: {
            if (total_error < best_error) {
                best_error = total_error;
                dp[p_index] *= 1.1;
                cout << "new p:\t" << p[0] << "\t" << p[1] << "\t" << p[2];
                cout << "new dp:\t" << dp[0] << "\t" << dp[1] << "\t" << dp[2];
                twiddle_state = 0;
                p_index++;
                p_index %= 3;
                NewRun();
                return;
            } else {
                p[p_index] -= 2 * dp[p_index];
                twiddle_state = 2;
                NewRun();
                return;
            }
        }
        case 2: {
            if (total_error < best_error) {
                best_error = total_error;
                dp[p_index] *= 1.1;
                cout << "new p:\t" << p[0] << "\t" << p[1] << "\t" << p[2];
                cout << "new dp:\t" << dp[0] << "\t" << dp[1] << "\t" << dp[2];
                twiddle_state = 0;
                p_index++;
                p_index %= 3;
                NewRun();
                return;
            } else {
                p[p_index] += dp[p_index];
                dp[p_index] *= 0.9;
                twiddle_state = 0;
                p_index++;
                p_index %= 3;
                NewRun();
                return;
            }
        }
    }
    cout << "unknown state\n";

    exit(-1);
}

void PID::UpdateError(double cte) {
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;

    cout << "Count: " << count << endl;

    if (count == (settle_count + eval_count)) {
        EvalTwiddle();
    }

    if (count > settle_count) {
        total_error += cte * cte;
    }
    count++;
}

double PID::TotalError() {
    return total_error;
}

double PID::SteerValue() {
    cout << "error:\t" << p_error << "\t" << d_error << "\t" << i_error << endl;
    cout << "dp values:\t" << dp[0] << "\t" << dp[1] << "\t" << dp[2] << endl;
    cout << "p values:\t" << p[0] << "\t" << p[1] << "\t" << p[2] << endl;
    cout << "error component:\t" << p[0] * p_error << "\t" << p[1] * d_error <<
            "\t" << p[2] * i_error << endl;

    return - p[0] * p_error - p[1] * d_error - p[2] * i_error;
}

double PID::ThrottleValue() {
}
