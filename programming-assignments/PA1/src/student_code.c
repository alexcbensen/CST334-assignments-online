
#include "student_code.h"
#include <string.h>
#include <stdlib.h>

String String__init(char* input_c_str) {
  String new_str;

  // Get size of the input string since we use it a few times throughout
  size_t length_of_string = strlen(input_c_str);

  // Set metadata associated with the string
  new_str.length = length_of_string;
  new_str.capacity = length_of_string + 1;

  // Copy over the data itself
  new_str.data = malloc(new_str.capacity);
  strncpy(new_str.data, input_c_str, new_str.capacity);

  // Return the string
  return new_str;
}

void String__delete(String* str) {
  free(str->data);
}

size_t String__length(const String* str) {
  return str->length;
}
/**
 * Increases capacity of given String struct to give new_size, if appropriate, otherwise leaves it untouched.
 * @param str
 * @param new_size
 */
void String__reserve(String* str, size_t new_capacity) {
  if (new_capacity > str->capacity) {
    char* new_data = (char*)malloc(new_capacity);

    if (new_data) {
      strncpy(new_data, str->data, str->length);
      free(str->data);
      str->data = new_data;
      str->capacity = new_capacity;
    }
  }
}

void String__resize(String* str, size_t new_size, const char c) {
  if (new_size > str->length) {
    String__reserve(str, new_size + 1);
    memset(str->data + str->length, c, new_size - str->length);
    str->length = new_size;
  } else {
    str->length = new_size;
    str->data[str->length] = '\0';
  }
}

void String__clear(String* str) {
  str->length = 0;
  str->data[0] = '\0';
}

bool String__empty(String* str) {
  return str->length == 0;
}

char String__at(String* str, size_t index) {
    if (index < str->length) {
        return str->data[index];
    } else {
        return '\0';
    }
}

char String__back(String* str) {
  if (str->length > 0) {
    return str->data[str->length - 1];
  } else {
    return '\0';
  }
}

char String__front(String* str) {
  if (str->length > 0) {
    return str->data[0];
  } else {
    return '\0';
  }
}

void String__append(String* str, const String* str_to_add) {
  // todo
}

void String__push_back(String* str, const char char_to_add) {
  // todo
}

void String__pop_back(String* str) {
  String__resize(str, (str->length - 1), '\0');
}

void String__insert(String* str, const String* str_to_insert, size_t index) {
  // todo
}

void String__erase(String* str, size_t pos, size_t len) {
  // todo
}

void String__replace(String* str, size_t pos, size_t len, const String* str_to_replace_with) {
  // todo
}

void String__swap(String* str1, String* str2) {
  // todo
}


