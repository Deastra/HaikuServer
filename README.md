# HaikuServer

#### Version 1
Two seperate terminals :
* First terminal :  
``` make server ```
* Second terminal:  
``` make client ``` for auto-generated signals or ``` make clientm ``` for manually inputting signals


#### Version 2
### * Method 1
Two seperate terminals :
* First terminal :  
``` gcc -pthread -o hr haiku_reader.c ```
* Second terminal:  
``` gcc -pthread -o hw haiku_writer.c ```

After compilation process is done:
* First terminal :  
``` ./hr ```
* Second terminal:  
``` ./hw ```

### * Method 2
Two seperate terminals :
* First terminal :  
``` make read ```
* Second terminal:  
``` make write ```


#### Version 3
Two seperate terminals :
* First terminal :  
``` make server ```
* Second terminal:  
``` make client ```
