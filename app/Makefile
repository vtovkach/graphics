CXX := g++

INC_DIRS := $(shell find ../include -type d)
CXXFLAGS := -std=c++20 -Wall -Wextra $(addprefix -I,$(INC_DIRS))

ifeq ($(DEBUG),1)
	CXXFLAGS += -O0 -g
else
	CXXFLAGS += -O2
endif

BUILD_DIR := ../build/app
TARGET := ../bin/example

APP_SOURCES := $(shell find . -name "*.cpp")
APP_OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(APP_SOURCES))

SRC_OBJECTS := $(shell find ../build -type f -name "*.o" ! -path "../build/app/*")

all: $(TARGET)

$(TARGET): $(APP_OBJECTS) $(SRC_OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)

.PHONY: all clean