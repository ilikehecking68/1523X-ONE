# Detect operating system and set processor count
ifeq ($(OS),Windows_NT)
    NPROC := $(NUMBER_OF_PROCESSORS)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        NPROC := $(shell nproc)
    else ifeq ($(UNAME_S),Darwin)
        NPROC := $(shell sysctl -n hw.ncpu)
    else ifneq (,$(findstring BSD,$(UNAME_S)))
        NPROC := $(shell sysctl -n hw.ncpu)
    else
        NPROC := 1
    endif
endif

# Enable parallel compilation
MAKEFLAGS += -j$(NPROC)

all: build

build:
	@$(MAKE) -f Makefile2

clean:
	@$(MAKE) -f Makefile2 clean

# This Makefile is a wrapper for Makefile2. It provides a simple interface to build and clean the project.
# It includes the common.mk file for shared settings and configurations.
# The all target builds the project by calling Makefile2, while the clean target cleans the project.