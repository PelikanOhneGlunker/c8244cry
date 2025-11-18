# Timestamp in C

</pre>

═══════════════════════════════════════

Here are several ways to get the current time in C:



▓▓▓ 1. Basic Current Time (Unix Timestamp) ▓▓▓



┌─ Code Block ─┐
│ #include <stdio.h>
│ #include <time.h>
│ 
│ int main() {
│     time_t current_time;
│ 
│     // Get current time as seconds since epoch
│     current_time = time(NULL);
│ 
│     printf("Current time (timestamp): %ld\n", current_time);
│ 
│     return 0;
│ }
└──────────────┘



▓▓▓ 2. Formatted Current Time ▓▓▓



┌─ Code Block ─┐
│ #include <stdio.h>
│ #include <time.h>
│ 
│ int main() {
│     time_t current_time;
│     struct tm *time_info;
│     char time_string[100];
│ 
│     // Get current time
│     current_time = time(NULL);
│ 
│     // Convert to local time
│     time_info = localtime(&current_time);
│ 
│     // Format the time
│     strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);
│ 
│     printf("Current time: %s\n", time_string);
│ 
│     return 0;
│ }
└──────────────┘



▓▓▓ 3. More Detailed Time Information ▓▓▓



┌─ Code Block ─┐
│ #include <stdio.h>
│ #include <time.h>
│ 
│ int main() {
│     time_t current_time;
│     struct tm *time_info;
│ 
│     current_time = time(NULL);
│     time_info = localtime(&current_time);
│ 
│     printf("Year: %d\n", time_info->tm_year + 1900);
│     printf("Month: %d\n", time_info->tm_mon + 1);
│     printf("Day: %d\n", time_info->tm_mday);
│     printf("Hour: %d\n", time_info->tm_hour);
│     printf("Minute: %d\n", time_info->tm_min);
│     printf("Second: %d\n", time_info->tm_sec);
│     printf("Day of week: %d (0=Sunday)\n", time_info->tm_wday);
│ 
│     return 0;
│ }
└──────────────┘



▓▓▓ 4. High-Resolution Time (with microseconds) ▓▓▓



┌─ Code Block ─┐
│ #include <stdio.h>
│ #include <sys/time.h>
│ #include <time.h>
│ 
│ int main() {
│     struct timeval tv;
│     struct tm *time_info;
│     char time_string[100];
│ 
│     // Get current time with microsecond precision
│     gettimeofday(&tv, NULL);
│ 
│     // Convert to local time
│     time_info = localtime(&tv.tv_sec);
│ 
│     // Format the time
│     strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);
│ 
│     printf("Current time: %s.%06ld\n", time_string, tv.tv_usec);
│ 
│     return 0;
│ }
└──────────────┘



▓▓▓ 5. Using clock_gettime() for High Precision ▓▓▓



┌─ Code Block ─┐
│ #include <stdio.h>
│ #include <time.h>
│ 
│ int main() {
│     struct timespec ts;
│     struct tm *time_info;
│     char time_string[100];
│ 
│     // Get current time with nanosecond precision
│     clock_gettime(CLOCK_REALTIME, &ts);
│ 
│     // Convert to local time
│     time_info = localtime(&ts.tv_sec);
│ 
│     // Format the time
│     strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);
│ 
│     printf("Current time: %s.%09ld\n", time_string, ts.tv_nsec);
│ 
│     return 0;
│ }
└──────────────┘
</pre>















