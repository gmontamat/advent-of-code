CC := cc
CFLAGS := -O2 -Wall -Wextra -pedantic -std=c11

.PHONY: compile run clean

# Homebrew OpenSSL 3 (only used for DAY=04)
OPENSSL_PREFIX := $(shell brew --prefix openssl@3 2>/dev/null)
OPENSSL_CFLAGS := -I"$(OPENSSL_PREFIX)/include" -Wno-deprecated-declarations
OPENSSL_LDFLAGS := -L"$(OPENSSL_PREFIX)/lib" -lcrypto

ifeq ($(DAY),04)
  EXTRA_CFLAGS := $(OPENSSL_CFLAGS)
  EXTRA_LDFLAGS := $(OPENSSL_LDFLAGS)
else
  EXTRA_CFLAGS :=
  EXTRA_LDFLAGS :=
endif

# Build only
compile:
	@cd $(DAY) && $(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o solution$(PART).out solution$(PART).c $(EXTRA_LDFLAGS)

# Build + run
run: compile
	@cd $(DAY) && ./solution$(PART).out $(IN)

clean:
	@find . -type f -name '*.out' -exec rm -f {} +
