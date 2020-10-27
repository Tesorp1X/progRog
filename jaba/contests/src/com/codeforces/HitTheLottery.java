package com.codeforces;

import java.util.Scanner;

public class HitTheLottery {

    private static int maxAmountOfDollars(int n) {

        int[] dollars = {100, 50, 20, 10, 5, 1};
        for (int i : dollars) {
            if (n >= i) return i;
        }
        return 1;
    }

    public static void main(String[] args) {

        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        in.close();
        int count = 0;
        while (n > 0) {
            ++count;
            n -= maxAmountOfDollars(n);
        }
        System.out.println(count);

    }

}
