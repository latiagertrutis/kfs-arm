int main(void)
{
    static int sum; // Expect 0 according to C standard

    if (sum == 0) {
        while (1);
    }
    else {
        return 0;
    }
}
