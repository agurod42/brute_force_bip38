#include <fstream>
#include <json/json.h>
#include <string>

using namespace std;

namespace brute38 {

class config {
    
private:
    Json::Value root;

public:
    config(const string &file_path) {
        ifstream file_stream(file_path, ifstream::binary);
        file_stream >> root;
        file_stream.close();
    }

    const string get(const string &key, const string &default_value = "") const {
        return root.get(key, default_value).asString();
    }

};

}