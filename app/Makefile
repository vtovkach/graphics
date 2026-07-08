CXX := g++

INC_DIRS := $(shell find ../include -type d)
CXXFLAGS := -std=c++20 -Wall -Wextra $(addprefix -I,$(INC_DIRS))

ifeq ($(DEBUG),1)
	CXXFLAGS += -O0 -g
else
	CXXFLAGS += -O2
endif

BUILD_DIR := ../build/app
TARGET_DIR := ../bin/
TARGET := $(TARGET_DIR)example

SDL_CFLAGS := $(shell pkg-config --cflags sdl3)
SDL_LIBS := $(shell pkg-config --libs sdl3)

APP_SOURCES := $(shell find . -name "*.cpp")
APP_OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(APP_SOURCES))

SRC_OBJECTS := $(shell find ../build -type f -name "*.o" ! -path "../build/app/*")

all: $(TARGET)

$(TARGET): $(APP_OBJECTS) $(SRC_OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $^ -o $@ $(SDL_LIBS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(TARGET_DIR)

.PHONY: all clean