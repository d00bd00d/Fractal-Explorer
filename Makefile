CXX := g++ 
LINKERS := -lGLEW -lGL -lglfw
FLAGS := -Wall -g -fsanitize=address,undefined

Fractal: main.o WindowManager.o GLFWutils.o WindowManager.h Coefficients.o
	$(CXX) $(FLAGS) -o Fractal Coefficients.o GLFWutils.o WindowManager.o main.o $(LINKERS)

main.o: main.cpp
	$(CXX) $(FLAGS) -c main.cpp $(LINKERS) 

WindowManager.o: WindowManager.cpp WindowManager.h GLFWutils.h Coefficients.h
	$(CXX) $(FLAGS) -c WindowManager.cpp $(LINKERS)

GLFWutils.o: GLFWutils.cpp GLFWutils.h
	$(CXX) $(FLAGS) -c GLFWutils.cpp $(LINKERS)

Coefficients.o: Coefficients.cpp Coefficients.h 
	$(CXX) $(FLAGS) -c Coefficients.cpp $(LINKERS) 
