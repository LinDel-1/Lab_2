//
// Functionality to write MyMatrix to file and read it from file
//

#pragma once
#include <fstream>
#include "MyMatrix.h"

template <typename T>
struct TextMode{};

template<typename T>
struct BinaryMode{};

template<>
struct TextMode<int>{
    static void write(const char* filename, const MyMatrix<int>& object){
        std::ofstream fout(filename);
        fout << "type: int" << std::endl;
        for (size_t i = 0; i < object.m_rows; ++i){
            fout << "|";
            for (size_t j = 0; j < object.m_cols; ++j){

            }
        }
        fout.close();
    }
    static void read(const char* filename){
        ;
    }
};

template<>
struct TextMode<double>{};