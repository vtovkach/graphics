CXX := g++

INC_DIRS := $(shell find . ../include -type d)
CXXFLAGS := -std=c++20 -Wall -Wextra $(addprefix -I,$(INC_DIRS))

ifeq ($(DEBUG),1)
	CXXFLAGS += -O0 -g
else
	CXXFLAGS += -O2
endif

BUILD_DIR := ../build

SOURCES := $(shell find . -type f -name "*.cpp")
OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

all: $(OBJECTS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean