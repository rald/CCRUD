#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PRODUCTS_FILE "products.txt"

#define TEMP_FILE "temp.txt"

struct Product
{
    int id;
    char name[16];
    float price;
    int quantity;
};

void flush()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void clrscr(void)
{
    system("clear");
}

void pause()
{
    printf("Press Enter to continue...");
    getchar();
}

int MainMenu(void)
{
    int choice;

    do
    {
        clrscr();

        printf(
            "*** Main Menu ***\n\n"
            "1. Add Product\n"
            "2. List Products\n"
            "3. Update Products\n"
            "4. Remove Product\n"
            "0. Exit\n\n");

        printf("choice: ");
        scanf("%d", &choice);
        flush();

    } while (choice < 0 || choice > 4);

    return choice;
}

void AddProduct(void)
{
    struct Product product;

    FILE *fout = fopen(PRODUCTS_FILE, "a");

    clrscr();

    printf("*** Add Product ***\n\n");

    printf("id: ");
    scanf("%d", &product.id);
    flush();

    printf("name: ");
    scanf("%s", product.name);

    printf("price: ");
    scanf("%f", &product.price);
    flush();

    printf("quantity: ");
    scanf("%d", &product.quantity);
    flush();

    fprintf(fout, "%-7d %-15s %10.2f %8d\n", product.id, product.name, product.price, product.quantity);

    fclose(fout);

    printf("\nproduct added\n\n");

    pause();
}

void ListProducts()
{
    struct Product product;

    FILE *fin = fopen(PRODUCTS_FILE, "r");

    clrscr();

    printf("%-7s %-15s %-10s %-8s\n", "id", "name", "price", "quantity");

    while (fscanf(fin, "%d %s %f %d", &product.id, product.name, &product.price, &product.quantity) == 4)
    {
        printf("%-7d %-15s %10.2f %8d\n", product.id, product.name, product.price, product.quantity);
    }

    fclose(fin);

    printf("\n");

    pause();
}

void UpdateProduct()
{
    int id;
    FILE *fin, *fout;
    struct Product product1, product2;
    bool found = false;
    int ans;

    clrscr();

    printf("*** Update Product ***\n\n");

    printf("Enter product id: ");
    scanf("%d", &id);
    flush();

    fin = fopen(PRODUCTS_FILE, "r");

    while (fscanf(fin, "%d %s %f %d", &product1.id, product1.name, &product1.price, &product1.quantity) == 4)
    {
        if (id == product1.id)
        {
            found = true;
            break;
        }
    }
    fclose(fin);

    if (found)
    {
        printf("\nid: %d\n", product1.id);
        printf("name: %s\n", product1.name);
        printf("price: %.2f\n", product1.price);
        printf("quantity: %d\n\n", product1.quantity);

        printf("new id: ");
        scanf("%d", &product1.id);
        printf("new name: ");
        scanf("%s", product1.name);
        printf("new price: ");
        scanf("%f", &product1.price);
        printf("new quantity: ");
        scanf("%d", &product1.quantity);
        
        printf("\n");

        do
        {
            printf("update product (y/n)? ");
            ans = getchar();
            flush();

        } while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');

        if (ans == 'Y' || ans == 'y')
        {
            fin = fopen(PRODUCTS_FILE, "r");

            fout = fopen(TEMP_FILE, "w");

            while (fscanf(fin, "%d %s %f %d", &product2.id, product2.name, &product2.price, &product2.quantity) == 4)
            {
                if (id == product2.id)
                {
                    fprintf(fout, "%-7d %-16s %10.2f %8d\n", product1.id, product1.name, product1.price, product1.quantity);
                }
                else
                {
                    fprintf(fout, "%-7d %-15s %10.2f %8d\n", product2.id, product2.name, product2.price, product2.quantity);
                }
            }

            fclose(fout);
            fclose(fin);

            remove(PRODUCTS_FILE);
            rename(TEMP_FILE, PRODUCTS_FILE);

            printf("\nproduct updated\n\n");
        }
        else
        {
            printf("\nproduct not updated\n\n");
        }
    }
    else
    {
        printf("\nproduct not found\n\n");
    }

    pause();
}

void RemoveProduct()
{
    int id;
    FILE *fin, *fout;
    struct Product product;
    bool found = false;
    int ans;

    clrscr();

    printf("*** Remove Product ***\n\n");

    printf("Enter product id: ");
    scanf("%d", &id);
    flush();

    fin = fopen(PRODUCTS_FILE, "r");

    while (fscanf(fin, "%d %s %f %d", &product.id, product.name, &product.price, &product.quantity) == 4)
    {
        if (id == product.id)
        {
            found = true;
            break;
        }
    }
    fclose(fin);

    if (found)
    {
        printf("\nid: %d\n", product.id);
        printf("name: %s\n", product.name);
        printf("price: %.2f\n", product.price);
        printf("quantity: %d\n\n", product.quantity);

        do
        {
            printf("remove product (y/n)? ");
            ans = getchar();
            flush();

        } while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');

        if (ans == 'Y' || ans == 'y')
        {
            fin = fopen(PRODUCTS_FILE, "r");

            fout = fopen(TEMP_FILE, "w");

            while (fscanf(fin, "%d %s %f %d", &product.id, product.name, &product.price, &product.quantity) == 4)
            {
                if (id != product.id)
                {
                    fprintf(fout, "%-7d %-16s %10.2f %8d\n", product.id, product.name, product.price, product.quantity);
                }
            }

            fclose(fout);
            fclose(fin);

            remove(PRODUCTS_FILE);
            rename(TEMP_FILE, PRODUCTS_FILE);

            printf("\nproduct removed\n\n");
        }
        else
        {
            printf("\nproduct  not removed\n\n");
        }
    }
    else
    {
        printf("\nproduct not found\n\n");
    }

    pause();
}

int main(void)
{
    bool quit = false;
    int choice;

    while (!quit)
    {
        choice = MainMenu();
        switch (choice)
        {
        case 0:
            quit = true;
            continue;
        case 1:
            AddProduct();
            break;
        case 2:
            ListProducts();
            break;
        case 3:
            UpdateProduct();
            break;
        case 4:
            RemoveProduct();
            break;
        }
    }

    clrscr();
    printf("Bye\n");
}
