BUILD_DIR = build
ROOT_PATH := code

CORE_DIR := src
CORE_INC := -I $(ROOT_PATH) 

TEST_DIR := test
TEST_INC := $(INC) -I $(ROOT_PATH)/test/ 
$(info CORE_INC: $(CORE_INC))
$(info TEST_INC: $(TEST_INC))

CC_OPT_LEVEL := -O3

CC = g++
CFLAGS = -std=c++11 -Wall $(CC_OPT_LEVEL)

$(info pwd: $(PWD))

CORE_CPP_FILES := $(wildcard $(ROOT_PATH)/$(CORE_DIR)/*.cpp)
CORE_OBJ_FILES := $(patsubst $(ROOT_PATH)/$(CORE_DIR)/%.cpp, $(BUILD_DIR)/$(CORE_DIR)/%.o, $(CORE_CPP_FILES))

TEST_CPP_FILES := $(wildcard $(ROOT_PATH)/$(TEST_DIR)/*.cpp)
TEST_PROGAMS := $(patsubst $(ROOT_PATH)/$(TEST_DIR)/%.cpp, $(BUILD_DIR)/$(TEST_DIR)/%, $(TEST_CPP_FILES))

# $(info CORE_CPP_FILES: $(CORE_CPP_FILES))
# $(info CORE_OBJ_FILES: $(CORE_OBJ_FILES))
# $(info TEST_CPP_FILES: $(TEST_CPP_FILES))

all: build

build:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/$(CORE_DIR)
	mkdir -p $(BUILD_DIR)/$(TEST_DIR)

core: $(CORE_OBJ_FILES)

$(CORE_OBJ_FILES): $(CORE_CPP_FILES)
	$(CC) $(CFALGS) $(CORE_INC) -c $< -o $@

test: $(TEST_PROGAMS)

$(TEST_PROGAMS): $(TEST_CPP_FILES) $(CORE_OBJ_FILES)	
	$(CC) $(CFLAGS) $(TEST_INC) $(CORE_INC) $< $(CORE_OBJ_FILES) -o $@

run_test: $(TEST_PROGAMS)
	$(info TEST_PROGAMS: $(TEST_PROGAMS))
	@for test in $(TEST_PROGAMS); do \
		echo "Running $$test"; \
		$$test; \
	done

clean:
	rm -rf $(BUILD_DIR)