#include <chrono>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "bip38.hpp"
#include "config.hpp"
#include "progress.hpp"

#define CONFIG_PATH          "config.json"
#define INVALID_SECRETS_PATH "invalid_secrets.json"
#define VALID_SECRETS_PATH   "valid_secret.json"

using namespace brute38;
using namespace std;

int main(int argc, char** argv) {

    config config(CONFIG_PATH);
    string public_key = config.get("publicAddressHex");
    string private_key = config.get("encryptedPrivateKey");

    unsigned number_of_cpus = thread::hardware_concurrency();

    vector<string> secrets = {
        "Satoshi",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "1",
        "TestingOneTwoThree",
    };
    atomic_int tested_secrets(0);

    Json::Value invalid_secrets;
    Json::Value valid_secrets;

    // Display start info

    cout << "Testing " << secrets.size() << " secrets on " << number_of_cpus << " CPU cores..." << endl;
    cout << "Public address: " << public_key << endl;
    cout << "BIP38 encrypted private key: " << private_key << endl;

    // Import invalid secrets

    cout << "Importing invalid secrets from \"" << INVALID_SECRETS_PATH << "\"..." << endl;

    try {
        ifstream file_stream(INVALID_SECRETS_PATH, ifstream::binary);
        file_stream >> invalid_secrets;
        cout << "Imported " << invalid_secrets.size() << " invalid secrets that will be skipped." << endl; 
    } catch (...) {
        cout << "No invalid secrets have been found, moving on..." << endl;
    }

    // Filter secrets

    cout << "Filtering secrets..." << endl;

    secrets.erase(
        remove_if(secrets.begin(), secrets.end(), [&](string secret) { 
            for (auto invalid_secret : invalid_secrets)
                if (invalid_secret == secret) return true;
            return false;
        }),
        secrets.end()
    );

    // Decrypt
    
    vector<thread>      threads;
    mutex               sync_mutex;
    condition_variable  sync_condition;
    atomic_int          number_of_threads(0);
    progress            progress(secrets.size());

    cout << "Decrypting with " << secrets.size() << " secrets..." << endl;

    for (auto secret : secrets) {
        unique_lock<mutex> sync_lock(sync_mutex);
        sync_condition.wait(sync_lock, [&] { return number_of_threads < number_of_cpus; });

        cout << progress.log(tested_secrets) << flush;

        thread([&](string secret) {

            number_of_threads++;

            // <where the decryption happens> 
            string decrypted_public_key = bip38_public_key_from_private_key(private_key, secret);

            tested_secrets++;

            if (decrypted_public_key == public_key) {
                cout << endl << "Saving valid secret (" << secret << ") to \"" << VALID_SECRETS_PATH << "\"..." << endl;
                ofstream file_stream(VALID_SECRETS_PATH, ofstream::out);
                file_stream << secret;
                file_stream.close();
                cout << "A valid secret has been found, aborting..." << endl;
                exit(0);
            }
            // </>

            number_of_threads--;

            if (number_of_threads < number_of_cpus) {
                unique_lock<mutex> sync_lock(sync_mutex);
                sync_condition.notify_all();
            }

        }, secret).detach();
    }

    // Wait until all secrets has been tested

    unique_lock<mutex> sync_lock(sync_mutex);
    sync_condition.wait(sync_lock, [&] { return tested_secrets == secrets.size(); });

    return 0;
}