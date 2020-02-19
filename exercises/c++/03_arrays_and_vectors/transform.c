#include <sstream>
#include <iostream>
#include <string>


int main(int argc, char* argv[])
{
  std::size_t rows;
  std::string buffer{};         //I put the input into a string
  buffer.append(argv[1]);
  buffer += " ";
  buffer.append(argv[2]);
  std::istringstream is{buffer};
  is >> rows;

  std::size_t cols;
  //std::istringstream is1{argv[2]};
  //is1 >> cols;
  is >> cols;

  std::cout << "Number of rows: " << rows << std::endl;
  std::cout << "Number of columns :" << cols << std::endl;

  return 0;
}
