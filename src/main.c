#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	char* data;
	size_t length;
	size_t capacity;
} String;

bool string_init(String* s) {
	s->capacity = 1;
	s->length = 0;
	s->data = malloc(s->capacity);
	if (!s->data) return false;
	s->data[0] = '\0';
	return true;
}

void string_free(String* s) {
	free(s->data);
	s->data = NULL;
	s->length = 0;
	s->capacity = 0;
}

bool string_push_char(String* s, char c) {
	if (s->length + 1 >= s->capacity) {
		size_t new_capacity = s->capacity * 2;
		char* new_data = realloc(s->data, new_capacity);
		if (!new_data) return false;
		s->data = new_data;
		s->capacity = new_capacity;
	}

	s->data[s->length] = c;
	s->length++;
	s->data[s->length] = '\0';
	return true;
}

void string_reverse(String* s) {
	for (size_t i = 0; i < s->length / 2; ++i) {
		char temp = s->data[i];
		s->data[i] = s->data[s->length - 1 - i];
		s->data[s->length - 1 - i] = temp;
	}
}

int main() {
	long long n = 0;
	String s;

	string_init(&s);

	printf("Enter number: ");
	scanf("%lld", &n);

	if (n < 0) {
		printf("INVALID VALUE negotive: %lld", n);
		return 1;
	} else if (n == 0) {
		string_push_char(&s, '0');
	} else {
		long long b = n;
		while (b > 0) {
			string_push_char(&s, b % 10 + '0');
			b /= 10;
		}
	}

	printf("Number: %lld", n);

	string_reverse(&s);

	printf("\nString: \"%s\"", s.data);

	string_free(&s);
}
