#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;

class ErrorRange {
    string str = "ErrorRange";
public:
    double rd;
    ErrorRange(double d) : rd(d) { }
    void Message() const {
        cout << "ErrorRange: current x is " << rd << endl;
    }
};

class ErrorNoFile {
    string str = "ErrorNoFile";
public:
    ErrorNoFile(string s) : str(s) { }
    void Message() const {
        cout << "ErrorNoFile: " << str << endl;
    }
};

namespace Task1 {
    string file1 = "dat1.dat";
    string file2 = "dat2.dat";
    string file3 = "dat3.dat";

    namespace algoritm2 {
        double Qnr(double x, double y) {
            if (y == 0) return 1;
            else if (x > y && y != 0) return (x * x) * (10 * (y * y) - (x / 2));
            else if (x <= y && 3 * x > y && y != 0) return x * x * x * x * y;
            else if (x <= y && 3 * x <= y && y != 0) return y * y * y * y * x;
            return 0;
        }

        double Qnk1(double x, double y) {
            return 12 * Qnr(2.5 * x, y) - 3 * Qnr(x, 1.5 * y);
        }

        double Rnk(double x, double y, double z) {
            return 1.15 * x * Qnk1(x, y) + 0.95 * y * Qnk1(y, x) + 0.8 * x * Qnk1(z, x);
        }
    }
    namespace algoritm3 {
        double T1(double x) {
            return atan(acos(sin(2 * x)));
        }

        double U1(double x) {
            return atan(acos(sin(3 * x)));
        }

        double Wnr1(double x, double y) {
            if (x > y) return T1(x) - 0.9 * U1(x) * U1(y);
            else return 0.9 * T1(x) * T1(y) - U1(x);
        }

        double Wnk(double x, double y) {
            return 10 * Wnr1(2.5 * x, y) - 4 * Wnr1(x, 2.5 * y);
        }
    }
    namespace algoritm4 {

        double U2(double x) {
            if (x < -5 || x > 5) throw ErrorRange(x);

            fstream fs1(file1);
            if (!fs1) return 0;

            double X[21], U[21], count, value, r = 0;
            bool found = false;

            for (int i = 0; i < 21; i++) {
                fs1 >> count >> value;
                X[i] = count;
                U[i] = value;
                if (count == x) {
                    r = value;
                    found = true;
                    break;
                }
            }

            if (found) return r;

            fs1.close();

            for (int i = 0; i < 21; i++)
                if (x == X[i]) return U[i];

            int i = 0;
            if (x < X[0] || x > X[20]) throw ErrorRange(x);
            while (x > X[i]) i++;

            return U[i] + (U[i + 1] - U[i]) * (x - X[i]) / (X[i + 1] - X[i]);
        }


        double T2(double x) {
            fstream fs2(file2);
            if (!fs2) return 0; 
            if (x < -10 || x > 10) throw ErrorRange(x); 

            double X[21], T[21];
            for (int i = 0; i < 21; i++) fs2 >> X[i] >> T[i];
            fs2.close();

            for (int i = 0; i < 21; i++) {
                if (x == X[i]) return T[i];
            }

            int i = 0;
            if (x < X[0]) throw ErrorRange(x);
            while (x > X[i]) {
                if (i == 20) throw ErrorRange(x);
                i++;
            }

            return T[i] + (T[i + 1] - T[i]) * (x - X[i]) / (X[i + 1] - X[i]); 
        }


  
        double Wnr2(double x, double y) {
            if (x > y) return 0.9 * T2(x) - U2(x) * U2(y);
            else return T2(x) * T2(y) - 0.9 * U2(x);
        }

        
        double Wnk2(double x, double y) {
            return 10 * Wnr2(x, y) - 3 * Wnr2(x, y);
        }

 
        double Gnk(double x, double y, double z) {
            if (x * x + y * y + z * z >= 0.001) {
                return x * Wnk2(x / sqrt(x * x + y * y + z * z), y / sqrt(x * x + y * y + z * z)) +  y * Wnk2(y / sqrt(x * x + y * y + z * z), x / sqrt(x * x + y * y + z * z)) + 
                    z * Wnk2(z / sqrt(x * x + y * y + z * z), y / sqrt(x * x + y * y + z * z));
            }
            else return 0;
        }
    }
}

using namespace Task1;

int main() {
   
    try {
        fstream fs1(file1, ios::in);
        if (!fs1) throw ErrorNoFile(file1);
        fstream fs2(file2, ios::in);
        if (!fs2) throw ErrorNoFile(file2);
        fstream fs3(file3, ios::in);
        if (!fs3) throw ErrorNoFile(file3);
    }
    catch (const ErrorNoFile& e) {
        e.Message();
        return 1;
    }

    while (true) {
        double x, y, z;
        string text;
        cout << "Pleace, enter x, y, z and text: ";
        cin >> x >> y >> z >> text;

        try {
            double u = algoritm4::Gnk(x, y, z);
            double v = algoritm4::Gnk(x, y, 2 * z);
            cout << "Result: " << algoritm4::Wnk2(u, v) << endl;
        }
        catch (const ErrorRange& e) {
            e.Message();
        }
        cout << endl;
    }

    return 0;
}
