if [ -e ".coverage_rc" ]
     then
     source .coverage_rc
     fi

     if [ -z ${EXCLUDES+x} ]
          then
          EXCLUDES=
               fi

               if [ -z ${FILENAME+x} ]
                    then
                    FILENAME=./tests/test_user_full
                             fi

rm -rvf build ; mkdir build ; cd build ; cmake -DCMAKE_BUILD_TYPE:STRING=Coverage .. ; make
                             make -j4 && \

                             "$FILENAME"   --log_level=all  && \
                             lcov -i -c -d . -o coverage.info && \
                             lcov -c -d . -o coverage.info && \
                             lcov -r coverage.info "/usr*" -o coverage.info && \
                             lcov -r coverage.info $EXCLUDES -o coverage.info && \
                             genhtml --legend  --no-branch-coverage --demangle-cpp -o html coverage.info
