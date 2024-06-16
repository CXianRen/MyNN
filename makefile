BUILD_DIR = build
ROOT_PATH := code

CORE_DIR := src
CORE_INC := -I $(ROOT_PATH) 

TEST_DIR := test
TEST_INC := $(INC) -I $(ROOT_PATH)/test/ 
# $(info CORE_INC: $(CORE_INC))
# $(info TEST_INC: $(TEST_INC))


EXAMPLES_DIR := example
EXAMPLES_INC := $(INC) -I $(ROOT_PATH)/example/

CC_OPT_LEVEL := -O3

CC = g++

openMP := -fopenmp

CFLAGS = -std=c++11 -Wall $(CC_OPT_LEVEL) $(openMP)


# $(info pwd: $(PWD))

CORE_CPP_FILES := $(wildcard $(ROOT_PATH)/$(CORE_DIR)/*.cpp)
CORE_OBJ_FILES := $(patsubst $(ROOT_PATH)/$(CORE_DIR)/%.cpp, $(BUILD_DIR)/$(CORE_DIR)/%.o, $(CORE_CPP_FILES))

TEST_CPP_FILES := $(wildcard $(ROOT_PATH)/$(TEST_DIR)/*.cpp)
TEST_PROGAMS := $(patsubst $(ROOT_PATH)/$(TEST_DIR)/%.cpp, $(BUILD_DIR)/$(TEST_DIR)/%, $(TEST_CPP_FILES))

EXAMPLE_CPP_FILES := $(wildcard $(ROOT_PATH)/$(EXAMPLES_DIR)/*.cpp)
EXAMPLES_PROGAMS := $(patsubst $(ROOT_PATH)/$(EXAMPLES_DIR)/%.cpp, $(BUILD_DIR)/$(EXAMPLES_DIR)/%, $(EXAMPLE_CPP_FILES))


# $(info CORE_CPP_FILES: $(CORE_CPP_FILES))
# $(info CORE_OBJ_FILES: $(CORE_OBJ_FILES))
# $(info TEST_CPP_FILES: $(TEST_CPP_FILES))
# $(info TEST_PROGAMS: $(TEST_PROGAMS))
# $(info EXAMPLES_PROGAMS: $(EXAMPLES_PROGAMS))

all: clean build run_test

build:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/$(CORE_DIR)
	mkdir -p $(BUILD_DIR)/$(TEST_DIR)
	mkdir -p $(BUILD_DIR)/$(EXAMPLES_DIR)

core: $(CORE_OBJ_FILES)

$(BUILD_DIR)/$(CORE_DIR)/%.o: $(ROOT_PATH)/$(CORE_DIR)/%.cpp
	$(CC) $(CFLAGS) $(CORE_INC) -c $< -o $@

test: $(TEST_PROGAMS)

$(BUILD_DIR)/$(TEST_DIR)/%: $(ROOT_PATH)/$(TEST_DIR)/%.cpp $(CORE_OBJ_FILES)
	$(CC) $(CFLAGS) -O0 -g  $(TEST_INC) $(CORE_INC) $< $(CORE_OBJ_FILES) -o $@

run_test: $(TEST_PROGAMS)
	$(info TEST_PROGAMS: $(TEST_PROGAMS))
	echo "Running tests..."
	@for test in $(TEST_PROGAMS); do \
		$$test; \
	done

example: $(EXAMPLES_PROGAMS)

$(BUILD_DIR)/$(EXAMPLES_DIR)/%: $(ROOT_PATH)/$(EXAMPLES_DIR)/%.cpp $(CORE_OBJ_FILES)
	$(CC) $(CFLAGS) $(EXAMPLES_INC) $(CORE_INC) $< $(CORE_OBJ_FILES) -o $@


fc_3layer: $(BUILD_DIR)/$(EXAMPLES_DIR)/fc_3layer
	 ./$(BUILD_DIR)/$(EXAMPLES_DIR)/fc_3layer

example:
	$(info "fc_3layer")

clean:
	rm -rf $(BUILD_DIR)