#include <iostream>
#include "../Modules/CalculationUnit/calculation_unit.h"

int main(int argc, char *argv[]) {
  CalculationUnit CU;

  double test = 90;
  std::cout << "-------------------" << std::endl;
  std::cout << "Test Default (D): " << test << std::endl;

  test = CU.DegreesToRadians(test);
  std::cout << "Test (R):" << test << std::endl;

  test = CU.RadiansToDegrees(test);
  std::cout << "Test (D): " << test << std::endl;
  //------

  Vec2 vector;

  std::cout << "VECTOR X : " << vector.x << std::endl;
  std::cout << "VECTOR Y : " << vector.y << std::endl;

  double result = CU.ConvertCoordinates(-1, 1, 2000, 4000, 1);

  //BEARING OFFSET
  const int offset = 90;
  int bearing = 0;
  std::cout << "-------------------" << std::endl;
  int offset_bearing = offset + bearing;
  Vec2 pos_vec = CU.DegreesToVector(offset_bearing);

  int destination_bearing = 0 + offset;
  Vec2 destination_vec = CU.DegreesToVector(destination_bearing);
  std::cout << "CURRENT BEARING" << std::endl;
  std::cout << "X: " << pos_vec.x << std::endl;
  std::cout << "Y: " << pos_vec.y << std::endl;
  std::cout << "-------------------" << std::endl;
  std::cout << "DESTINATION BEARING" << std::endl;
  std::cout << "X: " << destination_vec.x << std::endl;
  std::cout << "Y: " << destination_vec.y << std::endl;
  std::cout << "-------------------" << std::endl;

  Vec2 diff_vec = pos_vec - destination_vec;
  std::cout << "DIFFERENCE" << std::endl;
  std::cout << "X: " << diff_vec.x << std::endl;
  std::cout << "Y: " << diff_vec.y << std::endl;

  return 0;
}
