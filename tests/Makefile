#####################################
## Configuration

SRCDIR    = units
BUILDDIR  = dist
SRCFILES  = $(wildcard $(SRCDIR)/*.c)
TESTNAMES = $(patsubst %.c,%,$(SRCFILES))
TESTBINS  = $(addprefix $(BUILDDIR)/,$(TESTNAMES))

CC = clang
DBG = gdb
CCFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Wshadow -Wwrite-strings \
	-Wnested-externs -Wredundant-decls -Wstrict-prototypes -Wno-unused-parameter \
	-Wold-style-definition -Wmissing-include-dirs

INCLUDES = -I$(SRCDIR) -Iinclude -I../src
LIBRARIES = -lm 

DEBUGFLAGS = -g -O0
RELEASEFLAGS = -O3


#####################################
## Building

all: $(TESTNAMES)
	@chmod +x $(TESTBINS)

%: %.c detect-build-environment $(SRCFILES)
	@-compiledb -n make
	@mkdir -p $(BUILDDIR)/$(SRCDIR)
	$(CC) $< -o $(BUILDDIR)/$@ $(INCLUDES) $(LIBRARIES) $(CCFLAGS)


#####################################
## Utils

.PHONY: run debug clean check-build-type

run: clean $(TESTNAMES)
	@echo -----------------------------------------
	@for test in $(TESTBINS); do \
		./$${test} || exit $$?; \
	done

clean:
	@rm -rf $(BUILDDIR) *.json .cache/


#####################################
## Safeguards

check-build-type:
ifndef build
	build=debug
endif


apply-build-flags: check-build-type
ifeq ($(build), release)
	$(eval CCFLAGS += $(RELEASEFLAGS))
else
	$(eval CCFLAGS += $(DEBUGFLAGS))
endif


detect-build-environment: apply-build-flags
ifeq ($(OS),Windows_NT)
    CCFLAGS += -D PLATFORM_WIN32
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D PLATFORM_LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D PLATFORM_OSX
    endif
endif

