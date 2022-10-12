#include "graphics.h"

Matrix<double> move(double x, double y, double z) {
	return { {1      ,0      ,0      ,0      },
			 {0      ,1      ,0      ,0      },
			 {0      ,0      ,1      ,0      },
			 {x      ,y      ,z      ,1      } };
}


Matrix<double> projection(double z) {
	return  { {1      ,0      ,0      ,0      },
			  {0      ,1      ,0      ,0      },
			  {0      ,0      ,0      ,-1. / z},
			  {0      ,0      ,0      ,1      } };
}

Matrix<double> rotate_x(double angle) {
	double x = angle * M_PI / 180;
	return  { {1      ,0      ,0      ,0      },
			  {0      ,cos(x) ,sin(x) ,0      },
			  {0      ,-sin(x),cos(x) ,0      },
			  {0      ,0      ,0      ,1      } };
}


Matrix<double> rotate_y(double angle) {
	double y = angle * M_PI / 180;
	return  { {cos(y) ,0      ,-sin(y),0      },
			  {0      ,1      ,0      ,0      },
			  {sin(y) ,0      ,cos(y) ,0      },
			  {0      ,0      ,0      ,1      } };
}


Matrix<double> rotate_z(double angle) {
	double z = angle * M_PI / 180;
	return  { {cos(z) ,sin(z) ,0      ,0      },
			  {-sin(z),cos(z) ,0      ,0      },
			  {0      ,0      ,1      ,0      },
			  {0      ,0      ,0      ,1      } };
}

Matrix<double> identity(int size) {
	Matrix<double> answer(size, size);
	for (int i = 0; i < size; i++)
		answer[i][i] = 1;
	return answer;
}