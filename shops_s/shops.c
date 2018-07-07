#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int shops[5];
pthread_mutex_t mutex[5];


int loader_behavior(){
    while(1) {
        int shop_index = rand() % 5;
        if (!pthread_mutex_trylock(&mutex[shop_index])) {
            printf("Loader arrived to shop %d \n", shop_index);
            shops[shop_index] += 400 + rand() % 200;
            printf("Shop %d now contains %d\n", shop_index, shops[shop_index]);
            pthread_mutex_unlock(&mutex[shop_index]);
            printf("Loader left shop %d\n", shop_index);
            sleep(2);
        } else {
            printf("Shop %d is busy, loader goes to sleep\n", shop_index);
            sleep(2);
        }
    }
}


int customer_behavior(int *cust_need){
    while(1) {
        /*
         * Покупатель ищет непустой свободный магазин
         * */

        int shop_index = rand() % 5;
        while(shops[shop_index] != 0 && !pthread_mutex_trylock(&mutex[shop_index])){
            shop_index = rand() % 5;
        }
        /*
         * Делает покупки и засыпает
         * */
        printf("Customer %d arrived to shop %d \n", pthread_self, shop_index);
        if(*cust_need > shops[shop_index]){
            printf("Customer %d bought %d units\n", pthread_self, shops[shop_index]);
            *cust_need -= shops[shop_index];
            shops[shop_index] = 0;
        } else{
            printf("Customer %d bought %d units\n", pthread_self, cust_need);
            shops[shop_index] -= *cust_need;
            *cust_need = 0;
            pthread_exit(*cust_need);
        }
        printf("Customer %d still need %d units\n", pthread_self, *cust_need);
        pthread_mutex_unlock(&mutex[shop_index]);

        sleep(2);

    }
}



int main(){
    pthread_t loader;
    pthread_t customers[3];
    int cust_need[3];

    srand(time(NULL));

    /*
     * Заполнение магазинов и потребностей покупателей
     * */

    for(int i = 0; i < 5; i++) {
        shops[i] = 900 + rand() % 200;
        pthread_mutex_init ( &mutex[i], NULL);
        printf("Shop %d contains %d units\n", i, shops[i]);
    }
    for(int i = 0; i < 3; i++) {
        cust_need[i] = 9000 + rand() % 2000;
        printf("Customer %d wants %d units to buy\n", i, cust_need[i]);
    }

    /*
     * Запуск симуляции
     * */
    pthread_create(&loader, NULL, loader_behavior, NULL);

    for(int i = 0; i < 3; i++)
        pthread_create(&customers[i], NULL, customer_behavior, &cust_need[i]);

    for(int i = 0; i < 3; i++)
        pthread_join(customers[i], NULL);
}