#include <chrono>
#include <sstream>
#include <string>

using namespace std;

namespace brute38 {

class progress {

private:
    chrono::system_clock::time_point startup;
    int total;

public:
    progress(int t) {
        startup = chrono::system_clock::now();
        total = t;
    }

    string log(int progress) {
        ostringstream string_stream;
        
        string_stream << "\033[2K\r" << "Progress: " << (progress * 100 / total) << "% (" << progress << "/" << total << "), ";

        if (progress == 0) {
            string_stream << "calculating estimated duration...";
        } else {
            chrono::duration<double> diff = chrono::system_clock::now() - startup;
            string_stream << "finished in ~ " << (diff.count() / progress) * (total - progress) << "s";
        }

        return string_stream.str();
    }

};

}