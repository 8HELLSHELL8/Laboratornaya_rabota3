//#include <iostream>
//#include <iomanip>
//#include <cmath>
//
//// Функция, определяющая заданную функцию
//double myFunction(double x) {
//    if (-2.0 < x && x < 2.0) {
//
//        return 2 * cos(2 * x);
//        
//
//
//    } else{
//
//        return (0.5 * abs(x)) - 1.5;
//
//
//
//    }
//}
//
//int main() {
//    
//    double startPoint, endPoint, step;
//    std::cout << "Input x coordinate for starting point ";
//    std::cin >> startPoint;
//    std::cout << "Input x coordinate for ending point ";
//    std::cin >> endPoint;
//    std::cout << "Input step value ";
//    std::cin >> step;
//
//    std::cout << std::setw(10) << "X" << std::setw(15) << "Y" << std::endl;
//    std::cout << std::setw(33) << std::setfill('-') << "" << std::setfill(' ') << std::endl;
//
//    double epsilon = 1e-9; // Погрешность для работы с числами с плавающей точкой
//    for (double i = startPoint; i < endPoint + epsilon; i += step) {
//        std::cout << std::setw(10) << std::fixed << std::setprecision(2) << i << "      |" << std::setw(15) << std::fixed << std::setprecision(2) << myFunction(i) << "|" << std::endl;
//    }
//
//
//    
//    return 0;
//}
