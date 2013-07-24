#include "num2words-bg.h"
#include "string.h"

static const char* const ONES[] = {
  "часът",
  "один",
  "два",
  "три",
  "четыре",
  "пять",
  "шесть",
  "семь",
  "восем",
  "девять"
};

static const char* const TEENS[] ={
  "",
  "одинадцать",
  "двенадцать",
  "тринадесет",
  "четиринадесет",
  "петнадесет",
  "шестнадесет",
  "седемнадесет",
  "осемнадесет",
  "деветнадесет"
};

static const char* const TENS[] = {
  "",
  "десет",
  "двадесет",
  "тридесет",
  "четиридесет",
  "петдесет",
  "шестдесет",
  "седемдесет",
  "осемдесет",
  "десетдесет"
};

static size_t append_number(char* words, int num) {
  int tens_val = num / 10 % 10;
  int ones_val = num % 10;

  size_t len = 0;

  if (tens_val > 0) {
    if (tens_val == 1 && num != 10) {
      strcat(words, TEENS[ones_val]);
      return strlen(TEENS[ones_val]);
    }
    strcat(words, TENS[tens_val]);
    len += strlen(TENS[tens_val]);
    if (ones_val > 0) {
      strcat(words, " ");
      len += 1;
    }
  }

  if (ones_val > 0 || num == 0) {
    strcat(words, ONES[ones_val]);
    len += strlen(ONES[ones_val]);
  }
  return len;
}

static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}


void time_to_words(int hours, int minutes, char* words, size_t length) {

  size_t remaining = length;
  memset(words, 0, length);

  if (hours == 0 || hours == 12) {
    remaining -= append_string(words, remaining, TEENS[2]);
  } else {
    remaining -= append_number(words, hours % 12);
  }

  remaining -= append_string(words, remaining, " ");
  remaining -= append_number(words, minutes);
  remaining -= append_string(words, remaining, " ");
}

void time_to_3words(int hours, int minutes, char *line1, char *line2, char *line3, size_t length)
{
	char value[length];
	time_to_words(hours, minutes, value, length);
	
	memset(line1, 0, length);
	memset(line2, 0, length);
	memset(line3, 0, length);
	
	char *start = value;
	char *pch = strstr (start, " ");
	while (pch != NULL) {
		if (line1[0] == 0) {
			memcpy(line1, start, pch-start);
		} else if (line2[0] == 0) {
			memcpy(line2, start, pch-start);
		} else if (line3[0] == 0) {
			memcpy(line3, start, pch-start);
		}
		start += pch-start+1;
		pch = strstr(start, " ");
	}
	
	if (strcmp(line1, "две") == 0) {
		memcpy(line1, "два", 6);
	}
	
	if (memcmp(line2, "часът", 5) != 0) {
		if (strcmp(line2, "един") == 0) {
			memcpy(line2, "една", 8);
		}
	
		memmove(line2 + 3, line2, strlen(line2));
		memcpy(line2, "и ", 3);
	}
	
	if (strlen(line3) > 0) {
		if (strcmp(line3, "един") == 0) {
			memcpy(line3, "една", 8);
		}
	
		memmove(line3 + 3, line3, strlen(line3));
		memcpy(line3, "и ", 3);
	}
}
