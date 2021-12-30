#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double R, angle_deg, angle_rad, r, wave_length;

double y(double x)
{
    return -sqrt(R * R - x * x);
}

int main()
{
    double wave_len_nano;
    double dx;
    ifstream config("config.txt");
    config >> R >> angle_deg >> wave_len_nano >> dx;
    config.close();
    wave_length = wave_len_nano / 1000000000;
    angle_rad = angle_deg * M_PI / 90;
    r = R * sin(angle_rad / 2);

    ofstream delta_w("deltas.txt");
    delta_w.clear();

    double cur_x = 0;
    while (cur_x <= r)
    {
        double delta = 2 * (R - y(cur_x)) + wave_length / 2;
        double delta_w_ = (int)(delta * 1e9) % (int)(wave_length * 1e9);
        delta_w << cur_x << ";" << delta_w_ << endl;
        cur_x += dx;
    }
    delta_w.close();
}
