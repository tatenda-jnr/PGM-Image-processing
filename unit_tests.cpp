/**
 * author   : Tatenda Muvhu
 * version : 2017/05/14
 */

#define CATCH_CONFIG_MAIN

#include "lib/catch.hpp"
#include "lib/Image.h"

using namespace MVHADM001;
using namespace std;

TEST_CASE("image") {
    SECTION("copy") {
        unsigned char values[] = {155, 49, 200, 225, 84, 59, 100, 232, 255};
        unsigned char *heap = new unsigned char[9];
        for (int i = 0; i < 9; i++) heap[i] = values[i];
        Image image(3, 3, heap);

        Image copy = image;

        Image::iterator iterator = copy.begin(), end = copy.end();
        int i = 0;
        while (iterator != end) {
            REQUIRE((int) *iterator == (int) values[i]);
            *iterator++;
            i++;
        }
    }

    SECTION("move") {
        unsigned char values[] = {155, 49, 200, 225, 84, 59, 100, 232, 255};
        unsigned char *heap = new unsigned char[9];
        for (int i = 0; i < 9; i++) heap[i] = values[i];
        Image image(3, 3, heap);

        Image moved = move(image);

        Image::iterator iterator = moved.begin(), end = moved.end();
        int i = 0;
        while (iterator != end) {
            REQUIRE((int) *iterator == (int) values[i]);
            *iterator++;
            i++;
        }
    }

    SECTION("iterator") {
        unsigned char values[] = {155, 49, 200, 225, 84, 59, 100, 232, 255};
        unsigned char *heap = new unsigned char[9];
        for (int i = 0; i < 9; i++) heap[i] = values[i];
        Image image(3, 3, heap);
        Image::iterator iterator = image.begin(), end = image.end();
        int i = 0;
        while (iterator != end) {
            REQUIRE((int) *iterator == (int) values[i]);
            *iterator++;
            i++;
        }
    }

    SECTION("add") {
        unsigned char values[] = {128, 49, 203, 75, 28, 59, 74, 82, 255};
        unsigned char expected[] = {255, 98, 255, 150, 56, 118, 148, 164, 255};

        unsigned char *heap = new unsigned char[9];
        unsigned char *heap1 = new unsigned char[9];
        for (int i = 0; i < 9; i++) {
            heap[i] = values[i];
            heap1[i] = values[i];
        }

        Image image(3, 3, heap);
        Image image1(3, 3, heap1);

        Image out = image + image1;
        Image::iterator iterator = out.begin(), end = out.end();
        int i = 0;
        while (iterator != end) {
            REQUIRE((int) *iterator == (int) expected[i]);
            *iterator++;
            i++;
        }
    }

    SECTION("subtract") {
        unsigned char values[] = {155, 49, 200, 225, 84, 59, 100, 232, 234};
        unsigned char values1[] = {200, 49, 100, 75, 28, 255, 74, 82, 83};
        unsigned char expected[] = {0, 0, 100, 150, 56, 0, 26, 150, 151};

        unsigned char *heap = new unsigned char[9];
        unsigned char *heap1 = new unsigned char[9];
        for (int i = 0; i < 9; i++) {
            heap[i] = values[i];
            heap1[i] = values1[i];
        }

        Image image(3, 3, heap);
        Image image1(3, 3, heap1);

        Image out = image - image1;
        Image::iterator iterator = out.begin(), end = out.end();
        int i = 0;
        while (iterator != end) {
            REQUIRE((int) *iterator == (int) expected[i]);
            *iterator++;
            i++;
        }
    }

    SECTION("invert") {
        unsigned char values[] = {155, 49, 200, 225, 84, 59, 100, 232, 255};
        unsigned char expected[] = {100, 206, 55, 30, 171, 196, 155, 23, 0};
        unsigned char *heap = new unsigned char[9];
        for (int i = 0; i < 9; i++) {
            heap[i] = values[i];
        }

        Image image(3, 3, heap);

        Image out = !image;
        Image::iterator iterator = out.begin(), end = out.end();
        int i = 0;
        while (iterator != end) {
            REQUIRE((int) *iterator == (int) expected[i]);
            *iterator++;
            i++;
        }
    }


    SECTION("mask") {
        unsigned char values[] = {155, 49, 200, 225, 84, 59, 100, 232, 234};
        unsigned char values1[] = {0, 255, 255, 0, 0, 255, 0, 0, 255};
        unsigned char expected[] = {0, 49, 200, 0, 0, 59, 0, 0, 234};

        unsigned char *heap = new unsigned char[9];
        unsigned char *heap1 = new unsigned char[9];
        for (int i = 0; i < 9; i++) {
            heap[i] = values[i];
            heap1[i] = values1[i];
        }

        Image image(3, 3, heap);
        Image image1(3, 3, heap1);

        Image out = image / image1;
        Image::iterator iterator = out.begin(), end = out.end();
        int i = 0;
        while (iterator != end) {
            REQUIRE((int) *iterator == (int) expected[i]);
            *iterator++;
            i++;
        }
    }

    SECTION("threshold") {
        unsigned char values[] = {155, 49, 200, 225, 84, 59, 100, 232, 255};
        unsigned char expected[] = {255, 0, 255, 255, 0, 0, 0, 255, 255};
        unsigned char *heap = new unsigned char[9];
        for (int i = 0; i < 9; i++) {
            heap[i] = values[i];
        }

        Image image(3, 3, heap);
        Image out = (image * 100);
        Image::iterator iterator = out.begin(), end = out.end();
        int i = 0;
        while (iterator != end) {
            REQUIRE((int) *iterator == (int) expected[i]);
            *iterator++;
            i++;
        }
    }

    SECTION("filter") {
        float matrix_values[] = {0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625};
        int N = 3, j = 0;
        Matrix m = Matrix();
        int start = (N - (2 * N)) / 2, end = N / 2;
        for (int row = start; row <= end; row++) {
            for (int col = start; col <= end; col++) {
                Node n;
                n.value = matrix_values[j];
                n.x = col;
                n.y = row;
                m.data.push_back(n);
                j++;
            }
        }

        unsigned char values[] = {155, 49, 200, 225, 84, 59, 100, 232, 255};
        unsigned char expected[] = {78, 84, 68, 116, 136, 99, 87, 130, 105};
        unsigned char *heap = new unsigned char[9];
        for (int i = 0; i < 9; i++) {
            heap[i] = values[i];
        }

        Image image(3, 3, heap);
        Image out = (image % m);
        Image::iterator iterator = out.begin(), end1 = out.end();
        int i = 0;
        while (iterator != end1) {
            REQUIRE((int) *iterator == (int) expected[i]);
            *iterator++;
            i++;
        }
    }

}