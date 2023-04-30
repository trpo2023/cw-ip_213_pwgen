APP_NAME = app
TEST_NAME = test
LIB_NAME = libapp

CC = g++

CFLAGS = -Wall -Wextra -Werror
CFLAGS_TEST = -Isrc -MMD -Ithirdparty
CPPFLAGS = -I src -MP -MMD

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test


APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)
TEST_OBJ_PATH = $(OBJ_DIR)/$(TEST_DIR)

SRC_EXT = cpp
APP_RUN = $(BIN_DIR)/./$(APP_NAME)
TEST_CHECK = $(BIN_DIR)/./$(TEST_NAME)

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d) 

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $(CFLAGS_TEST) $< -o $@

.PHONY: test
test: $(TEST_PATH)

$(TEST_PATH): $(TEST_OBJ_PATH)/main.o $(TEST_OBJ_PATH)/test.o $(LIB_PATH)
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $@ $^ -lm
	
$(OBJ)/$(TEST_DIR)/%.o: $(TEST_DIR)/main.cpp $(TEST_DIR)/test.cpp $(LIB_OBJECTS)
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -c -o $@ $< -lm

.PHONY: clean
clean:
	rm -f $(APP_PATH) $(TEST_PATH) $(LIB_PATH) 
	rm -rf $(DEPS) $(APP_OBJECTS) $(LIB_OBJECTS)
	rm -rf $(TEST_OBJ_PATH)/*.*
	
.PHONY: run
run: $(APP_RUN)
	$(APP_RUN) $(ARGS)

.PHONY: rtest
rtest: $(TEST_CHECK)
	$(TEST_CHECK) 

$(eval ARGS := $(filter-out $@,$(MAKECMDGOALS)))

%:
    @: