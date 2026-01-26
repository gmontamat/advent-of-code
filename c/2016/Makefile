CC := cc
CFLAGS := -O2 -Wall -Wextra -pedantic -std=c11

.PHONY: compile run clean

# Build only
compile:
	@cd $(DAY) && $(CC) $(CFLAGS) -o solution$(PART).out solution$(PART).c

# Build + run
run: compile
	@cd $(DAY) && ./solution$(PART).out $(IN)

clean:
	@find . -type f -name '*.out' -exec rm -f {} +
