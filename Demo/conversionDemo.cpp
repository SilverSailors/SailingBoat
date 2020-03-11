#include <iostream>
#include "../Modules/Calculation_Unit/calculation_unit.hpp"

int main(int argc, char *argv[]) {
  Calculation_Unit CU;

  double test = 90;
  std::cout << "-------------------" << std::endl;
  std::cout << "Test Default (D): " << test << std::endl;

  test = CU.degrees_to_radians(test);
  std::cout << "Test (R):" << test << std::endl;

  test = CU.radians_to_degrees(test);
  std::cout << "Test (D): " << test << std::endl;
  //------

  VEC2 vector;

  std::cout << "VECTOR X : " << vector.x << std::endl;
  std::cout << "VECTOR Y : " << vector.y << std::endl;

  double result = CU.convert_coordinates(-1, 1, 2000, 4000, 1);

  //BEARING OFFSET
  const int offset = 90;
  int bearing = 0;
  std::cout << "-------------------" << std::endl;
  int offset_bearing = offset + bearing;
  VEC2 pos_vec = CU.degrees_to_vector(offset_bearing);

  int destination_bearing = 0 + offset;
  VEC2 destination_vec = CU.degrees_to_vector(destination_bearing);
  std::cout << "CURRENT BEARING" << std::endl;
  std::cout << "X: " << pos_vec.x << std::endl;
  std::cout << "Y: " << pos_vec.y << std::endl;
  std::cout << "-------------------" << std::endl;
  std::cout << "DESTINATION BEARING" << std::endl;
  std::cout << "X: " << destination_vec.x << std::endl;
  std::cout << "Y: " << destination_vec.y << std::endl;
  std::cout << "-------------------" << std::endl;

  VEC2 diff_vec = pos_vec - destination_vec;
  std::cout << "DIFFERENCE" << std::endl;
  std::cout << "X: " << diff_vec.x << std::endl;
  std::cout << "Y: " << diff_vec.y << std::endl;

  return 0;
}
