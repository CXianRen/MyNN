BUILD_DIR = build
SRC_DIR := src
INC_DIR := inc

CC = g++
CFLAGS = -std=c++11 -Wall -I$(INC_DIR) -O0

$(info pwd: $(PWD))

SRCS = $(wildcard  $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

EXEC = $(BUILD_DIR)/app

all: build $(EXEC)

build:
	mkdir -p $(BUILD_DIR)

$(EXEC): $(OBJS)	
	$(CC) $(CFLAGS) $(OBJS) main.cpp -o $(EXEC)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: clean all
	./$(EXEC)


TEST_DIR = test
TEST_PROGRAMS = test_dot test_activation test_mnist_load
TEST_SOURCES = $(addprefix $(TEST_DIR)/, $(TEST_PROGRAMS:=.cpp))
TEST_BINARIES = $(addprefix $(BUILD_DIR)/, $(TEST_PROGRAMS))

build_test: build $(TEST_PROGRAMS)

$(TEST_PROGRAMS): $(TEST_BINARIES)

$(BUILD_DIR)/%: $(TEST_DIR)/%.cpp $(OBJS)	
	$(CC) $(CFLAGS) $(OBJS)	 -o $@ $<

run_tests: $(TEST_BINARIES)
	@for test in $(TEST_BINARIES); do \
		echo "Running $$test"; \
		$$test; \
	done

clean:
	rm -rf $(BUILD_DIR)