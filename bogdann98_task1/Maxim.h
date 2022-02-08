#pragma once

class Maxim{
public:
   static int max(int a,int b, int c){
        if (a>=b && b>=c)
        {
            return a;
        }
        else if(b>=a && a>=c){
            return b;
        }
        else{
            return c;
        }
    }
};