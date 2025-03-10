
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

void String__reserve(String* str, size_t new_capacity) {
  if (new_capacity > str->capacity) {
    char* new_data = (char*)malloc(new_capacity);

    if (new_data) {
      memcpy(new_data, str->data, str->length);
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
  } else {
    memset(str->data + new_size, '\0', str->length - new_size);
  }

  str->length = new_size;
  str->data[str->length] = '\0';
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
  size_t new_length = str->length + str_to_add->length;

  if (new_length > str->capacity) {
    String__reserve(str, new_length + 1);
  }

  strncpy(str->data + str->length, str_to_add->data, str_to_add->length);
  str->length = new_length;
  str->data[str->length] = '\0';
}

void String__push_back(String* str, const char char_to_add) {
  String__resize(str, (str->length + 1), char_to_add);
}

void String__pop_back(String* str) {
  String__resize(str, (str->length - 1), '\0');
}

void String__insert(String* str, const String* str_to_insert, size_t index) {
  if (index > str->length) { return; }

  size_t new_length = str->length + str_to_insert->length;

  if (new_length > str->capacity) { String__reserve(str, new_length + 1); }

  memmove(str->data + index + str_to_insert->length, str->data + index, str->length - index);
  memcpy(str->data + index, str_to_insert->data, str_to_insert->length);

  str->length = new_length;
  str->data[str->length] = '\0';
}

void String__erase(String* str, size_t pos, size_t len) {
  if (pos >= str->length) { return; }

  size_t new_length = str->length - len;

  if (new_length > str->length) { return; }

  memmove(str->data + pos, str->data + pos + len, str->length - pos - len);
  str->length = new_length;
  str->data[str->length] = '\0';
}

void String__replace(String* str, size_t pos, size_t len, const String* str_to_replace_with) {
  if (pos >= str->length) { return; }

  size_t new_length = str->length - len + str_to_replace_with->length;

  if (new_length >= str->capacity) { String__reserve(str, new_length + 1); }

  memmove(str->data + pos + str_to_replace_with->length, str->data + pos + len, str->length - pos - len);
  memcpy(str->data + pos, str_to_replace_with->data, str_to_replace_with->length);

  str->length = new_length;
  str->data[str->length] = '\0';
}

void String__swap(String* str1, String* str2) {
  char* temp_data = str1->data;
  size_t temp_length = str1->length;
  size_t temp_capacity = str1->capacity;

  str1->data = str2->data;
  str1->length = str2->length;
  str1->capacity = str2->capacity;

  str2->data = temp_data;
  str2->length = temp_length;
  str2->capacity = temp_capacity;
}


