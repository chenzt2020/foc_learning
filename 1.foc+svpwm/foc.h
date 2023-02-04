#ifndef FOC_H
#define FOC_H

#include <cmath>
#include <cstdint>

class FOC {
public:
  float u_d;
  float u_q;
  float theta;

  float u_alpha;
  float u_beta;

  float t_a;
  float t_b;
  float t_c;

  float i_a;
  float i_b;
  float i_c;

  float i_alpha;
  float i_beta;

  float i_d;
  float i_q;

  void ipark() {
    sine = sin(theta);
    cosine = cos(theta);
    u_alpha = u_d * cosine - u_q * sine;
    u_beta = u_q * cosine + u_d * sine;
  }

  void ipark2() {
    u_alpha = u_d * cosine - u_q * sine;
    u_beta = u_q * cosine + u_d * sine;
  }

  void clarke() {
    i_alpha = i_a;
    i_beta = (i_a + 2 * i_b) * 0.5773502691896257;
  }

  void park() {
    sine = sin(theta);
    cosine = cos(theta);
    i_d = i_alpha * cosine + i_beta * sine;
    i_q = i_beta * cosine - i_alpha * sine;
  }

  void svpwm() {
    constexpr float ts = 1;

    float u1 = u_beta;
    float u2 = -0.8660254037844386 * u_alpha - 0.5 * u_beta;
    float u3 = 0.8660254037844386 * u_alpha - 0.5 * u_beta;

    uint8_t sector = (u1 > 0.0) + ((u2 > 0.0) << 1) + ((u3 > 0.0) << 2);

    if (sector == 5) {
      float t4 = u3;
      float t6 = u1;
      float sum = t4 + t6;
      if (sum > ts) {
        k_svpwm = ts / sum;
        t4 = k_svpwm * t4;
        t6 = k_svpwm * t6;
      }
      float t7 = (ts - t4 - t6) / 2;
      t_a = t4 + t6 + t7;
      t_b = t6 + t7;
      t_c = t7;
    } else if (sector == 1) {
      float t2 = -u3;
      float t6 = -u2;
      float sum = t2 + t6;
      if (sum > ts) {
        k_svpwm = ts / sum;
        t2 = k_svpwm * t2;
        t6 = k_svpwm * t6;
      }
      float t7 = (ts - t2 - t6) / 2;
      t_a = t6 + t7;
      t_b = t2 + t6 + t7;
      t_c = t7;
    } else if (sector == 3) {
      float t2 = u1;
      float t3 = u2;
      float sum = t2 + t3;
      if (sum > ts) {
        k_svpwm = ts / sum;
        t2 = k_svpwm * t2;
        t3 = k_svpwm * t3;
      }
      float t7 = (ts - t2 - t3) / 2;
      t_a = t7;
      t_b = t2 + t3 + t7;
      t_c = t3 + t7;
    } else if (sector == 2) {
      float t1 = -u1;
      float t3 = -u3;
      float sum = t1 + t3;
      if (sum > ts) {
        k_svpwm = ts / sum;
        t1 = k_svpwm * t1;
        t3 = k_svpwm * t3;
      }
      float t7 = (ts - t1 - t3) / 2;
      t_a = t7;
      t_b = t3 + t7;
      t_c = t1 + t3 + t7;
    } else if (sector == 6) {
      float t1 = u2;
      float t5 = u3;
      float sum = t1 + t5;
      if (sum > ts) {
        k_svpwm = ts / sum;
        t1 = k_svpwm * t1;
        t5 = k_svpwm * t5;
      }
      float t7 = (ts - t1 - t5) / 2;
      t_a = t5 + t7;
      t_b = t7;
      t_c = t1 + t5 + t7;
    } else if (sector == 4) {
      float t4 = -u2;
      float t5 = -u1;
      float sum = t4 + t5;
      if (sum > ts) {
        k_svpwm = ts / sum;
        t4 = k_svpwm * t4;
        t5 = k_svpwm * t5;
      }
      float t7 = (ts - t4 - t5) / 2;
      t_a = t4 + t5 + t7;
      t_b = t7;
      t_c = t5 + t7;
    }
  }

private:
  float sine;
  float cosine;

  float k_svpwm;
};

#endif // FOC_H
