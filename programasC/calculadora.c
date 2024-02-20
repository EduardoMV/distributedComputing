/**
 * @Eduardo Ulises Martínez Vaca
 */

#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Validar el string
int validar_expresion(const char *exp) {
    int open_parentheses = 0;
    int i;
    for (i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == '(') {
            open_parentheses++;
        } else if (exp[i] == ')') {
            open_parentheses--;
            if (open_parentheses < 0) {
                printf("Error: Los paréntesis no están balanceados. Hay un paréntesis de cierre sin su apertura.\n");
                exit(0);
            }
        }

        // Verificar si hay un número seguido por un paréntesis de apertura sin un operador entre ellos
        if (exp[i] == '(' && i > 0 && exp[i - 1] >= '0' && exp[i - 1] <= '9') {
            printf("Error: Falta un operador antes del paréntesis de apertura.\n");
            exit(0);
        }
    }

    if (open_parentheses > 0) {
        printf("Error: Los paréntesis no están balanceados. Falta un paréntesis de cierre.\n");
        exit(0);
    }

    char *div_by_zero = strstr(exp, "/0");
    if (div_by_zero != NULL) {
        printf("Error: División por cero.\n");
        exit(0);
    }

    return 1;
}

int main(int argc, char *argv[]) {
    //Verifica que se proporcione al menos un argumento
    if (argc <= 1) {
        printf("Error: No se proporcionaron argumentos para evaluar.\n");
        return 1;
    }

    //Concatena los carácteres en un string
    char eval_string[100] = "";
    for (int i = 1; i < argc; i++) {
        strcat(eval_string, argv[i]);
    }

    if (!validar_expresion(eval_string)) {
        printf("Error: Los paréntesis no están balanceados.\n");
        return 1;
    }

    Py_Initialize();
    // Construir la cadena de evaluación de Python
    char python_eval_string[1000] = "print(eval(\"";
    strcat(python_eval_string, eval_string);
    strcat(python_eval_string, "\"))");

    PyRun_SimpleString(python_eval_string);
    Py_Finalize();

    return 0;
}


