#include <fstream>
#include <string>

using namespace std;

namespace brute38 {

class config {

public:
    string encripted_private_key;
    string public_address;

    config(const string &file_path) {
        ifstream file_stream(file_path);
        for (string line; getline(file_stream, line);) {
            int eqp = line.find("=");
            string key = line.substr(0, eqp);
            if (key == "encryptedPrivateKey") encripted_private_key = line.substr(eqp + 1);
            else if (key == "publicAddressHex") public_address = line.substr(eqp + 1);
        }
        file_stream.close();
    }

};

}