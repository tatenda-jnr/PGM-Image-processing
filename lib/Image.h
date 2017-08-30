/**
 * author   : Tatenda Muvhu
 * version : 2017/05/07
 */

#ifndef MVHADM001_IMAGE_H
#define MVHADM001_IMAGE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

namespace MVHADM001 {
    class Node {
    public:
        float value{0};
        int x{0}, y{0};
    };

    class Matrix {
    public:
        std::vector<Node> data;
    };


    class Image {
    private:
        int width, height;
        std::unique_ptr<unsigned char[]> data;

    public:

        class iterator {
        private:
            unsigned char *ptr;

            friend class Image;

            explicit iterator(unsigned char *p) : ptr(p) {}

        public:

            iterator(const iterator &other) : ptr(other.ptr) {}

            iterator &operator=(const iterator &other) {
                if (this != &other) this->ptr = other.ptr;
                return *this;
            }

            iterator(iterator &&other) noexcept : ptr(other.ptr) {}

            iterator &operator=(iterator &&other) noexcept {
                if (this != &other) this->ptr = other.ptr;
                return *this;
            }

            ~iterator() {
                ptr = nullptr;
            };

            // define overloaded ops: *, ++, --, =
            // other methods for iterator
            iterator &operator++() {
                ptr++;
                return *this;
            }

            iterator operator++(int) {
                iterator temp = *this;
                ptr++;
                return temp;
            }

            iterator &operator--() {
                ptr--;
                return *this;
            }

            unsigned char &operator*() {
                return *ptr;
            }

            bool operator!=(const iterator &other) {
                return this->ptr != other.ptr;
            }

        };

        Image();

        Image(int, int, unsigned char []);

        ~Image();

        Image(const Image &other);

        Image &operator=(const Image &other);

        Image(Image &&other) noexcept;

        Image &operator=(Image &&other) noexcept;

        Image::iterator begin() const {
            return iterator(data.get());
        }

        Image::iterator end() {
            return iterator(data.get() + (width * height));
        }

        //overloaded operators
        Image operator+(Image &other);

        Image operator-(Image &other);

        Image operator!();

        Image operator/(Image &other);

        Image operator*(int f);

        Image operator%(Matrix &filter);

        friend std::ostream &operator<<(std::ostream &out, Image &image);

        friend std::istream &operator>>(std::istream &in, Image &image);

        //load and save images
        void load(std::string fileName);

        void save(std::string fileName);
    };
}
#endif
