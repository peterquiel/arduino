#!/bin/zsh

ctags -R -f tags.cpp `find -L /home/pedda/local/arduino -name "*.cpp" -o -name "*.h"`
ctags -R -f tags.ino --langmap=c++:.ino `find . -name "*.ino"`

ctags -R -f tags2.cpp `find . -name "*.cpp" -o -name "*.h"`
ctags -R -f tags3.cpp `find -L /home/pedda/Arduino/libraries -name "*.cpp" -o -name "*.h"`
cat tags.cpp tags.ino tags2.cpp tags3.cpp > .tags
sort .tags -o .tags
rm -f tags*

