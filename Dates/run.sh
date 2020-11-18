source ./emsdk_env.sh
emcc -std=c++11 /D/projects/webasm/Dates/Dates/Dates/YearMonth.cpp -s WASM=1 -o /D/projects/webasm/Dates/Dates/Dates/YearMonth.html