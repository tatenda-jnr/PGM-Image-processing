PGM Image processing 
--------------------

Program allows user to perform operations like masking, thresholding, inverting, adding, subtracting
and filtering PGM images 

usage :

    make
    ./imageops <option> OutputImageName
    
    <option>
        -a Image1 Image2 (add Image1 and Image2)
        -s Image1 Image2 (subtract Image2 from Image1)
        -i Image1    (invert Image1)
        -l Image1 Image2 (mask Image1 with Image2)
        -t Image1 f  (threshold Image1 with integer value f)
        
Matrix filtering
----------------
overloaded the % operator : to implement matrix filtering

usage : 

    ./imageops -g <image_name> <file_with_filter_data> OutputImageName
 
   

Unit tests 
----------

unit tests were done using the catch library

    make test
    ./test <test_case> -sc \<section>

    OR

    ./test -s
    to run all tests at once


check unit_tests.cpp for the test cases and their sections

Image.cpp 
---------
   - contains overloaded operators for image manipulation

unit_tests.cpp
--------------
   - contains test cases to test overloaded operators, image iterator
     as well as move and copy operations



