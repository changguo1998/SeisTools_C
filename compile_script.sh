# compile
gcc -c -g D:\Projects\SeisTools_C\include\basic\array_template.c -o D:\Projects\SeisTools_C\include\basic\array_template.a
gcc -c -g D:\Projects\SeisTools_C\include\basic\datetime.c -o D:\Projects\SeisTools_C\include\basic\datetime.a
gcc -c -g D:\Projects\SeisTools_C\include\basic\dict.c -o D:\Projects\SeisTools_C\include\basic\dict.a
gcc -c -g D:\Projects\SeisTools_C\include\math_adapter\array_math.c -o D:\Projects\SeisTools_C\include\math_adapter\array_math.a
gcc -c -g D:\Projects\SeisTools_C\include\math_adapter\dsp.c -o D:\Projects\SeisTools_C\include\math_adapter\dsp.a
gcc -c -g D:\Projects\SeisTools_C\include\seismic\raytrace.c -o D:\Projects\SeisTools_C\include\seismic\raytrace.a
gcc -c -g D:\Projects\SeisTools_C\include\seismic\trace.c -o D:\Projects\SeisTools_C\include\seismic\trace.a
gcc -c -g D:\Projects\SeisTools_C\test\test_array.c -o D:\Projects\SeisTools_C\test\test_array.o
gcc -c -g D:\Projects\SeisTools_C\test\test_datetime.c -o D:\Projects\SeisTools_C\test\test_datetime.o
# link
gcc -g \
    D:\Projects\SeisTools_C\include\basic\array_template.a \
    D:\Projects\SeisTools_C\include\math_adapter\dsp.a \
    D:\Projects\SeisTools_C\include\basic\basic_types.o \
 -o D:\Projects\SeisTools_C\test\test_array
gcc -g \
    D:\Projects\SeisTools_C\include\basic\datetime.a \
    D:\Projects\SeisTools_C\include\basic\basic_types.o \
 -o D:\Projects\SeisTools_C\test\test_datetime
