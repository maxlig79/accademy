class Maxim
{
    public: 
    static int maximOfThree(int firstNumber,int secondNumber,int thirdNumber)
    {
        int max = ( firstNumber > secondNumber) ? ((firstNumber > thirdNumber) ? firstNumber : thirdNumber) : ((secondNumber>thirdNumber) ? secondNumber : thirdNumber);
        return max;
    }
};
