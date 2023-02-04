#ifndef PID_H
#define PID_H

class PID {
public:
  float k_p;
  float k_i;
  float k_d;

  float u_i;
  float u;

  void init(float k_p, float k_i, float k_d, float u_max) {
    this->k_p = k_p;
    this->k_i = k_i;
    this->k_d = k_d;
    this->u_max = u_max;
  }
  void reset() {
    u_i = 0;
    saturation_flag = 0;
    last_error = 0;
  }
  float calc(float error) {
    if (saturation_flag == 0) {
      u_i += k_i * error;
    }
    u = k_p * error + u_i + k_d * (error - last_error);
    last_error = error;

    if (u > u_max) {
      u = u_max;
      saturation_flag = 1;
    } else if (u < -u_max) {
      u = -u_max;
      saturation_flag = 1;
    } else {
      saturation_flag = 0;
    }
    return u;
  }

private:
  bool saturation_flag;
  float last_error;
  float u_max;
};

#endif // PID_H
