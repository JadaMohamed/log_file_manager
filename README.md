# Log Analyzer

This C program is designed to analyze log files and extract relevant information based on date intervals. It provides functionalities to read log data from a file, search for logs within a specified date range, and display the results.

## Usage

1. **Compile the program:**
    ```bash
    gcc log_analyzer.c -o log_analyzer
    ```

2. **Run the compiled executable:**
    ```bash
    ./log_analyzer
    ```

3. **Follow the on-screen prompts** to input the start and end dates in the format (YYYY-DD-MM).

4. View the logs that fall within the specified date range.

## Log File Format

The program expects log entries in the following format within the log file:

`fileName#date#errorCode#functionName#message`

- `fileName`: Name of the file where the log originated.
- `date`: Date and time of the log entry in the format (MM/DD/YYYY-HH:MM:SS).
- `errorCode`: Code indicating the type of error.
- `functionName`: Name of the function where the log was generated.
- `message`: Detailed log message.

## Notes

- The program dynamically allocates memory for log entries.
- The log file should be named "log.text" and placed in the same directory as the executable. If not found, the program will attempt to locate it in the parent directory.
- Logs falling within the specified date range will be displayed on the console.

Feel free to customize the program to suit your specific log file format or analysis requirements.
