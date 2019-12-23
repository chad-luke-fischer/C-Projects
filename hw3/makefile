BIN_DIR = bin
CXX = g++
CPPFLAGS = -Wall -g -std=c++11

all: parser


$(BIN_DIR)/circular_list_int.o: ./circular_list_int.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/circular_list_int.o

$(BIN_DIR)/stackint.o: ./stackint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c $< -o $(BIN_DIR)/stackint.o

stacktest: ./stackint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c $< -o $@

parser: parser.cpp
	g++ -g -Wall -std=c++11 circular_list_int.cpp stackint.cpp parser.cpp -o parser



$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY:
clean:
	rm -rf $(BIN_DIR)