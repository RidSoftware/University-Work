# Options to pass to the C compiler
CFLAGS = -std=c99 -O2 -Wall -pedantic -g

# List of programs to build
TARGETS = trafficLights tut_led23 tut_led47

# Default rule, built if you just say "make"
all: $(TARGETS)

# Rules to build programs:

We could instead have a single pattern rule for both programs:
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Remove built programs and temporary files
clean:
	rm -f $(TARGETS) *~
