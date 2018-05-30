
*Goal now on*
1. write make file for compile
2. improve this code for finding only big size of faces(sometimes it thinks sth small face wrongly)


I tried->
$ gcc -std=c++11 facial_detection.cpp -o facial_detection -L/usr/lib -lstdc++ -lopencv_core -lopencv_highgui -lopencv_videoio

error->
/usr/bin/ld: /tmp/ccPQuczT.o: undefined reference to symbol 'lrint@@GLIBC_2.17' 
//lib/aarch64-linux-gnu/libm.so.6: error adding symbols: DSO missing from command line
collect2: error: ld returned 1 exit status

solved->
solution1) liking same things twice
for this case : gcc -std=c++11 facial_detection.cpp -o facial_detection -L/usr/lib -lstdc++ -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lopencv_objdetect -lm -lstdc++ -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lopencv_objdetect -lm

solution2) use liking option
for this case : gcc -std=c++11 facial_detection.cpp -o facial_detection -Xlinker --start-group -L/usr/lib -lstdc++ -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lopencv_objdetect -lm -Xlinker --end-group
=> It didn't work for me.

