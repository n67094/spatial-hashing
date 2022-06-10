.PHONY: build test clean

#use make BUILD=release or BUILD=debug
BUILD := release

BUILD_DIR := ./build

PROJECT_NAME := sample
PROJECT_SRC := ./src
PROJECT_CFILES := $(foreach dir,$(PROJECT_SRC),$(shell find $(dir) -name '*.c'))
PROJECT_OBJS := $(PROJECT_CFILES:%=$(BUILD_DIR)/$(PROJECT_NAME)/%.o)

TEST_NAME := test_sample
TEST_SRC := ./src ./test
TEST_CFILES := $(foreach dir,$(TEST_SRC),$(shell find $(dir) -name '*.c'))
TEST_CFILES := $(filter-out ./src/main.c, $(TEST_CFILES))
TEST_OBJS := $(TEST_CFILES:%=$(BUILD_DIR)/$(TEST_NAME)/%.o)

FLAGS.common := -std=c99 -Wall -o3
FLAGS.debug := -ggdb3 -DNDEBUG

CFLAGS := ${FLAGS.${BUILD}} ${FLAGS.common}
LDFLAGS := -framework OpenGL -framework Cocoa

#BUILD
#=====
build: $(BUILD_DIR)/$(PROJECT_NAME)

$(BUILD_DIR)/$(PROJECT_NAME): $(PROJECT_OBJS)
	$(CC) $(PROJECT_OBJS) -o $(PROJECT_NAME) $(LDFLAGS)

$(BUILD_DIR)/$(PROJECT_NAME)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#TEST
#====
test: $(BUILD_DIR)/$(TEST_NAME)

$(BUILD_DIR)/$(TEST_NAME): $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $(TEST_NAME) $(LDFLAGS)

$(BUILD_DIR)/$(TEST_NAME)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(PROJECT_NAME)
	rm -r $(TEST_NAME)
	rm -r $(BUILD_DIR)
