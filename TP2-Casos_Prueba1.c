#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Listar en pantalla las especies cuyo % de variación es negativo.
int main()
{
    FILE *html;
    FILE *p1;
    char *pchar;
    char *especie;
    char variacion[10];
    char *substring;
    char buffer[2048];


    if (html = fopen("SSL-TP2.html","rt"))
    {
        p1 = fopen("p1.csv","w");
        fprintf(p1, "Especie; Variación\n");

        while (fgets(buffer,2048,html)) // Lee una línea y guarda en buffer.
        {
            if ((pchar = strstr(buffer, "data-order")) && strstr(buffer, "Cdo.</td>")) // Verifica que en la línea existan data order y celda al contado
            {
                /*Leemos la Especie */

                while (*pchar != '>')
                    pchar++;
                int i = 0;
                pchar++;
                substring = strtok(pchar, "</td>");
                especie = substring;
                printf("%s:", especie);

                substring = strtok(NULL, "/"); /*Vencimiento */
                substring = strtok(NULL, "/"); /*Cant. Nominal */
                substring = strtok(NULL, "/");  /*Compra */
                substring = strtok(NULL, "/"); /*Venta */
                substring = strtok(NULL, "/"); // Cant.Nominal
                substring = strtok(NULL, "/"); // Ultimo

               /*Escribamos la Variacion y la Epecie*/

                i = 0;
                substring = strtok(NULL, "/");
                while (i != 3){
                    if (*substring == '>')
                    {
                        i++;
                    }
                    substring++;
                }

                if (*substring == '-')
                {
                    fprintf(p1, "%s;", especie);
                    while (*substring != '<')
                    {
                    fprintf(p1,"%c", *substring);
                    substring++;
                    }
                    fprintf(p1, "\n");
                }
            }
        }
        fclose(html);
        fclose(p1);
    }

    return 0;
}
