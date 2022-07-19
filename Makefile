CC                := gcc

ROOTDIR           := $(shell pwd)
BUILDDIR          := $(ROOTDIR)/build
SRCDIR            := $(ROOTDIR)/src
INCDIR            := $(ROOTDIR)/src/include
OBJDIR            := $(BUILDDIR)/objs
LIBDIR            := $(BUILDDIR)/lib
D_TARGET          := $(LIBDIR)/libpmsort.so
CMOCKA_SRCDIR     := $(ROOTDIR)/cmocka
CMOCKA_TARGET     := $(LIBDIR)/libcmocka.so
T_SRCDIR          := $(ROOTDIR)/unit-tests
TESTDIR           := $(BUILDDIR)/tests

SOURCES           := $(shell echo $(SRCDIR)/*.c)
T_SOURCES         := $(shell echo $(T_SRCDIR)/*.c)
CMOCKA_SOURCES    := $(shell find $(CMOCKA_SRCDIR) -type f -name *.c)

OBJECTS           := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.c=.o))
TESTS             := $(patsubst $(T_SRCDIR)/%,$(TESTDIR)/%,$(T_SOURCES:.c=))

INC               := -I$(INCDIR) -I/usr/local/include
CMOCKA_INC        := $(INC) -I$(CMOCKA_SRCDIR)/include
LIBS              := $(D_TARGET) $(CMOCKA_TARGET)
libs              := $(patsubst $(LIBDIR)/lib%,-l%,$(LIBS:%.so=%))

CFLAGS            := -fPIC -Werror -Wall -O3 -g
LDFLAGS           := -shared

.PHONY: all clean check-and-reinit-submodules

all: check-and-reinit-submodules $(CMOCKA_TARGET) $(D_TARGET) $(TESTS)

#Compile
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(D_TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	@mkdir -p $(TESTDIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

check-and-reinit-submodules:
	@if git submodule status | egrep -q '^[-]|^[+]' ; then \
		echo "INFO: Need to reinitialize git submodules"; \
		git submodule update --init; \
	fi

$(CMOCKA_TARGET): $(CMOCKA_SOURCES)
	@mkdir -p $(BUILDDIR)/cmocka
	@mkdir -p $(dir $@)
	@cd $(BUILDDIR)/cmocka; cmake $(CMOCKA_SRCDIR); make; cp $(BUILDDIR)/cmocka/src/libcmocka.so* $(LIBDIR)/

$(TESTDIR)/%: $(T_SRCDIR)/%.c $(LIBS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CMOCKA_INC) -L$(LIBDIR) -o $@ $< $(libs)

clean:
	rm -rf $(BUILDDIR)

print-%  : ; @echo $* = $($*)
