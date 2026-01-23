# Makefile at repo root

CC := cc
CFLAGS := -O2 -Wall -Wextra -std=c11

.PHONY: run
# Run like:
#   make run DAY=01 PART=1 IN=input
#   make run DAY=04 PART=2 IN=example
run:
	@cd $(DAY) && $(CC) $(CFLAGS) -o solution$(PART).out solution$(PART).c
	@cd $(DAY) && ./solution$(PART).out $(IN)

.PHONY: clean
clean:
	@find . -type f -name '*.out' -exec rm -f {} +
