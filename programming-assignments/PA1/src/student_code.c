#define GROUP_MAX_SIZE 50
#define ALPHABET_SIZE 26

#include "student_code.h"
#include <stdlib.h>

/**
Question: What are the differences between these commands and the ones for lab1? What do the differences mean?
My Answer:

**/

/***********
 * Strings *
 ***********/

/**
 * This function takes in a c-string and returns it's length.  It **does not** use the strlen(...) function in string.h
 * @param str The string that we will be finding the length of.  It will be null terminated
 * @return The length of the input string
 */
int get_str_length(char* str) {
    int length = 0;

    // While the current character is not the null terminator, increase the value of length
    while (str[length] != '\0') { length++; }

    return length;
}

// Question: How do we know that we've gotten to the end of a c-string?
// Answer: The null terminator '\0' is used to indicate the end of a c-string

/**
 * Returns a pointer to a copy of the original string.  It **does not** use strcpy or any related function (but may use strlen)
 * @param str An input string that is null terminated
 * @return a new char* that copies the input string str
 */
char* copy_str(char* str) {
    int length = get_str_length(str); // Get the length of the the passed-in string

    // If the length of the passed-in string is empty, return NULL, as there's no string to copy
    if (length == 0) { return NULL; }

    // Create a character array of the same length and space in memory as the original string
    char* strCopy = (char*)malloc((length + 1) * sizeof(char));

    // Copy the original string into the new string, character by character
    for (int i = 0; i < length; i++) { strCopy[i] = str[i]; }

    strCopy[length] = '\0'; // Add the null terminator to the end of the new string

    return strCopy; // Return the new string
}

/**
 * Truncates a string to a the given length, not including the null terminator.  If the given length is longer than the original string the original string is returned unchanged.
 * @param str A null-terminated input string
 * @param new_length The length of the output string.
 */
void truncate_string(char* str, int new_length) {
    int length = get_str_length(str); // Get the length of the original string

    if (new_length >= length) { return; } // Return original string if the new length is greater

    str[new_length] = '\0'; // Add the null terminator to the end of the string
}

/**
 * Converts a given string, str, to all uppercase letters
 * @param str A null-terminated input string
 */
void to_uppercase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') { str[i] -= 32; } // If the character is lowercase, convert it to uppercase (ASCII values)
    }
}

/**
 * Converts a given string, str, to all lowercase letters
 * @param str A null-terminated input string
 */
void to_lowercase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        // If the character is uppercase, convert it to lowercase (ASCII values)
        if (str[i] >= 'A' && str[i] <= 'Z') { str[i] += 32; }
    }
}

/**
 * Finds the index of the first usage of a target character, starting from 0.  If it doesn't exist return -1
 * @param str A null-terminated input string
 * @param target A character to find in string
 * @return The index of the first usage of the target character in the string
 */
int find_first_index(char* str, char target) {
    int first_index = -1; // Initialize as if the target character isn't found

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == target) { first_index = i; } // Return the index of the first instance of the target character
    }

    return first_index; // Return the first index of the target character
}

/**
 * Finds the index of the last usage of a target character, starting from 0.  If it doesn't exist return -1
 * @param str A null-terminated input string
 * @param target A character to find in string
 * @return The index of the last usage of the target character in the string
 */
int find_last_index(char* str, char target) {
    int last_index = -1; // Initialize as if the target character isn't found

    if (target >= 'A' && target <= 'Z') { target += 32; } // Convert the target character to lowercase (ASCII)

    for (int i = 0; str[i] != '\0'; i++) {
        char current_char = str[i]; // Get the current character of the string

        // Convert the current character to lowercase (ASCII)
        if (current_char >= 'A' && current_char <= 'Z') { current_char += 32; }

        // Update the last index each time the target character is found
        if (current_char == target) { last_index = i; }
    }

    return last_index; // Return the last index of the target character
}


/**************
 * Structures *
 **************/
/**
 * Create a new person object and return the object
 * @param first_name The first name of the new person as a null-terminated string
 * @param last_name The last name of the new person as a null-terminated string
 * @param age The age of the person as an int
 * @return A Person struct containing the new person
 */
Person person_make_new(char* first_name, char* last_name, int age) {
    Person new_person; // Create a new Person struct

    // Copy first_name to new_person.first_name
    for (int i = 0; i < (sizeof(new_person.first_name) - 1) && (first_name[i] != '\0'); i++) {
        new_person.first_name[i] = first_name[i];
    }

    // Copy last_name to new_person.last_name
    for (int i = 0; i < (sizeof(new_person.last_name) - 1) && (last_name[i] != '\0'); i++) {
        new_person.last_name[i] = last_name[i];
    }

    new_person.age = age;

    return new_person; // Return the Person struct that was created
}
/**
 * Return a string containing the full name and age of the person in the format "First Last (age)"
 * @param person The person to get the relevant string for
 * @return A string containing the name of the person
 */
char* person_to_string(Person person) {

    // Get the length of the string to be created. +6 is added to account for the spaces and parentheses
    int length = get_str_length(person.first_name) + get_str_length(person.last_name) + 6;

    // Allocate memory for the new string
    char* str = (char*)malloc((length + 1) * sizeof(char));

    // Use sprintf to format the string
    sprintf(str, "%s %s (%d)", person.first_name, person.last_name, person.age);

    return str; // Return the person's name and age, as a string
}

/**
 * A function to create a new empty group
 * @param group_name A null-terminated string to name the new group
 * @return A new Group struct
 */
Group group_make_new(char* group_name) {
    Group new_group; // Create a new Group struct

    // Initialize the group with the passed-in name
    new_group.group_name = group_name;

    // Initialize the group with no members
    for (int i = 0; i < GROUP_MAX_SIZE; i++) { new_group.group_members[i] = NULL; }

    // Initialize the number of people in the group to be 0
    new_group.num_members = 0;

    return new_group; // Return the new Group struct
}

/**
 * A function to find the total number of people in the group
 * @param group A Group struct that contains some number of people
 * @return The number of users in the group
 */
int num_people_in_group(Group group) {
    return group.num_members; // Return the number of people in the group
}

/**
 * Get the number of free spaces remaining in the group
 * @param group A Group struct that contains some number of people
 * @return The number of free spaces in the group
 */
int free_spaces_in_group(Group group) { return GROUP_MAX_SIZE - group.num_members; }

/**
 * Add a person to the group if possible and return the total number of free space in the group. Otherwise return -1.
 * @param group A group struct that contains some number of people
 * @param person_to_add The person to add to the group
 * @return The number of free spaces after add the new person, -1 if the group was already full
 */
int add_person(Group* group, Person* person_to_add) {
    // Return -1 if the group is full (or if it's over capacity)
    if (group->num_members >= GROUP_MAX_SIZE) { return -1; }

    // Return -1 if the person is already in the group
    for (int i = 0; i < group->num_members; i++) {
        if (group->group_members[i] == person_to_add) { return -1; }
    }

    // If the group isn't full, add the new person to it
    group->group_members[group->num_members] = person_to_add;

    group->num_members++; // Increment the number of people in the group

    // Calculate the number of free spaces in the group
    int free_space = GROUP_MAX_SIZE - group->num_members;

    // Return the number of free spaces
    return free_space;
}
    // Question: Say we have already added a person to the group and try to add them again.  What should be we do?  Where can we check what the expected behavior is?
    // Answer:

/**
 * Remove a person from the group if they are in the group, otherwise return -1
 * @param group A Group struct that contains some number of people
 * @param person_to_remove A person to remove from the group
 * @return The number of people remaining in the group, -1 if the person was not in the group
 */
int remove_person(Group* group, Person* person_to_remove) {
    int index = -1;

    // Find the index of the person to remove
    for (int i = 0; i < group->num_members; i++) {
        if (group->group_members[i] == person_to_remove) { index = i; break; }
    }

    // If the person isn't in the group, return -1
    if (index == -1) { return -1; }

    // If the person is in the group, remove them
    for (int i = index; i < group->num_members - 1; i++) {
        // Shift all remaining group members to the left
        group->group_members[i] = group->group_members[i + 1];
    }

    group->num_members--; // Decrement the number of people in the group

    return group->num_members; // Return the number of people left in the group
}



/*
 * Caesar Cipher
 */
/**
 * Shift a character 'left' by the shift amount by subtracting the shift size.
 *  e.g. 'a' with a shift_size = 1 will become 'z'
 * @param input_char
 * @param shift_size
 * @return
 */
char shift_left(char input_char, int shift_size) {
    int new_char;

    if (input_char >= 'a' && input_char <= 'z') {
        // Shift the character to the left by the shift size
        new_char = input_char - shift_size;

        // If the new character is less than 'a', add 26 to it (loop back around to the end of the alphabet)
        if (new_char < 'a') { new_char += 26; }

    } else if (input_char >= 'A' && input_char <= 'Z') {
        // Convert the character to lowercase and shift it to the right by the shift size
        new_char = input_char + shift_size + 32;

        // If the new character is less than 'A', add 26 to it (loop back around to the end of the alphabet)
        if (new_char < 'A') { new_char += 26; }
    } else { return input_char; }

    return new_char; // Return the new character
}

/**
 * Shift a character 'right' by the shift amount by subtracting the shift size.
 *  e.g. 'z' with a shift_size = 1 will become 'a'
 * @param input_char
 * @param shift_size
 * @return
 */
char shift_right(char input_char, int shift_size) {
    int new_char;

    if (input_char >= 'a' && input_char <= 'z') {
        // Shift the character to the right by the shift size
        new_char = input_char + shift_size;

        // If the new character is greater than 'z', subtract 26 from it (loop back around to the beginning of the alphabet)
        if (new_char > 'z') { new_char -= 26; }

    } else if (input_char >= 'A' && input_char <= 'Z') {
        // Convert the character to lowercase and shift it to the right by the shift size
        new_char = input_char + shift_size + 32;

        // If the new character is greater than 'Z', subtract 26 from it (loop back around to the beginning of the alphabet)
        if (new_char > 'Z') { new_char -= 26; }
    } else { return input_char; }
}

/**
 * Encrypts a string using a given shift.  Note: All characters should be converted to lowercase
 * @param input_str
 * @param shift_size
 * @return
 */
char* encrypt_caesar(char* input_str, int shift_size) {
    if (input_str == NULL) { return NULL; } // Return NULL if the input string is NULL

    // Convert the input string to lowercase
    char* lower_str = copy_str(input_str);
    to_lowercase(lower_str);

    // Get the length of the input string
    int length = get_str_length(lower_str);

    // Allocate memory for the new string
    char* encrypted_str = (char*)malloc((length + 1) * sizeof(char));

    // Encrypt each character in the input string
    for (int i = 0; i < length; i++) {
        // Shift the character to the right
        encrypted_str[i] = shift_right(lower_str[i], shift_size);
    }

    encrypted_str[length] = '\0'; // Add the null terminator to the end of the new string

    return encrypted_str; // Return the encrypted string
}

/**
 * Decrypts a string using a given shift.  Note: All characters should be converted to lowercase
 * @param input_str
 * @param shift_size
 * @return
 */
char* decrypt_caesar(char* input_str, int shift_size) {
    if (input_str == NULL) { return NULL; } // Return NULL if the input string is NULL

    // Convert the input string to lowercase
    char* lower_str = copy_str(input_str);
    to_lowercase(lower_str);

    // Get the length of the input string
    int length = get_str_length(lower_str);

    // Allocate memory for the new string
    char* decrypted_str = (char*)malloc((length + 1) * sizeof(char));

    // Decrypt each character in the input string
    for (int i = 0; i < length; i++) {
        // Shift the character to the left
        decrypted_str[i] = shift_left(lower_str[i], shift_size);
    }

    decrypted_str[length] = '\0'; // Add the null terminator to the end of the new string

    return decrypted_str; // Return the decrypted string
}

/*
 * General substitution Cipher
 */

/**
 * Returns true if a given encryption key has a valid decryption key.
 * @param encryption_key
 * @return
 */
bool is_reversible(int* encryption_key) {
    if (encryption_key == NULL) { return false; } // Return false if the encryption key is NULL

    int count[ALPHABET_SIZE] = {0}; // Integer array for how many times each letter is used. ex. [0, 1, 1, 0, 2, ...]

    // Please note I call it character here, but this is an int value, *corresponding* to a position in the alphabet
    int current_char; // The character of the encryption key currently being checked

    for(int i = 0; i < ALPHABET_SIZE; i++) {
        current_char = encryption_key[i]; // Get the current character from the encryption key

        // Return false if the current character isn't in the alphabet
        if (current_char < 0 || current_char >= ALPHABET_SIZE) { return false; }

        count[current_char]++;
    }

    // Return false if a character appears, more than once, in the encryption key
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (count[i] != 1) { return false; }
    }
}

/**
 * Generates a decryption key based on the encryption key, if one exists.  Otherwise returns NULL
 * @param encryption_key
 * @return
 */
int* get_decryption_key(int* encryption_key) {
    if (!is_reversible(encryption_key)) { return NULL; } // Return NULL if the encryption key isn't reversible

    int* decryption_key = (int*)malloc(ALPHABET_SIZE * sizeof(int)); // Allocate memory for the decryption key


    for (int i = 0; i < ALPHABET_SIZE; i++) {
        decryption_key[encryption_key[i]] = i; // Generate A decryption key, based on the encryption key
    }

    return decryption_key; // Return the decryption key
}

/**
 * Takes the input string and the encryption key and encrypts the input string in place
 * @param input_str
 * @param encryption_key
 */
void encrypt_substitution(char* input_str, int* encryption_key) {
    to_lowercase(input_str); // Convert the input string to lowercase

    for (int i = 0; input_str[i] != '\0'; i++) {
        // If the character is a lowercase letter, encrypt it
        // Check each character in the input string in case any of them aren't letters
        if (input_str[i] >= 'a' && input_str[i] <= 'z') {
            // The 'a' stuff here is to convert the ASCII value of the character to a value between 0 and 25
            input_str[i] = encryption_key[input_str[i] - 'a'] + 'a';
        }
    }
}

/**
 * Takes an encrypted input string and a decryption key and decrypts a string in place
 * @param input_str
 * @param decryption_key
 */
void decrypt_substitution(char* input_str, int* decryption_key) {
    to_lowercase(input_str); // Convert the input string to lowercase

    for (int i = 0; input_str[i] != '\0'; i++) {
        // If the character is a lowercase letter, decrypt it
        // Check each character in the input string in case any of them aren't letters
        if (input_str[i] >= 'a' && input_str[i] <= 'z') {
            // The 'a' stuff here continues to be to convert the ASCII value of the character to a value between 0 and 25
            input_str[i] = decryption_key[input_str[i] - 'a'] + 'a';
        }
    }
}




