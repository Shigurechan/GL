PRG         :=GL
SRC_DIR     :=source
OBJ_DIR     :=obj
DEP_DIR     :=obj
DEP        	:=$(wildcard $(DEP_DIR)/*.d)
SRC         :=$(wildcard $(SRC_DIR)/*.cpp)
OBJ         :=$(addprefix $(OBJ_DIR)/,$(patsubst %.cpp,%.o,$(notdir $(SRC))))
LDFLAGS 	:=`pkg-config --libs=opengl glew glfw3 freetype2`



$(PRG): $(OBJ)
    #$(CXX)  $^ -l ncurses -o $@
	$(CXX) $^ -o $@ -L/usr/local/lib -lGLU -lGL -lglfw3 -pthread -lGL -lGLEW  -lfreetype -ldl -lX11
 



$(OBJ_DIR)/%.o: source/%.cpp
#$(CXX) -std=c++2a -I/usr/local/include/freetype2 -I/usr/include/libpng16 -I/usr/local/include -pthread -c -MMD -MP $< -o $@
	$(CXX) -std=c++2a -I/usr/local/include/freetype2 -I/usr/include/libpng16 -I/usr/local/include -pthread -c -MMD -MP $< -o $@
	-include $(DEP)
	

clean:
	rm -f ./$(OBJ_DIR)/*.o *.out ./$(OBJ_DIR)/*.d *.a $(PRG)
