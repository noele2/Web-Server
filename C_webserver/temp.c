#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void remove_new_line(char* string)
{
    size_t length = strlen(string);
    if((length > 0) && (string[length-1] == '\n'))
    {
        string[length-1] ='\0';
    }
}

int main(int argc, char const *argv[])
{
    char hello[20000] = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 30\n\n ";


    char line[1000];
    char html[1000000] = "";
    FILE * fpointer = fopen("index.html", "r");

    while (fgets(line, 255, fpointer)){
        // line[ strcspn(line, "\n" ) ] = '\0';
        strcat(html, line);
    }
    
    printf("%s",html);
    fclose(fpointer);

    strcat(hello, html);
    printf("%s",hello);

}

