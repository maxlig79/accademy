class maxim
{
public:
    int MaximNumbers(int first, int second, int third)
    {
        int max = (first > second) ? ((first > third) ? first : third) : ((second > third) ? second : third);
        return max;
    }
};