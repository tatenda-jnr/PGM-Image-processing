/**
 * author   : Tatenda Muvhu
 * version : 2017/05/07
 */


#include "Image.h"

namespace MVHADM001 {
    using namespace std;

    /**
     *  default constructor 
     *  set width and height = 0
     */
    Image::Image() : width(0), height(0) {
    }

    /**
     * constructor to facilitate unit testing
     * @param w
     * @param h
     * @param array
     */
    Image::Image(int w, int h, unsigned char *array) : width(w), height(h), data(array) {
    }

    /**
     * destructor
     */
    Image::~Image() {
        data.reset(nullptr);
    }

    /**
     * copy constructor
     * @param other 
     */
    Image::Image(const Image &other) {
        this->width = other.width;
        this->height = other.height;
        this->data.reset(new unsigned char[width * height]);
        Image::iterator iterator = this->begin(), end = this->end();
        Image::iterator iterator_other = other.begin();

        while (iterator != end) {
            *iterator = *iterator_other;
            iterator++;
            iterator_other++;
        }
    }

    /**
     * copy assignment
     * @param other
     * @return
     */
    Image &Image::operator=(const Image &other) {
        if (this != &other) {
            this->width = other.width;
            this->height = other.height;
            this->data.reset(new unsigned char[width * height]);
            Image::iterator iterator = this->begin(), end = this->end();
            Image::iterator iterator_other = other.begin();

            while (iterator != end) {
                *iterator = *iterator_other;
                iterator++;
                iterator_other++;
            }
        }
        return *this;
    }

    /**
     * move constructor
     * @param other
     */
    Image::Image(Image &&other) noexcept {
        this->width = other.width;
        this->height = other.height;
        this->data.reset(new unsigned char[width * height]);
        this->data = move(other.data);
    }

    /**
     * move assignment
     * @param other
     * @return
     */
    Image &Image::operator=(Image &&other) noexcept {
        if (this != &other) {
            this->width = other.width;
            this->height = other.height;
            this->data.reset(new unsigned char[width * height]);
            this->data = move(other.data);
        }
        return *this;
    }

    /**
     * operator overloading ( operator + ),
     * makes sure images have the same dimensions
     * @param other
     * @return this + other
     */
    Image Image::operator+(Image &other) {
        Image::iterator iterator = this->begin(), end = this->end();
        Image::iterator iterator_other = other.begin();
        if (this->width == other.width && this->height == other.height) {
            while (iterator != end) {
                int value = *iterator + *iterator_other;
                value > 255 ? *iterator = 255 : *iterator = (unsigned char) value;
                iterator++;
                iterator_other++;
            }
        }
        return *this;
    }

    /**
     * operator overloading ( operator - ),
     * makes sure images have the same dimensions
     * @param other
     * @return this - other
     */
    Image Image::operator-(Image &other) {
        Image::iterator iterator = this->begin(), end = this->end();
        Image::iterator iterator_other = other.begin();
        if (this->width == other.width && this->height == other.height) {
            while (iterator != end) {
                int value = (int) *iterator - (int) *iterator_other;
                value < 0 ? *iterator = 0 : *iterator = (unsigned char) value;
                iterator++;
                iterator_other++;
            }
        }
        return *this;
    }

    /**
     * invert image operator
     * @return inverted image
     */
    Image Image::operator!() {
        Image::iterator iterator = this->begin(), end = this->end();
        while (iterator != end) {
            *iterator = (unsigned char) (255 - *iterator);
            iterator++;
        }
        return *this;
    }

    /**
     * mask image
     * @param other
     * @return
     */
    Image Image::operator/(Image &other) {
        Image::iterator iterator = this->begin(), end = this->end();
        Image::iterator iterator_other = other.begin();
        if (this->width == other.width && this->height == other.height) {
            while (iterator != end) {
                if (*iterator_other != 255) *iterator = 0;
                iterator++;
                iterator_other++;
            }
        }
        return *this;
    }

    /**
     * threshold operator
     * @param f - threshold
     * @return output image
     */
    Image Image::operator*(int f) {
        Image::iterator iterator = this->begin(), end = this->end();
        while (iterator != end) {
            *iterator > f ? *iterator = 255 : *iterator = 0;
            iterator++;
        }
        return *this;
    }

    /**
     * Extra credit
     * apply filter matrix to image
     * @param filter
     * @return filtered image
     */
    Image Image::operator%(Matrix &filter) {
        Image output = *this;
        Image::iterator iterator = this->begin(), iterator_other = output.begin();
        unsigned char *temp = data.get();

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                float sum = 0;
                for (Node n : filter.data) { // checking if index is in range
                    if ((j + n.x) >= 0 && (j + n.x) < width && (i + n.y) >= 0 && (i + n.y) < height) {
                        int pos = *(temp + ((i + n.y) * width) + (j + n.x));
                        sum = sum + (pos * n.value);
                    }
                }
                if (sum < 0) sum = 0;
                if (sum > 255) sum = 255;
                *iterator_other = (unsigned char) sum;
                *iterator++;
                *iterator_other++;
            }
        }
        return output;
    }

    /**
     * overloading the << stream parameter
     * @param out
     * @param image
     * @return
     */
    std::ostream &operator<<(std::ostream &out, Image &image) {
        if (out) {
            out << "P5\n";
            out << image.height << " " << image.width;
            out << "\n255\n";
            out.write(reinterpret_cast<char *>(image.data.get()), image.width * image.height);
        }
        return out;
    }

    /**
     * overloading the >> stream parameter
     * @param out
     * @param image
     * @return
     */
    std::istream &operator>>(std::istream &in, Image &image) {
        if (in) {
            string line;
            while (std::getline(in, line)) {
                if (line.substr(0) != "P" || line.substr(0) != "#") {
                    if (line == "255") break;
                    istringstream ss(line);
                    ss >> image.height >> ws >> image.width;
                }
            }

            image.data.reset(new unsigned char[image.width * image.height]);
            auto *arr = new char[image.width * image.height];
            in.read(arr, image.width * image.height);
            image.data.reset((unsigned char *) arr);
        }
        return in;
    }

    /**
     * reads pgm file and stores it into image object
     * @param fileName
     */
    void Image::load(string fileName) {
        ifstream input(fileName, ios::binary);
        input >> *this;
        input.close();
    }

    /**
     * saves image to a file
     * @param outputName
     */
    void Image::save(string outputName) {
        ofstream output(outputName, ios::binary);
        output << *this;
        output.close();
    }
}