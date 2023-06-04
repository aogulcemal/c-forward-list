CC := clang

LIBS = -lm

CFLAGS  = -std=c11
CFLAGS += -O0
CFLAGS += -ggdb3
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -Wshadow
CFLAGS += -gdwarf-4
CFLAGS += -pedantic
CFLAGS += -Wmissing-declarations
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-unused-parameter
CFLAGS += -Qunused-arguments
CFLAGS += -DUNITY_SUPPORT_64 -DUNITY_OUTPUT_COLOR

ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer

.PHONY: test
test: tests.out
	@./tests.out

.PHONY: memcheck
memcheck: ./*.c ./*.h
	@echo Compiling $@
	@$(CC) $(ASANFLAGS) $(CFLAGS) test-framework/unity.c ./*.c -o memcheck.out $(LIBS)
	@./memcheck.out
	@echo "Memory check passed"

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM

tests.out: ./*.c ./*.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) test-framework/unity.c ./*.c -o tests.out $(LIBS)