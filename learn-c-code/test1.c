
int main()
{
    int this_is_a_number;

    printf( "Please enter a number: " );
    scanf( "%d", &this_is_a_number );
    printf( "You entered %d", this_is_a_number );
    getchar();

    #define MAX(a, b) ((a) < (b) ? (b) : (a))
    int x = 15, y = 10;
    int z = MAX(x++, y++);

    printf("Max is %d", z);

    #define SWAP(a, b) \
      do               \
      {                \
        a ^= b;        \
        b ^= a;        \
        a ^= b;        \
      } while (0)

    int x2 = 10;
    int y2 = 5;
    int z2 = 4;

    if (x2 < 0)
      SWAP(x2, y2);
    else
      SWAP(x2, z2);

    printf(" x2 >>>  is %d", x2 );

    int age;
    printf("Please enter your age");
    scanf("%d", &age);
    if (age < 100)
    {
      printf("You are pretty young!\n");
    }
    else if (age == 100)
    {
      printf("You are old\n");
    }
    else
    {
      printf("You are really old\n");
    }

    return 0;
}
