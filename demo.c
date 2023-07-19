#include "ew_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hello {
    char name[64];
    int num;
} Hello;

Hello *MakeHello(const char *name, int num)
{
    Hello *hello = (Hello *)malloc(sizeof(Hello));
    if (!hello) {
        return NULL;
    }
    memset(hello->name, 0, sizeof(hello->name));
    snprintf(hello->name, sizeof(hello->name), "%s", name);
    hello->num = num;
    return hello;
}

void DestroyHello(Hello *hello)
{
    /**
     * TODO: Release other data
    */
    printf("free(%p)\n", hello);
    free(hello);
}


int main(void)
{
    ew_list *hlist = ew_list_create();
    ew_list_set_data_eraser(hlist, (data_eraser_t *)DestroyHello);
    
    int count = 0;
    ew_list_pushback(hlist, MakeHello("dog", ++count));
    ew_list_pushback(hlist, MakeHello("cat", ++count));
    ew_list_pushback(hlist, MakeHello("pig", ++count));
    ew_list_pushback(hlist, MakeHello("duck", ++count));

    ew_list_foreach(it, hlist) {
        Hello *data = (Hello *)it->data;
        printf("[%d] name: (%s)\n", data->num, data->name);
    }

    printf("delete pig\n");
    ew_list_foreach(it, hlist) {
        Hello *data = (Hello *)it->data;
        if (strncmp(data->name, "pig", 3) == 0) {
            ew_list_delete(hlist, it);
            break;
        }
    }

    ew_list_foreach(it, hlist) {
        Hello *data = (Hello *)it->data;
        printf("[%d] name: (%s)\n", data->num, data->name);
    }


    ew_list_destroy(hlist);
}



