
# RE



▓▓▓ Converting Different Data Types to `int` ▓▓▓



▒▒▒ 1. Numeric Types to `int` ▒▒▒


┌─ Code Block ─┐
│ #include <stdio.h>
│ 
│ int main() {
│     // Float to int (truncates decimal part)
│     float f = 3.14;
│     int i1 = (int)f;  // i1 = 3
│ 
│     // Double to int
│     double d = 5.99;
│     int i2 = (int)d;  // i2 = 5
│ 
│     // Char to int (ASCII value)
│     char c = 'A';
│     int i3 = (int)c;  // i3 = 65
│ 
│     // Long to int
│     long l = 1000L;
│     int i4 = (int)l;  // i4 = 1000
│ 
│     printf("float %.2f -> int %d\n", f, i1);
│     printf("double %.2f -> int %d\n", d, i2);
│     printf("char '%c' -> int %d\n", c, i3);
│     printf("long %ld -> int %d\n", l, i4);
│ 
│     return 0;
│ }
└──────────────┘



▒▒▒ 2. String to `int` (Parsing) ▒▒▒


┌─ Code Block ─┐
│ #include <stdio.h>
│ #include <stdlib.h>
│ #include <string.h>
│ 
│ int main() {
│     // Using atoi() - simple but no error checking
│     char str1[] = "123";
│     int num1 = atoi(str1);
│     printf("atoi(\"%s\") = %d\n", str1, num1);
│ 
│     // Using strtol() - better with error checking
│     char str2[] = "456";
│     char *endptr;
│     long num2 = strtol(str2, &endptr, 10);  // base 10
│ 
│     if (*endptr == '\0') {
│         printf("strtol(\"%s\") = %ld (success)\n", str2, num2);
│     } else {
│         printf("Conversion failed at: %s\n", endptr);
│     }
│ 
│     // Hexadecimal string to int
│     char hex[] = "0xFF";
│     int num3 = (int)strtol(hex, NULL, 16);  // base 16
│     printf("hex \"%s\" -> int %d\n", hex, num3);
│ 
│     return 0;
│ }
└──────────────┘



▓▓▓ Converting `int` to `char *` (String) ▓▓▓



▒▒▒ 1. Using `sprintf()` or `snprintf()` ▒▒▒


┌─ Code Block ─┐
│ #include <stdio.h>
│ #include <stdlib.h>
│ 
│ int main() {
│     int number = 12345;
│ 
│     // Method 1: sprintf (less safe)
│     char buffer1[20];
│     sprintf(buffer1, "%d", number);
│     printf("sprintf: %d -> \"%s\"\n", number, buffer1);
│ 
│     // Method 2: snprintf (safer - prevents buffer overflow)
│     char buffer2[20];
│     snprintf(buffer2, sizeof(buffer2), "%d", number);
│     printf("snprintf: %d -> \"%s\"\n", number, buffer2);
│ 
│     // Different formats
│     char hex_buffer[20];
│     snprintf(hex_buffer, sizeof(hex_buffer), "0x%X", number);
│     printf("hex format: %d -> \"%s\"\n", number, hex_buffer);
│ 
│     return 0;
│ }
└──────────────┘



▒▒▒ 2. Dynamic Memory Allocation ▒▒▒


┌─ Code Block ─┐
│ #include <stdio.h>
│ #include <stdlib.h>
│ #include <string.h>
│ 
│ char* int_to_string(int num) {
│     // Calculate required buffer size
│     int len = snprintf(NULL, 0, "%d", num) + 1;
│ 
│     // Allocate memory
│     char *str = malloc(len);
│     if (str == NULL) {
│         return NULL;  // Memory allocation failed
│     }
│ 
│     // Convert int to string
│     snprintf(str, len, "%d", num);
│     return str;
│ }
│ 
│ int main() {
│     int number = -9876;
│     char *str_ptr = int_to_string(number);
│ 
│     if (str_ptr != NULL) {
│         printf("Dynamic conversion: %d -> \"%s\"\n", number, str_ptr);
│         free(str_ptr);  // Don't forget to free!
│     }
│ 
│     return 0;
│ }
└──────────────┘



▓▓▓ Complete Example with Error Handling ▓▓▓



┌─ Code Block ─┐
│ #include <stdio.h>
│ #include <stdlib.h>
│ #include <string.h>
│ #include <errno.h>
│ 
│ // Safe string to int conversion
│ int safe_string_to_int(const char *str, int *result) {
│     char *endptr;
│     errno = 0;
│ 
│     long val = strtol(str, &endptr, 10);
│ 
│     // Check for various errors
│     if (errno == ERANGE) {
│         printf("Error: Number out of range\n");
│         return -1;
│     }
│ 
│     if (endptr == str) {
│         printf("Error: No digits found\n");
│         return -1;
│     }
│ 
│     if (*endptr != '\0') {
│         printf("Error: Invalid characters after number\n");
│         return -1;
│     }
│ 
│     *result = (int)val;
│     return 0;  // Success
│ }
│ 
│ // Safe int to string conversion
│ char* safe_int_to_string(int num) {
│     int len = snprintf(NULL, 0, "%d", num) + 1;
│     char *str = malloc(len);
│ 
│     if (str != NULL) {
│         snprintf(str, len, "%d", num);
│     }
│ 
│     return str;
│ }
│ 
│ int main() {
│     // Test string to int
│     const char *test_strings[] = {"123", "abc", "456def", "999999999999999999"};
│     int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
│ 
│     printf("=== String to Int Conversion ===\n");
│     for (int i = 0; i < num_tests; i++) {
│         int result;
│         printf("Converting \"%s\": ", test_strings[i]);
│ 
│         if (safe_string_to_int(test_strings[i], &result) == 0) {
│             printf("Success -> %d\n", result);
│         } else {
│             printf("Failed\n");
│         }
│     }
│ 
│     // Test int to string
│     printf("\n=== Int to String Conversion ===\n");
│     int test_numbers[] = {0, 123, -456, 999999};
│     int num_numbers = sizeof(test_numbers) / sizeof(test_numbers[0]);
│ 
│     for (int i = 0; i < num_numbers; i++) {
│         char *str_result = safe_int_to_string(test_numbers[i]);
│ 
│         if (str_result != NULL) {
│             printf("Converting %d -> \"%s\"\n", test_numbers[i], str_result);
│             free(str_result);
│         } else {
│             printf("Memory allocation failed for %d\n", test_numbers[i]);
│         }
│     }
│ 
│     return 0;
│ }
└──────────────┘



▓▓▓ Key Points to Remember: ▓▓▓


1. Type Casting: Use (int) for simple numeric conversions
2. String Parsing: Use strtol() instead of atoi() for better error handling
3. Int to String: Use snprintf() for safety, calculate buffer size properly
4. Memory Management: When using dynamic allocation, always free() the memory
5. Error Handling: Always check for conversion errors and edge cases


▓▓▓ Compilation and Testing: ▓▓▓


┌─ Code Block ─┐
│ gcc -o conversion conversion.c -Wall -Wextra
│ ./conversion
└──────────────┘


This should give you a solid foundation for type conversions in C! Let me know if you need
clarification on any specific part.


═══════════════════════════════════════
