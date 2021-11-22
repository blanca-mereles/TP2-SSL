#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Mismo reporte  pero en una tabla html, indicando en color verde las
filas de las especies cuyo precio de compra y precio de venta es menor al precio
de apertura. */

int main()
{
    FILE *html;
    FILE *P3;
    char *pchar;
    char *especie;
    double compra;
    char bcompra[10];
    double venta;
    char bventa[10];
    double variacion;
    char bvariacion[10];
    double apertura;
    char bapertura[10];
    char *substring;
    char buffer[2048];


    if (html = fopen("SSL-TP2.html","rt"))
    {
        P3 = fopen("P3.html","w");
        fprintf(P3, "<table>\n<tr>\n<th>Especie </th><th>Variacion </th>\n</tr>\n");

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

                substring = strtok(NULL, "/"); /*Vencimiento */
                substring = strtok(NULL, "/"); /*Cant. Nominal */

               /*Guardamos la Compra */

                i = 0;
                substring = strtok(NULL, "/");
                while (i != 2){
                    if (*substring == '>')
                    {
                        i++;
                    }
                    substring++;
                }

                int c = 0;
                while (*substring != '<'){
                    bcompra[c] = *substring;
                    if (bcompra[c] == ',') // Reemplazo coma por punto para poder convertir el string en float.
                    {
                        bcompra[c] = '.';
                    }
                    c++;
                    substring++;
                }

                compra = atof(bcompra);
                printf("Compra: %f\n", compra);

                /*Guardamos la Venta */

                i = 0;
                substring = strtok(NULL, "/");
                while (i != 2){
                    if (*substring == '>')
                    {
                        i++;
                    }
                    substring++;
                }

                c = 0;
                while (*substring != '<'){
                    bventa[c] = *substring;
                    if (bventa[c] == ',') // Reemplazo coma por punto para poder convertir el string en float.
                    {
                        bventa[c] = '.';
                    }
                    c++;
                    substring++;
                }

                venta = atof(bventa);
                printf("Venta: %f\n", venta);

                substring = strtok(NULL, "/"); // Cant.Nominal
                substring = strtok(NULL, "/"); // Ultimo

                /*Guardamos la Variacion */

                i = 0;
                substring = strtok(NULL, "/");
                while (i != 3){
                    if (*substring == '>')
                    {
                        i++;
                    }
                    substring++;
                }

                c = 0;
                while (*substring != '<'){
                    bvariacion[c] = *substring;
                    if (bvariacion[c] == ',') // Reemplazo coma por punto para poder convertir el string en float.
                    {
                        bvariacion[c] = '.';
                    }
                    c++;
                    substring++;
                }
                variacion = atof(bvariacion);
                printf("Variacion: %f\n", variacion);

                substring = strtok(NULL, "/"); // Estilo y color
                substring = strtok(NULL, "/"); // Estilo y color

               /*Guardamos la Apertura */

                i = 0;
                substring = strtok(NULL, "/");
                while (i != 2){
                    if (*substring == '>')
                    {
                        i++;
                    }
                    substring++;
                }

                c = 0;
                while (*substring != '<'){
                    bapertura[c] = *substring;
                    if (bapertura[c] == ',') // Reemplazo coma por punto para poder convertir el string en float.
                    {
                        bapertura[c] = '.';
                    }
                    c++;
                    substring++;
                }
                apertura = atof(bapertura);

                if (variacion < 0)
                {
                    if (venta < apertura && compra < apertura)
                    {
                    fprintf(P3, "<tr>\n");
                    fprintf(P3, "<td> <span style=\"color:#10da10;\">%s </span></td>", especie);
                    fprintf(P3, "<td> <span style=\"color:#10da10;\">%f </span></td>\n", variacion);
                    fprintf(P3, "</tr>\n");
                    }
                    else
                    {
                    fprintf(P3, "<tr>\n");
                    fprintf(P3, "<td> <span>%s </span></td>", especie);
                    fprintf(P3, "<td> <span>%f </span></td>\n", variacion);
                    fprintf(P3, "</tr>\n");
                    }
                }

            }
        }
        fprintf(P3, "</table>\n");
        fclose(html);
        fclose(P3);
    }

    return 0;
}
