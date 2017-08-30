/**
 * author   : Tatenda Muvhu
 * version : 2017/05/07
 */
#include <iterator>
#include "lib/Image.h"

int main(int arg_count, char *arg_value[]) {
    using namespace std;
    using namespace MVHADM001;

    if (arg_count < 3) {
        cout << "usage : imageops <option> OutputImageName" << endl;
        cout << "options :" << endl;
        cout << "   -a image1 image2 output" << endl;
        cout << "   -s image1 image2 output" << endl;
        cout << "   -i image1 output" << endl;
        cout << "   -l image1 image2 output" << endl;
        cout << "   -t image1 int_value output" << endl;
        cout << "   -g image1 matrix_file output" << endl;
        return 0;
    }

    string arg = string(arg_value[1]);
    string file1 = string(arg_value[2]), file2, output;
    if (arg == "-a") {
        file2 = string(arg_value[3]);
        output = string(arg_value[4]);

        Image img1;
        img1.load(file1);
        Image img2;
        img2.load(file2);
        Image out = img1 + img2;
        out.save(output);
    }

    if (arg == "-s") {
        file2 = string(arg_value[3]);
        output = string(arg_value[4]);

        Image img1;
        img1.load(file1);
        Image img2;
        img2.load(file2);
        Image out = img1 - img2;
        out.save(output);
    }

    if (arg == "-i") {
        output = string(arg_value[3]);
        Image img1;
        img1.load(file1);
        Image out = !img1;
        out.save(output);
    }

    if (arg == "-l") {
        file2 = string(arg_value[3]);
        output = string(arg_value[4]);

        Image img1;
        img1.load(file1);
        Image img2;
        img2.load(file2);
        Image out = img1 / img2;
        out.save(output);
    }

    if (arg == "-t") {
        int threshold = stoi(string(arg_value[3]));
        output = string(arg_value[4]);

        Image img1;
        img1.load(file1);
        Image out = (img1 * threshold);
        out.save(output);
    }

    if (arg == "-g") {
        ifstream filter_input(string(arg_value[3]).c_str());
        output = string(arg_value[4]);
        if (filter_input) {
            string line, buffer;
            while (getline(filter_input, line)) buffer += (" " + line);

            std::istringstream dims(buffer);
            std::vector<std::string> tokens{std::istream_iterator<std::string>{dims},
                                            std::istream_iterator<std::string>{}};

            Matrix m = Matrix();
            int N = stoi(tokens[0]), start = (N - (2 * N)) / 2, end = N / 2, i = 1;
            for (int row = start; row <= end; row++) {
                for (int col = start; col <= end; col++) {
                    Node n;
                    n.value = stof(tokens[i]);
                    n.x = col;
                    n.y = row;
                    m.data.push_back(n);
                    i++;
                }
            }

            Image img1;
            img1.load(file1);

            Image out = (img1 % m);
            out.save(output);
        }
    }
    return 0;
}