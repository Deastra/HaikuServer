# HaikuServer
### * Method 1
Two seperate terminals :
* First terminal : ``` gcc -pthread -o hr haiku_reader.c ```
* Second terminal: ``` gcc -pthread -o hw haiku_writer.c ```
After compilation process is done:
* First terminal : ``` ./hr ```
* Second terminal: ``` ./hw ```

### * Method 2
Two seperate terminals :
* First terminal : ``` make read ```
* Second terminal: ``` make write ```
