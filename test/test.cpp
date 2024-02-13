#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "../src/DD.h"

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
    StandardDD_gnu<uint32_t> stt(-1);
    stt.insert(1);
    stt.insert(2);
    stt.insert(3);
    stt.insert(4);
    stt.erase(4);
//    st.insert(2);
    stt.insert(4);
    stt.insert(5);
    for (int i = 0; i < stt.size(); i++) {
        cout << stt.getKth(i) << endl;
    }

    StandardDD_clang<int32_t> st(
            -1,
            [](int32_t& a, int32_t& b)->bool{return a < b;},
            [](int32_t& a, int32_t& b)->bool{return a == b;});
    st.insert(1);
    st.insert(2);
    st.insert(3);
    st.insert(4);
    st.erase(4);
//    st.insert(2);
    st.insert(4);
    st.insert(5);
    for (int i = 0; i < st.size(); i++) {
        cout << st.getKth(i) << endl;
    }
}