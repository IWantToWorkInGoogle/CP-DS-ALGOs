#include <string>
#include <filesystem>
#include <fstream>

using namespace std;

int main() {
#ifdef OlegSanders
    {
        filesystem::path input_file = filesystem::current_path();
        input_file /= "input.txt";
        if (!exists(input_file)) {
            ofstream create(input_file);
            create.close();
        }

        filesystem::path output_file = filesystem::current_path();
        output_file /= "output.txt";
        if (!exists(output_file)) {
            ofstream create(output_file);
            create.close();
        }

        freopen(input_file.string().c_str(), "r", stdin);
        freopen(output_file.string().c_str(), "w", stdout);
    }
#endif
}